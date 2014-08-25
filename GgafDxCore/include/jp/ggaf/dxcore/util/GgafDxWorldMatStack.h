#ifndef GGAFDXCORE_GGAFDXWORLDMATSTACK_H_
#define GGAFDXCORE_GGAFDXWORLDMATSTACK_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <list>
#include <stack>
#include <d3dx9.h>

namespace GgafDxCore {
class D3DXFRAME_WORLD;

class GgafDxWorldMatStack : public GgafCore::GgafObject {
protected:
   D3DXMATRIX m_WorldTransMatrix;
   std::stack<D3DXMATRIX*> m_MatrixStack;
   std::list<D3DXFRAME_WORLD*> m_DrawFrameList;

public:
   GgafDxWorldMatStack();
   virtual ~GgafDxWorldMatStack();
   virtual void SetWorldMatrix( D3DXMATRIX* worldmat );
   virtual void UpdateFrame( D3DXFRAME_WORLD* frame_world );
   std::list< D3DXFRAME_WORLD*>  *GetDrawList();

protected:
   void CalcFrameWorldMatrix( D3DXFRAME_WORLD* frame_world );   // フレームワールド行列算出再帰関数
};

}

#endif /*GGAFDXCORE_GGAFDXWORLDMATSTACK_H_*/
