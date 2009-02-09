#ifndef GGAFDX9EFFECTLEAD_H_
#define GGAFDX9EFFECTLEAD_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9EffectLead : public GgafCore::GgafResourceLead<ID3DXEffect> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
     * @param prm_pID3DXEffect テクスチャ
     */
    GgafDx9EffectLead(char* prm_idstr, ID3DXEffect* prm_pID3DXEffect);

    /**
     * オーバーライド
     */
    void processReleaseResource(ID3DXEffect* prm_pResource);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9EffectLead() {
    }
};

}
#endif /*GGAFDX9EFFECTLEAD_H_*/
