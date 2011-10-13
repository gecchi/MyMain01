#ifndef RANKUPSCENECONTROLLER_H_
#define RANKUPSCENECONTROLLER_H_


namespace MyStg2nd {
#ifdef P_STAGE_CONTROLLER
    #define P_RANK_UP_CONTROLLER (P_STAGE_CONTROLLER->_pRankUpSceneController)
#else
    #error P_STAGE_CONTROLLER isnt define
#endif
/**
 * ランクアップシーンのコントローラー .
 * 主な仕事はランクアップステージの切り替えです。
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class RankUpSceneController : public StageScene {

public:
//    static RankUpSceneController* _pRankUpSceneController;

    char _buf[60];
    RankUpScene* _pLastRankUpScene;

    RankUpSceneController(const char* prm_name);
    void execute();
    void slowdown(RankUpScene* prm_pLastAdded);
    void slowRelease(RankUpScene* prm_pInactive);

    void onReset() override;
    void readyStage(int prm_rank_level);
//    void readyNextStage();
//    void cannelStage(int prm_stage);

    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~RankUpSceneController();

};

}
#endif /*RANKUPSCENECONTROLLER_H_*/
