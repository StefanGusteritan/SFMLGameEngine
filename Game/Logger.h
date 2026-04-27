#pragma once
#include <iostream>

// --- MASTER COMPILE-TIME SWITCH ---
// Set to 0 to COMPLETELY remove all logging code from the binary (Zero overhead).
// Set to 1 to include logging code, which can then be toggled at runtime.
#define ENGINE_LOGGING_ENABLED 1

#if ENGINE_LOGGING_ENABLED
struct Logger
{
    static bool enabled;
};

#define LOG(x)           \
    if (Logger::enabled) \
    std::cout << x << std::endl
#define LOG_ERR(x)                                         \
    if (Logger::enabled)                                   \
    std::cerr << "\033[31m" << "ERROR: " << x << std::endl \
              << "\033[0m"
#else
#define LOG(x)
#define LOG_ERR(x)
#endif
