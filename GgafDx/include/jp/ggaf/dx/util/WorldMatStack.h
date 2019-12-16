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
   bool** _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act;
   int _as0_index;
   int _as1_index;
public:
   WorldMatStack();
   virtual ~WorldMatStack();
   virtual void registerFrameTransformationMatrix(FrameWorldMatrix* pFrame);
   virtual void SetWorldMatrix( D3DXMATRIX* worldmat );
   virtual void UpdateFrame(FrameWorldMatrix* prm_frame_world, int prm_as0_index = -1, int prm_as1_index = -1);

protected:
   void CalcFrameWorldMatrix(FrameWorldMatrix* frame_world);   // フレームワールド行列算出再帰関数
};

}

#endif /*GGAF_DX_WORLDMATSTACK_H_*/
