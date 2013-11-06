#ifndef GGAFCORE_GGAFELEMENT_H_
#define GGAFCORE_GGAFELEMENT_H_
#include "jp/ggaf/core/GgafNode.hpp"

#include "jp/ggaf/core/GgafProgress.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"

namespace GgafCore {

/**
 * ノード(GgafNode<T>)に、様々な状態管理機能を追加したクラス .
 * 所謂タスクシステムに必要な状態遷移機能が実装されている。<BR>
 * 毎フレーム、神(GgafGod)は、この世(GgafUniverse)に、次のメソッドを順に呼び出す仕組みになっている。<BR>
 * nextFrame() > behave() > settleBehavior() > judge() > [preDraw() > draw() > afterDraw()] > doFinally() <BR>
 * アプリケーションに登場するノードは全て、「この世」のツリーに所属するため、全ノードに対して上記の処理が行われる。
 * 上記の内、nextFrame() のみ毎フレーム必ず実行される。<BR>
 * behave(), settleBehavior(), judge(), doFinally() は、活動状態フラグ(_is_active_in_the_tree_flg)が true、かつ、
 * 一時停止フラグ(_was_paused_flg)が false の場合実行される。<BR>
 * preDraw(), draw(), afterDraw() は、次フレームまでの残時間に余裕がある場合、実行される。<BR>
 * 次フレームまでの残時間に余裕が無い場合、神はこの3メソッドをスキップする。
 * 但し、スキップするといっても、MAX_SKIP_FRAME フレームに１回は必ず実行する。<BR>
 * 上記の nextFrame() ～ doFinally() の処理を下位でオーバーライドすれば、タスクシステムの完成である。<BR>
 * しかし、メソッドの直接オーバーライドは非推奨である。オーバーライド用に各メソッド内でコールバックされる<BR>
 * 純粋仮想関数(processXxxxxx()) を用意しているので、そのメソッドをオーバーライドして下さい。<BR>
 * initialize() は、上記の nextFrame() ～ doFinally() を何れかを呼び出す前にインスタンスごとに１回だけ呼ばれる仕組みになっている。<BR>
 * 生存フラグ(_can_live_flg)がfalseの場合は、nextFrame() ～ doFinally() は全て実行されない。<BR>
 * (※旧クラス名はGgafFactor)
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafElement : public GgafNode<T> {

private:

    /**
     * ツリー構造において、再帰呼び出しを行う。
     * @param pFunc 再帰呼び出しするメソッド
     */
    inline void callRecursive(void (GgafElement<T>::*pFunc)()) {
        T* pElementTemp = GgafNode<T>::_pSubFirst;
        if (pElementTemp) {
            while(true) {
                (pElementTemp->*pFunc)(); //実行
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }

    /**
     * ツリー構造において、再帰呼び出しを行う。
     * @param pFunc 再帰呼び出しするメソッド(frame 引数有り)
     * @param prm_frame pFuncの引数であるframe
     */
    inline void callRecursive(void (GgafElement<T>::*pFunc)(frame), frame prm_frame) {
        T* pElementTemp = GgafNode<T>::_pSubFirst;
        if (pElementTemp) {
            while(true) {
                (pElementTemp->*pFunc)(prm_frame); //実行
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }


public:
    /** [r]神への近道 */
    GgafGod* _pGod;
    /** [r]initializeが行われたどうかのフラグ(true=行われた) */
    bool _was_initialize_flg;
    /** [r]ノードが誕生(addSubされた）時からのフレーム数総計(但し、_was_paused_flg = true 時は加算され無い) */
    frame _frame_of_life;
    /** [r]ノードが誕生(addSubされた）時から、振舞ったフレーム数総計(但し、_was_paused_flg = true 又は _is_active_flg = false 時は加算され無い) */
    frame _frame_of_behaving;
    /** [r]ノードが活動開始(onActive())時からの振舞ったフレーム数総計(但し、_was_paused_flg = true 又は _is_active_flg = false 時は加算され無い) */
    frame _frame_of_behaving_since_onActive;

    /** [r]ノード活動フラグ */
    bool _is_active_flg;
    /** [r]ノード活動フラグ(自ツリーも考慮あり) */
    bool _is_active_in_the_tree_flg;
    /** [r]一時停止フラグ */
    bool _was_paused_flg;
    /** [r]ノード生存フラグ */
    bool _can_live_flg;

    /** [r]次フレームの一時停止フラグ、次フレームのフレーム加算時 _was_paused_flg に反映される */
    bool _was_paused_flg_in_next_frame;
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
    /** [r]カレントフレーム内で一度でもリセットが実行されればtrue。毎フレーム false に更新される */
    bool _is_already_reset;
    /** [r]状態進捗管理オブジェクト */
    GgafProgress* _pProg;

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
     * 掃除(実行対象：配下ノード全て、自分自身はdeleteされません) .
     * 神が処理時間に余裕がでたとき等に、神が呼びだす。<BR>
     * 配下ノードの中にノード生存フラグ(_can_live_flg)が false になっているノードがあれば
     * prm_num_cleaning 個だけ delete する。<BR>
     * @param prm_num_cleaning 解放するオブジェクト数
     */
    virtual void clean(int prm_num_cleaning);

    /**
     * ノード初期処理(実行対象：thisのみ) .
     * インスタンス生成後、何れかが呼び出される前に、最初に必ず１回だけ呼び出される。<BR>
     * 補足：initialize()が呼び出された後、reset() が呼び出される。
     */
    virtual void initialize() = 0;

    /**
     * ノードのフレームを加算と、フレーム開始にあたってのいろいろな初期処理(実行対象：自ツリー全て) .
     * 毎フレーム必ず実行され、主に様々な状態フラグの更新を行う。 <BR>
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
     * ※基本は先頭→末尾の順、但しサブが存在すれば先に実行、存在しなければ次(隣)を実行。
     * </pre>
     * メソッド説明に『(実行対象：自ツリー全て)』と記述されている場合は、全て上記の順序で実行される。
     */
    virtual void nextFrame();

    /**
     * ノードのフレーム毎の振る舞い処理(実行対象：自ツリー全て) .
     * この処理では、全ノード座標移動処理を行うこととする。<BR>
     * 実装用の processBehavior() がコールバックされるためのフラグの条件は、<BR>
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （ _is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg ）の場合である。 <BR>
     * behave() は 仮想関数 processBehavior() をコールした後、配下のノード全てについて behave() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processBehavior() をオーバーライドして具体的な座標移動ロジックを実装する。 <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して behave() 実行後、次は settleBehavior() を実行することになる。<BR>
     */
    virtual void behave();

    /**
     * ノードのフレーム毎の振る舞い事後処理(実行対象：自ツリー全て) .
     * この処理では、全ノード座標移動が完了していることが保証された後の処理を行う事とする設計。<BR>
     * 更新が完了した座標情報から、それに伴う内部の様々なステータス等の更新処理をここで行う事を目的とする<BR>
     * 実装用の processSettlementBehavior() がコールバックされるためのフラグの条件は、<BR>
     * behave()と同じく活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット。<BR>
     * つまり ( _is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg )の場合である。 <BR>
     * settleBehavior()は、仮想関数 processSettlementBehavior() をコールした後、配下のノード全てについて settleBehavior() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processSettlementBehavior() をオーバーライドしてロジックを実装することとする。 <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して settleBehavior() 実行後、次に judge() を実行することになる。<BR>
     */
    virtual void settleBehavior();

    /**
     * ノードのフレーム毎の判定処理(実行対象：自ツリー全て) .
     * この処理では、ノード間の様々な判定処理を行う事とする設計。<BR>
     * 全ノード座標移動処理と伴なうステータス類の更新が完全に完了してが前提とする処理が行われる。<BR>
     * 実装用の processJudgement() がコールバックされるためのフラグの条件は、behave()と同じく、<BR>
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * つまり ( _is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg )の場合 <BR>
     * judge() は 仮想関数 processJudgement() をコールした後、配下のノード全てについて judge() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックで本メソッドを直接呼び出しを行わないこととする。<BR>
     * 下位クラスではコールされる processJudgement() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して judge() 実行後、<BR>
     * 神(GgafGod)はこの後、次フレームまでの残時間に余裕があれば preDraw() 無ければ doFinally() を実行することになる。<BR>
     */
    virtual void judge();

    /**
     * ノードのフレーム毎の描画事前処理(実行対象：自ツリー全て)（フレームスキップされて呼び出されない場合もある。） .
     * 実装用の processPreDraw() がコールバックされる条件は、活動フラグ、生存フラグがセット<BR>
     * (つまり _is_active_flg && _can_live_flg)の場合である。 <BR>
     * processPreDraw() をコールした後、配下のノード全てについて preDraw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processPreDraw() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して preDraw() 実行後、次に draw() を実行することになる。<BR>
     */
    virtual void preDraw();

    /**
     * ノードのフレーム毎の描画本処理(実行対象：自ツリー全て)（フレームスキップされて呼び出されない場合もある。） .
     * 実装用の processDraw() がコールバックされる条件は、活動フラグ、生存フラグがセット<BR>
     * (つまり _is_active_in_the_tree_flg && _can_live_flg)の場合である。 <BR>
     * processDraw() をコールした後、配下のノード全てについて draw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processDraw() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して draw() 実行後、次に afterDraw() を実行することになる。<BR>
     */
    virtual void draw();

    /**
     * ノードのフレーム毎の描画事後処理(実行対象：自ツリー全て)（フレームスキップされて呼び出されない場合もある。） .
     * 実装用の processAfterDraw() がコールバックされる条件は、活動フラグ、生存フラグがセット<BR>
     * (つまり _is_active_in_the_tree_flg && _can_live_flg)の場合である。 <BR>
     * processAfterDraw() をコールした後、配下のノード全てについて afterDraw() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processAfterDraw() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して afterDraw() 実行後、次に doFinally() を実行することになる。<BR>
     */
    virtual void afterDraw();

    /**
     * ノードのフレーム毎の最終処理(実行対象：自ツリー全て) .
     * 座標移動処理、判定処理、描画処理が終了した後に、最後に行う後始末処理を行う事とする設計。<BR>
     * 実装用の processFinal() がコールバックされる条件は、
     * 活動フラグ、生存フラグがセット、かつ一時停止フラグがアンセット<BR>
     * （_is_active_in_the_tree_flg && !_was_paused_flg && _can_live_flg）の場合である。 <BR>
     * processFinal() をコールした後、配下のノード全てについて doFinally() を再帰的に実行する。<BR>
     * 神(GgafGod)が実行するメソッドであり、通常は下位ロジックでは使用しないはずである。<BR>
     * 下位クラスではコールされる processFinal() をオーバーライドしてロジックを実装する <BR>
     * 神(GgafGod)は、この世(GgafUniverse)に対して doFinally() 実行後、<BR>
     * 次フレームまでの残時間に余裕があれば clean() を実行する。<BR>
     * その後は nextFrame() を実行することになる。<BR>
     */
    virtual void doFinally();

    /**
     * 非活動→活動時に切り替わった時のコールバック .
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
     * 活動→非活動時に切り替わった時のコールバック .
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
     * preDraw() 時の処理先頭でコールバックされる。 但し、神(GgafGod)が描画スキップした場合、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画事前処理を実装する。<BR>
     * 個別描画事前処理とは、主に当たり背景描画などである。<BR>
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processJudgement() が実行済みであることも保証する。<BR>
     * さらに、本メンバ関数実行後、processDraw()、processAfterDraw() が呼び出されることも保証される。
     */
    virtual void processPreDraw() {};

    /**
     * ノードのフレーム毎の個別描画本処理を実装。(本フレームワーク実装用／ユーザー実装用) .
     * draw() 時の処理先頭でコールバックされる。 但し、preDraw() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
     * このメンバ関数をオーバーライドして、ノード個別描画本処理を実装する。<BR>
     * 個別描画本処理とは主にキャラクタや、背景の描画を想定している。
     * 本メンバ関数がコールバックされると言う事は、全ノード対して、processPreDraw() が実行済みであることを保証する。<BR>
     */
    virtual void processDraw() = 0;

    /**
     * ノードのフレーム毎の個別表示事後処理を記述。(本フレームワーク実装用) .
     * afterDraw() 時の処理先頭でコールバックされる。 但し、preDraw() と同様に神(GgafGod)が描画スキップされた場合は、フレーム内で呼び出されません。<BR>
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
     * イベントを受け取る側は、onCatchEvent(hashval, void) を実装が必要です。<BR>
     * 自身の onCatchEvent(hashval, void) にも通知されるので注意して下さい。<BR>
     * @param prm_no イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void throwEventUpperTree(hashval prm_no, void* prm_pSource);

    /**
     * 自ノードと自ノードよりも親にあたるノード全てにイベントメッセージを通知(通知対象：ツリー全て) .
     * イベントを受け取る側は、onCatchEvent(hashval, void) を実装が必要です。<BR>
     * 自身の onCatchEvent(hashval, void) にも通知されるので注意して下さい。<BR>
     * 汎用引数 void* には、this が設定されます。<BR>
     * @param prm_no イベントメッセージ番号
     */
    virtual void throwEventUpperTree(hashval prm_no) {
        throwEventUpperTree(prm_no, this);
    }


    /**
     * 自ノードとその配下ノード全てにイベントメッセージを通知します(通知対象：所属の親全て) .
     * イベントを受け取る側は、onCatchEvent(hashval, void) を実装が必要である。<BR>
     * 自身の onCatchEvent(hashval, void) にも通知されるので注意して下さい。<BR>
     * @param prm_no イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void throwEventLowerTree(hashval prm_no, void* prm_pSource);

    /**
     * 自ノードとその配下ノード全てにイベントメッセージを通知します(通知対象：所属の親全て) .
     * イベントを受け取る側は、onCatchEvent(hashval, void) を実装が必要である。<BR>
     * 自身の onCatchEvent(hashval, void) にも通知されるので注意して下さい。<BR>
     * 汎用引数 void* には、this が設定されます。<BR>
     * @param prm_no イベントメッセージ番号
     */
    virtual void throwEventLowerTree(hashval prm_no) {
        throwEventLowerTree(prm_no, this);
    }

    /**
     * イベント発生時のコールバック .
     * throwEventUpperTree() throwEventLowerTree() で発した場合コールバックされます。<BR>
     * @param prm_no イベントメッセージ番号
     * @param prm_pSource  イベント用汎用ポインタ
     */
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) = 0;


    virtual bool isDisappear();
    /**
     * 神に謁見 .
     * @return  呼ばれて出てきた神
     */
    virtual GgafGod* askGod() = 0;

    //==================状態遷移メソッド郡==================>
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
     * 一時停止状態にする(実行対象：this のみ) .
     * 正確には、自ノードだけ次フレームから一時停止にする予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理(nextFrame())内で、めでたく一時停止状態(_was_paused_flg = true)になる。<BR>
     * したがって、本メソッドを実行しても『同一フレーム内』は一時停止状態の変化は無く一貫性は保たれる。<BR>
     * 配下ノードには何も影響がありません。<BR>
     */
    virtual void pause();

    /**
     * 一時停止状態にする(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に pause() が実行される。<BR>
     */
    virtual void pauseTree();

    /**
     * 即座に一時停止状態にする(実行対象：this のみ) .
     * 即座に一時停止状態フラグを更新(_was_paused_flg = true)する。<BR>
     * 『同一フレーム内』であっても、既に処理されたノードと未処理のノードで、異なる状態になってしまう。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void pauseImmed();

    /**
     * 即座に一時停止状態にする(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に pauseImmed() が実行される。<BR>
     * pauseImmed() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void pauseTreeImmed();

    //===================
    /**
     * 一時停止状態を解除する(実行対象：this のみ) .
     * 正確には、自ノードだけ次フレームから一時停止状態を解除する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理(nextFrame())内で、めでたく一時停止状態解除(_was_paused_flg = false)になる。<BR>
     * したがって、本メソッドを実行しても『同一フレーム内』は一時停止状態の変化は無く一貫性は保たれる。<BR>
     * 配下ノードには何も影響がありません。<BR>
     */
    virtual void unpause();

    /**
     * 一時停止状態を解除する(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に unpause() が実行される。<BR>
     */
    virtual void unpauseTree();

    /**
     * 即座に一時停止状態を解除する(実行対象：this のみ) .
     * 即座に一時停止状態フラグを更新(_was_paused_flg = false)する。<BR>
     * 『同一フレーム内』であっても、既に処理されたノードと未処理のノードで、異なる状態になってしまう。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void unpauseImmed();

    /**
     * 即座に一時停止状態を解除する(実行対象：自ツリー全て) .
     * 自身と配下ノード全てについて再帰的に unpauseImmed() が実行される。<BR>
     * unpauseImmed() の説明を要参照。<BR>
     * 使用するときは、他ノードの影響を良く考えて注意して使用すること。<BR>
     */
    virtual void unpauseTreeImmed();


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
    // 生成されたノードに、「表示」「非表示」という状態が存在し、使いまわす場合。
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
     * _can_live_flg がアンセットされることにより、自動的にツリーから切り離されゴミ箱(GgafGarbageBox) 配下に、
     * 所属することになる。その後、神(GgafGod)が余裕のある時 (FPSが高いとき) を見計らい clean() メソッドにより、<BR>
     * GgafGarbageBox に所属する配下ノードを delete するし、メモリーから消え去る。<BR>
     * <b>【注意】</b><BR>
     * お気づきかと思うが、本メソッドを実行して引数の猶予フレーム後になっても、
     * GgafGarbageBox 配下に移るだけで、直ぐには deleteされるとは限らないため、
     * 不正ポインタによる潜在的バグを起こす。細心の注意をはらおう～（うん、そう決めた）<BR>
     * @param prm_offset_frames 生存終了猶予フレーム(1～)
     */
    virtual void end(frame prm_offset_frames = 1);

    /**
     * ゴミ箱に放り込まれる直前に呼び出されるコールバック .
     * end(frame) 実行後、ゴミ箱(GgafGarbageBox) に取り込まれる直前に呼び出される。<BR>
     * 最速で、end(frame) で指定したフレーム + GGAF_END_DELAY 後に発生する。<BR>
     * 処理がもたつくと、それ以上の先のフレームで発生する。<BR>
     * 直前に処理が必要な場合は、オーバーライドして実装可能。<BR>
     */
    virtual void onEnd() {
    }

    /**
     * 自ノードを最終ノードに移動する .
     * 正確には、次フレームから最終ノードに移動する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理(nextFrame())内で、自ノードを最終ノードに移動させる処理が行われる。<BR>
     * 自ノードは切り離されて、両隣のノードは新たに接合し、現在の最終ノードの次のノードしてインサートされる。<BR>
     * 本メソッドを実行しても『同一フレーム内』は、ノード移動は無いため、一貫性は保たれる。<BR>
     */
    virtual void moveLast() override {
        _will_mv_last_in_next_frame_flg = true;
    }

    /**
     * 即座に自ノードを最終ノードに移動する .
     * 即座に自ノードを最終ノードに移動（ローテーション）させることにより、
     * 同一フレーム内で、ノード処理の２重実行、処理が行われないノード等が発生する恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void moveLastImmed() {
        GgafNode<T>::moveLast();
    }

    /**
     * 自ノードを先頭ノードに移動する .
     * 正確には、次フレームから最終ノードに移動する予約フラグを立てる。<BR>
     * そして、次フレーム先頭処理(nextFrame())内で、自ノードを先頭ノードに移動させる処理が行われる。<BR>
     * 自ノードは切り離されて、両隣のノードは新たに接合し、現在の先頭ノードの前のノードしてインサートされる。<BR>
     * 本メソッドを実行しても『同一フレーム内』は、ノード移動は無いため、一貫性は保たれる。<BR>
     */
    virtual void moveFirst() override {
        _will_mv_first_in_next_frame_flg = true;
    }

    /**
     * 即座に自ノードを先頭ノードに移動する .
     * 即座に自ノードを先頭ノードに移動（ローテーション）させることにより、
     * 同一フレーム内で、ノード処理の２重実行、処理が行われないノード等が発生する恐れがある。<BR>
     * 他ノードの影響、ツリー構造を良く考えて使用すること。<BR>
     */
    virtual void moveFirstImmed() {
        GgafNode<T>::moveFirst();
    }

    /**
     * 自ノードが非活動から活動状態に切り替わったかどうか調べる .
     * onActive() が呼ばれたフレームのみ true になる。
     * onActive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備しました。<BR>
     * @return  bool true:非活動から活動状態切り替わった／false:切り替わっていない
     */
    inline bool onChangeToActive();

    /**
     * 自ノードが活動状態から非活動に切り替わったかどうか調べる .
     * onInctive() が呼ばれたフレームのみ true になる。
     * onInctive() オーバーライドで事足りる場合は、その方がすっきり記述できるはず。<BR>
     * 他のノードの状態変化を知りたい時のために、本メソッドを準備しました。<BR>
     * @return  bool true:活動状態から非活動に切り替わった／false:切り替わっていない
     */
    inline bool onChangeToInactive();

    /**
     * 生存可能状態か調べる
     * @return  bool true:生存可能状態／false:生存不可状態
     */
    inline bool canLive() {
        return _can_live_flg;
    }

    /**
     * 活動中か調べる .
     * 自身フラグの状態で活動中かどうか判断
     * @return  bool true:活動中／false:非活動中
     */
    inline bool isActive();

    /**
     * 自ツリーで活動中かどうか判断 <BR>
     * たとえば、自身フラグの状態で活動中でも、親が活動中でない場合、
     * 自身は活動出来ない。それも考慮した上で、本当に活動中かどうか判定を行う。
     * @return true:自ツリーで活動中／false:自ツリーで非活動中
     */
    inline bool isActiveInTheTree();

    /**
     * 一時停止状態かどうか判断
     * @return true:一時停止状態／false:一時停止状態では無い
     */
    inline bool wasPaused();

    /**
     * 終了宣言したかどうか .
     * end(frame) が実行済みかどうか調べます。
     * @return true:終了宣言済み／false:まだ終了宣言されていない
     */
    inline bool wasDeclaredEnd();

    /**
     * 振る舞い状態時に加算されるフレーム数を取得する .
     * 「振る舞い状態」とは、canBehave() → true の条件成立時の事を意味する。<BR>
     * 0 Frame状態は基本存在せず、1 Frame ～ からの値になる。但し例外的に<BR>
     * 生成時コンストラクタ内、および、最初の initialize() 内では 0 Frame を返す。<BR>
     * 初回実行の onActive()、processBehavior()、processJudgement() 等の中で 1 になっている。<BR>
     * 以降、振る舞い態時にフレーム加算される。<BR>
     * @return 振る舞いフレーム数総計
     */
    inline frame getBehaveingFrame() {
        return _frame_of_behaving;
    }

    /**
     * 直近の onActive() から開始した振る舞い状態は何フレーム目かを返す。 .
     * 汎用オブジェクトなど、一度生成して使いまわす(deleteしない)場合、<BR>
     * 消失時に inactivate() 、出現時 activate() を繰り返すことが想定される。<BR>
     * そのような場合に、何フレーム目かを取得する際に都合が良いメソッド。<BR>
     * onActive() コールバック条件成立時にリセット(0)される。<BR>
     * getBehaveingFrame() と同じタイミングで加算される。processBehavior()では、1 ～ を返す。
     * @return onActive() からの振る舞いフレーム数
     */
    inline frame getActiveFrame() {
        return _frame_of_behaving_since_onActive;
    }

    /**
     * 自身と配下全てのオブジェクトに対して指定の関数を実行させる .
     * 配下オブジェクト（アクターかシーン）のポインタが、引数関数ポインタの pFuncの第１引数に渡ってくる。<BR>
     * 引数関数ポインタの pFunc の第２引数には、executeFuncLowerTree 呼び出し時の prm1(引数１)のポインタが渡ってくる。<BR>
     * 引数関数ポインタの pFunc の第３引数には、executeFuncLowerTree 呼び出し時の prm2(引数２)のポインタが渡ってくる。<BR>
     * 配下のオブジェクトが何であるのか判っている上で使用しないと危険である。<BR>
     * あと、ラムダ式とキャプチャーを使わせてください。<BR>
     *
     * ＜使用例＞<BR>
     * XXXXActor 配下のオブジェクト全てのアクター(但しGgafDxGeometricActor)のメンバ変数 _x に、
     * XXXXActorメンバ変数 _velo の値を加算させる。<BR>
     * XXXXActor クラスの実装サンプルを以下に記す<BR>
     * <code><pre>
     *
     * class XXXXActor : public GgafDxGeometricActor {
     * public :
     *     int velo_;
     *
     *     static void addX(GgafObject* pThat, void* p1, void* p2) {
     *         if (pThat->instanceOf(Obj_GgafDxGeometricActor)) { //GgafDxGeometricActorならば
     *             GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
     *             pActor->_x += (*((int*)p1));  //_x 加算。p1 には velo_ へのポインタが渡ってくる
     *         }
     *     }
     *
     *     void processBehavior() {
     *         //配下アクター全てにaddX実行
     *         velo_ = 1000;
     *         executeFuncLowerTree(XXXXActor::addX, &velo_, nullptr);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc オブジェクトに実行させたい関数。パラメータは(GgafObject*, void*, void*) 固定。
     * @param prm1 渡したい引数その１
     * @param prm2 渡したい引数その２
     */
    virtual void executeFuncLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2);


    /**
     * 進捗管理オブジェクト(GgafProgress) が管理する進捗の場合数を設定する。
     * 本メソッド実行後、_pProg メンバーが使用可能になる。
     * @param prm_num 進捗の場合の数
     */
    virtual void useProgress(int prm_num = 10) {
        if (_pProg == nullptr) {
            _pProg = NEW GgafProgress(&_frame_of_behaving, prm_num);
        } else {
            _TRACE_("＜警告＞useProgress() ["<<GgafNode<T>::getName()<<"] は既に useProgress している。以前の進捗の場合の数="<<_pProg->_num_progress<<"。今回引数 prm_num="<<prm_num);
            if (_pProg->_num_progress != prm_num) {
                throwGgafCriticalException("useProgress() ["<<GgafNode<T>::getName()<<"] は既に useProgress している。ダメじゃないのか？！。\n以前の進捗の場合の数="<<_pProg->_num_progress<<"。今回引数 prm_num="<<prm_num);
            }
        }
    }

    virtual GgafProgress* createProgress(int prm_num = 10) {
        return NEW GgafProgress(&_frame_of_behaving, prm_num);
    }

    /**
     * ツリー考慮ありノード活動フラグ(自)
     */
    virtual void updateActiveInTheTree() = 0;

};

///////////////////////////////////////////////////////////////// ここからは実装部

template<class T>
GgafElement<T>::GgafElement(const char* prm_name) : GgafCore::GgafNode<T>(prm_name),
_pGod(nullptr),
_was_initialize_flg(false),
_frame_of_life(0),
_frame_of_behaving(0),
_frame_of_behaving_since_onActive(0),
_is_active_flg(true),
_is_active_in_the_tree_flg(false),
_was_paused_flg(false),
_can_live_flg(true),
_was_paused_flg_in_next_frame(false),
_will_end_after_flg(false),
_frame_of_life_when_end(MAX_FRAME),
_will_activate_after_flg(false),
_frame_of_life_when_activation(0),
_will_inactivate_after_flg(false),
_frame_of_life_when_inactivation(0),
_on_change_to_active_flg(false),
_on_change_to_inactive_flg(false),
_will_mv_first_in_next_frame_flg(false),
_will_mv_last_in_next_frame_flg(false),
_is_already_reset(false),
_pProg(nullptr)
{

}

template<class T>
void GgafElement<T>::nextFrame() {
    //moveLast予約時
    if (_will_mv_last_in_next_frame_flg) {
        _will_mv_last_in_next_frame_flg = false;
        moveLastImmed();
        return;
        //即returnする事は重要。nextFrame() 処理の２重実行をさけるため。
        //このノードは、末尾に回されているため、必ずもう一度 nextFrame() の機会が訪れる。
    }
    _was_paused_flg = _was_paused_flg_in_next_frame;
    if (!_was_paused_flg) {
        _frame_of_life++;
        if (_will_end_after_flg && _frame_of_life_when_end == _frame_of_life) {
            _can_live_flg = false; //終了の時だ
        }
        _on_change_to_active_flg = false;
        _on_change_to_inactive_flg = false;
        if (_can_live_flg) {
            if (_is_active_flg) {  //現在activate
                if (_frame_of_life == 1) { //現在activate で １フレーム目
                    _on_change_to_active_flg = true;  //onActive確定
                } else { //現在activate で ２フレーム目以降

                    if (_will_inactivate_after_flg) {  //現在activate で、２フレーム目以降で、
                                                       //さらに inactivate予定
                        if (_frame_of_life == _frame_of_life_when_inactivation) { //現在activate で、２フレーム目以降で、
                                                                                  //inactivate予定で、今inactivateになる時が来た
                            _is_active_flg = false; //活動フラグOFF
                            _on_change_to_inactive_flg = true; //onInactive確定
                        } else { //現在activate で、２フレーム目以降で、inactivate予定だが、
                                 //未だinactivateになる時ではなかった
                            //特に何もない
                        }
                    } else { //現在activate で、２フレーム目以降で、
                             //さらに inactivateもありゃしません。
                        //特に何もない
                    }
                }
            } else { //現在inactivate
                if (_will_activate_after_flg) { //現在inactivate だが、activate予定。

                    if(_frame_of_life == _frame_of_life_when_activation) { //現在inactivate だが、activate予定
                                                                           //そして、activateになる時が来た
                        _is_active_flg = true; //活動フラグON
                        _on_change_to_active_flg = true;  //onActive処理
                    } else { //現在inactivate だが、activate予定
                             //そして、まだactivateになる時は来ない
                        //特に何もない
                    }
                } else {  //現在inactivate で、activate予定も無し・・・
                    //特に何もない
                }
            }
            _is_already_reset = false;

            updateActiveInTheTree();     //_is_active_in_the_tree_flg を更新

            if (_is_active_in_the_tree_flg) {
                _frame_of_behaving++;
                // 進捗を反映
                if (_pProg) {
                    _pProg->update();
                }
                _frame_of_behaving_since_onActive++;
            }
            //onActive処理
            if (_on_change_to_active_flg) {
                if (!_was_initialize_flg) {
                    initialize();       //初期化
                    _was_initialize_flg = true;
                    reset(); //リセット
                }
                _frame_of_behaving_since_onActive = 1; //リセット
                onActive(); //コールバック
                _frame_of_life_when_activation = 0;
                _will_activate_after_flg = false;
            }
            //onInactive処理
            if (_on_change_to_inactive_flg) {
                onInactive(); //コールバック
                _frame_of_life_when_inactivation = 0;
                _will_inactivate_after_flg = false;
            }
        }
    }

    //配下の全ノードに再帰的にnextFrame()実行
    T* pElement = GgafNode<T>::_pSubFirst; //一つ配下の先頭ノード
    if (pElement) {
        while(!pElement->_is_last_flg) {
            //一つ配下の先頭～中間ノードに nextFrame()
            pElement->nextFrame();
            if (pElement->_can_live_flg) {
                pElement = pElement->_pNext;
            } else {
                pElement->onEnd();
                pElement = pElement->_pNext; //一個進ませて退避させてから
                GgafGarbageBox::_pGarbageBox->add(pElement->_pPrev); //一個前をゴミ箱へ(連結が切れる)
            }
        }
        //一つ配下の末尾ノードに nextFrame()
        pElement->nextFrame();
        if (pElement->_can_live_flg) {
            //OK何もしない
        } else {
            pElement->onEnd();
            GgafGarbageBox::_pGarbageBox->add(pElement); //ゴミ箱へ
        }
    }

    if (_will_mv_first_in_next_frame_flg) {
        _will_mv_first_in_next_frame_flg = false;
        moveFirstImmed();
        //moveFirstを一番最後にすることは重要。
        //これは nextFrame() の２重実行を避けるため。
    }
}

template<class T>
void GgafElement<T>::behave() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg && !_was_paused_flg) {
        processBehavior();    //ユーザー実装用
        callRecursive(&GgafElement<T>::behave); //再帰
    }
}

template<class T>
void GgafElement<T>::settleBehavior() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) { //_was_paused_flg は忘れていません
        processSettlementBehavior(); //フレームワーク用
        callRecursive(&GgafElement<T>::settleBehavior); //再帰
    }
}

template<class T>
void GgafElement<T>::judge() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg && !_was_paused_flg) {
        processJudgement();    //ユーザー実装用
        callRecursive(&GgafElement<T>::judge); //再帰
    }
}

template<class T>
void GgafElement<T>::preDraw() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) {
        processPreDraw();
        callRecursive(&GgafElement<T>::preDraw); //再帰
    }
}

template<class T>
void GgafElement<T>::draw() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) {
        processDraw();
        callRecursive(&GgafElement<T>::draw); //再帰
    }
}

template<class T>
void GgafElement<T>::afterDraw() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) {
        processAfterDraw();
        callRecursive(&GgafElement<T>::afterDraw); //再帰
    }
}

template<class T>
void GgafElement<T>::doFinally() {
    if ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg && !_was_paused_flg) {
        processFinal();
        callRecursive(&GgafElement<T>::doFinally); //再帰
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
            onReset();
            _is_already_reset = true;
        }
        callRecursive(&GgafElement<T>::resetTree); //再帰
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
        callRecursive(&GgafElement<T>::activateTree); //再帰
    }
}

template<class T>
void GgafElement<T>::activateImmed() {
    if (_can_live_flg) {
        _is_active_flg = true;
    }
}

template<class T>
void GgafElement<T>::activateTreeImmed() {
    if (_can_live_flg) {
        activateImmed();
        callRecursive(&GgafElement<T>::activateTreeImmed); //再帰
    }
}

template<class T>
void GgafElement<T>::activateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("activateDelay(0) は無意味である。いつまでも activate() されませんよ！！！。意図してますか？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //１時間後
        throwGgafCriticalException("activateDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも activate() されませんよ！！！。負の数になったのとちがう？。 name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
#ifdef MY_DEBUG
        if (_is_active_flg) {
            _TRACE_("＜警告＞activateDelay("<<prm_offset_frames<<") しましたけど、既に活動状態ですよ。意図してますか？ name="<<GgafNode<T>::_name<<" this="<<this);
        }
#endif
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
#ifdef MY_DEBUG
    if (prm_frames == 0) {
        throwGgafCriticalException("activateWhile(0) は無意味である。いつまでも activate() されませんよ！！！。意図してますか？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_frames >= 60*60*60) { //１時間後
        throwGgafCriticalException("activateWhile("<<prm_frames<<") って遅すぎるんちゃうん？。いつまでも activate() されませんよ！負の数になったのとちがう？。 name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        _will_activate_after_flg = true;
        _frame_of_life_when_activation = _frame_of_life + 1;
        _will_inactivate_after_flg = true;
        _frame_of_life_when_inactivation = _frame_of_life + prm_frames;
    }
}

template<class T>
void GgafElement<T>::activateTreeDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("activateTreeDelay(0) は無意味である。いつまでも activate() されませんよ！！！。意図してますか？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //１時間後
        throwGgafCriticalException("activateTreeDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも activate() されませんよ！負の数になったのとちがう？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        activateDelay(prm_offset_frames);
        callRecursive(&GgafElement<T>::activateTreeDelay, prm_offset_frames); //再帰
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
        callRecursive(&GgafElement<T>::inactivateTree); //再帰
    }
}

template<class T>
void GgafElement<T>::inactivateDelay(frame prm_offset_frames) {
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("inactivateDelay(0) は無意味である。いつまでも inactivate() されませんよ！！！。意図してますか？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //１時間後
        throwGgafCriticalException("inactivateDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも inactivate() されませんよ！負の数になったのとちがう？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
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
#ifdef MY_DEBUG
    if (prm_offset_frames == 0) {
        throwGgafCriticalException("inactivateTreeDelay(0) は無意味である。いつまでも inactivate() されませんよ！！！。意図してますか？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
    if (prm_offset_frames >= 60*60*60) { //１時間後
        throwGgafCriticalException("inactivateTreeDelay("<<prm_offset_frames<<") って遅すぎるんちゃうん？。いつまでも inactivate() されませんよ！負の数になったのとちがう？ name="<<GgafNode<T>::_name<<" this="<<this);
    }
#endif
    if (_can_live_flg) {
        inactivateDelay(prm_offset_frames);
        callRecursive(&GgafElement<T>::inactivateTreeDelay, prm_offset_frames); //再帰
    }
}

template<class T>
void GgafElement<T>::inactivateImmed() {
    if (_can_live_flg) {
        _is_active_flg = false;
    }
}

template<class T>
void GgafElement<T>::inactivateTreeImmed() {
    if (_can_live_flg) {
        inactivateImmed();
        callRecursive(&GgafElement<T>::inactivateTreeImmed); //再帰
    }
}

template<class T>
void GgafElement<T>::pauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
        callRecursive(&GgafElement<T>::pauseTree); //再帰
    }
}

template<class T>
void GgafElement<T>::pause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::pauseTreeImmed() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
        callRecursive(&GgafElement<T>::pauseTreeImmed); //再帰
    }
}

template<class T>
void GgafElement<T>::pauseImmed() {
    if (_can_live_flg) {
        _was_paused_flg = true;
        _was_paused_flg_in_next_frame = true;
    }
}

template<class T>
void GgafElement<T>::unpauseTree() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
        callRecursive(&GgafElement<T>::unpauseTree); //再帰
    }
}

template<class T>
void GgafElement<T>::unpause() {
    if (_can_live_flg) {
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::unpauseTreeImmed() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
        callRecursive(&GgafElement<T>::unpauseTreeImmed); //再帰
    }
}

template<class T>
void GgafElement<T>::unpauseImmed() {
    if (_can_live_flg) {
        _was_paused_flg = false;
        _was_paused_flg_in_next_frame = false;
    }
}

template<class T>
void GgafElement<T>::end(frame prm_offset_frames) {
    if (_will_end_after_flg) {
        //既にend()実行済みの場合、より早くend()するならば有効とする
        if (_frame_of_life_when_end < _frame_of_life + prm_offset_frames + GGAF_END_DELAY) {
            //今回指定の方が遅いフレーム指定であるため無視する。
            return;
        }
    }
    _will_end_after_flg = true;
    _frame_of_life_when_end = _frame_of_life + prm_offset_frames + GGAF_END_DELAY;
    inactivateDelay(prm_offset_frames);
    //指定フレーム時には、まずinactivateが行われ、+GGAF_END_DELAY フレーム後 _can_live_flg = falseになる。
    //onEnd()は _can_live_flg = false 時発生
    if (GgafNode<T>::_pSubFirst) {
        T* pElementTemp = GgafNode<T>::_pSubFirst;
        while(true) {
            pElementTemp->end(prm_offset_frames);
            if (pElementTemp->_is_last_flg) {
                break;
            } else {
                pElementTemp = pElementTemp->_pNext;
            }
        }
    }
}

template<class T>
bool GgafElement<T>::isActive() {
    return (_can_live_flg && _is_active_flg) ? true : false;
}
template<class T>
bool GgafElement<T>::isActiveInTheTree() {
    return ( _is_active_flg && _is_active_in_the_tree_flg && _can_live_flg) ? true : false;
}

template<class T>
bool GgafElement<T>::onChangeToActive() {
    return (_can_live_flg && _on_change_to_active_flg) ? true : false;
}

template<class T>
bool GgafElement<T>::onChangeToInactive() {
    return (_can_live_flg && _on_change_to_inactive_flg) ? true : false;
}

template<class T>
bool GgafElement<T>::wasPaused() {
    return _was_paused_flg;
}

template<class T>
bool GgafElement<T>::wasDeclaredEnd() {
    return (_will_end_after_flg || _can_live_flg == false) ? true : false;
}

//template<class T>
//T* GgafElement<T>::extract() {
//    if (_can_live_flg) {
//        return extract();
//    } else {
//        //_TRACE_("[GgafElement<"<<_class_name<<">::extract()] ＜警告＞ "<<getName()<<"は、死んでいます。");
//        return extract();
//    }
//}

template<class T>
void GgafElement<T>::clean(int prm_num_cleaning) {
    if (GgafNode<T>::_pSubFirst == nullptr) {
        return;
    }

    T* pElementTemp = GgafNode<T>::_pSubFirst->_pPrev;
    T* pWk;

    while(GgafGarbageBox::_cnt_cleaned < prm_num_cleaning) {
        if (pElementTemp->_pSubFirst) {
            //子の子がまだのっている場合さらにもぐる
            pElementTemp->clean(prm_num_cleaning);
            if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                break;
            }
        }
        if (pElementTemp->_is_first_flg) { //最後の一つ
            if (pElementTemp->_pSubFirst) {
                //子の子がまだのっている場合さらにもぐる
                pElementTemp->clean(prm_num_cleaning);
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            if (pElementTemp->_can_live_flg == false) {
                GGAF_DELETE(pElementTemp);
                GgafGarbageBox::_cnt_cleaned++;
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            break;
        } else {
            pWk = pElementTemp;
            if (pWk->_pSubFirst) {
                //子の子がまだのっている場合さらにもぐる
                pWk->clean(prm_num_cleaning);
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
            pElementTemp = pElementTemp->_pPrev;
            if (pWk->_can_live_flg == false) {
                GGAF_DELETE(pWk);
                GgafGarbageBox::_cnt_cleaned++;
                if (GgafGarbageBox::_cnt_cleaned >= prm_num_cleaning) {
                    break;
                }
            }
        }
    }
}


template<class T>
void GgafElement<T>::executeFuncLowerTree(void (*pFunc)(GgafObject*, void*, void*), void* prm1, void* prm2) {
    if (_can_live_flg && _is_active_flg) {   //TODO:activeフラグも、入れても良いかな・・・
        if (_was_initialize_flg) {
            pFunc(this, prm1, prm2);
        } else {

        }
        if (GgafNode<T>::_pSubFirst) {
            T* pElementTemp = GgafNode<T>::_pSubFirst;
            while(true) {
                pElementTemp->executeFuncLowerTree(pFunc, prm1, prm2);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventLowerTree(hashval prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        onCatchEvent(prm_no, prm_pSource);
        if (GgafNode<T>::_pSubFirst) {
            T* pElementTemp = GgafNode<T>::_pSubFirst;
            while(true) {
                pElementTemp->throwEventLowerTree(prm_no, prm_pSource);
                if (pElementTemp->_is_last_flg) {
                    break;
                } else {
                    pElementTemp = pElementTemp->_pNext;
                }
            }
        }
    }
}

template<class T>
void GgafElement<T>::throwEventUpperTree(hashval prm_no, void* prm_pSource) {
    if (_can_live_flg) {
        if (_was_initialize_flg) {
            onCatchEvent(prm_no, prm_pSource);
        }
        if (GgafNode<T>::_pParent) {
            T* pElementTemp = GgafNode<T>::_pParent;
            pElementTemp->throwEventUpperTree(prm_no, prm_pSource);
        } else {
            //てっぺん
        }
    }
}

template<class T>
bool GgafElement<T>::isDisappear() {
    if (_is_active_in_the_tree_flg == false) {
        return true;
    } else {
        return false;
    }
}

template<class T>
GgafElement<T>::~GgafElement() {
    GGAF_DELETE_NULLABLE(_pProg);
}

}
#endif /*GGAFCORE_GGAFELEMENT_H_*/
