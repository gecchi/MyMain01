#ifndef DEPOSITORYCONNECTION_H_
#define DEPOSITORYCONNECTION_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"

namespace VioletVreath {

/**
 * Depositoryへのコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class DepositoryConnection : public GgafCore::ResourceConnection<GgafCore::ActorDepository> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pDepo デポジトリ
     */
    DepositoryConnection(const char* prm_idstr, GgafCore::ActorDepository* prm_pDepo);

    void processReleaseResource(GgafCore::ActorDepository* prm_pResource);

    virtual ~DepositoryConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
