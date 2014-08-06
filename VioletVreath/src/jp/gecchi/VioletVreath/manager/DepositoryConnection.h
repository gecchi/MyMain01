#ifndef DEPOSITORYCONNECTION_H_
#define DEPOSITORYCONNECTION_H_
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

namespace VioletVreath {

/**
 * Depository�ւ̃R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DepositoryConnection : public GgafCore::GgafResourceConnection<GgafCore::GgafActorDepository> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pDepo �f�|�W�g��
     */
    DepositoryConnection(char* prm_idstr, GgafCore::GgafActorDepository* prm_pDepo);

    void processReleaseResource(GgafCore::GgafActorDepository* prm_pResource);

    virtual ~DepositoryConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
