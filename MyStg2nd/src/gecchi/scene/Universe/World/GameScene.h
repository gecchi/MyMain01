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
 * �Q�[���V�[���N���X .
 * �w���̐�(Universe)�́A�Ƃ��鐢�E(World)�ŁA�Q�[�����s�Ȃ��Ă�����(GameScene)������܂����B�x<BR>
 * �Ƃ������T�O�̌��ɐ݌v���s���܂����B<BR>
 * �{�N���X�́A�Q�[���̑S�̓I�ȐU�镑�����������Ă��܂��B<BR>
 * ��ɁA�T�u�V�[���̐؂�ւ������s���܂��B<BR>
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameScene : public GgafDx9LibStg::DefaultScene {

public:
    CommonScene* _pCommonScene;
    MyShipScene* _pMyShipScene;
    StageController* _pStageController;
    /** �R�}����t���O */
    bool _is_frame_advance;
    bool _was_paused_flg_GameMainScene_prev_frame;
    int _stage;

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
