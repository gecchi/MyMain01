#ifndef GGAFDX9SPRITESETACTOR_H_
#define GGAFDX9SPRITESETACTOR_H_
namespace GgafDx9Core {

//enum GgafDx9AnimationMethod {
//    ORDER_LOOP, REVERSE_LOOP, OSCILLATE_LOOP, ORDER_NOLOOP, REVERSE_NOLOOP, NOT_ANIMATED
//};

/**
 * スプライトアクター.
 * GgafDx9GeometricActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです。<BR>
 */
class GgafDx9SpriteSetActor : public GgafDx9DrawableActor {

private:

    /** 内部アニメフレーム用カウンタ */
    unsigned int _aniframe_counter;

public:
    int _draw_set_num;
//    int _draw_set_index;
//    int _draw_object_num;


    /** モデルオブジェクトへのポインタ */
    GgafDx9SpriteSetModel* _pSpriteSetModel;

    /** エフェクト */
    GgafDx9SpriteSetEffect* _pSpriteSetEffect;

    /** アニメパターン番号の上限番号 */
    unsigned int _pattno_ani_top;
    /** 現在表示中のアニメパターン番号 */
    unsigned int _pattno_ani_bottom;
    /** 現在表示中のアニメパターン番号(0～) */
    unsigned int _pattno_ani_now;
    /** パターンとパターンの間隔フレーム数 */
    unsigned int _frame_ani_interval;
    /** アニメ方式 */
    GgafDx9AnimationMethod _animation_method;
    /** OSCILLATE_LOOP用の現在のアニメ方向 */
    bool _is_reverse_order_in_oscillate_animation_flg;

    /** ビルボード要否 */
    bool _isBillboardingFlg;

    GgafDx9SpriteSetActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDraw();

    virtual ~GgafDx9SpriteSetActor(); //デストラクタ

    /**
     * アニメーションを次のコマへ進める .
     * アニメーションを行いたい場合メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
     */
    void addNextAnimationFrame();

    /**
     * アニメーションパターンを設定する .
     * @param prm_pattno_ani アニメーションパターン番号
     */
    void setActivAnimationPattern(int prm_pattno_ani);

    /**
     * アニメーションパターンを上限のアニメーションパターン番号に設定する .
     */
    void resetActivAnimationPattern();

    /**
     * アニメーションパターンの範囲を制限する .
     * @param prm_top 上限のアニメーションパターン番号
     * @param prm_bottom 下限のアニメーションパターン番号
     */
    void setAnimationPatternRenge(int prm_top, int prm_bottom);

    /**
     * アニメーション方法を設定する.
     * @param prm_method アニメーション方法定数
     * @param prm_interval アニメーション間隔フレーム（default=1)
     */
    void setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_interval);

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

    /**
     * ビルボード有効 .
     * （デフォルトは無効です）<BR>
     */
    void enableBillboarding() {
        _isBillboardingFlg = true;
    }

    /**
     * ビルボード無効 .
     * （デフォルトは無効です）<BR>
     */
    void disableBillboarding() {
        _isBillboardingFlg = false;
    }
};

}
#endif /*GGAFDX9SPRITESETACTOR_H_*/
