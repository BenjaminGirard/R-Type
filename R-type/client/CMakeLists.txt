cmake_minimum_required(VERSION 3.8)
project(cpp_rtype)

add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-D_WIN32_WINNT=0x0501)

# if (WIN32)
set(Boost_USE_STATIC_LIBS ON)
# endif (WIN32)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
		../SolidEngine/include/AComponent.hpp
		../SolidEngine/include/AEntity.hpp
		../SolidEngine/include/Alias.hpp
		../SolidEngine/include/ASystem.hpp
		../SolidEngine/include/EntityManager.hpp
		../SolidEngine/include/SystemManager.hpp
		../SolidEngine/include/Manager.hpp
        include/GraphicSystem.hpp
		../Common/include/Protocol.hpp
		../Common/include/GraphicComponent.hpp
		src/GraphicSystem.cpp

		src/main.cpp ../SolidEngine/include/Rtype.hpp ../SolidEngine/include/Rtype.hpp ../SolidEngine/include/Mediator.hpp include/EventSystem.hpp src/EventSystem.cpp include/ActionComponent.hpp ../SolidEngine/include/Action.hpp ../SolidEngine/include/Event.hpp include/QuitSystem.hpp include/ClickableComponent.hpp include/InputComponent.hpp include/MenuSystem.hpp src/MenuSytem.cpp include/Client.hpp ../Common/include/LibraryCrossLoader.hpp ../Common/include/LifeComponent.hpp include/NetworkTCPSystem.hpp  src/NetworkTCPSystem.cpp include/TCPDataProtocol.hpp ../Common/include/TeamComponent.hpp ../Common/include/SpeedComponent.hpp ../Common/include/PowerComponent.hpp ../Common/include/DirectionComponent.hpp  ../Common/include/CoolDown.hpp ../Common/include/AMovementComponent.hpp ../Common/include/StraightMoveComponent.hpp ../Common/include/CosHorizontalMovementComponent.hpp  ../Common/include/StraightMoveComponent.hpp ../Common/include/CosHorizontalMovementComponent.hpp include/UDPSystem.hpp src/UDPSystem.cpp src/TCPReceive.cpp src/TCPSend.cpp ../Common/include/ServerIDComponent.hpp)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SolidEngine/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Common/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(rtype_client ${SOURCE_FILES})

if(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)

if (WIN32)
	set (OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Libs/openssl_windows")
	set(OPENSSL_USE_STATIC_LIBS true)
endif(WIN32)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

set(SFML_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libs/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS system audio network graphics window)
include_directories(${SFML_INCLUDE_DIR})
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libs/boost_1_64_0")
find_package(Boost 1.64.0 REQUIRED thread system)
include_directories(${Boost_INCLUDE_DIRS})

find_package (Threads)

target_link_libraries(rtype_client ${SFML_LIBRARIES}
					${SFML_DEPENDENCIES}
					${Boost_LIBRARIES}
					${CMAKE_THREAD_LIBS_INIT}
		            ${OPENSSL_LIBRARIES})
if (UNIX)
	target_link_libraries(rtype_client ${CMAKE_DL_LIBS})
endif(UNIX)
