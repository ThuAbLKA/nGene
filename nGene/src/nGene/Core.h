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