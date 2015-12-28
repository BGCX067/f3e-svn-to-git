#ifndef COMMON_H
#define COMMON_H

#ifndef NULL
#define NULL 0
#endif

#ifndef DLL
//	#define DLL
#endif

#ifndef DLL
	#ifndef EXPORTDLL 
		#define DLL __declspec(dllimport)
	#else 
		#define DLL __declspec(dllexport)
	#endif
#endif

#include <BaseTsd.h>
#include <windows.h>

#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

// Atomic Data Types
namespace f3
{
	//template<int J>
	//class FilteredTimer;
	class Timer;
	class Window;
	typedef INT32 I32 ;
	typedef UINT32 UI32 ;
	typedef float F32;
	typedef INT64 I64;
	typedef UINT64 UI64 ;
	typedef std::string string;
	typedef unsigned char byte;
	
	namespace util
	{
		class Log;

		extern Log log;
		extern DLL Timer timer;
	}

	namespace graphics
	{
		class DebugContext;

		extern DLL DebugContext debug;
		enum DeviceType { GL, DX10 };
	}

	namespace scene
	{
	}

	namespace platform
	{
		extern HWND hWnd;
		Window* createWindow();
	}

	namespace input
	{

	}
}

namespace f3u = f3::util;
namespace f3g = f3::graphics;
namespace f3i = f3::input;
namespace f3s = f3::scene;


#include <f3base/Log.h>
#endif

#pragma warning( disable : 4251 4273 4275 4251 )
