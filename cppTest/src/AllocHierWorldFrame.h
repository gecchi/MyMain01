#pragma once

#include "allochierarchybase.h"



// ワールド変換行列付きフレーム構造体
class D3DXFRAME_WORLD : public D3DXFRAME
{
public:
   D3DXMATRIX WorldTransMatrix;
};


// D3DXFRAME_WORLD取り扱いAllocateHierarchyクラス
class CAllocHierWorldFrame :
	public CAllocHierarchyBase
{
public:
	CAllocHierWorldFrame(void);
public:
	virtual ~CAllocHierWorldFrame(void);

protected:
	// フレーム構造体を生成する
	virtual D3DXFRAME* CreateNewFrame();
};
