//
// Created by jacquat on 17/01/18.
//

#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

# include <unordered_map>
# include <SFML/Graphics.hpp>
# include "GraphicSystem.hpp"
# include "Event.hpp"
# include "Action.hpp"
# include "ASystem.hpp"
#include "TCPDataProtocol.hpp"

namespace SolidEngine {

    class EventSystem : public ASystem {
    public:
        explicit EventSystem(Sptr<Mediator> &mediator);
        void execute() override;
        void addEvent(Event event, Action action) { _events[event] = action; }
        std::any findTCPInfo(Action action, uint64_t id = 0);

    private:
        std::unordered_map<Event, Action> _events;
    };
}


#endif /* EVENTSYSTEM_HPP */
