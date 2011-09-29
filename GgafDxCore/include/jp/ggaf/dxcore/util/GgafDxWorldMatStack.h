#ifndef GGAFDXWORLDMATSTACK_H_
#define GGAFDXWORLDMATSTACK_H_

namespace GgafDxCore {

class GgafDxWorldMatStack
{
protected:
   D3DXMATRIX m_WorldTransMatrix;
   stack<D3DXMATRIX*> m_MatrixStack;
   list<D3DXFRAME_WORLD*> m_DrawFrameList;

public:
   GgafDxWorldMatStack(void);
   ~GgafDxWorldMatStack(void);
   virtual void SetWorldMatrix( D3DXMATRIX* worldmat );
   virtual void UpdateFrame( D3DXFRAME_WORLD* frame );
   list< D3DXFRAME_WORLD*>  *GetDrawList();

protected:
   void CalcFrameWorldMatrix( D3DXFRAME_WORLD* frame );   // フレームワールド行列算出再帰関数
};

}

#endif /*GGAFDXWORLDMATSTACK_H_*/
