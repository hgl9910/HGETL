/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ******************************************************************************
*/

#include "main.h"
#include "Types.h"
// #include "Utils.h"
//#include "Gpiodef.h"
//#include "GpioImpl.h"
#include "Gpio.h"
//#include "Access.h"
//#include "Fields.h"
//#include "Concepts.h"
//#include "Register.h"
//#include "GpioImpl.h"



/**
  * @brief  The application entry point.
  * @retval int
  */
extern "C" int main(void)
{

      // RCC_AHB1ENR: GPIOA (Bit 0) und GPIOC (Bit 2) aktivieren
    auto* const rcc_ahb1enr =
        reinterpret_cast<volatile std::uint32_t*>(0x40023830UL);

    *rcc_ahb1enr |= (1u << 0) | (1u << 2);

    // PA0: Eingang
    PortA.set_mode(mode_t::input, pin_t::P0);
    PortA.set_pupd(pupd_t::pullup, pin_t::P0);

    // PC13: Ausgang
    PortC.set_mode(mode_t::output, pin_t::P13);



while (1)
{
    PortC.set_pin(
        PortA.get_pin(pin_t::P0),
        pin_t::P13
    );
}

  
}

