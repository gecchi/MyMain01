#ifndef SPLINESEQUENCE_H_
#define SPLINESEQUENCE_H_
namespace GgafDx9LibStg {

enum SplinTraceOption {
    ABSOLUTE_COORD,
    RELATIVE_COORD,
    RELATIVE_DIRECTION,
};

/**
 * スプライン曲線移動を実行するためのオブジェクト .
 * 補完点に移動するため、粒度が荒いとカクカクです。
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineSequence : public GgafCore::GgafObject {

public:
    /** スプライン情報セット */
    SplineManufacture* _pManufacture;
    /** exec()からの経過フレーム数 */
    frame _execute_frames;
    /** 現在プログラム実行中であるかどうか */
    bool _is_executing;
    /** 座標を操作する対象となるアクター */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_target;
    /** コンストラクタ内部でSpline3Dを生成した場合true/コンストラクタ引数にSpline3Dが渡された場合、false */
//    bool _is_create_pManufacture;
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

    SplineSequence(SplineManufacture* prm_pManufacture,  GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA);

    /**
     * 各補完点を読み込み時、X軸方向、Y軸方向、Z軸方向それぞれに加算(平行移動)し、補正します .
     * デフォルトは adjustCoodOffset(0, 0, 0) となります。<BR>
     * <b>[注意]</b><BR>
     * 内部で、adjustAxisXFlip() adjustAxisYFlip() adjustAxisZFlip() が考慮され後に
     * adjustCoodOffset()  が考慮されますます。<BR>
     * @param prm_offset_X X軸方向補正増加分
     * @param prm_offset_Y Y軸方向補正増加分
     * @param prm_offset_Z Z軸方向補正増加分
     */
    virtual void adjustCoodOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z);

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
     * 対象アクター(_pActor_target)の座標を、スプラインの一番最初の基点座標で設定する .
     * exec(ABSOLUTE_COORD) の場合、つまり「絶対座標移動スプライン」の場合、有効な設定となりうるでしょう。<BR>
     * 「絶対座標移動スプライン」あまり意味がありません。<BR>
     */
    void setAbsoluteBeginCoordinate();

    /**
     * 後からスプラインオブジェクトを設定。
     * @param prm_sp
     */
    virtual void setManufacture(SplineManufacture* prm_pManufacture);

    /**
     * スプライン曲線の補完点を移動するプログラムを実行開始
     * @param prm_option オプション 特に意味無し。下位実装拡張用
     */
    virtual void exec(SplinTraceOption prm_option = ABSOLUTE_COORD);

    /**
     * 移動実行メソッド .
     * 移動を行うために、毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave();

    /**
     * スプライン移動プログラム実行中か
     * @return true:実行中 / false:実行が終了している
     */
    bool isExecuting() {
        return _is_executing;
    }

    virtual ~SplineSequence();
};

}
#endif /*SPLINESEQUENCE_H_*/
