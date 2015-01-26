//-----------------------------------------------------------
// 
// UDKinectFundamental.h
//
// Copyright (c) 2012 UDKinect, Charlie Hodara
//
// This file is released under the MIT License.
//
// Permission is hereby granted, free of charge, to any person obtaining 
// a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions: 
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR 
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
//
//-----------------------------------------------------------

#ifndef __UDKINECT_FUNDAMENTAL_H__
#define __UDKINECT_FUNDAMENTAL_H__

#define UDKINECT_DEBUG

//-----------------------------------------------------------
// API Export/Import Macros
//-----------------------------------------------------------

#define UDKINECT_API_EXPORT __declspec(dllexport)
#define UDKINECT_API_IMPORT __declspec(dllimport)
#define UDKINECT_EXPORT

#ifdef __cplusplus
	#define UDKINECT_C_API_EXPORT extern "C" UDKINECT_API_EXPORT
	#define UDKINECT_C_API_IMPORT extern "C" UDKINECT_API_IMPORT
	#define UDKINECT_CPP_API_EXPORT UDKINECT_API_EXPORT
	#define UDKINECT_CPP_API_IMPORT UDKINECT_API_IMPORT
#else
	#define UDKINECT_C_API_EXPORT UDKINECT_API_EXPORT
	#define UDKINECT_C_API_IMPORT UDKINECT_API_IMPORT
#endif

#ifdef UDKINECT_EXPORT
	#define UDKINECT_C_API UDKINECT_C_API_EXPORT
	#define UDKINECT_CPP_API UDKINECT_CPP_API_EXPORT
#else
	#define UDKINECT_C_API UDKINECT_C_API_IMPORT
	#define UDKINECT_CPP_API UDKINECT_CPP_API_IMPORT
#endif

//-----------------------------------------------------------
// DEBUG/LOG MACRO
//-----------------------------------------------------------

namespace UDKinectUtil
{
	void debug_write_log(const char* logName, const char* txt);
	void debug_print_message(const char* format, ...);
	void debug_print_assert(const char* filename, int line, const char* expression);
	void debug_reset_log();
	void error_exit(LPTSTR lpszFunction);
} // namespace UDKinectUtil

#ifdef UDKINECT_DEBUG
    #define UDKINECT_ASSERT(bValue)\
        if( !(bValue) )\
        {\
            UDKinectUtil::debug_print_assert(__FILE__, __LINE__, #bValue);\
            assert(bValue);\
        }
	#define UDKINECT_ASSERT_MSG(bValue, x, ...)\
        if( !(bValue) )\
        {\
            UDKinectUtil::debug_print_assert(__FILE__, __LINE__, #bValue);\
            UDKinectUtil::debug_print_message(x, ## __VA_ARGS__);\
            assert(bValue);\
        }
	#define UDKINECT_DEBUG_MSG(x, ...)  UDKinectUtil::debug_print_message(x, ## __VA_ARGS__ );
	#define UDKINECT_RESET_LOG()		UDKinectUtil::debug_reset_log();
#else
	#define UDKINECT_ASSERT(bValue)
	#define UDKINECT_ASSERT_MSG(bValue, x, ...)
	#define UDKINECT_DEBUG_MSG(x,...)
	#define UDKINECT_RESET_LOG()
#endif

//-----------------------------------------------------------
// UDK types
//-----------------------------------------------------------
//@zpj
#include "stdafx.h"

namespace UDKinect
{
	struct UDKVector
	{
		float x, y, z;
	};

	struct UDKVector2D
	{
		float x, y;
	};

	template<typename DataType>
	struct UDKArray
	{
		DataType* Data;

		inline int Num()
		{
			return ArrayNum;
		}

		inline void Reallocate(int NewNum, bool bCompact=false)
		{
			ArrayNum = NewNum;
			if( ArrayNum > ArrayMax || bCompact )
			{
				ArrayMax = ArrayNum;
				Data = (DataType*)(*ReallocFunctionPtr)( Data, ArrayMax * sizeof(DataType), 8);
			}
		}
	private:
		int ArrayNum;
		int ArrayMax;
	};

	struct tKinectFrame
	{
		UDKArray<RGBQUAD> buffer;
	};

	extern "C"
	{
		typedef void* (*ReallocFunctionPtrType)(void* Original, DWORD Count, DWORD Alignment);

		extern ReallocFunctionPtrType ReallocFunctionPtr;

		struct FDLLBindInitData
		{
			INT Version;
			ReallocFunctionPtrType ReallocFunctionPtr;
		};

		UDKINECT_C_API void DLLBindInit( FDLLBindInitData* InitData );
	}
} // namespace UDKinect

#endif // __UDKINECT_FUNDAMENTAL_H__