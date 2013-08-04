#ifndef MAGICMETER_H_
#define MAGICMETER_H_
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"

namespace VioletVreath {

#ifdef P_MYSHIP
    #define P_MAGICMETER (P_MYSHIP->pMagicMeter_)
#else
    #error P_MAGICMETER isnt define
#endif


typedef GgafCore::GgafLinkedListRing<Magic> MagicList;

/**
 * 魔法メーター .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultBoardSetActor {
    enum {
        SE_CURSOR_MOVE_METER       ,
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
    TractorMagic* pTractorMagic_;
    SpeedMagic*   pSpeedMagic_;
    LockonMagic*  pLockonMagic_;
    TorpedoMagic* pTorpedoMagic_;
    LaserMagic*   pLaserMagic_;
    OptionMagic*  pOptionMagic_;
    VreathMagic*  pVreathMagic_;
    SmileMagic*   pSmileMagic_;

    /** 自機のMP */
    GgafLib::AmountGraph* pMP_MyShip_;
    /** MPのCOST分表示用 */
    GgafLib::AmountGraph cost_disp_mp_;
    /** 自機のVreath */
    GgafLib::AmountGraph* pVreath_MyShip_;
    /** VreathのCOST分表示用 */
    GgafLib::AmountGraph cost_disp_vreath;
    /** Vreathのダメージ分表示用 */
    GgafLib::AmountGraph damage_disp_vreath;

    /** 残魔法効果持続時間表示 */
    MagicMeterStatus* pMagicMeterStatus_;
    /** エネルギーバー */
    EnergyBar* pEnergyBar_;
    /** コスト表示バー */
    CostDispBar* pCostDispBar_;
    /** ヴレスギーバー */
    VreathBar* pVreathBar_;
    /** コスト表示バー */
    CostDispBar* pCostDispBar2_;
    /** ダメージ表示バー */
    DamageDispBar* pDamageDispBar_;

    /** 魔法リスト */
    MagicList lstMagic_;

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

    float alpha_velo_;

    /** 魔法メーター１つの横幅(px) */
    float width_px_;
    /** 魔法メーター１つの高さ(px) */
    float height_px_;
    /** 魔法メーター１つの横幅 */
    coord width_;
    /** 魔法メーター１つの高さ */
    coord height_;

    std::stringstream st_[10];

    /** [r]詠唱時効果音発生管理オブジェクト2 */
    GgafDxCore::GgafDxSeTransmitterForActor* pSeTx4Cast_;
    GgafDxCore::GgafDxSeTransmitterForActor* pSeTx4Invoke_;
public:
    MagicMeter(const char* prm_name, GgafLib::AmountGraph* prm_pMP_MyShip, GgafLib::AmountGraph* prm_pVreath_MyShip);

    void saveStatus(int prm_saveno);

    void loadStatus(int prm_saveno);

    void save(std::stringstream& sts);

    void load(std::stringstream& sts);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void processDraw() override;

    void rollOpen(int prm_meter_index);

    void rollClose(int prm_meter_index);


    void setMeterAlpha(float a);
    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/

