#ifndef GGAFDX9WORLDMATSTACK_H_
#define GGAFDX9WORLDMATSTACK_H_

namespace GgafDx9Core {

class GgafDx9WorldBoundMatStack
{
protected:
   D3DXMATRIX m_WorldTransMatrix;
   stack<D3DXMATRIX*> m_MatrixStack;
   list<D3DXFRAME_WORLD*> m_DrawFrameList;

public:
   GgafDx9WorldBoundMatStack(void);
   ~GgafDx9WorldBoundMatStack(void);
   virtual void SetWorldMatrix( D3DXMATRIX* worldmat );
   virtual void UpdateFrame( D3DXFRAME_WORLD* frame );
   list< D3DXFRAME_WORLD*>  *GetDrawList();

protected:
   void CalcFrameWorldMatrix( D3DXFRAME_WORLD* frame );   // �t���[�����[���h�s��Z�o�ċA�֐�
};

}

#endif /*GGAFDX9WORLDMATSTACK_H_*/
