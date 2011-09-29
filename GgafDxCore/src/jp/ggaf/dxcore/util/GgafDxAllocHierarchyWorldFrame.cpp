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


// ���[���h�ϊ��s��t���̃t���[���\���̂𐶐�
D3DXFRAME* GgafDxAllocHierarchyWorldFrame::CreateNewFrame()
{
    D3DXFRAME_WORLD* tmp = NEW D3DXFRAME_WORLD;
    ZeroMemory( tmp, sizeof(D3DXFRAME_WORLD) );
    AddDelList( NEW deleter<D3DXFRAME_WORLD>( tmp ) );
    return tmp;
}
