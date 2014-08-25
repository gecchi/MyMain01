#ifndef GGAFDXCORE_GGAFDXSECONNECTION_H_
#define GGAFDXCORE_GGAFDXSECONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/dxcore/sound/GgafDxSe.h"

namespace GgafDxCore {

/**
 * GgafDxSe�R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class GgafDxSeConnection : public GgafCore::GgafResourceConnection<GgafDxSe> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr �T�E���h�G�t�F�N�g���ʖ�
     * @param prm_pGgafDxSe �T�E���h�G�t�F�N�g�I�u�W�F�N�g�i���l�̃|�C���^�j
     */
    GgafDxSeConnection(char* prm_idstr, GgafDxSe* prm_pGgafDxSe);

    void processReleaseResource(GgafDxSe* prm_pResource);

    virtual ~GgafDxSeConnection() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXSECONNECTION_H_*/
