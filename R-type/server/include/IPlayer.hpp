#ifndef IPLAYER_HPP_
# define IPLAYER_HPP_

# include <queue>
# include <vector>
# include <string>
# include <cstdint>

struct Package {
};

class IPlayer {
public:
    virtual ~IPlayer() = default;

    virtual std::queue<std::vector<char>> receiveData() = 0;

    virtual bool sendData(std::vector<char> const &data) = 0;

    virtual uint64_t getId() const = 0;

    virtual bool dataAvailable() = 0;

    virtual bool isAuthentified() const = 0;

    virtual bool setUsername(std::string const &) = 0;

    virtual std::string const &getUsername() const = 0;

    virtual bool isDead() const = 0;
};

#endif // ICLIENT_HPP_
