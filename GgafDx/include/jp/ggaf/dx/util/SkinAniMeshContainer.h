#ifndef GGAF_DX_SKINANIMESHCONTAINER_H_
#define GGAF_DX_SKINANIMESHCONTAINER_H_
#include "GgafDxCommonHeader.h"

#include <map>

namespace GgafDx {

/**
 * ���[���h�ϊ��s��t���t���[���\����
 */
class SkinAniMeshContainer : public D3DXMESHCONTAINER {
public:
    DWORD dwMaxInfleNum;            // �{�[���ő�e����
    DWORD dwBoneCombNum;            // �{�[���R���r�l�[�V������
    D3DXBONECOMBINATION *pBoneComb;  // �{�[���R���r�l�[�V�����\���̔z��ւ̃|�C���^
};

}
#endif /*GGAF_DX_SKINANIMESHCONTAINER_H_*/
