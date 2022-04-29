#ifndef GGAF_CORE_PHASE_H_
#define GGAF_CORE_PHASE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#ifdef _MSC_VER
    #if _MSC_VER < 1600
        #include <map>
        #define unordered_map map
    #else
        #include <unordered_map>
    #endif
#else
        #include <unordered_map>
#endif

#define GGAF_PHASE_NOTHING (-1)
#define GGAF_PHASE_NULL (-2)

typedef int_fast32_t phase;

namespace GgafCore {

/**
 * フェーズ進捗管理クラス .
 * フェーズを管理する機能を持ったのクラスです。
 * 時間経過に伴い、フェーズ番号を変更を行うメソッドを提供、
 * また、フェーズ番号を変更に伴う様々な条件成立のメソッドを提供する。<br>
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class Phase : public Object {

public:
    /** [r]現在フェーズ番号(-1, 0～) */
    phase _phase;
    /** [r]１単位時間前のフェーズ番号(-1, 0～) */
    phase _phase_prev;
    /** [r]次の単位時間加算時に反映予定のフェーズ番号(-1, 0～) */
    phase _phase_next;
    /** [r]各フェーズ番号の進捗変更時の時間の保存 */
    std::unordered_map<phase, frame> _map_changed_frame;
    /** [r]時間カウンター(時間経過に伴い増加する何らかの変数)の参照 */
    frame* _p_frame_counter;

public:
    /**
     * コンストラクタ .
     * 初期化時のフェーズ番号は GGAF_PHASE_NOTHING(-1) に設定されている。<BR>
     * これは、どの進捗状態でも無い事を意味で設定している。<BR>
     * 通常の進捗状態は 0～ とする。<BR>
     * @param prm_p_frame_counter 時間カウンターの参照(何らか経過に伴いインクリメント(+1)されていく変数の参照)
     */
    Phase(frame* prm_p_frame_counter);

    void reset();

    /**
     * 現在のフェーズ番号取得 .
     * @return フェーズ番号(GGAF_PHASE_NOTHING or 0～)
     */
    inline phase get() const {
        return _phase;
    }

    /**
     * 現在の進捗を即座に設定する .
     * 即座に反映される。-1 は設定不可。<BR>
     * 初期化などではこの reset(int) を使用し、<BR>
     * 状態変化時は change(int) を使用する。<BR>
     * という設計。<BR>
     * 【注意】<BR>
     * hasJustChanged() は成立しません。<BR>
     * @param prm_phase フェーズ番号(0～)
     */
    void reset(phase prm_phase);

    /**
     * 現在の進捗を無し GGAF_PHASE_NOTHING(-1) に設定する .
     * 即座に反映される。
     */
    void setNothing();

    /**
     * 引数のフェーズ番号へ変更された時の時間を調べる .
     * @param prm_phase フェーズ番号(0～)
     * @return 引数のフェーズ番号へ変更された時(直近)の時間
     */
    frame getFrameWhenChanged(phase prm_phase);

    /**
     * 現在のフェーズ番号内で何フレームなのかを取得(0～) .
     * hasJustChanged() 成立時は 1 が返る。（リセットされる）
     * その後、加算されていく。
     * @return 進捗内経過時間
     */
    inline frame getFrame() const {
        std::unordered_map<phase, frame>::const_iterator i = _map_changed_frame.find(_phase);
        return ((*_p_frame_counter) - (i->second));
    }

    /**
     * 現在のフェーズ番号内でのフレーム数と引数のフレームが同じかを調べる .
     * @param prm_frame
     * @return
     */
    inline bool hasArrivedFrameAt(frame prm_frame) const {
        std::unordered_map<phase, frame>::const_iterator i = _map_changed_frame.find(_phase);
        return prm_frame == ((*_p_frame_counter) - (i->second)) ? true : false;
    }

    /**
     * フェーズ番号を変更 .
     * 但し、直後には反映されず update() 時に反映される。
     * GGAF_PHASE_NOTHING(-1) は設定不可。
     * reset(phase) と使い分けること。
     * @param prm_phase フェーズ番号(0～)
     */
    virtual void change(phase prm_phase);

    /**
     * フェーズ番号を確率別で変更 .
     * 【記入例】<br>
     * <code>
     * _pPhase->changeProbab(
     *              60, PHASE_MOVE01,
     *               0, PHASE_MOVE02,
     *              20, PHASE_MOVE03,
     *               0, PHASE_MOVE04,
     *              15, PHASE_MOVE05,
     *              10, PHASE_MOVE06,
     *               5, PHASE_MOVE07
     *         );
     * </code>
     * 【上記の意味】<br>
     * 60% の確率でフェーズ番号を PHASE_MOVE01 に変更、<br>
     *  0% の確率でフェーズ番号を PHASE_MOVE02 に変更、<br>
     * 20% の確率でフェーズ番号を PHASE_MOVE03 に変更、<br>
     *  0% の確率でフェーズ番号を PHASE_MOVE04 に変更、<br>
     * 15% の確率でフェーズ番号を PHASE_MOVE05 に変更、<br>
     * 10% の確率でフェーズ番号を PHASE_MOVE06 に変更、<br>
     *  5% の確率でフェーズ番号を PHASE_MOVE07 に変更、<br>
     * <br>
     * 確率（百分率）部分の合計が必ず 100 になる必要があります。<br>
     * （※内部的に、引数の確率の和が100になるまで、永遠に引数を読み込み続けます。注意して使用して！）<br>
     * @param prm_p1 確率その１
     * @param prm_v1 その確率で変更するフェーズ番号その１(0～)
     */
    void changeProbab(uint32_t prm_p1, phase prm_v1, ...);

    /**
     * フェーズ番号を無し GGAF_PHASE_NOTHING(-1) に変更 .
     * 但し、直後には反映されず update() 時に反映される。
     */
    virtual void changeNothing();

    /**
     * フェーズ番号を+1する .
     * 但し、直後には反映されず update() 時に反映される。
     * change(_phase+1) と同じ意味である。
     */
    virtual void changeNext();

    /**
     * 現在のフェーズ番号内でのフレーム数と引数のフレームが同じならば、フェーズ番号を+1する .
     * 但し、直後には反映されず update() 時に反映される。
     * @param prm_frame
     */
    inline void changeNextWhenArrivedFrameAt(frame prm_frame) {
        if (hasArrivedFrameAt(prm_frame)) {
            changeNext();
        }
    }

    /**
     * フェーズ番号が切り替わった直後なのかどうかを判定。 .
     * change(phase) によりフェーズ番号切り替えた次の update() 時だけ true になります。<BR>
     * reset(phase) によりフェーズ番号切り替えた場合は成立しません。<BR>
     * change(phase) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @return true:進捗に切り替わった直後である／false:それ以外
     */
    inline bool hasJustChanged() const {
        if (_phase != _phase_prev && _phase_prev >= GGAF_PHASE_NOTHING) {
            return true;
        } else {
            return false;
        }
    }
    /**
     * 現在のフェーズ番号がGGAF_PHASE_NOTHINGが否か調べる。 .
     * @return
     */
    inline bool isNothing() const {
        return _phase == GGAF_PHASE_NOTHING ? true : false;
    }

    /**
     * 引数のフェーズ番号に切り替わった直後なのかどうか調べる。.
     * hasJustChanged() に現在のフェーズ番号の条件を付加します。
     * change(phase) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @param prm_phase 現在のフェーズ番号条件
     * @return true:引数のフェーズ番号に切り替わった／false:そうではない
     */
    bool hasJustChangedTo(phase prm_phase) const;

    /**
     * 引数のフェーズ番号から切り替わった直後なのかどうかを調べる。.
     * hasJustChanged() に前回のフェーズ番号の条件を付加します。
     * change(phase) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @param prm_phase 前回（切り替わる前）のフェーズ番号
     * @return true:切り替わった際、前回のフェーズ番号は引数のフェーズ番号だった／false:そうではない
     */
    bool hasJustChangedFrom(phase prm_phase) const;

    /**
     * フェーズ番号が変化したか（前回と同じかどうか）調べる .
     * 変化した場合、その新しいフェーズ番号を返す。
     * change(phase) 又は changeNext() を実行した次フレームで取得条件が成立。
     * reset(phase) によりフェーズ番号切り替えた場合は成立しません。<BR>
     * @return GGAF_PHASE_NULL(-2) 又は GGAF_PHASE_NOTHING(-1) 又は フェーズ番号
     *         GGAF_PHASE_NULL   ：フェーズ番号が変化していない
     *         GGAF_PHASE_NOTHING：フェーズ番号が無し GGAF_PHASE_NOTHING(-1) に変化した直後だった。
     *         0～               ：フェーズ番号が変化した直後であるので、その新しいフェーズ番号を返す
     */
    phase getPhaseOnChange() const;

    /**
     * フェーズ番号が何から変化したか調べる .
     * 変化した場合、その元のフェーズ番号を返す。
     * change(phase) 又は changeNext() を実行した次フレームで取得条件が成立。
     * reset(phase) によりフェーズ番号切り替えた場合は成立しません。<BR>
     * @return GGAF_PHASE_NULL(-2) 又は GGAF_PHASE_NOTHING(-1) 又は フェーズ番号
     *         GGAF_PHASE_NULL   ：フェーズ番号が変化していない
     *         GGAF_PHASE_NOTHING：フェーズ番号が無し GGAF_PHASE_NOTHING(-1) から変化した直後だった。
     *         0～               ：フェーズ番号が変化がした直後であるので、変化前の元のフェーズ番号返す
     */
    phase getFromPhaseOnChange() const;

    /**
     * フェーズ番号が次フレームに変更される予定ならば、現在のフェーズ番号を取得する .
     * 同一フレーム内で change(phase) 又は changeNext() を実行済みの場合、取得条件が成立。
     * @return GGAF_PHASE_NULL(-2) 又は GGAF_PHASE_NOTHING(-1) 又は フェーズ番号
     *         GGAF_PHASE_NULL   ：次フレームにフェーズ番号が変更される予定ではない。
     *         GGAF_PHASE_NOTHING：現在進捗が無し GGAF_PHASE_NOTHING(-1) で、次フレームにフェーズ番号が変更される予定である。
     *         0～               ：次フレームにフェーズ番号が変更される予定であるので、現在のフェーズ番号を返す。
     */
    phase getPhaseWhenPhaseWillChange() const;

    /**
     * フェーズ番号が次フレームに変更される予定ならば、その変更されるフェーズ番号を取得する .
     * 同一フレーム内で change(phase) 又は changeNext() を実行済みの場合、取得条件が成立。
     * @return GGAF_PHASE_NULL(-2) 又は GGAF_PHASE_NOTHING(-1) 又は フェーズ番号
     *         GGAF_PHASE_NULL   ：次フレームにフェーズ番号が変更される予定ではない。
     *         GGAF_PHASE_NOTHING：次フレームに進捗無し GGAF_PHASE_NOTHING(-1) となる予定である。
     *         0～             ：次フレームにフェーズ番号が変更される予定であるので、その新しいフェーズ番号を返す。
     */
    phase getToPhaseWhenPhaseWillChange() const;

    /**
     * 時間に伴って進捗を更新 .
     * 時間カウンターの増加処理で、この処理をコールしてください。
     */
    virtual void update();

    virtual ~Phase();
};

}
#endif /*GGAF_CORE_PHASE_H_*/
