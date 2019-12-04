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
    ZeroMemory( tmp, sizeof(FrameWorldMatrix) );
//    addDelList( NEW Deleter<FrameWorldMatrix>( tmp ) );
    return tmp;
}
