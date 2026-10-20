#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>

#include "Access.h"
#include "Concepts.h"
#include "Fields.h"
#include "Gpiodef.h"
#include "Register.h"
#include "Types.h"
#include "Utils.h"



    struct gpio_regs {
       
         register_t<register_policy::mW, 0xFFFFFFFFu, 0xFFFFFFFFu> moder;    // 0x00
         register_t<register_policy::mW, 0xFFFFFFFFu, 0xFFFFFFFFu> otyper;   // 0x04
         register_t<register_policy::mW, 0xFFFFFFFFu, 0xFFFFFFFFu> ospeedr;  // 0x08
         register_t<register_policy::mW, 0xFFFFFFFFu, 0xFFFFFFFFu> pupdr;    // 0x0C
         register_t<register_policy::dW, 0xFFFFFFFFu, 0x00000000u> idr;      // 0x10   
         register_t<register_policy::mW, 0xFFFFFFFFu, 0xFFFFFFFFu> odr;      // 0x14
         register_t<register_policy::dW, 0x00000000u, 0xFFFFFFFFu> bsrr;     // 0x18
         register_t<register_policy::mW, 0xFFFFFFFFu, 0xFFFFFFFFu> lckr;     // 0x1C
         register_t<register_policy::mW, 0xFFFFFFFFu, 0xFFFFFFFFu> afr[2];   // 0x20/0x24

        using mode_field      = field_t<mode_t,  0,2,rw_policy>;
        using otype_field     = field_t<otype_t, 0,1,rw_policy>; 
        using ospeed_field    = field_t<ospeed_t,0,2,rw_policy>;
        using pupd_field      = field_t<pupd_t,  0,2,rw_policy>;
        using altf_field      = field_t<altf_t,  0,4,rw_policy>;
        using bsrr_field      = field_t<pin_value_t,  0,1,rw_policy>;
 
        using odr_field      = field_t<pin_value_t,  0,1,wo_policy>;
        using idr_field      = field_t<pin_value_t,  0,1,ro_policy>;
 
    };
 
    struct gpio_impl : gpio_regs{
 
    public:

      gpio_impl() = default;

      // no copy or move allowed  
      gpio_impl(gpio_impl const&) = delete;
      gpio_impl& operator=(gpio_impl const&) = delete;
      gpio_impl(gpio_impl&&) = delete;
      gpio_impl& operator=(gpio_impl&&) = delete; 

      // single pin get mode (result shifted to 0-position) 
      template<typename T = mode_field>
        T::value_type get_mode(pin_t pin){
           return moder.template get<T>(std::to_underlying(pin));
      }

        // single pin set mode
      template<typename T = mode_field>
      void set_mode(typename T::value_type mode, pin_t pin)
      {
         moder.template set<T>(mode, std::to_underlying(pin));
      }

      // varadic set mode
      template<typename T = mode_field, typename ... Args>
      void set_mode(typename T::value_type mode, Args&& ... args )
      requires all_same_as<pin_t, std::remove_cvref_t<Args>...> {
         moder.template vset<T>(mode, std::forward<Args>(args) ...);
        }


        // single pin get output type (result shifted to 0-position)
        template<typename T = otype_field>
        T::value_type get_otype(pin_t pin){
           return otyper.template get<T>(std::to_underlying(pin));
        }

        // single pin set output type
      template<typename T = otype_field>
      void set_otype(typename T::value_type otyp, pin_t pin)
      {
         otyper.template set<T>(otyp, std::to_underlying(pin));
        }

        // varadic set output type
      template<typename T = otype_field, typename ... Args>
      void set_otype(typename T::value_type otype, Args&& ... args )
      requires all_same_as<pin_t, std::remove_cvref_t<Args>...> {
         otyper.template vset<T>(otype, std::forward<Args>(args) ...);
        }


        // single pin get output speed (result shifted to 0-position)
        template<typename T = ospeed_field>
        T::value_type get_ospeed(pin_t pin){
           return ospeedr.template get<T>(std::to_underlying(pin));
        }

        // single pin set output speed
      template<typename T = ospeed_field>
      void set_ospeed(typename T::value_type ospeed, pin_t pin)
      {
         ospeedr.template set<T>(ospeed, std::to_underlying(pin));
        }

        // varadic set output speed
      template<typename T = ospeed_field, typename ... Args>
      void set_ospeed(typename T::value_type ospeed, Args&& ... args )
      requires all_same_as<pin_t, std::remove_cvref_t<Args>...> {
         ospeedr.template vset<T>(ospeed, std::forward<Args>(args) ...);
        }

        // single pin get pullup/pulldown (result shifted to 0-position)
        template<typename T = pupd_field>
        T::value_type get_pupd(pin_t pin){
           return pupdr.template get<T>(std::to_underlying(pin));
        }

        // single pin set pullup/pulldown
      template<typename T = pupd_field>
      void set_pupd(typename T::value_type pupd, pin_t pin)
      {
         pupdr.template set<T>(pupd, std::to_underlying(pin));
        }

      // variadic set pullup/pulldown
      template<typename T = pupd_field, typename ... Args>
      void set_pupd(typename T::value_type pupd, Args&& ... args )
      requires all_same_as<pin_t, std::remove_cvref_t<Args>...> {
         pupdr.template vset<T>(pupd, std::forward<Args>(args) ...);
        }

/*
      // single pin set pin value
      template<typename T = odr_field>
      void set_pin(typename T::value_type value, pin_t pin)
      {
         odr.template set<T>(value, std::to_underlying(pin));
      }
*/

      template<typename T = bsrr_field>
      void set_pin(typename T::value_type value, pin_t pin)
      {
         constexpr auto pin_count = 16u;
         const auto pos = std::to_underlying(pin);
         const auto bit = value == T::value_type::SET ? pos: pos + pin_count;

         bsrr.write(register_value{1} << bit);
      }

      // single pin get pin value
      template<typename T = idr_field>
      T::value_type get_pin(pin_t pin){
           return idr.template get<T>(std::to_underlying(pin));
      }

        // single pin get alternate function (result shifted to 0-position)
        template<typename T = altf_field>
        T::value_type get_altf(pin_t pin){
            auto p = std::to_underlying(pin);
            if( p < 8 )
               return afr[0].template get<T>(p);
            else
               return afr[1].template get<T>(p-8);
        }

        // single pin set alternate function
        template<typename T = altf_field>
        void set_altf(typename T::value_type altf, pin_t pin)
        {
            auto p = std::to_underlying(pin);
            if( p < 8 )
               return afr[0].template set<T>(altf, p);
            else
               return afr[1].template set<T>(altf, p-8);
        }

       
       
    protected:
    ~gpio_impl();
    

};