#ifndef GGAFDXCUBEMAPMESHSETMODEL_H_
#define GGAFDXCUBEMAPMESHSETMODEL_H_
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"

namespace GgafDxCore {

/**
 * ���}�b�v���b�V���Z�b�g���f�� .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshSetModel : public GgafDxMeshSetModel {
    friend class GgafDxModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxCubeMapMeshSetModel(char* prm_model_name);

    virtual ~GgafDxCubeMapMeshSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCUBEMAPMESHSETMODEL_H_*/

