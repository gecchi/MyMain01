#ifndef GGAF_DX_CUBEMAPMESHSETMODEL_H_
#define GGAF_DX_CUBEMAPMESHSETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"

namespace GgafDx {

/**
 * ���}�b�v���b�V���Z�b�g���f�� .
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetModel : public MeshSetModel {
    friend class ModelManager;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    CubeMapMeshSetModel(const char* prm_model_name);

    virtual ~CubeMapMeshSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_CUBEMAPMESHSETMODEL_H_*/

