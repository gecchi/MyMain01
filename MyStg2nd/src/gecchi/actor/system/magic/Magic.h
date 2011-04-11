#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

#define MAGIC_NOTHING 0
#define MAGIC_STAND_BY 1
#define MAGIC_CASTING 2
#define MAGIC_INVOKING 3
#define MAGIC_EFFECTING 4
#define MAGIC_ABANDONING 9

#define MAGIC_EXECUTE_NG_INVOKING    (-2)
#define MAGIC_EXECUTE_NG_MP_IS_SHORT (-1)
#define MAGIC_EXECUTE_NG             (-1)
#define MAGIC_EXECUTE_THE_SAME_LEVEL 0
#define MAGIC_EXECUTE_OK             1
#define MAGIC_EXECUTE_OK_LEVELUP     1
#define MAGIC_EXECUTE_OK_LEVELDOWN   2

typedef int magic_point;
typedef frame magic_time;
/**
 * 抽象魔法クラス .
 * 魔法についての本クラスの基本的な約束事。
 * ①次のステップがあります。
 * a) 詠唱：魔法詠唱開始 ～ 魔法詠唱終了
 * b) 発動：魔法発動開始・魔法コスト発生 ～ 魔法発動終了
 * c) 持続：魔法効果持続開始 ～ 魔法効果持続終了
 * ②レベルの概念があります。
 * レベルによって、a)b)c) の "～"の時間、及び魔法コストを個別で保持できます。
 * ②機能
 * ・a) 詠唱ならば魔法破棄（停止）が可能
 * ・詠唱は基本詠唱時間を設定し、詠唱速度割合が調整可能
 * ・魔法コストは基本魔法コストを設定し、コスト割合が調整可能
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::GgafMainActor {
    /** 新しいレベル */
    int _new_level;
    /** 前回のレベル */
    int _last_level;


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
    GgafDx9Core::GgafDx9GeometricActor* _pCaster;
    GgafDx9Core::GgafDx9GeometricActor* _pReceiver;

    char* _name;
    /** 現在のレベル */
    int _level;
    /** 最高レベル */
    int _max_level;
    /** マジックポイント数量バー */
    GgafDx9LibStg::AmountGraph* _pMP;
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

    float _fRate_cost;
    float _fRate_time_of_casting;
    float _fRate_time_of_invoking;
    float _fRate_time_of_effecting;
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
     *
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
     * @param prm_fRate_keep_cost 各レベル毎の効果持続時間減割合  0.0～1.0
     *                            (1.0:レベルによる効果持続時削減無し,
     *                            (0.8:レベル1のとき prm_time_of_effect
     *                                 レベル2のとき prm_time_of_effect * 0.8
     *                                 レベル3のとき prm_time_of_effect * 0.8 * 0.8
     *                                 レベル4のとき prm_time_of_effect * 0.8 * 0.8 * 0.8  という持続時間が設定される)
     * @param prm_keep_cost_base 基本魔法効果持続中維持コスト
     * @param prm_fRate_keep_cost 各レベル毎の維持コスト増加割合  1.0～
     *                            (1.0:レベルによる維持コスト増加無し,
     *                            (1.2:レベル1のとき prm_keep_cost_base
     *                                 レベル2のとき prm_keep_cost_base * 1.2
     *                                 レベル3のとき prm_keep_cost_base * 1.2 * 1.2
     *                                 レベル4のとき prm_keep_cost_base * 1.2 * 1.2 * 1.2  という維持コストが設定される)
     * @return
     */
    Magic(const char* prm_name,
          int   prm_max_level,
          magic_point prm_cost_base, float prm_fRate_cost,
          magic_time  prm_time_of_casting_base , float prm_fRate_time_of_casting,
          magic_time  prm_time_of_invoking_base, float prm_fRate_time_of_invoking,
          magic_time  prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
          magic_point prm_keep_cost_base       , float prm_fRate_keep_cost_base);


//          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
//          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);
    void initialize() override;

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
     * 実行 .
     * @param prm_new_level
     */
    void execute(int prm_new_level);


    /**
     * 詠唱開始コールバック(１回だけコールバック) .
     */
    virtual void processCastBegin(int prm_now_level, int prm_new_level) {};

    /**
     * 詠唱中コールバック .
     */
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) {};

    /**
     * 詠唱終了コールバック .
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法発動開始コールバック。ここまでくると詠唱キャンセルは不可とする。(１回だけコールバック) .
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) {};

    /**
     * 魔法発動中コールバック .
     */
    virtual void processInvokeingBehavior(int prm_now_level, int prm_new_level) {};

    virtual void processInvokeFinish(int prm_last_level, int prm_now_level) {};
    /**
     * 魔法持続開始コールバック(１回だけコールバック) .
     */
    virtual void processEffectBegin(int prm_now_level) {};

    /**
     * 魔法持続中コールバック .
     */
    virtual void processEffectingBehavior(int prm_now_level) {};

    virtual void processEffectFinish(int prm_now_level) {};

    /**
     * 魔法破棄コールバック .
     */
    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) {};


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
