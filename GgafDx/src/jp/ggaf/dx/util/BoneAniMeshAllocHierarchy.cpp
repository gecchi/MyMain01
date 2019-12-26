#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"

#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

using namespace GgafDx;

BoneAniMeshAllocHierarchy::BoneAniMeshAllocHierarchy() : AllocHierarchy() {
}

BoneAniMeshAllocHierarchy::~BoneAniMeshAllocHierarchy() {
}

D3DXFRAME* BoneAniMeshAllocHierarchy::createNewFrame() {
    BoneAniMeshFrame* tmp = NEW BoneAniMeshFrame;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    //独自追加した分の初期化
    tmp->_frame_index = UINT_MAX; // 0 有効なインデックスなので 0 で初期化したくなかった
    D3DXMatrixIsIdentity(&(tmp->_world_trans_matrix)); //とりあえず単位行列
    return tmp;
}
D3DXMESHCONTAINER* BoneAniMeshAllocHierarchy::createNewMeshContainer() {
    return AllocHierarchy::createNewMeshContainer(); //今のところ変更なし
}
