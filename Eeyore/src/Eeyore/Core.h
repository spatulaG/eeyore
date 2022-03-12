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