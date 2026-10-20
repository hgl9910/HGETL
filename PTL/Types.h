#pragma once

#include <cstdint>


namespace hgptl {
   /* used types */
using device_base       = std::uintptr_t; 
using device_register   = volatile std::uint32_t;

using register_value    = std::uint32_t;
constexpr register_value register_value_MAX = UINT32_MAX;

// gpio address 
constexpr device_base   CONST_PERIPH_BASE       = 0x40000000UL; 
constexpr device_base   CONST_AHB1PERIPH_BASE   = CONST_PERIPH_BASE + 0x00020000UL;

constexpr device_base   CONST_GPIOA_BASE        = CONST_AHB1PERIPH_BASE + 0x0000UL;
constexpr device_base   CONST_GPIOB_BASE        = CONST_AHB1PERIPH_BASE + 0x0400UL;
constexpr device_base   CONST_GPIOC_BASE        = CONST_AHB1PERIPH_BASE + 0x0800UL;
constexpr device_base   CONST_GPIOD_BASE        = CONST_AHB1PERIPH_BASE + 0x0C00UL;
constexpr device_base   CONST_GPIOE_BASE        = CONST_AHB1PERIPH_BASE + 0x1000UL;
constexpr device_base   CONST_GPIOH_BASE        = CONST_AHB1PERIPH_BASE + 0x1C00UL;    
 
}

