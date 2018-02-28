//
// Created by jacquat on 12/01/18.
//

#ifndef GRAPHICCOMPONENT_HPP_
# define GRAPHICCOMPONENT_HPP_

# include <iostream>
# include <vector>
# include <memory>
# include "AComponent.hpp"

namespace SolidEngine {
    class GraphicComponent : public SolidEngine::AComponent {
    public:
        inline static std::vector<int> _ids;

        explicit GraphicComponent(std::string const &s = "", std::string const &text = "")
                : AComponent(std::type_index(typeid(GraphicComponent))),
                  _picturePath(s), _text(text) {
            int i;
            for (i = 0; i < _ids.size(); i++)
                if (_ids[i] == -1)
                    break;
            _id = i;
          std::cout << "id :" << _id << std::endl;
            if (i >= _ids.size())
                _ids.push_back(0);
            else
              _ids[i] = 0;
        }

        ~GraphicComponent() override { _ids[_id] = -1;}

        std::string _picturePath;
        std::string _text;
        int _id;
    };
}


#endif /* GRAPHICCOMPONENT_HPP_ */
