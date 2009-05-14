#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#define GAME_PROG_INIT      1
#define GAME_PROG_DEMO      2
#define GAME_PROG_BEGINNING 3
#define GAME_PROG_MAIN      4
#define GAME_PROG_ENDING    5

namespace MyStg2nd {


/**
 * �Q�[���V�[���N���X .
 * ���̐��ɂƂ��鐢�E�ŁA�Q�[�����s�Ȃ��Ă����ʂ�����܂����B<BR>
 * �{�N���X�́A�Q�[���̑S�̓I�ȐU�镑�����������Ă��܂��B<BR>
 */
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
    void processBehavior();
    void processJudgement();
    void processFinal();

//    void cannelGameDemo();
//
//    void cannelGameMain();

};

}
#endif /*GAMESCENE_H_*/
