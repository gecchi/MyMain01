#ifndef GGAFDX9SPRITESETACTOR_H_
#define GGAFDX9SPRITESETACTOR_H_
namespace GgafDx9Core {

//enum GgafDx9UvFlipMethod {
//    FLIP_ORDER_LOOP, FLIP_REVERSE_LOOP, FLIP_OSCILLATE_LOOP, FLIP_ORDER_NOLOOP, FLIP_REVERSE_NOLOOP, NOT_ANIMATED
//};

/**
 * スプライトアクター.
 * GgafDx9GeometricActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです。<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteSetActor : public GgafDx9DrawableActor {

private:
//
//    /** 内部アニメフレーム用カウンタ */
//    unsigned int _frame_counter_uvflip;

public:
    int _draw_set_num;
//    int _draw_set_index;
//    int _draw_object_num;



    /** モデルオブジェクトへのポインタ */
    GgafDx9SpriteSetModel* _pSpriteSetModel;

    /** エフェクト */
    GgafDx9SpriteSetEffect* _pSpriteSetEffect;

    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFliper* _pUvFliper;
//    /** アニメパターン番号の上限番号 */
//    unsigned int _pattno_uvflip_top;
//    /** 現在表示中のアニメパターン番号 */
//    unsigned int _pattno_uvflip_bottom;
//    /** 現在表示中のアニメパターン番号(0～) */
//    unsigned int _pattno_uvflip_now;
//    /** パターンとパターンの間隔フレーム数 */
//    unsigned int _frame_uvflip_interval;
//    /** アニメ方式 */
//    GgafDx9UvFlipMethod _uvflip_method;
//    /** FLIP_OSCILLATE_LOOP用の現在のアニメ方向 */
//    bool _is_reverse_order_in_oscillate_animation_flg;


    GgafDx9SpriteSetActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafDx9Checker* prm_pChecker );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDraw() override;

    virtual ~GgafDx9SpriteSetActor(); //デストラクタ

//    /**
//     * アニメーションを次のコマへ進める .
//     * アニメーションを行いたい場合メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
//     */
//    void behaveUvFlip();
//
//    /**
//     * アニメーションパターンを設定する .
//     * @param prm_pattno_uvflip アニメーションパターン番号
//     */
//    void setUvFlipPtnNo(int prm_pattno_uvflip);
//
//    /**
//     * アニメーションパターンを上限のアニメーションパターン番号に設定する .
//     */
//    void resetUvFlipPtnNo();
//
//    /**
//     * アニメーションパターンの範囲を制限する .
//     * @param prm_top 上限のアニメーションパターン番号
//     * @param prm_bottom 下限のアニメーションパターン番号
//     */
//    void forceUvFlipPtnRange(int prm_top, int prm_bottom);
//
//    /**
//     * アニメーション方法を設定する.
//     * @param prm_method アニメーション方法定数
//     * @param prm_interval アニメーション間隔フレーム（default=1)
//     */
//    void setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval);

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

};

}
#endif /*GGAFDX9SPRITESETACTOR_H_*/
