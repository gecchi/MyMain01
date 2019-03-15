#ifndef GGAF_DX_CUBEMAPMESHMODEL_H_
#define GGAF_DX_CUBEMAPMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MeshModel.h"

namespace GgafDx {

/**
 * ���}�b�v���b�V�����f�� .
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class CubeMapMeshModel : public MeshModel {
    friend class ModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    CubeMapMeshModel(const char* prm_model_name);

    virtual ~CubeMapMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_CUBEMAPMESHMODEL_H_*/
