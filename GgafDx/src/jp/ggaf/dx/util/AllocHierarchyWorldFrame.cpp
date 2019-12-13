#include "jp/ggaf/dx/util/AllocHierarchyWorldFrame.h"


using namespace GgafDx;

AllocHierarchyWorldFrame::AllocHierarchyWorldFrame(void)
{
}

AllocHierarchyWorldFrame::~AllocHierarchyWorldFrame(void)
{
}


// ワールド変換行列付きのフレーム構造体を生成
D3DXFRAME* AllocHierarchyWorldFrame::createNewFrame()
{
    FrameWorldMatrix* tmp = NEW FrameWorldMatrix;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    //追加した分は ZeroMemory しない
//    D3DXMATRIX _world_trans_matrix;
//    std::map<uint64_t, D3DXMATRIX*> Actor_PrevTransformationMatrix;



//    addDelList( NEW Deleter<FrameWorldMatrix>( tmp ) );
    return tmp;
}
