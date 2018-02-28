//
// Created by tetard on 26/01/18.
//

#include <LifeComponent.hpp>
#include <string>
#include <PowerComponent.hpp>
#include <SizeComponent.hpp>
#include <SpeedComponent.hpp>
#include <StraightMoveComponent.hpp>
#include <TeamComponent.hpp>
#include <GeneratorContainerComponent.hpp>
#include <BalancePowerComponent.hpp>
#include <BasicProjectileGeneratorComponent.hpp>
#include <DeathSystem.hpp>
#include <ImpactSystem.hpp>
#include <InputSystem.hpp>
#include <CollisionSystem.hpp>
#include <CooldownComponent.hpp>
#include <MonsterGeneratorSystem.hpp>
#include <InputComponent.hpp>
#include <System/AutoMoveSystem.hpp>
#include <Component/InputMoveComponent.hpp>
#include "GameConfiguration.hpp"

GameConfiguration::GameConfiguration(SolidEngine::Manager &m, int32_t nbPlayer) {
  m.addSystem<CollisionSystem>();
  m.addSystem<AutoMoveSystem>();
  m.addSystem<ImpactSystem>();
  m.addSystem<InputSystem>();
  m.addSystem<MonsterGeneratorSystem>();
  m.addSystem<DeathSystem>();

  constexpr int32_t basicX = 150;
  constexpr int32_t basicY = 275;

  for (int32_t pindex = 0; pindex < nbPlayer; pindex++) {
    auto &player = m.addEntity();
    player.addComp<CollisionComponent>();
    player.addComp<DirectionComponent>(1, 0);
    player.addComp<SolidEngine::GraphicComponent>("../Assets/ship_130x101_player" + std::to_string(pindex + 1) + ".png");
    player.addComp<LifeComponent>(3, 0);
    player.addComp<PositionComponent>(basicX, basicY + (150 * pindex));
    player.addComp<PowerComponent>(1);
    player.addComp<SizeComponent>(130, 101);
    player.addComp<SpeedComponent>(500);
    player.addComp<InputMoveComponent>(std::make_shared<StraightMoveComponent>());
    player.addComp<TeamComponent>(Team::FRIENDLY);
    player.addComp<BalancePowerComponent>(15);
    player.addComp<GeneratorContainerComponent>();
    player.addComp<InputComponent>();

    auto &generatorContainer = player.getComp<GeneratorContainerComponent>();

    auto &basicGun = m.addEntity();
    basicGun.addComp<SizeComponent>(1, 0);
    basicGun.addComp<DirectionComponent>(1, 0);
    basicGun.addComp<PositionComponent>(basicX + 130, basicY + (150 * pindex) + 50);
    basicGun.addComp<SpeedComponent>(500);
    basicGun.addComp<AutoMoveComponent>(std::make_shared<StraightMoveComponent>());
    basicGun.addComp<TeamComponent>(Team::FRIENDLY);
    basicGun.addComp<BalancePowerComponent>(1);
    basicGun.addComp<CoolDownComponent>(200);
    basicGun.addComp<BasicProjectileGeneratorComponent>("../Assets/little_player" + std::to_string(pindex + 1) + "_projectile40x30.png");

    generatorContainer.addGenerator(&basicGun);
  }

}