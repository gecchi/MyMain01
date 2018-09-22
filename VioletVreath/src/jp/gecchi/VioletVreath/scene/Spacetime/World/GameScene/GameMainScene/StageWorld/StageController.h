#ifndef STAGECONTROLLER_H_
#define STAGECONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../StageWorld.h"
#include "../StageWorld/StageController/Stage.h"
#include "../StageWorld/StageController/TransitStage.h"

#ifdef pSTAGE_WORLD
    #define pSTAGE_CTRLER (pSTAGE_WORLD->pStageCtrler_)
#else
    #error pSTAGE_WORLD isnt define
#endif
DECLARE_HASHVAL(EVENT_STAGEDEBUG_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGE01_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGE02_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGE03_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGE04_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGE05_WAS_FINISHED);

DECLARE_HASHVAL(EVENT_TRANSIT_WAS_END);

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
