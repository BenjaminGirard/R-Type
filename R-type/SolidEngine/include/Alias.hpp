#ifndef ALIAS_HPP_
# define ALIAS_HPP_

# include <memory>
# include <utility>

namespace SolidEngine {
    #define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

    template<typename T>
    using Sptr = std::shared_ptr<T>;

    template<typename T>
    using Uptr = std::unique_ptr<T>;

};


#endif /* ALIAS_HPP_ */
