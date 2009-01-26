#pragma once

#include <d3dx9.h>
#include <stack>
#include <list>
#include "AllocHierWorldFrame.h"

using namespace std;


class CWorldTransMatStack
{
protected:
   D3DXMATRIX m_WorldTransMatrix;
   stack< D3DXMATRIX* > m_MatrixStack;
   list< D3DXFRAME_WORLD*> m_DrawFrameList;

public:
   CWorldTransMatStack(void);
   ~CWorldTransMatStack(void);
   virtual void SetWorldMatrix( D3DXMATRIX* worldmat );
   virtual void UpdateFrame( D3DXFRAME_WORLD* frame );
   list< D3DXFRAME_WORLD*>  *GetDrawList();

protected:
   void CalcFrameWorldMatrix( D3DXFRAME_WORLD* frame );   // フレームワールド行列算出再帰関数
};
