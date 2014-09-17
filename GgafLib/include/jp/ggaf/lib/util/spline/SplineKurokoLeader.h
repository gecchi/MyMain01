#ifndef GGAFLIB_SPLINEKUROKOLEADER_H_
#define GGAFLIB_SPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafLib {

/**
 * スプライン曲線移動を実行するためのオブジェクト .
 * 黒衣に指示を出して移動を先導します。
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineKurokoLeader : public GgafCore::GgafObject {

public:
    enum SplinTraceOption {
        ABSOLUTE_COORD,     //絶対座標移動
        RELATIVE_COORD,     //スプライン座標の(0,0,0)を、アクターの現座標とし相対座標で計算
        RELATIVE_DIRECTION, //スプライン座標の(0,0,0)を、アクターの現座標とし相対座標とし、アクターの現在向き（_pKuroko の _ang_rz_mv, _ang_ry_mv)でスプライン座標群をワールド変換。
    };

    /** スプライン情報セット */
    SplineManufacture* _pManufacture;
    /** start()からの経過フレーム数 */
    frame _leading_frames;
    /** 先導開始をしたかどうか */
    bool _was_started;
    /** 現在先導中であるかどうか */
    bool _is_leading;
    /** 座標を操作する対象となるアクター */
    GgafDxCore::GgafDxGeometricActor* _pActor_target;
    /** コンストラクタ内部でSplineLineを生成した場合true/コンストラクタ引数にSplineLineが渡された場合false。一時しのぎいずれ消す。*/
    bool _is_created_pManufacture;
    /**
     * [r]オプション
     * ABSOLUTE_COORD     : 絶対座標移動。
     * RELATIVE_COORD     : 始点を現座標とし、スプライン座標群は相対移動で計算。
     * RELATIVE_DIRECTION : 始点を現座標とし、さらに現在の向き（_pKuroko の _ang_rz_mv, _ang_ry_mv)でスプライン座標群をワールド変換。
     */
    SplinTraceOption _option;
    /** [r] ループカウンタ */
    int _cnt_loop;
    /** [r] 設定ループ数。-1 で無限 */
    int _max_loop;

    /** [r]始点X座標 */
    coord _x_start;
    /** [r]始点Y座標 */
    coord _y_start;
    /** [r]始点Z座標 */
    coord _z_start;

    coord _offset_x;
    coord _offset_y;
    coord _offset_z;

    int _flip_x;
    int _flip_y;
    int _flip_z;
    /** [r]アクターの現在位置からスプライン始点までの距離。start()時点で更新される。 */
    int _distance_to_begin;
    /** [r]現在向かっている最中の補完点(基準点も含む)の数 */
    int _point_index;
    /** [r]始点座標を固定する。（固定しない場合は黒子Aのアクターの座標になる） */
    bool _is_fix_start_pos;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pKuroko
     */
    SplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    /**
     * 各補完点を読み込み時、X軸方向、Y軸方向、Z軸方向それぞれに加算(平行移動)し、補正します .
     * デフォルトは adjustCoordOffset(0, 0, 0) となります。<BR>
     * <b>[注意]</b><BR>
     * 内部で、adjustAxisXFlip() adjustAxisYFlip() adjustAxisZFlip() が考慮され、
     * さらに Manufacture のXYZ方向の補正割合が乗じられた後、一番最後に
     * adjustCoordOffset()  が考慮され差分加算されます。<BR>
     * @param prm_offset_x X軸方向補正増加分
     * @param prm_offset_y Y軸方向補正増加分
     * @param prm_offset_z Z軸方向補正増加分
     */
    virtual void adjustCoordOffset(coord prm_offset_x, coord prm_offset_y, coord prm_offset_z);

    /**
     * スプラインの各座標点を、X軸反転します。
     */
    virtual void adjustAxisXFlip() {
        _flip_x = -_flip_x;
    }

    /**
     * スプラインの各座標点を、Y軸反転します。
     */
    virtual void adjustAxisYFlip() {
        _flip_y = -_flip_y;
    }

    /**
     * スプラインの各座標点を、Z反転します。
     */
    virtual void adjustAxisZFlip() {
        _flip_z = -_flip_z;
    }

    /**
     * 対象アクター(_pActor_target)の座標を、スプラインの一番最初の制御点座標で設定する .
     * start(SplineKurokoLeader::ABSOLUTE_COORD) の場合、つまり「絶対座標移動スプライン」の場合、
     * 有効な設定となりうるでしょう。<BR>
     */
    void setAbsoluteBeginCoord();

    /**
     * 後からスプラインオブジェクトを設定。
     * @param prm_pManufacture
     */
    virtual void setManufacture(SplineManufacture* prm_pManufacture);

    /**
     * スプライン曲線の補完点を移動する先導開始 .
     */
    virtual void start(SplinTraceOption prm_option, int prm_max_loop = 1);

    /**
     * スプライン曲線の補完点を移動する先導をやめる（注：アクターが停止するわけではない） .
     */
    virtual void stop();

    /**
     * 移動実行メソッド .
     * 移動を行うために、毎フレームこのメソッドを呼び出す必要があります。<BR>
     * start() を行った同一フレームに実行を避けるといったことは不要。<BR>
     * start() を行った最初のbehave()は、『現在の座標→ポイント[0]』への処理となります。<BR>
     * 黒衣(GgafDxCore::GgafDxKuroko)のbehave();より先に実行して下さい。
     */
    virtual void behave();

    /**
     * 黒衣を先導中か否か .
     * @return true:先導中 / false:先導が終了している
     */
    inline bool isLeading() {
        return _is_leading;
    }

    /**
     * 黒衣を先導が終了したか否か。 .
     * @return true:先導が終了している / false:まだ開始していないか、先導中
     */
    inline bool isFinished() {
        if (_was_started) {
            return _is_leading ? false : true;
        } else {
            return false;
        }
    }

    /**
     * スプラインの補完点と補完点の間の距離を取得する。
     * SplineManufacture::adjustAxisRate(double,double,double);<BR>
     * による補正済みの補完点間距離が取得される。<BR>
     * 引数インデックス=0 はstart() を実行後に取得出来るようになる。<BR>
     * <pre>
     *
     *   X:制御点
     *   o:制御点間の補完点（スプライン曲線通過点）
     *
     *        getSegmentDistance(0)
     *            ||
     *            ||    getSegmentDistance(1)   getSegmentDistance(5)   getSegmentDistance(8)
     *            ||         ||                     ||                         ||
     *        <-----------> <--->                <------->                  <------->
     *    自機・・・・・・ X----o----o----o-----X--------o---------o--------o-------X
     *                    始点
     *                    [0]  [1]  [2]  [3]   [4]      [5]       [6]      [7]     [8]
     *
     *  </pre>
     * @param prm_index インデックス（0=アクター現座標→始点間の距離。1=始点→始点+1の補完点間距離・・・）
     * @return そのセグメントの距離
     */
    coord getSegmentDistance(int prm_index);

    /**
     * 現在の座標〜始点[0]〜終点間の距離を取得する。
     * @return 合計距離
     */
    coord getTotalDistance();

    /**
     * スプラインの補完点(基準点も含む)の数を返す。
     * <pre>
     *
     *   X:制御点
     *   o:制御点間の補完点（スプライン曲線通過点）
     *
     *        getSegmentDistance(0)
     *            ||
     *            ||    getSegmentDistance(1)   getSegmentDistance(5)   getSegmentDistance(8)
     *            ||         ||                     ||                         ||
     *        <-----------> <--->                <------->                  <------->
     *    自機・・・・・・ X----o----o----o-----X--------o---------o--------o-------X
     *                    始点
     *                    [0]  [1]  [2]  [3]   [4]      [5]       [6]      [7]     [8]
     *
     * </pre>
     *  上図の場合 補完点インデックスが０〜８の９個なので、戻り値は9となる。
     * @return 補完点(基準点も含む)の数
     */
    int getPointNum();

    /**
     * 補完点の座標を取得する。
     * @param prm_index 補完点インデックス(0〜) <BR>
     *                  開始点インデックス：0 〜 最終点インデックス：getPointNum()-1
     * @param out_x 戻り値X座標
     * @param out_y 戻り値Y座標
     * @param out_z 戻り値Z座標
     */
    virtual void getPointCoord(int prm_index, coord &out_x, coord&out_y, coord &out_z);

    /**
     * スプラインの開始座標を引数の座標に固定（start()時に影響しない）。
     * もし、本メソッドを実行しなかった場合、スプライン開始座標は、<BR>
     * 「スプライン開始座標 ＝ start()時の黒子Aのアクターの座標」となる。<BR>
     * これを避けて、スプライン開始座標を、任意の座標に上書き設定を行う。
     * 想定使用方法は、本メソッド実行で開始座標を設定した後、<BR>
     * 実際の移動するアクターの座標は別の場所に設定して、スプライン移動を開始、<BR>
     * そうするとスプライン曲線軌道に徐々に合流するような効果を演出することができる。<BR>
     * 但し、start()時、スプライン移動繰り返し設定(２週以上)を行った場合、２周目以降には適用されない。<BR>
     * @param prm_x
     * @param prm_y
     * @param prm_z
     */
    void fixStartPosition(coord prm_x, coord prm_y, coord prm_z) {
        _is_fix_start_pos = true;
        _x_start = prm_x;
        _y_start = prm_y;
        _z_start = prm_z;
    }

    /**
     * スプラインの開始座標固定を解除する。
     */
    void unfixStartPosition() {
        _is_fix_start_pos = false;
    }
    virtual ~SplineKurokoLeader();
};

}
#endif /*GGAFLIB_SPLINEKUROKOLEADER_H_*/
