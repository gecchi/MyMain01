#pragma once

#include "allochierarchybase.h"



// ���[���h�ϊ��s��t���t���[���\����
class D3DXFRAME_WORLD : public D3DXFRAME
{
public:
   D3DXMATRIX WorldTransMatrix;
};


// D3DXFRAME_WORLD��舵��AllocateHierarchy�N���X
class CAllocHierWorldFrame :
	public CAllocHierarchyBase
{
public:
	CAllocHierWorldFrame(void);
public:
	virtual ~CAllocHierWorldFrame(void);

protected:
	// �t���[���\���̂𐶐�����
	virtual D3DXFRAME* CreateNewFrame();
};
