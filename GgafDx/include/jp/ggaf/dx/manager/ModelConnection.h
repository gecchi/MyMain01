#ifndef GGAF_DX_MODELCONNECTION_H_
#define GGAF_DX_MODELCONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * ���f�������̃R�l�N�V����.
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class ModelConnection : public GgafCore::ResourceConnection<Model> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���f�����ʖ�
     * @param prm_pModel ���\�[�X�ƂȂ郂�f��
     */
    ModelConnection(const char* prm_idstr, Model* prm_pModel);

    void processReleaseResource(Model* prm_pResource);

    virtual ~ModelConnection() {
    }
};

}
#endif /*GGAF_DX_MODELCONNECTION_H_*/
