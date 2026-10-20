# HGPTL — HG Type-Safe Peripheral Template Library

HGPTL is a C++ template library for type-safe access to memory-mapped microcontroller peripherals.

The project explores how modern C++ can be used to describe peripheral registers, register fields and peripheral configurations in a way that allows the compiler to detect invalid operations at compile time.

The initial development and testing target is the STM32F411.

**Status:** Experimental — hobby and learning project, not intended for production use.

## Design Goals

- **Type safety:** Use strong types and scoped enumerations instead of unrestricted integer values wherever appropriate.
- **Compile-time validation:** Detect invalid register fields, values and peripheral configurations as early as possible.
- **Memory-mapped layout:** Represent peripheral register layouts directly, with compile-time checks for register offsets and structure layout.
- **Minimal runtime overhead:** Use templates and compile-time information to avoid unnecessary runtime abstractions.
- **Controlled implementation details:** Keep low-level register representations and implementation mechanisms separate from the public API.
- **Readable interface:** Provide an API that is understandable to embedded developers familiar with C-style peripheral programming.
- **Hardware-specific definitions:** Keep peripheral addresses and register descriptions separate from generic access mechanisms.

## Architecture

HGPTL separates the description of peripheral hardware from the mechanisms used to access it.

### Register and field definitions

Registers are represented by typed abstractions that describe their access properties and supported operations.

Register fields define properties such as:

- Bit position and width
- Permitted access
- Supported values
- Bit masks

Strongly typed field values help prevent invalid combinations and accidental use of unrelated values.

Access policies distinguish read-only, write-only and read/write registers or fields where applicable.

### Peripheral implementations

Peripheral implementations describe the hardware register layout and provide the operations needed to use the peripheral.

The implementation must preserve the actual hardware layout. Compile-time checks are used to validate properties such as standard layout and register offsets.

Hardware-specific details should remain hidden behind the public peripheral interface wherever possible.

### Public API

The public API is intended to provide a straightforward interface for embedded applications while retaining the type safety of the underlying implementation.

For example, GPIO operations should allow pins and modes to be specified using dedicated types rather than arbitrary integers.

The goal is to make incorrect operations difficult to express and, where possible, impossible to compile.

## GPIO

GPIO is the initial peripheral used to develop and validate the design.

The implementation covers the STM32 GPIO register layout, typed register fields and basic pin operations.

The development tests include configuring pin modes and controlling output states. The implementation also accounts for the different semantics of the GPIO output data register (ODR) and the bit set/reset register (BSRR).

GPIO serves as the reference implementation for evaluating whether the same design can be applied to more complex peripherals.

Demo Application

The project currently includes a simple demo application for the STM32F411 Black Pill board.

The application demonstrates basic GPIO functionality: each time the user presses the user button, the onboard LED lights up.

The demo serves as a practical test of the GPIO implementation and the underlying type-safe register access mechanisms.

## Timer Support

Timers are the next major step in validating the architecture.

Timer peripherals have more complex register layouts and configurations than GPIO. They also contain features that differ between timer instances, such as input capture, output compare, PWM generation and advanced timer control.

The design must accommodate these differences without weakening type safety or requiring invalid registers and fields to be exposed through the public API.

Timer support is under development.

## Hardware Description and Code Generation

A longer-term goal is to generate hardware-specific definitions from CMSIS-SVD descriptions.

The intended workflow is:

1. Read the device description.
2. Build an internal hardware model.
3. Generate C++ definitions for peripheral addresses, registers, fields and supported values.
4. Use the generated definitions together with the generic HGPTL implementation in the embedded application.

The SVD processing and code-generation tools are intended to run on the development computer, not on the microcontroller.

This approach should reduce repetitive hardware-description code and make it easier to support additional devices.

## Development Environment

The initial development environment uses:

- **Language:** C++23
- **Target:** STM32F411
- **Compiler:** ARM GNU Toolchain (`arm-none-eabi-g++`)
- **IDE:** Visual Studio Code
- **Build system:** GNU Make

Compiler optimization and compile-time validation are important parts of the development process.

## Project Status

HGPTL is an experimental project. The design is being developed incrementally, using real peripheral implementations to test the underlying abstractions.

Current focus:

- Typed register and field abstractions
- GPIO implementation and testing
- Compile-time validation of register layouts and field definitions
- Evaluation of the design for timer peripherals

Future work includes broader timer support, additional peripherals and automated generation of device-specific definitions from SVD files.

## License

License information has not yet been specified.
