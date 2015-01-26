//-----------------------------------------------------------
// 
// UDKinect.h
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

#ifndef __UDKINECT_H__
#define __UDKINECT_H__

#include "UDKinectNuiManager.h"

//-----------------------------------------------------------
// Init / ShutDown
//-----------------------------------------------------------

UDKINECT_C_API int		UDKinectInitialize( int userTrackingStyle, int skeletonSmoothing );
UDKINECT_C_API void		UDKinectShutDown();

//-----------------------------------------------------------
// Nui
//-----------------------------------------------------------

UDKINECT_C_API int		UDKinectIsSensorReady();

UDKINECT_C_API void		UDKinectSetCameraElevationAngle( int elevation );
UDKINECT_C_API int		UDKinectGetCameraElevationAngle();

UDKINECT_C_API void		UDKinectSetSkeletonSmoothing( int smoothingStyle );

UDKINECT_C_API int		UDKinectGetSkeletonTrackingState( int userIndex, int boneId );
UDKINECT_C_API int		UDKinectGetSkeletonPosition( int userIndex, int boneId, UDKinect::UDKVector* pBonePosition );
UDKINECT_C_API void		UDKinectGetSkeletonPositionTransformedToDepthImage( int userIndex, int boneId, UDKinect::UDKVector2D* pBonePosition );

// Returns the skeleton space coordinates of a given pixel in the depth image
UDKINECT_C_API void		UDKinectTransformDepthImageToSkeleton( UDKinect::UDKVector2D* pDepthCoord, UDKinect::UDKVector* pOutCoord, int depthValue );

// Returns the depth space coordinates of the specified point in skeleton space
UDKINECT_C_API void		UDKinectTransformSkeletonToDepthImage( UDKinect::UDKVector* pSkelLoc, UDKinect::UDKVector2D* pOutCoord );

//-----------------------------------------------------------
// User
//-----------------------------------------------------------

UDKINECT_C_API int		UDKinectIsUserReady( int userIndex );
UDKINECT_C_API int		UDKinectGetNbUserReady();

UDKINECT_C_API void		UDKinectSetUserTrackingStyle( int userTrackingStyle );

//-----------------------------------------------------------
// Preview window
//-----------------------------------------------------------

UDKINECT_C_API void		UDKinectShowPreviewWindow( int imageType );
UDKINECT_C_API void		UDKinectHidePreviewWindow( int imageType );

UDKINECT_C_API void		UDKinectShowPreviewWindows();
UDKINECT_C_API void		UDKinectHidePreviewWindows();

//-----------------------------------------------------------
// Test
//-----------------------------------------------------------

UDKINECT_C_API int		UDKinectGetImageStream( int imageType, struct UDKinect::tKinectFrame* pKinectFrame );

#endif __UDKINECT_H__