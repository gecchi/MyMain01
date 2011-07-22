#ifndef STAGECONTROLLER_H_
#define STAGECONTROLLER_H_


namespace MyStg2nd {

/**
 * ゲームメインシーンクラス .
 */
class StageController : public GgafDx9LibStg::DefaultScene {

public:
//    static StageController* _pStageController;

    char _buf[60];

    StageScene* _pSceneMainCannnel;

//    frame _frame_Begin;
//    frame _frame_Play;
//    frame _frame_End;

    int _stage;
    bool _had_ready_stage;
//    frame _frame_ready_stage;
    StageController(const char* prm_name);

//    void setStage(int prm_stage) {
//        _stage = prm_stage;
//    }

    void onReset() override;
    void readyStage(int prm_stage);
    void readyNextStage();
//    void cannelStage(int prm_stage);

    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~StageController();

};

}
#endif /*STAGECONTROLLER_H_*/
