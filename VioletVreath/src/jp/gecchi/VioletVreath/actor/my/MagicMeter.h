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
        SE_NG_MP_IS_SHORT       ,
        SE_EFFECT_MAGIC    ,
        SE_NOTICE_LEVELDOWN_MAGIC,
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

//    /** 自機のMP */
//    GgafLib::PxQuantity* pMP_MyShip_;
//    /** 自機のVreath */
//    GgafLib::PxQuantity* pVreath_MyShip_;
//    /** Vreathのダメージ分表示用 */
//    GgafLib::PxQuantity damage_disp_vreath;

    /** 残魔法効果持続時間表示 */
    MagicMeterStatus* pMagicMeterStatus_;
    /** エネルーバー */
    MpBar* pMpBar_;
    /** コスト表示バー */
    CostDispBar* pMpCostDispBar_;
    /** ヴレスーバー */
    VreathBar* pVreathBar_;
    /** コスト表示バー */
    CostDispBar* pVreathCostDispBar_;
    /** ダメージ表示バー */
    DamageDispBar* pDamageDispBar_;

    /** 魔法リスト */
    MagicList lstMagic_;

    /** メータ主カーソル */
    MagicMeterCursor001* pMainCur_;
    /** 各魔法(配列)のレベルのカーソル */
    MagicLvCursor001** papLvTgtMvCur_;
    /** 各魔法(配列)の現レベル強調表示用カーソル */
    MagicLvCursor002** papLvNowCur_;
    /** 各魔法(配列)の詠唱中レベル強調表示用カーソル */
    MagicLvCursor003** papLvCastingCur_;

    /** [r]現在の各魔法(配列)のロールアップ表示状態(0.0:閉じている ～ 1.0:開いている) */
    float* r_roll_;
    /** [r/w]各魔法(配列)のロールアップの速さ */
    float* r_roll_velo_;

    float alpha_velo_;

    /** 魔法メーター１つの横幅(px) */
    const float width_px_;
    /** 魔法メーター１つの高さ(px) */
    const float height_px_;
    /** 魔法メーター１つの横幅 */
    const coord width_;
    /** 魔法メーター１つの高さ */
    const coord height_;

    std::stringstream st_[10];

    /** [r]詠唱中効果音発生管理 */
    GgafDxCore::GgafDxSeTransmitterForActor* pSeTx4Cast_;
    /** [r]発動中効果音発生管理 */
    GgafDxCore::GgafDxSeTransmitterForActor* pSeTx4Invoke_;
    /** 予告発生の残り時間を設定 */
    frame fraeme_of_notice_remaind_;

public:
    MagicMeter(const char* prm_name, int* prm_pMP_MyShip, int* prm_pVreath_MyShip);

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

