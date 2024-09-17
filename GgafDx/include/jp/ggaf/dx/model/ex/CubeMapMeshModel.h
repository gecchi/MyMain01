#ifndef GGAF_DX_CUBEMAPMESHMODEL_H_
#define GGAF_DX_CUBEMAPMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
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
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".modelx"��ǉ�����ƃ��f����`�t�@�C�����ɂȂ�B
     */
    CubeMapMeshModel(const char* prm_model_id);

    virtual ~CubeMapMeshModel();
};

}
#endif /*GGAF_DX_CUBEMAPMESHMODEL_H_*/

