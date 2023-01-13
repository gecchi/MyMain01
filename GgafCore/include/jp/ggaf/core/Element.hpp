#ifndef GGAF_CORE_ELEMENT_H_
#define GGAF_CORE_ELEMENT_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Node.hpp"

#include "jp/ggaf/core/Config.h"
#include "jp/ggaf/core/Phase.h"
#include "jp/ggaf/core/GarbageBox.h"
#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * ノード(Node<T>)に、様々な状態管理機能を追加したクラス .
 * 所謂タスクシステムに必要なフェーズ機能が実装されている。<BR>
 * 毎フレーム、管理者(Caretaker)は、この世(Spacetime)に、次のメソッドを順に呼び出す仕組みになっている。<BR>
 * nextFrame() > behave() > settleBehavior() > judge() > [preDraw() > draw() > afterDraw()] > doFinally() <BR>
 * アプリケーションに登場するノードは全て、「この世」のツリーに所属するため、全ノードに対して上記の処理が行われる。
 * 上記の内、nextFrame() のみ毎フレーム必ず実行される。<BR>
 * behave(), settleBehavior(), judge(), doFinally() は、活動状態フラグ(_is_active_in_the_tree_flg)が true の場合実行される。<BR>
 * preDraw(), draw(), afterDraw() は、次フレームまでの残時間に余裕がある場合、実行される。<BR>
 * 次フレームまでの残時間に余裕が無い場合、管理者はこの3メソッドをスキップする。
 * 但し、スキップするといっても、MAX_SKIP_FRAME フレームに１回は必ず実行する。<BR>
 * 上記の nextFrame() ～ doFinally() の処理を下位でオーバーライドすれば、タスクシステムの完成である。<BR>
 * しかし、メソッドの直接オーバーライドは非推奨である。オーバーライド用に各メソッド内でコールバックされる<BR>
 * 純粋仮想関数(processXxxxxx()) を用意しているので、そのメソッドをオーバーライドして下さい。<BR>
 * initialize() は、上記の nextFrame() ～ doFinally() を何れかを呼び出す前にインスタンスごとに１回だけ呼ばれる仕組みになっている。<BR>
 * 生存フラグ(_can_live_flg)がfalseの場合は、nextFrame() ～ doFinally() は全て実行されない。<BR>
 * (※旧クラス名はFactor)
 * @tparam T 管理する要素の型（この型のポインタ型が内部で管理される。）
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */
template<class T>
class Element : public Node<T> {

protected:
//    /**
//     * 自ツリーの配下ノード全てに、再帰呼び出しを行う。
//     * @param pFunc 再帰呼び出しするメソッド
//     */
//    inline void callRecursive(void (Element<T>::*pFunc)()) const {
//        T* pElementTemp = Node<T>::_pChildFirst;
//        while (pElementTemp) {
//            (pElementTemp->*pFunc)(); //実行
//            if (pElementTemp->_is_last_flg) {
//                break;
//            } else {
//                pElementTemp = pElementTemp->_pNext;
//            }
//        }
//    }
//
//    /**
//     * 自ツリーの配下ノード全てに、再帰呼び出しを行う。
//     * @param pFunc 再帰呼び出しするメソッド(frame 引数有り)
//     * @param prm_frame pFuncの引数であるframe
//     */
//    inline void callRecursive(void (Element<T>::*pFunc)(frame), frame prm_frame) const {
//        T* pElementTemp = Node<T>::_pChildFirst;
//        while (pElementTemp) {
//            (pElementTemp->*pFunc)(prm_frame); //実行
//            if (pElementTemp->_is_last_flg) {
//                break;
//            } else {
//                pElementTemp = pElementTemp->_pNext;
//            }
//        }
//    }


public:
    /** [r]管理者への近道 */
    Caretaker* _pCaretaker;
    /** [r]initializeが行われたどうかのフラグ(true=行われた) */
    bool _was_initialize_flg;
    /** [r]ノードが誕生(appendChildされた）時からのフレーム数総計 */
    frame _frame_of_life;
    /** [r]ノードが誕生(appendChildされた）時から、振舞ったフレーム数総計(_is_active_flg = false 時は加算され無い) */
    frame _frame_of_behaving;
    /** [r]ノードが活動開始(onActive())時からの振舞ったフレーム数総計(_is_active_flg = false 時は加算され無い) */
    frame _frame_of_behaving_since_onActive;

    /** [r]ノード活動フラグ */
    bool _is_active_flg;
    /** [r]ノード活動フラグ(自ツリーも考慮あり) */
    bool _is_active_in_the_tree_flg;
    /** [r]ノード生存フラグ */
    bool _can_live_flg;

    /** [r]終了する予定の _frame_of_life */
    frame _frame_of_life_when_end;
    /** [r]活動開始する予定の _frame_of_life */
    frame _frame_of_life_when_activation;
    /** [r]活動終了する予定の _frame_of_life */
    frame _frame_of_life_when_inactivation;
    /** [r]活動状態変更時のフラグ。0:コールバックなし / 1:onInactive()成立時 / 2:onActive()成立時 */
    int _on_change_to;
    /** [r]カレントフレーム内で一度でもリセットが実行されればtrue。毎フレーム false に更新される */
    bool _is_already_reset;
    /** [r]フェーズ管理オブジェクト */
    Phase* _pPhase;

public:
    /**
     * コンストラクタ
     * @param prm_name ノード名称（ユニークにして下さい）
     */
    explicit Element(const char* prm_name);

    /**
     * デストラクタ。自ツリーノードを解放する。 .
     */
    virtual ~Element();

    /**
     * 掃除(実行対象：配下ノード全て、自分自身はdeleteされません) .
     * 管理者が処理時間に余裕がでたとき等に、管理者が呼びだす。<BR>
     * 配下ノードの中にノード生存フラグ(_can_live_flg)が false になっているノードがあれば
     * prm_num_cleaning 個だけ delete する。<BR>
     * @param prm_num_cleaning 解放するオブジェクト数
     */
    virtual void clean(int prm_num_cleaning);

    /**
     * ノード初期処理(実行対象：thisのみ) .
     * インスタンス生成後、何れかが呼び出される前に、最初に必ず１回だけ呼び出される。<BR>
     * ＜コンストラクタとinitialize()の使い分けについて＞<BR>
     * ・コンストラクタは愛で生成時に呼び出されるが、initialize() はツリーに属し、活動開始する直前に呼ばれる。
     * ・initialize() は コンストラクタでは不可な、仮想関数を呼べるというメリットがある。<BR>
     * ・initialize() は、単なる関数なので、任意の箇所で明示的に何度でも呼び出すことも可能。<BR>
     * 補足：initialize()が呼び出された後、reset() が呼び出される。
     */
    virtual void initialize() = 0;

    /**
     * ノードのフレームを加算と、フレーム開始にあたってのいろいろな初期処理(実行対象：自ツリー全て) .
     * 毎フレーム必ず実行され、主に様々な状態フラグの更新を行う。 <BR>
     * _is_active_flg_in_next_frame, _can_live_flg_in_next_frame を<BR>
     * _is_active_flg,  _can_live_flg に反映（コピー）する。<BR>
     * また、_will_mv_first_in_next_frame_flg, _will_mv_last_in_next_frame_flg が true の場合は、<BR>
     * それぞれ、自ノードの先頭ノードへの移動、末尾ノードへの移動処理も実行される。<BR>
     * その後、配下ノード全てに nextFrame() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して nextFrame() 実行後、次は behave() を実行することになる。<BR>
     * 次のような構造の場合、実行順は①～⑬の順序となる。いわゆる pre-order 順。<BR>
     * ノード間で参照関係がある場合は、注意が必要。<BR>
     * <pre>
     * (Ｐ)⇔①Ｐ⇔(Ｐ)
     *         ↓
     * (Ｅ)⇔②Ａ⇔⑥Ｂ⇔⑪Ｃ⇔⑫Ｄ⇔⑬Ｅ⇔(Ａ)
     *         │    └────────────┐
     *         ↓                              ↓
     * (Ｈ)⇔③Ｆ⇔④Ｇ⇔⑤Ｈ⇔(Ｆ)    (Ｌ)⇔⑦Ｉ⇔⑧Ｊ⇔⑨Ｋ⇔⑩Ｌ⇔(Ｉ)
     *
     * ※基本は先頭→末尾の順、但し子が存在すれば先に実行、存在しなければ次(隣)を実行。
     * </pre>
     * メソッド説明に『(実行対象：自ツリー全て)』と記述されている場合は、全て上記の順序で実行される。
     */
    virtual void nextFrame();

    /**
     * ノードのフレーム毎の振る舞い処理(実行対象：自ツリー全て) .
     * この処理では、全ノード座標移動処理を行うこととする。<BR>
     * 実装用の processBehavior() がコールバックされるためのフラグの条件は、<BR>
     * 活動フラグがセット( _is_active_in_the_tree_flg == true) の場合である。 <BR>
     * behave() は 仮想関数 processBehavior() をコールした後、配下のノード全てについて behave() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processBehavior() をオーバーライドして具体的な座標移動ロジックを実装する。 <BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して behave() 実行後、次は settleBehavior() を実行することになる。<BR>
     */
    virtual void behave();

    /**
     * ノードのフレーム毎の振る舞い事後処理(実行対象：自ツリー全て) .
     * この処理では、全ノード座標移動が完了していることが保証された後の処理を行う事とする設計。<BR>
     * 更新が完了した座標情報から、それに伴う内部の様々なステータス等の更新処理をここで行う事を目的とする<BR>
     * 実装用の processSettlementBehavior() がコールバックされるためのフラグの条件は、<BR>
     * 一時停止フラグの状態と無関係に実行される点が behave() と異なる。<BR>
     * settleBehavior()は、仮想関数 processSettlementBehavior() をコールした後、配下のノード全てについて settleBehavior() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processSettlementBehavior() をオーバーライドしてロジックを実装することとする。 <BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して settleBehavior() 実行後、次に judge() を実行することになる。<BR>
     */
    virtual void settleBehavior();


    virtual void preJudge();
    /**
     * ノードのフレーム毎の判定処理(実行対象：自ツリー全て) .
     * この処理では、ノード間の様々な判定処理を行う事とする設計。<BR>
     * 全ノード座標移動処理と伴なうステータス類の更新が完全に完了してが前提とする処理が行われる。<BR>
     * 実装用の processJudgement() がコールバックされるためのフラグの条件は、behave()と同じく、<BR>
     * 活動フラグがセット(_is_active_in_the_tree_flg == true)の場合 <BR>
     * judge() は 仮想関数 processJudgement() をコールした後、配下のノード全てについて judge() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processJudgement() をオーバーライドしてロジックを実装する <BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して judge() 実行後、<BR>
     * 管理者(Caretaker)はこの後、次フレームまでの残時間に余裕があれば preDraw() 無ければ doFinally() を実行することになる。<BR>
     */
    virtual void judge();

    /**
     * ノードのフレーム毎の描画事前処理(実行対象：自ツリー全て)（フレームスキップされて呼び出されない場合もある。） .
     * 実装用の processPreDraw() がコールバックされる条件は、活動フラグがセット<BR>
     * ( _is_active_in_the_tree_flg )の場合である。 <BR>
     * processPreDraw() をコールした後、配下のノード全てについて preDraw() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processPreDraw() をオーバーライドしてロジックを実装する <BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して preDraw() 実行後、次に draw() を実行することになる。<BR>
     */
    virtual void preDraw();

    /**
     * ノードのフレーム毎の描画本処理(実行対象：自ツリー全て)（フレームスキップされて呼び出されない場合もある。） .
     * 実装用の processDraw() がコールバックされる条件は、活動フラグがセット<BR>
     * (_is_active_in_the_tree_flg)の場合である。 <BR>
     * processDraw() をコールした後、配下のノード全てについて draw() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processDraw() をオーバーライドしてロジックを実装する <BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して draw() 実行後、次に afterDraw() を実行することになる。<BR>
     */
    virtual void draw();

    /**
     * ノードのフレーム毎の描画事後処理(実行対象：自ツリー全て)（フレームスキップされて呼び出されない場合もある。） .
     * 実装用の processAfterDraw() がコールバックされる条件は、活動フラグがセット<BR>
     * (_is_active_in_the_tree_flg)の場合である。 <BR>
     * processAfterDraw() をコールした後、配下のノード全てについて afterDraw() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processAfterDraw() をオーバーライドしてロジックを実装する <BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して afterDraw() 実行後、次に doFinally() を実行することになる。<BR>
     */
    virtual void afterDraw();

    /**
     * ノードのフレーム毎の最終処理(実行対象：自ツリー全て) .
     * 座標移動処理、判定処理、描画処理が終了した後に、最後に行う後始末処理を行う事とする設計。<BR>
     * 実装用の processFinal() がコールバックされる条件は、
     * 活動フラグがセット(_is_active_in_the_tree_flg == true)の場合である。 <BR>
     * processFinal() をコールした後、配下のノード全てについて doFinally() を再帰的に実行する。<BR>
     * 管理者(Caretaker)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processFinal() をオーバーライドしてロジックを実装する <BR>
     * 管理者(Caretaker)は、この世(Spacetime)に対して doFinally() 実行後、<BR>
     * 次フレームまでの残時間に余裕があれば clean() を実行する。<BR>
     * その後は nextFrame() を実行することになる。<BR>
     */
    virtual void doFinally();

    /**
     * 非活動→活動時に切り替わった時のコールバック(ユーザー実装用) .
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
     * 活動→非活動時に切り替わった時のコールバック(ユーザー実装用) .
     * 活動状態から非活動状態に変化したときに１回コールバックされる。<BR>
     * 呼び出されるタイミングはフレーム加算直後である。通常 behave() よりも前に実行される。<BR>
     * 必要に応じてオーバーライドする。<BR>
     */
    virtual void onInactive() {
    }

    /**
     * フレーム毎の個別振る舞い処理を実装。(ユーザー実装用) .
     * behave() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の振る舞いを処理を実装する。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理等である。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、nextFrame() が実行済みであることを保証する。<BR>
     */
    virtual void processBehavior() = 0;

    /**
     * フレーム毎の個別振る舞い事後処理を実装。(フレームワーク実装用) .
     */
    virtual void processSettlementBehavior() {}


    virtual void processPreJudgement() {}
    /**
     * フレーム毎の個別判断処理を実装。(ユーザー実装用) .
     * judge() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数をオーバーライドして、ノード個別判断処理を記述する。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対してて、processBehavior() が実行済みであることを保証する。<BR>
     * 本メンバ関数の存在意図として、processBehavior() で座標移動処理が全て完了した後、
     * 本メンバ関数で当たり判定処理を実装するといった使い方を想定している。<BR>
     */
    virtual void processJudgement() = 0;

    /**
     * ノードのフレーム毎の個別描画事前処理を実装。(本フレームワーク実装用) .
     * preDraw() 時の処理先頭でコールバックされる。 但し、管理者(Caretaker)が描画スキップした場合、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画事前処理を実装する。<BR>
     * 個別描画事前処理とは、主に当たり背景描画などである。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processJudgement() が実行済みであることも保証する。<BR>
     * さらに、本メンバ関数実行後、processDraw()、processAfterDraw() が呼び出されることも保証される。
     */
    virtual void processPreDraw() {};

    /**
     * ノードのフレーム毎の個別描画本処理を実装。(本フレームワーク実装用／ユーザー実装用) .
     * draw() 時の処理先頭でコールバックされる。 但し、preDraw() と同様に管理者(Caretaker)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画本処理を実装する。<BR>
     * 個別描画本処理とは主にキャラクタや、背景の描画を想定している。
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processPreDraw() が実行済みであることを保証する。<BR>
     */
    virtual void processDraw() = 0;

    /**
     * ノードのフレーム毎の個別表示事後処理を記述。(本フレームワーク実装用) .
     * afterDraw() 時の処理先頭でコールバックされる。 但し、preDraw() と同様に管理者(Caretaker)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別表示事後処理を実装する。<BR>
     * 個別表示事後処理とは、最前面レイヤーで実現するフェードエフェクトや、常に最前面に表示される情報表示などである。<BR>
     * 本メンバがコールバックされると言う事は、全ノード対して、processDraw() が実行済みであることを保証する。<BR>
     */
    virtual void processAfterDraw() {};

    /**
     * ノードのフレーム毎の個別終端処理を実装。(本フレームワーク実装用) .
     * doFinally() 時の処理先頭でコールバックされる。<BR>
     * このメンバ関数を下位クラスでオーバーライドして、ノード個別の終端処理を実装する。<BR>
     * 終端処理とは、フラグ管理の実行などである。<BR>
     * 想定している振る舞い処理とは、主に座標計算と移動処理である。その他なんでも良いである。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processJudgement() が実行済みで 描画処理は終了していることを保証する。<BR>
     */
    virtual void processFinal() {};

    /**
     * 自ノードと自ノードよりも親にあたるノード全てにイベントメッセージを通知(通知対象：ツリー全て) .
     * 但し、ノードは正しいツリーの一員でなければ通知されません。<BR>
     * 正しいツリーの一員とは、_can_live_flg と _was_initialize_flg が true である事です。<BR>
     * イベントを受け取る側は、onCatchEvent(eventval, void) を実装が必要です。<BR>
     * 自身の onCatchEvent(eventval, void) にも通知されるので注意して下さい。<BR>
     * @param prm_event_val イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void throwEventUpperTree(eventval prm_event_val, void* prm_pSource);

    /**
     * 自ノードと自ノードよりも親にあたるノード全てにイベントメッセージを通知(通知対象：ツリー全て) .
     * 但し、ノードは正しいツリーの一員でなければ通知されません。<BR>
     * 正しいツリーの一員とは、_can_live_flg と _was_initialize_flg が true である事です。<BR>
     * イベントを受け取る側は、onCatchEvent(eventval, void) を実装が必要です。<BR>
     * 自身の onCatchEvent(eventval, void) にも通知されるので注意して下さい。<BR>
     * 汎用引数 void* には、this が設定されます。<BR>
     * @param prm_event_val イベントメッセージ番号
     */
    virtual void throwEventUpperTree(eventval prm_event_val) {
        throwEventUpperTree(prm_event_val, this);
    }


    /**
     * 自ノードとその配下ノード全てにイベントメッセージを通知します(通知対象：所属の親全て) .
     * イベントを受け取る側は、onCatchEvent(eventval, void) を実装が必要である。<BR>
     * 自身の onCatchEvent(eventval, void) にも通知されるので注意して下さい。<BR>
     * @param prm_event_val イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void throwEventLowerTree(eventval prm_event_val, void* prm_pSource);

    /**
     * 自ノードとその配下ノード全てにイベントメッセージを通知します(通知対象：所属の親全て) .
     * イベントを受け取る側は、onCatchEvent(eventval, void) を実装が必要である。<BR>
     * 自身の onCatchEvent(eventval, void) にも通知されるので注意して下さい。<BR>
     * 汎用引数 void* には、this が設定されます。<BR>
     * @param prm_event_val イベントメッセージ番号
     */
    virtual void throwEventLowerTree(eventval prm_event_val) {
        throwEventLowerTree(prm_event_val, this);
    }

    /**
     * イベント発生時のコールバック .
     * throwEventUpperTree() throwEventLowerTree() で発した場合コールバックされます。<BR>
     * @param prm_event_val イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) {}


    virtual bool isDisappear();
    /**
     * 管理者に謁見 .
     * @return  呼ばれて出てきた管理者
     */
    virtual Caretaker* askCaretaker() = 0;

    //==================フェーズメソッド郡==================>
    /**
     * 活動状態にする(実行対象：this のみ) .
     * 正確には、自ノードだけ次フレームから活動状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理(nextFrame())内で、めでたく活動状態(_is_active_flg = true)になる。<BR>
     * 直前の状態が非活動だったならば、先頭処理内で onActive() のコールバックが行われる。<BR>
     * したがって、本メソッドを実行しても『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * 配下ノードには何も影響がありません。<BR>
     * 既に inactivateDelay() 実行済みの場合は、取り消されてactivate()が有効になる。<BR>
     * 既に activateDelay() 実行済みの場合は、今回指定算フレーム1で(activate() = activateDelay(1))上書きする。<BR>
     * <B>[補足]</B><BR>
     * ノード生成直後はデフォルトで活動状態となっているため、最初は activate() 不要。<BR>
     * <B>【注意】</B><BR>
     * processBehavior() で 自身を activate() を呼び出すコードは通常意味が無い。<BR>
     * タスクシステムの仕組み上 processBehavior() は活動状態にのみ実行されるので、永遠に実行されない事になる。<BR>
     */
    virtual void activate();

    /**
     * 活動状態にする(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に activate() が実行される。<BR>
     */
    virtual void activateTree();

    /**
     * 少し遅延してから活動状態にする(実行対象：this のみ) .
     * 引数のフレーム数遅延して activate() が実行される。<BR>
     * activateDelay(1) は、activate() と同じ意味になる。<BR>
     * @param prm_offset_frames 遅延フレーム数(1～)
     */
    virtual void activateDelay(frame prm_offset_frames = 1);

    /**
     * 少し遅延してから活動状態にする(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に activateDelay(frame) が実行される。<BR>
     * activateTreeDelay(1) は、activateTree() と同じ意味になる。<BR>
     * @param prm_offset_frames 遅延フレーム数(1～)
     */
    virtual void activateTreeDelay(frame prm_offset_frames = 1);

    /**
     * 一定時間だけ活動状態にする(実行対象：this のみ) .
     * 活動状態にした後、引数のフレーム数経過すると、非活動状態になる。
     * activateWhile(10); は
     * activate(); inactivateDelay(10); の実行と同等の効果である。
     * @param prm_frames 活動フレーム
     */
    virtual void activateWhile(frame prm_frames = 1);

    /**
     * 即座に活動状態にする(実行対象：this のみ) .
     * 即座に状態フラグを更新(_is_active_flg = true)する。<BR>
     * onActive() コールバックは実行されない。初期化以外で本メソッドの使用は非推奨。<BR>
     * 以下の点を留意して使用する際は注意が必要である。<BR>
     * 『同一フレーム内』であっても、既に処理されたノードと未処理のノードで、異なる状態になってしまう。<BR>
     * 処理で、「このノードが活動状態ならば・・・」等、その状態（フラグ）により分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void activateImmed();

    /**
     * 即座に活動状態にする(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に activateImmed() が実行される。<BR>
     * activateImmed() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void activateTreeImmed();
    //===================

    /**
     * 非活動状態にする(実行対象：this のみ) .
     * 正確には、自ノードだけ次フレームから非活動状態にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理(nextFrame())内で、本当の非活動状態(_is_active_flg = false)になる。<BR>
     * 直前の状態が活動状態だったならば、先頭処理内で onInactive() のコールバックが行われる。<BR>
     * したがって、本メソッドを実行しても『同一フレーム内』は活動状態の変化は無く一貫性は保たれる。<BR>
     * 配下ノードには何も影響がありません。<BR>
     */
    virtual void inactivate();

    /**
     * 非活動状態にする
     * 自身と配下ノード全てについて再帰的に inactivate() が実行される。<BR>
     */
    virtual void inactivateTree();

    /**
     * 少し遅延してから非活動状態にする(実行対象：this のみ) .
     * 引数のフレーム数遅延して inactivate() が実行される。<BR>
     * inactivateDelay(1) は、inactivate() と同じ意味になる。<BR>
     * @param prm_offset_frames 遅延フレーム数(1～)
     */
    virtual void inactivateDelay(frame prm_offset_frames = 1);


    /**
     * 少し遅延してから活動状態にする(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に inactivateDelay(frame) が実行される。<BR>
     * inactivateDelay(1) は、inactivateTree() と同じ意味になる。<BR>
     * @param prm_offset_frames 遅延フレーム数(1～)
     */
    virtual void inactivateTreeDelay(frame prm_offset_frames = 1);

    /**
     * 即座に非活動状態にする(実行対象：this のみ) .
     * 即座に状態フラグを更新(_is_active_flg = false)する。<BR>
     * onInactive() コールバックは実行されない。初期化以外で本メソッドの使用は非推奨。<BR>
     * 以下の点を留意して使用する際は注意が必要である。<BR>
     * 『同一フレーム内』であっても、既に処理されたノードと未処理のノードで、異なる状態になってしまう。<BR>
     * 処理で、「このノードが非活動状態ならば・・・」等、その状態（フラグ）により分岐していた場合、<BR>
     * 同一フレーム内の処理結果の整合性が崩れる恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void inactivateImmed();

    /**
     * 即座に非活動状態にする(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に inactivateImmed() が実行される。<BR>
     * inactivateImmed() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void inactivateTreeImmed();

    //===================
    /**
     * 状態をリセットするための処理である onReset() をコールバックする。(実行対象：thisのみ) .
     * 次のような動作を『即時』に行います。<BR>
     * 次フレームの先頭処理( nextFrame() )内ではありません。<BR>
     * 同一フレーム内で何度 reset() を呼び出しても、１フレームで onReset() は１回しか呼ばれない
     * ようにするためのメソッドである。次のように動作する。<BR>
     * ① 同一フレーム内で、初めての呼び出しであるかチェック<BR>
     *   ・初めての呼び出しである。  → ②へ<BR>
     *   ・２回以上呼び出されている。→ 何もしないでreturn<BR>
     * ② 下位実装処理の onReset() をコールバックする。<BR>
     * 補足:内部で initialize() 呼び出し直後に、１回だけ reset() は自動的に呼び出される。<BR>
     */
    virtual void reset();
    // ＜メモ initialize(), onReset(), onActive() の使い分けについて＞
    // 状態をリセット処理は、どこに実装するべきか？
    // initialize() ・・・ 生成後、最初の１回だけ事前にコールバックされる。初期化処理等に使用することを想定。
    // onReset()    ・・・ 生成後、initialize() の後、１回だけ無条件でコールされる。
    //                     その後、任意のタイミングの reset() 実行でコールバックされる。
    // onActive()   ・・・ 生成後、initialize() の後の活動状態時 １フレーム目の behave() 直前にコールされる。
    //                     その後 非活動→活動状態になった時、自動的にコールバックされる。
    // ノード(アクターやシーン)の処理サイクルによって使い分ける。
    // アクター生成後、そのコンストラクタで何もしなかった場合、最初の nextFrame() 時に
    // initialize() ＞ onReset() ＞onActive() の順に実行されることになる。
    //
    // ・１サイクルなノード(アクターやシーン)の場合
    // 生成後、初めての「終了」という状態を迎えた際に、そのまま解放となる場合。つまり、インスタンスを使いまわさない場合。
    // initialize(), onReset(), onActive() は事前に各１回実行されるので、どこに状態をリセット処理を実装しても差異は無いはず。
    // 多くの通常のアクターや、一時的な短いシーンはこれに該当すると予想する。
    // どこに実装しても良いが、initialize() で実装を統一したほうが、他のオブジェクトから操作しやすい。
    //
    // ・onActive() を使用すべき場合
    // 生成されたノードに、「表示(活動)」「非表示(非活動)」という状態が存在し、何度も使いまわす場合。
    // 表示(活動) ～ 非表示(非活動) が、ノードの１サイクルのと一致する場合。
    // initialize() ・・・ 初期化処理、
    // onActive()   ・・・ 状態リセット処理
    // と使い分けて記述し。 inacivate()、active() で状態リセット行う。
    // なぜ onReset() に状態リセット処理を記述し、reset()コールではいけないのかというと、
    // 処理の中心である processBehavior() メソッドは、非表示(非活動) はコールされないため、
    // 自身のオブジェクトの処理で reset() を記述しても実行されることが無いという事態に陥る。
    // もちろん、他のオブジェクトから、非表示(非活動)→表示(活動) をチェックし、reset() を実行してあげれば
    // 問題ないが、いつリセットされるのか、処理を追いかけないと分からないようになるというデメリットもあるのではないだろうか。
    // onActive() がコールされても、getBehaveingFrame() は「リセットされない」が、
    // getActiveFrame()は「リセット」される事に注意。
    // 主に敵弾など汎用的なアクターは、これに該当すると予想する。
    //
    // ・onReset() を使用すべき場合
    // 生成されたノードに、「表示(活動)」「非表示(非活動)」という概念が無い。表示(活動)しっぱなし。
    // だがしかし、処理サイクル（リセット）の概念があるノード場合
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
     * 状態をリセットする(実行対象：自ツリー全て) .
     * 自ツリー全てのオブジェクトに対し reset() を『即時』実行する。
     * reset() の説明要参照。
     */
    virtual void resetTree();

    /**
     * 実際の状態をリセットする処理(ユーザー実装用) .
     * reset() 或いは、resetTree() を実行することでコールバックされる。
     * 個別のの状態リセット処理を、下位クラスでオーバーライドしてください。
     */
    virtual void onReset() {}


    /**
     * 終了宣言する。(実行対象：自ツリー全て) .
     * 自ノードを引数のフレーム後に「生存終了」状態にすることを宣言する。（終了予約フラグを立てる） <BR>
     * 自身と配下ノード全てについて再帰的に end(frame) が実行され生存終了宣言が行われる。<br>
     * 親ノードが終了すれば、子ノードも終了せざるを得ないからである。<BR>
     * 終了フラグは一度立てると元にもどせません。以降 end(frame) を重ねて呼び出しても無視され、<BR>
     * 引数の猶予フレームは、そのフレーム後に生存終了となる遅延フレーム数である。<BR>
     * 「生存終了」とは具体的には、振る舞いフラグ(_is_active_flg)、生存フラグ(_can_live_flg) を、
     * アンセットする予約フラグを立てること事で、猶予フレーム後の先頭処理( nextFrame() )で実際にフラグが更新され
     * 本当の終了状態になる。<BR>
     * _can_live_flg がアンセットされることにより、自動的にツリーから切り離されゴミ箱(GarbageBox) 配下に、
     * 所属することになる。その後、管理者(Caretaker)が余裕のある時 (FPSが高いとき) を見計らい clean() メソッドにより、<BR>
     * GarbageBox に所属する配下ノードを delete するし、メモリーから消え去る。<BR>
     * <b>【注意】</b><BR>
     * 本メソッドを実行して引数の猶予フレーム後になっても、
     * GarbageBox 配下に移るだけで、直ぐには deleteされるとは限らないため、
     * 不正ポインタによる潜在的バグを起こす。細心の注意をはらおう～（うん、そう決めた）<BR>
     * @param prm_offset_frames 生存終了猶予フレーム(1～)
     */
    virtual void end(frame prm_offset_frames = 1);

    /**
     * ゴミ箱に放り込まれる直前に呼び出されるコールバック(フレームワーク実装用) .
     * end(frame) 実行後、ゴミ箱(GarbageBox) に取り込まれる直前に呼び出される。<BR>
     * つまり、_can_live_flg が false から true になった時に呼び出される。<BR>
     * ですが、まだツリーに所属していおり、自身のノードの鎖はまだ切れていない状態です。<BR>
     * 最速で、end(frame) で指定したフレーム + GGAF_END_DELAY 後に発生する。<BR>
     * 処理がもたつくと、それ以上の先のフレームで発生する。<BR>
     * 直前に処理が必要な場合は、オーバーライドして実装可能。<BR>
     */
    virtual void onEnd() {
    }

    /**
     * 自ノードが非活動から活動状態に切り替わったかどうか調べる .
     * onActive() が呼ばれたフレームのみ true になる。
     * onActive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備しました。<BR>
     * @return  bool true:非活動から活動状態切り替わった／false:切り替わっていない
     */
    inline bool hasJustChangedToActive() const {
        return _on_change_to == 2 ? true : false;
    }

    /**
     * 自ノードが活動状態から非活動に切り替わったかどうか調べる .
     * onInctive() が呼ばれたフレームのみ true になる。
     * onInctive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備しました。<BR>
     * @return  bool true:活動状態から非活動に切り替わった／false:切り替わっていない
     */
    inline bool hasJustChangedToInactive() const {
        return _on_change_to == 1 ? true : false;
    }

    /**
     * 生存可能状態か調べる
     * @return  bool true:生存可能状態／false:生存不可状態
     */
    inline bool canLive() const {
        return _can_live_flg;
    }

    /**
     * 活動中か調べる .
     * 自身フラグの状態で活動中かどうか判断
     * @return  bool true:活動中／false:非活動中
     */
    inline bool isActive() const {
        return (_can_live_flg && _is_active_flg) ? true : false;
    }

    /**
     * 自ツリーで活動中かどうか判断 <BR>
     * たとえば、自身フラグの状態で活動中でも、親が活動中でない場合、
     * 自身は活動出来ない。それも考慮した上で、本当に活動中かどうか判定を行う。
     * @return true:自ツリーで活動中／false:自ツリーで非活動中
     */
    inline bool isActiveInTheTree() const {
        return (_is_active_in_the_tree_flg && _can_live_flg) ? true : false;
    }

    /**
     * 終了宣言したかどうか .
     * end(frame) が実行済みかどうか調べます。
     * @return true:終了宣言済み／false:まだ終了宣言されていない
     */
    inline bool wasDeclaredEnd() const {
        return (_frame_of_life_when_end > _frame_of_life || _can_live_flg == false) ? true : false;
    }

    /**
     * 振る舞い状態時に加算されるフレーム数を取得する .
     * 「振る舞い状態」とは、canBehave() → true の条件成立時の事を意味する。<BR>
     * 0 Frame状態は基本存在せず、1 Frame ～ からの値になる。但し例外的に<BR>
     * 生成時コンストラクタ内、および、最初の initialize() 内では 0 Frame を返す。<BR>
     * 初回実行の onActive()、processBehavior()、processJudgement() 等の中で 1 になっている。<BR>
     * 以降、振る舞い態時にフレーム加算される。<BR>
     * @return 振る舞いフレーム数総計
     */
    inline frame getBehaveingFrame() const {
        return _frame_of_behaving;
    }

    /**
     * 直近の onActive() から開始した振る舞い状態は何フレーム目かを返す。 .
     * 汎用オブジェクトなど、一度生成して使いまわす(deleteしない)場合、<BR>
     * 消失時に inactivate() 、出現時 activate() を繰り返すことが想定される。<BR>
     * そのような場合に、何フレーム目かを取得する際に都合が良いメソッド。<BR>
     * onActive() コールバック条件成立時にリセット(0)され、onActive() 内では、常に 0 を返す。<BR>
     * getBehaveingFrame() と同じタイミングで加算される。processBehavior()では、1 ～ を返す。<BR>
     * @return onActive() からの振る舞いフレーム数
     */
    inline frame getActiveFrame() const {
        return _frame_of_behaving_since_onActive;
    }

    /**
     * 自身と配下全てのオブジェクトに対して指定の関数を実行させる .
     * 配下オブジェクト（アクターかシーン）のポインタが、引数関数ポインタの pFuncの第１引数に渡ってくる。<BR>
     * 引数関数ポインタの pFunc の第２引数には、executeFuncLowerTree 呼び出し時の prm1(引数１)のポインタが渡ってくる。<BR>
     * 引数関数ポインタの pFunc の第３引数には、executeFuncLowerTree 呼び出し時の prm2(引数２)のポインタが渡ってくる。<BR>
     * 引数関数ポインタの pFunc の第４引数には、executeFuncLowerTree 呼び出し時の prm3(引数３)のポインタが渡ってくる。<BR>
     * 配下のオブジェクトが何であるのか判っている上で使用しないと危険である。<BR>
     *
     * ＜使用例＞<BR>
     * XXXXActor 配下のオブジェクト全てのアクター(但しGgafDx::GeometricActor)のメンバ変数 _x に、
     * XXXXActorメンバ変数 _velo の値を加算させる。<BR>
     * XXXXActor クラスの実装サンプルを以下に記す<BR>
     * <code><pre>
     *
     * class XXXXActor : public GgafDx::GeometricActor {
     * public :
     *     int velo_;
     *
     *     static void addX(Object* pThat, void* p1, void* p2, void* p3) {
     *         if (pThat->instanceOf(Obj_GgafDx_GeometricActor)) { //GeometricActorならば
     *             GgafDx::GeometricActor* pActor = (GgafDx::GeometricActor*)pThat;
     *             pActor->_x += (*((int*)p1));  //_x 加算。p1 には velo_ へのポインタが渡ってくる
     *         }
     *     }
     *
     *     void processBehavior() {
     *         //配下アクター全てにaddX実行
     *         velo_ = 1000;
     *         executeFuncLowerTree(XXXXActor::addX, &velo_, nullptr, nullptr);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc オブジェクトに実行させたい関数。パラメータは(Object*, void*, void*, void*) 固定。
     * @param prm1 渡したい引数その１
     * @param prm2 渡したい引数その２
     * @param prm3 渡したい引数その３
     */
    virtual void executeFuncLowerTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3);

    /**
     * フェーズ管理オブジェクト(Phase) を取得する。
     * @return フェーズ管理オブジェクト
     */
    inline virtual Phase* getPhase() const {
        return _pPhase;
    }

    /**
     * 本オブジェクトの _frame_of_behaving に関連性を持った、フェーズ管理オブジェクト(Phase) を生成し取得 .
     * 自動でフェーズの更新は行われないので、呼び出し元で updateを行ってください。
     * @param prm_num フェーズの場合の数
     * @return 新しいフェーズ管理オブジェクト
     */
    virtual Phase* createAnotherPhase() {
        return NEW Phase(&_frame_of_behaving);
    }

    /**
     * ツリー考慮ありノード活動フラグ(自)
     */
    virtual void updateActiveInTheTree() = 0;

    /**
     * 活動予定か否かを返す .
     * @return
     */
    inline bool isActivateScheduled() {
        if (_frame_of_life_when_activation >= _frame_of_life) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * 非活動予定か否かを返す .
     * @return
     */
    inline bool isInactivateScheduled() {
        if (0 < _frame_of_life_when_inactivation &&
                _frame_of_life_when_inactivation >= _frame_of_life) {
            return true;
        } else {
            return false;
        }
    }
};

///////////////////////////////////////////////////////////////// ここからは実装部

template<class T>
Element<T>::Element(const char* prm_name) :
    Node<T>(prm_name),
    _pCaretaker(nullptr),
    _was_initialize_flg(false),
    _frame_of_life(0),
    _frame_of_behaving(0),
    _frame_of_behaving_since_onActive(0),
    _is_active_flg(false),             //生成直後はfalseであるが、何もしないと初回nextFrame()でアクティブになる予定
    _is_active_in_the_tree_flg(false),
    _can_live_flg(true),
    _frame_of_life_when_end(0),
    _frame_of_life_when_activation(1), //初回フレームにアクティブになるために1
    _frame_of_life_when_inactivation(0),
    _on_change_to(0),
    _is_already_reset(false),
    _pPhase(NEW Phase(&_frame_of_behaving))
{
}

template<class T>
void Element<T>::nextFrame() {
    const frame frame_of_life = (++_frame_of_life);
    _is_already_reset = false;
    if (frame_of_life == _frame_of_life_when_end) {
        _can_live_flg = false; //終了の時だ
    } else {
        if (_is_active_flg) {  //現在activate
            if (frame_of_life == _frame_of_life_when_inactivation) { //現在 activate だが、今inactivateになる時が来た
                _on_change_to = 1;
                _is_active_flg = false; //活動フラグOFF
                _is_active_in_the_tree_flg = false;
                onInactive(); //コールバック
            } else {
                _on_change_to = 0;
                updateActiveInTheTree();     //_is_active_in_the_tree_flg を更新
                if (_is_active_in_the_tree_flg) {
                    _frame_of_behaving++;
                    _pPhase->update();// フェーズを反映
                    _frame_of_behaving_since_onActive++;
                }
            }
        } else { //現在inactivate
            if (frame_of_life == _frame_of_life_when_activation) { //現在inactivate だが、今activateになる時が来た
                _on_change_to = 2;      //onActive処理
                _is_active_flg = true;  //活動フラグON
                updateActiveInTheTree();     //_is_active_in_the_tree_flg を更新
                if (_is_active_in_the_tree_flg) {
                    _frame_of_behaving++;
                    _pPhase->update();  // フェーズを反映
                    _frame_of_behaving_since_onActive++;
                }
                if (!_was_initialize_flg) {
                    initialize();       //初期化
                    _was_initialize_flg = true;
                    reset(); //リセット
                }
                _frame_of_behaving_since_onActive = 0; //リセット
                onActive();   //コールバック
                _frame_of_behaving_since_onActive = 1;
            } else {
                _on_change_to = 0;
                _is_active_in_the_tree_flg = false;
            }
        }
    }
    //再帰
    //配下の全ノードに再帰的にnextFrame()実行
    T* p = Node<T>::_pChildFirst; //一つ配下の先頭ノード。潜れる場合は先に潜る。
    if (p) {
        while (!p->_is_last_flg) {
            //配下の先頭 ～ 末尾-1 ノードに nextFrame()
            p->nextFrame();  //再帰
            if (p->_can_live_flg) {
                p = p->_pNext;
            } else {
                p->onEnd();
                p = p->_pNext; //先に一個進ませて退避させてから
                GarbageBox::_pGarbageBox->add(p->_pPrev); //一個前をゴミ箱へ(連結が切れる)
            }
        }
        //配下の最後の末尾ノードに nextFrame()
        p->nextFrame(); //再帰
        if (p->_can_live_flg) {
            //OK 次は無し→親ノードの処理へ
        } else {
            p->onEnd();
            GarbageBox::_pGarbageBox->add(p); //ゴミ箱へ
        }
    }
}

template<class T>
void Element<T>::behave() {
    if (_is_active_in_the_tree_flg) {
        processBehavior();    //ユーザー実装用
        //callRecursive(&Element<T>::behave);
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->behave();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::settleBehavior() {
    if (_is_active_in_the_tree_flg) {
        processSettlementBehavior(); //フレームワーク用
        //callRecursive(&Element<T>::settleBehavior); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->settleBehavior();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::preJudge() {
    if (_is_active_in_the_tree_flg) {
        processPreJudgement();    //フレームワーク用
        //callRecursive(&Element<T>::preJudge); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->preJudge();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::judge() {
    if (_is_active_in_the_tree_flg) {
        processJudgement();    //ユーザー実装用
        //callRecursive(&Element<T>::judge); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->judge();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::preDraw() {
    if (_is_active_in_the_tree_flg) {
        processPreDraw();
        //callRecursive(&Element<T>::preDraw); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->preDraw();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::draw() {
    if (_is_active_in_the_tree_flg) {
        processDraw();
        //callRecursive(&Element<T>::draw); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->draw();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::afterDraw() {
    if (_is_active_in_the_tree_flg) {
        processAfterDraw();
        //callRecursive(&Element<T>::afterDraw); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->afterDraw();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::doFinally() {
    if (_is_active_in_the_tree_flg) {
        processFinal();
        //callRecursive(&Element<T>::doFinally); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->doFinally();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::reset() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //初期化
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            onReset();
            _is_already_reset = true;
        }
    }
}

template<class T>
void Element<T>::resetTree() {
    if (_can_live_flg) {
        if(_was_initialize_flg == false) {
            initialize();       //初期化
            _was_initialize_flg = true;
        }
        if (_is_already_reset == false) {
            onReset();
            _is_already_reset = true;
        }
        //callRecursive(&Element<T>::resetTree); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->resetTree(); //実行
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::activate() {
    if (_can_live_flg) {
        activateDelay(1);
    }
}

template<class T>
void Element<T>::activateTree() {
    if (_can_live_flg) {
        activateDelay(1);
        //callRecursive(&Element<T>::activateTree); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->activateTree(); //実行
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::activateImmed() {
    if (_can_live_flg) {
        if (!_was_initialize_flg) {
            initialize();       //初期化
            _was_initialize_flg = true;
            reset(); //リセット
        }
        _is_active_flg = true;
        _frame_of_life_when_activation = _frame_of_life;
        updateActiveInTheTree();
    }
}

template<class T>
void Element<T>::activateTreeImmed() {
    if (_can_live_flg) {
        activateImmed();
        //callRecursive(&Element<T>::activateTreeImmed); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->activateTreeImmed(); //実行
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::activateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("activateDelay(0) は無意味である。いつまでも activate() されませんよ！！！。意図してますか？ name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= SEC_F(60*60)) { //１時間後
        throwCriticalException("activateDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも activate() されませんよ！！！。負の数になったのとちがう？。 name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
#ifdef MY_DEBUG
        if (_is_active_flg) {
            _TRACE_("【警告】activateDelay("<<prm_offset_frames<<") しましたけど、既に活動状態ですよ。意図してますか？ name="<<Node<T>::_name<<" this="<<this);
        }
#endif
        //既にinactivateDelay()実行済みの場合は
        //そのinactivateDelay()は無効化される。
        //
        //inactivate();
        //activate();
        //の順に実行すると、activate() が無条件で勝つ
        //activate();
        //inactivate();
        //の順に実行すると、inactivate() が勝つ
        //既にactivateDelay()実行済みの場合は、今回指定算フレームで上書きする（後勝ち）。
        //(※inactivateDelay() と優先の考えが違うため注意)
        _frame_of_life_when_inactivation = 0;
        _frame_of_life_when_activation = _frame_of_life + prm_offset_frames;
    }
}

template<class T>
void Element<T>::activateWhile(frame prm_frames) {
#ifdef MY_DEBUG
    if (prm_frames == 0) {
        throwCriticalException("activateWhile(0) は無意味である。いつまでも activate() されませんよ！！！。意図してますか？ name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_frames >= 60*60*60) { //１時間後
        throwCriticalException("activateWhile("<<prm_frames<<") って遅すぎるんちゃうん？。いつまでも activate() されませんよ！負の数になったのとちがう？。 name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        _frame_of_life_when_activation = _frame_of_life + 1;
        _frame_of_life_when_inactivation = _frame_of_life + prm_frames;
    }
}

template<class T>
void Element<T>::activateTreeDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("activateTreeDelay(0) は無意味である。いつまでも activate() されませんよ！！！。意図してますか？ name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= SEC_F(60*60)) { //１時間後
        throwCriticalException("activateTreeDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも activate() されませんよ！負の数になったのとちがう？ name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        activateDelay(prm_offset_frames);
        //callRecursive(&Element<T>::activateTreeDelay, prm_offset_frames); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->activateTreeDelay(prm_offset_frames); //実行
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::inactivate() {
    if (_can_live_flg) {
        inactivateDelay(1);
    }
}

template<class T>
void Element<T>::inactivateTree() {
    if (_can_live_flg) {
        inactivateDelay(1);
        //callRecursive(&Element<T>::inactivateTree); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->inactivateTree();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::inactivateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("inactivateDelay(0) は無意味である。いつまでも inactivate() されませんよ！！！。意図してますか？ name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= SEC_F(60*60)) { //１時間後
        throwCriticalException("inactivateDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも inactivate() されませんよ！負の数になったのとちがう？ name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {


        if (_frame_of_life_when_activation >= _frame_of_life + prm_offset_frames) {
            //inactive と同フレーム、または inactive 予定よりも後に active 予定ならば、
            //(activeにはならないようにするため)無効にする。
            //activate();
            //inactivate();
            //の順に実行すると、inactivate() が勝つ
            _frame_of_life_when_activation = 0;
        }

        //既にinactivateDelay()実行済みの場合、今回の指定が、
        //より早く inactivate する指定ならば上書きするが、
        //より遅く inactivate する指定ならば、過去のinactivate する方を優先
        if (0 < _frame_of_life_when_inactivation &&
                _frame_of_life_when_inactivation < _frame_of_life + prm_offset_frames) {
            //今回指定算フレームの方が遅い場合は無視される。
            return;
        } else {
            //inactivateを予約
            _frame_of_life_when_inactivation = _frame_of_life + prm_offset_frames;
        }
    }
}

template<class T>
void Element<T>::inactivateTreeDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwCriticalException("inactivateTreeDelay(0) は無意味である。いつまでも inactivate() されませんよ！！！。意図してますか？ name="<<Node<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= SEC_F(60*60)) { //１時間後
        throwCriticalException("inactivateTreeDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも inactivate() されませんよ！負の数になったのとちがう？ name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        inactivateDelay(prm_offset_frames);
        //callRecursive(&Element<T>::inactivateTreeDelay, prm_offset_frames); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->inactivateTreeDelay(prm_offset_frames);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::inactivateImmed() {
#ifdef MY_DEBUG
    if (_frame_of_life == 0) {
        throwCriticalException("inactivateImmed() アクター生成後すぐにinactivateImmed()することは無意味でおかしい。inactivate()で良くないですか？ name="<<Node<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        _is_active_flg = false;
        _frame_of_life_when_inactivation = _frame_of_life;
        updateActiveInTheTree();
    }
}

template<class T>
void Element<T>::inactivateTreeImmed() {
    if (_can_live_flg) {
        inactivateImmed();
        //callRecursive(&Element<T>::inactivateTreeImmed); //再帰
        //再帰
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->inactivateTreeImmed();
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::end(frame prm_offset_frames) {
    if (_frame_of_life < _frame_of_life_when_end &&
                         _frame_of_life_when_end < _frame_of_life + prm_offset_frames + GGAF_END_DELAY) {
        //既にend()実行済みであり、さらに今回指定のよりも早く _frame_of_life_when_end に到達するため無視する。
        return;
    }
    _frame_of_life_when_end = _frame_of_life + prm_offset_frames + GGAF_END_DELAY;
    inactivateDelay(prm_offset_frames);
    //指定フレーム時には、まずinactivateが行われ、+GGAF_END_DELAY フレーム後 _can_live_flg = falseになる。
    //onEnd()は _can_live_flg = false 時発生
    T* pElementTemp = Node<T>::_pChildFirst;
    while (pElementTemp) {
        pElementTemp->end(prm_offset_frames);
        if (pElementTemp->_is_last_flg) {
            break;
        } else {
            pElementTemp = pElementTemp->_pNext;
        }
    }
}

//template<class T>
//T* Element<T>::extract() {
//    if (_can_live_flg) {
//        return extract();
//    } else {
//        //_TRACE_("[Element<"<<_class_name<<">::extract()] 【警告】 "<<getName()<<"は、死んでいます。");
//        return extract();
//    }
//}

template<class T>
void Element<T>::clean(int prm_num_cleaning) {
    if (Node<T>::_pChildFirst == nullptr) {
        return;
    }

    T* pElementTemp = Node<T>::_pChildFirst->_pPrev;
    T* pWk;

    while (GarbageBox::_cnt_cleaned < prm_num_cleaning) {
        if (pElementTemp->_pChildFirst) {
            //子の子がまだのっている場合さらにもぐる
            pElementTemp->clean(prm_num_cleaning);
            if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }
        if (pElementTemp->_is_first_flg) { //最後の一つ
            if (pElementTemp->_pChildFirst) {
                //子の子がまだのっている場合さらにもぐる
                pElementTemp->clean(prm_num_cleaning);
                if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            GGAF_DELETE(pElementTemp);
            GarbageBox::_cnt_cleaned++;
            if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pChildFirst) {
                //子の子がまだのっている場合さらにもぐる
                pWk->clean(prm_num_cleaning);
                if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            GGAF_DELETE(pWk);
            GarbageBox::_cnt_cleaned++;
            if (GarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }
    }
}

template<class T>
void Element<T>::executeFuncLowerTree(void (*pFunc)(Object*, void*, void*, void*), void* prm1, void* prm2, void* prm3) {
    if (_can_live_flg && _is_active_flg) {
        pFunc(this, prm1, prm2, prm3);
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->executeFuncLowerTree(pFunc, prm1, prm2, prm3);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::throwEventLowerTree(eventval prm_event_val, void* prm_pSource) {
    if (_can_live_flg) {
        onCatchEvent(prm_event_val, prm_pSource);
        T* pElementTemp = Node<T>::_pChildFirst;
        while (pElementTemp) {
            pElementTemp->throwEventLowerTree(prm_event_val, prm_pSource);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
void Element<T>::throwEventUpperTree(eventval prm_event_val, void* prm_pSource) {
    if (_can_live_flg) {
        onCatchEvent(prm_event_val, prm_pSource);
        if (Node<T>::_pParent) {
            T* pElementTemp = Node<T>::_pParent;
            pElementTemp->throwEventUpperTree(prm_event_val, prm_pSource);
        } else {
            //ツリーの頂点なので、再帰終了
        }
    }
}

template<class T>
bool Element<T>::isDisappear() {
    if (_is_active_in_the_tree_flg == false) {
        return true;
    } else {
        return false;
    }
}

template<class T>
Element<T>::~Element() {
    GGAF_DELETE_NULLABLE(_pPhase);
}

}
#endif /*GGAF_CORE_ELEMENT_H_*/
