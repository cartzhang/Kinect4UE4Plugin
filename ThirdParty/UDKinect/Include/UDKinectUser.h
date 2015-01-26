//-----------------------------------------------------------
// 
// UDKinectUser.h
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

#ifndef __UDKINECT_USER_H__
#define __UDKINECT_USER_H__

#include "UDKInectFundamental.h"

namespace UDKinect
{
	class User
	{
	public:
		User();
		~User();

		void									reset();

		bool									isReady() const;

		void									setSkeleton( NUI_SKELETON_DATA* pSkelData );
		
		NUI_SKELETON_DATA*						getSkeleton() const { return m_pSkeletonData; }

		NUI_SKELETON_TRACKING_STATE				getSkeletonTrackingState() const;

		const Vector4&							getBoneLocation( NUI_SKELETON_POSITION_INDEX boneId ) const;
		NUI_SKELETON_POSITION_TRACKING_STATE	getBoneTrackingState( NUI_SKELETON_POSITION_INDEX boneId ) const;

	private:
		NUI_SKELETON_DATA* m_pSkeletonData;
	};
} // namespace UDKinect

#endif // __UDKINECT_USER_H__
