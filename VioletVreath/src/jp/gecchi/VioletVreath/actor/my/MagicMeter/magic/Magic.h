#ifndef MAGIC_H_
#define MAGIC_H_
#include "jp/ggaf/core/actor/GgafMainActor.h"

namespace VioletVreath {

typedef int magic_point;
typedef frame magic_time;

#define MAGIC_CAST_NG_INVOKING_NOW          (-3)
#define MAGIC_CAST_NG_MP_IS_SHORT           (-2)
#define MAGIC_CAST_CANCEL                   (-1)
#define MAGIC_CAST_NOTHING                  (0)
#define MAGIC_CAST_OK_LEVELUP               (1)
#define MAGIC_CAST_OK_LEVELDOWN             (2)
#define MAGIC_CAST_OK_CANCEL_AND_LEVELUP    (3)
#define MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN  (4)

#define MAGIC_INVOKE_NG_INVOKING_NOW (-3)
#define MAGIC_INVOKE_NG_MP_IS_SHORT (-2)
#define MAGIC_INVOKE_NOTHING        (0)
#define MAGIC_INVOKE_OK_LEVELUP     (1)
#define MAGIC_INVOKE_OK_LEVELDOWN   (2)

#define MAGIC_EFFECT_NG_MP_IS_SHORT (-2)
#define MAGIC_EFFECT_NOTHING        (0)
#define MAGIC_EFFECT_OK_LEVELUP     (1)
#define MAGIC_EFFECT_OK_LEVELDOWN   (2)

#define MMETER_MAX_LEVEL 9

/**
 * 抽象魔法クラス .
 * 魔法とMPについての本クラスの基本的な説明。<BR>
 * ・魔法を使用すると各魔法に設定されたMPを消費します。これを「基本魔法コスト」呼びます。<BR>
 * ・魔法にはレベルという概念があり、何もない状態はレベル０です。レベルを＋１する場合「基本魔法コスト」が消費されます。<BR>
 *   但し、飛びレベル(＋２以上)の場合、MP消費を割安にする設定が可能です。<BR>
 * ・飛びレベルアップについて、たとえば「スピード」と言う魔法にレベル１～５があり、基本魔法コストは 10 だったとします。<BR>
 *   「スピード Level1」＞「スピード Level2」 と２回レベルアップを行った場合、MPコストは 10+10=20 ですが、<BR>
 *   いきなり「スピード Level2」とした場合、MPコストは (10+10)*0.8 = 16 というような設定が飛びレベルアップでは可能です。<BR>
 *   この 0.8 のことを「削減割合」と呼ぶ事とします。<BR>
 * ・レベルダウンの概念が存在します。レベルダウンはいつでも行えます。<BR>
 *   レベルダウン時にその分をMPに幾らか還元するという設定も出来ます。<BR>
 * ・魔法にはライフサイクルがあり、次のステップが存在します。各パラメータが設定可能です。<BR>
 *   a) 魔法のレベルアップ実行<BR>
 *   b) 詠唱：魔法詠唱開始→詠唱中→詠唱終了 (詠唱は途中でキャンセル可)  <BR>
 *   c) 発動：魔法発動開始→魔法中→魔法終了 (発動になるとキャンセル不可) <BR>
 *   d) 持続：魔法効果持続開始(コスト発生・効果発生) →効果持続中→果持続終了（魔法のレベルダウン）<BR>
 * ・魔法の種類には、即効性魔法、効果持続魔法 の２種類があります。
 *   さらに効果持続性魔法には、効果持続時間に維持コスト有り、維持コスト無しの２種類があります。<BR>
 *   1)「即効性魔法」は 「d) 持続」のプロセスが無い魔法であり、レベルアップ・ダウンという概念が存在しません。<BR>
 *   2)「効果持続性魔法」は「d) 持続」中に設定された効果持続時間を超えると自動でレベルダウン(－１)します。<BR>
 *      2-a)「維持コスト有」は さらに「d) 持続」中にMPを消費します。もし、途中でMPが0になってしまった場合、
 *           強制的にレベル０にレベルダウンします。<BR>
 *      2-b)「維持コスト無」は 「d) 持続」中にMPを消費しません。途中でMPが0でもレベルダウンは起こりません。
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::GgafMainActor {
public:
    enum {
        STATE_NOTHING = 1,
        STATE_CAST_BEGIN,
        STATE_CASTING    ,
        STATE_INVOKE_BEGIN,
        STATE_INVOKING   ,
        STATE_EFFECT_BEGIN  ,
        STATE_EFFECTING  ,
        STATE_ABANDONING ,
    };

    /**
     * 各レベルの情報 .
     */
    class LevelInfo {
    public:
        /** [r]魔法効果持続終了残り時間 */
        magic_time remainingtime_of_effect_;
        /** [r/w]魔法効果持続時間 */
        magic_time time_of_effect_;
        /** [r/w]魔法効果持続中コスト  */
        magic_point keep_cost_;
        /** [r/w]アニメパターン番号 */
        int pno_;

        LevelInfo() : remainingtime_of_effect_(0),
                      time_of_effect_(0),
                      keep_cost_(0),
                      pno_(0) {
        }
    };

public:
    /** [r]最高上限レベル */
    int max_level_;
    /** [r]現在のレベル */
    int level_;
    /** [r]新しいレベル */
    int new_level_;
    /** [r]前回のレベル */
    int last_level_;
    /** [r]１フレーム前のレベル */
    int prev_frame_level_;

    /** [r]マジックポイント数量バー */
    GgafLib::AmountGraph* pMP_;
    /** [r]各レベルの情報 0～MMETER_MAX_LEVEL */
    LevelInfo lvinfo_[MMETER_MAX_LEVEL+1];

    /** [r]本魔法発動に必要なコストの基本単位 */
    magic_point cost_base_;
    /** [r]本魔法詠唱開始 ～ 魔法詠唱終了の基本単位時間  */
    magic_time time_of_casting_base_;
    /** [r]本魔法発動開始 ～ 魔法発動終了の基本単位時間 */
    magic_time time_of_invoking_base_;
    /** [r]本魔法効果持続開始 ～ 魔法効果持続終了の基本単位時間  */
    magic_time time_of_effect_base_;
    /** [r]本魔法効果持続中コストの基本単位  */
    magic_point keep_cost_base_;

    /** [r]飛びレベル時の魔法コスト削減割合(0.0～1.0) */
    double r_cost_;
    /** [r]飛びレベル時の詠唱時間削減割合(0.0～1.0) */
    double r_time_of_casting_;
    /** [r]飛びレベル時の発動時間削減割合(0.0～1.0) */
    double r_time_of_invoking_;
    /** [r]各レベル毎の効果持続時間削減割合(0.0～1.0) */
    double r_each_lv_time_of_effecting_;
    /** [r]各レベル毎の維持コスト増加割合 (1.0～ )*/
    double r_keep_cost_;

    /** [r]次の進捗状態になる為に必要なフレーム数(を一時保持) */
    magic_time time_of_next_state_;
    /** [r]レベルアップ中かどうか */
    bool is_working_;


    /** [r]飛びレベル差別魔法コスト情報 0差～MMETER_MAX_LEVEL差 */
    magic_point interest_cost_[MMETER_MAX_LEVEL+1];
    /** [r]飛びレベル差別詠唱時間情報 0差～MMETER_MAX_LEVEL差 */
    magic_time  interest_time_of_casting_[MMETER_MAX_LEVEL+1];
    /** [r]飛びレベル差別発動時間情報 0差～MMETER_MAX_LEVEL差 */
    magic_time  interest_time_of_invoking_[MMETER_MAX_LEVEL+1];


    progress temp_hold_status_;
    int temp_hold_new_level_;
public:

    /**
     * 魔法の定義を行う .
     * 飛びレベルとはレベル差が１より大きい(レベル差２以上)を指す。
     * @param prm_name 魔法名
     * @param prm_pMP マジックポイントの数量バー
     * @param prm_max_level 本魔法の最高レベル 1～MMETER_MAX_LEVEL
     * @param prm_cost_base              基本魔法コスト
     * @param prm_r_cost                 飛びレベル時の魔法コスト削減割合 0.0～1.0
     *                                   (【例】1.0:飛びレベルでも割引無し、
     *                                          0.8:レベル差２以上時、コスト=prm_cost_base*レベル差*0.8)
     * @param prm_time_of_casting_base   基本魔法詠唱時間
     * @param prm_r_time_of_casting      飛びレベル時の詠唱時間削減割合0.0～1.0
     *                                   (【例】1.0:飛びレベルでも割引無し,
     *                                          0.8:レベル差２以上時、詠唱時間=prm_time_of_casting_base*レベル差*0.8)
     * @param prm_time_of_invoking_base  基本魔法発動時間
     * @param prm_r_time_of_invoking     飛びレベル時の発動時間削減割合0.0～1.0
     *                                   (【例】1.0:飛びレベルでも割引無し,
     *                                          0.8:レベル差２以上時、発動時間=prm_time_of_invoking_base*レベル差*0.8)
     * @param prm_time_of_effect_base 基本魔法効果持続時間。
     *                                0を指定すると、「即効性魔法」と解釈される。
     *                                0より大きい値を設定すると、「効果持続性魔法」と解釈される。
     * @param prm_r_each_lv_time_of_effecting 各レベル毎の効果持続時間削減割合  0.0～1.0
     *                      (【例】1.0:レベルによる効果持続時削減無し,
     *                             0.8:レベル1のとき prm_time_of_effect
     *                                 レベル2のとき prm_time_of_effect * 0.8
     *                                 レベル3のとき prm_time_of_effect * 0.8 * 0.8
     *                                 レベル4のとき prm_time_of_effect * 0.8 * 0.8 * 0.8  という持続時間が設定される)
     * @param prm_keep_cost_base 基本魔法効果持続中維持コスト。0ならば「維持コスト無し」0より大きい値を設定すると「維持コスト有」となる。
     * @param prm_r_each_lv_keep_cost 各レベル毎の維持コスト増加割合 1.0～
     *                      (【例】1.0:レベルによる維持コスト増加無し,
     *                             1.2:レベル1のとき prm_keep_cost_base
     *                                 レベル2のとき prm_keep_cost_base * 1.2
     *                                 レベル3のとき prm_keep_cost_base * 1.2 * 1.2
     *                                 レベル4のとき prm_keep_cost_base * 1.2 * 1.2 * 1.2  という維持コストが設定される)
     * @return
     */
    Magic(const char* prm_name, GgafLib::AmountGraph* prm_pMP,
          int prm_max_level,
          magic_point prm_cost_base            , double prm_r_cost,
          magic_time  prm_time_of_casting_base , double prm_r_time_of_casting,
          magic_time  prm_time_of_invoking_base, double prm_r_time_of_invoking,
          magic_time  prm_time_of_effect_base  , double prm_r_each_lv_time_of_effecting,
          magic_point prm_keep_cost_base       , double prm_r_each_lv_keep_cost);

    void init();

    void initialize() override {}

    void onReset() override;

    void processBehavior() override;

    void processJudgement() override {}

    void processDraw() override {}

    void processFinal() override {}

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    void save(std::stringstream& sts);

    void load(std::stringstream& sts);

    /**
     * 詠唱開始実行 .
     * @param prm_new_level
     */
    virtual int cast(int prm_new_level);

    /**
     * 魔法詠唱開始コールバック(１回だけコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 詠唱する新しいレベル(1～ )
     */
    virtual void processCastBegin(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法詠唱中コールバック(毎フレームコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 詠唱中の新しいレベル(1～ )
     */
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法詠唱終了コールバック(１回だけコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 詠唱中完了し発動予定の新しいレベル(1～ )
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {};


    /**
     * 発動開始実行 .
     * @param prm_new_level
     */
    virtual int invoke(int prm_new_level);

    /**
     * 魔法発動開始コールバック。ここまでくると詠唱キャンセルは不可とする。(１回だけコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 発動させようとしている新しいレベル(1～ )
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法発動中コールバック(毎フレームコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 現在発動中の新しいレベル(1～ )
     */
    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法発動終了コールバック(１回だけコールバック) .
     * @param prm_now_level 魔法発動終了直前の、現在のレベル。(0～ )
     * @param prm_new_level 魔法発動終了直後の、昇格すべき新しいレベル。(1～ )
     */
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {};

    /**
     * 効果発揮実行 .
     * @param prm_level 効果発揮時レベル
     */
    virtual int effect(int prm_level);

    /**
     * 魔法効果持続開始コールバック(１回だけコールバック) .
     * 魔法発動終了 → 魔法効果持続開始、のタイミングで呼び出される。さらに、<BR>
     * 魔法効果持続中 → レベルアップ or レベルダウン、のタイミングでも呼び出される。<BR>
     * prm_last_level < prm_now_level の場合レベルアップ .
     * prm_last_level > prm_now_level の場合レベルダウン .
     * @param prm_last_level 効果持続が開始される前のレベル。(レベルアップ時：0～ ／レベルダウン時：1～)
     * @param prm_now_level 効果持続が開始されたレベル。(レベルアップ時：1～ ／レベルダウン時：1～)
     */
    virtual void processEffectBegin(int prm_last_level, int prm_now_level) {};

    /**
     * 魔法効果持続中コールバック(毎フレームコールバック) .
     * 【注意】即効性魔法(time_of_effect_base_==0)の魔法は、本コールバックは行われません。
     * @param prm_last_level  以前のレベル。
     * @param prm_now_level 現在(持続中)のレベル。
     */
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) {};

    /**
     * 魔法持続全終了コールバック(１回だけコールバック) .
     * レベル0になるレベルダウンが行われた直前に呼び出されます。<BR>
     * 捕捉：レベル0にならないレベルダウン processEffectBegin() が呼び出されます。<BR>
     * @param prm_justbefore_level 効果持続が終了する直前のレベル(ちなみに現在レベルは必ず0)。
     */
    virtual void processEffectFinish(int prm_justbefore_level) {};


    /**
     * そのレベルの魔法が詠唱実行できるか調べる
     * @param prm_new_level 詠唱するレベル
     * @return MAGIC_CAST_NG_INVOKING_NOW          (-3)  現在発動中のた為、不可
     *         MAGIC_CAST_NG_MP_IS_SHORT           (-2)  レベルアップ詠唱となるが、MPが足りないた為、不可
     *         MAGIC_CAST_CANCEL                   (-1)  現在詠唱中で、引数のレベルは、現在のレベルと一致。つまり詠唱キャンセル指示になる。（可能・不可能で言えば可能）
     *         MAGIC_CAST_NOTHING                  (0)   引数のレベルは、現在のレベルと一致。なにも指示してないことになる。（可能・不可能で言えば可能）
     *         MAGIC_CAST_OK_LEVELUP               (1)   レベルアップ詠唱となる。MPが足りる為可能
     *         MAGIC_CAST_OK_LEVELDOWN             (2)   レベルダウン詠唱となる。もちろん可能
     *         MAGIC_CAST_OK_CANCEL_AND_LEVELUP    (3)   現在の詠唱をキャンセルしてのレベルアップ詠唱となる。MPが足りる為可能
     *         MAGIC_CAST_OK_CANCEL_AND_LEVELDOWN  (4)   現在の詠唱をキャンセルしてのレベルダウン詠唱となる。もちろん可能
     */
    int chkCastAble(int prm_new_level);

    /**
     * そのレベルの魔法が発動実行ができるか調べる
     * @param prm_new_level 発動するレベル
     * @return
     */
    int chkInvokeAble(int prm_new_level);

    /**
     * そのレベルの魔法が効果が実行ができるか調べる
     * @param prm_level
     * @return
     */
    int chkEffectAble(int prm_level);

    /**
     * 魔法をキャンセルする .
     */
    virtual void cancel();

    /**
     * ダウンレベル実行時の還元MPを計算して返す .
     * 残効果持続の割合を乗ずる。
     * 早くレベルダウンしたほうがお得にするため。
     * @param prm_now_level 現在のレベル
     * @param prm_target_down_level ダウンレベル
     * @return
     */
    magic_point calcReduceMp(int prm_now_level, int prm_target_down_level);

    /**
     * 効果持続時間合計の試算 .
     * @param prm_now_level 現在のレベル
     * @param prm_target_up_level レベルアップのレベル
     * @return 試算された効果持続時間合計
     */
    magic_time calcTotalEffecTime(int prm_now_level, int prm_target_up_level);


    virtual ~Magic();
};

}


#endif /*MAGIC_H_*/
