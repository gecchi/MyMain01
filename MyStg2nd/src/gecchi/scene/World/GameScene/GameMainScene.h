#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

#define GAMEMAIN_PROG_INIT     1
#define GAMEMAIN_PROG_BEGIN    2
#define GAMEMAIN_PROG_PLAY     3
#define GAMEMAIN_PROG_END      4

namespace MyStg2nd {

class GameMainScene : public GgafDx9LibStg::DefaultScene {

public:
    char _buf[20];
    GgafDx9LibStg::FontBoardActor* _pFontBoard_SCORE;
    GgafDx9LibStg::FontBoardActor* _pFontBoard01;
    GgafDx9LibStg::FontBoardActor* _pFontBoard02;



    Stage01Scene* _pStage01;
    Stage02Scene* _pStage02;
    Stage03Scene* _pStage03;
    Stage04Scene* _pStage04;
    Stage05Scene* _pStage05;
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

    void initialize();

    virtual void processBehavior();

    virtual void processFinal();

    virtual ~GameMainScene();

};

}
#endif /*GAMEMAINSCENE_H_*/
