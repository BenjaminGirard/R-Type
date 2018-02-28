cmake_minimum_required(VERSION 3.8)
project(cpp_rtype)

add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-D_WIN32_WINNT=0x0501)
add_definitions(-g3)

set(Boost_USE_STATIC_LIBS ON)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
		../SolidEngine/include/Mediator.hpp
        ../SolidEngine/include/AComponent.hpp
		../SolidEngine/include/Action.hpp
        ../SolidEngine/include/AEntity.hpp
        ../SolidEngine/include/Alias.hpp
        ../SolidEngine/include/ASystem.hpp
        ../SolidEngine/include/EntityManager.hpp
		../SolidEngine/include/Event.hpp
		../SolidEngine/include/Id.hpp
        ../SolidEngine/include/SystemManager.hpp
        ../SolidEngine/include/Manager.hpp
        ../SolidEngine/include/Rtype.hpp

		src/main.cpp
		src/BoostServer.cpp
		src/Session.cpp
		src/Server.cpp
        src/Core.cpp
		src/PacketHandler.cpp
		src/RoomManager.cpp
        src/Room.cpp

		src/AutoMoveSystem.cpp
        include/Room.hpp
		src/UdpServer.cpp

        src/DeathSystem.cpp
        src/ImpactSystem.cpp
        src/InputSystem.cpp
        src/MonsterGeneratorSystem.cpp

        DynamicLibraryAPI/TetardMonster.cpp
		DynamicLibraryAPI/BibMonster.cpp
#		DynamicLibraryAPI/MatteusMonster.cpp
#		DynamicLibraryAPI/StitchMonster.cpp
#		DynamicLibraryAPI/SmartieMonster.cpp
#		DynamicLibraryAPI/FlakyxMonster.cpp
#		DynamicLibraryAPI/TekMonster.cpp
#		DynamicLibraryAPI/SolidMonster.cpp
#		DynamicLibraryAPI/YougoMonster.cpp)
		include/UsernameHandler.hpp
		src/UsernameHandler.cpp
		src/GameInstance.cpp
		include/GameInstance.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SolidEngine/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Common/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/DynamicLibraryAPI)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Component)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/System)

add_executable(rtype_server ${SOURCE_FILES})

find_package (Threads)

if (WIN32)
	set (OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Libs/openssl_windows")
	set(OPENSSL_USE_STATIC_LIBS true)
endif(WIN32)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(Threads)

set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../Libs/boost_1_64_0")
find_package(Boost 1.64.0 REQUIRED thread system)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(rtype_server ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

if (UNIX)
	target_link_libraries(rtype_server stdc++fs)
endif (UNIX)
