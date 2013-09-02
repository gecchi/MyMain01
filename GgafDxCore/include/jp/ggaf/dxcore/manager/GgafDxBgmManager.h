#ifndef GGAFDXCORE_GGAFDXBGMMANAGER_H_
#define GGAFDXCORE_GGAFDXBGMMANAGER_H_
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"

namespace GgafDxCore {

/**
 * GgafDxBgm 管理クラス .
 * 生成済み GgafDxBgm オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxBgmManager : public GgafCore::GgafResourceManager<GgafDxBgm> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDxBgmManager(const char* prm_manager_name);

    GgafDxBgm* processCreateResource(char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<GgafDxBgm>* processCreateConnection(char* prm_idstr, GgafDxBgm* prm_pResource) override;

    /**
     * 現在演奏中のBGMのボリュームを更新 .
     */
    void updateVolume();

    virtual ~GgafDxBgmManager() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXBGMMANAGER_H_*/
