#ifndef GGAFDXWORLDMATSTACK_H_
#define GGAFDXWORLDMATSTACK_H_

namespace GgafDxCore {

class GgafDxWorldMatStack {
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

#endif /*GGAFDXWORLDMATSTACK_H_*/
