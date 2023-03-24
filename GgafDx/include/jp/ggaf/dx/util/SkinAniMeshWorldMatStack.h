#ifndef GGAF_DX_SKINANIMESHWORLDMATSTACK_H_
#define GGAF_DX_SKINANIMESHWORLDMATSTACK_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
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
class SkinAniMeshWorldMatStack : public GgafCore::Object {
public:
    D3DXMATRIX _actor_world_trans_matrix;
    std::stack<D3DXMATRIX*> _stack_matrix;
    std::list<SkinAniMeshFrame*> m_DrawFrameList; //D3DXAniMeshActor維持用、削除予定

    /** 前回ワールド変換の計算に使用されたフレームの変換行列の保存 */
    std::vector<D3DXMATRIX> _prevTransformationMatrixList;
    /** [アニメーションセットインデックス][フレームインデックス] ＝ アニメーション対象かどうか の情報配列 */
    bool** _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act;
    int _as0_index;
    int _as1_index;
public:
    SkinAniMeshWorldMatStack();
    virtual ~SkinAniMeshWorldMatStack();
    virtual void registerFrameTransformationMatrix(SkinAniMeshFrame* pFrame);
    virtual void SetWorldMatrix( D3DXMATRIX* worldmat );

    /**
     * アクターのワールド変換を行う .
     * @param prm_frame_root アニメーションボーンフレームのルート
     * @param prm_as0_index トラック0に設定されているアニメーションセットインデックス
     * @param prm_as1_index トラック1に設定されているアニメーションセットインデックス
     * @param prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act
     */
    virtual void UpdateFrame(D3DXMATRIX* prm_pMatBaseTransformMatrix, SkinAniMeshFrame* prm_frame_root, int prm_as0_index = -1, int prm_as1_index = -1,
           bool** prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = nullptr);

    //D3DXAniMeshActor維持用、削除予定
    std::list< SkinAniMeshFrame*> *GetDrawList() {
        return &m_DrawFrameList;
    }
public:
   /**
    * フレームワールド行列算出再帰関数 .
    * @param frame_world ボーンフレーム
    */
    void CalcSkinAniMeshFrame(SkinAniMeshFrame* frame_world);
    void CalcSkinAniMeshFrame_old(SkinAniMeshFrame* frame_world);   //D3DXAniMeshActor維持用、削除予定
};

}

#endif /*GGAF_DX_SKINANIMESHWORLDMATSTACK_H_*/
