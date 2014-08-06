#ifndef DEPOSITORYCONNECTION_H_
#define DEPOSITORYCONNECTION_H_
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

namespace VioletVreath {

/**
 * Depositoryへのコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DepositoryConnection : public GgafCore::GgafResourceConnection<GgafCore::GgafActorDepository> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pDepo デポジトリ
     */
    DepositoryConnection(char* prm_idstr, GgafCore::GgafActorDepository* prm_pDepo);

    void processReleaseResource(GgafCore::GgafActorDepository* prm_pResource);

    virtual ~DepositoryConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
