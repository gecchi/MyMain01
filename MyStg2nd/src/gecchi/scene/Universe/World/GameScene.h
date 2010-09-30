#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#define GAME_PROG_INIT      1
#define GAME_PROG_DEMO      2
#define GAME_PROG_BEGINNING 3
#define GAME_PROG_MAIN      4
#define GAME_PROG_ENDING    5

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


    GameDemoScene*      _pScene_GameDemo;
    GameBeginningScene* _pScene_GameBeginning;
    GameMainScene*      _pScene_GameMain;
    GameEndingScene*    _pScene_GameEnding;
    GameOverScene*     _pScene_GameOver;


    /** コマ送りフラグ */
    bool _is_frame_advance;

    int _stage;
    GgafDx9LibStg::DefaultScene* _pSceneCannel;

    CommonScene* _pCommonScene;

    GameScene(const char* prm_name);
    virtual ~GameScene();

    void initialize() override;
    void processBehavior() override;
    void processJudgement() override;
    void processFinal() override;
    //virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override;
//    void cannelGameDemo();
//
//    void cannelGameMain();

};

}
#endif /*GAMESCENE_H_*/
