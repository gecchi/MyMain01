#ifndef GGAFDXEFFECTCONNECTION_H_
#define GGAFDXEFFECTCONNECTION_H_
namespace GgafDxCore {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffectConnection : public GgafCore::GgafResourceConnection<GgafDxEffect> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr エフェクト識別名(＝ファイル名)
     * @param prm_pEffect エフェクト
     */
    GgafDxEffectConnection(char* prm_idstr, GgafDxEffect* prm_pEffect);

    /**
     * オーバーライド
     */
    void processReleaseResource(GgafDxEffect* prm_pResource);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxEffectConnection() {
    }
};

}
#endif /*GGAFDXEFFECTCONNECTION_H_*/
