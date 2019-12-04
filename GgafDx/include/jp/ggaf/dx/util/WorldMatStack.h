#ifndef GGAF_DX_WORLDMATSTACK_H_
#define GGAF_DX_WORLDMATSTACK_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <list>
#include <stack>
#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {
class FrameWorldMatrix;

class WorldMatStack : public GgafCore::Object {
protected:
   D3DXMATRIX m_WorldTransMatrix;
   std::stack<D3DXMATRIX*> m_MatrixStack;
   std::list<FrameWorldMatrix*> m_DrawFrameList;

public:
   WorldMatStack();
   virtual ~WorldMatStack();
   virtual void SetWorldMatrix( D3DXMATRIX* worldmat );
   virtual void UpdateFrame( FrameWorldMatrix* frame_world );
   std::list< FrameWorldMatrix*>  *GetDrawList();

protected:
   void CalcFrameWorldMatrix( FrameWorldMatrix* frame_world );   // フレームワールド行列算出再帰関数
};

}

#endif /*GGAF_DX_WORLDMATSTACK_H_*/
