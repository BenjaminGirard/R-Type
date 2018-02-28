//
// Created by jacquat on 25/01/18.
//

#include <PositionComponent.hpp>
#include <SizeComponent.hpp>
#include <GraphicComponent.hpp>
#include <LifeComponent.hpp>
#include "ServerIDComponent.hpp"
#include "Binary.hpp"
#include "Protocol.hpp"
#include "ActionComponent.hpp"
#include "UDPSystem.hpp"
#include "Rtype.hpp"

using boost::asio::ip::udp;

SolidEngine::UDPSystem::UDPSystem(Sptr<Mediator> &mediator, boost::asio::io_service &io_service, std::mutex &mutex)
    :ASystem(mediator), ANetwork(), _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
     _io_service(io_service), _mutex(mutex)
{
  _requiredComp.emplace_back(std::type_index(typeid(ActionComponent)));

  _input[UP] = SolidRType::UDPData::INPUT::UP;
  _input[DOWN] = SolidRType::UDPData::INPUT::DOWN;
  _input[LEFT] = SolidRType::UDPData::INPUT::LEFT;
  _input[RIGHT] = SolidRType::UDPData::INPUT::RIGHT;
  _input[PAUSE_INPUT] = SolidRType::UDPData::INPUT::PAUSE_INPUT;
  _input[SHOOT] = SolidRType::UDPData::INPUT::SHOOT;
  _input[QUIT] = SolidRType::UDPData::INPUT::QUIT;

  _action[SolidRType::UDPData::COMMAND_TYPE::ADD_ELEMENT] = &SolidEngine::UDPSystem::addElement;
  _action[SolidRType::UDPData::COMMAND_TYPE::UPDATE_ELEMENT] = &SolidEngine::UDPSystem::updateElement;
  _action[SolidRType::UDPData::COMMAND_TYPE::DELETE_ELEMENT] = &SolidEngine::UDPSystem::deleteElement;
  _action[SolidRType::UDPData::COMMAND_TYPE::CHANGE_GAME_STATUS] = &SolidEngine::UDPSystem::changeGameStatus;

  auto &entity = _mediator->pingCreateEntity();
  entity.addComp<PositionComponent>(0, 0);
  entity.addComp<SizeComponent>(1920, 1080);
  entity.addComp<GraphicComponent>("../Assets/test.png");
}

SolidEngine::UDPSystem::~UDPSystem()
{
    if (_t.joinable())
        _t.join();
}

void SolidEngine::UDPSystem::connect() {
  udp::resolver resolver(_io_service);
  udp::resolver::query query(udp::v4(), getHost(), getPort());
  udp::resolver::iterator iter = resolver.resolve(query);
  _remote_endpoint = *iter;

  _id = getServerId();

  this->startReceive();
  _t = std::thread([this] { this->_io_service.run(); });

  std::vector<char> pingCreate(1024);

  SolidRType::UdpPkg<SolidRType::UDPData::PingPackage> to_serialize;
  std::memset(&to_serialize, 0, sizeof(SolidRType::UdpPkg<SolidRType::UDPData::PingPackage>));
  to_serialize.id = _id;
  to_serialize.pkg_id = SolidRType::UDPData::PING;
  pingCreate << to_serialize;

  _socket.async_send_to(boost::asio::buffer(pingCreate), _remote_endpoint,
                        boost::bind(&UDPSystem::handleSend, this, boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred));

}

void SolidEngine::UDPSystem::addElement()
{
  SolidRType::UdpPkg<SolidRType::UDPData::AddElementInfo > pkg;
  pkg << _data;
  auto &entity = _mediator->pingCreateEntity();
  entity.addComp<ServerIDComponent>(pkg.data.elementId);
  entity.addComp<PositionComponent>(pkg.data.PhysicalInfo.x, pkg.data.PhysicalInfo.y);
  entity.addComp<SizeComponent>(pkg.data.PhysicalInfo.sizex, pkg.data.PhysicalInfo.sizey);
  entity.addComp<GraphicComponent>(pkg.data.path);

  std::cout << "Path received = " << pkg.data.path << std::endl;
    if (pkg.data.metaInfo.isPlayer) {
        entity.addComp<LifeComponent>(pkg.data.metaInfo.nbLives);
    }
}

void SolidEngine::UDPSystem::updateElement() {
  std::cout << "update element" << std::endl;
  SolidRType::UdpPkg<SolidRType::UDPData::UpdateElementInfo> pkg;
  pkg << _data;

  try {
    auto &entity = findEntityServerId(pkg.data.elementId);
    auto &pos = entity.getComp<PositionComponent>();
    pos.x = pkg.data.PhysicalInfo.x;
    pos.y = pkg.data.PhysicalInfo.y;
    std::cout << "POS X:" << pos.x << std::endl;
    std::cout << "POS Y:" << pos.y << std::endl;

    auto &size = entity.getComp<SizeComponent>();
    size.width = pkg.data.PhysicalInfo.sizex;
    size.height = pkg.data.PhysicalInfo.sizey;

  } catch (const std::invalid_argument &e) { std::cout << e.what() << std::endl; }
}
void SolidEngine::UDPSystem::deleteElement()
{
    SolidRType::UdpPkg<SolidRType::UDPData::DeleteElementInfo > pkg;
    pkg << _data;

  try {
    auto &entity = findEntityServerId(pkg.data.elementId);
    _mediator->pingDeleteEntity(&_mediator->getEntity(entity.getId()));
  } catch (const std::invalid_argument &e) { std:: cout << e.what() << std::endl;}
}

void SolidEngine::UDPSystem::changeGameStatus()
{
    SolidRType::UdpPkg<SolidRType::UDPData::ChangeGameStatus> pkg;
    pkg << _data;
}

void SolidEngine::UDPSystem::execute()
{
  static bool isConnected = false;

  if (getNetworkType() == TCP)
    return;

  if (isConnected == false) {
    connect();
    isConnected = true;
  }

  for (auto &entity : _entityVec) {

    auto &actionComponent = entity->getComp<ActionComponent>();
    if (actionComponent._action >= UP && actionComponent._action <= SHOOT) {

      try {
        SolidRType::UDPData::CommonClientHeader header;
        header.clientId = _id;
        header.CommandType = SolidRType::UDPData::USER_INPUT;

        SolidRType::UDPData::UserInput userInput;
        userInput.Header = header;
        userInput.inputUser = _input[actionComponent._action];
        std::vector<char> buffer(1024);

        SolidRType::UdpPkg<SolidRType::UDPData::UserInput> package;
        package.id = _id;
        package.pkg_id = SolidRType::UDPData::USER_INPUT;
        package.data = userInput;

        buffer << package;

        _socket.async_send_to(boost::asio::buffer(buffer), _remote_endpoint,
                              boost::bind(&UDPSystem::handleSend, this, boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));

      } catch (const std::invalid_argument &e) { std::cout << e.what() << std::endl; }

      std::cout << "Try Send !" << std::endl;
    }
  }
}

void SolidEngine::UDPSystem::handleSend(const boost::system::error_code& error,
                                        std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::cout << "Send Succeed ! Size : " << bytes_transferred << std::endl;
    }
}

void SolidEngine::UDPSystem::startReceive()
{
    std::cout << "Receive !" << std::endl;
    _socket.async_receive_from(
            boost::asio::buffer(_data), _remote_endpoint,
            boost::bind(&UDPSystem::handleReceive, this,
                        boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void SolidEngine::UDPSystem::handleReceive(const boost::system::error_code& error, std::size_t)
{
 // _mutex.lock();
  if (!error || error == boost::asio::error::message_size) {
    uint8_t tmpPkgId;
    int64_t tmpId;
    std::memcpy(&tmpId, &_data[0], sizeof(int64_t));
    std::memcpy(&tmpPkgId, &_data[sizeof(int64_t)], sizeof(uint8_t));
    std::cout << SolidRType::UDPData::COMMAND_TYPE::UPDATE_ELEMENT << std::endl;
    std::cout << tmpId << std::endl;
    std::cout << (int)tmpPkgId << std::endl;
    std::cout << "size action : " << _action.size() << std::endl;
    if (_action.find(tmpPkgId) != _action.end())
      _action[tmpPkgId](*this);
    else
      std::cout << "C est pas dans la map" << std::endl;
    std::cout << "Receive ! " << std::endl;
  } else
    std::cout << "Error !" << std::endl;
  //_mutex.unlock();
  startReceive();
}

SolidEngine::AEntity &SolidEngine::UDPSystem::findEntityServerId(uint64_t sid) const {
  auto entities = _mediator->pingGetEntitiesByComp(std::type_index(typeid(ServerIDComponent)));
  for (auto &it : entities) {
    auto &SidComp = it->getComp<ServerIDComponent>();
    std::cout << "Sid == " << sid << " vs me == " << SidComp._id << std::endl;
    if (SidComp._id == sid)
      return *it;
  } throw std::invalid_argument("no matching id for Server id in findEntityServerId");
};
