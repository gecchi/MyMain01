#ifndef STAGECONTROLLER_H_
#define STAGECONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/TransitStage.h"

#ifdef P_STAGE_WORLD
    #define P_STAGE_CTRLER (P_STAGE_WORLD->pStageCtrler_)
#else
    #error P_STAGE_WORLD isnt define
#endif

HASHVAL(EVENT_STG01_WAS_END);
HASHVAL(EVENT_STG02_WAS_END);
HASHVAL(EVENT_STG03_WAS_END);
HASHVAL(EVENT_STG04_WAS_END);
HASHVAL(EVENT_STG05_WAS_END);

HASHVAL(EVENT_TRANSIT_WAS_END);

namespace VioletVreath {

/**
 * ゲームメインシーンのコントローラー .
 * 主な仕事はメインステージの切り替え、
 * ランクアップシーンの差込です。
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class StageController : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT        ,
        PROG_BEGIN       ,
        PROG_PLAY_STAGE  ,
        PROG_PLAY_TRANSIT,
        PROG_PLAY_RANKUP ,
        PROG_FINISH      ,
        PROG_BANPEI,
    };

    char buf_[60];
    /** メインステージ(現在アクティブな面のシーンポインタ） */
    Stage* pStageMainCannel_;
    /** 通過ステージシーン */
    TransitStage* pTransitStage_;

    LabelSceneSymbol* _pSceneSymbol;

    int loop_;
    int main_stage_;

public:
    StageController(const char* prm_name);

    void onReset() override;
    void readyStage(int prm_main_stage);
    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~StageController();

};

}
#endif /*STAGECONTROLLER_H_*/
