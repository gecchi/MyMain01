#include "jp/ggaf/dxcore/util/GgafDxWorldMatStack.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxWorldMatStack::GgafDxWorldMatStack(void) : GgafObject() {
}

GgafDxWorldMatStack::~GgafDxWorldMatStack(void) {
}

// ワールド変換行列の設定
void GgafDxWorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    m_WorldTransMatrix = *worldmat;
}

void GgafDxWorldMatStack::UpdateFrame(D3DXFRAME_WORLD* frame_world) {
    // スタックの初期化
    while (!m_MatrixStack.empty())
        m_MatrixStack.pop();

    // 描画フレームリストの初期化
    m_DrawFrameList.clear();

    // ワールド変換行列をスタックに積む
    m_MatrixStack.push(&m_WorldTransMatrix);

    // ルートフレームからワールド変換行列を連続計算
    CalcFrameWorldMatrix(frame_world);
}

void GgafDxWorldMatStack::CalcFrameWorldMatrix(D3DXFRAME_WORLD* frame_world) {
    // 現在のスタックの先頭にあるワールド変換行列を参照
    D3DXMATRIX *pStackMat = m_MatrixStack.top();

    D3DXMatrixMultiply(&(frame_world->WorldTransMatrix), &(frame_world->TransformationMatrix), pStackMat);

    if (frame_world->pMeshContainer) {
        //_TRACE_("フレームにメッシュコンテナがあり");
        // 引数のフレームに対応するワールド変換行列を計算
        m_DrawFrameList.push_back(frame_world);
    }


//    // フレームにメッシュコンテナがあれば、このフレームをリストに追加する
//    if (frame_world->pMeshContainer) {
//        _TRACE_("フレームにメッシュコンテナがあり");
//        // 引数のフレームに対応するワールド変換行列を計算
//        D3DXMatrixMultiply(&frame_world->WorldTransMatrix, &frame_world->TransformationMatrix, pStackMat);
//        m_DrawFrameList.push_back(frame_world);
//    } else {
//        D3DXMatrixMultiply(&frame_world->WorldTransMatrix, &frame_world->TransformationMatrix, pStackMat);
//        m_DrawFrameList.push_back(frame_world);
//    }

    // 子フレームがあればスタックを積んで、子フレームのワールド変換座標の計算へ
    if (frame_world->pFrameFirstChild) {
        m_MatrixStack.push(&(frame_world->WorldTransMatrix));
        CalcFrameWorldMatrix((D3DXFRAME_WORLD*)frame_world->pFrameFirstChild);
        m_MatrixStack.pop(); // 子フレームがもう終わったのでスタックを1つ外す
    }

    // 兄弟フレームがあれば「現在の」スタックを利用
    if (frame_world->pFrameSibling) {
        //_TRACE_("兄弟フレームへいきます");
        CalcFrameWorldMatrix((D3DXFRAME_WORLD*)frame_world->pFrameSibling);
    }
}

// 描画リストを取得
std::list<D3DXFRAME_WORLD*> *GgafDxWorldMatStack::GetDrawList() {
    return &m_DrawFrameList;
}
