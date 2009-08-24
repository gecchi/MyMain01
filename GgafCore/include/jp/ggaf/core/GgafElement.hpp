#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNodeに、タスクシステム及び様々な状態管理（フラグ管理）を追加。 .
 * 毎フレーム、を神(GgafGod)はこの世(GgafUniverse)に、次のメソッド順で呼び出す仕組みになっている。この世(GgafUniverse)も本templateを実装している。<BR>
 * nextFrame() > behave() > judge() > [preDraw() > draw() > afterDraw()] > finally() <BR>
 * 上記の内、nextFrame() finally() は毎フレーム実行される。<BR>
 * behave() judge() は活動状態フラグ(_is_active_flg)が true、かつ、一時停止フラグ(_was_paused_flg)が false の場合実行される。<BR>
 * preDraw() draw() afterDraw() は、次フレームまでの残時間に余裕がある場合<BR>
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

public:
    /** 神への近道 */
    GgafGod* _pGod;
    /** initializeが行われたどうかのフラグ(true=行われた) */
    bool _was_initialize_flg;

    /** 余命 */
    DWORD _dwGodFrame_when_goodbye;
    /** 相対フレーム計算用 */
    DWORD _frame_relative;
    /** ノード活動フラグ */
    bool _is_active_flg;
    /** 一時停止フラグ */
    bool _was_paused_flg;
    /** ノード生存フラグ */
    bool _can_live_flg;

    /** 次フレームのノード活動フラグ、次フレームのフレーム加算時 _is_active_flg に反映される */
    bool _is_active_flg_in_next_frame;
    /** 次フレームの一時停止フラグ、次フレームのフレーム加算時 _was_paused_flg に反映される */
    bool _was_paused_flg_in_next_frame;
    /** 次フレームの一時非表示フラグ、次フレームのフレーム加算時 _can_live_flg に反映される  */
    bool _can_live_flg_in_next_frame;

    /** 先頭ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが先頭ノードに移動する */
    bool _will_move_first_in_next_frame_flg;
    /** 末尾ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが末尾ノードに移動する */
    bool _will_move_last_in_next_frame_flg;

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



    /** ノードが誕生(addSubされた）時からのフレーム */
    DWORD _lifeframe;

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
     * 掃除(自ツリー) .
     * 神が処理時間に余裕がでたとき等に、神が呼びだす。<BR>
     * 配下ノードの中にノード生存フラグ(_can_live_flg)が false になっているノードがあれば prm_num_cleaning 個だけ delete する。<BR>
     * @param prm_num_cleaning 解放するオブジェクト数
     */
    virtual void cleane(int prm_num_cleaning);

    /**
     * ノード初期処理(単体) .
     * インスタンス生成後、
     * 何れかが呼び出される前に、最初に必ず１回だけ呼び出される。<BR>
     */
    virtual void initialize() = 0;

    /**
     * ノードのフレームを加算と、フレーム開始にあたってのいろいろな初期処理(自ツリー) .
     * _is_active_flg_in_next_frame _was_paused_flg_in_next_frame _can_live_flg_in_next_frame を<BR>
     * _is_active_flg _was_paused_flg _can_live_flg に反映（コピー）する。<BR>
     * また、_will_move_first_in_next_frame_flg, _will_move_last_in_next_frame_flg が true の場合は、<BR>
     * それぞれ、自ノードの先頭ノードへの移動、末尾ノードへの移動処理も実行される。<BR>
     * その後、配下ノード全てに nextFrame() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して本メンバ関数実行後、behave()を実行する。<BR>
     */
    virtual void nextFrame();

    /**
     * ノードのフレーム毎の振る舞い処理(自ツリー) .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （ _is_active_flg && !_was_paused_flg && _can_live_flg ）の場合 <BR>
     * processBehavior() をコールした後、配下のノード全てについて behave() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して本メンバ関数実行後、judge()を実行する。<BR>
     */
    virtual void behave();

    /**
     * 非活動→活動時に切り替わった時の処理(単体) .
     * 非活動状態から活動状態に変化したときに１回コールバックされる。<BR>
     * 呼び出されるタイミングはフレーム加算直後である。
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onActive() {
    }

    /**
     * 活動→非活動時に切り替わった時の処理(単体) .
     * 活動状態から非活動状態に変化したときに１回コールバックされる。<BR>
     * 呼び出されるタイミングはフレーム加算直後である。
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onInactive() {
    }

    /**
     * ノードのフレーム毎の判定処理(自ツリー) .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * つまり ( _is_active_flg && !_was_paused_flg && _can_live_flg )の場合 <BR>
     * processJudgement() をコールした後、配下のノード全てについて judge() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して本メンバ関数実行後、次フレームまでの残時間に余裕があれば preDraw()
     * 無ければ finally() を実行する。<BR>
     */
    virtual void judge();

    /**
     * ノードのフレーム毎の描画事前処理(自ツリー)（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、<BR>
     * (つまり _is_active_flg && _can_live_flg)の場合 <BR>
     * processPreDraw() をコールした後、配下のノード全てについて preDraw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して本メンバ関数実行後、draw() を実行する。<BR>
     */
    virtual void preDraw();

    /**
     * ノードのフレーム毎の描画本処理(自ツリー)（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、<BR>
     * (つまり _is_active_flg && _can_live_flg)の場合 <BR>
     * processDraw() をコールした後、配下のノード全てについて draw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して本メンバ関数実行後、afterDraw() を実行する。<BR>
     */
    virtual void draw();

    /**
     * ノードのフレーム毎の描画事後処理(自ツリー)（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット<BR>
     * (つまり _is_active_flg && _can_live_flg)の場合 <BR>
     * processTerminate() をコールした後、配下のノード全てについて afterDraw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して本メンバ関数実行後、finally() を実行する。<BR>
     */
    virtual void afterDraw();

    /**
     * ノードのフレーム毎の最終処理(自ツリー) .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （_is_active_flg && !_was_paused_flg && _can_live_flg）の場合 <BR>
     * processFinally() をコールした後、配下のノード全てについて finally() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して本メンバ関数実行後、次フレームまでの残時間に余裕があれば cleane() を実行する。<BR>
     */
    virtual void finally();

    /**
     * ノードの何かの処理(自ツリー)(フレーム毎ではない) .
     * 活動フラグがセット、( _is_active_flg = true )の場合 <BR>
     * 直ちに processHappen(int) をコールした後、配下のノード全てについて happen() を再帰的に実行する。<BR>
     * @param   prm_no 何かの番号
     */
    virtual void happen(int prm_no);

    /**
     * フレーム毎の個別振る舞い処理を実装。(フレームワーク実装用、単体) .
     */
    virtual void processPreBehavior() {}

    /**
     * フレーム毎の個別振る舞い処理を実装。(ユーザー実装用、単体) .
     * behave() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の振る舞いを処理を実装する。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理等である。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、nextFrame() が実行済みであることを保証する。<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * フレーム毎の個別判断処理を実装。(フレームワーク実装用、単体) .
     */
    virtual void processPreJudgement() {}

    /**
     * フレーム毎の個別判断処理を実装。(ユーザー実装用、単体) .
     * judge() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数をオーバーライドして、ノード個別判断処理を記述する。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対してて、processBehavior() が実行済みであることを保証する。<BR>
     * 本メンバ関数の存在意図として、processBehavior() で座標移動処理が全て完了した後､
     * 本メンバ関数で当たり判定処理を実装するといった使い方を想定している。<BR>
     */
    virtual void processJudgement() = 0;

    /**
     * ノードのフレーム毎の個別描画事前処理を実装。(フレームワーク実装用、単体) .
     * preDraw() 時の処理先頭でコールバックされる。 但し、神(GgafGod)が描画スキップした場合、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画事前処理を実装する。<BR>
     * 個別描画事前処理とは、主に当たり背景描画などである。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processJudgement() が実行済みであることも保証する。<BR>
     * さらに、本メンバ関数実行後、processDraw()、processAfterDraw() が呼び出されることも保証される。
     */
    virtual void processPreDraw() {};

    /**
     * ノードのフレーム毎の個別描画本処理を実装。(単体) .
     * draw() 時の処理先頭でコールバックされる。 但し、preDraw() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画本処理を実装する。<BR>
     * 個別描画本処理とは主にキャラクタや、背景の描画を想定している。
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processPreDraw() が実行済みであることを保証する。<BR>
     */
    virtual void processDraw() = 0;

    /**
     * ノードのフレーム毎の個別表示事後処理を記述。(フレームワーク実装用、単体) .
     * afterDraw() 時の処理先頭でコールバックされる。 但し、preDraw() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別表示事後処理を実装する。<BR>
     * 個別表示事後処理とは、最前面レイヤーで実現するフェードエフェクトや、常に最前面に表示される情報表示などである。<BR>
     * 本メンバがコールバックされると言う事は、全ノード対して、processDraw() が実行済みであることを保証する。<BR>
     */
    virtual void processAfterDraw() {};

    /**
     * ノードのフレーム毎の個別終端処理を実装。(単体) .
     * finally() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の終端処理を実装する。<BR>
     * 終端処理とは、フラグ管理の実行などである。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理である。その他なんでも良いである。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processJudgement() が実行済みで 描画処理は終了していることを保証する。<BR>
     */
    virtual void processFinal() = 0;

    /**
     * ノードの個別何かの処理を記述。(単体)
     * happen() 時の処理先頭でコールバックされる。
     * 利用目的不定の汎用イベント用コールバック
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
     * そして、次フレーム先頭処理で活動状態になる事になる。<BR>
     * 自身と配下ノード全てについて再帰的に activateTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * 自ノードの processBehavior() で本メソッドを呼び出すコードを書いても、タスクシステムの仕組み上、<BR>
     * 実行されることは無いので、他ノードから実行したり、processFinal() などでの使用を想定。<BR>
     * <B>[補足]</B>ノード生成直後は、活動状態となっている。<BR>
     */
    void activateTree();

    /**
     * 活動状態にする(単体) .
     * Nフレーム後に activate() が実行されることを予約する。<BR>
     * 自身と配下ノード全てについて再帰的に activateAfter(DWORD) が実行される。<BR>
     * activateAfter(1) は、activate() と同じ意味になります。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * @param prm_frame_offset 遅延フレーム数(1～)
     */
    void activateAfter(DWORD prm_frame_offset);

    /**
     * 活動状態にする(単体) .
     * 自ノードだけ次フレームから活動状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     */
    void activate();

    /**
     * 活動状態にする(単体・即時) .
     * 自ノードについて、即座に活動状態にする。通常、本メソッドの使用は非推奨。<BR>
     * 即座に状態が変化するため、以下の点を留意して、使用する際は注意が必要である。<BR>
     * 実行前の自ノード状態が 非活動状態 ( _is_active_flg == false ) の場合、非活動→活動に変化したとして、<BR>
     * 直ちに onActive() コールバックを呼び出し、また _on_change_to_active_flg = true とする。<BR>
     * onActive() コールバックは、次フレーム加算時は呼び出されない。 （２重に呼ばれる事は無いようにしてある）<BR>
     * さらに onActive() は仮想関数であるため、もし本クラスを継承した下位にクラスのコンストラクタ内で activateImmediately() <BR>
     * を呼び出した場合、継承クラスの実装の onActive() は実行されず、空実装の本クラスの onInctive() が呼び出される。<BR>
     * また、 _on_change_to_active_flg をはじめ、その他本メソッドによって変化した新たなフラグ状態は、<BR>
     * 『同一フレーム内』の残りの未処理のノードに対してのみ有効となる。つまり、<BR>
     * 『同一フレーム内』であっても、既に処理されたノードとは異なる状態になる可能性が大きく、<BR>
     * 他ノードのロジックが、「このノードが活動状態ならば・・・」等、その状態（フラグ）により処理分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    void activateImmediately();

    /**
     * 活動状態にする(自ツリー・即時) .
     * 自身と配下ノード全てについて再帰的に activateImmediately() が実行される。<BR>
     * activateImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void activateTreeImmediately();
    //===================
    /**
     * 非活動状態にする(自ツリー) .
     * 正確には、次フレームから非活動状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で非活動状態になる事になる。<BR>
     * 自身と配下ノード全てについて再帰的に inactivate() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     */
    void inactivateTree();

    /**
     * 非活動予約する(自ツリー) .
     * Nフレーム後に inactivateTree() が実行されることを予約する。<BR>
     * 自身と配下ノード全てについて再帰的に inactivateAfter(DWORD) が実行される。<BR>
     * inactivateAfter(1) は、inactivateTree() と同じ意味になります。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     * @param prm_frame_offset 遅延フレーム数(1～)
     */
    void inactivateAfter(DWORD prm_frame_offset);

    /**
     * 非活動状態にする(単体) .
     * 自ノードだけ次フレームから非活動状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     */
    void inactivate();

    /**
     * 非活動状態にする(単体・即時) .
     * 自ノードについて、即座に非活動状態にする。通常、本メソッドの使用は非推奨。<BR>
     * 即座に状態が変化するため、以下の点を留意して、使用する際は注意が必要である。<BR>
     * 実行前の自ノード状態が 活動状態 ( _is_active_flg == true ) の場合、活動→非活動に変化したとして、<BR>
     * 直ちに onInctive() コールバックを呼び出し、また _on_change_to_inactive_flg = true とする。<BR>
     * onInctive() コールバックは、次フレーム加算時は呼び出されない。（２重に呼ばれる事は無いようにしてある） <BR>
     * さらに onInctive() は仮想関数であるため、もし本クラスを継承した下位にクラスのコンストラクタ内で inactivateImmediately() <BR>
     * を呼び出した場合、継承クラスの実装の onInctive() は実行されず、空実装の本クラスの onInctive() が呼び出される。<BR>
     * また、 _on_change_to_inactive_flg をはじめ、その他本メソッドによって変化した新たなフラグ状態は、<BR>
     * 『同一フレーム内』の残りの未処理のノードに対してのみ有効となる。つまり、<BR>
     * 『同一フレーム内』であっても、既に処理されたノードとは異なる状態になる可能性が大きく、<BR>
     * 他ノードのロジックが、「このノードが非活動状態ならば・・・」等、その状態（フラグ）により処理分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    void inactivateImmediately();

    /**
     * 非活動状態にする(自ツリー・即時) .
     * 自身と配下ノード全てについて再帰的に inactivateImmediately() が実行される。<BR>
     * inactivateImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void inactivateTreeImmediately();

    //===================
    /**
     * 一時停止にする(自ツリー) .
     * 正確には、次フレームから一時停止にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止になる事になる。<BR>
     * 自身と配下ノード全てについて再帰的に pause() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止の変化は無く一貫性は保たれる。<BR>
     */
    void pauseTree();

    /**
     * 一時停止にする(単体) .
     * 自ノードだけ次フレームから一時停止にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     * 本メソッドを実行しても、『同一フレーム内』は一時停止の変化は無く一貫性は保たれる。<BR>
     */
    void pause();

    /**
     * 一時停止状態にする(単体・即時) .
     * 自ノードについて、即座に一時停止状態（ _was_paused_flg = true ）にする。通常、本メソッドの使用は非推奨。<BR>
     * 即座に状態が変化するため、以下の点を留意して使用する際は注意が必要である。<BR>
     * 変化した新たなフラグ状態は、『同一フレーム内』の残りの未処理のノードに対してのみ有効となる。つまり、<BR>
     * 『同一フレーム内』であっても、既に処理されたノードとは異なる状態になる可能性があり、<BR>
     * 他ノードのロジックが、「このノードが一時停止状態ならば・・・」等、その状態（フラグ）により処理分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    void pauseImmediately();

    /**
     * 一時停止状態にする(自ツリー・即時) .
     * 自身と配下ノード全てについて再帰的に pauseImmediately() が実行される。<BR>
     * pauseImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void pauseTreeImmediately();

    //===================
    /**
     * 一時停止状態を解除する(自ツリー) .
     * 正確には、次フレームから一時停止状態を解除する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止状態が解除される事になる。<BR>
     * 自身と配下ノード全てについて再帰的に unpause() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止状態を解除の変化は無く一貫性は保たれる。<BR>
     */
    void unpauseTree();
    /**
     * 一時停止状態を解除する(単体) .
     * 自ノードだけ次フレームから一時停止状態を解除にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     * 本メソッドを実行しても、『同一フレーム内』は一時停止状態を解除の変化は無く一貫性は保たれる。<BR>
     */
    void unpause();

    /**
     * 一時停止状態を解除する(自ツリー・即時) .
     * 自身と配下ノード全てについて再帰的に unpauseImmediately() が実行される。<BR>
     * unpauseImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void unpauseTreeImmediately();

    /**
     * 一時停止状態を解除する(単体・即時) .
     * 自ノードについて、即座に一時停止していない状態（ _was_paused_flg = false ）にする。通常、本メソッドの使用は非推奨。<BR>
     * 即座に状態が変化するため、以下の点を留意して使用する際は注意が必要である。<BR>
     * 変化した新たなフラグ状態は、『同一フレーム内』の残りの未処理のノードに対してのみ有効となる。つまり、<BR>
     * 『同一フレーム内』であっても、既に処理されたノードとは異なる状態になる可能性があり、<BR>
     * 他ノードのロジックが、「このノードが一時停止状態ならば・・・」等、その状態（フラグ）により処理分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    void unpauseImmediately();
    //===================

    /**
     * さよならします。(自ツリー) .
     * 自ノードを次フレームから「生存終了」状態にすることを宣言する。 <BR>
     * 自ツリーノード全てに生存終了(adios())がお知らせが届く。<BR>
     * 生存終了とは具体的には、振る舞いフラグ(_is_active_flg)、生存フラグ(_can_live_flg) を、
     * 次フレームからアンセットする事である。<BR>
     * _can_live_flg がアンセットされることにより、神(GgafGod)が処理時間の余裕のある時に cleane() メソッドにより
     * delete の対象となる。<BR>
     * したがって、本メンバ関数を実行しても、『同一フレーム内』では、まだdeleteは行なわれない。
     * インスタンスがすぐに解放されないことに注意。今はさよならするだけ。<BR>
     * 注意：さよならした後『同一フレーム内』に、 _can_live_flg をセットし直しても駄目です。<BR>
     * これは本メソッドで、GgafGarbageRootActorに所属するためです。<BR>
     */
    void adios(DWORD prm_frame_offset = 0);

    /**
     * 自ツリーノードを最終ノードに移動する(単体) .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの最終にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではない。<BR>
     */
    void moveLast() {
        _will_move_last_in_next_frame_flg = true;
    }

    /**
     * 自ツリーノードを先頭ノードに移動する(単体) .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの先頭にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではない。<BR>
     */
    void moveFirst() {
        _will_move_first_in_next_frame_flg = true;
    }

    /**
     * 所属ツリーから独立する(単体)
     * @return  T* 脱退し独立した自ノードのポインタ
     *
     */
    T* becomeIndependent();


    /**
     * 非活動から活動に切り替わったかどうか .
     * ただし、onActive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備した。<BR>
     * @return  bool true:切り替わった／false:切り替わっていない
     */
    bool onChangeToActive();

    /**
     * 活動から停止に切り替わったかどうか .
     * ただし、onInactive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備した。<BR>
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
     * 描画中かどうか調べる（非表示でないかどうか）
     * @return  bool true:描画できる(表示対象)／false:描画はしない(非表示対象)
     */
    bool isVisible();

    /**
     * ノードの現在の経過フレームを取得する
     */
    DWORD getSurvivalFrame() {
        return _lifeframe;
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
            _frame_relative(0), _is_active_flg(true), _was_paused_flg(false), _can_live_flg(true),
            _is_active_flg_in_next_frame(true), _was_paused_flg_in_next_frame(false),
            _can_live_flg_in_next_frame(true), _will_move_first_in_next_frame_flg(false), _will_move_last_in_next_frame_flg(false),
            _will_activate_after_a_few_frames_flg(false), _frame_of_activation(0), _will_inactivate_after_a_few_frames_flg(false), _frame_of_inactivation(0),
            _on_change_to_active_flg(false), _on_change_to_inactive_flg(false) {
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _lifeframe=" << _lifeframe << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);
    _was_paused_flg  = _was_paused_flg_in_next_frame;
    if (_was_paused_flg) {
        return;
    }

    //死の時か
    if (_dwGodFrame_when_goodbye == (askGod()->_godframe)) {
        _is_active_flg_in_next_frame = false;
        _can_live_flg_in_next_frame = false;
    }


    if (_will_move_last_in_next_frame_flg) {
        _will_move_last_in_next_frame_flg = false;
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
                    activate();
                    _frame_of_activation = 0;
                    _will_activate_after_a_few_frames_flg = false;
                }
            }

            if (_will_inactivate_after_a_few_frames_flg) {
                //遅延stop処理
                if (_lifeframe == _frame_of_inactivation) {
                    inactivate();
                    _frame_of_inactivation = 0;
                    _will_inactivate_after_a_few_frames_flg = false;
                }
            }
            if (_is_active_flg) {
                _lifeframe++;
            }
        }

        //活動、非活動の状態変化時
        if (_is_active_flg == false && _is_active_flg_in_next_frame) {
            _on_change_to_active_flg = true;
            onActive(); //コールバック
        } else if (_is_active_flg && _is_active_flg_in_next_frame == false) {
            _on_change_to_inactive_flg = true;
            onInactive(); //コールバック
        } else {
            _on_change_to_active_flg = false;
            _on_change_to_inactive_flg = false;
        }

        //フラグたちを反映
        _is_active_flg   = _is_active_flg_in_next_frame;
        _can_live_flg    = _can_live_flg_in_next_frame;

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

        if (_will_move_first_in_next_frame_flg) {
            _will_move_first_in_next_frame_flg = false;
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

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        _frame_relative = 0;
        processPreBehavior();
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
        processPreJudgement();
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
void GgafElement<T>::preDraw() {
    if(_was_initialize_flg == false) {
        initialize();
        _was_initialize_flg = true;
    }

    if (_is_active_flg && _can_live_flg) {
        _frame_relative = 0;
        processPreDraw();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->preDraw();
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
void GgafElement<T>::draw() {
    if (_is_active_flg && _can_live_flg) {
        _frame_relative = 0;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->draw();
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
void GgafElement<T>::afterDraw() {
    if (_is_active_flg && _can_live_flg) {
        _frame_relative = 0;
        processAfterDraw();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->afterDraw();
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
void GgafElement<T>::activate() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
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
void GgafElement<T>::activateImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
            onActive(); //コールバック
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::activateTreeImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg == false) {
            _on_change_to_active_flg = true;
            onInactive(); //コールバック
        } else {
            _on_change_to_active_flg = false;
        }
        _is_active_flg = true;
        _was_paused_flg = false;
        _is_active_flg_in_next_frame = true;
        _was_paused_flg_in_next_frame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeImmediately();
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
void GgafElement<T>::activateAfter(DWORD prm_frame_offset) {
    _will_activate_after_a_few_frames_flg = true;
    _frame_of_activation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivate() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        _is_active_flg_in_next_frame = false;
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
void GgafElement<T>::inactivateAfter(DWORD prm_frame_offset) {
    _will_inactivate_after_a_few_frames_flg = true;
    _frame_of_inactivation = _lifeframe + prm_frame_offset;
}

template<class T>
void GgafElement<T>::inactivateImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _is_active_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeImmediately() {
    if (_can_live_flg) {
        if (_is_active_flg) {
            _on_change_to_inactive_flg = true;
        } else {
            _on_change_to_inactive_flg = false;
        }
        _is_active_flg = false;
        _is_active_flg_in_next_frame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeImmediately();
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
        _was_paused_flg_in_next_frame = true;
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
void GgafElement<T>::pause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeImmediately();
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
void GgafElement<T>::pauseImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
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
void GgafElement<T>::unpause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeImmediately();
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
void GgafElement<T>::unpauseImmediately() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
    }
}
template<class T>
void GgafElement<T>::adios(DWORD prm_frame_offset) {

    _dwGodFrame_when_goodbye = (askGod()->_godframe) + prm_frame_offset + 1;
    if (SUPER::_pSubFirst != NULL) {
        T* pElementTemp = SUPER::_pSubFirst;
        while(true) {
            pElementTemp->adios(prm_frame_offset);
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
    if (_can_live_flg && _is_active_flg) {
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
        return SUPER::extract();
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
