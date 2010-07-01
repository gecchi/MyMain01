#ifndef GGAFDX9UVFLIPPER_H_
#define GGAFDX9UVFLIPPER_H_
namespace GgafDx9Core {

/**
 * テクスチャUVフリッパー.
 * テクスチャをパラパラアニメが如く切り替える事を簡単に行うために
 * 作成したクラス。
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class GgafDx9UvFlipper : public GgafCore::GgafObject {
private:

    /** 内部アニメフレーム用カウンタ */
    DWORD _frame_counter_uvflip;


public:
    GgafDx9GeometricActor* _pActor;

    float _tex_width;
    float _tex_height;
    int _tex_col_num;

    /** 現在表示中のアニメパターン番号(0～) */
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

    int* _paInt_PtnOffset_Customized;
    int _nPtn_Customized;
    int _cnt_Customized;
    GgafDx9UvFlipper(GgafDx9GeometricActor* prm_pActor);


    virtual ~GgafDx9UvFlipper();


    void copyStatesFrom(GgafDx9UvFlipper* prm_pUvFlipper_Other) {
        _tex_width             = prm_pUvFlipper_Other->_tex_width;
        _tex_height            = prm_pUvFlipper_Other->_tex_height;
        _tex_col_num           = prm_pUvFlipper_Other->_tex_col_num;
        _pattno_uvflip_now     = prm_pUvFlipper_Other->_pattno_uvflip_now;
        _pattno_uvflip_top     = prm_pUvFlipper_Other->_pattno_uvflip_top;
        _pattno_uvflip_bottom  = prm_pUvFlipper_Other->_pattno_uvflip_bottom;
        _frame_uvflip_interval = prm_pUvFlipper_Other->_frame_uvflip_interval;
        _uvflip_method         = prm_pUvFlipper_Other->_uvflip_method;
        _is_reverse_order_in_oscillate_animation_flg =
                prm_pUvFlipper_Other->_is_reverse_order_in_oscillate_animation_flg;
    }

    /**
     * テクスチャのフリッピングパターンの番号に対応するUV座標のズレるオフセットを定義する。 .
     * <pre>
     * ＜例＞
     *
     *   setTextureUvRotation(3, 1.0/5, 1.0/4);
     *   forcePtnNoRange(0,9);
     *   setPtnNo(5);
     *
     * を実行時のパターン概念図
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
     * ０～９はパターン番号と呼ぶこととする。
     * 描画時、頂点バッファの各頂点のUV座標に、
     * アクティブなパターンの左上のUV座標がオフセットとして加算されることを想定して本メソッドを作成。
     * 上の図の例では、パターン番号5がアクティブなのでこの状態で
     *
     *   float u, v;
     *   getUV(u, v);
     *
     * を実行するとパターン番号5番の左上のUV座標の
     *
     *   u = 0.4, v = 0.25
     *
     * が得られる。
     * 本メソッドによるパターン設定は、この getUV() メソッドの結果にのみ影響を与える。
     * getUV()を使用しないのでれば、本メソッドによる設定は無意味である。
     *
     * 【補足】
     * GgafDx9UvFlipper はフレームワークの描画処理に埋め込まれているアクタークラスが存在する。
     * メンバ _pUvFlipper が存在しているクラスがそれである。
     * 描画時にどのように作用しているかここにメモを残す。
     *
     * ・GgafDx9SpriteActor
     *   GgafDx9SpriteSetActor
     *   GgafDx9BoardActor
     *   GgafDx9BoardSetActor
     *   GgafDx9PointSpriteActor について・・・
     *       描画時、現在パターン番号(_pattno_uvflip_now) のみ参照されている。getUV() は内部で使用していない。
     *       したがって、setTextureUvRotation() の呼び出しはフレームワークの描画処理では無意味。
     *       アニメーションのUV座標のオフセット情報は、定義Xファイル(拡張子.sprx)から読み取られて、モデルで保持している。
     *       上記アクター実装者は _pattno_uvflip_now の操作だけで良い。（そして実装者は俺）
     *       コンストラクタで以下の初期処理を実行している。
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW GgafDx9UvFlipper(this);
     *       _pUvFlipper->forcePtnNoRange(0, 最大アニメーションパターン番号);
     *       _pUvFlipper->setPtnNo(0);
     *       _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *
     * ・GgafDx9SpriteMeshActor
     *   GgafDx9SpriteMeshSetActor  について・・・
     *       内部で getUV() を使用している。よって setTextureUvRotation() による設定が必須。
     *       描画時頂点バッファのUV座標に getUV() で得たUVオフセット値をシェーダーへ渡し加算している。
     *       しかし『setTextureUvRotation() は内部で実行していない』ため、継承クラス側の初期処理などで、
     *       事前に１回は setTextureUvRotation() を呼び出して、パターンの番号とUV座標（オフセット値）の
     *       対応を定義しておく事が前提となる作りになっている。UV切り替えしないのであれば別の呼ばなくても大丈夫。
     *       コンストラクタで以下の初期処理を実行している。必要に応じて下位実装クラスで setTextureUvRotation() 等を行うという仕組み。
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW GgafDx9UvFlipper(this);
     *       _pUvFlipper->forcePtnNoRange(0, 算出した最大アニメーションパターン番号);
     *       _pUvFlipper->setPtnNo(0);
     *       _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *
     * ・その他のアクタークラスについて・・・
     *       クラス内部に GgafDx9UvFlipper は組み込まれていない。
     *
     * 【まとめ】
     * 要は GgafDx9SpriteMeshActor, GgafDx9SpriteSetMeshActor 利用時は
     * setTextureUvRotation() の事前実行が必要、他は不要。
     * （TODO:本クラスの事前呼び出しをクラスの仕組みで強制させる仕組みは現在無い。いずれ作りたい。が、とりあえず今は自分で気を付ける）
     * </pre>
     * @param prm_tex_col_num パターンのカラム数。UV座標を改行するために使用される(自然数)
     * @param prm_tex_width １パターンの幅(0.0f～1.0f)
     * @param prm_tex_height １パターンの高さ(0.0f～1.0f)
     */
    virtual void setTextureUvRotation(int prm_tex_col_num, float prm_tex_width, float prm_tex_height);

    /**
     * アニメーションを1フレーム分進行させる .
     * 本メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
     * 呼び出すことで、setFlipMethod()で設定した方法に応じて<BR>
     * アクティブなパターン番号(_pattno_uvflip_now)が内部で切り替わります。<BR>
     */
    virtual void behave();

    /**
     * 現在のアニメーションパターン番号(_pattno_uvflip_now)に対応するUV座標を取得する。 .
     * 事前に setTextureUvRotation() の呼び出を行ってく必要がある。
     * @param out_u [out] 座標U
     * @param out_v [out] 座標V
     */
    virtual void getUV(float& out_u, float& out_v);


    /**
     * 現在のアニメーションパターンを設定する .
     * @param prm_pattno_uvflip アニメーションパターン番号
     */
    void setPtnNo(int prm_pattno_uvflip);

    /**
     * アニメーションパターンを上限のアニメーションパターン番号(一番若い番号)に設定する .
     */
    void setPtnNoToTop();

    /**
     * アニメーションパターンの範囲を制限する .
     * @param prm_top 上限のアニメーションパターン番号(若い方の番号)
     * @param prm_bottom 下限のアニメーションパターン番号(古い方の番号。若いの反対語ってないのか)
     */
    void forcePtnNoRange(int prm_top, int prm_bottom);

    void customizePtnOrder(int prm_aPtnOffset[], int prm_num);

    /**
     * アニメーション方法を設定する .
     * <pre>
     * ＜例＞forcePtnNoRange(0,5) が設定済みとした場合。
     * FLIP_ORDER_LOOP     : 0,1,2,3,4,5,0,1,2,3,4,5,...
     * FLIP_REVERSE_LOOP   : 5,4,3,2,1,0,5,4,3,2,1,0,5,4...
     * FLIP_ORDER_NOLOOP   : 0,1,2,3,4,5,5,5,5,5,5,5...
     * FLIP_REVERSE_NOLOOP : 5,4,3,2,1,0,0,0,0,0,0...
     * FLIP_OSCILLATE_LOOP : 0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
     * NOT_ANIMATED        : 3,3,3,3,3,3,3... （何もしない）
     * </pre>
     * @param prm_method アニメーション方法定数
     * @param prm_interval アニメーション間隔フレーム（default=1)
     */
    void setFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval = 1);

};

}
#endif /*GGAFDX9SPRITEMESHACTOR_H_*/
