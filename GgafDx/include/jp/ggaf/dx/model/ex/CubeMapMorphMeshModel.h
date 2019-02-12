#ifndef GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#define GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"

namespace GgafDx {

/**
 * ���}�b�v���[�t���b�V�����f�� .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshModel : public MorphMeshModel {
    friend class ModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    CubeMapMorphMeshModel(const char* prm_model_name);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~CubeMapMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_CUBEMAPMORPHMESHMODEL_H_*/

