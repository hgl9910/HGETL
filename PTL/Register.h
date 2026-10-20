#pragma once

#include <utility>

namespace hgptl::devices::detail{

enum class register_policy
{
    mW,     // Read-Modify-Write
    dW      // Direct Write
};

template<
    register_policy Policy,
    register_value ReadMask,
    register_value WriteMask
>
struct register_t
{
private:
    device_register reg;  // das device register


    // Zentrale Lesefunktion
    register_value read_impl(register_value mask) const
    {
        static_assert(ReadMask != 0, "Register not readable");
        return reg & mask & ReadMask;
    }

    // Zentrale Schreibfunktion
    void write_impl(register_value value, register_value mask)
    {
        static_assert(WriteMask != 0, "Register not writeable");

        mask &= WriteMask;
        value &= mask;

        if constexpr (Policy == register_policy::mW)
        {
            static_assert(ReadMask != 0,
                          "Read-Modify-Write requires readable register");

            reg = (reg & ~mask) | value;
        }
        else
        {
            // Direct write: kein Lesen des Registers.
            // Nur für Register geeignet, deren Hardwaresemantik
            // einen direkten maskierten Wert akzeptiert.
            reg = value;
        }
    }

public:
    // Raw register access
    register_value read() const
    {
        return read_impl(ReadMask);
    }

    void write(register_value value)
    {
        write_impl(value, WriteMask);
    }

    // Raw register access with mask
    register_value read(register_value mask) const
    {
        return read_impl(mask);
    }

    void write(register_value value, register_value mask)
    {
        write_impl(value, mask);
    }

    // Fixed-position field access
    template<register_field field>
    field::value_type get() const
    {
        static_assert(field::access::is_readable,
                      "Field not readable");
        static_assert((field::mask & ReadMask) == field::mask,
                      "Field exceeds register ReadMask");

        return static_cast<field::value_type>(
            (read_impl(field::mask) >> field::pos)
        );
    }

    template<register_field field>
    void set(field::value_type value)
    {
        static_assert(field::access::is_writeable,
                      "Field not writeable");
        static_assert((field::mask & WriteMask) == field::mask,
                      "Field exceeds register WriteMask");

        const auto val =
            static_cast<register_value>(std::to_underlying(value))
            << field::pos;

        write_impl(val, field::mask);
    }

    // Indexed field access
    template<register_field field>
    field::value_type get(unsigned idx) const
    {
        static_assert(field::access::is_readable,
                      "Field not readable");

        const auto pos = field::width * idx;
        const auto mask = field::mask << pos;

        static_assert((field::mask & ReadMask) == field::mask,
                      "Field exceeds register ReadMask");

        return static_cast<field::value_type>(
            (read_impl(mask) >> pos)
        );
    }

    template<register_field field>
    void set(field::value_type value, unsigned idx)
    {
        static_assert(field::access::is_writeable,
                      "Field not writeable");

        const auto pos = field::width * idx;
        const auto mask = field::mask << pos;
        const auto val =
            static_cast<register_value>(
                std::to_underlying(value)
            ) << pos;

        write_impl(val, mask);
    }

    // Variadic field-array write
    template<register_field field, typename... Args>
    void vset(field::value_type val, Args&&... args)
    {
        static_assert(field::access::is_writeable,
                      "Field not writeable");

        const auto v = std::to_underlying(val);

        const auto mask =
            varadic_or<register_value, field::width>(
                field::mask, std::forward<Args>(args)...
            );

        const auto value =
            varadic_or<register_value, field::width>(
                v, std::forward<Args>(args)...
            );

        write_impl(value, mask);
    }
};

}