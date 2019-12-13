#ifndef GGAF_DX_WORLDMATSTACK_H_
#define GGAF_DX_WORLDMATSTACK_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <list>
#include <stack>
#include <vector>
#include <map>
#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 *
 */
class WorldMatStack : public GgafCore::Object {
public:
   D3DXMATRIX _actor_world_trans_matrix;
   std::stack<D3DXMATRIX*> m_MatrixStack;

   /** 前回ワールド変換の計算に使用されたフレームの変換行列の保存 */
   std::vector<D3DXMATRIX>  _prevTransformationMatrixList;

   std::map<FrameWorldMatrix*, std::vector<ID3DXAnimationSet*>>* _pModel_MapBornFrame_AnimationSetList;
   ID3DXAnimationSet* _pAs0;
   ID3DXAnimationSet* _pAs1;
public:
   WorldMatStack();
   virtual ~WorldMatStack();
   virtual void registerFrameTransformationMatrix(FrameWorldMatrix* pFrame);
   virtual void SetWorldMatrix( D3DXMATRIX* worldmat );
   virtual void UpdateFrame(FrameWorldMatrix* prm_frame_world, ID3DXAnimationSet* prm_pAs1 = nullptr, ID3DXAnimationSet* prm_pAs2= nullptr);

protected:
   void CalcFrameWorldMatrix(FrameWorldMatrix* frame_world);   // フレームワールド行列算出再帰関数
};

}

#endif /*GGAF_DX_WORLDMATSTACK_H_*/
