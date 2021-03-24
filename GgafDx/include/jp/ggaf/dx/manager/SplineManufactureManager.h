#ifndef GGAF_DX_SPLINEMANUFACTUREMANAGER_H_
#define GGAF_DX_SPLINEMANUFACTUREMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {
/**
 * SplineManufacture 管理クラス .
 * 生成済み SplineManufacture オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureManager : public GgafCore::ResourceManager<SplineManufacture> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    SplineManufactureManager(const char* prm_manager_name);

    SplineManufacture* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<SplineManufacture>* processCreateConnection(const char* prm_idstr, SplineManufacture* prm_pResource) override;

    virtual ~SplineManufactureManager() {
    }
};

}
#endif /*GGAF_DX_SPLINEMANUFACTUREMANAGER_H_*/
