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
    //�Ǝ��ǉ��������̏�����
    tmp->_frame_index = UINT_MAX; // 0 �L���ȃC���f�b�N�X�Ȃ̂� 0 �ŏ������������Ȃ�����
    D3DXMatrixIsIdentity(&(tmp->_world_trans_matrix)); //�Ƃ肠�����P�ʍs��
    return tmp;
}
D3DXMESHCONTAINER* BoneAniMeshAllocHierarchy::createNewMeshContainer() {
    return AllocHierarchy::createNewMeshContainer(); //���̂Ƃ���ύX�Ȃ�
}
