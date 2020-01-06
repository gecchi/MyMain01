#ifndef GGAF_DX_SKINANIMESHCONTAINER_H_
#define GGAF_DX_SKINANIMESHCONTAINER_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/BoneAniMeshContainer.h"

namespace GgafDx {

/**
 * ���[���h�ϊ��s��t���t���[���\����
 */
class SkinAniMeshContainer : public BoneAniMeshContainer {
public:
    DWORD _dwMaxInfleNum;            // �{�[���ő�e����
    DWORD _dwBoneCombNum;            // �{�[���R���r�l�[�V������
    ID3DXBuffer* _pBoneCombinationTable;
//    D3DXBONECOMBINATION* _pBoneComb; // �{�[���R���r�l�[�V�����\���̔z��ւ̃|�C���^
    DWORD _dwBoneOffsetMatrixNum;
    D3DXMATRIX* _paBoneOffsetMatrix;
};

}
#endif /*GGAF_DX_SKINANIMESHCONTAINER_H_*/
