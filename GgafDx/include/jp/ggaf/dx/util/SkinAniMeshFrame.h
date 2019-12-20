#ifndef GGAF_DX_SKINANIMESHFRAME_H_
#define GGAF_DX_SKINANIMESHFRAME_H_
#include "GgafDxCommonHeader.h"

#include <map>
#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

namespace GgafDx {

/**
 * ���[���h�ϊ��s��t���t���[���\����
 */
class SkinAniMeshFrame : public BoneAniMeshFrame {
public:
    D3DXMATRIX bone_offset_matrix;    // �{�[���I�t�Z�b�g�s��
    D3DXMATRIX conbined_matrix;  // �����s��
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIXEX_H_*/
