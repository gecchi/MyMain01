#ifndef GGAF_DX_EFFECTCONNECTION_H_
#define GGAF_DX_EFFECTCONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class EffectConnection : public GgafCore::ResourceConnection<Effect> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr エフェクト識別名(＝ファイル名)
     * @param prm_pEffect エフェクト
     */
    EffectConnection(const char* prm_idstr, Effect* prm_pEffect);

    /**
     * オーバーライド
     */
    void processReleaseResource(Effect* prm_pResource);

    /**
     * デストラクタ<BR>
     */
    virtual ~EffectConnection() {
    }
};

}
#endif /*GGAF_DX_EFFECTCONNECTION_H_*/
