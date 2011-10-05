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
    #define P_STAGE_CONTROLLER (P_GAME_SCENE->_pStageSceneController)
#else
    #error P_GAME_SCENE isnt define
#endif
namespace MyStg2nd {


/**
 * ゲームシーンクラス .
 * 『この世(Universe)の、とある世界(World)で、ゲームが行なわれている場面(GameScene)がありました。』<BR>
 * といった概念の元に設計を行いました。<BR>
 * 本クラスは、ゲームの全体的な振る舞いを実装しています。<BR>
 * 主に、サブシーンの切り替え等を行います。<BR>
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameScene : public GgafLib::DefaultScene {

public:
    CommonScene* _pCommonScene;
    MyShipScene* _pMyShipScene;
    GamePauseScene* _pGamePauseScene;
    /** GameMain、或いは、Demoの配下へ移動される */
    StageSceneController* _pStageSceneController;
    /** コマ送りフラグ */
    bool _is_frame_advance;
    bool _was_paused_flg_GameMainScene_prev_frame;

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
