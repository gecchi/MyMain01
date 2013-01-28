#ifndef RANKUPSTAGECONTROLLER_H_
#define RANKUPSTAGECONTROLLER_H_

#ifdef P_STAGE_WORLD
    #define P_RANK_UP_CONTROLLER (P_STAGE_WORLD->pRankUpStageCtrler_)
#else
    #error P_STAGE_CTRLER isnt define
#endif

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
        PROG_INIT = 1,
        PROG_PLAY    ,
        PROG_FINISH  ,
    };

    char buf_[60];
    RankUpStage* apRankUpStage_[MAX_RANKUP_SCENE];
    RankUpStage* pNowRankUpStage_;

public:
    RankUpStageController(const char* prm_name);
    void execute();

    void onReset() override;
    void ready(int prm_rank_level);

    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~RankUpStageController();

};

}
#endif /*RANKUPSTAGECONTROLLER_H_*/
