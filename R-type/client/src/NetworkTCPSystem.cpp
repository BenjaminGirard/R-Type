//
// Created by nicolas on 23/01/2018.
//

#include <iterator>
#include "Rtype.hpp"
#include "NetworkTCPSystem.hpp"
#include "ActionComponent.hpp"
#include "Rtype.hpp"

SolidEngine::NetworkTCPSystem::NetworkTCPSystem(Sptr<Mediator> &mediator,
                                                boost::asio::io_service& io_service,
                                                boost::asio::ssl::context &context):
        ASystem(mediator),
        ANetwork(),
        _receiveMode({
                             { SolidRType::TCPData::USER_AUTHENTICATION_REQUEST,
                                     (&NetworkTCPSystem::receiveAuthentificationRequest) },
                             { SolidRType::TCPData::START_GAME,
                                     (&NetworkTCPSystem::receiveLaunchGame) },
                             { SolidRType::TCPData::USER_ID,
                                     (&NetworkTCPSystem::receiveUserID) },
                             { SolidRType::TCPData::USER_CREATE_ROOM_REQUEST,
                                     (&NetworkTCPSystem::receiveCreateRoom) },
                             { SolidRType::TCPData::USER_ASK_LIST_ROOM_REQUEST,
                                     (&NetworkTCPSystem::receiveAskForRoom) },
                             { SolidRType::TCPData::ROOM_INFO,
                                     (&NetworkTCPSystem::receiveRoomInfo) },
                             { SolidRType::TCPData::USER_ASK_JOIN_ROOM_REQUEST,
                                     (&NetworkTCPSystem::receiveJoinRoom) }
                     }),
        _client(std::make_shared<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(_io_service, context)),
        _isConnected(false),
        _update(false)
{
    _requiredComp.emplace_back(std::type_index(typeid(ActionComponent)));
}

int			SolidEngine::NetworkTCPSystem::send(const std::vector<char>& msg)
{
    std::cout << "sending" << std::endl;
    boost::system::error_code						error;

    boost::asio::write(*_client, (boost::asio::buffer(msg)), error);
    if (error) {
        resetConnection();
        return -1;
    }
    return 0;
}

void	    	SolidEngine::NetworkTCPSystem::resetConnection()
{
    if (!_io_service.stopped())
        _io_service.reset();
    boost::asio::ssl::context context(boost::asio::ssl::context_base::sslv23);
    context.load_verify_file("../R-type/Common/ssl_files/server.crt");
    _client.reset(new boost::asio::ssl::stream<boost::asio::ip::tcp::socket>(_io_service, context));
    _isConnected = false;
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
}

int 			SolidEngine::NetworkTCPSystem::receive()
{
    try
    {
        int												l = 8192;
        std::vector<char>								buf(l);
        boost::system::error_code						error;
        boost::asio::read(*_client, boost::asio::buffer(buf), error);

        if (error) {
            resetConnection();
            return -1;
        }
        int code = static_cast<int>(buf[0]);
        std::cout << "RECIEVE | code: " << std::to_string(code) << std::endl;

        auto it = _receiveMode.find(static_cast<SolidRType::TCPData::COMMAND_TYPE>(code));
        fnct f;
        if (it != _receiveMode.end()) {
            f = it->second;
            return (this->*f)(buf);
        }
        return 0;
    }
    catch (const std::exception &e)
    {
        resetConnection();
        return -1;
    }
}

void		SolidEngine::NetworkTCPSystem::handle_handshake(const boost::system::error_code& error)
{
    std::cout << "handle handshake" << "\n";
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    if (error)
    {
        std::cout << "Handshake failed: " << error.message() << "\n";
        return resetConnection();
    }
    _isConnected = true;
}

void 		SolidEngine::NetworkTCPSystem::handle_connect(const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "handle connect" << "\n";
        _client->async_handshake(boost::asio::ssl::stream_base::client,
                                 boost::bind(&NetworkTCPSystem::handle_handshake, this,
                                             boost::asio::placeholders::error));

    }
    else
    {
        std::cout << "Connect failed: " << error.message() << "\n";
        resetConnection();
    }
}

int        SolidEngine::NetworkTCPSystem::tryConnection()
{
    try
    {
        boost::asio::ip::tcp::resolver::query			query(getHost().c_str(), getPort().c_str());

        boost::asio::ip::tcp::resolver::iterator		iterator = boost::asio::ip::tcp::resolver(_io_service).resolve(query);

        boost::asio::connect(_client->lowest_layer(), iterator);
        _client->async_handshake(boost::asio::ssl::stream_base::client,
                                 boost::bind(&NetworkTCPSystem::handle_handshake, this,
                                             boost::asio::placeholders::error));

        run();

        return 0;
    }
    catch (const boost::system::system_error& ex)
    {
        //std::cout << "connection failed: " << e.what()<< std::endl;
       return -1;
    }
}

bool    	SolidEngine::NetworkTCPSystem::disconnect()
{
    _io_service.stop();
    return (true);
}

void		SolidEngine::NetworkTCPSystem::run()
{
    _io_service.run();
}


void        SolidEngine::NetworkTCPSystem::execute() {
    if (getNetworkType() == UDP)
        return ;
    if (_update) {
        std::this_thread::sleep_for(std::chrono::microseconds(5000));
        if (receive() == SolidRType::TCPData::START_GAME) {
            std::vector<std::string> udp{getPort(), getHost()};
            auto &newEntity = _mediator->pingCreateEntity();
            newEntity.addComp<ActionComponent>(Action::CHANGE_TO_UDP, udp);
            auto &newEntityStart = _mediator->pingCreateEntity();
            newEntityStart.addComp<ActionComponent>(Action::START_GAME);
        }
        if (!_isConnected) {
            auto &newEntity = _mediator->pingCreateEntity();
            newEntity.addComp<ActionComponent>(Action::CREATE_CONNECTION_MENU);
        }
    }
    for (auto &entity: _entityVec) {
        auto &actionComponent = entity->getComp<ActionComponent>();
        switch (actionComponent._action) {
            case CONNECTIONTCP: {
                setPort(std::any_cast<std::vector<std::string>>(actionComponent._data)[0]);
                setHost(std::any_cast<std::vector<std::string>>(actionComponent._data)[1]);

                tryConnection();
                if (!_isConnected) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::CREATE_CONNECTION_MENU);
                    break;
                }
                receive();
                auto &newEntity = _mediator->pingCreateEntity();
                newEntity.addComp<ActionComponent>(Action::PROFILE_MENU);
                break;
            }
            case NAME_AUTHORIZATION: {
                std::string name(std::any_cast<std::vector<std::string>>(actionComponent._data)[0]);

                for (int i = 0; i < sizeof(char[255]); i++)
                    _dataProtocol._playerInfo.username[i] = name.c_str()[i];
                sendAuthentificationRequest(_dataProtocol._playerInfo);

                if (receive() == SolidRType::TCPData::CONFIRM::KO) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::PROFILE_MENU);
                    break;
                }
                if (!_isConnected) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::CREATE_CONNECTION_MENU);
                    break;
                }
                auto &newEntity = _mediator->pingCreateEntity();
                newEntity.addComp<ActionComponent>(Action::MENU);
                break;
            }
            case CREATE_ROOM: {
                std::vector<std::string> tmp(std::any_cast<std::vector<std::string>>(actionComponent._data));
                if (std::isdigit(tmp[0][0]))
                    _dataProtocol._create.roomSize = static_cast<uint8_t>(std::stoi(tmp[0]));
                else {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::CREATE_MENU);
                    break;
                }

                for (int i = 0; i < sizeof(char[255]); i++)
                    _dataProtocol._create.password[i] = tmp[1].c_str()[i];

                sendCreateRoom(_dataProtocol._create);
                receive();
                if (!_isConnected) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::CREATE_CONNECTION_MENU);
                    break;
                }

                sendUserReady(SolidRType::TCPData::CONFIRM::OK);

                _update = true;

                auto &newEntity = _mediator->pingCreateEntity();
                newEntity.addComp<ActionComponent>(Action::WAITING_ROOM_MENU,
                                                   std::make_shared<char>(_dataProtocol._authCreate.info.roomId));
                break;
            }
            case ASK_ROOM_LIST: {
                _dataProtocol._rooms.clear();
                sendAskForRoom();
                receive();
                if (!_isConnected) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::CREATE_CONNECTION_MENU);
                    break;
                }

                std::cout << _dataProtocol._rooms.size() << std::endl;

                auto &newEntity = _mediator->pingCreateEntity();
                newEntity.addComp<ActionComponent>(Action::JOIN_MENU, _dataProtocol._rooms);
                break;
            }
            case JOIN_ROOM_ID: {
                _dataProtocol._askJoin.roomId = *std::any_cast<std::shared_ptr<char>>(actionComponent._data);
                auto &newEntity = _mediator->pingCreateEntity();
                newEntity.addComp<ActionComponent>(Action::JOIN_MENU_PASSWORD);
                break;
            }
            case JOIN_ROOM: {
                std::string pwd = std::any_cast<std::vector<std::string>>(actionComponent._data)[0];
                for (int i = 0; i < sizeof(char[255]); i++)
                    _dataProtocol._askJoin.password[i] = pwd.c_str()[i];

                sendJoinRoom(_dataProtocol._askJoin);
                if (receive() == SolidRType::TCPData::CONFIRM::KO) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::ASK_ROOM_LIST);
                    break;
                }
                if (!_isConnected) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::CREATE_CONNECTION_MENU);
                    break;
                }

                sendUserReady(SolidRType::TCPData::CONFIRM::OK);

                _update = true;

                auto &newEntity = _mediator->pingCreateEntity();
                newEntity.addComp<ActionComponent>(Action::WAITING_ROOM_MENU,
                                                   std::make_shared<char>(_dataProtocol._askJoin.roomId));
                break;
            }
            case LEAVE_ROOM: {
                uint64_t test = *(std::any_cast<std::shared_ptr<char>>(actionComponent._data));
                sendLeaveRoom(*(std::any_cast<std::shared_ptr<char>>(actionComponent._data)));

                _update = false;

                if (!_isConnected) {
                    auto &newEntity = _mediator->pingCreateEntity();
                    newEntity.addComp<ActionComponent>(Action::CREATE_CONNECTION_MENU);
                    break;
                }

                auto &newEntity = _mediator->pingCreateEntity();
                newEntity.addComp<ActionComponent>(Action::MENU);
                break;
            }
            case CHANGE_TO_UDP: {
                _update = false;
                disconnect();
                setNetworkType(UDP);
                std::cout << "changed to udp game can start" << std::endl;
                break ;
            }
            default:
                break;
        }
    }

}