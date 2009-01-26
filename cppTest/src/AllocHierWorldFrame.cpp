#include "AllocHierWorldFrame.h"

CAllocHierWorldFrame::CAllocHierWorldFrame(void)
{
}

CAllocHierWorldFrame::~CAllocHierWorldFrame(void)
{
}


// ワールド変換行列付きのフレーム構造体を生成
D3DXFRAME* CAllocHierWorldFrame::CreateNewFrame()
{
	D3DXFRAME* tmp = new D3DXFRAME_WORLD;
	ZeroMemory( tmp, sizeof(D3DXFRAME_WORLD) );
	AddDelList( tmp );
	return tmp;
}