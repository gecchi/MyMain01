#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#define GAME_SCENE_PROG_INIT      1
#define GAME_SCENE_PROG_PRE_TITLE 2
#define GAME_SCENE_PROG_TITLE     3
#define GAME_SCENE_PROG_DEMO      4
#define GAME_SCENE_PROG_BEGINNING 5
#define GAME_SCENE_PROG_MAIN      6
#define GAME_SCENE_PROG_ENDING    7
#define GAME_SCENE_PROG_GAME_OVER 8
#ifdef P_WORLD
    #define P_GAME_SCENE (P_WORLD->_pGameScene)
#else
    #error P_WORLD isnt define
#endif

namespace MyStg2nd {


/**
 * ゲームシーンクラス .
 * この世にとある世界で、ゲームが行なわれている場面がありました。<BR>
 * 本クラスは、ゲームの全体的な振る舞いを実装しています。<BR>
 * 主に、サブシーンの切り替えです。
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameScene : public GgafDx9LibStg::DefaultScene {

public:
    CommonScene* _pCommonScene;
    MyShipScene* _pMyShipScene;
    GamePreTitleScene*   _pScene_PreGameTitle;
    GameTitleScene*      _pScene_GameTitle;
    GameDemoScene*      _pScene_GameDemo;
    GameBeginningScene* _pScene_GameBeginning;
    GameMainScene*      _pScene_GameMain;
    GameEndingScene*    _pScene_GameEnding;
    GameOverScene*     _pScene_GameOver;


    /** コマ送りフラグ */
    bool _is_frame_advance;

    int _stage;
//    GgafDx9LibStg::DefaultScene* _pSceneCannel;



    GameScene(const char* prm_name);

    void reset() override;
    void initialize() override;
    void onActive() override;

    void processBehavior() override;
    void processJudgement() override;
    void processFinal() override;

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~GameScene();

};

}
#endif /*GAMESCENE_H_*/
