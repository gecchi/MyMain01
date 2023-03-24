#ifndef GGAF_DX_CURVEMANUFACTUREMANAGER_H_
#define GGAF_DX_CURVEMANUFACTUREMANAGER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {

/**
 * CurveManufacture 管理クラス .
 * 生成済み CurveManufacture オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveManufactureManager : public GgafCore::ResourceManager<CurveManufacture> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    CurveManufactureManager(const char* prm_manager_name);

    CurveManufacture* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<CurveManufacture>* processCreateConnection(const char* prm_idstr, CurveManufacture* prm_pResource) override;

    virtual ~CurveManufactureManager() {
    }
};

}
#endif /*GGAF_DX_CURVEMANUFACTUREMANAGER_H_*/
