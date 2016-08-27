#ifndef GGAFLIB_SPLINEKUROKOLEADER_H_
#define GGAFLIB_SPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafLib {

enum SplinTraceOption {
    ABSOLUTE_COORD,     //絶対座標移動
    RELATIVE_COORD,     //スプライン座標の(0,0,0)を、アクターの現座標とし相対座標で計算
    RELATIVE_COORD_DIRECTION, //スプライン座標の(0,0,0)を、アクターの現座標とし相対座標とし、アクターの現在の向き（_rx > _rz > _ry)でスプライン座標群をワールド変換。
};

/**
 * スプライン曲線移動を実行するためのオブジェクト .
 * 黒衣に指示を出して移動を先導します。
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineKurokoLeader : public GgafCore::GgafObject {

public:
    /** スプライン情報セット */
    SplineManufacture* _pManufacture;
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
     * RELATIVE_COORD_DIRECTION : 始点を現座標とし、さらに現在の向き（_pKuroko の _rz_mv, _ry_mv)でスプライン座標群をワールド変換。
     */
    SplinTraceOption _option;
    /** [r] ループカウンタ */
    int _cnt_loop;
    /** [r] 設定ループ数。-1 で無限 */
    int _max_loop;

    /** [r]そのループでの始点X座標 */
    coord _x_start_in_loop;
    /** [r]そのループでの始点Y座標 */
    coord _y_start_in_loop;
    /** [r]そのループでの始点Z座標 */
    coord _z_start_in_loop;

    coord _offset_x;
    coord _offset_y;
    coord _offset_z;

    int _flip_x;
    int _flip_y;
    int _flip_z;
    /** [r]アクターの現在位置からスプライン始点までの距離。start()時点で更新される。 */
    int _distance_to_begin;
    /** [r]始点座標を固定する。（固定しない場合は黒子Aのアクターの座標になる） */
    bool _is_fix_start_pos;

    bool _is_fix_start_ang;
    bool _is_loop_ang_by_face;
    angle _ang_rx_mv_start;
    angle _rz_mv_start;
    angle _ry_mv_start;

//    bool _is_linked_start_pos;
//    bool _is_linked_start_ang;

    float _sinRx_begin;
    float _cosRx_begin;
    float _sinRz_begin;
    float _cosRz_begin;
    float _sinRy_begin;
    float _cosRy_begin;


    coord _actor_prev_x;
    coord _actor_prev_y;
    coord _actor_prev_z;
    coord _actor_prev_rx;
    coord _actor_prev_rz;
    coord _actor_prev_ry;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pKuroko
     */
    SplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* prm_pKuroko);

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
     * start(ABSOLUTE_COORD) の場合、つまり「絶対座標移動スプライン」の場合、
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
     * @param prm_option ABSOLUTE_COORD     絶対座標移動
     *                   RELATIVE_COORD     スプライン座標の(0,0,0)を、対象黒衣のアクターの現座標とし、相対座標で計算
     *                   RELATIVE_COORD_DIRECTION スプライン座標の(0,0,0)を、対象黒衣のアクターの現座標とし、相対座標で計算。その後、現在の向き（_rx > _rz > _ry)でスプライン座標群をワールド変換。
     * @param prm_max_loop 繰り返し回数、省略時は１ループ。
     */
    virtual void start(SplinTraceOption prm_option, int prm_max_loop = 1);

    virtual void restart();

    /**
     * スプライン曲線の補完点を移動する先導をやめる（注：アクターが停止するわけではない） .
     */
    virtual void stop();

    /**
     * 移動実行メソッド .
     * 移動を行うために、黒衣の状態を更新します。
     * start() を行った同一フレームに実行を避けるといったことは不要。<BR>
     * start() を行った最初のbehave()は、現在の座標～ポイント[0] が離れていればその移動処理、
     * もし、現在の座標とポイント[0]が重なっていれば、現在の座標～ポイント[1]への移動処理となります。<BR>
     * 黒衣(GgafDxCore::GgafDxKuroko)のbehave();より先に実行して下さい。
     */
    virtual void behave() = 0;

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
     * 現在の座標～始点[0]～終点間の距離を取得する。
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
     *  上図の場合 補完点インデックスが０～８の９個なので、戻り値は9となる。
     * @return 補完点(基準点も含む)の数
     */
    int getPointNum();

    /**
     * 補完点の座標を取得する。
     * @param prm_index 補完点インデックス(0～) <BR>
     *                  開始点インデックス：0 ～ 最終点インデックス：getPointNum()-1
     * @param out_x 戻り値X座標
     * @param out_y 戻り値Y座標
     * @param out_z 戻り値Z座標
     */
    virtual void getPointCoord(int prm_index, coord& out_x, coord& out_y, coord& out_z);

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
        _x_start_in_loop = prm_x;
        _y_start_in_loop = prm_y;
        _z_start_in_loop = prm_z;
    }

    /**
     * スプラインの開始移動方向を固定（start()時に影響しない）。
     * もし、本メソッドを実行しなかった場合、スプライン開始時のスプライン方向は、<BR>
     * 「スプライン開始方向 ＝ start()時の対象アクターの黒子Aの向きの方向(_rz, _ry）となる。<BR>
     * これを避けて、スプライン開始時、任意のスプライン方向に上書き設定を行う。<BR>
     * 但し、start()時、スプライン移動繰り返し設定(２週以上)を行った場合、２周目以降には適用されない。<BR>
     * ※スプライン方向の設定は、RELATIVE_COORD_DIRECTION の場合のみ意味がある。
     * 注意：rx > rz > ry の引数順！
     * @param prm_rx
     * @param prm_rz
     * @param prm_ry
     */
    void fixStartAngle(angle prm_rx, angle prm_rz, angle prm_ry);

    /**
     * スプラインの開始座標固定を解除する。
     */
    void unfixStartPosition() {
        _is_fix_start_pos = false;
    }

    void unfixStartAngle() {
        _is_fix_start_ang = false;
    }
    /**
     * スプライン移動の開始方向を、自分が向いている方向に対して開始する (デフォルト).
     * start()時の対象アクターの向きの方向(_rz, _ry)に座標変換されて、スプラインの軌跡が構築される。
     */
    void setLoopAngleByFaceAng() {
        _is_loop_ang_by_face = true;
    }

    /**
     * スプライン移動の開始方向を、自分が移動している方向に対して開始する .
     * start()時の対象アクター黒子Aの移動方向(getKuroko()->_rz_mv, getKuroko()->_ry_mv）
     * に座標変換されて、スプラインの軌跡が構築される。
     */
    void setLoopAngleByMvAng() {
        _is_loop_ang_by_face = false;
    }



//    void linkedStartPosition() {
//        unfixStartPosition();
//        _is_linked_start_pos = true;
//    }
//
//    void unlinkedStartPosition() {
//        _is_linked_start_pos = false;
//    }
//
//    void linkedStartAngle() {
//        unfixStartAngle();
//        _is_linked_start_ang = true;
//    }
//
//    void unlinkedStartAngle() {
//        _is_linked_start_ang = false;
//    }

    virtual ~SplineKurokoLeader();
};

}
#endif /*GGAFLIB_SPLINEKUROKOLEADER_H_*/
