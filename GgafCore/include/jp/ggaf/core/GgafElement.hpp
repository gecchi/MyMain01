#ifndef GGAFELEMENT_H_
#define GGAFELEMENT_H_
namespace GgafCore {

#define SUPER GgafCore::GgafNode<T>

/**
 * GgafNodeに、タスクシステム及び様々な状態管理（フラグ管理）を追加。 .
 * 毎フレーム、を神(GgafGod)は世界(GgafWorld)に、次のメソッド順で呼び出す仕組みになっている。世界(GgafWorld)も本templateを実装している。<BR>
 * nextFrame() > behave() > judge() > [drawPrior() > drawMain() > drawTerminate()] > finally() <BR>
 * 上記の内、nextFrame()、finally() は毎フレーム実行される。<BR>
 * behave()、judge() は活動状態フラグ(_isActiveFlg)が true、かつ、一時停止フラグ(_wasPausedFlg)が false の場合実行される。<BR>
 * drawPrior()、drawMain()、drawTerminate() は、次フレームまでの残時間に余裕があり、かつ一時非表示フラグ(_wasBlindedFlg) が false の場合<BR>
 * 実行される。次フレームまでの残時間に余裕が無い場合、神はこの３メソッドをスキップするが、MAX_SKIP_FRAME フレームに１回は実行する。<BR>
 * 上記の nextFrame() 〜 finally() のオーバーライドは非推奨。オーバーライド用に純粋仮想(processXxxxxx()) を用意している。<BR>
 * initialize() は、上記の nextFrame() 〜 finally() を何れかを呼び出す前にインスタンスごとに１回だけ呼ばれる仕組みになっている。<BR>
 * 但し、生存フラグ(_isAliveFlg)がfalseの場合（deleteされる）は、nextFrame() 〜 finally() は全て実行されない。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

protected:

    /** 神への近道 */
    GgafGod* _pGod;
    /** initializeが行われたどうかのフラグ(true=行われた) */
    bool _wasInitializedFlg;

public:
    /** 余命 */
    DWORD _dwGodFrame_ofDeath;
    /** ノードが誕生(addSubされた）時からのフレーム */
    DWORD _dwFrame;
    /** 相対フレーム計算用 */
    DWORD _dwFrame_relative;
    /** ノード活動フラグ */
    bool _isActiveFlg;
    /** 一時停止フラグ */
    bool _wasPausedFlg;
    /** 一時非表示フラグ */
    bool _wasBlindedFlg;
    /** ノード生存フラグ */
    bool _isAliveFlg;

    /** 次フレームノード活動予約フラグ、次フレームのフレーム加算時 _isActiveFlg に反映される */
    bool _willActNextFrameFlg;
    /** 次フレーム一時停止予約フラグ、次フレームのフレーム加算時 _wasPausedFlg に反映される */
    bool _willPauseNextFrameFlg;
    /** 次フレーム一時非表示予約フラグ、次フレームのフレーム加算時 _wasBlindedFlg に反映される  */
    bool _willBlindNextFrameFlg;
    /** 次フレーム生存予約フラグ、次フレームのフレーム加算時 _isAliveFlg に設定される */
    bool _willBeAliveNextFrameFlg;

    /** 先頭ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが先頭ノードに移動する */
    bool _willMoveFirstNextFrameFlg;
    /** 末尾ノードに移動予約フラグ、次フレームのフレーム加算時に、自ノードが末尾ノードに移動する */
    bool _willMoveLastNextFrameFlg;

    /** あとで活動予約フラグ */
    bool _willActAfterFrameFlg;
    /** あとで活動までの残フレーム数（神フレームと一致したら活動） */
    DWORD _dwGodFremeWhenAct;

    /** あとで非活動予約フラグ */
    bool _willInactAfterFrameFlg;
    /** あとで停止の残フレーム数（神フレームと一致したら停止） */
    DWORD _dwGodFremeWhenInact;

    /** ノードが活動に切り替わった(_isActiveFlg が false → true)瞬間に１フレームだけセットされるフラグ */
    bool _switchedToActFlg;
    /** ノードが停止に切り替わった(_isActiveFlg が true → false)瞬間に１フレームだけセットされるフラグ */
    bool _switchedToInactFlg;

    /** 描画されましたフラグ */
    bool _wasExecutedProcessDrawMainFlg;

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
     * 神が処理時間に余裕がでたとき等に呼ばれる。<BR>
     * 配下ノードの中にノード生存フラグ(_isAliveFlg)が false になっているノードがあれば prm_num_cleaning 個だけ delete する。<BR>
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
     * _willActNextFrameFlg, _willPauseNextFrameFlg, _willBlindNextFrameFlg, _willBeAliveNextFrameFlg を<BR>
     * _isActiveFlg, _wasPausedFlg, _wasBlindedFlg, _isAliveFlg に反映（コピー）する。<BR>
     * また、_willMoveFirstNextFrameFlg, _willMoveLastNextFrameFlg が true の場合は、<BR>
     * それぞれ、自ノードの先頭ノードへの移動、末尾ノードへの移動処理も実行される。<BR>
     * その後、配下ノード全てに nextFrame() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、behave()を実行する。<BR>
     */
    virtual void nextFrame();

    /**
     * ノードのフレーム毎の振る舞い処理 .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （_isActiveFlg && !_wasPausedFlg && _isAliveFlg）の場合 <BR>
     * processBehavior() をコールした後、配下のノード全てについて behave() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、judge()を実行する。<BR>
     */
    virtual void behave();

    /**
     * 非活動→活動時に切り替わった時の処理 .
     * 非活動状態から活動状態に変化したときに１回コールバックされる。<BR>
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onAct() {
    }

    /**
     * 活動→非活動時に切り替わった時の処理 .時処理 .
     * 活動状態から非活動状態に変化したときに１回コールバックされる。<BR>
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onInact() {
    }

    /**
     * ノードのフレーム毎の判定処理 .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * (つまり _isActiveFlg && !_wasPausedFlg && _isAliveFlg)の場合 <BR>
     * processJudgement() をコールした後、配下のノード全てについて judge() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、次フレームまでの残時間に余裕があれば drawPrior()、
     * 無ければ finally()を実行する。<BR>
     */
    virtual void judge();

    /**
     * ノードのフレーム毎の描画事前処理（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
     * (つまり _isActiveFlg && !_wasBlindedFlg && _isAliveFlg)の場合 <BR>
     * processDrawPrior() をコールした後、配下のノード全てについて drawPrior() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、drawMain() を実行する。<BR>
     */
    virtual void drawPrior();

    /**
     * ノードのフレーム毎の描画本処理（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
     * (つまり _isActiveFlg && !_wasBlindedFlg && _isAliveFlg)の場合 <BR>
     * processDrawMain() をコールした後、配下のノード全てについて drawMain() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、drawTerminate() を実行する。<BR>
     */
    virtual void drawMain();

    /**
     * ノードのフレーム毎の描画事後処理（フレームスキップされて呼び出されない場合もある。） .
     * 活動フラグ、生存フラグがセット、かつ一時非表示フラグがアンセット<BR>
     * (つまり _isActiveFlg && !_wasBlindedFlg && _isAliveFlg)の場合 <BR>
     * processTerminate() をコールした後、配下のノード全てについて drawTerminate() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、finally() を実行する。<BR>
     */
    virtual void drawTerminate();

    /**
     * ノードのフレーム毎の最終処理 .
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （_isActiveFlg && !_wasPausedFlg && _isAliveFlg）の場合 <BR>
     * processFinally() をコールした後、配下のノード全てについて finally() を再帰的に実行する。<BR>
     * 神(GgafGod)は、世界(GgafWorld)に対して本メンバ関数実行後、次フレームまでの残時間に余裕があれば cleane() を実行する。<BR>
     */
    virtual void finally();

    /**
     * ノードの何かの処理(フレーム毎ではない) .
     * 活動フラグがセット、(つまり _isActiveFlg)の場合 <BR>
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
     * 自身と配下ノード全てについて再帰的に act() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * 自ノードの processBehavior() で本メソッドを呼び出すコードを書いても、タスクシステムの仕組み上、<BR>
     * 実行されることは無いので、他ノードから実行したり、processFinal() などでの使用を想定。<BR>
     * <B>[補足]</B>ノード生成直後は、活動状態となっている。<BR>
     */
    void act();
    /**
     * 活動予約する(自ツリー) .
     * Nフレーム後に act() が実行されることを予約する。<BR>
     * 自身と配下ノード全てについて再帰的に actAfter(DWORD) が実行される。<BR>
     * actAfter(1) は、act() と同じ意味になります。<BR>
     * @param prm_dwFrameOffset 遅延フレーム数(1〜)
     */
    void actAfter(DWORD prm_dwFrameOffset);
    /**
     * 活動状態にする(単体) .
     * 自ノードだけ次フレームから活動状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void actAlone();
    /**
     * 活動状態にする(自ツリー・即時) .
     * 正確には、活動フラグを即座に立てる。<BR>
     * 自身と配下ノード全てについて再帰的に actImmediately() が実行される。<BR>
     * 他のノードからの、「活動状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、actImmediately() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void actImmediately();
    /**
     * 活動状態にする(単体・即時) .
     * 自ノードのみについて、活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void actImmediatelyAlone();
    //===================
    /**
     * 非活動状態にする(自ツリー) .
     * 正確には、次フレームから非活動状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で非活動状態になる事になります。<BR>
     * 自身と配下ノード全てについて再帰的に inact() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非活動状態の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void inact();
    /**
     * 非活動予約する(自ツリー) .
     * Nフレーム後に inact() が実行されることを予約する。<BR>
     * 自身と配下ノード全てについて再帰的に inactAfter(DWORD) が実行される。<BR>
     * inactAfter(1) は、inact() と同じ意味になります。<BR>
     * @param prm_dwFrameOffset 遅延フレーム数(1〜)
     */
    void inactAfter(DWORD prm_dwFrameOffset);
    /**
     * 非活動状態にする(単体) .
     * 自ノードだけ次フレームから非活動状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void inactAlone();
    /**
     * 非活動状態にする(自ツリー・即時) .
     * 正確には、活動フラグを即座に下げる。<BR>
     * 自身と配下ノード全てについて再帰的に inactImmediately() が実行される。<BR>
     * 他のノードからの、「非活動状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、inactImmediately() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void inactImmediately();
    /**
     * 非活動状態にする(単体・即時) .
     * 自ノードのみについて、非活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void inactImmediatelyAlone();
    //===================
    /**
     * 一時停止にする(自ツリー) .
     * 正確には、次フレームから一時停止にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止になる事になります。<BR>
     * 自身と配下ノード全てについて再帰的に pause() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void pause();
    /**
     * 一時停止にする(単体) .
     * 自ノードだけ次フレームから一時停止にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void pauseAlone();
    /**
     * 一時停止にする(自ツリー・即時) .
     * 正確には、一時停止フラグを即座に立てる。<BR>
     * 自身と配下ノード全てについて再帰的に pauseImmediately() が実行される。<BR>
     * 他のノードからの、「一時停止ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、pauseImmediately() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void pauseImmediately();
    /**
     * 一時停止にする(単体・即時) .
     * 自ノードのみについて、一時停止フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void pauseImmediatelyAlone();
    //===================
    /**
     * 一時停止状態を解除にする(自ツリー) .
     * 正確には、次フレームから一時停止状態を解除する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で一時停止状態が解除される事になります。<BR>
     * 自身と配下ノード全てについて再帰的に unpause() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は一時停止状態を解除の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void unpause();
    /**
     * 一時停止状態を解除にする(単体) .
     * 自ノードだけ次フレームから一時停止状態を解除にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void unpauseAlone();
    /**
     * 一時停止状態を解除する(自ツリー・即時) .
     * 正確には、一時停止状態フラグを即座に下げる。<BR>
     * 自身と配下ノード全てについて再帰的に unpauseImmediately() が実行される。<BR>
     * 他のノードからの、「一時停止状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、unpauseImmediately() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void unpauseImmediately();
    /**
     * 一時停止状態を解除にする(単体・即時) .
     * 自ノードのみについて、非活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void unpauseImmediatelyAlone();
    //===================
    /**
     * 非表示状態にする(自ツリー) .
     * 正確には、次フレームから非表示状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で非表示状態になる事になります。<BR>
     * 自身と配下ノード全てについて再帰的に blind() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非表示状態の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     * <B>[補足]</B>ノード生成直後は、非表示状態となっている。<BR>
     */
    void blind();
    /**
     * 非表示状態にする(単体) .
     * 自ノードだけ次フレームから非表示状態にする予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void blindAlone();
    /**
     * 非表示状態にする(自ツリー・即時) .
     * 正確には、非活動フラグを即座に立てる。<BR>
     * 自身と配下ノード全てについて再帰的に blindImmediately() が実行される。<BR>
     * 他のノードからの、「非表示状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、blindImmediately() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void blindImmediately();
    /**
     * 非表示状態にする(単体・即時) .
     * 自ノードのみについて、非活動フラグを即座に立てる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void blindImmediatelyAlone();
    //===================
    /**
     * 非表示状態を解除にする(自ツリー) .
     * 正確には、次フレームから非表示状態を解除する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理で非表示状態が解除される事になります。<BR>
     * 自身と配下ノード全てについて再帰的に unblind() が実行される。<BR>
     * 本メソッドを実行しても、『同一フレーム内』は非表示状態の変化は無く一貫性は保たれる。<BR>
     * 他ノードに対して使用したり、processFinal() などでの使用を想定。<BR>
     */
    void unblind();
    /**
     * 非表示状態を解除にする(単体) .
     * 自ノードだけ次フレームから非表示状態を解除する予約フラグを立てる。<BR>
     * 配下ノードには何も影響がありません。
     */
    void unblindAlone();
    /**
     * 非表示状態を解除する(自ツリー・即時) .
     * 正確には、非表示フラグを即座に下げる。<BR>
     * 自身と配下ノード全てについて再帰的に unblindImmediately() が実行される。<BR>
     * 他のノードからの、「非表示状態ならば・・・処理」という判定を行なっている場合、<BR>
     * 使用には注意が必要。なぜならば、unblindImmediately() を実行する前と実行した後で<BR>
     * 『同一フレーム内』で、状態が変化するためである。他のノードからの参照するタイミングによっては<BR>
     * 同一フレームであるにもかかわらず、異なった状態判定になるかもしれない。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void unblindImmediately();
    /**
     * 非表示状態を解除する(単体・即時) .
     * 自ノードのみについて、非表示状フラグを即座に下げる。<BR>
     * 『同一フレーム内』で、状態が変化するためである。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    void unblindImmediatelyAlone();
    //===================
    /**
     * 自ノードを次フレームから絶命させることを宣言する .
     * 配下ノード全てに生存終了(farewell())がお知らせが届く。<BR>
     * 絶命させるとは具体的には、表示フラグ(_wasBlindedFlg)、振る舞いフラグ(_isActiveFlg)、生存フラグ(_isAliveFlg) を <BR>
     * 次フレームからアンセットする事である。<BR>
     * これにより、神(GgafGod)が処理時間の余裕のある時に実行される cleane() メソッドにより delete の対象となる。<BR>
     * したがって、本メンバ関数を実行しても、『同一フレーム内』ではインスタンスがすぐに解放されません。<BR>
     */
    void farewell(DWORD prm_dwFrameOffset = 0);

    /**
     * 自ツリーノードを最終ノードに移動する .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの最終にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではありません。<BR>
     */
    void moveLast();
    /**
     * 自ツリーノードを先頭ノードに移動する .
     * 次フレームの先頭処理(nextFrame())で自ツリーノードを兄弟ノードグループの先頭にシフトする。<BR>
     * <B>[注意]</B>即座に順繰り処理が実行されるわけではありません。<BR>
     */
    void moveFirst();

    /**
     * 所属ツリーから独立する
     * @return  T* 脱退し独立した自ノードのポインタ
     *
     */
    T* becomeIndependent();

    /**
     * 生存可能か調べる
     * @return  bool true:生存可能／false:生存不可
     */
    bool isAlive();

    /**
     * 活動中か調べる
     * @return  bool true:活動中／false:非活動中
     */
    bool isPlaying();

    /**
     * 非活動から活動に切り替わったかどうか .
     * ただし、onAct() で代用できる場合は、そちらをオーバーライドしたほうがすっきり記述できるはず。
     * @return  bool true:切り替わった／false:切り替わっていない
     */
    bool switchedToAct();

    /**
     * 活動から停止に切り替わったかどうか .
     * このメソッドは今のところ使いどころは無いかもしれません。
     * @return  bool true:切り替わった／false:切り替わっていない
     */
    bool switchedToInact();

    /**
     * 活動しているか
     * @return  bool true:活動可能／false:活動不可
     */
    bool isBehaving();

    /**
     * 描画するかどうか調べる（非表示でないかどうか）
     * @return  bool true:描画できる／false:描画はしない
     */
    bool canDraw();

    /**
     * ノードの現在の経過フレームを取得する
     */
    DWORD getFrame();

    /**
     * 相対経過フレームの判定。
     * 直前の relativeFrame(int) 実行時（結果がtrue/falseに関わらず）のフレーム数からの経過フレーム数に達したか判定する。
     * 注意：入れ子や条件分岐により、relativeFrame(int) が呼び出される回数が変化する場合、相対経過フレームも変化する。
     * @param   prm_dwFrame_relative    経過フレーム数
     * @return  bool    true:経過フレーム数に達した/false:達していない
     */
    bool relativeFrame(DWORD prm_dwFrame_relative);

};

///////////////////////////////////////////////////////////////// ここからは実装部

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : SUPER(prm_name),
            _pGod(NULL), _wasInitializedFlg(false), _dwGodFrame_ofDeath(MAXDWORD), _dwFrame(0),
            _dwFrame_relative(0), _isActiveFlg(true), _wasPausedFlg(false), _wasBlindedFlg(false), _isAliveFlg(true),
            _willActNextFrameFlg(true), _willPauseNextFrameFlg(false), _willBlindNextFrameFlg(false),
            _willBeAliveNextFrameFlg(true), _willMoveFirstNextFrameFlg(false), _willMoveLastNextFrameFlg(false),
            _willActAfterFrameFlg(false), _dwGodFremeWhenAct(0), _willInactAfterFrameFlg(false), _dwGodFremeWhenInact(0),
            _switchedToActFlg(false), _switchedToInactFlg(false), _wasExecutedProcessDrawMainFlg(false) {
}

template<class T>
void GgafElement<T>::nextFrame() {
    TRACE("GgafElement::nextFrame BEGIN _dwFrame=" << _dwFrame << " name=" << GgafNode<T>::_name << " class="
            << GgafNode<T>::_class_name);

    //死の時か
    if (_dwGodFrame_ofDeath == (askGod()->_dwFrame_God)) {
        _willActNextFrameFlg = false;
        _willBeAliveNextFrameFlg = false;
    }


    if (_willMoveLastNextFrameFlg) {
        _willMoveLastNextFrameFlg = false;
        SUPER::moveLast();
    } else {

        if(_wasInitializedFlg == false) {
            initialize();
            _wasInitializedFlg = true;
        }

        _wasExecutedProcessDrawMainFlg = false; //未描画に

        if (_isAliveFlg) {
            if (_willActAfterFrameFlg) {
                //遅延play処理
                if (askGod()->_dwFrame_God >= _dwGodFremeWhenAct) {
                    actImmediately();
                    _dwGodFremeWhenAct = 0;
                    _willActAfterFrameFlg = false;
                }
            } else if (_willInactAfterFrameFlg) {
                //遅延stop処理
                if (askGod()->_dwFrame_God == _dwGodFremeWhenInact) {
                    inactImmediately();
                    _dwGodFremeWhenInact = 0;
                    _willInactAfterFrameFlg = false;
                }
            }
            if (_isActiveFlg) {
                _dwFrame++;
            }
        }

        //活動、非活動の状態変化時
        if (_isActiveFlg == false && _willActNextFrameFlg) {
            _switchedToActFlg = true;
        } else if (_isActiveFlg && _willActNextFrameFlg == false) {
            _switchedToInactFlg = true;
        } else {
            _switchedToActFlg = false;
            _switchedToInactFlg = false;
        }
        //フラグたちを反映
        _isActiveFlg   = _willActNextFrameFlg;
        _wasPausedFlg  = _willPauseNextFrameFlg;
        _wasBlindedFlg = _willBlindNextFrameFlg;
        _isAliveFlg    = _willBeAliveNextFrameFlg;

        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                if (pElementTemp->_isLastFlg) {
                    pElementTemp->nextFrame();
                    if (pElementTemp->_isAliveFlg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp);
                    }
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                    pElementTemp->SUPER::_pPrev->nextFrame();
                    if (pElementTemp->SUPER::_pPrev->_isAliveFlg == false) {
                        GgafFactory::_pGarbageBox->add(pElementTemp->SUPER::_pPrev);
                    }
                }
            }
        }

        if (_willMoveFirstNextFrameFlg) {
            _willMoveFirstNextFrameFlg = false;
            SUPER::moveFirst();
        }

    }
    TRACE("GgafElement::nextFrame END _dwFrame="<<_dwFrame<<" name="<<GgafNode<T>::_name<<" class="<<GgafNode<T>::_class_name);
}

template<class T>
void GgafElement<T>::behave() {
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    //活動、非活動の状態変化時コールバック
    if (_switchedToActFlg) {
        onAct();
    } else if (_switchedToInactFlg) {
        onInact();
    }

    if (_isActiveFlg && !_wasPausedFlg && _isAliveFlg) {
        _dwFrame_relative = 0;
        processBehavior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->behave();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasPausedFlg && _isAliveFlg) {
        _dwFrame_relative = 0;
        processJudgement();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->judge();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasBlindedFlg && _isAliveFlg) {
        _dwFrame_relative = 0;
        processDrawPrior();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawPrior();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasBlindedFlg && _isAliveFlg) {
        _dwFrame_relative = 0;
        if (!_wasExecutedProcessDrawMainFlg) {
            processDrawMain();
            _wasExecutedProcessDrawMainFlg = true;
        }
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawMain();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasBlindedFlg && _isAliveFlg) {
        _dwFrame_relative = 0;
        processDrawTerminate();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->drawTerminate();
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isAliveFlg) {
        _dwFrame_relative = 0;
        processHappen(prm_no);
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->happen(prm_no);
                if (pElementTemp->_isLastFlg) {
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
    if(_wasInitializedFlg == false) {
        initialize();
        _wasInitializedFlg = true;
    }

    if (_isActiveFlg && !_wasPausedFlg && _isAliveFlg) {
        _dwFrame_relative = 0;
        processFinal();
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->finally();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::actAlone() {
    if (_isAliveFlg) {
        _willActNextFrameFlg = true;
        _willPauseNextFrameFlg = false;
        _willBlindNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::act() {
    if (_isAliveFlg) {
        _willActNextFrameFlg = true;
        _willPauseNextFrameFlg = false;
        _willBlindNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->act();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::actImmediatelyAlone() {
    if (_isAliveFlg) {
        if (_isActiveFlg == false) {
            _switchedToActFlg = true;
        } else {
            _switchedToActFlg = false;
        }
        _isActiveFlg = true;
        _wasPausedFlg = false;
        _wasBlindedFlg = false;
        _willActNextFrameFlg = true;
        _willPauseNextFrameFlg = false;
        _willBlindNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::actImmediately() {
    if (_isAliveFlg) {
        if (_isActiveFlg == false) {
            _switchedToActFlg = true;
        } else {
            _switchedToActFlg = false;
        }
        _isActiveFlg = true;
        _wasPausedFlg = false;
        _wasBlindedFlg = false;
        _willActNextFrameFlg = true;
        _willPauseNextFrameFlg = false;
        _willBlindNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->actImmediately();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::actAfter(DWORD prm_dwFrameOffset) {
    _willActAfterFrameFlg = true;
    _dwGodFremeWhenAct = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::inactAlone() {
    if (_isAliveFlg) {
        _willActNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::inact() {
    if (_isAliveFlg) {
        _willActNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inact();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::inactAfter(DWORD prm_dwFrameOffset) {
    _willInactAfterFrameFlg = true;
    _dwGodFremeWhenInact = askGod()->_dwFrame_God + prm_dwFrameOffset;
}

template<class T>
void GgafElement<T>::inactImmediatelyAlone() {
    if (_isAliveFlg) {
        if (_isActiveFlg) {
            _switchedToInactFlg = true;
        } else {
            _switchedToInactFlg = false;
        }
        _isActiveFlg = false;
        _willActNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::inactImmediately() {
    if (_isAliveFlg) {
        if (_isActiveFlg) {
            _switchedToInactFlg = true;
        } else {
            _switchedToInactFlg = false;
        }
        _isActiveFlg = false;
        _willActNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->inactImmediately();
                if (pElementTemp->_isLastFlg) {
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
    if (_isAliveFlg) {
        _willPauseNextFrameFlg = true;
        //_isActiveFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pause();
                if (pElementTemp->_isLastFlg) {
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
    if (_isAliveFlg) {
        _willPauseNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::pauseImmediately() {
    if (_isAliveFlg) {
        _wasPausedFlg = true;
        _willPauseNextFrameFlg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->pauseImmediately();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::pauseImmediatelyAlone() {
    if (_isAliveFlg) {
        _wasPausedFlg = true;
        _willPauseNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::unpause() {
    if (_isAliveFlg) {
        _willPauseNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpause();
                if (pElementTemp->_isLastFlg) {
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
    if (_isAliveFlg) {
        _willPauseNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::unpauseImmediately() {
    if (_isAliveFlg) {
        _wasPausedFlg = false;
        _willPauseNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unpauseImmediately();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unpauseImmediatelyAlone() {
    if (_isAliveFlg) {
        _wasPausedFlg = false;
        _willPauseNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::blind() {
    if (_isAliveFlg) {
        _willBlindNextFrameFlg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->blind();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::blindAlone() {
    if (_isAliveFlg) {
        _willBlindNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::blindImmediately() {
    if (_isAliveFlg) {
        _wasBlindedFlg = true;
        _willBlindNextFrameFlg = true;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->blindImmediately();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::blindImmediatelyAlone() {
    if (_isAliveFlg) {
        _wasBlindedFlg = true;
        _willBlindNextFrameFlg = true;
    }
}

template<class T>
void GgafElement<T>::unblind() {
    if (_isAliveFlg) {
        _willBlindNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unblind();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unblindAlone() {
    if (_isAliveFlg) {
        _willBlindNextFrameFlg = false;
    }
}

template<class T>
void GgafElement<T>::unblindImmediately() {
    if (_isAliveFlg) {
        _wasBlindedFlg = false;
        _willBlindNextFrameFlg = false;
        if (SUPER::_pSubFirst != NULL) {
            T* pElementTemp = SUPER::_pSubFirst;
            while(true) {
                pElementTemp->unblindImmediately();
                if (pElementTemp->_isLastFlg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->SUPER::_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::unblindImmediatelyAlone() {
    if (_isAliveFlg) {
        _wasBlindedFlg = false;
        _willBlindNextFrameFlg = false;
    }
}
template<class T>
void GgafElement<T>::farewell(DWORD prm_dwFrameOffset) {

    _dwGodFrame_ofDeath = (askGod()->_dwFrame_God) + prm_dwFrameOffset + 1;
    if (SUPER::_pSubFirst != NULL) {
        T* pElementTemp = SUPER::_pSubFirst;
        while(true) {
            pElementTemp->farewell(prm_dwFrameOffset);
            if (pElementTemp->_isLastFlg) {
                break;
            } else {
                pElementTemp = pElementTemp->SUPER::_pNext;
            }
        }
    }
}

template<class T>
DWORD GgafElement<T>::getFrame() {
    return _dwFrame;
}

template<class T>
bool GgafElement<T>::isAlive() {
    return _isAliveFlg;
}

template<class T>
bool GgafElement<T>::isPlaying() {
    if (_isAliveFlg && _isActiveFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::switchedToAct() {
    if (_isAliveFlg && _switchedToActFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::switchedToInact() {
    if (_isAliveFlg && _switchedToInactFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::canDraw() {
    if (_isAliveFlg && _isActiveFlg && !_wasBlindedFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::isBehaving() {
    if (_isAliveFlg && _isActiveFlg && !_wasPausedFlg) {
        return true;
    } else {
        return false;
    }
}

template<class T>
bool GgafElement<T>::relativeFrame(DWORD prm_dwFrame_relative) {
    _dwFrame_relative += prm_dwFrame_relative;
    if (_dwFrame == _dwFrame_relative) {
        return true;
    } else {
        return false;
    }
}

template<class T>
void GgafElement<T>::moveLast() {
    _willMoveLastNextFrameFlg = true;
}

template<class T>
void GgafElement<T>::moveFirst() {
    _willMoveFirstNextFrameFlg = true;
}

template<class T>
T* GgafElement<T>::becomeIndependent() {
    if (_isAliveFlg) {
        return SUPER::tear();
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

        if (pElementTemp->_isFirstFlg) { //最後の一つ
            if (pElementTemp->_pSubFirst) {
                //子の子がまだのっている場合さらにもぐる
                pElementTemp->cleane(prm_num_cleaning);
                if (GgafFactory::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_isAliveFlg == false) {
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
            if (pWk->_isAliveFlg == false) {
                DELETE_IMPOSSIBLE_NULL(pWk);
                GgafFactory::_cnt_cleaned++;
                Sleep(1);
            }
        }
    }
}

template<class T>
GgafElement<T>::~GgafElement() {
    //_TRACE_("~GgafElement() <"<<SUPER::_class_name << ">::farewell() :"<< SUPER::getName() <<"_dwGodFrame_ofDeath="<<_dwGodFrame_ofDeath<<"/_dwFrame="<<_dwFrame);
}

}
#endif /*GGAFELEMENT_H_*/
