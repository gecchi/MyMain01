#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

#define GAMEMAIN_PROG_INIT     1
#define GAMEMAIN_PROG_BEGIN    2
#define GAMEMAIN_PROG_PLAY     3
#define GAMEMAIN_PROG_END      4

namespace MyStg2nd {

/**
 * ゲームメインシーンクラス .
 */
class GameMainScene : public GgafDx9LibStg::DefaultScene {

public:
    char _buf[20];
    GgafDx9Core::GgafDx9StringBoardActor* _pStringBoard_SCORE;
    GgafDx9Core::GgafDx9StringBoardActor* _pStringBoard_RANK;
    GgafDx9Core::GgafDx9StringBoardActor* _pStringBoard_STAMINA;
    GgafDx9Core::GgafDx9StringBoardActor* _pStringBoard01;
    GgafDx9Core::GgafDx9StringBoardActor* _pStringBoard02;



    Stage01Scene* _pScene_Stage01;
    Stage02Scene* _pScene_Stage02;
    Stage03Scene* _pScene_Stage03;
    Stage04Scene* _pScene_Stage04;
    Stage05Scene* _pScene_Stage05;
    StageScene* _pSceneMainCannnel;

    DWORD _dwFrame_Begin;
    DWORD _dwFrame_Play;
    DWORD _dwFrame_End;

    int _stage;

    GameMainScene(const char* prm_name);

    void setStage(int prm_stage) {
        _stage = prm_stage;
    }

    void reset();
    void ready(int prm_stage);


    void cannelStage(int prm_stage);

    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~GameMainScene();

};

}
#endif /*GAMEMAINSCENE_H_*/
