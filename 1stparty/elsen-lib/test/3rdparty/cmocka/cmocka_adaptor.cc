#if defined(__xtensa__)
#include <setjmp.h>

// The ESP32 toolchain contains a definition for this function but no implementation. This tricks
// cmock and a linker error is generated, so just define it here.
using SigCallback = void (*)(int);
extern "C" SigCallback signal(int, SigCallback)
{
    return nullptr;
}

// set/longjmp are not implemented for ESP32
extern "C" void __wrap_longjmp(jmp_buf, int)
{}
#endif
