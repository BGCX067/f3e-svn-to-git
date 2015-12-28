#ifndef COMMON_H
#define COMMON_H

#ifndef NULL
#define NULL 0
#endif

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include "Log.h"

#endif