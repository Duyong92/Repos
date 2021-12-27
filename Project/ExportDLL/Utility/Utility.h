#pragma once

#ifdef UTILITY_EXPORTS
#define UTILITY_API __declspec(dllexport)
#else
#define UTILITY_API __declspec(dllimport)
#endif

extern "C" UTILITY_API void errorPrint()