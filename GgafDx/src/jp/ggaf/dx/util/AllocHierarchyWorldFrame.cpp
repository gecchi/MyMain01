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
    D3DXFRAME_WORLD* tmp = NEW D3DXFRAME_WORLD;
    ZeroMemory( tmp, sizeof(D3DXFRAME_WORLD) );
    addDelList( NEW Deleter<D3DXFRAME_WORLD>( tmp ) );
    return tmp;
}
