#ifndef RANKUPSTAGECONTROLLER_H_
#define RANKUPSTAGECONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld.h"

#ifdef P_STAGE_WORLD
    #define P_RANKUP_CONTROLLER (P_STAGE_WORLD->pRankUpStageCtrler_)
#else
    #error P_STAGE_CTRLER isnt define
#endif

HASHVAL(EVENT_RANKUP_WAS_END);
HASHVAL(EVENT_RANKUP_ON_GARBAGED);

namespace VioletVreath {

#define MAX_RANKUP_SCENE 100

/**
 * ランクアップシーンのコントローラー .
 * 主な仕事はランクアップステージの切り替えです。
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class RankUpStageController : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT  ,
        PROG_PLAY  ,
        PROG_FINISH,
        PROG_BANPEI,
    };

    char buf_[60];
    RankUpStage* apRankUpStage_[MAX_RANKUP_SCENE];
    RankUpStage* pNowRankUpStage_;
    GgafDxCore::GgafDxSeConnection* pSeConn_RankUpStageExec_;
public:
    RankUpStageController(const char* prm_name);
    void startRunkUpStage(int prm_rank_up_level);

    void onReset() override;
    void ready(int prm_rank_up_level);

    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    /**
     * 配下のランクアップステージを全て開放(sayonara())する。
     */
    void sayonaraRankUpStages();
    virtual ~RankUpStageController();

};

}
#endif /*RANKUPSTAGECONTROLLER_H_*/
