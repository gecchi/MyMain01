#include "jp/ggaf/dx/util/WorldMatStack.h"
#include "jp/ggaf/dx/util/AllocHierarchyWorldFrame.h"

using namespace GgafDx;

WorldMatStack::WorldMatStack(void) : GgafCore::Object() {
}

WorldMatStack::~WorldMatStack(void) {
}

// ワールド変換行列の設定
void WorldMatStack::SetWorldMatrix(D3DXMATRIX* worldmat) {
    m_WorldTransMatrix = *worldmat;
}

void WorldMatStack::UpdateFrame(FrameWorldMatrix* frame_world) {
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

void WorldMatStack::CalcFrameWorldMatrix(FrameWorldMatrix* frame_world) {
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
        CalcFrameWorldMatrix((FrameWorldMatrix*)frame_world->pFrameFirstChild);
        m_MatrixStack.pop(); // 子フレームがもう終わったのでスタックを1つ外す
    }

    // 兄弟フレームがあれば「現在の」スタックを利用
    if (frame_world->pFrameSibling) {
        //_TRACE_("兄弟フレームへいきます");
        CalcFrameWorldMatrix((FrameWorldMatrix*)frame_world->pFrameSibling);
    }
}

// 描画リストを取得
std::list<FrameWorldMatrix*> *WorldMatStack::GetDrawList() {
    return &m_DrawFrameList;
}
