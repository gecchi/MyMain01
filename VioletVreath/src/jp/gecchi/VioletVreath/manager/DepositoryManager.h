#ifndef DEPOSITORYMANAGER_H_
#define DEPOSITORYMANAGER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"

namespace VioletVreath {

/**
 * Depository 管理クラス .
 * 生成済み Depository オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class DepositoryManager : public GgafCore::ResourceManager<GgafCore::ActorDepository> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    DepositoryManager(const char* prm_manager_name);

    GgafCore::ActorDepository* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<GgafCore::ActorDepository>* processCreateConnection(const char* prm_idstr, GgafCore::ActorDepository* prm_pResource) override;

    virtual ~DepositoryManager() {
    }
};

}
#endif /*DEPOSITORYMANAGER_H_*/
