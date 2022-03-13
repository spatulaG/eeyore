#pragma once

#ifdef ER_PLATFORM_WINDOWS
	#ifdef ER_BUILD_DLL
		#define EEYORE_API __declspec(dllexport)
	#else
		#define EEYORE_API __declspec(dllimport)
	#endif
#else
	#error Eeyore only supports Windows!
#endif

#define BIT(x) (1 << x)//shift 1 to left for x bit, see: bit field