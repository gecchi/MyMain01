#include "jp/ggaf/dx/util/WorldMatStack.h"
#include "jp/ggaf/dx/util/AllocHierarchyWorldFrame.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
using namespace GgafDx;

WorldMatStack::WorldMatStack() : GgafCore::Object() {
//    _pModel_MapBoneFrameIndex_ActAnimationSetIndexList = nullptr;
    _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act = nullptr;
    _as0_index = -1;
    _as1_index = -1;
    _prevTransformationMatrixList.clear();
}

WorldMatStack::~WorldMatStack(void) {
}

void WorldMatStack::registerFrameTransformationMatrix(FrameWorldMatrix* pFrame) {
    _prevTransformationMatrixList.push_back(pFrame->TransformationMatrix);
    if (pFrame->pFrameFirstChild) {
        // 子フレーム有り
        registerFrameTransformationMatrix((FrameWorldMatrix*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //兄弟フレーム有り
        registerFrameTransformationMatrix((FrameWorldMatrix*)pFrame->pFrameSibling);
    }
}
// ワールド変換行列の設定
void WorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    _actor_world_trans_matrix = *worldmat;
}

void WorldMatStack::UpdateFrame(FrameWorldMatrix* prm_frame_world, int prm_as0_index, int prm_as1_index) {

    // スタックの初期化
    while (!m_MatrixStack.empty())
        m_MatrixStack.pop();

//    // 描画フレームリストの初期化
//    _vecDrawBoneFrame.clear();

    // ワールド変換行列をスタックに積む
    m_MatrixStack.push(&_actor_world_trans_matrix);
    _as0_index = prm_as0_index;
    _as1_index = prm_as1_index;
    // ルートフレームからワールド変換行列を連続計算
    CalcFrameWorldMatrix(prm_frame_world);
}

void WorldMatStack::CalcFrameWorldMatrix(FrameWorldMatrix* prm_pBoneFrame) {
    // 現在のスタックの先頭にあるワールド変換行列を参照
    D3DXMATRIX *pStackMat = m_MatrixStack.top();

    //このフレーム(frame_world)が、アニメーション対象なのか判定
    //アニメーション対象のフレームは、frame_world->TransformationMatrix を変換行列として使用する。
    //アニメーション対象ではないのフレームだった場合、アクターごとに保持している前回の変換行列を使用する。
    bool is_target_frame = false;
    LPSTR born_frame_name = prm_pBoneFrame->Name;
    if (born_frame_name) {
        if (_as0_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as0_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true;

        } else if (_as1_index >= 0 && _papaBool_Model_AnimationSetIndex_BoneFrameIndex_is_act[_as1_index][prm_pBoneFrame->_frame_index]) {
            is_target_frame = true;
        }
    }

    if (is_target_frame) {
        //アニメーション対象のフレームである
        _prevTransformationMatrixList[prm_pBoneFrame->_frame_index]  = prm_pBoneFrame->TransformationMatrix; //TransformationMatrix 保存
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), &(prm_pBoneFrame->TransformationMatrix), pStackMat);
    } else {
        D3DXMATRIX* pMatrix = &(_prevTransformationMatrixList[prm_pBoneFrame->_frame_index]);
        D3DXMatrixMultiply(&(prm_pBoneFrame->_world_trans_matrix), pMatrix, pStackMat);
    }

    // 子フレームがあればスタックを積んで、子フレームのワールド変換座標の計算へ
    if (prm_pBoneFrame->pFrameFirstChild) {
        m_MatrixStack.push(&(prm_pBoneFrame->_world_trans_matrix));
        CalcFrameWorldMatrix((FrameWorldMatrix*)prm_pBoneFrame->pFrameFirstChild);
        m_MatrixStack.pop(); // 子フレームがもう終わったのでスタックを1つ外す
    }

    // 兄弟フレームがあれば「現在の」スタックを利用
    if (prm_pBoneFrame->pFrameSibling) {
        //_TRACE_("兄弟フレームへいきます");
        CalcFrameWorldMatrix((FrameWorldMatrix*)prm_pBoneFrame->pFrameSibling);
    }
}

