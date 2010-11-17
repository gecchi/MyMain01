#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

#define GAMEMAIN_SCENE_PROG_INIT     1
#define GAMEMAIN_SCENE_PROG_BEGIN    2
#define GAMEMAIN_SCENE_PROG_PLAY     3
#define GAMEMAIN_SCENE_PROG_END      4



namespace MyStg2nd {

/**
 * ゲームメインシーンクラス .
 */
class GameMainScene : public GgafDx9LibStg::DefaultScene {

public:
//    static GameMainScene* _pGameMainScene;

    char _buf[20];
    LabelGecchi16Font* _pFont16_SCORE;
    LabelGecchi16Font* _pFont16_RANK;
    LabelGecchi16Font* _pFont16_STAMINA;
    LabelGecchi8Font* _pFont8_JIKI_X;
    LabelGecchi8Font* _pFont8_JIKI_Y;
    LabelGecchi8Font* _pFont8_JIKI_Z;
    LabelGecchi16Font* _pFont1601;
    LabelGecchi16Font* _pFont1602;

    StageScene* _pSceneMainCannnel;

//    frame _frame_Begin;
//    frame _frame_Play;
//    frame _frame_End;

    int _stage;
    bool _had_ready_stage;
//    frame _frame_ready_stage;
    GameMainScene(const char* prm_name);

//    void setStage(int prm_stage) {
//        _stage = prm_stage;
//    }

    void reset() override;
    void readyStage(int prm_stage);
    void readyNextStage();
//    void cannelStage(int prm_stage);

    void initialize() override;
    void processBehavior() override;
    void processFinal() override;
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~GameMainScene();

};

}
#endif /*GAMEMAINSCENE_H_*/
