#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNodeに、タスクシステム及び様々な状態管理（フラグ管理）を追加。 .
 * 毎フレーム、を神(GgafGod)は世界(GgafWorld)に、次のメソッド順で呼び出す仕組みになっている。世界(GgafWorld)も本templateを実装している。<BR>
 * nextFrame() > behave() > judge() > [drawPrior() > drawMain() > drawTerminate()] > finally() <BR>
 * 上記の内、nextFrame()、finally() は毎フレーム実行される。<BR>
 * behave()、judge() は活動状態フラグ(_is_active_flg)が true、かつ、一時停止フラグ(_was_paused_flg)が false の場合実行される。<BR>
 * drawPrior()、drawMain()、drawTerminate() は、次フレームまでの残時間に余裕があり、かつ一時非表示フラグ(_was_hidden_flg) が false の場合<BR>
 * 実行される。次フレームまでの残時間に余裕が無い場合、神はこの３メソッドをスキップするが、MAX_SKIP_FRAME フレームに１回は実行する。<BR>
 * 上記の nextFrame() ～ finally() のオーバーライドは非推奨。オーバーライド用に純粋仮想(processXxxxxx()) を用意している。<BR>
 * initialize() は、上記の nextFrame() ～ finally() を何れかを呼び出す前にインスタンスごとに１回だけ呼ばれる仕組みになっている。<BR>
 * 但し、生存フラグ(_can_live_flg)がfalseの場合（deleteされる）は、nextFrame() ～ finally() は全て実行されない。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

private:

protected:
    /** 神への近道 */
    GgafGod* _pGod;
    /** initializeが行われたどうかのフラグ(true=行われた) */
    bool _was_initialize_flg;

    /** 余命 */
    DWORD _dwGodFrame_when_goodbye;
    /** ノードが誕生(addSubされた）時からのフレーム */
    DWORD _lifeframe;
    /** 相対フレーム計算用 */
    DWORD _frame_relative;
    /** ノード活動フラグ */
    bool _is_active_flg;
    /** 一時停止フラグ */
    bool _was_paused_flg;
    /** 一時非表示フラグ */
    bool _was_hidden_flg;
    /** ノード生存フラグ */
    bool _can_live_flg;

    /** 次フレームノード活動予約フラグ、次フレームのフレーム加算時 _is_active_flg に反映される */
    bool _will_activate_at_next_frame_flg;
    /** 次フレーム一時停止予約フラグ、次フレームのフレーム加算時 _was_paused_flg に反映される */
    bool _wil_pause_at_next_frame_flg;
    /** 次フレーム一時非表示予約フラグ、次フレームのフレーム加算時 _was_hidden_flg に反映される  */
    bool _will_hidden_at_next_frame_flg;
    /** 次フレーム生存予約フラグ、次フレームのフレーム加算時 _can_live_flg に設定される */
    bool _will_be_alive_at_next_frame_flg;

    /** 先頭ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが先頭ノードに移動する */
    bool _will_move_first_at_next_frame_flg;
    /** 末尾ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが末尾ノードに移動する */
    bool _will_move_last_at_next_frame_flg;

    /** あとで活動予約フラグ */
    bool _will_activate_after_a_few_frames_flg;
    /** あとで活動までの残フレーム数（神フレームと一致したら活動） */
    DWORD _frame_of_activation;

    /** あとで非活動予約フラグ */
    bool _will_inactivate_after_a_few_frames_flg;
    /** あとで停止の残フレーム数（神フレームと一致したら停止） */
    DWORD _frame_of_inactivation;

    /** ノードが活動に切り替わった(_is_active_flg が false → true)瞬間に１フレームだけセットされるフラグ */
    bool _on_change_to_active_flg;
    /** ノードが停止に切り替わった(_is_active_flg が true → false)瞬間に１フレームだけセットされるフラグ */
    bool _on_change_to_inactive_flg;

public:
    /**
     * コンストラクタ
     * @param prm_name ノード名称（ユニークにして下さい）
     */
    GgafElement(const char* prm_name);

    /**
     * デストラクタ。自ツリーノードを解放する。 .
     */
    virtual ~GgafElement();

    /**
     * 掃除 .
     * 神が処理時間に余裕がでたとき等に、神が呼びだす。<BR>
     * 配下ノードの中にノード生存フラグ(_can_live_flg)が false になっているノードがあれば prm_num_cleaning 個だけ delete する。<BR>
     * @param prm_num_cleaning 解放するオブジェクト数
     */
    virtual void cleane(int prm_num_cleaning);

    /**
     * ノード初期処理 .
     * インスタンス生成後、nextFrame(),behave(),judge(),drawPrior(),drawMain(),drawTerminate(),happen(int),finally() の
     * 何れかが呼び出された時、最初に必ず１回だけ呼び出される。<BR>
     */
    virtual void initialize() = 0;

    /**
     * ノードのフレームを加算と、フレーム開始にあたってのいろいろな初期処理 .
     * _will_activate_at_next_frame_flg, _wil_pause_at_next_frame_flg, _will_hidden_at_next_frame_flg, _will_be_alive_at_next_frame_flg を<BR>
     * _is_active_flg, _was_paused_flg, _was_hidden_flg, _can_live_flg に反映（コピー）する。<BR>
     * また、_will_move_first_at_next_frame_flg, _will_move_last_at_next_frame_flg が true の場合は、<BR>
     * それぞれ、自ノードの先頭ノードへの移動、末尾ノードへの移動処理も実行される。<BR>
     * その後、配下ノード全てに nextFrame() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、behave()を実行する。<BR>
     */
    virtual void nextFrame();

    /**
     * ノードのフレーム毎の振る舞い処理 .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （_is_active_flg && !_was_paused_flg && _can_live_flg）の場合 <BR>
     * processBehavior() をコールした後、配下のノード全てについて behave() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、judge()を実行する。<BR>
     */
    virtual void behave();

    /**
     * 非活動→活動時に切り替わった時の処理 .
     * 非活動状態から活動状態に変化したときに１回コールバックされる。<BR>
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onActive() {
    }

    /**
     * 活動→非活動時に切り替わった時の処理 .
     * 活動状態から非活動状態に変化したときに１回コールバックされる。<BR>
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onInactive() {
    }

    /**
     * ノードのフレーム毎の判定処理 .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * (つまり _is_active_flg && !_was_paused_flg && _can_live_flg)の場合 <BR>
     * processJudgement() をコールした後、配下のノード全てについて judge() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、次フレームまでの残時間に余裕があれば drawPrior()、
     * 無ければ finally()を実行する。<BR>
     */
    virtual void judge();

    /**
     * ノードのフレーム毎の描画事前処理（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
     * (つまり _is_active_flg && !_was_hidden_flg && _can_live_flg)の場合 <BR>
     * processDrawPrior() をコールした後、配下のノード全てについて drawPrior() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、drawMain() を実行する。<BR>
     */
    virtual void drawPrior();

    /**
     * ノードのフレーム毎の描画本処理（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
     * (つまり _is_active_flg && !_was_hidden_flg && _can_live_flg)の場合 <BR>
     * processDrawMain() をコールした後、配下のノード全てについて drawMain() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、drawTerminate() を実行する。<BR>
     */
    virtual void drawMain();

    /**
     * ノードのフレーム毎の描画事後処理（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
     * (つまり _is_active_flg && !_was_hidden_flg && _can_live_flg)の場合 <BR>
     * processTerminate() をコールした後、配下のノード全てについて drawTerminate() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、finally() を実行する。<BR>
     */
    virtual void drawTerminate();

    /**
     * ノードのフレーム毎の最終処理 .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （_is_active_flg && !_was_paused_flg && _can_live_flg）の場合 <BR>
     * processFinally() をコールした後、配下のノード全てについて finally() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、次フレームまでの残時間に余裕があれば cleane() を実行する。<BR>
     */
    virtual void finally();

    /**
     * ノードの何かの処理(フレーム毎ではない) .
     * 活動フラグがセット、(つまり _is_active_flg)の場合 <BR>
     * processHappen(int) をコールした後、配下のノード全てについて happen() を再帰的に実行する。<BR>
     * @param   prm_no 何かの番号
     */
    virtual void happen(int prm_no);

    /**
     * フレーム毎の個別振る舞い処理を実装。 .
     * behave() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の振る舞いを処理を実装する。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理等である。<BR>
     * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、nextFrame() が実行済みであることを保証する。<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * フレーム毎の個別判断処理を実装。 .
     * judge() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数をオーバーライドして、ノード個別判断処理を記述する。<BR>
     * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、behave() が実行済みであることを保証する。<BR>
     * 本メンバ関数の存在意図として、processBehavior() で座標移動処理が全て完了した後､
     * 本メンバ関数で当たり判定処理を実装するといった使い方を想定している。<BR>
     */
    virtual void processJudgement() = 0;

    /**
     * ノードのフレーム毎の個別描画事前処理を実装。 .
     * drawPrior() 時の処理先頭でコールバックされる。 但し、神(GgafGod)が描画スキップした場合、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画事前処理を実装する。<BR>
     * 個別描画事前処理とは、主に当たり背景描画などである。<BR>
     * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、judge() が実行済みであることも保証する。<BR>
     * さらに、本メンバ関数実行後、processDrawMain()、processDrawTerminate() が呼び出されることも保証される。
     */
    virtual void processDrawPrior() = 0;

    /**
     * ノードのフレーム毎の個別描画本処理を実装。 .
     * drawMain() 時の処理先頭でコールバックされる。 但し、drawPrior() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画本処理を実装する。<BR>
     * 個別描画本処理とは主にキャラクタや、背景の描画を想定している。
     * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、drawPrior() が実行済みであることを保証する。<BR>
     */
    virtual void processDrawMain() = 0;

    /**
     * ノードのフレーム毎の個別表示事後処理を記述
     * drawTerminate() 時の処理先頭でコールバックされる。 但し、drawPrior() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別表示事後処理を実装する。<BR>
     * 個別表示事後処理とは、最前面レイヤーで実現するフェードエフェクトや、常に最前面に表示される情報表示などである。<BR>
     * 本メンバがコールバックされると言う事は、自ツリーノード全てに対して、drawMain() が実行済みであることを保証する。<BR>
     */
    virtual void processDrawTerminate() = 0;

    /**
     * ノードのフレーム毎の個別終端処理を実装。 .
     * finally() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の終端処理を実装する。<BR>
     * 終端処理とは、フラグ管理の実行などである。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理である。その他なんでも良いである。<BR>
     * 本メンバ関数がコールバックされると言う事は、自ツリーノード全てに対して、judge() が実行済みであることを保証する。<BR>
     */
    virtual void processFinal() = 0;

    /**
     * ノードの個別何かの処理を記述
     * happen() 時の処理先頭でコールバックされる。
     * 利用目的不定の汎用イベント用メソッド
     * @param   int prm_no 何かの番号
     */
    virtual void processHappen(int prm_no) = 0;

    /**
     * 神に謁見 .
     * @return  呼ばれて出てきた神
     */
    virtual GgafGod* askGod() = 0;

    //==================状態変移メソッド郡==================>
    /**
     * 活動状態にする(自ツリー) .
     * 正確には、次フレームから活動状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で活動状態になる事になります。<BR>
     * 自身と配下ノード全てについて再帰的に activateTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * 自ノードの processBehavior() で本メソッドを呼び出すコードを書いても、タスクシステムの仕組み上、<BR>
     * 実行されることは無いので、他ノードから実行したり、processFinal() などでの使用を想定。<BR>
     * <B>[補足]</B>ノード生成直後は、活動状態となっている。<BR>
     */
    void activateTree();
    /**
     * 活動予約する(自ツリー) .
     * Nフレーム後に activateTree() が実行されることを予約する。<BR>
     * 自身と配下ノード全てについて再帰的に activateTreeAfter(DWORD) が実行される。<BR>
     * activateTreeAfter(1) は、activateTree() と同じ意味になります。<BR>
     * @param prm_frame_offset 遅延フレーム数(1～)
     */
    void activateTreeAfter(DWORD prm_frame_offset);
    /**
     * 活動状態にする(単体) .
     * 自ノードだけ次フレームから活動状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void activateAlone();
    /**
     * 活動状態にする(自ツリー・即時) .
     * 正確には、活動フラグを即座に立てる。<BR>
     * 自身と配下ノード全てについて再帰的に activateTreeNow() が実行される。<BR>
     * 他のノードからの、「活動状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、activateTreeNow() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void activateTreeNow();
    /**
     * 活動状態にする(単体・即時) .
     * 自ノードのみについて、活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void activateAloneNow();
    //===================
    /**
     * 非活動状態にする(自ツリー) .
     * 正確には、次フレームから非活動状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で非活動状態になる事になります。<BR>
     * 自身と配下ノード全てについて再帰的に inactivateTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void inactivateTree();
    /**
     * 非活動予約する(自ツリー) .
     * Nフレーム後に inactivateTree() が実行されることを予約する。<BR>
     * 自身と配下ノード全てについて再帰的に inactivateTreeAfter(DWORD) が実行される。<BR>
     * inactivateTreeAfter(1) は、inactivateTree() と同じ意味になります。<BR>
     * @param prm_frame_offset 遅延フレーム数(1～)
     */
    void inactivateTreeAfter(DWORD prm_frame_offset);
    /**
     * 非活動状態にする(単体) .
     * 自ノードだけ次フレームから非活動状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void inactivateAlone();
    /**
     * 非活動状態にする(自ツリー・即時) .
     * 正確には、活動フラグを即座に下げる。<BR>
     * 自身と配下ノード全てについて再帰的に inactivateTreeNow() が実行される。<BR>
     * 他のノードからの、「非活動状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、inactivateTreeNow() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void inactivateTreeNow();
    /**
     * 非活動状態にする(単体・即時) .
     * 自ノードのみについて、非活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void inactivateAloneNow();
    //===================
    /**
     * 一時停止にする(自ツリー) .
     * 正確には、次フレームから一時停止にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止になる事になります。<BR>
     * 自身と配下ノード全てについて再帰的に pauseTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void pauseTree();
    /**
     * 一時停止にする(単体) .
     * 自ノードだけ次フレームから一時停止にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void pauseAlone();
    /**
     * 一時停止にする(自ツリー・即時) .
     * 正確には、一時停止フラグを即座に立てる。<BR>
     * 自身と配下ノード全てについて再帰的に pauseTreeNow() が実行される。<BR>
     * 他のノードからの、「一時停止ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、pauseTreeNow() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void pauseTreeNow();
    /**
     * 一時停止にする(単体・即時) .
     * 自ノードのみについて、一時停止フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void pauseAloneNow();
    //===================
    /**
     * 一時停止状態を解除にする(自ツリー) .
     * 正確には、次フレームから一時停止状態を解除する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止状態が解除される事になります。<BR>
     * 自身と配下ノード全てについて再帰的に unpauseTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止状態を解除の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void unpauseTree();
    /**
     * 一時停止状態を解除にする(単体) .
     * 自ノードだけ次フレームから一時停止状態を解除にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void unpauseAlone();
    /**
     * 一時停止状態を解除する(自ツリー・即時) .
     * 正確には、一時停止状態フラグを即座に下げる。<BR>
     * 自身と配下ノード全てについて再帰的に unpauseTreeNow() が実行される。<BR>
     * 他のノードからの、「一時停止状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、unpauseTreeNow() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void unpauseTreeNow();
    /**
     * 一時停止状態を解除にする(単体・即時) .
     * 自ノードのみについて、非活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void unpauseAloneNow();
    //===================
    /**
     * 非表示状態にする(自ツリー) .
     * 正確には、次フレームから非表示状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で非表示状態になる事になります。<BR>
     * 自身と配下ノード全てについて再帰的に hideTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非表示状態の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     * <B>[補足]</B>ノード生成直後は、非表示状態となっている。<BR>
     */
    void hideTree();
    /**
     * 非表示状態にする(単体) .
     * 自ノードだけ次フレームから非表示状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void hideAlone();
    /**
     * 非表示状態にする(自ツリー・即時) .
     * 正確には、非活動フラグを即座に立てる。<BR>
     * 自身と配下ノード全てについて再帰的に hideTreeNow() が実行される。<BR>
     * 他のノードからの、「非表示状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、hideTreeNow() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void hideTreeNow();
    /**
     * 非表示状態にする(単体・即時) .
     * 自ノードのみについて、非活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void hideAloneNow();
    //===================
    /**
     * 非表示状態を解除にする(自ツリー) .
     * 正確には、次フレームから非表示状態を解除する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で非表示状態が解除される事になります。<BR>
     * 自身と配下ノード全てについて再帰的に showTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非表示状態の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void showTree();
    /**
     * 非表示状態を解除にする(単体) .
     * 自ノードだけ次フレームから非表示状態を解除する予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void showAlone();
    /**
     * 非表示状態を解除する(自ツリー・即時) .
     * 正確には、非表示フラグを即座に下げる。<BR>
     * 自身と配下ノード全てについて再帰的に showTreeNow() が実行される。<BR>
     * 他のノードからの、「非表示状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、showTreeNow() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void showTreeNow();
    /**
     * 非表示状態を解除する(単体・即時) .
     * 自ノードのみについて、非表示状フラグを即座に下げる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void showAloneNow();
    //===================
    /**
     * さよならします。 .
     * 自ノードを次フレームから「生存終了」状態にすることを宣言する。 <BR>
     * 自ツリーノード全てに生存終了(arigatou_sayounara())がお知らせが届く。<BR>
     * 生存終了とは具体的には、表示フラグ(_was_hidden_flg)、振る舞いフラグ(_is_active_flg)、生存フラグ(_can_live_flg) を、
     * 次フレームからアンセットする事である。<BR>
     * _can_live_flg がアンセットされることにより、神(GgafGod)が処理時間の余裕のある時に cleane() メソッドにより
     * delete の対象となる。<BR>
     * したがって、本メンバ関数を実行しても、『同一フレーム内』では、まだdeleteは行なわれない。
     * インスタンスがすぐに解放されないことに注意。今はさよならするだけ。<BR>
     * 注意：さよならした後『同一フレーム内』に、 _can_live_flg をセットし直しても駄目です。<BR>
     * これは本メソッドで、GgafGarbageRootActorに所属するためです。<BR>
     */
    void arigatou_sayounara(DWORD prm_frame_offset = 0);

    /**
     * 自ツリーノードを最終ノードに移動する .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの最終にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではありません。<BR>
     */
    void moveLast() {
        _will_move_last_at_next_frame_flg = true;
    }

    /**
     * 自ツリーノードを先頭ノードに移動する .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの先頭にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではありません。<BR>
     */
    void moveFirst() {
        _will_move_first_at_next_frame_flg = true;
    }

    /**
     * 所属ツリーから独立する
     * @return  T* 脱退し独立した自ノードのポインタ
     *
     */
    T* becomeIndependent();


    /**
     * 非活動から活動に切り替わったかどうか .
     * ただし、onActive() で代用できる場合は、そちらをオーバーライドしたほうがすっきり記述できるはず。
     * @return  bool true:切り替わった／false:切り替わっていない
     */
    bool onChangeToActive();

    /**
     * 活動から停止に切り替わったかどうか .
     * このメソッドは今のところ使いどころは無いかもしれません。
     * @return  bool true:切り替わった／false:切り替わっていない
     */
    bool onChangeToInactive();

    /**
     * 生存可能か調べる
     * @return  bool true:生存可能／false:生存不可
     */
    bool canLive() {
        return _can_live_flg;
    }

    /**
     * 活動中か調べる
     * @return  bool true:活動中／false:非活動中
     */
    bool isActive();

    /**
     * 振る舞いは行なわれているか（＝一時停止されていないか）
     * @return  bool true:振る舞い可能（一時停止では無い）／false:振る舞い不可（一時停止中）
     */
    bool isBehaving();

    /**
     * 描画するかどうか調べる（非表示でないかどうか）
     * @return  bool true:描画できる(表示対象)／false:描画はしない(非表示対象)
     */
    bool isVisible();

    /**
     * ノードの現在の経過フレームを取得する
     */
    DWORD getSurvivalFrame() {
        return _lifeframe;
    }

    bool willActivateAtNextFrame() {
        return _will_activate_at_next_frame_flg;
    }

    bool willPauseAtNextFrame() {
        return _wil_pause_at_next_frame_flg;
    }

    bool willHiddenAtNextFrame() {
        return _will_hidden_at_next_frame_flg;
    }

    bool willBeAliveAtNextFrame() {
        return _will_be_alive_at_next_frame_flg;
    }

    bool willMoveFirstAtNextFrame() {
        return _will_move_first_at_next_frame_flg;
    }

    bool willMoveLastAtNextFrame() {
        return _will_move_last_at_next_frame_flg;
    }

    /**
     * 相対経過フレームの判定。
     * 直前の relativeFrame(int) 実行時（結果がtrue/falseに関わらず）のフレーム数からの経過フレーム数に達したか判定する。
     * 注意：入れ子や条件分岐により、relativeFrame(int) が呼び出される回数が変化する場合、相対経過フレームも変化する。
     * @param   prm_frame_relative    経過フレーム数
     * @return  bool    true:経過フレーム数に達した/false:達していない
     */
    bool relativeFrame(DWORD prm_frame_relative);

};

///////////////////////////////////////////////////////////////// ここからは実装部

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : SUPER(prm_name),
            _pGod(NULL), _was_initialize_flg(false), _dwGodFrame_when_goodbye(MAXDWORD), _lifeframe(0),
            _frame_relative(0), _is_active_flg(true), _was_paused_flg(false), _was_hidden_flg(false), _can_live_flg(true),
            _will_activate_at_next_frame_flg(true), _wil_pause_at_next_frame_flg(false), _will_hidden_at_next_frame_flg(false),
            _will_be_alive_at_next_frame_flg(true), _will_move_first_at_next_frame_flg(false), _will_move_last_at_next_frame_flg(false),
            _will_activate_after_a_few_frames_flg(false), _frame_of_activation(0), _will_inactivate_after_a_few_frames_flg(false), _frame_of_inactivation(0),
            _on_change_to_active_flg(false), _on_change_to_inactive_flg(false) {
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _lifeframe=" << _lifeframe << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);

    //死の時か
    if (_dwGodFrame_when_goodbye == (askGod()->_godframe)) {
        _will_activate_at_next_frame_flg = false;
        _will_be_alive_at_next_frame_flg = false;
    }


    if (_will_move_last_at_next_frame_flg) {
        _will_move_last_at_next_frame_flg = false;
        SUPER::moveLast();
    } else {

        if(_was_initialize_flg == false) {
            initialize();
            _was_initialize_flg = true;
        }

        if (_can_live_flg) {
            if (_will_activate_after_a_few_frames_flg) {
                //遅延play処理
                if (_lifeframe >= _frame_of_activation) {
                    activateTreeNow();
                    _frame_of_activation = 0;
                    _will_activate_after_a_few_frames_flg = false;
                }
            } else if (_will_inactivate_after_a_few_frames_flg) {
                //遅延stop処理
                if (_lifeframe == _frame_of_inactivation) {
                    inactivateTreeNow();
                    _frame_of_inactivation = 0;
                    _will_inactivate_after_a_few_frames_flg = false;
                }
            }
            if (_is_active_flg) {
                _lifeframe++;
            }
        }

        //活動、非活動の状態変化時
        if (_is_active_flg == false && _will_activate_at_next_frame_flg) {
            _on_change_to_active_flg = true;
        } else if (_is_active_flg && _will_activate_at_next_frame_flg == false) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_active_flg = false;
            _on_change_to_inactive_flg = false;
        }
        //フラグたちを反映
        _is_active_flg   = _will_activate_at_next_frame_flg;
        _was_paused_flg  = _wil_pause_at_next_frame_flg;
        _was_hidden_flg = _will_hidden_at_next_frame_flg;
        _can_live_flg    = _will_be_alive_at_next_frame_flg;

        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                if (pElementTemp->_is_last_flg) {
                    pElementTemp->nextFrame();
                    if (pElementTemp->_can_live_flg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp);
                    }
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                    pElementTemp->SUPER::_pPrev->nextFrame();
                    if (pElementTemp->SUPER::_pPrev->_can_live_flg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp->SUPER::_pPrev);
                    }
                }
            }
        }

        if (_will_move_first_at_next_frame_flg) {
            _will_move_first_at_next_frame_flg = false;
            SUPER::moveFirst();
        }

    }
    TRACE("GgafElement::nextFrame END _lifeframe="<<_lifeframe<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    //活動、非活動の状態変化時コールバック
    if (_on_change_to_active_flg) {
        onActive();
    } else if (_on_change_to_inactive_flg) {
        onInactive();
    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
        processBehavior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::judge() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
        processJudgement();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::drawPrior() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        _frame_relative = 0;
        processDrawPrior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawPrior();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::drawMain() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        _frame_relative = 0;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawMain();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::drawTerminate() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        _frame_relative = 0;
        processDrawTerminate();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawTerminate();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::happen(int prm_no) {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_can_live_flg) {
        _frame_relative = 0;
        processHappen(prm_no);
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->happen(prm_no);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::finally() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
        processFinal();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->finally();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateAlone() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateAloneNow() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _was_hidden_flg = false;
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::activateTreeNow() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _was_hidden_flg = false;
        _will_activate_at_next_frame_flg = true;
        _wil_pause_at_next_frame_flg = false;
        _will_hidden_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeNow();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateTreeAfter(DWORD prm_frame_offset) {
    _will_activate_after_a_few_frames_flg = true;
    _frame_of_activation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivateAlone() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        _will_activate_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateTreeAfter(DWORD prm_frame_offset) {
    _will_inactivate_after_a_few_frames_flg = true;
    _frame_of_inactivation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivateAloneNow() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _will_activate_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeNow() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _will_activate_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeNow();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseTree() {
    if (_can_live_flg) {
        _wil_pause_at_next_frame_flg = true;
        //_is_active_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseAlone() {
    if (_can_live_flg) {
        _wil_pause_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeNow() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _wil_pause_at_next_frame_flg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeNow();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseAloneNow() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _wil_pause_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_can_live_flg) {
        _wil_pause_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpauseAlone() {
    if (_can_live_flg) {
        _wil_pause_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeNow() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _wil_pause_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeNow();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpauseAloneNow() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _wil_pause_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::hideTree() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->hideTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::hideAlone() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::hideTreeNow() {
    if (_can_live_flg) {
        _was_hidden_flg = true;
        _will_hidden_at_next_frame_flg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->hideTreeNow();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::hideAloneNow() {
    if (_can_live_flg) {
        _was_hidden_flg = true;
        _will_hidden_at_next_frame_flg = true;
    }
}

template<class T>
void GgafElement<T>::showTree() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->showTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::showAlone() {
    if (_can_live_flg) {
        _will_hidden_at_next_frame_flg = false;
    }
}

template<class T>
void GgafElement<T>::showTreeNow() {
    if (_can_live_flg) {
        _was_hidden_flg = false;
        _will_hidden_at_next_frame_flg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->showTreeNow();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::showAloneNow() {
    if (_can_live_flg) {
        _was_hidden_flg = false;
        _will_hidden_at_next_frame_flg = false;
    }
}
template<class T>
void GgafElement<T>::arigatou_sayounara(DWORD prm_frame_offset) {

    _dwGodFrame_when_goodbye = (askGod()->_godframe) + prm_frame_offset + 1;
    if (SUPER::_pSubFirst != NULL) {
        T* pElementTemp = SUPER::_pSubFirst;
        while(true) {
            pElementTemp->arigatou_sayounara(prm_frame_offset);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->SUPER::_pNext;
            }
        }
    }
}


template<class T>
bool GgafElement<T>::isActive() {
    if (_can_live_flg && _is_active_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::onChangeToActive() {
    if (_can_live_flg && _on_change_to_active_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::onChangeToInactive() {
    if (_can_live_flg && _on_change_to_inactive_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::isVisible() {
    if (_can_live_flg && _is_active_flg && !_was_hidden_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::isBehaving() {
    if (_can_live_flg && _is_active_flg && !_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(DWORD prm_frame_relative) {
    _frame_relative += prm_frame_relative;
    if (_lifeframe == _frame_relative) {
        return true;
    } else {
        return false;
    }
}


template<class T>
T* GgafElement<T>::becomeIndependent() {
    if (_can_live_flg) {
        return SUPER::breakAwayFromTree();
    } else {
        throwGgafCriticalException("[GgafTreeNode<"<<SUPER::_class_name<<">::becomeIndependent()] ＜警告＞ "<<SUPER::getName()<<"は、いずれ死に行く運命である。");
    }
}

template<class T>
void GgafElement<T>::cleane(int prm_num_cleaning) {
    if (SUPER::_pSubFirst == NULL) {
        return;
    }

    T* pElementTemp = SUPER::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafFactory::_cnt_cleaned < prm_num_cleaning) {

        if (pElementTemp->_pSubFirst) {
            //子の子がまだのっている場合さらにもぐる
            pElementTemp->cleane(prm_num_cleaning);
            if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }

        if (pElementTemp->_is_first_flg) { //最後の一つ
            if (pElementTemp->_pSubFirst) {
                //子の子がまだのっている場合さらにもぐる
                pElementTemp->cleane(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pElementTemp);
                GgafFactory::_cnt_cleaned++;
                Sleep(1);
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //子の子がまだのっている場合さらにもぐる
                pWk->cleane(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pWk);
                GgafFactory::_cnt_cleaned++;
                Sleep(1);
            }
        }
    }
}

template<class T>
GgafElement<T>::~GgafElement() {
}

}
#endif /*GGAFELEMENT_H_*/
