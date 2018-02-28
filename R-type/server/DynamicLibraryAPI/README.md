# Dynamic Library API

![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)

Dynamic Library API is a dynamic library that allow you to create monsters.

## How to use it ?

First, you'll have to include ADynamicEntity.hpp in your DefaultMonster.hpp.
```
#include "ADynamicEntity.hpp"
```
Then create a class that heritate from ADynamicEntity.
```
#include "ADynamicEntity.hpp"

class DefaultMonster : public ADynamicEntity {
public:
    DefaultMonster();
    };

```

After this point, in your DefaultMonster.cpp, you will implement a default constructor with components map in parent's parameters.

```
#include "DefaultMonster.hpp"

DefaultMonster::DefaultMonster() :
    ADynamicEntity(
            {
	                {
			                std::type_index(typeid(SolidEngine::GraphicComponent)),
					                std::make_shared<SolidEngine::GraphicComponent>("")
							            },
								                {
										                std::type_index(typeid(LifeComponent)),
												                std::make_shared<LifeComponent>(100)
														            }
															            }) {}
```
Then, use an extern "C" to obtain both function's symbol.
PS : Here, PLUGIN_EXPORT is a maccro for the windows portability that you should put before function implementation.

```
extern "C" {
PLUGIN_EXPORT ADynamicEntity* createEntity()
  {
     return new DefaultMonster();
       }

PLUGIN_EXPORT void deleteEntity(DefaultMonster* object )
  {
      delete object;
        }
	}
```

For last but not least, you have to add you librairie at the end of the CMAKELIST.txt file.
```
add_library(DefaultMonster SHARED DefaultMonster.cpp)
```
Repeat all those operations to add other monsters.

## Author

* **Yohann N'GOALA** - *Initial work* - ***R-Type Epitech***

## Initial work participators

* [Benjamin Girard](https://github.com/BenjaminGirard)
* [Nicolas Dejean](https://github.com/Nicolasdejean)
* [Yohann N'Goala](https://github.com/YohannNgoala)
* Sebastien Vidal
* Matteo Margeritte
* Ugo Pereira
* Thibaut Jacquart
