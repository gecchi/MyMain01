#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"


using namespace GgafDx;

BoneAniMeshAllocHierarchy::BoneAniMeshAllocHierarchy(void)
{
}

BoneAniMeshAllocHierarchy::~BoneAniMeshAllocHierarchy(void)
{
}


// ���[���h�ϊ��s��t���̃t���[���\���̂𐶐�
D3DXFRAME* BoneAniMeshAllocHierarchy::createNewFrame()
{
    BoneAniMeshFrame* tmp = NEW BoneAniMeshFrame;
    ZeroMemory( tmp, sizeof(D3DXFRAME) );
    //	���L�̓Ǝ��ǉ��������� ZeroMemory ���Ȃ��Ŏ����ŏ�����
    //    /** �t���[���c���[�𒼗񉻂����ۂ̗v�f�ԍ� */
    //    UINT _frame_index; //BoneAniMeshWorldMatStack �� _prevTransformationMatrixList �̗v�f�ԍ��ƈ�v������K�v������
    //    /** �`�掞�A�v�Z��̃��[���h�ϊ��s�񂪊i�[����� */
    //    D3DXMATRIX _world_trans_matrix;

    return tmp;
}
