#ifndef GGAF_CORE_CURTAIN_H_
#define GGAF_CORE_CURTAIN_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafCore {

enum CurtainState {
    OPEN,
    OPENING,
    OPENED,
    CLOSE,
    CLOSING,
    CLOSED
};

/**
 * カーテン .
 * カーテンを開く、閉じるの管理します。<BR>
 * <pre>
 *
 *           |             |         <-- カーテンレール止めが刺さっている位置
 *     0     v             v    n
 *     +-----+------+------+----+    <-- カーテンレール
 *           +------+
 *           |  カ  |
 *           |  ｜  |
 *           |  テ  |
 *           |  ン  |
 *           |      |
 *           +------+
 *
 *
 *     <---------- 1 ----------->
 *     <- 2 ->
 *     <------- 3 --------->
 *     <---- 4 ----->
 *           <----- 5 ----->
 *
 *  1. _curtain_rail_length （カーテンレール全体の長さ）
 *  2. _min_position  (カーテンが100% 開いたと判定される位置）
 *  3. _max_position  (カーテンが100% 閉じた判定される位置）
 *  4. _curtain_position （現在のカーテン位置）
 *  5. _moveable_length   (カーテン可動範囲(長さ) = 3 - 2 )
 * </pre>
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
template<class T>
class Curtain : public Object {

public:
    /** [r]現在のカーテンの状態 */
    CurtainState _state;
    /** [r]カーテンレールの長さ */
    const T _curtain_rail_length;
    /** [r]カーテンが100% 開いたと判定される位置 */
    const T _min_position;
    /** [r]カーテンが100% 閉じた判定される位置 */
    const T _max_position;
    /** [r]カーテン可動範囲(長さ) */
    const T _moveable_length;
    /** [r]現在のカーテンの閉まっている長さ */
    T _curtain_position;
    /** [r]カーテンを開く際の速度 */
    T _opening_velocity;
    /** [r]カーテンを閉める際の速度 */
    T _closing_velocity;

public:
    /**
     * コンストラクタ .
     * @param prm_curtain_rail_length カーテンレールの長さ
     * @param prm_min_position カーテンが100% 開いたと判定される位置
     * @param prm_max_position カーテンが100% 閉じた判定される位置
     */
    Curtain(T prm_curtain_rail_length,
            T prm_min_position,
            T prm_max_position) : Object(),
    _curtain_rail_length(prm_curtain_rail_length),
    _min_position(prm_min_position),
    _max_position(prm_max_position),
    _moveable_length(_max_position - _min_position)
    {
        _curtain_position = _min_position; //最初は100%開いています
        _state = OPENED;
        _opening_velocity = 0.0f;
        _closing_velocity = 0.0f;
    }

    /**
     * カーテンを徐々に開ける .
     * 本メソッドを実行すると、behave() が呼び出されるごとに
     * prm_opening_velocity づつカーテンが開きます（長さが短くなります）。
     * カーテンのは長さの 0.0 まです。長さ 0.0  に達すると、processCloseDone() を
     * コールバックし open は終了します。
     * @param prm_opening_velocity カーテンを開ける速度
     */
    virtual void openV(T prm_opening_velocity) {
        _opening_velocity = prm_opening_velocity;
        _state = OPEN;
    }
    virtual void openT(frame prm_opening_frames) {
        T length = _curtain_position - _min_position;
        openV((T)(length / prm_opening_frames));
    }

    /**
     * カーテンを即座に最大に開ける .
     * 本メソッドを実行すると カーテンレールの長さは 0.0 になります。
     * processOpenDone() を１回コールバックします。
     */
    virtual void open() {
        _curtain_position = _min_position;
        _state = OPENED;
        processOpenDone();
    }

    /**
     * カーテンを徐々に閉める .
     * 本メソッドを実行すると、behave() が呼び出されるごとに
     * prm_closing_velocity づつカーテンがを閉じてゆきます（長さが長くなります）。<BR>
     * カーテンレールの長さの最大はデフォルトで 1.0 です。
     * デフォルトでは長さ 1.0 に達すると、processCloseDone() を１回
     * コールバックし、close は終了します。
     * @param prm_closing_velocity カーテンを閉める速度
     */
    virtual void closeV(T prm_closing_velocity) {
        _closing_velocity = prm_closing_velocity;
        _state = CLOSE;
    }
    virtual void closeT(frame prm_closing_frames) {
        T length = _moveable_length - (_curtain_position - _min_position);
        closeV((T)(length / prm_closing_frames));
    }

    /**
     * カーテンを即座に閉めきる .
     * 本メソッドを実行すると カーテンレールの長さは 1.0 になります。
     * processOpenDone() を１回コールバックします。
     */
    virtual void close() {
        _curtain_position = _max_position;
        _state = CLOSED;
        processCloseDone();
    }

    /**
     * カーテンを動かす .
     * 本クラスを機能させるにには、毎フレームこのメソッドを実行してください。
     * 毎フレーム behave() することで次のメソッドが適宜呼び出されるようになります。
     * <code>
     * processOpenBegin()
     * processOpening()
     * processOpenDone()
     * processCloseBegin()
     * processClosing()
     * processCloseDone()
     * </code>
     */
    virtual void behave() {
        if (_state == OPEN) {
            processOpenBegin();
            _state = OPENING;
        } else if (_state == OPENING) {
            _curtain_position -= _opening_velocity;
            if (_curtain_position < _min_position) {
                _curtain_position = _min_position;
                _state = OPENED;
                processOpenDone();
            } else {
                processOpening();
            }

        } else if (_state == CLOSE) {
            processCloseBegin();
            _state = CLOSING;
        } else if (_state == CLOSING) {
            _curtain_position += _closing_velocity;
            if (_curtain_position > _max_position) {
                _curtain_position = _max_position;
                _state = CLOSED;
                processCloseDone();
            } else {
                processClosing();
            }
        }
    }

    /**
     * カーテンの位置（閉まってい部分）を取得 .
     * @return カーテンの位置
     */
    virtual T getCurtainPosition() {
        return _curtain_position;
    }

    /**
     * カーテンの閉まっている割合を取得 .
     * @return カーテンの閉まっている割合(0.0：100%開いている ～ 1.0：100%閉まっている）
     */
    virtual T getClosingRatio() {
        return (_curtain_position - _min_position) / _moveable_length;
    }

    /**
     * カーテンが開き始める瞬間の処理 .
     * open() 時に１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpenBegin() {};

    /**
     * カーテンが開いていく途中の処理 .
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpening() {};

    /**
     * カーテンが開ききった時の処理 .
     * _curtain_position が 0.0 になった際１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processOpenDone() {};

    /**
     * カーテンが閉まり始める瞬間の処理 .
     * close() 時に１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processCloseBegin() {};

    /**
     * カーテンが閉まっていく途中の処理 .
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processClosing() {};

    /**
     * カーテンが閉まった時の処理 .
     * _curtain_position が _curtain_rail_length になった際１度だけ呼び出されます。 <BR>
     * 下位で実際の処理を実装してください。<BR>
     */
    virtual void processCloseDone() {};

    virtual ~Curtain() {

    }
};

}
#endif /*GGAF_CORE_CURTAIN_H_*/
