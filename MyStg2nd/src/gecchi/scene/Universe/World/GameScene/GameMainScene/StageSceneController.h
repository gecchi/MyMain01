#ifndef STAGESCENECONTROLLER_H_
#define STAGESCENECONTROLLER_H_


namespace MyStg2nd {

/**
 * ゲームメインシーンのコントローラー .
 * 主な仕事はメインステージの切り替え、
 * ランクアップシーンの差込です。
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class StageSceneController : public GgafLib::DefaultScene {

public:
//    static StageSceneController* _pStageSceneController;

    char _buf[60];
    /** メインステージ(現在アクティブな面のシーンポインタ） */
    StageScene* _pStageSceneMainCannel;
    /** 通過ステージシーン */
    TransitStage* _pTransitStage;
    /** ランクアップ挿入シーン */
    RankUpSceneController* _pRankUpSceneController;
    int _rank_level_wk;
    int _loop;
    int _main_stage;
    StageSceneController(const char* prm_name);


    void onReset() override;
    void readyStage(int prm_main_stage);
    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~StageSceneController();

};

}
#endif /*STAGESCENECONTROLLER_H_*/
