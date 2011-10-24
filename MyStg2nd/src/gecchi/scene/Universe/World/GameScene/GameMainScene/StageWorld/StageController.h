#ifndef STAGECONTROLLER_H_
#define STAGECONTROLLER_H_

#ifdef P_STAGE_WORLD
    #define P_STAGE_CONTROLLER (P_STAGE_WORLD->_pStageController)
#else
    #error P_STAGE_WORLD isnt define
#endif

namespace MyStg2nd {

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
//    static StageController* _pStageController;

    char _buf[60];
    /** メインステージ(現在アクティブな面のシーンポインタ） */
    Stage* _pStageMainCannel;
    /** 通過ステージシーン */
    TransitStage* _pTransitStage;

    int _loop;
    int _main_stage;

    StageController(const char* prm_name);


    void onReset() override;
    void readyStage(int prm_main_stage);
    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~StageController();

};

}
#endif /*STAGECONTROLLER_H_*/
