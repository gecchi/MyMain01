#ifndef GGAF_DX_BONEANIMESHFRAME_H_
#define GGAF_DX_BONEANIMESHFRAME_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * ���[���h�ϊ��s��t���t���[���\����
 */
class BoneAniMeshFrame : public D3DXFRAME {
public:
    /** �t���[���c���[�𒼗񉻂����ۂ̗v�f�ԍ� */
    DWORD _frame_index; //BoneAniMeshWorldMatStack �� _prevTransformationMatrixList �̗v�f�ԍ��ƈ�v������K�v������
    /** �`�掞�A�v�Z��̃��[���h�ϊ��s�񂪊i�[����� */
    D3DXMATRIX _world_trans_matrix;
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIX_H_*/
