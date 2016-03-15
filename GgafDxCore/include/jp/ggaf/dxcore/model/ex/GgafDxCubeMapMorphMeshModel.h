#ifndef GGAFDXCORE_GGAFDXCUBEMAPMORPHMESHMODEL_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"

namespace GgafDxCore {

/**
 * ���}�b�v���[�t���b�V�����f�� .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMorphMeshModel : public GgafDxMorphMeshModel {
    friend class GgafDxModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxCubeMapMorphMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual ~GgafDxCubeMapMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMORPHMESHMODEL_H_*/

