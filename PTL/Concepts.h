#pragma once

#include <concepts>
#include <type_traits>

#include "Access.h"

/*
    ----------------------------------- 
    concepts
    -------------------------------------
    */

    template<typename T, typename ... Args>
        concept all_same_as = (std::same_as<T, Args> && ...) && (sizeof...(Args) > 0);

/*
    template<typename T, typename ... U>
			requires (sizeof...(Args) > 0 && ...);
*/

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