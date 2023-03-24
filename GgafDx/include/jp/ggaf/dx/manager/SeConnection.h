#ifndef GGAF_DX_SECONNECTION_H_
#define GGAF_DX_SECONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/sound/Se.h"

namespace GgafDx {

/**
 * Se�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class SeConnection : public GgafCore::ResourceConnection<Se> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �T�E���h�G�t�F�N�g���ʖ�
     * @param prm_pSe �T�E���h�G�t�F�N�g�I�u�W�F�N�g�i���l�̃|�C���^�j
     */
    SeConnection(const char* prm_idstr, Se* prm_pSe);

    void processReleaseResource(Se* prm_pResource);

    virtual ~SeConnection() {
    }
};

}
#endif /*GGAF_DX_SECONNECTION_H_*/
