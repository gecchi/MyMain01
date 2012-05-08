#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace VioletVreath {

#define MMETER_MAX_LEVEL 9

#ifdef P_MYSHIP_SCENE
    #define P_MAGICMETER (P_MYSHIP_SCENE->pMagicMeter_)
#else
    #error P_MYSHIP_SCENE isnt define
#endif


/**
 * 魔法メーター .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultBoardSetActor {
    enum {
        SE_CURSOR_MOVE_METER = 0   ,
        SE_CURSOR_MOVE_LEVEL       ,
        SE_CURSOR_MOVE_LEVEL_CANCEL,
        SE_CURSOR_BAD_MOVE         ,
        SE_EXECUTE_LEVELUP_MAGIC   ,
        SE_EXECUTE_LEVELDOWN_MAGIC ,
        SE_EXECUTE_CANCEL_LEVELUP_MAGIC   ,
        SE_EXECUTE_CANCEL_LEVELDOWN_MAGIC ,
        SE_CANT_INVOKE_MAGIC       ,
        SE_BAD_OPERATION   ,
    };
public:
    D3DXHANDLE h_active_magic_;
    /** MP */
    GgafLib::AmountGraph mp_;

    /** COST */
    GgafLib::AmountGraph cost_disp_;

    /** 残魔法効果持続時間表示 */
    MagicMeterStatus* pMagicMeterStatus_;
    /** エネルギーバー */
    EnergyBar* pEnergyBar_;
    /** コスト表示バー */
    CostDispBar* pCostDispBar_;
    /** 魔法リスト */
    GgafCore::GgafLinkedListRing<Magic> ringMagics_;

    /** メータ主カーソル */
    MagicMeterCursor001* pMagicCursor_;
    /** 各魔法(配列)のレベルのカーソル */
    MagicLvCursor001** papLvTargetCursor_;
    /** 各魔法(配列)の現レベル強調表示用カーソル */
    MagicLvCursor002** papLvHilightCursor_;
    /** 各魔法(配列)の詠唱中レベル強調表示用カーソル */
    MagicLvCursor003** papLvCastingMarkCursor_;

    /** [r]現在の各魔法(配列)のロールアップ表示状態(0.0:閉じている ～ 1.0:開いている) */
    float* paFloat_rr_;
    /** [r/w]各魔法(配列)のロールアップの速さ */
    float* paFloat_velo_rr_;

    /** 魔法メーター１つの横幅(px) */
    float width_px_;
    /** 魔法メーター１つの高さ(px) */
    float height_px_;
    /** 魔法メーター１つの横幅 */
    coord width_;
    /** 魔法メーター１つの高さ */
    coord height_;

    std::stringstream st_[10];

public:
    MagicMeter(const char* prm_name);

    void saveStatus(int prm_saveno);

    void loadStatus(int prm_saveno);

    void save(std::stringstream& sts);

    void load(std::stringstream& sts);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void processDraw() override;

    void rollOpen(int prm_meter_index);

    void rollClose(int prm_meter_index);

    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/

