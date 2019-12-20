#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
using namespace GgafDx;

BoneAniMeshWorldMatStack::BoneAniMeshWorldMatStack() : GgafCore::Object() {
//    _pModel_MapBoneFrameIndex_ActAnimationSetIndexList = nullptr;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _as0_index = -1;
    _as1_index = -1;
    _prevTransformationMatrixList.clear();
}

BoneAniMeshWorldMatStack::~BoneAniMeshWorldMatStack(void) {
}

void BoneAniMeshWorldMatStack::registerFrameTransformationMatrix(BoneAniMeshFrame* pFrame) {
    _prevTransformationMatrixList.push_back(pFrame->TransformationMatrix);
    if (pFrame->pFrameFirstChild) {
        // 子フレーム有り
        registerFrameTransformationMatrix((BoneAniMeshFrame*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //兄弟フレーム有り
        registerFrameTransformationMatrix((BoneAniMeshFrame*)pFrame->pFrameSibling);
    }
}
// ワールド変換行列の設定
void BoneAniMeshWorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    _actor_world_trans_matrix = *worldmat;
}

void BoneAniMeshWorldMatStack::UpdateFrame(BoneAniMeshFrame* prm_frame_root, int prm_as0_index, int prm_as1_index, bool** prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act) {
#ifdef MY_DEBUG
    if (_prevTransformationMatrixList.size() == 0) {
        throwCriticalException("BoneAniMeshWorldMatStack::UpdateFrame() を実行前にregisterFrameTransformationMatrix() でフレーム登録して下さい。");
    }
#endif
    // スタックの初期化
    while (!_stack_matrix.empty())
        _stack_matrix.pop();

    // ワールド変換行列をスタックに積む
    _stack_matrix.push(&_actor_world_trans_matrix);
    _as0_index = prm_as0_index;
    _as1_index = prm_as1_index;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = prm_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act;
    // ルートフレームからワールド変換行列を連続計算
    if (_papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act) {
        CalcBoneAniMeshFrame(prm_frame_root);
    } else {
        m_DrawFrameList.clear();  //削除予定
        CalcBoneAniMeshFrame_old(prm_frame_root);  //削除予定
    }
}

void BoneAniMeshWorldMatStack::CalcBoneAniMeshFrame_old(BoneAniMeshFrame* prm_pBoneFrame) {
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
        CalcBoneAniMeshFrame_old((BoneAniMeshFrame*)prm_pBoneFrame->pFrameFirstChild);
        _stack_matrix.pop(); // 子フレームがもう終わったのでスタックを1つ外す
    }

    // 兄弟フレームがあれば「現在の」スタックを利用
    if (prm_pBoneFrame->pFrameSibling) {
        //_TRACE_("兄弟フレームへいきます");
        CalcBoneAniMeshFrame_old((BoneAniMeshFrame*)prm_pBoneFrame->pFrameSibling);
    }
}

void BoneAniMeshWorldMatStack::CalcBoneAniMeshFrame(BoneAniMeshFrame* prm_pBoneFrame) {
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
        //アニメーションコントローラーの pAc->AdvanceTime(0, nullptr) によりモデルのフレームの TransformationMatrix が更新されているので、
        //それを(prm_pBoneFrame->TransformationMatrix) を使用してワールド変換
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), &(prm_pBoneFrame->TransformationMatrix), pStackMat);
        //TransformationMatrix を保存
        _prevTransformationMatrixList[prm_pBoneFrame->_frame_index]  = prm_pBoneFrame->TransformationMatrix;
    } else {
        //アニメーション対象のフレームでない
        //アニメーションコントローラーの pAc->AdvanceTime(0, nullptr) でも、モデルのフレームの TransformationMatrix が影響されないので、
        //以前の何かのアニメーション時の行列が残ってしまっている。よってそれ(prm_pBoneFrame->TransformationMatrix) は使用しない。
        //前回保存の TransformationMatrix 使用してワールド変換する。つまりこのボーンは前回と変わらず停止状態。
        D3DXMATRIX* pMatrix = &(_prevTransformationMatrixList[prm_pBoneFrame->_frame_index]); //前回保存済みのTransformationMatrix
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), pMatrix, pStackMat);
    }

    // 子フレームがあればスタックを積んで、子フレームのワールド変換座標の計算へ
    if (prm_pBoneFrame->pFrameFirstChild) {
        _stack_matrix.push(&(prm_pBoneFrame->_world_trans_matrix));
        CalcBoneAniMeshFrame((BoneAniMeshFrame*)prm_pBoneFrame->pFrameFirstChild);
        _stack_matrix.pop(); // 子フレームがもう終わったのでスタックを1つ外す
    }

    // 兄弟フレームがあれば「現在の」スタックを利用
    if (prm_pBoneFrame->pFrameSibling) {
        CalcBoneAniMeshFrame((BoneAniMeshFrame*)prm_pBoneFrame->pFrameSibling);
    }
}

