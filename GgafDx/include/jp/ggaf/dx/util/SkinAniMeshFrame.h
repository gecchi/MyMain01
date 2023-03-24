#ifndef GGAF_DX_SKINANIMESHFRAME_H_
#define GGAF_DX_SKINANIMESHFRAME_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

namespace GgafDx {

/**
 * ���[���h�ϊ��s��t���t���[���\����
 */
class SkinAniMeshFrame : public BoneAniMeshFrame {
public:
    DWORD _bone_id;
    /** �{�[���I�t�Z�b�g�s�� */
    D3DXMATRIX _bone_offset_matrix; //���[�J�����_���{�[����Ԃ̍��W�ɕϊ�����s��
                                    //�l�����Fboneanimesh ��X�t�@�C���̃��b�V���́Askin���b�V�����_�Ƀ{�[���I�t�Z�b�g�s����|�������́i�ł͂Ȃ����H�j
    D3DXMATRIX _combined_matrix;  // �����s��
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIXEX_H_*/
