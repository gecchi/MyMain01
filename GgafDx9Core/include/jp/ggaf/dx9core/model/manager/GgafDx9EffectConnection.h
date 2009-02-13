#ifndef GGAFDX9EFFECTCONNECTION_H_
#define GGAFDX9EFFECTCONNECTION_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9EffectConnection : public GgafCore::GgafResourceConnection<ID3DXEffect> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
     * @param prm_pID3DXEffect テクスチャ
     */
    GgafDx9EffectConnection(char* prm_idstr, ID3DXEffect* prm_pID3DXEffect);

    /**
     * オーバーライド
     */
    void processReleaseResource(ID3DXEffect* prm_pResource);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9EffectConnection() {
    }
};

}
#endif /*GGAFDX9EFFECTCONNECTION_H_*/
