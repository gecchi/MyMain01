#ifndef GGAF_DX_WORLDMODEL_H_
#define GGAF_DX_WORLDMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"

namespace GgafDx {

/**
 * ���E���E���f�� .
 * @version 1.00
 * @since 2011/05/20
 * @author Masatoshi Tsuge
 */
class WorldBoundModel : public MorphMeshModel {
    friend class ModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".modelx"��ǉ�����ƃ��f����`�t�@�C�����ɂȂ�B
     */
    WorldBoundModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~WorldBoundModel();
};

}
#endif /*GGAF_DX_WORLDMODEL_H_*/

