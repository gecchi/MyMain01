#ifndef RANKUPSTAGECONTROLLER_H_
#define RANKUPSTAGECONTROLLER_H_

#ifdef P_STAGE_WORLD
    #define P_RANK_UP_CONTROLLER (P_STAGE_WORLD->_pRankUpStageController)
#else
    #error P_STAGE_CONTROLLER isnt define
#endif

namespace MyStg2nd {

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
//    static RankUpStageController* _pRankUpStageController;

    char _buf[60];
    RankUpStage* _apRankUpStage[MAX_RANKUP_SCENE];
    RankUpStage* _pNowRankUpStage;

    RankUpStageController(const char* prm_name);
    void execute();

    void onReset() override;
    void ready(int prm_rank_level);
//    void readyNextStage();
//    void cannelStage(int prm_stage);

    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~RankUpStageController();

};

}
#endif /*RANKUPSTAGECONTROLLER_H_*/
