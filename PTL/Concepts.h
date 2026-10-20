#pragma once

namespace hgptl::detail {
/*
    ----------------------------------- 
    concepts
    -------------------------------------
*/

    template<typename T, typename ... Args>
        concept all_same_as = (std::same_as<T, Args> && ...) && (sizeof...(Args) > 0);

}

namespace hgptl::devices::detail {
template<typename T>
concept register_field = requires {
    typename T::value_type;
    typename T::access;
    requires std::is_enum_v<typename T::value_type>;
    requires access_policy<typename T::access>;
    T::pos;
    T::width;
    T::mask;
};

}