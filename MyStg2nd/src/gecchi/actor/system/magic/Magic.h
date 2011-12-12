#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

typedef int magic_point;
typedef frame magic_time;

#define MAGIC_EXECUTE_NG_INVOKING    (-2)
#define MAGIC_EXECUTE_NG_MP_IS_SHORT (-1)
#define MAGIC_EXECUTE_NG             (-1)
#define MAGIC_EXECUTE_THE_SAME_LEVEL (0)
#define MAGIC_EXECUTE_OK             (1)
#define MAGIC_EXECUTE_OK_LEVELUP     (1)
#define MAGIC_EXECUTE_OK_LEVELDOWN   (2)

/**
 * 抽象魔法クラス .
 * 魔法とMPについての本クラスの基本的な約束事。
 * ・魔法を使用すると各く魔法に設定されたMPを消費します。これを「基本魔法コスト」呼びます。<BR>
 * ・魔法にはレベルという概念があり、基本的にレベルを＋１するのに「基本魔法コスト」が消費されます。<BR>
 *   但し、飛びレベル(＋２以上)の場合、MP消費を割安にする設定が出来ます。<BR>
 *   たとえば「スピード」と言う魔法にレベル１～５があり、基本魔法コストは 10 だったとします。<BR>
 *   「スピード Level1」＞「スピード Level2」 とした場合、MPコストは 10+10=20 ですが、<BR>
 *   いきなり「スピード Level2」とした場合、MPコストは (10+10)*0.8 = 16 という設定が可能です。<BR>
 *   この 0.8 のことを「削減割合」と呼ぶ事とします。
 * ・レベルダウンの概念が存在します。レベルダウンはいつでも行えます。<BR>
 *   レベルダウン時にその分をMPに幾らか戻すという設定も出来ます。<BR>
 * ・魔法にはライフサイクルがあり、次のステップが存在します。各パラメータが設定可能です。<BR>
 *   a) 魔法のレベルアップ実行<BR>
 *   b) 詠唱：魔法詠唱開始・詠唱中・詠唱終了<BR>
 *   c) 発動：魔法発動開始(コスト発生) ・魔法中・魔法終了<BR>
 *   d) 持続：魔法効果持続開始(効果発生) ・効果持続中・果持続終了<BR>
 *   e) 魔法のレベルダウン<BR>
 * ・「b) 詠唱」までならば破棄（停止）が可能です。<BR>
 *   「c) 発動」までステップが進むと、MPが消費され途中破棄は不可能になります。<BR>
 *   「d) 持続」になるまで、レベルアップ、レベルダウンの操作は出来ないこととします。<BR>
 * ・魔法には、維持コスト無し、維持コスト有り の２種類があります。<BR>
 *   維持コスト無しは、「d) 持続」中にMPを消費しません。<BR>
 *   維持コスト有りは、「d) 持続」中にMPを消費します。<BR>
 *   維持コスト無しは、MPが枯渇してもレベルダウンしません。<BR>
 *   維持コスト有りは、MPが枯渇した場合自動でレベルダウンします。<BR>
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::GgafMainActor {


public:
    /**
     * 各レベルの情報 .
     */
    class LevelInfo {
    public:
        /** 該当レベルで魔法が適用中であるかどうか(発動開始～効果終了までtrue) */
        bool _is_working;
        /** 魔法効果持続終了残り時間 */
        magic_time _remaining_time_of_effect;
        /** 魔法効果持続時間 */
        magic_time _time_of_effect;
        /** 魔法効果持続中コスト  */
        magic_point _keep_cost;
        /** アニメパターン番号 */
        int _pno;
        LevelInfo() : _is_working(false),
                      _remaining_time_of_effect(0),
                      _keep_cost(0),
                      _pno(0) {
        }
    };
//    GgafDxCore::GgafDxGeometricActor* _pCaster;
//    GgafDxCore::GgafDxGeometricActor* _pReceiver;

    char* _name;
    /** 最高レベル */
    int _max_level;
    /** 現在のレベル */
    int _level;


    /** 新しいレベル */
    int _new_level;
    /** 前回のレベル */
    int _last_level;


    /** マジックポイント数量バー */
    GgafLib::AmountGraph* _pMP;
    /** メーターへのポインタ */
    MagicMeter* _pMagicMeter;

    /** 各レベルの情報 0～MMETER_MAX_LEVEL */
    LevelInfo _lvinfo[MMETER_MAX_LEVEL+1];
    /** 飛びレベル差別魔法コスト情報 0差～MMETER_MAX_LEVEL差 */
    magic_point _interest_cost[MMETER_MAX_LEVEL+1];
    /** 飛びレベル差別詠唱時間情報 0差～MMETER_MAX_LEVEL差 */
    magic_time  _interest_time_of_casting[MMETER_MAX_LEVEL+1];
    /** 飛びレベル差別発動時間情報 0差～MMETER_MAX_LEVEL差 */
    magic_time  _interest_time_of_invoking[MMETER_MAX_LEVEL+1];

    /** 本魔法発動に必要なコストの基本単位 */
    magic_point _cost_base;
    /** 本魔法詠唱開始 ～ 魔法詠唱終了の基本単位時間  */
    magic_time _time_of_casting_base;
    /** 本魔法発動開始 ～ 魔法発動終了の基本単位時間 */
    magic_time _time_of_invoking_base;
    /** 本魔法効果持続開始 ～ 魔法効果持続終了の基本単位時間  */
    magic_time _time_of_effect_base;
    /** 本魔法効果持続中コストの基本単位  */
    magic_point _keep_cost_base;

    /** 飛びレベル時の魔法コスト削減割合(0.0～1.0) */
    float _fRate_cost;
    /** 飛びレベル時の詠唱時間削減割合(0.0～1.0) */
    float _fRate_time_of_casting;
    /** 飛びレベル時の発動時間削減割合(0.0～1.0) */
    float _fRate_time_of_invoking;
    /** 各レベル毎の効果持続時間削減割合(0.0～1.0) */
    float _fRate_time_of_effecting;
    /** 各レベル毎の維持コスト増加割合 (1.0～ )*/
    float _fRate_keep_cost;

    magic_time _time_of_next_state;

//    /** 状態 */
//    int _state;
    /** レベルアップ中かどうか */
    bool _is_working;

    float _discount_rate;

    float _rr;
    float _velo_rr;

public:
    /**
     * 魔法の定義を行う .
     * 飛びレベルとはレベル差が１より大きい(レベル差２以上)を指す。
     * @param prm_name 魔法名
     * @param prm_max_level 本魔法の最高レベル 1～MMETER_MAX_LEVEL
     * @param prm_cost_base 基本魔法コスト
     * @param prm_fRate_cost 飛びレベル時の魔法コスト削減割合 0.0～1.0 (1.0:飛びレベルでも割引無し、0.8:レベル差２以上時、魔法コスト２割引)
     * @param prm_time_of_casting_base 基本魔法詠唱時間
     * @param prm_fRate_time_of_casting 飛びレベル時の詠唱時間削減割合0.0～1.0 (1.0:飛びレベルでも割引無し, 0.8:レベル差２以上時、詠唱時間２割引)
     * @param prm_time_of_invoking_base 基本魔法発動時間
     * @param prm_fRate_time_of_invoking 飛びレベル時の発動時間削減割合0.0～1.0 (1.0:飛びレベルでも割引無し, 0.8:レベル差２以上時、発動時間２割引)
     * @param prm_time_of_effect 基本魔法効果持続時間
     * @param prm_fRate_time_of_effecting 各レベル毎の効果持続時間削減割合  0.0～1.0
     *                            (1.0:レベルによる効果持続時削減無し,
     *                            (0.8:レベル1のとき prm_time_of_effect
     *                                 レベル2のとき prm_time_of_effect * 0.8
     *                                 レベル3のとき prm_time_of_effect * 0.8 * 0.8
     *                                 レベル4のとき prm_time_of_effect * 0.8 * 0.8 * 0.8  という持続時間が設定される)
     * @param prm_keep_cost_base 基本魔法効果持続中維持コスト
     * @param prm_fRate_keep_cost_base 各レベル毎の維持コスト増加割合 1.0～
     *                            (1.0:レベルによる維持コスト増加無し,
     *                            (1.2:レベル1のとき prm_keep_cost_base
     *                                 レベル2のとき prm_keep_cost_base * 1.2
     *                                 レベル3のとき prm_keep_cost_base * 1.2 * 1.2
     *                                 レベル4のとき prm_keep_cost_base * 1.2 * 1.2 * 1.2  という維持コストが設定される)
     * @return
     */
    Magic(const char* prm_name, GgafLib::AmountGraph* prm_pMP,
          int   prm_max_level,
          magic_point prm_cost_base, float prm_fRate_cost,
          magic_time  prm_time_of_casting_base , float prm_fRate_time_of_casting,
          magic_time  prm_time_of_invoking_base, float prm_fRate_time_of_invoking,
          magic_time  prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
          magic_point prm_keep_cost_base       , float prm_fRate_keep_cost_base);


//          GgafDxCore::GgafDxGeometricActor* prm_pCaster,
//          GgafDxCore::GgafDxGeometricActor* prm_pReceiver);
    void initialize() override {
    }

    void onReset() override {
    }

    void processBehavior() override;

    void processJudgement() override {
    }
    void processDraw() override {
    }
    void processFinal()  override {
    }
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }


    void rollOpen();
    void rollClose();

    /**
     * そのレベルの魔法が実行できるか調べる
     * @param prm_new_level
     * @return
     */
    int chkExecuteAble(int prm_new_level);

    /**
     * 詠唱開始実行 .
     * @param prm_new_level
     */
    virtual void cast(int prm_new_level);

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
     * @param prm_new_level 詠唱中完了した新しいレベル(1～ )
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level) {};

    /**
     * 発動開始実行 .
     * @param prm_new_level
     */
    virtual void invoke(int prm_new_level);

    /**
     * 魔法発動開始コールバック。ここまでくると詠唱キャンセルは不可とする。(１回だけコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 発動させようとしている新しいレベル(1～ )
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法発動中コールバック(毎フレームコールバック) .
     * @param prm_now_level 現在のレベル(0～ )
     * @param prm_new_level 発動させようとしている新しいレベル(1～ )
     */
    virtual void processInvokeingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法発動終了コールバック(１回だけコールバック) .
     * @param prm_last_level 発動中だった頃の、現在のレベル。(0～ )
     * @param prm_now_level 発動により、これから昇格する新しいレベル。(1～ )
     */
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level) {};

    /**
     * 効果発揮実行 .
     * @param prm_new_level
     */
    virtual void effect(int prm_level);

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

//    /**
//     * 魔法破棄コールバック .
//     * @param prm_last_high_level 降格前の現在のレベル
//     * @param prm_new_low_level 新しく変わる降格レベル
//     */
//    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) {};
//
//
//    /**
//     * 魔法破棄コールバック .
//     * @param prm_last_high_level 降格前の現在のレベル
//     * @param prm_new_low_level 新しく変わる降格レベル
//     */
//    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) {};


    /**
     * 魔法を完了する .
     */
//    virtual void commit();
    /**
     * 魔法をキャンセルする .
     */
    virtual void cancel();

    virtual ~Magic();
};

}
#endif /*MAGIC_H_*/
