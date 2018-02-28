//
// Created by tetard on 27/01/18.
//

#include <MonsterGeneratorSystem.hpp>
#include <regex>
#include <LibraryCrossLoader.hpp>
#include <experimental/filesystem>
#include <Mediator.hpp>
#include <ASystem.hpp>
#include <InputComponent.hpp>
#include <BalancePowerComponent.hpp>
#include "GeneratorContainerComponent.hpp"
#include <ctime>
#include <cstdlib>
#include <TetardMonster.hpp>
#include <BibMonster.hpp>
#include <GameInstance.hpp>
#include "Mediator.hpp"

MonsterGeneratorSystem::MonsterGeneratorSystem(const std::shared_ptr <SolidEngine::Mediator> &mediator) :
        SolidEngine::ASystem(mediator),
        _monstersGenerators({std::make_shared<BibMonster>()}) {
//#if defined(_MSC_VER)
//  std::string extension(".dll");
//#elif defined(__GNUC__)
//  std::string extension(".so");
//#endif
//    _requiredComp = {
//            std::type_index(typeid(InputComponent)),
//            std::type_index(typeid(BalancePowerComponent)),
//            std::type_index(typeid(GeneratorContainerComponent))
//    };
//
//  std::srand(std::time(0));
//  for(auto& p: std::experimental::filesystem::directory_iterator("./DynamicLibrary")) {
//
//    if (std::regex_match(p.path().string(), std::regex(".*([.]" + std::string(&extension[1] + std::string(")"))))) {
//      std::string path = p.path().string();
//      void *tmp = LibraryCrossLoader::loadLibrary(path.erase(path.size() - extension.size(), path.size()).c_str());
//      if (tmp != nullptr)
//        _libs.push_back(tmp);
//    }
//  }
//
//  for (auto &it : _libs) {
//    void *createFunction = LibraryCrossLoader::loadFunction(it, "createEntity");
//    void *deleteFunction = LibraryCrossLoader::loadFunction(it, "deleteEntity");
//    if (createFunction != nullptr && deleteFunction != nullptr)
//      _monserList.emplace_back(std::make_pair(reinterpret_cast<create_fptr>(createFunction)(), reinterpret_cast<delete_fptr>(deleteFunction)));
//  }
  _requiredComp = {
          std::type_index(typeid(InputComponent)),
          std::type_index(typeid(BalancePowerComponent)),
          std::type_index(typeid(GeneratorContainerComponent))
  };
}

MonsterGeneratorSystem::~MonsterGeneratorSystem() {
//  for (auto &it : _monserList)
//    it.second(it.first);
//  for (auto &it : _libs)
//    LibraryCrossLoader::freeLibraryMemory(it);
}

void MonsterGeneratorSystem::execute() {
//  if (_monserList.empty())
//    return ;
//
//  int32_t balancePlayers = 0;
//  for (auto &it : _entityVec) {
//    it->getComp<BalancePowerComponent>().getPower();
//    auto gunMap = it->getComp<GeneratorContainerComponent>().getGenContainer();
//    for (auto &gun : gunMap)
//      balancePlayers += gun.second->getComp<BalancePowerComponent>().getPower();
//  }
//
//  while (balancePlayers > 0) {
//
//    int rindex = std::rand() % _monserList.size();
//
//    std::cout << balancePlayers << std::endl;
//
//    balancePlayers -= std::stoi(_monserList[rindex].first->getEntityInfo());
//
//    std::cout << balancePlayers << std::endl;
//    _monserList[rindex].first->generateEntity(_mediator, 1080, static_cast<int32_t >(rand() % 1920), -1.0, 0.0);
//  }


  if (_monstersGenerators.empty())
    return ;

  int32_t balancePlayers = 0;
  for (auto &it : _entityVec) {
    balancePlayers += it->getComp<BalancePowerComponent>().getPower();
  }

  while (balancePlayers > 0) {

    int rindex = std::rand() % _monstersGenerators.size();
    balancePlayers -= std::stoi(_monstersGenerators[rindex]->getEntityInfo());

    _monstersGenerators[rindex]->createEntity(_mediator, 1800, static_cast<int32_t >(rand() % 1080), -1.0, 0.0);
  }
}