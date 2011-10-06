#ifndef RANKUPCONTROLLER_H_
#define RANKUPCONTROLLER_H_


namespace MyStg2nd {

/**
 * ランクアップシーンのコントローラー .
 * 主な仕事はランクアップステージの切り替えです。
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class RankUpSceneController : public GgafLib::DefaultScene {

public:
//    static RankUpSceneController* _pRankUpSceneController;

    char _buf[60];

    RankUpScene* _pSceneMainCannnel;

//    frame _frame_Begin;
//    frame _frame_Play;
//    frame _frame_End;
    int _loop;
    int _stage;
//    bool _had_ready_stage;
//    frame _frame_ready_stage;
    RankUpSceneController(const char* prm_name);

//    void setStage(int prm_stage) {
//        _stage = prm_stage;
//    }

    void onReset() override;
    void readyStage(int prm_stage);
//    void readyNextStage();
//    void cannelStage(int prm_stage);

    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~RankUpSceneController();

};

}
#endif /*RANKUPCONTROLLER_H_*/
