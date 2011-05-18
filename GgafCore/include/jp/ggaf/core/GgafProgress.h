#ifndef GGAFPROGRESS_H_
#define GGAFPROGRESS_H_


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
    /** [r]現在進捗番号(1～99) */
    int _progress;
    /** [r]１単位時間前の進捗番号(1～99) */
    int _progress_prev;
    /** [r]次の単位時間加算時に反映予定の進捗番号(1～99) */
    int _progress_next;
    /** [r]各進捗番号の進捗変更時の時間の保存 */
    frame* _paFrame_ProgressChanged;
    /** [r]時間カウンター(時間経過に伴い増加する何らかの変数)の参照 */
    frame* _pFrame_count;
    /** 管理される進捗番号の個数 */
    int _num_progress;

    /**
     * コンストラクタ .
     * 初期化時の進捗番号は -1 に設定されている。<BR>
     * これは、生成直後進捗番号はどの番号でも無いという意味で設定している。<BR>
     * 本当は進捗番号の初期値を 0 としたいところだったが、0 という値はすでに進捗を表しているような気がするため避けた。<BR>
     * 生成直後、set(0) により初期進捗番号を初期化する場合は、特に考慮は不要。<BR>
     * しかし、set(0) を行わず、いきなり change(0) を行った際、進捗番号が 0 番でも isJustChanged() が成立する効果がある。<BR>
     * 初回進捗番号設定時にブレイク判定を行うかどうかで、考慮されたし。<BR>
     * @param prm_pFrame_count 時間カウンターの参照(何らか経過に伴いインクリメント(+1)されていく変数の参照)
     * @param prm_num_progress 最大進捗番号数
     */
    GgafProgress(frame* prm_pFrame_count, int prm_num_progress);

    /**
     * 現在の進捗番号取得 .
     * @return 進捗番号(1～99)
     */
    virtual int get();

    /**
     * 現在の進捗を設定する .
     * 即座に反映される。<BR>
     * 初期化などではこの set(int) を使用し、<BR>
     * 状態変化時は change(int) を使用する。<BR>
     * という設計。<BR>
     * @param prm_progress 進捗番号(1～99)
     */
    virtual void set(int prm_progress);

    /**
     * 引数の進捗番号へ変更された時の時間を調べる .
     * @param prm_progress 進捗番号(1～99)
     * @return 引数の進捗番号へ変更された時(直近)の時間
     */
    virtual frame getFrameWhenChanged(int prm_progress);

    /**
     * 現在の進捗番号内での経過時間を取得 .
     * @return 進捗内経過時間
     */
    virtual frame getFrameInProgress();

    /**
     * 進捗番号を変更 .
     * 但し、直後には反映されず update() 時に反映される。
     * set(int) と使い分けること。
     * @param prm_progress 進捗番号(1～99)
     */
    virtual void change(int prm_progress);

    /**
     * 進捗番号を+1する .
     * 1～99 の範囲となるように注意すること。
     * 但し、直後には反映されず update() 時に反映される。
     * change(_progress+1) と同じ意味である。
     */
    virtual void changeNext();

    /**
     * 進捗番号が切り替わった直後なのかどうかを判定。 .
     * change(int) により進捗番号切り替えた次の update() 時だけ true になります。<BR>
     * set(int) により進捗番号切り替えた場合は成立しません。<BR>
     * @return true:進捗に切り替わった直後である／false:それ以外
     */
    virtual bool isJustChanged();

    /**
     * 引数の進捗番号に切り替わった直後なのかどうか調べる。.
     * isJustChanged() に現在の進捗番号の条件を付加します。
     * @param prm_progress 現在の進捗番号条件
     * @return true:引数の進捗番号に切り替わった／false:そうではない
     */
    virtual bool isJustChangedTo(int prm_progress);

    /**
     * 引数の進捗番号から切り替わった直後なのかどうかを調べる。.
     * isJustChanged() に前回の進捗番号の条件を付加します。
     * @param prm_progress 前回（切り替わる前）の進捗番号
     * @return true:切り替わった際、前回の進捗番号は引数の進捗番号だった／false:そうではない
     */
    virtual bool isJustChangedFrom(int prm_progress);

    /**
     * 進捗番号が変化したか（前回と同じかどうか）調べる .
     * 変化した場合、その新しい進捗番号を返す。
     * @return 0 又は 進捗番号
     *         0    ：変化していない
     *         0以外：変化が有りで、その新しい進捗番号
     */
    virtual int getChangedTo();

    /**
     * 進捗番号が何から変化したか調べる .
     * 変化した場合、その元の進捗番号を返す。
     * @return 0 又は 進捗番号
     *         0    ：変化していない
     *         0以外：変化が有りで、変化前の元の進捗番号
     */
    virtual int getChangeFrom();

    /**
     * 時間に伴って進捗を更新 .
     * 時間カウンターの増加処理で、この処理をコールしてください。
     */
    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFCURTAIN_H_*/
