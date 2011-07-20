#ifndef GAMESCENE_H_
#define GAMESCENE_H_


#ifdef P_WORLD
    #define P_GAME_SCENE (P_WORLD->_pGameScene)
#else
    #error P_WORLD isnt define
#endif

#ifdef P_GAME_SCENE
    #define P_COMMON_SCENE (P_GAME_SCENE->_pCommonScene)
#else
    #error P_GAME_SCENE isnt define
#endif

#ifdef P_GAME_SCENE
    #define P_MYSHIP_SCENE (P_GAME_SCENE->_pMyShipScene)
#else
    #error P_GAME_SCENE isnt define
#endif

#ifdef P_GAME_SCENE
    #define P_STAGE_CONTROLLER (P_GAME_SCENE->_pStageController)
#else
    #error P_GAME_SCENE isnt define
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

private:
//    void changeFlippingSubScene(progress prm_progress);
//    void changeFadeingSubScene(progress prm_progress, frame prm_fadeout_frames = FADE_FRAMES, frame prm_fadein_frames = FADE_FRAMES);
public:
    CommonScene* _pCommonScene;
    MyShipScene* _pMyShipScene;
    StageController* _pStageController;
//    GamePreTitleScene*   _pScene_PreGameTitle;
//    GameTitleScene*      _pScene_GameTitle;
//    GameDemoScene*      _pScene_GameDemo;
//    GameBeginningScene* _pScene_GameBeginning;
//    GameMainScene*      _pScene_GameMain;
//    GameEndingScene*    _pScene_GameEnding;
//    GameOverScene*     _pScene_GameOver;

//    std::map<progress, DefaultScene*> _mapSubScene;
    /** コマ送りフラグ */
    bool _is_frame_advance;
    bool _was_paused_flg_GameMainScene_prev_frame;
    int _stage;
//    GgafDx9LibStg::DefaultScene* _pSceneCannel;


    GameScene(const char* prm_name);

    void onReset() override;
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
