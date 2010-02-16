#ifndef GGAFDX9UVFLIPER_H_
#define GGAFDX9UVFLIPER_H_
namespace GgafDx9Core {

/**
 * テクスチャUVフリッパー.
 * テクスチャをパラパラアニメが如く切り替える事を簡単に行うために
 * 作成したクラス。
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class GgafDx9UvFliper : public GgafCore::GgafObject {
private:

    /** 内部アニメフレーム用カウンタ */
    int _frame_counter_uvflip;


public:
    GgafDx9GeometricActor* _pActor;

    float _tex_width;
    float _tex_height;
    int _tex_col_num;

    /** 現在表示中のアニメパターン番号(0〜) */
    int _pattno_uvflip_now;

    /** アニメパターン番号の上限番号 */
    int _pattno_uvflip_top;
    /** 現在表示中のアニメパターン番号 */
    int _pattno_uvflip_bottom;
    /** パターンとパターンの間隔フレーム数 */
    DWORD _frame_uvflip_interval;
    /** アニメ方式 */
    GgafDx9UvFlipMethod _uvflip_method;
    /** FLIP_OSCILLATE_LOOP用の現在のアニメ方向 */
    bool _is_reverse_order_in_oscillate_animation_flg;


    GgafDx9UvFliper(GgafDx9GeometricActor* prm_pActor);


    virtual ~GgafDx9UvFliper();

    /**
     * テクスチャのフリッピングパターンの番号に対応するUV座標のズレを定義する。
     * ＜例＞
     * setTextureUvRotation(3, 1.0/5, 1.0/4);
     * forceUvFlipPtnRange(0,9);
     * setUvFlipPtnNo(5);
     *
     * を実行時の概念図
     *
     *          3 = prm_tex_col_num
     *     <-------->
     *     0.2 = prm_tex_width
     *     <-->
     * (0,0)              (1,0)
     *     +--+--+--+--+--+  ^
     *     | 0| 1| 2|  |  |  | 0.25 = prm_tex_height
     *     +--+--+--+--+--+  v
     *     | 3| 4|!5|  |  |
     *     +--+--+--+--+--+
     *     | 6| 7| 8|  |  |
     *     +--+--+--+--+--+
     *     | 9|  |  |  |  |
     *     +--+--+--+--+--+
     * (1,0)              (1,1)
     *  u,v
     *
     * (※"!" は現在アクティブなパターン番号)
     *
     * ０〜９はパターン番号と呼ばれる。
     * 描画時、頂点バッファの各頂点のUV座標に、
     * アクティブなパターンの左上のUV座標がオフセットとして加算されることになる。
     * 上の図の例では、パターン番号5がアクティブなので全頂点のUV座標は(+0.4, +0.25)加算される。
     * @param prm_tex_col_num UV座標を改行するパターン数(自然数)
     * @param prm_tex_width １パターンの幅(0.0f〜1.0f)
     * @param prm_tex_height １パターンの高さ(0.0f〜1.0f)
     */
    virtual void setTextureUvRotation(int prm_tex_col_num, float prm_tex_width, float prm_tex_height);

    /**
     * アニメーションを進行させる .
     * 本メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
     * 呼び出すことで、setUvFlipMethod()で設定した方法に応じて<BR>
     * アクティブなパターンが内部で切り替わります。<BR>
     */
    virtual void behave();

    /**
     * UV座標を取得する。
     * @param out_u [out] 座標U
     * @param out_v [out] 座標V
     */
    virtual void getUV(float& out_u, float& out_v);


    /**
     * 現在のアニメーションパターンを設定する .
     * @param prm_pattno_uvflip アニメーションパターン番号
     */
    void setUvFlipPtnNo(int prm_pattno_uvflip);

    /**
     * アニメーションパターンを上限のアニメーションパターン番号(一番若い方の番号)に設定する .
     */
    void resetUvFlipPtnNo();

    /**
     * アニメーションパターンの範囲を制限する .
     * @param prm_top 上限のアニメーションパターン番号(若い方の番号)
     * @param prm_bottom 下限のアニメーションパターン番号(古い方の番号。若いの反対語ってないのか；)
     */
    void forceUvFlipPtnRange(int prm_top, int prm_bottom);

    /**
     * アニメーション方法を設定する.
     * @param prm_method アニメーション方法定数
     * @param prm_interval アニメーション間隔フレーム（default=1)
     */
    void setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval = 1);

};

}
#endif /*GGAFDX9SPRITEMESHACTOR_H_*/
