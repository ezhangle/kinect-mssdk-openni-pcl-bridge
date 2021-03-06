//@COPYRIGHT@//
//
// Copyright (c) 2012, Tomoto S. Washio
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Tomoto S. Washio nor the names of his
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TOMOTO S. WASHIO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//@COPYRIGHT@//

#pragma once;
#include "base.h"
#include "MSRKinectFrameReader.h"
#include "MSRKinectSkeletonContext.h"

class MSRKinectSkeletonReader :
	public MSRKinectFrameReader<MSRKinectSkeletonContext>
{
private:
	 typedef MSRKinectFrameReader<MSRKinectSkeletonContext> SuperClass;

public:
	MSRKinectSkeletonReader(MSRKinectRequirement* pRequirement, HANDLE hNextFrameEvent) : SuperClass(pRequirement, hNextFrameEvent, INFINITE)
	{
		m_pRequirement->AddCapabilityRequirement(XN_CAPABILITY_SKELETON);
	}

	virtual void Setup()
	{
		m_pRequirement->DoInitialize();
		CHECK_HRESULT(GetSensor()->NuiSkeletonTrackingEnable(m_hNextFrameEvent, NUI_SKELETON_TRACKING_FLAG_ENABLE_IN_NEAR_RANGE));
	}

	void SetSkeletonProfile(XnSkeletonProfile eProfile)
	{
		DWORD flags = NUI_SKELETON_TRACKING_FLAG_ENABLE_IN_NEAR_RANGE;
		if (eProfile == XN_SKEL_PROFILE_HEAD_HANDS || eProfile == XN_SKEL_PROFILE_UPPER) {
			flags |= NUI_SKELETON_TRACKING_FLAG_ENABLE_SEATED_SUPPORT;
		}
		CHECK_HRESULT(GetSensor()->NuiSkeletonTrackingEnable(m_hNextFrameEvent, flags));
	}
};
