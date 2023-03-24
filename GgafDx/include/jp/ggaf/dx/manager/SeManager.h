#ifndef GGAF_DX_SEMANAGER_H_
#define GGAF_DX_SEMANAGER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/dx/sound/Se.h"

namespace GgafDx {

/**
 * Se 管理クラス .
 * 生成済み Se オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class SeManager : public GgafCore::ResourceManager<Se> {

    /** [r]サウンドエフェクト・マスターボリューム割合 0.0～1.0 */
    double _se_master_volume_rate;

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称
     */
    SeManager(const char* prm_manager_name);

    GgafCore::ResourceConnection<Se>* processCreateConnection(const char* prm_idstr, Se* prm_pResource) override;

    Se* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    void setSeMasterVolumeRate(double prm_volume_rate);

    double getSeMasterVolumeRate();

    virtual ~SeManager() {
    }
};

}
#endif /*GGAF_DX_SEMANAGER_H_*/
