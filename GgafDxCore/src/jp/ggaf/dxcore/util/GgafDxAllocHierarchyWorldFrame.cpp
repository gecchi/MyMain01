#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAllocHierarchyWorldFrame::GgafDxAllocHierarchyWorldFrame(void)
{
}

GgafDxAllocHierarchyWorldFrame::~GgafDxAllocHierarchyWorldFrame(void)
{
}


// ワールド変換行列付きのフレーム構造体を生成
D3DXFRAME* GgafDxAllocHierarchyWorldFrame::createNewFrame()
{
    D3DXFRAME_WORLD* tmp = NEW D3DXFRAME_WORLD;
    ZeroMemory( tmp, sizeof(D3DXFRAME_WORLD) );
    addDelList( NEW Deleter<D3DXFRAME_WORLD>( tmp ) );
    return tmp;
}
