﻿#ifndef GGAFDX9EFFECTCONNECTION_H_
#define GGAFDX9EFFECTCONNECTION_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDx9EffectConnection : public GgafCore::GgafResourceConnection<GgafDx9Effect> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_idstr エフェクト識別名(＝ファイル名)
     * @param prm_pEffect エフェクト
     */
    GgafDx9EffectConnection(char* prm_idstr, GgafDx9Effect* prm_pEffect);

    /**
     * オーバーライド
     */
    void processReleaseResource(GgafDx9Effect* prm_pResource);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9EffectConnection() {
    }
};

}
#endif /*GGAFDX9EFFECTCONNECTION_H_*/
