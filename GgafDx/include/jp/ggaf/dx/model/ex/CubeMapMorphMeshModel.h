#ifndef GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#define GGAF_DX_CUBEMAPMORPHMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
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
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".modelx"��ǉ�����ƃ��f����`�t�@�C�����ɂȂ�B
     */
    CubeMapMorphMeshModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~CubeMapMorphMeshModel();
};

}
#endif /*GGAF_DX_CUBEMAPMORPHMESHMODEL_H_*/

