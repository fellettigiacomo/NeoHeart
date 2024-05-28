//
// Created by depau on 28/05/24.
//

#ifndef NEOPISELL_ATTINYPORTS_H
#define NEOPISELL_ATTINYPORTS_H

/// Force the compiler to assume the value is a compile-time constant
#define CONSTEXPR(_x) __builtin_constant_p(_x) ? (_x) : (_x)

namespace ports {
    static constexpr uintptr_t PortA =  0x0400; /* I/O Ports */
    static constexpr uintptr_t PortB =  0x0420; /* I/O Ports */
    static constexpr uintptr_t PortC =  0x0440; /* I/O Ports */

    static constexpr uintptr_t VPortA =  0x0000; /* Virtual Ports */
    static constexpr uintptr_t VPortB =  0x0004; /* Virtual Ports */
    static constexpr uintptr_t VPortC =  0x0008; /* Virtual Ports */
}

template<uint8_t Pin>
struct PinInfo {
    static constexpr uint8_t pin = Pin;
    static constexpr uint8_t portPin = -1;
    static constexpr uintptr_t portAddr = -1;
    static constexpr uintptr_t vportAddr = -1;
    static constexpr uint8_t pinMask = -1;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA0> {
    static constexpr uint8_t portPin = 0;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA1> {
    static constexpr uint8_t portPin = 1;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA2> {
    static constexpr uint8_t portPin = 2;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA3> {
    static constexpr uint8_t portPin = 3;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA4> {
    static constexpr uint8_t portPin = 4;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA5> {
    static constexpr uint8_t portPin = 5;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA6> {
    static constexpr uint8_t portPin = 6;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PA7> {
    static constexpr uint8_t portPin = 7;
    static constexpr uintptr_t portAddr = ports::PortA;
    static constexpr uintptr_t vportAddr = ports::VPortA;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PB0> {
    static constexpr uint8_t portPin = 0;
    static constexpr uintptr_t portAddr = ports::PortB;
    static constexpr uintptr_t vportAddr = ports::VPortB;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PB1> {
    static constexpr uint8_t portPin = 1;
    static constexpr uintptr_t portAddr = ports::PortB;
    static constexpr uintptr_t vportAddr = ports::VPortB;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PB2> {
    static constexpr uint8_t portPin = 2;
    static constexpr uintptr_t portAddr = ports::PortB;
    static constexpr uintptr_t vportAddr = ports::VPortB;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PB3> {
    static constexpr uint8_t portPin = 3;
    static constexpr uintptr_t portAddr = ports::PortB;
    static constexpr uintptr_t vportAddr = ports::VPortB;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PB4> {
    static constexpr uint8_t portPin = 4;
    static constexpr uintptr_t portAddr = ports::PortB;
    static constexpr uintptr_t vportAddr = ports::VPortB;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PB5> {
    static constexpr uint8_t portPin = 5;
    static constexpr uintptr_t portAddr = ports::PortB;
    static constexpr uintptr_t vportAddr = ports::VPortB;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PC0> {
    static constexpr uint8_t portPin = 0;
    static constexpr uintptr_t portAddr = ports::PortC;
    static constexpr uintptr_t vportAddr = ports::VPortC;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PC1> {
    static constexpr uint8_t portPin = 1;
    static constexpr uintptr_t portAddr = ports::PortC;
    static constexpr uintptr_t vportAddr = ports::VPortC;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PC2> {
    static constexpr uint8_t portPin = 2;
    static constexpr uintptr_t portAddr = ports::PortC;
    static constexpr uintptr_t vportAddr = ports::VPortC;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

template<>
struct PinInfo<PIN_PC3> {
    static constexpr uint8_t portPin = 3;
    static constexpr uintptr_t portAddr = ports::PortC;
    static constexpr uintptr_t vportAddr = ports::VPortC;
    static constexpr uint8_t pinMask = 1 << portPin;

    static volatile PORT_t *port() { return reinterpret_cast<PORT_t *>(portAddr); }
    static volatile VPORT_t *vport() { return reinterpret_cast<VPORT_t *>(vportAddr); }
};

#endif //NEOPISELL_ATTINYPORTS_H
