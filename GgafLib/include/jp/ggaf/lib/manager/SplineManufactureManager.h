#ifndef GGAFLIB_SPLINEMANUFACTUREMANAGER_H_
#define GGAFLIB_SPLINEMANUFACTUREMANAGER_H_
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

namespace GgafLib {
/**
 * SplineManufacture 管理クラス .
 * 生成済み SplineManufacture オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureManager : public GgafCore::GgafResourceManager<SplineManufacture> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    SplineManufactureManager(const char* prm_manager_name);

    SplineManufacture* processCreateResource(char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<SplineManufacture>* processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource) override;

    virtual ~SplineManufactureManager() {
    }
};

}
#endif /*GGAFLIB_SPLINEMANUFACTUREMANAGER_H_*/
