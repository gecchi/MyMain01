#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9AllocHierarchyWorldFrame::GgafDx9AllocHierarchyWorldFrame(void)
{
}

GgafDx9AllocHierarchyWorldFrame::~GgafDx9AllocHierarchyWorldFrame(void)
{
}


// ���[���h�ϊ��s��t���̃t���[���\���̂𐶐�
D3DXFRAME* GgafDx9AllocHierarchyWorldFrame::CreateNewFrame()
{
    D3DXFRAME_WORLD* tmp = NEW D3DXFRAME_WORLD;
    ZeroMemory( tmp, sizeof(D3DXFRAME_WORLD) );
    AddDelList( NEW deleter<D3DXFRAME_WORLD>( tmp ) );
    return tmp;
}
