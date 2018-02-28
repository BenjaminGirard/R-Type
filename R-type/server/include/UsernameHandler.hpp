//
// Created by matteo on 28/01/18.
//

#ifndef CPP_RTYPE_USERNAMEHANDLER_HPP
#define CPP_RTYPE_USERNAMEHANDLER_HPP

#include <unordered_set>
#include <string>

class UsernameHandler {
    std::unordered_set<std::string> _usernames;

public:
    UsernameHandler() = default;

    ~UsernameHandler() = default;

    UsernameHandler(const UsernameHandler &) = delete;

    UsernameHandler &operator=(const UsernameHandler &) = delete;

    bool addUsername(const std::string &username);

    void removeUsername(const std::string &username);
};


#endif //CPP_RTYPE_USERNAMEHANDLER_HPP
