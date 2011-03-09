#ifndef MAGIC_H_
#define MAGIC_H_
namespace MyStg2nd {

#define MAGIC_NOTHING 0
#define MAGIC_STAND_BY 1
#define MAGIC_CASTING 2
#define MAGIC_INVOKING 3
#define MAGIC_EFFECTING 4
#define MAGIC_ABANDONING 9


typedef int magic_point;
typedef int magic_time;
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
class Magic : public GgafCore::GgafObject {
public:
    /**
     * 各レベルの情報 .
     */
    class LevelInfo {
    public:
        /** 該当レベルで魔法が適用中であるかどうか */
        bool _is_effecting;
        /** 魔法効果持続終了残り時間 */
        magic_time _remaining_time_of_effect;
        /** 魔法効果持続中コスト  */
        magic_point _keep_cost;
        /** アニメパターン番号 */
        int _pno;
        LevelInfo() : _is_effecting(false),
                      _remaining_time_of_effect(0),
                      _keep_cost(0),
                      _pno(0) {
        }
    };
    GgafDx9Core::GgafDx9GeometricActor* _pCaster;
    GgafDx9Core::GgafDx9GeometricActor* _pReceiver;

    char* _name;
    magic_point* _pMP;
    MagicMeter* _pMagicMeter;
    /** 新しいレベル */
    int _new_level;
    /** 現在のレベル */
    int _level;
    /** 最高レベル 1 */
    int _max_level;
    /** 各レベル毎の情報 */
    LevelInfo _lvinfo[MMETER_MAX_LEVEL_Y];

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

    magic_time _executing_time;
    magic_time _time_of_next_state;

    /** 状態 */
    int _state;
    /** レベルアップ中かどうか */
    boolean _is_leveling;

    float _discount_rate;

    float _rr;
    float _velo_rr;

public:
    /**
     *
     * @param prm_name 魔法名
     * @param prm_pMagicMeter 魔法メーター
     * @param prm_pMP
     * @param prm_max_level 本魔法の最高レベル 1～MMETER_MAX_LEVEL_Y
     * @param prm_cost_base 基本魔法コスト
     * @param prm_fRate_cost 飛びレベル時の魔法コスト削減割合 0.0～1.0 (1.0:飛びレベルでも割引無し)
     * @param prm_time_of_casting_base 基本魔法詠唱時間
     * @param prm_fRate_time_of_casting 飛びレベル時の詠唱時間削減割合0.0～1.0 (1.0:飛びレベルでも割引無し)
     * @param prm_time_of_invoking_base 基本魔法発動時間
     * @param prm_fRate_time_of_invoking 飛びレベル時の発動時間削減割合0.0～1.0 (1.0:飛びレベルでも割引無し)
     * @param prm_time_of_effect_base 基本魔法効果持続時間
     * @param prm_fRate_time_of_effecting 飛びレベル時の果持続時間削減割合0.0～1.0 (1.0:飛びレベルでも割引無し)
     * @param prm_keep_cost_base 基本魔法効果持続中維持コスト
     * @param prm_fRate_keep_cost レベル毎の果持続中維持コスト増加割合 0.0～1.0 (0.0:レベルによる維持コスト増加無し)
     * @return
     */
    Magic(const char* prm_name,
          MagicMeter* prm_pMagicMeter,
          magic_point* prm_pMP,
                int   prm_max_level,
                magic_point prm_cost_base, float prm_fRate_cost,
                magic_time  prm_time_of_casting_base , float prm_fRate_time_of_casting,
                magic_time  prm_time_of_invoking_base, float prm_fRate_time_of_invoking,
                magic_time  prm_time_of_effect_base  , float prm_fRate_time_of_effecting,
                magic_point prm_keep_cost_base       , float prm_fRate_keep_cost_base);


//          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
//          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);

    void behave();

    void rollOpen();
    void rollClose();

    bool execute(int prm_new_level);


    /**
     * 詠唱する .
     */
    virtual void cast();

    /**
     * 発動する.
     */
    virtual void invoke();

    /**
     * 終了する .
     */
    virtual void effect();

    /**
     * 遺棄する .
     */
    virtual void abandon(int prm_last_level);

    /**
     * 詠唱開始コールバック(１回だけコールバック) .
     */
    virtual void processCastBegin() = 0;

    /**
     * 詠唱中コールバック .
     */
    virtual void processCastingBehavior() = 0;

    /**
     * 魔法発動開始コールバック。ここまでくると詠唱キャンセルは不可とする。(１回だけコールバック) .
     */
    virtual void processInvokeBegin() = 0;

    /**
     * 魔法発動中コールバック .
     */
    virtual void processInvokeingBehavior() = 0;

    /**
     * 魔法持続開始コールバック(１回だけコールバック) .
     */
    virtual void processEffectBegin() = 0;

    /**
     * 魔法持続中コールバック .
     */
    virtual void processEffectingBehavior() = 0;

    /**
     * 魔法破棄コールバック .
     */
    virtual void processOnAbandon(int prm_last_level) = 0;


    /**
     * 魔法を完了する .
     */
    virtual void commit();
    /**
     * 魔法をキャンセルする .
     */
    virtual void cancel();

    virtual ~Magic();
};

}
#endif /*MAGIC_H_*/
