#ifndef DEPOSITORYCONNECTION_H_
#define DEPOSITORYCONNECTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"

namespace VioletVreath {

/**
 * Depository�ւ̃R�l�N�V����.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DepositoryConnection : public GgafCore::ResourceConnection<GgafCore::ActorDepository> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pDepo �f�|�W�g��
     */
    DepositoryConnection(const char* prm_idstr, GgafCore::ActorDepository* prm_pDepo);

    void processReleaseResource(GgafCore::ActorDepository* prm_pResource);

    virtual ~DepositoryConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
