#include "jp/ggaf/dx/util/AllocHierarchyWorldFrame.h"


using namespace GgafDx;

AllocHierarchyWorldFrame::AllocHierarchyWorldFrame(void)
{
}

AllocHierarchyWorldFrame::~AllocHierarchyWorldFrame(void)
{
}


// ���[���h�ϊ��s��t���̃t���[���\���̂𐶐�
D3DXFRAME* AllocHierarchyWorldFrame::createNewFrame()
{
    FrameWorldMatrix* tmp = NEW FrameWorldMatrix;
    ZeroMemory( tmp, sizeof(FrameWorldMatrix) );
//    addDelList( NEW Deleter<FrameWorldMatrix>( tmp ) );
    return tmp;
}
