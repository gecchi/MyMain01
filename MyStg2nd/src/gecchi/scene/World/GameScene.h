#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#define GAME_PROG_INIT      1
#define GAME_PROG_DEMO      2
#define GAME_PROG_BEGINNING 3
#define GAME_PROG_MAIN      4
#define GAME_PROG_ENDING    5

namespace MyStg2nd {

class GameScene : public GgafDx9LibStg::DefaultScene {

public:
    GameDemoScene*      _pGameDemo;
    GameBeginningScene* _pGameBeginning;
    GameMainScene*      _pGameMain;
    GameEndingScene*    _pGameEnding;

    int _stage;
    GgafDx9LibStg::DefaultScene* _pSceneCannel;

    CommonScene* _pCommonScene;

    GameScene(const char* prm_name);
    virtual ~GameScene();

    void initialize();
    virtual void processBehavior();
    virtual void processFinal();

//    void cannelGameDemo();
//
//    void cannelGameMain();

};

}
#endif /*GAMESCENE_H_*/
