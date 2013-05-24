#ifndef GGAFDXCUBEMAPMORPHMESHMODEL_H_
#define GGAFDXCUBEMAPMORPHMESHMODEL_H_
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
    GgafDxCubeMapMorphMeshModel(char* prm_model_name);

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual ~GgafDxCubeMapMorphMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCUBEMAPMORPHMESHMODEL_H_*/

