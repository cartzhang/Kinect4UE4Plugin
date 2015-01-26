//-----------------------------------------------------------
// 
// UDKinectImageStreamDepth.cpp
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

#ifndef __UDKINECT_IMAGE_STREAM_DEPTH_H__
#define __UDKINECT_IMAGE_STREAM_DEPTH_H__

#include "UDKinectImageStream.h"

namespace UDKinect
{
	class ImageStreamDepth: public ImageStream
	{
	public:
		ImageStreamDepth();
		virtual ~ImageStreamDepth();

	private:
		bool processImageFrame( const NUI_IMAGE_FRAME& imageFrame );

		RGBQUAD shortToQuadDepth( USHORT s );
	};
} // namespace UDKinect

#endif // __UDKINECT_IMAGE_STREAM_DEPTH_H__
