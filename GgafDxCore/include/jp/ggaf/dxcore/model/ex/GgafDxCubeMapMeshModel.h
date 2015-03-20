#ifndef GGAFDXCORE_GGAFDXCUBEMAPMESHMODEL_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"

namespace GgafDxCore {

/**
 * ���}�b�v���b�V�����f�� .
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshModel : public GgafDxMeshModel {
    friend class GgafDxModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxCubeMapMeshModel(char* prm_model_name);

    virtual ~GgafDxCubeMapMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMESHMODEL_H_*/

