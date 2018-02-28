//
// Created by matteo on 28/01/18.
//

#include <fstream>
#include <iostream>
#include "UsernameHandler.hpp"

bool UsernameHandler::addUsername(const std::string &username) {
    return  _usernames.insert(username).second;
}

void UsernameHandler::removeUsername(const std::string &username) {
    _usernames.erase(username);
}

