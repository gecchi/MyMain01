#ifndef GGAFDX9SPRITEACTORD_H_
#define GGAFDX9SPRITEACTORD_H_
namespace GgafDx9Core {

/**
 * スプライトアクター.
 * GgafDx9GeometricActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです。<BR>
 * いわゆる板ポリ<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteActor : public GgafDx9DrawableActor {

public:
    /** モデルオブジェクトへのポインタ */
    GgafDx9SpriteModel* _pSpriteModel;
    /** エフェクト */
    GgafDx9SpriteEffect* _pSpriteEffect;
    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFliper* _pUvFliper;

    GgafDx9SpriteActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteActor();

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

};

}
#endif /*GGAFDX9SPRITEACTORD_H_*/
