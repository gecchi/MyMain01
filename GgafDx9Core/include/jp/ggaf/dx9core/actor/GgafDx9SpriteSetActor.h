#ifndef GGAFDX9SPRITESETACTOR_H_
#define GGAFDX9SPRITESETACTOR_H_
namespace GgafDx9Core {

/**
 * スプライトセットアクター.
 * GgafDx9DrawableActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、複数同時描画に最適化されたアクターです。<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteSetActor : public GgafDx9DrawableActor {

public:
    /** 同時描画セット数 */
    int _draw_set_num;

    /** モデルオブジェクトへのポインタ */
    GgafDx9SpriteSetModel* _pSpriteSetModel;

    /** エフェクト */
    GgafDx9SpriteSetEffect* _pSpriteSetEffect;

    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9SpriteSetActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteSetActor();

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

};

}
#endif /*GGAFDX9SPRITESETACTOR_H_*/
