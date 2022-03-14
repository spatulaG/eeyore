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

#ifdef ER_ENABLE_ASSERTS
	#define ER_ASSERT(x,...){if(!(x)){ER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}// set breakpoint
	#define ER_CORE_ASSERT(x,...){if(!(x)){ER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }} // get stripped in released build, check state build status
#else
	#define ER_ASSERT(x,...)
	#define ER_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)//shift 1 to left for x bit, see: bit field