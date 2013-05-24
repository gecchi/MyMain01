#include "stdafx.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAllocHierarchyWorldFrame::GgafDxAllocHierarchyWorldFrame(void)
{
}

GgafDxAllocHierarchyWorldFrame::~GgafDxAllocHierarchyWorldFrame(void)
{
}


// ���[���h�ϊ��s��t���̃t���[���\���̂𐶐�
D3DXFRAME* GgafDxAllocHierarchyWorldFrame::createNewFrame()
{
    D3DXFRAME_WORLD* tmp = NEW D3DXFRAME_WORLD;
    ZeroMemory( tmp, sizeof(D3DXFRAME_WORLD) );
    addDelList( NEW Deleter<D3DXFRAME_WORLD>( tmp ) );
    return tmp;
}
