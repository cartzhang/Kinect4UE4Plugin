//-----------------------------------------------------------
// 
// UDKinectNuiManager.h
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

#ifndef __UDKINECT_NUI_MANAGER_H__
#define __UDKINECT_NUI_MANAGER_H__

#include "UDKInectFundamental.h"
#include "UDKinectUser.h"
#include "UDKinectPreviewWindow.h"
#include "UDKinectImageStream.h"

namespace UDKinect
{
	#define UDKINECT_MAX_USER 2

	enum eUserTrackingStyle
	{
		eUserTrackingStyle_QUEUE,
		eUserTrackingStyle_MEMORY
	};

	enum eSkeletonSmoothing
	{
		eSkeletonSmoothing_NONE,
		eSkeletonSmoothing_FAST_LOW_LATENCY,
		eSkeletonSmoothing_SMOOTH_HIGH_LATENCY
	};

	enum eImageType
	{
		eImageType_COLOR,
		eImageType_DEPTH,
		eImageType_COUNT
	};

	class NuiManager
	{
	public:
		//-----------------------------------------------------------
		// Init / ShutDown
		//-----------------------------------------------------------

		NuiManager();
		~NuiManager();

		bool initialize( eUserTrackingStyle userTrackingStyle, eSkeletonSmoothing skelSmoothing );
		bool initialize( OLECHAR* pInstanceName, eUserTrackingStyle userTrackingStyle, eSkeletonSmoothing skelSmoothing );
		void shutdown();

		bool isReady() const { return m_bIsReady; }

		//-----------------------------------------------------------
		// Nui
		//-----------------------------------------------------------

		INuiSensor*		getNuiInstance() const { return m_pNuiSensor; }

		void			setCameraElevationAngle( int elevation );
		int				getCameraElevationAngle() const;

		bool			hasSkeletalEngine() const { return HasSkeletalEngine( m_pNuiSensor ); }

		void			setSkeletonSmoothing( eSkeletonSmoothing skelSmoothing ) { m_SkeletonSmoothing = skelSmoothing; }

		ImageStream*	getImageStream( eImageType type ) const { return m_ImageStream[type]; }

		static void CALLBACK staticStatusProc( HRESULT hrStatus, const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName, void* pUserData );

		//-----------------------------------------------------------
		// User
		//-----------------------------------------------------------

		bool				isUserReady( int user=0 ) const;
		User&				getUser( int user );
		int					getNbUserReady() const;
		
		void				setUserTrackingStyle( eUserTrackingStyle userTrackingStyle ) { m_UserTrackingStyle = userTrackingStyle; }
		eUserTrackingStyle	getUserTrackingStyle() const { m_UserTrackingStyle; }

		//-----------------------------------------------------------
		// Preview window
		//-----------------------------------------------------------

		void showPreviewWindow( eImageType imageType, bool bVisible );
		void showPreviewWindows( bool bVisible );

		//-----------------------------------------------------------

	private:
		bool m_bIsReady;

		//-----------------------------------------------------------
		// Nui
		//-----------------------------------------------------------

		INuiSensor*			m_pNuiSensor;
		BSTR				m_instanceId;

		HANDLE				m_hThNuiProcess;
		HANDLE				m_hEvNuiProcessStop;

		HANDLE				m_hNextSkeletonEvent;
		eSkeletonSmoothing	m_SkeletonSmoothing;
		NUI_SKELETON_FRAME	m_SkeletonFrame;

		ImageStream*		m_ImageStream[eImageType_COUNT];

		static DWORD WINAPI     staticProcessThread(LPVOID pParam);
		DWORD WINAPI            processThread();

		void CALLBACK           statusProc( HRESULT hrStatus, const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName );

		void					gotDepthAlert();
		void					gotColorAlert();
		void					gotSkeletonAlert();

		//-----------------------------------------------------------
		// User
		//-----------------------------------------------------------

		User				m_Users[UDKINECT_MAX_USER];
		eUserTrackingStyle	m_UserTrackingStyle;

		//-----------------------------------------------------------
	};

	extern NuiManager g_NuiManager;
} // namespace UDKinect

#endif // __UDKINECT_NUI_MANAGER_H__

