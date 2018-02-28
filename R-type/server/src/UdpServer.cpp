//
// Created by pereira on 24/01/2018.
//

#include <PositionComponent.hpp>
#include <SizeComponent.hpp>
#include <CollisionComponent.hpp>
#include <DirectionComponent.hpp>
#include <GraphicComponent.hpp>
#include <LifeComponent.hpp>
#include <PowerComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <TeamComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <IdPlayerComponent.hpp>
#include <Component/InputMoveComponent.hpp>
#include <Component/AutoMoveComponent.hpp>
#include <Component/CooldownComponent.hpp>
#include <Component/BasicProjectileGeneratorComponent.hpp>
#include "MessageComponent.hpp"
#include "UdpServer.hpp"
#include "InputComponent.hpp"

SolidEngine::UdpServer::UdpServer(Sptr<Mediator> &mediator, boost::asio::io_service &io_service, std::mutex &mutex, uint32_t nbPlayers)
: ASystem(mediator), _ioService(io_service), _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 4242)),
  _rcvFct({
       {SolidRType::UDPData::UPDATE_ELEMENT, &SolidEngine::UdpServer::updateElem},
       {SolidRType::UDPData::DELETE_ELEMENT ,&SolidEngine::UdpServer::delElem},
       {SolidRType::UDPData::USER_INPUT ,&SolidEngine::UdpServer::UpdtInput},
       {SolidRType::UDPData::ADD_ELEMENT ,&SolidEngine::UdpServer::addElem},
       {SolidRType::UDPData::CHANGE_GAME_STATUS ,&SolidEngine::UdpServer::changeStatus}
   }), _mutex(mutex), _nbPlayers(nbPlayers)
{
    _requiredComp = {
            std::type_index(typeid(MessageComponent)),
            std::type_index(typeid(InputComponent)),
            std::type_index(typeid(IdPlayerComponent))
    };
    this->start_receive();
    _t = std::thread([this]{_ioService.run();});
}

SolidEngine::UdpServer::~UdpServer() {
    _ioService.stop();
    if (_t.joinable())
        _t.join();
}

void SolidEngine::UdpServer::start_receive()
{
    _socket.async_receive_from(boost::asio::buffer(_recv_buffer), _remote_endpoint,
                               boost::bind(&UdpServer::handle_receive, this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void SolidEngine::UdpServer::addPlayer(int64_t Id)
{

  constexpr int32_t basicX = 150;
  constexpr int32_t basicY = 275;

  static int pindex = 0; // to be changed with a static queue

  std::cout << "player " << pindex << " created of " << _nbPlayers << std::endl;
  auto &newPlayer = _mediator->pingCreateEntity();

  newPlayer.addComp<CollisionComponent>();
  newPlayer.addComp<DirectionComponent>(1, 0);
  newPlayer.addComp<SolidEngine::GraphicComponent>("../Assets/ship_130x101_player" + std::to_string(pindex % 4 + 1) + ".png");
  newPlayer.addComp<LifeComponent>(3, 0);
  newPlayer.addComp<PositionComponent>(basicX, basicY + (150 * (pindex % 4 + 1)));
  newPlayer.addComp<PowerComponent>(1);
  newPlayer.addComp<SizeComponent>(130, 101);
  newPlayer.addComp<SpeedComponent>(500);
  newPlayer.addComp<InputMoveComponent>(std::make_shared<StraightMoveComponent>());
  newPlayer.addComp<TeamComponent>(Team::FRIENDLY);
  newPlayer.addComp<BalancePowerComponent>(15);
  newPlayer.addComp<GeneratorContainerComponent>();
  newPlayer.addComp<IdPlayerComponent>(Id);
  newPlayer.addComp<InputComponent>();
  newPlayer.addComp<MessageComponent>();


  auto &generatorContainer = newPlayer.getComp<GeneratorContainerComponent>();
  generatorContainer.addGenerator(std::make_shared<BasicProjectileGeneratorComponent>("../Assets/little_player" + std::to_string(pindex % 4 + 1) + "_projectile40x30.png"));

  SolidRType::UDPData::AddElementInfo newPlayerInfo;
  std::memset(&newPlayerInfo, 0, sizeof(SolidRType::UDPData::AddElementInfo));

  newPlayerInfo.elementId = Id;

  std::string path = newPlayer.getComp<SolidEngine::GraphicComponent>()._picturePath;
  std::memcpy(newPlayerInfo.path, &(path.c_str()[0]), path.size());
  newPlayerInfo.PhysicalInfo.x = newPlayer.getComp<PositionComponent>().x;
  newPlayerInfo.PhysicalInfo.y = newPlayer.getComp<PositionComponent>().y;
  newPlayerInfo.PhysicalInfo.sizex = newPlayer.getComp<SizeComponent>().width;
  newPlayerInfo.PhysicalInfo.sizey = newPlayer.getComp<SizeComponent>().height;
  newPlayerInfo.metaInfo.isPlayer = 1;
  newPlayerInfo.metaInfo.level = 0;
  newPlayerInfo.metaInfo.nbLives = 3;

  pindex++;
  if (pindex == _nbPlayers) {
    auto &MsgComp = newPlayer.getComp<MessageComponent>();
    MsgComp.pushInfoToSend<SolidRType::UDPData::AddElementInfo>(newPlayer.getId(), SolidRType::UDPData::ADD_ELEMENT, newPlayerInfo);
    for (auto &it : _newPlayersPackages)
      MsgComp.pushInfoToSend<SolidRType::UDPData::AddElementInfo>(newPlayer.getId(), SolidRType::UDPData::ADD_ELEMENT, it);
  }
  else _newPlayersPackages.push_back(newPlayerInfo);

  _players.insert(std::make_pair(Id, _remote_endpoint));
}

void SolidEngine::UdpServer::updateElem(int8_t IdPkg, int64_t Id)
{
    SolidRType::UdpPkg<SolidRType::UDPData::UpdateElementInfo> pkg;
    pkg << _recv_buffer;

    for (auto &it : _entityVec)
    {
        if (it->getId() == Id)
        {

        }
    }
}

void SolidEngine::UdpServer::delElem(int8_t IdPkg, int64_t Id)
{
    SolidRType::UdpPkg<SolidRType::UDPData::DeleteElementInfo> pkg;
    pkg << _recv_buffer;

    for (auto &it : _entityVec)
    {
        if (it->getId() == Id)
        {

        }
    }
}

void SolidEngine::UdpServer::UpdtInput(int8_t IdPkg, int64_t Id)
{
    SolidRType::UdpPkg<SolidRType::UDPData::UserInput> pkg;
    pkg << _recv_buffer;

    std::cout << "je rentre pour update input" << std::endl;
    for (auto &it : _entityVec)
    {
        std::cout << "yo" << std::endl;
        if (it->getComp<IdPlayerComponent>()._playerId == Id)
        {
            std::cout << "j'update input" << std::endl;
            auto &input_comp = it->getComp<InputComponent>();

          if (pkg.data.inputUser == SolidRType::UDPData::INPUT::UP)
            std::cout << "UP ::::::: !!!" << std::endl;
          else if (pkg.data.inputUser == SolidRType::UDPData::INPUT::LEFT)
            std::cout << "LEFT ::::::: !!!" << std::endl;
          else if (pkg.data.inputUser == SolidRType::UDPData::INPUT::RIGHT)
            std::cout << "RIGHT ::::::: !!!" << std::endl;
          if (pkg.data.inputUser == SolidRType::UDPData::INPUT::DOWN)
            std::cout << "DOWN ::::::: !!!" << std::endl;

            input_comp.push(pkg.data.inputUser);
        }
    }
}

void SolidEngine::UdpServer::addElem(int8_t IdPkg, int64_t Id)
{
    SolidRType::UdpPkg<SolidRType::UDPData::AddElementInfo> pkg;
    pkg << _recv_buffer;

    for (auto &it : _entityVec)
    {
        if (it->getId() == Id)
        {

        }
    }
}

void SolidEngine::UdpServer::changeStatus(int8_t IdPkg, int64_t Id)
{
    SolidRType::UdpPkg<SolidRType::UDPData::ChangeGameStatus> pkg;
    pkg << _recv_buffer;

    for (auto &it : _entityVec)
    {
        if (it->getId() == Id)
        {

        }
    }
    /*auto &status_comp = it->getComp<>();
    status_comp.push(_pkg->status);*/
}

void SolidEngine::UdpServer::handle_receive(const boost::system::error_code& error, std::size_t len)
{
  _mutex.lock();
  std::cout << "received a package" << std::endl;
    if (!error || error == boost::asio::error::message_size)
    {
        int8_t tmpPkgId;
        int64_t tmpId;

        if (_recv_buffer.size() >= sizeof(int64_t) + sizeof(int8_t)) {
            std::memcpy(&tmpId, &_recv_buffer[0], sizeof(int64_t));
            std::memcpy(&tmpPkgId, &_recv_buffer[sizeof(int64_t)], sizeof(int8_t));
            std::cout << "j ai bien recu" << tmpId <<  std::endl;
            if (tmpPkgId == SolidRType::UDPData::PING)
              addPlayer(tmpId);
            else if (_rcvFct.find(tmpPkgId) != _rcvFct.end()) {
                std::cout << "je call" << std::endl;
                _rcvFct[tmpPkgId](*this, tmpPkgId, tmpId);
            }
        }
        else
            std::cerr << "packet is corrupt and disrispect the protocol" << std::endl;
    }
  _mutex.unlock();
  this->start_receive();
}

void SolidEngine::UdpServer::send_to(std::vector<char> &send_buff, int64_t Id)
{
  if (_players.find(Id) != _players.end())
  {
//  for (auto &it : _players)
    _socket.async_send_to(boost::asio::buffer(send_buff), _players[Id],
                          boost::bind(&UdpServer::handle_send, this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
  }
}

void SolidEngine::UdpServer::execute()
{
  for (auto &i : _entityVec)
  {
    if (i->hasComp<MessageComponent>()) {
      auto &cmp = i->getComp<MessageComponent>();
      std::vector<char> msg;
      while (true)
      {
        if (!_players.empty())
          msg = std::move(cmp.tryPop());
        else
          msg.clear();
        if (!msg.empty())
        {
          for (auto &it : _players)
          {
            std::cout << "j envoie" << std::endl;
            send_to(msg, it.first);
          }
        }
        else break;
      }
    }
  }
}

void SolidEngine::UdpServer::handle_send(const boost::system::error_code &error, std::size_t)
{
    if (!error || error == boost::asio::error::message_size) {
        std::cout << "Send Succeed ! Size : " << std::endl;
    }
}

void SolidEngine::UdpServer::check_sum_crc()
{

}