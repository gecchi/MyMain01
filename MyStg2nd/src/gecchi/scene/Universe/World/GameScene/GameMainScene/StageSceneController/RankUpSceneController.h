#ifndef RANKUPSCENECONTROLLER_H_
#define RANKUPSCENECONTROLLER_H_


namespace MyStg2nd {

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

    RankUpSceneController(const char* prm_name);

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
