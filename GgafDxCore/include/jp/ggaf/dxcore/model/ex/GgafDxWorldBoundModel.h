#ifndef GGAFDXCORE_GGAFDXWORLDMODEL_H_
#define GGAFDXCORE_GGAFDXWORLDMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"

namespace GgafDxCore {

/**
 * ���E���E���f�� .
 * @version 1.00
 * @since 2011/05/20
 * @author Masatoshi Tsuge
 */
class GgafDxWorldBoundModel : public GgafDxMorphMeshModel {
    friend class GgafDxModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxWorldBoundModel(char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual ~GgafDxWorldBoundModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXWORLDMODEL_H_*/

