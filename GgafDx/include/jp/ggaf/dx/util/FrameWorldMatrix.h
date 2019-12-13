#ifndef GGAF_DX_FRAMEWORLDMATRIX_H_
#define GGAF_DX_FRAMEWORLDMATRIX_H_
#include "GgafDxCommonHeader.h"

#include <map>
#include "jp/ggaf/dx/util/AllocHierarchy.h"

namespace GgafDx {

/**
 * ���[���h�ϊ��s��t���t���[���\����
 */
class FrameWorldMatrix : public D3DXFRAME {
public:
    /** �t���[���c���[�𒼗񉻂����ۂ̗v�f�ԍ� */
    UINT _frame_index; //WorldMatStack �� _prevTransformationMatrixList �̗v�f�ԍ��ƈ�v������K�v������
    /** �`�掞�A�v�Z��̃��[���h�ϊ��s�񂪊i�[����� */
    D3DXMATRIX _world_trans_matrix;
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIX_H_*/
