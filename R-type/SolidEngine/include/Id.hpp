# ifndef ID_HPP_
# define ID_HPP_

# include <vector>
# include <iostream>
# include <mutex>

namespace SolidEngine {
    class IntIDFactory {
    private:
        inline static uint64_t _id;
        inline static std::vector<uint64_t> _unusedIds;
        inline static std::mutex counter_mutex;

    public:
        static uint64_t getNextId() noexcept {
          std::unique_lock<std::mutex> lock(counter_mutex);
          if (!_unusedIds.empty()) {
              uint64_t to_return = _unusedIds.back();
            _unusedIds.pop_back();
            return to_return;
          }
          return _id++;
        }

        static void addUnusedId(uint64_t _unused) noexcept {
          std::unique_lock<std::mutex> lock(counter_mutex);
          _unusedIds.push_back(_unused);
        }
    };
};

#endif /* ID_HPP_ */
