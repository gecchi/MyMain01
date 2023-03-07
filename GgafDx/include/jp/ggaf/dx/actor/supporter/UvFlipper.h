#ifndef GGAF_DX_UVFLIPPER_H_
#define GGAF_DX_UVFLIPPER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafDx {

/**
 * テクスチャUVフリッパー.
 * テクスチャをパラパラアニメが如く切り替える事を簡単に行うために
 * 作成したクラス。
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class UvFlipper : public GgafCore::Object {
private:

    /** 内部アニメフレーム用カウンタ */
    frame _frame_counter_uvflip;

public:

    struct UV {
        float _u;
        float _v;
    };

    /** [r/w]アニメパターン0番の左上基準U座標(0.0～1.0) */
    float _base_u;
    /** [r/w]アニメパターン0番の左上基準V座標(0.0～1.0) */
    float _base_v;
    /** [r/w]１つのアニメパターンの幅(0.0～1.0) */
    float _one_ptn_tex_width;
    /** [r/w]１つのアニメパターンの高さ(0.0～1.0) */
    float _one_ptn_tex_height;
    /** [r]アニメパターンのカラム数(横に並ぶパターン数) */
    int _ptn_col_num;
    /** [r]アニメパターンの行数(縦に並ぶパターン数) */
    int _ptn_row_num;

    /** [r/w]現在表示中のアニメパターン番号(0～) */
    int _pattno_uvflip_now;
    /** [r/w]最大アニメパターン番号 */
    int _pattno_uvflip_max;
    /** [r/w]アニメパターン番号の上限番号 */
    int _pattno_uvflip_top;
    /** [r/w]アニメパターン番号の下限番号 */
    int _pattno_uvflip_bottom;
    /** [r/w]パターンとパターンの間隔フレーム数 */
    frame _uvflip_interval_frames;
    /** [r]アニメ方式 */
    UvFlippingMethod _uvflip_method;
    /** [r]FLIP_OSCILLATE_LOOP用の現在のアニメ方向 */
    bool _is_reverse_order_in_oscillate_animation_flg;

    int* _pa_ptn_offset_customized;
    int _ptn_customized;
    int _cnt_customized;
    /** [r]内部UV配列 */
    UV* _paUV;

public:
    UvFlipper();

    virtual ~UvFlipper();

    void copyStatesFrom(UvFlipper* prm_pUvFlipper_other) {
        _one_ptn_tex_width      = prm_pUvFlipper_other->_one_ptn_tex_width;
        _one_ptn_tex_height     = prm_pUvFlipper_other->_one_ptn_tex_height;
        _ptn_col_num            = prm_pUvFlipper_other->_ptn_col_num;
        _pattno_uvflip_now      = prm_pUvFlipper_other->_pattno_uvflip_now;
        _pattno_uvflip_top      = prm_pUvFlipper_other->_pattno_uvflip_top;
        _pattno_uvflip_bottom   = prm_pUvFlipper_other->_pattno_uvflip_bottom;
        _pattno_uvflip_max      = prm_pUvFlipper_other->_pattno_uvflip_max;
        _uvflip_interval_frames = prm_pUvFlipper_other->_uvflip_interval_frames;
        _uvflip_method          = prm_pUvFlipper_other->_uvflip_method;
        _is_reverse_order_in_oscillate_animation_flg =
                prm_pUvFlipper_other->_is_reverse_order_in_oscillate_animation_flg;
    }

    /**
     * テクスチャのフリッピングパターンの番号に対応するUV座標のズレるオフセットを定義する。 .
     * <pre>
     * ＜例＞
     *
     *   _pUvFlipper->locatePatternNo(0, 0, 1.0/5, 1.0/4, 3, 10);
     *   _pUvFlipper->setActivePtn(5);
     *
     * を実行時のパターン概念図
     *
     *          3 = prm_ptn_col_num
     *     <-------->
     *     1.0/5 = 0.2 = prm_one_ptn_tex_width
     *     <-->
     * (0,0)              (1,0)
     *     +--+--+--+--+--+  ^
     *     | 0| 1| 2|  |  |  | 1.0/4 = 0.25 = prm_one_ptn_tex_height
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
     * ０～９はパターン番号と呼ぶこととする。(prm_num_of_max_patterns で番号数が決まる)
     * パターン番号の並び順は左上から右へ、改行して再び右への順で固定。
     * 但し、基準となる左上の座標、改行までのパターン数は設定が可能。
     * 描画時、頂点バッファの各頂点のUV座標に、
     * アクティブなパターンの左上のUV座標がオフセットとして加算されることを想定して本メソッドを作成。
     * 上の図の例では、パターン番号5がアクティブなのでこの状態で
     *
     *   float u, v;
     *   _pUvFlipper->getUV(u, v);
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
     * UvFlipper はフレームワークの描画処理に埋め込まれているアクタークラスが存在する。
     * メンバ _pUvFlipper が存在しているクラスがそれである。
     *
     * ・SpriteActor
     *   SpriteSetActor
     *   BoardActor
     *   BoardSetActor
     *   PointSpriteActor について・・・
     *       コンストラクタで以下の初期処理を実行している。
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW UvFlipper();
     *       _pUvFlipper->locatePatternNo(縦分割数, 横分割数);
     *       _pUvFlipper->setActivePtn(0);
     *       _pUvFlipper->exec(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *       縦分割数, 横分割数はスプライト定義ファイル(.sprx)から取得される。
     *
     * ・SpriteMeshActor
     *   SpriteMeshSetActor  について・・・
     *       コンストラクタで以下の初期処理を実行している。必要に応じて下位実装クラスで locatePatternNo() を再実行可能。
     *       ----------------------------------------------------------
     *       _pUvFlipper = NEW UvFlipper();
     *       _pUvFlipper->locatePatternNo(1, 1);
     *       _pUvFlipper->setActivePtn(0);
     *       _pUvFlipper->exec(NOT_ANIMATED, 1);
     *       ----------------------------------------------------------
     *
     * ・その他のアクタークラスについて・・・
     *       クラス内部に UvFlipper は組み込まれていない。
     *
     * </pre>
     * @param prm_base_u 基準左上U座標(0.0f～1.0f)
     * @param prm_base_v 基準左上V座標(0.0f～1.0f)
     * @param prm_one_ptn_tex_width １パターンの幅(0.0f～1.0f)
     * @param prm_one_ptn_tex_height １パターンの高さ(0.0f～1.0f)
     * @param prm_ptn_col_num パターンのカラム数(横に並ぶパターン数)
     * @param prm_num_of_max_patterns 最大パターン数 (1～)
     */
    virtual void locatePatternNo(float prm_base_u, float prm_base_v,
                                 float prm_one_ptn_tex_width, float prm_one_ptn_tex_height,
                                 int prm_ptn_col_num, int prm_num_of_max_patterns);

    /**
     * テクスチャのフリッピングパターンの番号に対応するUV座標のズレるオフセットを定義する。 .
     * locatePatternNo(float, float, float, float, int, int); <BR>
     * の簡易設定版。内部で他の引数の値が自動計算されて実行される。 <BR>
     * locatePatternNo(5, 4); とした場合以下のようになる。 <BR>
     * <pre>
     *     prm_base_u = 0
     *     prm_base_v = 0
     *
     *              5 = prm_ptn_col_num
     *     <-------------->
     *     1.0/5 = 0.2 = prm_one_ptn_tex_width
     *     <-->
     * (0,0)              (1,0)
     *     +--+--+--+--+--+  ^
     *     | 0| 1| 2| 3| 4|  | 1.0/4 = 0.25 = prm_one_ptn_tex_height
     *     +--+--+--+--+--+  v
     *     | 5| 6| 7| 8| 9|
     *     +--+--+--+--+--+
     *     |10|11|12|13|14|
     *     +--+--+--+--+--+
     *     |15|16|17|18|19|
     *     +--+--+--+--+--+
     * (1,0)              (1,1)
     *
     *  prm_pattno_uvflip_max = 20 は引数に無いが、内部自動計算
     *
     *  </pre>
     * @param prm_ptn_col_num テクスチャ縦分割数
     * @param prm_ptn_row_num テクスチャ横分割数
     */
    virtual void locatePatternNo(int prm_ptn_col_num, int prm_ptn_row_num);
    virtual void locatePatternNo(IPlaneModel* prm_pPlaneModel);
    void remapPatternNoUv(int prm_ptn_num, ...);

    virtual void setBaseUv(float prm_base_u, float prm_base_v) {
        _base_u = prm_base_u;
        _base_v = prm_base_v;
    }

    /**
     * アニメーションを1フレーム分進行させる .
     * 本メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
     * 呼び出すことで、exec()で設定した方法に応じて<BR>
     * アクティブなパターン番号(_pattno_uvflip_now)が内部で切り替わります。<BR>
     */
    virtual void behave();

    /**
     * 現在のアニメーションパターン番号(_pattno_uvflip_now)に対応する左上のUV座標を取得する。 .
     * 事前に locatePatternNo() の呼び出を行ってく必要がある。
     * @param out_u[out] 座標U
     * @param out_v[out] 座標V
     */
    virtual void getUV(float& out_u, float& out_v);

    /**
     * 引数のアニメーションパターン番号に対応する左上のUV座標を取得する。 .
     * @param prm_pattno_uvflip アニメーションパターン番号
     * @param out_u[out] アニメーションパターン番号の座標U
     * @param out_v[out] アニメーションパターン番号座標V
     */
    virtual void getUV(int prm_pattno_uvflip, float& out_u, float& out_v);

    /**
     * 現在のアニメーションパターンを設定する .
     * setFlipPtnRange(int, int) の範囲外でも問題なく設定出来ます。
     * @param prm_pattno_uvflip アニメーションパターン番号
     */
    void setActivePtn(int prm_pattno_uvflip);

    /**
     * 現在のアニメーションパターンを取得する .
     * @return 現在のアニメーションパターン番号
     */
    inline int getActivePtn() {
        return _pattno_uvflip_now;
    }

    /**
     * フリップアニメーションパターンの上限の下限のパターン番号を設定 .
     * あくまで、フリップの上限下限であり、現在のパターン番号を制限するものではありません。<BR>
     * setActivePtn(int) で範囲外でパターン番号も問題なく設定出来ます。
     * @param prm_top 上限のアニメーションパターン番号(若い方の番号)
     * @param prm_bottom 下限のアニメーションパターン番号(古い方の番号。若い番号の反対語って古い番号なのだろうか；)
     */
    void setFlipPtnRange(int prm_top, int prm_bottom);

    /**
     * 上限パターン番号（最も若い番号）を取得 .
     * @return 上限パターン番号（最も若い番号）
     */
    int getTopPtnno() {
        return _pattno_uvflip_top;
    }

    /**
     * 下限パターン番号（最も古い番号）を取得 .
     * @return 下限パターン番号（最も古い番号）
     */
    int getBottomPtnno() {
        return _pattno_uvflip_bottom;
    }

    /**
     * 最大アニメパターン番号を取得 .
     * @return 最大アニメパターン番号
     */
    int getMaxPtnno() {
        return _pattno_uvflip_max;
    }

    /**
     * アニメーションパターンを上限パターン番号（最も若い番号）に設定する .
     */
    void setActivePtnToTop() {
        setActivePtn(_pattno_uvflip_top);
    }

    /**
     * アニメーションパターンを下限パターン番号（最も古い番号）に設定する .
     */
    void setActivePtnToBottom() {
        setActivePtn(_pattno_uvflip_bottom);
    }

    /**
     * 現在のアニメーションパターン番号を上限パターン番号からの(相対)番号数で設定する .
     * @param prm_pattno_uvflip_from_top 上限パターン番号からのパターン番号数
     */
    void setActivePtnFromTop(int prm_pattno_uvflip_from_top) {
        setActivePtn(_pattno_uvflip_top + prm_pattno_uvflip_from_top);
    }

    /**
     * FLIP_CUSTOMIZED_LOOP、FLIP_CUSTOMIZED_NOLOOP時のパターン順を定義。TODO:未テスト。 .
     * @param prm_aPtnOffset
     * @param prm_num
     */
    void customizePtnOrder(int prm_aPtnOffset[], int prm_num);

    /**
     * アニメーション方法を設定する .
     * <pre>
     * ＜例＞setFlipPtnRange(0,5) が設定済みとした場合。
     * FLIP_ORDER_LOOP     : 0,1,2,3,4,5,0,1,2,3,4,5,...
     * FLIP_REVERSE_LOOP   : 5,4,3,2,1,0,5,4,3,2,1,0,5,4...
     * FLIP_ORDER_NOLOOP   : 0,1,2,3,4,5,5,5,5,5,5,5...
     * FLIP_REVERSE_NOLOOP : 5,4,3,2,1,0,0,0,0,0,0...
     * FLIP_OSCILLATE_LOOP : 0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
     * NOT_ANIMATED        : 3,3,3,3,3,3,3... （何もしない）
     *
     * ＜ちょこっと特殊な使い方＞
     * 【例１】
     * setActivePtn(0);
     * setFlipPtnRange(3,5);
     * exec(FLIP_ORDER_LOOP); とした場合、
     * パターン番号: 0,1,2,3,4,5,3,4,5,3,4,5,...
     *
     * 【例２】
     * setActivePtn(5);
     * setFlipPtnRange(0,3);
     * exec(FLIP_REVERSE_LOOP); とした場合、
     * パターン番号: 5,4,3,2,1,0,3,2,1,0,3,2,1,0,...
     *
     * </pre>
     * @param prm_method フリップ順の方法
     * @param prm_interval フリップ間隔フレーム（default=1)
     */
    void exec(UvFlippingMethod prm_method, int prm_interval = 1);

    /**
     * アニメーションを停止 .
     */
    void stop() {
        exec(NOT_ANIMATED);
    }

    /**
     * アニメーション中であるか .
     * @return true : アニメーション中 / false : アニメーション中ではない
     */
    bool isFlipping() {
        return _uvflip_method == NOT_ANIMATED ? false : true;
    }

};

}
#endif /*GGAF_DX_SPRITEMESHACTOR_H_*/
