#ifndef GGAFDX9POINTSPRITEACTOR_H_
#define GGAFDX9POINTSPRITEACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9DrawableActor を継承し、独自のXファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * @version 1.00
 * @since 2009/02/26
 * @author Masatoshi Tsuge
 */
class GgafDx9PointSpriteActor : public GgafDx9DrawableActor {

public:

    /** モデル資源 */
    GgafDx9PointSpriteModel* _pPointSpriteModel;
    /** エフェクト資源 */
    GgafDx9PointSpriteEffect* _pPointSpriteEffect;

    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名。末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDx9PointSpriteActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    /**
     * α値設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha α値
     */
    void setAlpha(float prm_fAlpha) override;

    virtual ~GgafDx9PointSpriteActor(); //デストラクタ
};

}
#endif /*GGAFDX9POINTSPRITEACTOR_H_*/
