#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define GGAF_NODE GgafCore::GgafNode<T>
/** 共通遅延解放フレーム数 */
#define GGAF_SAYONARA_DELAY (60*15)
//GGAF_SAYONARA_DELAYは全Element共通の解放遅延フレーム数で、
//長めに設定しないと、いろいろ不都合が多い。
//消失後もなお参照が可能とするための仕組みで、
//例えば、消滅後の爆発SE等で、3D効果のためSE発声元座標情報がしばらく必要とか、
//消滅後の消滅アクターに属する子アクターの発射弾が、親アクターの座標を参照しているなど、
//消滅しても、しばらくは残存させなければいけない場合がある。
//基本的に、消滅確定→完全に消失までのフレームの最大フレームを指定する。
//GGAF_SAYONARA_DELAYを短めに設定すると、現在は10秒(60*15)
//消滅後の子の発射弾については、残された発射弾が突然消えるので少し不自然。という程度で問題はない。
//しかし、SEの3D効果は、エラーになるため、SE再生時間の最大フレーム数を設定しなければいけない。
//例えば爆発SEが１分かかるような物が一つでも使用したい場合は、最大の1分(60*60)を設定しなければならない。



/**
 * GgafNodeに、様々な状態遷移管理（タスクシステム）を追加。 .
 * 毎フレーム、神(GgafGod)はこの世(GgafUniverse)に、次のメソッド順で呼び出す仕組みになっている。この世(GgafUniverse)も本templateを実装している。<BR>
 * nextFrame() > behave() > settleBehavior() > judge() > [preDraw() > draw() > afterDraw()] > doFinally() <BR>
 * 上記の内、nextFrame() doFinally() は毎フレーム実行される。<BR>
 * behave() settleBehavior() judge() は活動状態フラグ(_is_active_flg)が true、かつ、一時停止フラグ(_was_paused_flg)が false の場合実行される。<BR>
 * preDraw() draw() afterDraw() は、次フレームまでの残時間に余裕がある場合実行される。<BR>
 * 次フレームまでの残時間に余裕が無い場合、神はこの３メソッドをスキップするが、MAX_SKIP_FRAME フレームに１回は実行する。<BR>
 * 上記の nextFrame() ～ doFinally() の直接オーバーライドは非推奨。オーバーライド用に各メソッドでコールバックされる純粋仮想関数(processXxxxxx()) を用意している。<BR>
 * initialize() は、上記の nextFrame() ～ doFinally() を何れかを呼び出す前にインスタンスごとに１回だけ呼ばれる仕組みになっている。<BR>
 * 但し、生存フラグ(_can_live_flg)がfalseの場合（deleteされる）は、nextFrame() ～ doFinally() は全て実行されない。<BR>
 * (※旧クラス名はGgafFactor)
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

private:

protected:

public:
    /** [r]神への近道 */
    GgafGod* _pGod;
    /** [r]initializeが行われたどうかのフラグ(true=行われた) */
    bool _was_initialize_flg;

    /** [r]ノードが誕生(addSubされた）時からのフレーム数総計(但し、_was_paused_flg==true 時は加算され無い) */
    frame _frame_of_life;
    /** [r]ノードが誕生(addSubされた）時から、振舞ったフレーム数総計(但し、_was_paused_flg==true 又は _is_active_flg==false 時は加算され無い) */
    frame _frame_of_behaving;
    /** [r]ノードが活動開始(onActive())時からの振舞ったフレーム数総計(但し、_was_paused_flg==true 又は _is_active_flg==false 時は加算され無い) */
    frame _frame_of_behaving_since_onActive;
    /** [r]相対フレーム計算用 */
    frame _frameEnd;
    /** [r]ノード活動フラグ */
    bool _is_active_flg;
    /** [r]一時停止フラグ */
    bool _was_paused_flg;
    /** [r]ノード生存フラグ */
    bool _can_live_flg;

    /** [r]次フレームのノード活動フラグ、次フレームのフレーム加算時 _is_active_flg に反映される */
//    bool _is_active_flg_in_next_frame;
    /** [r]次フレームの一時停止フラグ、次フレームのフレーム加算時 _was_paused_flg に反映される */
    bool _was_paused_flg_in_next_frame;
    /** [r]次フレームの一時非表示フラグ、次フレームのフレーム加算時 _can_live_flg に反映される  */
    //bool _can_live_flg_in_next_frame;

    /** [r]終了フラグ */
    bool _will_end_after_flg;
    /** [r]終了する予定の _frame_of_life */
    frame _frame_of_life_when_end;


    /** [r]あとで活動予約フラグ */
    bool _will_activate_after_flg;
    /** [r]活動開始する予定の _frame_of_life */
    frame _frame_of_life_when_activation;

    /** [r]あとで非活動予約フラグ */
    bool _will_inactivate_after_flg;
    /** [r]活動終了する予定の _frame_of_life */
    frame _frame_of_life_when_inactivation;

    /** [r]ノードが活動に切り替わった(_is_active_flg が false → true)瞬間に１フレームだけセットされるフラグ */
    bool _on_change_to_active_flg;
    /** [r]ノードが停止に切り替わった(_is_active_flg が true → false)瞬間に１フレームだけセットされるフラグ */
    bool _on_change_to_inactive_flg;

    /** [r]先頭ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが先頭ノードに移動する */
    bool _will_mv_first_in_next_frame_flg;
    /** [r]末尾ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが末尾ノードに移動する */
    bool _will_mv_last_in_next_frame_flg;

    bool _is_already_reset;

    GgafProgress* _pProg;

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
    virtual void clean(int prm_num_cleaning);

    /**
     * ノード初期処理(単体) .
     * インスタンス生成後、何れかが呼び出される前に、最初に必ず１回だけ呼び出される。<BR>
     * 補足：initialize()が呼び出された後、reset() が呼び出されます。
     */
    virtual void initialize() = 0;

    /**
     * ノードのフレームを加算と、フレーム開始にあたってのいろいろな初期処理(自ツリー) .
     * 様々な状態フラグの更新を主に行う <BR>
     * _is_active_flg_in_next_frame _was_paused_flg_in_next_frame _can_live_flg_in_next_frame を<BR>
     * _is_active_flg _was_paused_flg _can_live_flg に反映（コピー）する。<BR>
     * また、_will_mv_first_in_next_frame_flg, _will_mv_last_in_next_frame_flg が true の場合は、<BR>
     * それぞれ、自ノードの先頭ノードへの移動、末尾ノードへの移動処理も実行される。<BR>
     * その後、配下ノード全てに nextFrame() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して nextFrame() 実行後、次は behave() を実行することになる。<BR>
     * 次のような構造の場合、実行順は①～⑬の順序となる。<BR>
     * ノード間で参照関係がある場合は、注意が必要。<BR>
     * <pre>
     * (Ｐ)⇔①Ｐ⇔(Ｐ)
     *         ↓
     * (Ｅ)⇔②Ａ⇔⑥Ｂ⇔⑪Ｃ⇔⑫Ｄ⇔⑬Ｅ⇔(Ａ)
     *         │    └────────────┐
     *         ↓                              ↓
     * (Ｈ)⇔③Ｆ⇔④Ｇ⇔⑤Ｈ⇔(Ｆ)    (Ｌ)⇔⑦Ｉ⇔⑧Ｊ⇔⑨Ｋ⇔⑩Ｌ⇔(Ｉ)
     *
     * ※サブが存在すれば先に実行、存在しなければ次(隣)を実行。
     * <pre>
     * メソッド説明に『(自ツリー)』と記述されている場合は、全て上記の順序で実行される。
     */
    virtual void nextFrame();

    /**
     * ノードのフレーム毎の振る舞い処理(自ツリー) .
     * この処理では、全ノード座標移動処理を行うこととする。<BR>
     * 実行されるためのフラグの条件は、<BR>
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （ _is_active_flg && !_was_paused_flg && _can_live_flg ）の場合 <BR>
     * behave() は 仮想関数 processBehavior() をコールした後、配下のノード全てについて behave() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processBehavior() をオーバーライドして具体的な座標移動ロジックを実装する。 <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して behave() 実行後、次は settleBehavior() を実行することになる。<BR>
     */
    virtual void behave();

    /**
     * 非活動→活動時に切り替わった時の処理(単体) .
     * 非活動状態から活動状態に変化したときに、 behave() よりも前に１回コールバックされる。<BR>
     * 必要に応じてオーバーライドする。<BR>
     * ＜コールされるタイミング詳細＞
     * ①非活動→活動時に切り替わった時
     * nextFrame() 処理中、前フレームの状態フラグ「非活動状態」で、現フレームの状態フラグが「活動状態」となる場合、
     * nextFrame() 内で、現フレームの状態フラグを「活動状態」にし、フレーム加算した後 コールバック
     * ②生成後、１フレーム目の時
     * 実際には存在しない前フレーム(0フレーム目)の状態フラグを、生成後の初期値で「非活動状態」としている為。
     * 生成後、初めて nextFrame() 処理される場合、nextFrame() 内でコールバックされることになる。
     */
    virtual void onActive() {
    }

    /**
     * 活動→非活動時に切り替わった時の処理(単体) .
     * 活動状態から非活動状態に変化したときに１回コールバックされる。<BR>
     * 呼び出されるタイミングはフレーム加算直後である。通常 behave() よりも前に実行される。<BR>
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onInactive() {
    }

    /**
     * ノードのフレーム毎の振る舞い事後処理(自ツリー) .
     * この処理では、全ノード座標移動が完了していることが保証された後の処理を行う事とする設計。<BR>
     * 更新が完了した座標情報から、それに伴う内部の様々なステータス等の更新処理をここで行う事を目的とする<BR>
     * 実行されるためのフラグの条件は、behave()と同じく、活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット。<BR>
     * つまり ( _is_active_flg && !_was_paused_flg && _can_live_flg )の場合である。 <BR>
     * settleBehavior()は、仮想関数 processSettlementBehavior() をコールした後、配下のノード全てについて settleBehavior() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processSettlementBehavior() をオーバーライドしてロジックを実装することとする。 <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して settleBehavior() 実行後、次に judge() を実行することになる。<BR>
     */
    virtual void settleBehavior();


    /**
     * ノードのフレーム毎の判定処理(自ツリー) .
     * この処理では、ノード間の様々な判定処理を行う事とする設計。<BR>
     * 全ノード座標移動処理と伴なうステータス類の更新が完全に完了してが前提とする処理が行われる。<BR>
     * 実行されるためのフラグの条件は、behave()と同じく、<BR>
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * つまり ( _is_active_flg && !_was_paused_flg && _can_live_flg )の場合 <BR>
     * judge() は 仮想関数 processJudgement() をコールした後、配下のノード全てについて judge() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processJudgement() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して judge() 実行後、<BR>
     * 神(GgafGod)はこの後、次フレームまでの残時間に余裕があれば preDraw() 無ければ doFinally() を実行することになる。<BR>
     */
    virtual void judge();

    /**
     * ノードのフレーム毎の描画事前処理(自ツリー)（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、<BR>
     * (つまり _is_active_flg && _can_live_flg)の場合 <BR>
     * processPreDraw() をコールした後、配下のノード全てについて preDraw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processPreDraw() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して preDraw() 実行後、次に draw() を実行することになる。<BR>
     */
    virtual void preDraw();

    /**
     * ノードのフレーム毎の描画本処理(自ツリー)（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、<BR>
     * (つまり _is_active_flg && _can_live_flg)の場合 <BR>
     * processDraw() をコールした後、配下のノード全てについて draw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processDraw() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して draw() 実行後、次に afterDraw() を実行することになる。<BR>
     */
    virtual void draw();

    /**
     * ノードのフレーム毎の描画事後処理(自ツリー)（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット<BR>
     * (つまり _is_active_flg && _can_live_flg)の場合 <BR>
     * processAfterDraw() をコールした後、配下のノード全てについて afterDraw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processAfterDraw() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して afterDraw() 実行後、次に doFinally() を実行することになる。<BR>
     */
    virtual void afterDraw();

    /**
     * ノードのフレーム毎の最終処理(自ツリー) .
     * 座標移動処理、判定処理、描画処理が終了した後に、最後に行う後始末処理を行う事とする設計。<BR>
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （_is_active_flg && !_was_paused_flg && _can_live_flg）の場合 <BR>
     * processFinally() をコールした後、配下のノード全てについて doFinally() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processFinally() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して doFinally() 実行後、<BR>
     * 次フレームまでの残時間に余裕があれば clean() を実行する。<BR>
     * その後は nextFrame() を実行することになる。<BR>
     */
    virtual void doFinally();


    /**
     * フレーム毎の個別振る舞い処理を実装。(ユーザー実装用、単体) .
     * behave() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の振る舞いを処理を実装する。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理等である。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、nextFrame() が実行済みであることを保証する。<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * フレーム毎の個別振る舞い事後処理を実装。(フレームワーク実装用、単体) .
     */
    virtual void processSettlementBehavior() {}

    /**
     * フレーム毎の個別判断処理を実装。(ユーザー実装用、単体) .
     * judge() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数をオーバーライドして、ノード個別判断処理を記述する。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対してて、processBehavior() が実行済みであることを保証する。<BR>
     * 本メンバ関数の存在意図として、processBehavior() で座標移動処理が全て完了した後、
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
     * ノードのフレーム毎の個別描画本処理を実装。(フレームワーク実装用／ユーザー実装用、単体) .
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
     * ノードのフレーム毎の個別終端処理を実装。(ユーザー実装用、単体) .
     * doFinally() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の終端処理を実装する。<BR>
     * 終端処理とは、フラグ管理の実行などである。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理である。その他なんでも良いである。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processJudgement() が実行済みで 描画処理は終了していることを保証する。<BR>
     */
    virtual void processFinal() = 0;

    /**
     * 自ノードよりも親にあたるノード全てにイベントメッセージを通知します .
     * イベントを受け取る側は、onCatchEvent(UINT32, void) を実装が必要です。
     * @param prm_no イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void throwEventToLowerTree(UINT32 prm_no, void* prm_pSource = NULL);

    /**
     * 配下ノード全てにイベントメッセージを通知します .
     * イベントを受け取る側は、onCatchEvent(UINT32, void) を実装が必要です。
     * @param prm_no イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void throwEventToUpperTree(UINT32 prm_no, void* prm_pSource = NULL);


    /**
     * イベント発生時の処理 .
     * @param prm_no イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) = 0;


    virtual bool isDisappear();
    /**
     * 神に謁見 .
     * @return  呼ばれて出てきた神
     */
    virtual GgafGod* askGod() = 0;

    //==================状態遷移メソッド郡==================>
    /**
     * 活動状態にする(自ツリー・コールバック有り) .
     * 正確には、次フレームから活動状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で活動状態になる事とする。<BR>
     * 自身と配下ノード全てについて再帰的に activateTree() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * 自ノードの processBehavior() で 自身を activateTree() を呼び出すコードを書いても、タスクシステムの仕組み上、<BR>
     * processBehavior()は活動状態にのみ実行されるので、実行されることが無く意味が無い。<BR>
     * 他ノードへ実行したり、processFinal() などでの使用を想定。<BR>
     * <B>[補足]</B>ノード生成直後は、活動状態となっている。<BR>
     */
    virtual void activateTree();

    /**
     * 活動状態にする(単体・コールバック有り) .
     * 自ノードだけ次フレームから活動状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     */
    virtual void activate();

    /**
     * 活動状態にする(単体・コールバック有り).
     * 引数のフレーム数遅延して activate() が実行されます。<BR>
     * 自身と配下ノード全てについて再帰的に activateDelay(frame) が実行される。<BR>
     * activateDelay(1) は、activate() と同じ意味になります。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * @param prm_offset_frames 遅延フレーム数(1～)
     */
    virtual void activateDelay(frame prm_offset_frames = 1);


    virtual void activateTreeDelay(frame prm_offset_frames = 1);

    /**
     * 一定時間だけ活動状態にする(単体・コールバック有り).
     * 活動状態にした後、引数のフレーム数経過すると、非活動状態になります。
     * activateWhile(10); は
     * activate(); inactivateDelay(10); の実行と同等の効果です。
     * @param prm_offset_frames 活動フレーム
     */
    virtual void activateWhile(frame prm_frames = 1);

    /**
     * 活動状態にする(単体・即時・コールバック無し) .
     * 自ノードについて、即座に活動状態にする。初期化以外で本メソッドの使用は非推奨。<BR>
     * onActive() コールバックは実行されない。<BR>
     * 即座に状態が変化するため、初期化以外での使用時は以下の点を留意して、使用する際は注意が必要である。<BR>
     * 『同一フレーム内』の残りの未処理のノードに対して有効になってしまう。つまり、<BR>
     * 『同一フレーム内』であっても、既に処理されたノードとは異なる状態になる可能性が大きく、<BR>
     * 他ノードのロジックが、「このノードが活動状態ならば・・・」等、その状態（フラグ）により処理分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void activateImmediately();

    /**
     * 活動状態にする(自ツリー・即時・コールバック無し)
     * 自身と配下ノード全てについて再帰的に activateImmediately() が実行される。<BR>
     * activateImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void activateTreeImmediately();
    //===================
    /**
     * 非活動状態にする(自ツリー・コールバック有り) .
     * 自身と配下ノード全てについて、次フレームから非活動状態にする予約フラグを立てます。
     * 次フレームの内部先頭処理(nextFrame())内で完全に非活動状態となります。
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     * 自身と配下ノード全てについて再帰的に inactivate() が実行される事と同等です。<BR>
     */
    virtual void inactivateTree();

    /**
     * 非活動状態にする(単体・コールバック有り) .
     * 自ノードだけ次フレームから非活動状態にする予約フラグを立てます。
     * 次フレームの内部先頭処理(nextFrame())内で完全に非活動状態となります。
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     * 配下ノードには何も影響がありません。
     */
    virtual void inactivate();

    /**
     * 非活動予約する(自ツリー・コールバック有り) .
     * 引数のフレーム数遅延して inactivate() が実行されます。<BR>
     * 自身と配下ノード全てについて再帰的に inactivateDelay(UINT32) が実行される。<BR>
     * inactivateDelay(1) は、inactivate() と同じ意味になります。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     * @param prm_offset_frames 遅延フレーム数(1～)
     */
    virtual void inactivateDelay(frame prm_offset_frames = 1);



    virtual void inactivateTreeDelay(frame prm_offset_frames = 1);

    /**
     * 非活動状態にする(単体・即時・コールバック無し)  .
     * 自ノードについて、即座に非活動状態にする。初期化以外で、本メソッドの使用は非推奨。<BR>
     * onInactive() コールバックは実行されない。<BR>
     * 即座に状態が変化するため、初期化以外での使用時は以下の点を留意して、使用する際は注意が必要である。<BR>
     * 『同一フレーム内』の残りの未処理のノードに対してのみ有効となる。つまり、<BR>
     * 『同一フレーム内』であっても、既に処理されたノードとは異なる状態になる可能性が大きく、<BR>
     * 他ノードのロジックが、「このノードが非活動状態ならば・・・」等、その状態（フラグ）により処理分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void inactivateImmediately();

    /**
     * 非活動状態にする(自ツリー・即時・コールバック無し)  .
     * 自身と配下ノード全てについて再帰的に inactivateImmediately() が実行される。<BR>
     * inactivateImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void inactivateTreeImmediately();

    //===================
    /**
     * 一時停止にする(自ツリー) .
     * 正確には、次フレームから一時停止にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止になる事とする。<BR>
     * 自身と配下ノード全てについて再帰的に pause() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止の変化は無く一貫性は保たれる。<BR>
     */
    virtual void pauseTree();

    /**
     * 一時停止にする(単体) .
     * 自ノードだけ次フレームから一時停止にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     * 本メソッドを実行しても、『同一フレーム内』は一時停止の変化は無く一貫性は保たれる。<BR>
     */
    virtual void pause();

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
    virtual void pauseImmediately();

    /**
     * 一時停止状態にする(自ツリー・即時) .
     * 自身と配下ノード全てについて再帰的に pauseImmediately() が実行される。<BR>
     * pauseImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void pauseTreeImmediately();

    //===================
    /**
     * 一時停止状態を解除する(自ツリー) .
     * 正確には、次フレームから一時停止状態を解除する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止状態が解除される事になる。<BR>
     * 自身と配下ノード全てについて再帰的に unpause() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止状態を解除の変化は無く一貫性は保たれる。<BR>
     */
    virtual void unpauseTree();
    /**
     * 一時停止状態を解除する(単体) .
     * 自ノードだけ次フレームから一時停止状態を解除にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     * 本メソッドを実行しても、『同一フレーム内』は一時停止状態を解除の変化は無く一貫性は保たれる。<BR>
     */
    virtual void unpause();

    /**
     * 一時停止状態を解除する(自ツリー・即時) .
     * 自身と配下ノード全てについて再帰的に unpauseImmediately() が実行される。<BR>
     * unpauseImmediately() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void unpauseTreeImmediately();

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
    virtual void unpauseImmediately();
    //===================
    /**
     * 状態をリセットする .
     * 次のような動作を『即時』に行います（次フレームの先頭処理時ではありません）。<BR>
     * ① 同一フレーム内で、初めての呼び出しであるかチェック<BR>
     *   ・初めての呼び出しである。  → ②へ<BR>
     *   ・２回以上呼び出されている。→ 何もしないでreturn<BR>
     * ② 次の内部フレームカウンタをリセット<BR>
     *   ・getBehaveingFrame() を 0 にする。<BR>
     *   ・getActivePartFrame() を 0 にする。<BR>
     * ③ 下位実装処理の onReset() を呼び出します。<BR>
     * 補足:内部で initialize() 呼び出し直後に、１回だけ reset() は自動的に呼び出されます。<BR>
     * <pre>
     */
    virtual void reset();
    // ＜メモ initialize(), onReset(), onActive() の使い分けについて＞
    // 状態をリセット処理は、どこに実装するべきか？
    // initialize() ・・・ 生成後、最初の１回だけ事前にコールバックされる。初期化処理等に使用することを想定。
    // onReset()    ・・・ 生成後、initialize() の後、１回だけ無条件でコールされる。その後、reset() 実行ででコールバックされる。
    // onActive()   ・・・ 生成後、initialize() の後の活動状態時 １フレーム目の behave() 直前にコールされる。
    //                     その後 非活動→活動状態になった時、自動的にコールバックされる。
    // ノード(アクターやシーン)の処理サイクルによって使い分ける。
    //
    // ・１サイクルなノード(アクターやシーン)の場合
    // 生成後、初めての「終了」という状態を迎えた際に、そのまま解放となる場合。つまり、インスタンスを使いまわさない場合。
    // initialize(), onReset(), onActive() は事前に各１回実行されるので、どこに状態をリセット処理を実装しても差異は無いはず。
    // 多くの通常のアクターや、一時的な短いシーンはこれに該当すると予想する。
    // どこに実装しても良いが、initialize() で実装を統一したほうが、他のオブジェクトから操作しやすい。
    //
    // ・onActive() を使用すべき場合
    // 生成されたノードに、「表示」「非表示」という状態が存在し、使いまわす場合。
    // 表示(活動) ～ 非表示(非活動) が、ノードの１サイクルのと一致する場合。
    // initialize() ・・・ 初期化処理、
    // onActive()   ・・・ 状態リセット処理
    // と使い分けて記述し。 inacivate()、active() で状態リセット行う。
    // なぜ onReset() に状態リセット処理を記述し、reset()コールではいけないのかというと、
    // 処理の中心である processBehavior() メソッドは、非表示(非活動) はコールされないため、
    // 自身のオブジェクトの処理で reset() を記述しても実行されることが無いという自体に陥る。
    // もちろん、他のオブジェクトから、非表示(非活動)→表示(活動) をチェックし、reset() を実行してあげれば
    // 問題ないが、いつリセットされるのか、処理を追いかけないと分からないようになるというデメリットもあるのではないだろうか。
    // onActive() がコールされても、getBehaveingFrame() は「リセットされない」が、
    // getActivePartFrame()は「リセット」される事に注意。
    // 主に敵弾など汎用的なアクターは、これに該当すると予想する。
    //
    // ・onReset() を使用すべき場合
    // 生成されたノードに、「表示」「非表示」という概念が無い（或いは表示しっぱなし）で、
    // なおかつ、処理サイクル（リセット）の概念があるノード場合
    // initialize() ・・・ 初期化処理、
    // onReset()    ・・・ 状態リセット処理
    // と使い分けて記述し。 reset() で状態リセットを行う。
    // onReset() コールバック時は、内部フレームカウンタは「リセットされる」事に注意。
    // 主にシーンと、一部のアクターは、これに該当すると予想する。
    //
    // ・onActive() onReset() 複合して使用すべき場合。
    // 表示(活動) ～ 非表示(非活動) が、ノードの１サイクルと一致しない場合、
    // initialize() ・・・ 初期化処理、
    // onActive()   ・・・ 画面描画時初期化処理
    // onReset()    ・・・ 状態リセット処理
    // と使い分けて記述し。 inacivate()、activate() で reset() をコールしつつ。
    // reset() で状態リセットを行う。
    // 自機はこれに該当すると予想。
    //
    // ・initialize() onActive() onReset() どっちでもよい場合。
    // 表示(活動) ～ 非表示(非活動) が、ノードの生成～解放に一致する場合。
    // つまりリセットというか使い回す概念がないオブジェクトは、オブジェクトの初期化は
    // initialize() onActive() onReset() の何処に記述してもほぼ意味は同じである。
    // 生成から、表示(活動)までにタイムラグが在るならば、onActive() onReset() のどちらかに
    // 記述すべきか。


    /**
     * 状態をリセットする（自ツリー） .
     * 自ツリー全てのオブジェクトに対し reset() を『即時』実行します。
     */
    virtual void resetTree();

    /**
     * 状態をリセットする(ユーザー実装用) .
     * reset() 或いは、resetTree() を実行することで呼び出されます。
     * 個別のの状態リセット処理を、下位クラスでオーバーライドしてください。
     */
    virtual void onReset() {}


    /**
     * 終了します。(自ツリー) .
     * 自ノードを引数のフレーム後に「生存終了」状態にすることを宣言する。（終了フラグを立てる） <BR>
     * 自ツリーノード全て道連れで、終了(end())がお知らせが届く。<br>
     * 親ノードが終了すれば、子ノードも終了せざるを得ないからである。<BR>
     * 終了フラグは一度立てると元にもどせません。以降 end() を重ねて呼び出しても無視します。<BR>
     * 引数の猶予フレーム後に生存終了とする。<BR>
     * 「生存終了」とは具体的には、振る舞いフラグ(_is_active_flg)、生存フラグ(_can_live_flg) を、
     * 次フレームからアンセットする予約フラグを立てること事である。<BR>
     * _can_live_flg がアンセットされることにより、ゴミ箱(GgafGarbageBox) に所属することになる。<BR>
     * そして神(GgafGod)処理に余裕のある時を見計らい clean() メソッドにより、<BR>
     * GgafGarbageBoxが保持するGgafDisusedActor 配下ノードを delete することとなる。<BR>
     * したがって、本メンバ関数を実行して引数の猶予フレーム後になっても、まだdeleteは行なわれず、<BR>
     * GgafDisusedActor 配下に移るだけ。（タスクからは除外されている）。<BR>
     * 次フレーム以降でも直ぐには delete されるとは限らない。<BR>
     * インスタンスがすぐに解放されないことに注意せよ！（内部的なバグを生みやすい）。<BR>
     * @param prm_offset_frames 生存終了猶予フレーム(1～)
     */
    virtual void end(frame prm_offset_frames = 1);

    /**
     * 自ツリーノードを最終ノードに移動する(単体) .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの最終にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではない。<BR>
     */
    virtual void moveLast() override {
        _will_mv_last_in_next_frame_flg = true;
    }

    virtual void moveLastImmediately() {
        GGAF_NODE::moveLast();
    }
    /**
     * 自ツリーノードを先頭ノードに移動する(単体) .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの先頭にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではない。<BR>
     */
    virtual void moveFirst() override {
        _will_mv_first_in_next_frame_flg = true;
    }

    virtual void moveFirstImmediately() {
        GGAF_NODE::moveFirst();
    }
//    /**
//     * 所属ツリーから独立する(単体)
//     * extract() のラッパーで、生存確認のチェック付き。通常はこちらを使用する。
//     * @return  T* 脱退し独立した自ノードのポインタ
//     */
//    virtual T* extract() override;


    /**
     * 非活動から活動に切り替わったかどうか .
     * ただし、onActive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備した。<BR>
     * @return  bool true:切り替わった／false:切り替わっていない
     */
    virtual bool onChangeToActive();

    /**
     * 活動から停止に切り替わったかどうか .
     * ただし、onInactive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備した。<BR>
     * @return  bool true:切り替わった／false:切り替わっていない
     */
    virtual bool onChangeToInactive();

    /**
     * 生存可能か調べる
     * @return  bool true:生存可能／false:生存不可
     */
    virtual bool canLive() {
        return _can_live_flg;
    }

    /**
     * 活動中か調べる
     * @return  bool true:活動中／false:非活動中
     */
//    virtual bool isActive();

    /**
     * 振る舞い可能か調べる（＝一時停止されていないか）
     * @return  bool true:振る舞い可能（活動中で一時停止では無い）／false:振る舞い不可
     */
    virtual bool canBehave();

    /**
     */
    virtual bool wasPause();

    /**
     * 終了宣言したかどうか
     * @return
     */
    virtual bool wasDeclaredEnd();

    /**
     * 振る舞い状態に加算されるフレーム数を取得する .
     * 何もセットしない場合、次のような値を返す。<BR>
     * 1 Frame ～ からの値になる。0 Frame状態は基本存在しない。但し例外的に<BR>
     * 生成時コンストラクタ内、および、最初の initialize() 内では 0 Frame を返す。<BR>
     * 初回実行の onActive()、processBehavior()、processJudgement() 等の中で 1 になっている。<BR>
     * 以降、振る舞い態時にフレーム加算される。<BR>
     * 「振る舞い状態」とは、canBehave() == true の条件成立時の事を意味する。<BR>
     * @return 振る舞いフレーム数総計
     */
    virtual UINT32 getBehaveingFrame();

    /**
     * 振る舞い状態onActive()から開始した、振る舞い状態は何フレーム目かを返す。 .
     * 汎用オブジェクトなど、一度生成して使いまわす(deleteしない)場合、<BR>
     * 消失時に inactivate() 、 出現時 activate() を繰り返すことを想定。<BR>
     * getBehaveingFrame() と同じタイミングで加算される。processBehavior()では、1 ～ を返す。
     * onActive()コールバック条件成立時にリセットされる。<BR>
     * @return onActive()からの振る舞いフレーム数
     */
    virtual UINT32 getActivePartFrame();


    /**
     * 相対経過振る舞いフレームの判定。
     * 直前の relativeFrame(int) 実行時（結果がtrue/falseに関わらず）のフレーム数からの経過フレーム数に達したか判定する。
     * 初回呼び出しは、getBehaveingFrame() == ０からの相対フレーム数となるため、１度は空呼び出しを行う（なんとかしたい）事になるかもしれない。
     * 注意：入れ子や条件分岐により、relativeFrame(int) が呼び出される回数が変化する場合、相対経過フレームも変化する。
     * @param   prm_frameEnd    相対振る舞いフレーム数
     * @return  bool    true:経過フレーム数に達した/false:達していない
     */
    virtual bool relativeFrame(frame prm_frameEnd);




    /**
     * 配下全てのオブジェクトに対して指定の関数を実行させる .
     * 配下オブジェクト（アクターかシーン）のポインタが、引数関数ポインタの pFuncの第１引数に渡ってくる。<BR>
     * 引数関数ポインタの pFunc の第２引数には、executeFuncToLowerTree 呼び出し時の prm1(引数１)のポインタが渡ってくる。<BR>
     * 引数関数ポインタの pFunc の第３引数には、executeFuncToLowerTree 呼び出し時の prm2(引数２)のポインタが渡ってくる。<BR>
     * 配下のオブジェクトが何であるのか判っている上で使用しないと危険である。<BR>
     * あと、早くC++でラムダ式を使わせてください。<BR>
     *
     * ＜使用例＞<BR>
     * XXXXScene 配下のオブジェクト全てのアクター(但しGgafDxGeometricActor)のメンバ変数 _X に、
     * XXXXSceneメンバ変数 _velo の値を加算させる。<BR>
     * XXXXScene クラスの実装サンプルを以下に記す<BR>
     * <code><pre>
     *
     * class XXXXScene : public GgafScene {
     *
     *     int _velo;
     *
     *     static void addX(GgafObject* pThat, void* p1, void* p2) { //p1に_veloが渡る
     *         if (pThat->_obj_class >= Obj_GgafScene) {
     *             return; //シーンならば無視
     *         }
     *         GgafActor* pActor = (GgafActor*)pThat;
     *         if (pActor->_obj_class & Obj_GgafDxGeometricActor) {
     *             //GgafDxGeometricActorならば _X を加算
     *             ((GgafDxGeometricActor*)pActor)->_X += (*((int*)p1));
     *         }
     *     }
     *
     *     void processBehavior() {
     *         //配下アクター全てにaddX実行
     *         executeFuncToLowerTree(XXXXScene::addX, _velo, NULL);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc オブジェクトに実行させたい関数
     * @param prm1 同時に渡したい引数その１
     * @param prm2 同時に渡したい引数その２
     */
    virtual void executeFuncToLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2);


    virtual void useProgress(int prm_num = 10) {
        if (_pProg == NULL) {
            _pProg = NEW GgafProgress(&_frame_of_behaving, prm_num);
        } else {
            _TRACE_("["<<GGAF_NODE::getName()<<"] は既に useProgress しています。prm_num="<<prm_num);
        }
    }

};

///////////////////////////////////////////////////////////////// ここからは実装部

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : GgafCore::GgafNode<T>(prm_name),
_pGod(NULL),
_was_initialize_flg(false),
_frame_of_life(0),
_frame_of_behaving(0),
_frame_of_behaving_since_onActive(0),
_frameEnd(0),
_is_active_flg(true),
_was_paused_flg(false),
_can_live_flg(true),
//_is_active_flg_in_next_frame(true),
_was_paused_flg_in_next_frame(false),
//_can_live_flg_in_next_frame(true),
_will_end_after_flg(false),
_frame_of_life_when_end(MAXDWORD),
_will_activate_after_flg(false),
_frame_of_life_when_activation(0),
_will_inactivate_after_flg(false),
_frame_of_life_when_inactivation(0),
_on_change_to_active_flg(false),
_on_change_to_inactive_flg(false),
_will_mv_first_in_next_frame_flg(false),
_will_mv_last_in_next_frame_flg(false),
_is_already_reset(false),
_pProg(NULL)
{

}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _frame_of_behaving=" << _frame_of_behaving << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);
    _was_paused_flg  = _was_paused_flg_in_next_frame;
    if (_was_paused_flg) {
        return;
    }
    //moveLast予約時
    if (_will_mv_last_in_next_frame_flg) {
        _will_mv_last_in_next_frame_flg = false;
        GGAF_NODE::moveLast();
        return;
        //即returnする事は重要。nextFrame() 処理の２重実行をさけるため。
        //このノードは、末尾に回されているため、必ずもう一度 nextFrame() の機会が訪れる。
    }


    //終了の時か
    if (_will_end_after_flg && _frame_of_life_when_end == _frame_of_life+1) { //まだ _frame_of_life が進んで無いため+1
       // _is_active_flg_in_next_frame = false;
        _can_live_flg = false;
    }

    //_can_live_flg    = _can_live_flg_in_next_frame;

    _on_change_to_active_flg = false;
    _on_change_to_inactive_flg = false;
    _frame_of_life++;
    if (_can_live_flg) {

        if(_was_initialize_flg == false) {
            initialize();       //初期化
            _was_initialize_flg = true;
            reset(); //リセット
        }


        if (_is_active_flg && _frame_of_life == 1) {
            //生まれてそのままならば、いきなり一回だけonActive()。
            _on_change_to_active_flg = true;
            //フレーム加算してからonActive()
            _frame_of_behaving++;
            _frame_of_behaving_since_onActive = 1;
            onActive(); //コールバック
            _frame_of_life_when_activation = 0;
            _will_activate_after_flg = false;
        } else if (_will_activate_after_flg) {
            if (_is_active_flg) { //もともと活動中
                _frame_of_behaving++;
                _frame_of_behaving_since_onActive++;
            } else if(_frame_of_life == _frame_of_life_when_activation) {
                //activate処理
                if (_is_active_flg == false) {//_is_active_flg = false → true  時
                    _is_active_flg = true; //活動フラグON!!!
                    _on_change_to_active_flg = true;
                    //フレーム加算してからonActive()
                    _frame_of_behaving++;
                    _frame_of_behaving_since_onActive = 1;
                    onActive(); //コールバック
                    _frame_of_life_when_activation = 0;
                    _will_activate_after_flg = false;
                } else {                      //もともと活動中
                    _frame_of_behaving++;
                    _frame_of_behaving_since_onActive++;
                }
            }
        } else {
            _frame_of_behaving++;
            _frame_of_behaving_since_onActive++;
        }

        if (_will_inactivate_after_flg) {
            if (_frame_of_life == _frame_of_life_when_inactivation) {
                _frame_of_life_when_inactivation = 0;
                _will_inactivate_after_flg = false;
                //inactivate処理
                if (_is_active_flg == true) { //_is_active_flg = true → false 時
                    _is_active_flg = false;//活動フラグOFF!!!
                    _on_change_to_inactive_flg = true;
                    onInactive(); //コールバック

                } else {
                    //もともと非活動中
                }
            } else {

            }
        }
        _is_already_reset = false;
    }

    //配下のnextFrame()実行
    if (GGAF_NODE::_pSubFirst) {
        T* pElementTemp = GGAF_NODE::_pSubFirst;
        while(true) {

            if (pElementTemp->_is_last_flg) {
                pElementTemp->nextFrame();
                if (pElementTemp->_can_live_flg == false) {
                    GgafFactory::_pGarbageBox->add(pElementTemp); //ゴミ箱へ
                }
                break;
            } else {
                pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                pElementTemp->GGAF_NODE::_pPrev->nextFrame();
                if (pElementTemp->GGAF_NODE::_pPrev->_can_live_flg == false) {
                    GgafFactory::_pGarbageBox->add(pElementTemp->GGAF_NODE::_pPrev); //ゴミ箱へ
                }
            }
        }
    }


    if (_will_mv_first_in_next_frame_flg) {
        _will_mv_first_in_next_frame_flg = false;
        GGAF_NODE::moveFirst();
        //moveFirstを一番最後にすることは重要。
        //これは nextFrame() の２重実行を避けるため。
    }

    // 進捗を反映
    if (_pProg) {
        _pProg->update();
    }
    TRACE("GgafElement::nextFrame END _frame_of_behaving="<<_frame_of_behaving<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processBehavior();    //ユーザー実装用
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::settleBehavior() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    //if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processSettlementBehavior(); //フレームワーク用
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->settleBehavior();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}


template<class T>
void GgafElement<T>::judge() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processJudgement();    //ユーザー実装用
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::preDraw() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processPreDraw();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->preDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::draw() {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processDraw();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->draw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::afterDraw() {
    if (_is_active_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processAfterDraw();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->afterDraw();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}


template<class T>
void GgafElement<T>::doFinally() {
//    if(_was_initialize_flg == false) {
//        initialize();
//        _was_initialize_flg = true;
//    }

    if (_is_active_flg && !_was_paused_flg && _can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            processFinal();
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->doFinally();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::reset() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //初期化
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            _frame_of_behaving = 0;
            _frame_of_behaving_since_onActive = 0;
            onReset();
            _is_already_reset = true;
        }
    }
}


template<class T>
void GgafElement<T>::resetTree() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //初期化
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            _frame_of_behaving = 0;
            _frame_of_behaving_since_onActive = 0;
            onReset();
            _is_already_reset = true;
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->resetTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activate() {
    if (_can_live_flg) {
        activateDelay(1);
    }
}

template<class T>
void GgafElement<T>::activateTree() {
    if (_can_live_flg) {
        activateDelay(1);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateImmediately() {
    if (_can_live_flg) {
        _is_active_flg = true;
    }
}

template<class T>
void GgafElement<T>::activateTreeImmediately() {
    if (_can_live_flg) {
        activateImmediately();
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::activateDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        //既にinactivateDelay()実行済みの場合は
        //そのinactivateDelay()は無効化される。
        _will_inactivate_after_flg = false;

        //既にactivateDelay()実行済みの場合は、今回指定算フレームで上書きする（後勝ち）。
        //(※inactivateDelay() と優先の考えが違うため注意)
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + prm_offset_frames;
    }
}
template<class T>
void GgafElement<T>::activateWhile(frame prm_frames) {
    if (_can_live_flg) {
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + 1;
        _will_inactivate_after_flg = true;
        _frame_of_life_when_inactivation = _frame_of_life + prm_frames;
    }
}


template<class T>
void GgafElement<T>::activateTreeDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        activateDelay(prm_offset_frames);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->activateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivate() {
    if (_can_live_flg) {
        inactivateDelay(1);
    }
}

template<class T>
void GgafElement<T>::inactivateTree() {
    if (_can_live_flg) {
        inactivateDelay(1);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        if (_will_activate_after_flg) {
            //既にactivateDelay()実行済みの場合
            if (_frame_of_life_when_activation >= _frame_of_life + prm_offset_frames) {
                //inactive 予定よりも後に active 予定ならば、(activeにはならないため)無効にする。
                _will_activate_after_flg = false;
            }
        }

        if (_will_inactivate_after_flg) {
            //既にinactivateDelay()実行済みの場合、より早く inactivate するならば上書きする
            if (_frame_of_life_when_inactivation < _frame_of_life + prm_offset_frames) {
                //今回指定算フレームの方が遅い場合は無視される。
                return;
            }
        }
        _will_inactivate_after_flg = true;
        _frame_of_life_when_inactivation = _frame_of_life + prm_offset_frames;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeDelay(frame prm_offset_frames) {
    if (_can_live_flg) {
        inactivateDelay(prm_offset_frames);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeDelay(prm_offset_frames);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactivateImmediately() {
    if (_can_live_flg) {
        _is_active_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeImmediately() {
    if (_can_live_flg) {
        inactivateImmediately();
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->inactivateTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
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
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->pauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
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
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->pauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
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
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTree();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
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
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->unpauseTreeImmediately();
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
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
void GgafElement<T>::end(frame prm_offset_frames) {
    if (_will_end_after_flg) {
        //既にend()実行済みの場合、より早くend()するならば有効とする
        if (_frame_of_life_when_end < _frame_of_life + prm_offset_frames + GGAF_SAYONARA_DELAY) {
            //今回指定の方が遅いフレーム指定であるため無視する。
            return;
        }
    }
    _will_end_after_flg = true;
    _frame_of_life_when_end = _frame_of_life + prm_offset_frames + GGAF_SAYONARA_DELAY;
    inactivateDelay(prm_offset_frames); //指定フレームにはinactivateが行われる
    if (GGAF_NODE::_pSubFirst) {
        T* pElementTemp = GGAF_NODE::_pSubFirst;
        while(true) {
            if (prm_offset_frames > 2) {
                pElementTemp->end(prm_offset_frames-1); //出来るだけ末端からendする
            } else {
                pElementTemp->end(prm_offset_frames);
            }
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->GGAF_NODE::_pNext;
            }
        }
    }
}


//template<class T>
//bool GgafElement<T>::isActive() {
//    if (_can_live_flg && _is_active_flg) {
//        return true;
//    } else {
//        return false;
//    }
//}

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
bool GgafElement<T>::canBehave() {
    if (_can_live_flg && _is_active_flg && !_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}


template<class T>
bool GgafElement<T>::wasPause() {
    if (_was_paused_flg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::wasDeclaredEnd() {
    if (_will_end_after_flg || _can_live_flg == false) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(frame prm_frameEnd) {
    if (_frame_of_behaving == _frameEnd) {
        _frameEnd += prm_frameEnd;
        return true;
    } else {
        return false;
    }
}


//template<class T>
//T* GgafElement<T>::extract() {
//    if (_can_live_flg) {
//        return GGAF_NODE::extract();
//    } else {
//        //_TRACE_("[GgafElement<"<<GGAF_NODE::_class_name<<">::extract()] ＜警告＞ "<<GGAF_NODE::getName()<<"は、死んでいます。");
//        return GGAF_NODE::extract();
//    }
//}

template<class T>
void GgafElement<T>::clean(int prm_num_cleaning) {
    if (GGAF_NODE::_pSubFirst == NULL) {
        return;
    }

    T* pElementTemp = GGAF_NODE::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafFactory::_cnt_cleaned < prm_num_cleaning) {

        if (pElementTemp->_pSubFirst) {
            //子の子がまだのっている場合さらにもぐる
            pElementTemp->clean(prm_num_cleaning);
            if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }

        if (pElementTemp->_is_first_flg) { //最後の一つ
            if (pElementTemp->_pSubFirst) {
                //子の子がまだのっている場合さらにもぐる
                pElementTemp->clean(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pElementTemp);
                GgafFactory::_cnt_cleaned++;
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //子の子がまだのっている場合さらにもぐる
                pWk->clean(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_can_live_flg == false) {
                DELETE_IMPOSSIBLE_NULL(pWk);
                GgafFactory::_cnt_cleaned++;
            }
        }
    }
}


template<class T>
UINT32 GgafElement<T>::getBehaveingFrame() {
   return _frame_of_behaving;
}

template<class T>
UINT32 GgafElement<T>::getActivePartFrame() {
   return _frame_of_behaving_since_onActive;
}
template<class T>
void GgafElement<T>::executeFuncToLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    if (_can_live_flg) {
        if (_was_initialize_flg) {
            pFunc(this, prm1, prm2);
        }
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->executeFuncToLowerTree(pFunc, prm1, prm2);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventToLowerTree(UINT32 prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        _frameEnd = 0;
        onCatchEvent(prm_no, prm_pSource);
        if (GGAF_NODE::_pSubFirst) {
            T* pElementTemp = GGAF_NODE::_pSubFirst;
            while(true) {
                pElementTemp->throwEventToLowerTree(prm_no, this);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->GGAF_NODE::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventToUpperTree(UINT32 prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        if (_was_initialize_flg) {
            _frameEnd = 0;
            onCatchEvent(prm_no, prm_pSource);
        }
        if (GGAF_NODE::_pParent) {
            T* pElementTemp = GGAF_NODE::_pParent;
            pElementTemp->throwEventToUpperTree(prm_no, this);
        } else {
            //てっぺん
        }
    }
}


template<class T>
bool GgafElement<T>::isDisappear() {
    if (_is_active_flg == false) {
//    if (_will_inactivate_after_flg ||
//        _is_active_flg_in_next_frame == false ||
//        _will_end_after_flg ) {
        return true;
    } else {
        return false;
    }
}


template<class T>
GgafElement<T>::~GgafElement() {
    DELETE_POSSIBLE_NULL(_pProg);
}

}
#endif /*GGAFELEMENT_H_*/
