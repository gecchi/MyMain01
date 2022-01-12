#include "jp/ggaf/dx/util/SkinAniMeshWorldMatStack.h"
#include "jp/ggaf/dx/util/SkinAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/util/SkinAniMeshFrame.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
using namespace GgafDx;

SkinAniMeshWorldMatStack::SkinAniMeshWorldMatStack() : GgafCore::Object() {
//    _pModel_MapBoneFrameIndex_ActAnimationSetIndexList = nullptr;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _as0_index = -1;
    _as1_index = -1;
    _prevTransformationMatrixList.clear();
}

SkinAniMeshWorldMatStack::~SkinAniMeshWorldMatStack(void) {
}

void SkinAniMeshWorldMatStack::registerFrameTransformationMatrix(SkinAniMeshFrame* pFrame) {
    _prevTransformationMatrixList.push_back(pFrame->TransformationMatrix);
    if (pFrame->pFrameFirstChild) {
        // 子フレーム有り
        registerFrameTransformationMatrix((SkinAniMeshFrame*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //兄弟フレーム有り
        registerFrameTransformationMatrix((SkinAniMeshFrame*)pFrame->pFrameSibling);
    }
}
// ワールド変換行列の設定
void SkinAniMeshWorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    _actor_world_trans_matrix = *worldmat;
}

void SkinAniMeshWorldMatStack::UpdateFrame(D3DXMATRIX* prm_pMatBaseTransformMatrix, SkinAniMeshFrame* prm_frame_root, int prm_as0_index, int prm_as1_index, bool** prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act) {
#ifdef MY_DEBUG
    if (_prevTransformationMatrixList.size() == 0) {
        throwCriticalException("SkinAniMeshWorldMatStack::UpdateFrame() を実行前にregisterFrameTransformationMatrix() でフレーム登録して下さい。");
    }
#endif
    // スタックの初期化
    while (!_stack_matrix.empty()) {
        _stack_matrix.pop();
    }
    // ワールド変換行列をスタックに積む
    D3DXMATRIX _mat_top;
    D3DXMatrixMultiply(&_mat_top, prm_pMatBaseTransformMatrix, &_actor_world_trans_matrix);//world変換に予め、ベース変換を掛けておく
    _stack_matrix.push(&_mat_top);
    _as0_index = prm_as0_index;
    _as1_index = prm_as1_index;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act;
    // ルートフレームからワールド変換行列を連続計算
    if (_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act) {
        CalcSkinAniMeshFrame(prm_frame_root);
    } else {
        m_DrawFrameList.clear();  //削除予定
        CalcSkinAniMeshFrame_old(prm_frame_root);  //削除予定
    }
}

void SkinAniMeshWorldMatStack::CalcSkinAniMeshFrame_old(SkinAniMeshFrame* prm_pBoneFrame) {
     //削除予定
    // 現在のスタックの先頭にあるワールド変換行列を参照
    D3DXMATRIX *pStackMat = _stack_matrix.top();
    D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), &(prm_pBoneFrame->TransformationMatrix), pStackMat);
    if (prm_pBoneFrame->pMeshContainer) {
        //メッシュコンテナ有り
        m_DrawFrameList.push_back(prm_pBoneFrame);
    }
    // 子フレームがあればスタックを積んで、子フレームのワールド変換座標の計算へ
    if (prm_pBoneFrame->pFrameFirstChild) {
        _stack_matrix.push(&(prm_pBoneFrame->_world_trans_matrix));
        CalcSkinAniMeshFrame_old((SkinAniMeshFrame*)prm_pBoneFrame->pFrameFirstChild);
        _stack_matrix.pop(); // 子フレームがもう終わったのでスタックを1つ外す
    }
    // 兄弟フレームがあれば「現在の」スタックを利用
    if (prm_pBoneFrame->pFrameSibling) {
        //_TRACE_("兄弟フレームへいきます");
        CalcSkinAniMeshFrame_old((SkinAniMeshFrame*)prm_pBoneFrame->pFrameSibling);
    }
}

void SkinAniMeshWorldMatStack::CalcSkinAniMeshFrame(SkinAniMeshFrame* prm_pBoneFrame) {
    // 現在のスタックの先頭にあるワールド変換行列を参照
    D3DXMATRIX *pStackMat = _stack_matrix.top();

    //このフレーム(frame_world)が、アニメーション対象なのか判定
    bool is_target_frame = false;
    LPSTR born_frame_name = prm_pBoneFrame->Name;
    if (born_frame_name) {
        if (_as0_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as0_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true; //このフレームは、トラック0のアニメーションセットのアニメーション対象である
        } else if (_as1_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as1_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true; //このフレームは、トラック1のアニメーションセットのアニメーション対象である
        }
    }

    if (is_target_frame) {
        //アニメーション対象のフレームである場合、
        //アニメーションコントローラーの pAc->AdvanceTime(t, nullptr) によりモデルのフレームの TransformationMatrix が更新されているので、
        //それを(prm_pBoneFrame->TransformationMatrix) を使用してワールド変換
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), &(prm_pBoneFrame->TransformationMatrix), pStackMat);
        D3DXMatrixMultiply(&(prm_pBoneFrame->_combined_matrix), &(prm_pBoneFrame->_bone_offset_matrix), &(prm_pBoneFrame->_world_trans_matrix));
        //TransformationMatrix を保存
        _prevTransformationMatrixList[prm_pBoneFrame->_frame_index]  = prm_pBoneFrame->TransformationMatrix;


    } else {
        //アニメーション対象のフレームでない
        //アニメーションコントローラーの pAc->AdvanceTime(t, nullptr) でも、モデルのフレームの TransformationMatrix が影響されないので、
        //以前の何かのアニメーション時の行列が残ってしまっている。よってそれ(prm_pBoneFrame->TransformationMatrix) は使用しない。
        //前回保存の TransformationMatrix 使用してワールド変換する。つまりこのボーンは前回と変わらず停止状態。
        D3DXMATRIX* pMatrix = &(_prevTransformationMatrixList[prm_pBoneFrame->_frame_index]); //前回保存済みのTransformationMatrix
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), pMatrix, pStackMat);
        D3DXMatrixMultiply(&(prm_pBoneFrame->_combined_matrix), &(prm_pBoneFrame->_bone_offset_matrix), &(prm_pBoneFrame->_world_trans_matrix));

    }

    // 子フレームがあればスタックを積んで、子フレームのワールド変換座標の計算へ
    if (prm_pBoneFrame->pFrameFirstChild) {
        _stack_matrix.push(&(prm_pBoneFrame->_world_trans_matrix));
        CalcSkinAniMeshFrame((SkinAniMeshFrame*)prm_pBoneFrame->pFrameFirstChild);
        _stack_matrix.pop(); // 子フレームがもう終わったのでスタックを1つ外す
    }

    // 兄弟フレームがあれば「現在の」スタックを利用
    if (prm_pBoneFrame->pFrameSibling) {
        CalcSkinAniMeshFrame((SkinAniMeshFrame*)prm_pBoneFrame->pFrameSibling);
    }
}

