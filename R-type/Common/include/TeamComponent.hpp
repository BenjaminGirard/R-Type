//
// Created by tetard on 21/01/18.
//

#ifndef CPP_RTYPE_TEAMCOMPONENT_HPP
#define CPP_RTYPE_TEAMCOMPONENT_HPP

#include <AComponent.hpp>

enum Team {
    FRIENDLY,
    ENEMY
};

class TeamComponent : public SolidEngine::AComponent {
public:
    TeamComponent(Team team) : AComponent(std::type_index(typeid(TeamComponent))), _team(team) {}

    ~TeamComponent() override = default;

    Team getTeam() const { return _team; }

    void setTeam(Team team) { _team = team; }

private:
    Team _team;
};

#endif //CPP_RTYPE_TEAMCOMPONENT_HPP
