//
// Created by jacquat on 13/01/18.
//

#ifndef RTYPE_HPP_
# define RTYPE_HPP_

# include "Action.hpp"
# include "Event.hpp"
# include "Manager.hpp"

void SolidEngine::Mediator::stop() { _manager->stop(); }
void SolidEngine::Mediator::start() { _manager->start(); }
void SolidEngine::Mediator::pingDeleteComponent(AEntity *entity) { _manager->removeComponent(entity->getId()); }
void SolidEngine::Mediator::pingCreateComponent(AEntity *entity){ _manager->addComponent(entity->getId()); }
void SolidEngine::Mediator::pingDeleteEntity(AEntity *entity){ _manager->removeEntity(entity->getId()); }
SolidEngine::AEntity &SolidEngine::Mediator::pingCreateEntity(){ return _manager->addEntity(); }
SolidEngine::AEntity &SolidEngine::Mediator::getEntity(uint64_t id){ return _manager->getEntity(id); }
std::vector<std::shared_ptr<SolidEngine::AEntity>> SolidEngine::Mediator::pingGetEntitiesByComp(std::type_index t) {return _manager->getEntitiesByComp(t); }


void    SolidEngine::AEntity::addComponent() { _mediator->pingCreateComponent(this); }
void    SolidEngine::AEntity::removeComponent(){ _mediator->pingDeleteComponent(this); }

#endif /* RTYPE_HPP_ */
