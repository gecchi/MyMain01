#ifndef GGAFPROGRESS_H_
#define GGAFPROGRESS_H_

#define PROGRESS_NOTHING (0)

typedef int progress;

namespace GgafCore {

/**
 * 進捗管理クラス .
 * 時間経過に伴い、進捗番号を変更を行うメソッドを提供、
 * また、進捗番号を変更に伴う様々な条件成立のメソッドを提供する。<br>
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class GgafProgress : public GgafObject {

public:
    /** [r]現在進捗番号(0, 1～) */
    progress _progress;
    /** [r]１単位時間前の進捗番号(0, 1～) */
    progress _progress_prev;
    /** [r]次の単位時間加算時に反映予定の進捗番号(0, 1～) */
    progress _progress_next;
    /** [r]各進捗番号の進捗変更時の時間の保存 */
    frame* _paFrame_progress_changed;
    /** [r]時間カウンター(時間経過に伴い増加する何らかの変数)の参照 */
    frame* _pFrame_count;
    /** 管理される進捗番号の個数 */
    int _num_progress;


    /**
     * コンストラクタ .
     * 初期化時の進捗番号は 0 に設定されている。<BR>
     * これは、どの進捗状態でも無い事を意味で設定している。<BR>
     * 通常の進捗状態は 1～ とする。<BR>
     * @param prm_pFrame_count 時間カウンターの参照(何らか経過に伴いインクリメント(+1)されていく変数の参照)
     * @param prm_num_progress 最大進捗番号数(10を設定すると 0番～10番の11個の進捗状態が使用可能となる)
     */
    GgafProgress(frame* prm_pFrame_count, int prm_num_progress);

    /**
     * 現在の進捗番号取得 .
     * @return 進捗番号(0, 1～)
     */
    virtual progress get();

    /**
     * 現在の進捗を設定する .
     * 即座に反映される。0 は設定不可。<BR>
     * 初期化などではこの set(int) を使用し、<BR>
     * 状態変化時は change(int) を使用する。<BR>
     * という設計。<BR>
     * @param prm_progress 進捗番号(1～)
     */
    virtual void set(progress prm_progress);

    /**
     * 現在の進捗を0(無し)に設定する .
     * 即座に反映される。
     */
    virtual void setNothing();

    /**
     * 引数の進捗番号へ変更された時の時間を調べる .
     * @param prm_progress 進捗番号(1～)
     * @return 引数の進捗番号へ変更された時(直近)の時間
     */
    virtual frame getFrameWhenChanged(progress prm_progress);

    /**
     * 現在の進捗番号内で何フレームなのかを取得(1～) .
     * isJustChanged() 成立時は 1 が返る。（リセットされる）
     * その後、加算されていく。
     * @return 進捗内経過時間
     */
    virtual frame getFrameInProgress();

    /**
     * 進捗番号を変更 .
     * 但し、直後には反映されず update() 時に反映される。
     * 0 は設定不可。
     * set(progress) と使い分けること。
     * @param prm_progress 進捗番号(1～)
     */
    virtual void change(progress prm_progress);

    /**
     * 進捗番号を0(無し)に変更 .
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
     * 進捗番号が切り替わった直後なのかどうかを判定。 .
     * change(progress) により進捗番号切り替えた次の update() 時だけ true になります。<BR>
     * set(progress) により進捗番号切り替えた場合は成立しません。<BR>
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @return true:進捗に切り替わった直後である／false:それ以外
     */
    virtual bool isJustChanged();

    /**
     * 引数の進捗番号に切り替わった直後なのかどうか調べる。.
     * isJustChanged() に現在の進捗番号の条件を付加します。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @param prm_progress 現在の進捗番号条件
     * @return true:引数の進捗番号に切り替わった／false:そうではない
     */
    virtual bool isJustChangedTo(progress prm_progress);

    /**
     * 引数の進捗番号から切り替わった直後なのかどうかを調べる。.
     * isJustChanged() に前回の進捗番号の条件を付加します。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @param prm_progress 前回（切り替わる前）の進捗番号
     * @return true:切り替わった際、前回の進捗番号は引数の進捗番号だった／false:そうではない
     */
    virtual bool isJustChangedFrom(progress prm_progress);

    /**
     * 進捗番号が変化したか（前回と同じかどうか）調べる .
     * 変化した場合、その新しい進捗番号を返す。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @return 0(false) 又は 進捗番号
     *         0(false)：進捗番号が変化していない
     *         0以外   ：進捗番号が変化した直後であるので、その新しい進捗番号を返す
     */
    virtual progress get_WhenJustChanged();

    /**
     * 進捗番号が何から変化したか調べる .
     * 変化した場合、その元の進捗番号を返す。
     * change(progress) 又は changeNext() を実行した次フレームで取得条件が成立。
     * @return 0(false) 又は 進捗番号
     *         0(false)：進捗番号が変化していない
     *         0以外   ：進捗番号が変化がした直後であるので、変化前の元の進捗番号返す
     */
    virtual progress getPrev_WhenJustChanged();

    /**
     * 進捗番号が次フレームに変更される予定ならば、現在の進捗番号を取得する .
     * 同一フレーム内で change(progress) 又は changeNext() を実行済みの場合、取得条件が成立。
     * @return 0(false) 又は 進捗番号
     *         0(false)：次フレームに進捗番号が変更される予定ではない。
     *         0以外   ：次フレームに進捗番号が変更される予定であるので、現在の進捗番号を返す。
     */
    virtual progress get_WhenWillChange();

    /**
     * 進捗番号が次フレームに変更される予定ならば、その変更される進捗番号を取得する .
     * 同一フレーム内で change(progress) 又は changeNext() を実行済みの場合、取得条件が成立。
     * @return 0(false) 又は 進捗番号
     *         0(false)：次フレームに進捗番号が変更される予定ではない。
     *         0以外   ：次フレームに進捗番号が変更される予定であるので、その新しい進捗番号を返す。
     */
    virtual progress getNext_WhenWillChange();

    /**
     * 時間に伴って進捗を更新 .
     * 時間カウンターの増加処理で、この処理をコールしてください。
     */
    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFCURTAIN_H_*/
