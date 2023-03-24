#ifndef GGAF_DX_BGMMANAGER_H_
#define GGAF_DX_BGMMANAGER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/dx/sound/Bgm.h"

namespace GgafDx {

/**
 * Bgm 管理クラス .
 * 生成済み Bgm オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class BgmManager : public GgafCore::ResourceManager<Bgm> {

    /** [r]BGM・マスターボリュームの割合 0.0～1.0 */
    double _bgm_master_volume_rate;

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    BgmManager(const char* prm_manager_name);

    Bgm* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<Bgm>* processCreateConnection(const char* prm_idstr, Bgm* prm_pResource) override;

    void setBgmMasterVolumeRate(double prm_volume_rate);

    float getBgmMasterVolumeRate();


    /**
     * 現在演奏中の全てのBGMボリュームを更新 .
     */
    void updateVolume();

    virtual ~BgmManager() {
    }
};

}
#endif /*GGAF_DX_BGMMANAGER_H_*/
