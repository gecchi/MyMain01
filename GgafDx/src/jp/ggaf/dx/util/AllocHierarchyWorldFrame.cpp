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
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    //�ǉ��������� ZeroMemory ���Ȃ�
//    D3DXMATRIX _world_trans_matrix;
//    std::map<uint64_t, D3DXMATRIX*> Actor_PrevTransformationMatrix;



//    addDelList( NEW Deleter<FrameWorldMatrix>( tmp ) );
    return tmp;
}
