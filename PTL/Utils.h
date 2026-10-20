#pragma once

#include <limits>
#include <utility>

namespace hgptl {
    /*
    ----------------------------------- 
     utils 
    -------------------------------------
    */

    // generate position 0-based mask from Field-BitWidth 
    template<typename T>
    static unsigned constexpr generate_mask(T width) noexcept {
        return width == 0 ? 0u : generate_mask(width - 1) << 1 | 1;                        
    }

    // (shifted) mask
    template <typename T, const unsigned width, const unsigned pos =0>
    requires ( (width+pos) <= std::numeric_limits<T>::digits && width > 0 )
    struct make_mask {   
        static constexpr T value = generate_mask<T>(width) << pos ;
    };

    // create varadic bit mask  
    template< typename T = register_value,unsigned width, typename ...Args > 
    constexpr T varadic_or(unsigned mask, Args&&... args ) noexcept {
        return static_cast<T>( ((mask << width*std::to_underlying(args)) | ...) );
    }

}