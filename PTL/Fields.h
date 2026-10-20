#pragma once

#include <limits>

#include "Access.h"
#include "Concepts.h"
#include "Types.h"
#include "Utils.h"

    /*
    ----------------------------------- 
    field type
    -------------------------------------
    */
    template<   typename T,     // value type
                unsigned p,     // field posiion 
                unsigned w,     // field width
                access_policy a // field access
            >
    requires ( (w+p) <= std::numeric_limits<register_value>::digits && (w > 0) )    
    struct field_t {
        using value_type = T;
        using access = a;

        static constexpr unsigned pos = p;
        static constexpr unsigned width = w;
        static constexpr unsigned mask = make_mask<register_value,width,pos>::value;
    };
