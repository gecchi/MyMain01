#ifndef GGAF_CORE_PROGRESS_H_
#define GGAF_CORE_PROGRESS_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#define PROGRESS_NOTHING (-1)
#define PROGRESS_NULL (-2)

typedef int_fast32_t progress;

namespace GgafCore {

/**
 * 状態遷移進捗管理クラス .
 * 状態遷移を管理する機能を持ったのクラスです。
 * 時間経過に伴い、進捗番号を変更を行うメソッドを提供、
 * また、進捗番号を変更に伴う様々な条件成立のメソッドを提供する。<br>
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class Progress : public Object {

public:
    /** [r]現在進捗番号(-1, 0～) */
    progress _progress;
    /** [r]１単位時間前の進捗番号(-1, 0～) */
    progress _progress_prev;
    /** [r]次の単位時間加算時に反映予定の進捗番号(-1, 0～) */
    progress _progress_next;
    /** [r]各進捗番号の進捗変更時の時間の保存 */
    frame* _pa_frame_of_progress_changed;
    /** [r]時間カウンター(時間経過に伴い増加する何らかの変数)の参照 */
    frame* _p_frame_counter;
    /** 管理される進捗番号の個数 */
    int _num_progress;

public:
    /**
     * コンストラクタ .
     * 初期化時の進捗番号は PROGRESS_NOTHING(-1) に設定されている。<BR>
     * これは、どの進捗状態でも無い事を意味で設定している。<BR>
     * 通常の進捗状態は 0～ とする。<BR>
     * @param prm_p_frame_counter 時間カウンターの参照(何らか経過に伴いインクリメント(+1)されていく変数の参照)
     * @param prm_num_progress 最大進捗番号数(10を設定すると 0番～10番の11個の進捗状態が使用可能となる)
     */
    Progress(frame* prm_p_frame_counter, int prm_num_progress);


    void reset();

    /**
     * 現在の進捗番号取得 .
     * @return 進捗番号(PROGRESS_NOTHING or 0～)
     */
    inline progress get() const {
        return _progress;
    }

    inline int getProgressNum() const {
        return _num_progress;
    }

    /**
     * 現在の進捗を即座に設定する .
     * 即座に反映される。-1 は設定不可。<BR>
     * 初期化などではこの reset(int) を使用し、<BR>
     * 状態変化時は change(int) を使用する。<BR>
     * という設計。<BR>
     * 【注意】<BR>
     * hasJustChanged() は成立しません。<BR>
     * @param prm_progress 進捗番号(0～)
     */
    void reset(progress prm_progress);

    /**
     * 現在の進捗を無し PROGRESS_NOTHING(-1) に設定する .
     * 即座に反映される。
     */
    void setNothing();

    /**
     * 引数の進捗番号へ変更された時の時間を調べる .
     * @param prm_progress 進捗番号(0～)
     * @return 引数の進捗番号へ変更された時(直近)の時間
     */
    frame getFrameWhenChanged(progress prm_progress) const;

    /**
     * 現在の進捗番号内で何フレームなのかを取得(0～) .
     * hasJustChanged() 成立時は 1 が返る。（リセットされる）
     * その後、加算されていく。
     * @return 進捗内経過時間
     */
    inline frame getFrame() const {
        return ((*_p_frame_counter) - _pa_frame_of_progress_changed[_progress+1]);
    }

    /**
     * 現在の進捗番号内でのフレーム数と引数のフレームが同じかを調べる .
     * @param prm_frame
     * @return
     */
    inline bool hasArrivedAt(frame prm_frame) const {
        return prm_frame == ((*_p_frame_counter) - _pa_frame_of_progress_changed[_progress+1]) ? true : false;
    }

    /**
     * 進捗番号を変更 .
     * 但し、直後には反映されず update() 時に反映される。
     * PROGRESS_NOTHING(-1) は設定不可。
     * reset(progress) と使い分けること。
     * @param prm_progress 進捗番号(0～)
     */
    virtual void change(progress prm_progress);

    /**
     * 進捗番号を確率別で変更 .
     * 【記入例】<br>
     * <code>
     * _pProg->changeProbab(
     *              60, PROG_MOVE01,
     *               0, PROG_MOVE02,
     *              20, PROG_MOVE03,
     *               0, PROG_MOVE04,
     *              15, PROG_MOVE05,
     *              10, PROG_MOVE06,
     *               5, PROG_MOVE07
     *         );
     * </code>
     * 【上記の意味】<br>
     * 60% の確率で進捗番号を PROG_MOVE01 に変更、<br>
     *  0% の確率で進捗番号を PROG_MOVE02 に変更、<br>
     * 20% の確率で進捗番号を PROG_MOVE03 に変更、<br>
     *  0% の確率で進捗番号を PROG_MOVE04 に変更、<br>
     * 15% の確率で進捗番号を PROG_MOVE05 に変更、<br>
     * 10% の確率で進捗番号を PROG_MOVE06 に変更、<br>
     *  5% の確率で進捗番号を PROG_MOVE07 に変更、<br>
     * <br>
     * 確率（百分率）部分の合計が必ず 100 になる必要があります。<br>
     * （※内部的に、引数の確率の和が100になるまで、永遠に引数を読み込み続けます。注意して使用して！）<br>
     * @param prm_p1 確率その１
     * @param prm_v1 その確率で変更する進捗番号その１(0～)
     */
    void changeProbab(uint32_t prm_p1, progress prm_v1, ...);

    /**
     * 進捗番号を無し PROGRESS_NOTHING(-1) に変更 .
     * 但し、直後には反映されず update() 時に反映される。
     */
    virtual void changeNothing();

    /**
     * 進捗番号を+1する .
     * 但し、直後には反映されず update() 時に反映される。
     * change(_progress+1) と同じ意味である。
     */
    virtual void changeNext();

    /**
     * 現在の進捗番号内でのフレーム数と引数のフレームが同じならば、進捗番号を+1する .
     * 但し、直後には反映されず update() 時に反映される。
     * @param prm_frame
     */
    inline void changeNextWhenArrivedAt(frame prm_frame) {
        if (hasArrivedAt(prm_frame)) {
            changeNext();
        }
    }

    /**
     * 進捗番号が切り替わった直後なのかどうかを判定。 .
     * change(progress) により進捗番号切り替えた次の update() 時だけ true になります。<BR>
     * reset(progress) により進捗番号切り替えた場合は成立しません。<BR>
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @return true:進捗に切り替わった直後である／false:それ以外
     */
    inline bool hasJustChanged() const {
        if (_progress != _progress_prev && _progress_prev >= PROGRESS_NOTHING) {
            return true;
        } else {
            return false;
        }
    }
    /**
     * 現在の進捗番号がPROGRESS_NOTHINGが否か調べる。 .
     * @return
     */
    inline bool isNothing() const {
        return _progress == PROGRESS_NOTHING ? true : false;
    }

    /**
     * 引数の進捗番号に切り替わった直後なのかどうか調べる。.
     * hasJustChanged() に現在の進捗番号の条件を付加します。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @param prm_progress 現在の進捗番号条件
     * @return true:引数の進捗番号に切り替わった／false:そうではない
     */
    bool hasJustChangedTo(progress prm_progress) const;

    /**
     * 引数の進捗番号から切り替わった直後なのかどうかを調べる。.
     * hasJustChanged() に前回の進捗番号の条件を付加します。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @param prm_progress 前回（切り替わる前）の進捗番号
     * @return true:切り替わった際、前回の進捗番号は引数の進捗番号だった／false:そうではない
     */
    bool hasJustChangedFrom(progress prm_progress) const;

    /**
     * 進捗番号が変化したか（前回と同じかどうか）調べる .
     * 変化した場合、その新しい進捗番号を返す。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * reset(progress) により進捗番号切り替えた場合は成立しません。<BR>
     * @return PROGRESS_NULL(-2) 又は PROGRESS_NOTHING(-1) 又は 進捗番号
     *         PROGRESS_NULL   ：進捗番号が変化していない
     *         PROGRESS_NOTHING：進捗番号が無し PROGRESS_NOTHING(-1) に変化した直後だった。
     *         0～             ：進捗番号が変化した直後であるので、その新しい進捗番号を返す
     */
    progress getProgOnChange() const;

    /**
     * 進捗番号が何から変化したか調べる .
     * 変化した場合、その元の進捗番号を返す。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * reset(progress) により進捗番号切り替えた場合は成立しません。<BR>
     * @return PROGRESS_NULL(-2) 又は PROGRESS_NOTHING(-1) 又は 進捗番号
     *         PROGRESS_NULL   ：進捗番号が変化していない
     *         PROGRESS_NOTHING：進捗番号が無し PROGRESS_NOTHING(-1) から変化した直後だった。
     *         0～             ：進捗番号が変化がした直後であるので、変化前の元の進捗番号返す
     */
    progress getFromProgOnChange() const;

    /**
     * 進捗番号が次フレームに変更される予定ならば、現在の進捗番号を取得する .
     * 同一フレーム内で change(progress) 又は changeNext() を実行済みの場合、取得条件が成立。
     * @return PROGRESS_NULL(-2) 又は PROGRESS_NOTHING(-1) 又は 進捗番号
     *         PROGRESS_NULL   ：次フレームに進捗番号が変更される予定ではない。
     *         PROGRESS_NOTHING：現在進捗が無し PROGRESS_NOTHING(-1) で、次フレームに進捗番号が変更される予定である。
     *         0～             ：次フレームに進捗番号が変更される予定であるので、現在の進捗番号を返す。
     */
    progress getProgWhenProgWillChange() const;

    /**
     * 進捗番号が次フレームに変更される予定ならば、その変更される進捗番号を取得する .
     * 同一フレーム内で change(progress) 又は changeNext() を実行済みの場合、取得条件が成立。
     * @return PROGRESS_NULL(-2) 又は PROGRESS_NOTHING(-1) 又は 進捗番号
     *         PROGRESS_NULL   ：次フレームに進捗番号が変更される予定ではない。
     *         PROGRESS_NOTHING：次フレームに進捗無し PROGRESS_NOTHING(-1) となる予定である。
     *         0～             ：次フレームに進捗番号が変更される予定であるので、その新しい進捗番号を返す。
     */
    progress getToProgWhenProgWillChange() const;

    /**
     * 時間に伴って進捗を更新 .
     * 時間カウンターの増加処理で、この処理をコールしてください。
     */
    virtual void update();

    virtual ~Progress();
};

}
#endif /*GGAF_CORE_PROGRESS_H_*/
