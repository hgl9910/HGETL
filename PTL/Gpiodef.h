#pragma once

#include "Types.h"

namespace hgptl::gpio {


    enum class gpio_base_t : device_base{
        portA = CONST_GPIOA_BASE,
        portB = CONST_GPIOB_BASE,
        portC = CONST_GPIOC_BASE,
        portD = CONST_GPIOD_BASE,
        portE = CONST_GPIOE_BASE,
        portH = CONST_GPIOH_BASE,
    };  

     enum pin_t { P0 = 0, P1, P2, P3, P4, P5, P6, P7,
                       P8, P9, P10, P11, P12, P13, P14, P15 };
    // pin modes 2Bit
    enum mode_t { input = 0, output, alternate, analog };
 
    // output type 1Bit
    enum class otype_t { pushpull =  0, opendrain };
    
    // outputspeed 2 Bit 
    enum class ospeed_t { low = 0, medium, high, very_high}; 
    
    // pullup pulldown 1 Bit
    enum class pupd_t {	nopullup = 0, pullup, pulldown, /*reserved*/};
    
    // alternate function
    enum class altf_t { af_0, af_1, af_2, af_3, af_4, af_5, af_6, af_7, af_8,
			           af_9, af_10,	af_11, af_12, af_13, af_14, af_15};

                       
    enum class pin_value_t { RESET, SET };                   

}   