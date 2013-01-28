#ifndef SPLINESEQUENCE_H_
#define SPLINESEQUENCE_H_
namespace GgafLib {



/**
 * スプライン曲線移動を実行するためのオブジェクト .
 * 補完点に移動するため、粒度が荒いとカクカクです。
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineSequence : public GgafCore::GgafObject {

public:
    enum SplinTraceOption {
        ABSOLUTE_COORD,     //絶対座標移動
        RELATIVE_COORD,     //スプライン座標の(0,0,0)を、アクターの現座標とし相対座標で計算
        RELATIVE_DIRECTION, //スプライン座標の(0,0,0)を、アクターの現座標とし相対座標とし、アクターの現在向き（_pKurokoA の _angRzMv, _angRyMv)でスプライン座標群をワールド変換。
    };

    /** スプライン情報セット */
    SplineManufacture* _pManufacture;
    /** exec()からの経過フレーム数 */
    frame _execute_frames;
    /** 現在プログラム実行中であるかどうか */
    bool _is_executing;
    /** 座標を操作する対象となるアクター */
    GgafDxCore::GgafDxGeometricActor* _pActor_target;
    /** コンストラクタ内部でSplineLineを生成した場合true/コンストラクタ引数にSplineLineが渡された場合false。一時しのぎいずれ消す。*/
    bool _is_created_pManufacture;
    /**
     * [r]オプション
     * ABSOLUTE_COORD     : 絶対座標移動。
     * RELATIVE_COORD     : 始点を現座標とし、スプライン座標群は相対移動で計算。
     * RELATIVE_DIRECTION : 始点を現座標とし、さらに現在の向き（_pKurokoA の _angRzMv, _angRyMv)でスプライン座標群をワールド変換。
     */
    SplinTraceOption _option;

    /** [r]始点X座標 */
    coord _X_begin;
    /** [r]始点Y座標 */
    coord _Y_begin;
    /** [r]始点Z座標 */
    coord _Z_begin;

    coord _offset_X;
    coord _offset_Y;
    coord _offset_Z;

    int _flip_X;
    int _flip_Y;
    int _flip_Z;
    /** [r]アクターの現在位置からスプライン始点までの距離。exec()時点で更新される。 */
    int _distance_to_begin;
    /** [r]現在処理中の補完点(基準点も含む)の数 */
    int _point_index;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pKurokoA
     */
    SplineSequence(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    /**
     * 各補完点を読み込み時、X軸方向、Y軸方向、Z軸方向それぞれに加算(平行移動)し、補正します .
     * デフォルトは adjustCoordOffset(0, 0, 0) となります。<BR>
     * <b>[注意]</b><BR>
     * 内部で、adjustAxisXFlip() adjustAxisYFlip() adjustAxisZFlip() が考慮され、
     * さらに Manufacture のXYZ方向の補正割合が乗じられた後、一番最後に
     * adjustCoordOffset()  が考慮され差分加算されます。<BR>
     * @param prm_offset_X X軸方向補正増加分
     * @param prm_offset_Y Y軸方向補正増加分
     * @param prm_offset_Z Z軸方向補正増加分
     */
    virtual void adjustCoordOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z);

    /**
     * スプラインの各座標点を、X軸反転します。
     */
    virtual void adjustAxisXFlip() {
        _flip_X = -_flip_X;
    }

    /**
     * スプラインの各座標点を、Y軸反転します。
     */
    virtual void adjustAxisYFlip() {
        _flip_Y = -_flip_Y;
    }

    /**
     * スプラインの各座標点を、Z反転します。
     */
    virtual void adjustAxisZFlip() {
        _flip_Z = -_flip_Z;
    }

    /**
     * 対象アクター(_pActor_target)の座標を、スプラインの一番最初の制御点座標で設定する .
     * exec(SplineSequence::ABSOLUTE_COORD) の場合、つまり「絶対座標移動スプライン」の場合、有効な設定となりうるでしょう。<BR>
     * 「絶対座標移動スプライン」以外あまり意味がありません。<BR>
     */
    void setAbsoluteBeginCoordinate();

    /**
     * 後からスプラインオブジェクトを設定。
     * @param prm_pManufacture
     */
    virtual void setManufacture(SplineManufacture* prm_pManufacture);

    /**
     * スプライン曲線の補完点を移動するプログラムを実行開始
     * @param prm_option オプション 特に意味無し。下位実装拡張用
     */
    virtual void exec(SplinTraceOption prm_option = ABSOLUTE_COORD);

    virtual void stop();
    /**
     * 移動実行メソッド .
     * 移動を行うために、毎フレームこのメソッドを呼び出す必要があります。<BR>
     * exec() を行った同一フレームに実行を避けるといったことは不要。<BR>
     * exec() を行った最初のbehave()は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    virtual void behave();

    /**
     * スプライン移動プログラム実行中か
     * @return true:実行中 / false:実行が終了している
     */
    bool isExecuting() {
        return _is_executing;
    }
    /**
     * スプラインの補完点と補完点の間の距離を取得する。
     * SplineManufacture::adjustAxisRate(double,double,double);<BR>
     * による補正済みの補完点間距離が取得される。<BR>
     * 引数インデックス=0 はexec() を実行後に取得出来るようになる。<BR>
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
     * @return
     */
    coord getSegmentDistance(int prm_index);

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

    virtual ~SplineSequence();
};

}
#endif /*SPLINESEQUENCE_H_*/
