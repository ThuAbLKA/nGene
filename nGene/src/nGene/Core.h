#pragma once

// dll build macro
#ifdef NGN_PLATFORM_WINDOWS
	#ifdef NGN_BUILD_DLL
		#define NGN_API __declspec(dllexport)
	#else
		#define NGN_API __declspec(dllimport)
	#endif
#else
	#error nGene only supports windows
#endif

#ifdef NGN_ENABLE_ASSERTS
    #define NGN_CORE_ASSERT(x, ...) { if(!(x)) { NGN_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); DebugBreak(); } }
#else
	#define NGN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)