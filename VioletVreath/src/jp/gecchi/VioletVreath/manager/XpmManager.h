#ifndef XPMMANAGER_H_
#define XPMMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/core/util/GgafXpm.h"
namespace VioletVreath {

/**
 * Pixmap(GgafCore::GgafXpm)資源管理クラス .
 * 生成済み GgafXpm オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2014/10/06
 * @author Masatoshi Tsuge
 */
class XpmManager : public GgafCore::GgafResourceManager<GgafCore::GgafXpm> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    XpmManager(const char* prm_manager_name);

    GgafCore::GgafXpm* processCreateResource(char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<GgafCore::GgafXpm>* processCreateConnection(char* prm_idstr, GgafCore::GgafXpm* prm_pResource) override;


    virtual ~XpmManager() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/
