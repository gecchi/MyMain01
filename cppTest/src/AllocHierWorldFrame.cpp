#include "AllocHierWorldFrame.h"

CAllocHierWorldFrame::CAllocHierWorldFrame(void)
{
}

CAllocHierWorldFrame::~CAllocHierWorldFrame(void)
{
}


// ���[���h�ϊ��s��t���̃t���[���\���̂𐶐�
D3DXFRAME* CAllocHierWorldFrame::CreateNewFrame()
{
	D3DXFRAME* tmp = new D3DXFRAME_WORLD;
	ZeroMemory( tmp, sizeof(D3DXFRAME_WORLD) );
	AddDelList( tmp );
	return tmp;
}