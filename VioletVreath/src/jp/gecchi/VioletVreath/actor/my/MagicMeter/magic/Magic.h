#ifndef MAGIC_H_
#define MAGIC_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace VioletVreath {

typedef int_fast32_t magic_point;
typedef frame magic_time;
#define MAX_MAGIC_TIME MAX_FRAME

#define MAGIC_CAST_NG_INVOKING_NOW          (-5)
#define MAGIC_CAST_NG_MP_IS_SHORT           (-4)
#define MAGIC_CAST_CANCEL                   (-3)
#define MAGIC_CAST_LEVELDOWN                (-2)
#define MAGIC_CAST_CANCEL_AND_LEVELDOWN     (-1)
#define MAGIC_CAST_NOTHING                  (0)
#define MAGIC_CAST_OK_LEVELUP               (1)
#define MAGIC_CAST_OK_CANCEL_AND_LEVELUP    (3)

#define MAGIC_INVOKE_NG_INVOKING_NOW (-3)
#define MAGIC_INVOKE_NG_MP_IS_SHORT  (-2)
#define MAGIC_INVOKE_NOTHING         (0)
#define MAGIC_INVOKE_OK_LEVELUP      (1)
#define MAGIC_INVOKE_OK_LEVELDOWN    (2)

#define MAGIC_EFFECT_NG_MP_IS_SHORT (-2)
#define MAGIC_EFFECT_NOTHING        (0)
#define MAGIC_EFFECT_OK_LEVELUP     (1)
#define MAGIC_EFFECT_OK_LEVELDOWN   (2)

#define MMETER_MAX_LEVEL 10

/**
 * 抽象魔法クラス .
 * 魔法とMPについての本クラスの基本的な説明。<BR>
 * ・魔法を使用すると各魔法に設定されたMPを消費します。<BR>
 * ・魔法にはレベルという概念があり、何もない状態はレベル０です。レベル１にする場合「基本魔法コスト」が消費されます。<BR>
 * ・各レベルにコストが設定出来ます。レベルに応じて、「基本魔法コスト」に「レベル増加割合」 が乗じられた値がコストになります。<BR>
 * ・但し、飛びレベルアップ(＋２以上)の場合、MP消費を割安にする設定が可能です。<BR>
 * ・飛びレベルアップについて、たとえば「スピード」と言う魔法にレベル１～５があり、
 *   基本魔法コスト = 10, レベル増加割合 = 1.2 として、各レベルに必要なコストは 10,12,14,17,21 だったとします。<BR>
 *   「何も無し」 ＞「スピード Level1」＞「スピード Level2」 と１段階づつ２回レベルアップを行った場合、MPコストは 10+12=22 ですが、<BR>
 *   いきなり 「何も無し」 ＞「スピード Level2」とした場合、MPコストは (10+12)*0.8 = 19 というような設定が飛びレベルアップでは可能です。<BR>
 *   この 0.8 のことを「飛びレベル削減割合」と呼ぶ事とします。「飛びレベル削減割合」はレベル差に応じ個別設定できるようになっています。<BR>
 * ・レベルダウンの概念が存在します。レベルダウンはいつでも行えます。<BR>
 *   レベルダウン時に使用率に応じてMPに幾らか還元するという設定も出来ます。<BR>
 * ・魔法にはライフサイクルがあり、次のステップが存在します。各パラメータが設定可能です。<BR>
 *   a) 魔法のレベルアップ実行<BR>
 *   b) 詠唱：魔法詠唱開始→詠唱中→詠唱終了 (詠唱は途中でキャンセル可)  <BR>
 *   c) 発動：魔法発動開始→魔法中→魔法終了 (発動になるとキャンセル不可) <BR>
 *   d) 持続：魔法効果持続開始(コスト発生・効果発生) →効果持続中→果持続終了（魔法のレベルダウン）<BR>
 * ・魔法の種類には、「即効性魔法」、「効果持続性魔法」 の２種類があります。
 *   1)「即効性魔法」は 「d) 持続」のプロセスが無い魔法であり、レベルアップ・ダウンという概念が存在しません。<BR>
 *   2)「効果持続性魔法」は、「d) 持続」中、MP消費する「維持コスト有り」、MP消費しない「維持コスト無し」の２種類があります。
 *      また、予め設定された効果持続時間を超えると自動でレベルダウン(－１)します。<BR>
 *      2-a)「維持コスト有」は 「d) 持続」中にMPを消費し、もし途中でMPが0になってしまった場合、強制的にレベル0にまでレベルダウンします。<BR>
 *      2-b)「維持コスト無」は 「d) 持続」中にMPを消費しません。途中でMPが0でもレベルダウンは起こりません。（効果持続時間切れのみで起こる）<BR>
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::MainActor {
public:
    enum {
        PHASE_NOTHING     ,  //待機
        PHASE_RE_CASTING  ,  //詠唱中キャンセル再詠唱
        PHASE_CASTING     ,  //詠唱中
        PHASE_INVOKING    ,  //発動中
        PHASE_RE_EFFECT   ,  //効果持続中
        PHASE_EFFECT_START,  //効果持続開始
        PHASE_ABANDONING  ,  //破棄 （未使用）
        PHASE_BANPEI,
    };

    /**
     * 各レベルの情報 .
     */
    class LevelInfo {
    public:
        /** [r]魔法効果持続終了残り時間 */
        magic_time remained_frame_of_effecting;
        /** [r/w]魔法コスト */
        magic_point cost_;
        /** [r/w]詠唱時間 */
        magic_time casting_frames_;
        /** [r/w]発動時間 */
        magic_time invoking_frames_;
        /** [r/w]魔法効果持続時間 */
        magic_time effecting_frames_;
        /** [r/w]魔法効果持続中コスト  */
        magic_point keep_cost_;
        /** [r/w]アニメパターン番号 */
        int pno_;
        LevelInfo() : remained_frame_of_effecting(0),
                      cost_(0),
                      casting_frames_(0),
                      invoking_frames_(0),
                      effecting_frames_(0),
                      keep_cost_(0),
                      pno_(0) {
        }
    };

    /**
     * レベル差の情報 .
     */
    class LevelDiffInfo {
    public:
        /** [r]飛びレベル時の魔法コスト削減割合(0.0～1.0) */
        double r_cost_lv_diff_;
        /** [r]飛びレベル時の詠唱時間削減割合(0.0～1.0) */
        double r_casting_frames_lv_diff_;
        /** [r]飛びレベル時の発動時間削減割合(0.0～1.0) */
        double r_invoking_frames_lv_diff_;

        LevelDiffInfo() : r_cost_lv_diff_(0.0),
                          r_casting_frames_lv_diff_(0.0),
                          r_invoking_frames_lv_diff_(0.0) {
        }
    };

public:
    /** [r]マジックポイント */
    int* const pMP_;

    /** [r]現在の最高上限レベル */
    int max_level_;
    /** [r]現在のレベル(現在効果持続しているレベル、発動終了→効果持続開始のタイミングで切り替わる) */
    int level_;
    /** [r]新しいレベル(詠唱中、発動中の時、に次になろうとするレベル) */
    int new_level_;
    /** [r]前回のレベル(効果持続中の時、効果持続する前のレベル) */
    int last_level_;
    /** [r]１フレーム前のレベル */
    int prev_frame_level_;

    int level_nextframe_;
    int new_level_nextframe_;
    int last_level_nextframe_;

    /** [r]本魔法発動に必要なコストの基本単位 */
    const magic_point cost_base_;
    /** [r]本魔法詠唱開始 ～ 魔法詠唱終了の基本単位時間  */
    const magic_time casting_frames_base_;
    /** [r]本魔法発動開始 ～ 魔法発動終了の基本単位時間 */
    const magic_time invoking_frames_base_;
    /** [r]本魔法効果持続開始 ～ 魔法効果持続終了の基本単位時間  */
    const magic_time effecting_frames_base_;
    /** [r]本魔法効果持続中コストの基本単位  */
    const magic_point keep_cost_base_;

    /** [r]各レベル毎の魔法コスト増加割合(1.0～) 通常、高レベルほど魔法コストが多い */
    const double r_every_lv_cost_;
    /** [r]各レベル毎の詠唱時間増加割合(1.0～) 通常、高レベルほど詠唱時間が長い */
    const double r_every_lv_casting_frames_;
    /** [r]各レベル毎の発動時間増加割合(1.0～) 通常、高レベルほど発動時間が長い */
    const double r_every_lv_invoking_frames_;
    /** [r]各レベル毎の効果持続時間削減割合(0.0～1.0) 通常、高レベルほど効果持続時間が短い */
    const double r_every_lv_effecting_frames_;
    /** [r]各レベル毎の維持コスト増加割合 (1.0～ ) 通常、高レベルほど維持コストが多い */
    const double r_each_lv_keep_cost_;
    /** [r]各レベルの情報 配列インデックスは[レベル] */
    LevelInfo lvinfo_[MMETER_MAX_LEVEL+1];

    /** [r]飛びレベル時の魔法コスト削減割合(通常 0.0～1.0) 通常、レベル差が多いほど魔法コストが割安 */
    const double r_cost_lv_diff_base_;
    /** [r]飛びレベル時の詠唱時間削減割合(通常 0.0～1.0) 通常、レベル差が多いほど詠唱時間が短縮 */
    const double r_casting_frames_lv_diff_base_;
    /** [r]飛びレベル時の発動時間削減割合(通常 0.0～1.0) 通常、レベル差が多いほど発動時間が短縮 */
    const double r_invoking_frames_lv_diff_base_;
    /** [r]各レベル差の情報の配列、配列インデックスは[レベル差] */
    LevelDiffInfo lvdiff_[MMETER_MAX_LEVEL+1];

    /** [r]レベルアップに必要なコストの情報セット。配列インデックスは[現レベル][新しいレベル] */
    magic_point level_up_cost_[MMETER_MAX_LEVEL+1][MMETER_MAX_LEVEL+1];
    /** [r]レベルアップに詠唱時間の情報セット。配列インデックスは[現レベル][新しいレベル] */
    magic_time  level_up_casting_frames_[MMETER_MAX_LEVEL+1][MMETER_MAX_LEVEL+1];
    /** [r]レベルアップに発動時間の情報セット。配列インデックスは[現レベル][新しいレベル] */
    magic_time  level_up_invoking_frames_[MMETER_MAX_LEVEL+1][MMETER_MAX_LEVEL+1];

    /** [r]次のフェーズになる為に必要なフレーム数(を一時保持) */
    magic_time time_of_next_state_;

    int temp_hold_status_;
    int temp_hold_new_level_;

    int last_cast_;
    int last_invoke_;
    int last_effect_;

public:
    /**
     * 魔法の定義を行う .
     * 飛びレベルとはレベル差が１より大きい(レベル差２以上)を指す。
     * @param prm_name 魔法名
     * @param prm_pMP マジックポイントの数量バー
     * @param prm_max_level 本魔法の初期最高レベル 1～MMETER_MAX_LEVEL
     * @param prm_cost_base       基本魔法コスト(基本消費MP)
     * @param prm_r_every_lv_cost 各レベルのコスト増加割合。通常、1.0～ （1.0より大きいと高レベルほどコストが割高になる）<br>
     *                      (【例】1.0:レベルによる増加割合無し（＝全レベル基本魔法コスト）<br>
     *                             1.2:レベル1単体で必要なコスト ＝ 基本コスト<br>
     *                                 レベル2単体で必要なコスト ＝ 基本コスト * 1.2<br>
     *                                 レベル3単体で必要なコスト ＝ 基本コスト * 1.2 * 1.2<br>
     *                                 レベル4単体で必要なコスト ＝ 基本コスト * 1.2 * 1.2 * 1.2  コストが設定される)
     * @param prm_r_cost_lv_diff 飛びレベル時の魔法コスト削減割合 0.0～1.0 （1.0より小さいと、飛びレベル時コストが割安になる。纏めて飛ぶほどお得）<br>
     *                      (【例】1.0:いくら飛びレベルでもコスト割引無し,<br>
     *                             0.8:飛びレベル差2のとき、そのレベルアップに必要なコスト * 0.8<br>
     *                                 飛びレベル差3のとき、そのレベルアップに必要なコスト * 0.8 * 0.8<br>
     *                                 飛びレベル差4のとき、そのレベルアップに必要なコスト * 0.8 * 0.8 * 0.8
     * @param prm_casting_frames_base 基本詠唱時間
     * @param prm_r_every_lv_cost 各レベルの詠唱時間増加割合。通常、1.0～ （1.0より大きいと高レベルほど詠唱時間が長い）<br>
     *                      (【例】1.0:レベルによる詠唱時間増加割合無し（＝全レベル基本詠唱時間）<br>
     *                             1.2:レベル1単体で必要な詠唱時間 ＝ 基本詠唱時間<br>
     *                                 レベル2単体で必要な詠唱時間 ＝ 基本詠唱時間 * 1.2<br>
     *                                 レベル3単体で必要な詠唱時間 ＝ 基本詠唱時間 * 1.2 * 1.2<br>
     *                                 レベル4単体で必要な詠唱時間 ＝ 基本詠唱時間 * 1.2 * 1.2 * 1.2 時間が設定される)
     * @param prm_r_casting_frames_lv_diff_base 飛びレベル時の詠唱時間削減割合 0.0～1.0 （1.0より小さいと、飛びレベル時、詠唱時間が短縮になる。纏めて飛ぶほどお得）<br>
     *                      (【例】1.0:いくら飛びレベルでもコスト割引無し,<br>
     *                             0.8:飛びレベル差2のとき、そのレベルアップに必要な詠唱時間 * 0.8<br>
     *                                 飛びレベル差3のとき、そのレベルアップに必要な詠唱時間 * 0.8 * 0.8<br>
     *                                 飛びレベル差4のとき、そのレベルアップに必要な詠唱時間 * 0.8 * 0.8 * 0.8
     * @param prm_invoking_frames_base 基本発動時間
     * @param prm_r_every_lv_invoking_frames 各レベルの発動時間増加割合。通常、1.0～ （1.0より大きいと高レベルほど発動までが長くなる）<br>
     *                      (【例】1.0:レベルによる発動時間増加割合無し（＝全レベル基本詠唱時間）<br>
     *                             1.2:レベル1単体で必要な発動時間 ＝ 基本発動時間<br>
     *                                 レベル2単体で必要な発動時間 ＝ 基本発動時間 * 1.2<br>
     *                                 レベル3単体で必要な発動時間 ＝ 基本発動時間 * 1.2 * 1.2<br>
     *                                 レベル4単体で必要な発動時間 ＝ 基本発動時間 * 1.2 * 1.2 * 1.2 時間が設定される)
     * @param prm_r_invoking_frames_lv_diff_base 飛びレベル時の発動時間削減割合 0.0～1.0 （1.0より小さいと、飛びレベル時、発動時間が短縮になる。纏めて飛ぶほどお得）<br>
     *                      (【例】1.0:いくら飛びレベルでもコスト割引無し,<br>
     *                             0.8:飛びレベル差2のとき、そのレベルアップに必要な発動時間 * 0.8<br>
     *                                 飛びレベル差3のとき、そのレベルアップに必要な発動時間 * 0.8 * 0.8<br>
     *                                 飛びレベル差4のとき、そのレベルアップに必要な発動時間 * 0.8 * 0.8 * 0.8
     *
     * @param prm_effecting_frames_base 基本効果持続時間。<br>
     *                                0を指定すると、「即効性魔法」と解釈される。<br>
     *                                0より大きい値を設定すると、「効果持続性魔法」と解釈される。<br>
     * @param prm_r_every_lv_effecting_frames 各レベルの効果持続時間削減割合。通常 0.0～1.0 （高レベルほど持続は短い）<br>
     *                      (【例】1.0:レベルによる効果持続時削減無し,<br>
     *                             0.9:レベル1単体で得られる持続時間 ＝ 基本効果持続時間<br>
     *                                 レベル2単体で得られる持続時間 ＝ 基本効果持続時間 * 0.9<br>
     *                                 レベル3単体で得られる持続時間 ＝ 基本効果持続時間 * 0.9 * 0.9<br>
     *                                 レベル4単体で得られる持続時間 ＝ 基本効果持続時間 * 0.9 * 0.9 * 0.9  という持続時間が設定される)
     * @param prm_keep_cost_base 効果持続中の基本維持コスト。0ならば「維持コスト無し」0より大きい値を設定すると「維持コスト有」となる。
     * @param prm_r_each_lv_keep_cost レベル毎の維持コスト増加割合 通常 1.0～ (高レベルほど維持コストがかかる）<br>
     *                      (【例】1.0:レベルによる維持コスト増加無し,<br>
     *                             1.1:レベル1のときの維持コスト ＝ 基本維持コスト<br>
     *                                 レベル2のときの維持コスト ＝ 基本維持コスト * 1.1<br>
     *                                 レベル3のときの維持コスト ＝ 基本維持コスト * 1.1 * 1.1<br>
     *                                 レベル4のときの維持コスト ＝ 基本維持コスト * 1.1 * 1.1 * 1.1  という維持コストが設定される)
     * @return
     */
    Magic(const char* prm_name, int* prm_pMP,
          int prm_max_level,
          magic_point prm_cost_base            , double prm_r_every_lv_cost            , double prm_r_cost_lv_diff_base,
          magic_time  prm_casting_frames_base  , double prm_r_every_lv_casting_frames  , double prm_r_casting_frames_lv_diff_base,
          magic_time  prm_invoking_frames_base , double prm_r_every_lv_invoking_frames , double prm_r_invoking_frames_lv_diff_base,
          magic_time  prm_effecting_frames_base, double prm_r_every_lv_effecting_frames,
          magic_point prm_keep_cost_base       , double prm_r_each_lv_keep_cost);

    void init();

    virtual void initialize() override {}

    virtual void onReset() override;

    virtual void processNextFrame() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    virtual void save(std::stringstream& sts);

    virtual void loadProperties(std::stringstream& sts);

    /**
     * 詠唱開始実行 .
     * @param prm_new_level 詠唱する新しいレベル
     * @return 詠唱実行の処理状況
     * @retval  MAGIC_CAST_NG_INVOKING_NOW         効果発動中のため詠唱不可だったので、
     *                                             →何もしなかった。
     * @retval  MAGIC_CAST_NG_MP_IS_SHORT          MPが少なく詠唱不可だったので、
     *                                             →何もしなかった。
     * @retval  MAGIC_CAST_NOTHING                 現在のレベルと同じレベルを詠唱しようとしているので、
     *                                             →何もしなかった。
     * @retval  MAGIC_CAST_CANCEL                  他のレベルを詠唱中、現在の効果持続レベルと同じレベルを詠唱指定したので、
     *                                             →詠唱中止。フェーズが PHASE_NOTHING への遷移を実行した。
     * @retval  MAGIC_CAST_OK_LEVELUP              現在の効果持続レベルより高いレベルを詠唱を指定ので、
     *                                             →詠唱シークエンス開始、フェーズを PHASE_CASTING への遷移を実行した。
     * @retval  MAGIC_CAST_LEVELDOWN               現在の効果持続レベルより低いレベルを詠唱を指定ので、
     *                                             →魔法効果開始 effect(prm_new_level) を実行した。
     * @retval  MAGIC_CAST_OK_CANCEL_AND_LEVELUP   他のレベルを詠唱中に再詠唱を行おうとしていて、再詠唱のレベルが、現在の効果持続レベルより高ので、
     *                                             →再詠唱シークエンス開始、フェーズが PHASE_RE_CASTING への遷移を実行した。
     * @retval  MAGIC_CAST_CANCEL_AND_LEVELDOWN    他のレベルを詠唱中に再詠唱を行おうとしていて、再詠唱のレベルが、現在の効果持続レベルより低いので、
     *                                             →魔法効果開始 effect(prm_new_level) を実行した。
     */
    virtual int cast(int prm_new_level);

    /**
     * 魔法詠唱開始コールバック(１回だけコールバック) .
     * 次のタイミングで呼び出される。<BR>
     * ・詠唱中ではない状態→効果中レベル以外のレベルの魔法の詠唱実行時<BR>
     * ・現在詠唱中→効果中レベル以外のレベルの魔法の詠唱実行時<BR>
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 詠唱する新しいレベル(1～ )
     */
    virtual void processCastBegin(int prm_now_level, int prm_new_level) = 0;

    /**
     * 魔法詠唱中コールバック(毎フレームコールバック) .
     * 【注意】レベルダウン時は１回だけコールされ processCastFinish() が実行されます。
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 詠唱中の新しいレベル(1～ )
     */
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) = 0;

    /**
     * 魔法詠唱中、詠唱キャンセル時のコールバック .
     * @param prm_now_level 現在のレベル(0～ )
     */
    virtual void processCastingCancel(int prm_now_level) = 0;

    /**
     * 魔法詠唱終了コールバック(１回だけコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 詠唱中完了し発動予定の新しいレベル(1～ )
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) = 0;

    /**
     * 発動開始実行(１回だけコールバック) .
     * @param prm_new_level 発動する新しいレベル
     * @return 発動実行の処理状況
     */
    virtual int invoke(int prm_new_level);

    /**
     * 魔法発動開始コールバック .
     * ここまでくると詠唱キャンセルは不可とする。(１回だけコールバック)
     * レベルダウン時も呼び出されます。
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 発動させようとしている新しいレベル(1～ )
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) = 0;

    /**
     * 魔法発動中コールバック(毎フレームコールバック) .
     * 【注意】レベルダウン時は１回だけコールされ processInvokeFinish() が実行されます。
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 現在発動中の新しいレベル(1～ )
     */
    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) = 0;

    /**
     * 魔法発動中、発動キャンセル時のコールバック .
     * 通常は魔法発動時にキャンセルはできないが、やむを得ないに事情により強制キャンセルされる場合に
     * 呼び出される。
     * 例えば、発動中にMPが枯渇してしまったとか、死んだとか。
     * @param prm_now_level 現在のレベル(0～ )
     */
    virtual void processInvokingCancel(int prm_now_level) = 0;

    /**
     * 魔法発動終了コールバック(１回だけコールバック) .
     * レベルダウン時も呼び出されます。
     * @param prm_now_level 魔法発動終了直前の、現在のレベル。(0～ )
     * @param prm_new_level 魔法発動終了直後の、昇格すべき新しいレベル。(1～ )
     * @param prm_result_effect invoke()の結果
     */
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) = 0;

    /**
     * 効果発揮実行 .
     * @param prm_level 効果発揮時レベル
     */
    virtual int effect(int prm_level);

    /**
     * 魔法効果持続開始コールバック(１回だけコールバック) .
     * 次のタイミングで呼び出される
     * ・魔法発動終了 → 魔法効果持続開始時（prm_last_level < prm_now_level）<BR>
     * ・レベルダウン実行時 （手動 or 効果時間満期 or コストあり魔法のMP枯渇）<BR>
     * @param prm_last_level 効果持続が開始される前のレベル。(レベルアップ時：0～ ／レベルダウン時：1～)
     * @param prm_now_level 効果持続が開始されたレベル。(レベルアップ時：1～ ／レベルダウン時：0～)
     */
    virtual void processEffectBegin(int prm_last_level, int prm_now_level) = 0;

    /**
     * 魔法効果持続中コールバック(毎フレームコールバック) .
     * 即効性魔法(effecting_frames_base_==0)の魔法は１回だけコールバックされることになります。
     * 【注意】レベル0でも、内部的にはレベル0の魔法が効果持続中と考えられ本メソッドは呼び出され続けます。
     * @param prm_last_level  以前のレベル。
     * @param prm_now_level 現在(持続中)のレベル。
     */
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) = 0;

    /**
     * そのレベルの魔法が詠唱実行できるか調べる
     * @param prm_new_level 詠唱するレベル
     * @retval MAGIC_CAST_NG_INVOKING_NOW       (-3)  現在発動中のた為、不可
     * @retval MAGIC_CAST_NG_MP_IS_SHORT        (-2)  レベルアップ詠唱となるが、MPが足りないた為、不可
     * @retval MAGIC_CAST_CANCEL                (-1)  現在詠唱中で、引数のレベルは、現在のレベルと一致。つまり詠唱キャンセル指示になる。（可能・不可能で言えば可能）
     * @retval MAGIC_CAST_NOTHING               (0)   引数のレベルは、現在のレベルと一致。なにも指示してないことになる。（可能・不可能で言えば可能）
     * @retval MAGIC_CAST_OK_LEVELUP            (1)   レベルアップ詠唱となる。MPが足りる為可能
     * @retval MAGIC_CAST_LEVELDOWN             (2)   レベルダウン詠唱となる。もちろん可能
     * @retval MAGIC_CAST_OK_CANCEL_AND_LEVELUP (3)   現在の詠唱をキャンセルしてのレベルアップ詠唱となる。MPが足りる為可能
     * @retval MAGIC_CAST_CANCEL_AND_LEVELDOWN  (4)   現在の詠唱をキャンセルしてのレベルダウン詠唱となる。もちろん可能
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
     * ダウンレベル実行時の還元MPを計算して返す .
     * 残効果持続の割合を乗ずる。
     * 早くレベルダウンしたほうがお得にするため。
     * @param prm_now_level 現在のレベル
     * @param prm_target_down_level ダウンレベル
     * @return
     */
    magic_point calcReduceMp(int prm_now_level, int prm_target_down_level);

    virtual ~Magic();
};

}

#endif /*MAGIC_H_*/
