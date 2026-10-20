#pragma once

#include <new>

#include "GpioImpl.h"

// gpio instances
template<gpio_base_t base>
struct gpio_t : gpio_impl {

    static constexpr device_base address = static_cast<device_base>(base);

inline  void *operator new(std::size_t){
    return reinterpret_cast< void *>(address);
}



private:
    ~gpio_t() {}
    // copy operator ?
};

// port instances
using gpioa_t = gpio_t<gpio_base_t::portA>;
using gpiob_t = gpio_t<gpio_base_t::portB>;
using gpioc_t = gpio_t<gpio_base_t::portC>;
using gpiod_t = gpio_t<gpio_base_t::portD>;
using gpioe_t = gpio_t<gpio_base_t::portE>;
using gpioh_t = gpio_t<gpio_base_t::portH>;

// gpio concepts 
template <typename T>
    concept gpio_device_t = std::derived_from<T, gpio_impl>;

// layout sanity check 
template<typename T>
    requires( gpio_device_t<T>)
    consteval void check_gpio_layout() {
    static_assert(
    std::is_standard_layout<T>::value
    && sizeof(T) == 40 
    && offsetof(T,moder)  == 0x00
    && offsetof(T,otyper) == 0x04
    && offsetof(T,ospeedr)== 0x08
    && offsetof(T,pupdr)  == 0x0C      
    && offsetof(T,idr)    == 0x10      
    && offsetof(T,odr)    == 0x14      
    && offsetof(T,bsrr)   == 0x18      
    && offsetof(T,lckr)   == 0x1C      
    && offsetof(T,afr[0]) == 0x20       
    && offsetof(T,afr[1]) == 0x24
    ,
    "gpio class layout check failed");
};

template<typename T>
  concept gpio_device = std::derived_from<T,gpio_impl>; 

template <typename T>
    concept is_gpio_A = std::is_same_v<T, gpioa_t>;

    template <typename T>
    concept is_gpio_B = std::is_same_v<T, gpiob_t>;

    template <typename T>
    concept is_gpio_C = std::is_same_v<T, gpioc_t>;

    template <typename T>
    concept is_gpio_D = std::is_same_v<T, gpiod_t>;

    template <typename T>
    concept is_gpio_E = std::is_same_v<T, gpioe_t>;

    template <typename T>
    concept is_gpio_H = std::is_same_v<T, gpioh_t>;

// compile time port tests 
template void check_gpio_layout<gpioa_t>();
template void check_gpio_layout<gpiob_t>();
template void check_gpio_layout<gpioc_t>();
template void check_gpio_layout<gpiod_t>();
template void check_gpio_layout<gpioe_t>();
template void check_gpio_layout<gpioh_t>();


inline gpioa_t& PortA = *reinterpret_cast<gpioa_t*>(gpioa_t::address);
inline gpiob_t& PortB = *reinterpret_cast<gpiob_t*>(gpiob_t::address);
inline gpioc_t& PortC = *reinterpret_cast<gpioc_t*>(gpioc_t::address);
inline gpiod_t& PortD = *reinterpret_cast<gpiod_t*>(gpiod_t::address);
inline gpioe_t& PortE = *reinterpret_cast<gpioe_t*>(gpioe_t::address);
inline gpioh_t& PortH = *reinterpret_cast<gpioh_t*>(gpioh_t::address);

// high level 

namespace hgl::gpio { 
    template<gpio_device_t port,pin_t pin> 
    struct gpiopin_t {
    
    };
} 