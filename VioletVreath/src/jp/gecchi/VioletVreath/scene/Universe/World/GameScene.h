#ifndef GAMESCENE_H_
#define GAMESCENE_H_


#ifdef P_WORLD
    #define P_GAME_SCENE (P_WORLD->pGameScene_)
#else
    #error P_WORLD isnt define
#endif


namespace VioletVreath {


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
class GameScene : public GgafLib::DefaultScene {

public:

    enum {
        PROG_INIT = 1  ,
        PROG_PRE_TITLE ,
        PROG_TITLE     ,
        PROG_DEMO      ,
        PROG_BEGINNING ,
        PROG_MAIN      ,
        PROG_ENDING    ,
        PROG_GAME_OVER ,
        PROG_FINISH    ,
    };


    CommonScene* pCommonScene_;
    MyShipScene* pMyShip_Scene;
//    GamePauseScene* pGamePauseScene_;

    MenuBoardPause* pMenuBoardPause_;
    /** GameMain�A�����́ADemo�̔z���ֈړ������ */
    StageWorld* pStageWorld_;

    /** �R�}����t���O */
    bool is_frame_advance_;
    bool was_paused_flg_GameMainScene_prev_frame_;

    GameScene(const char* prm_name);

    void onReset() override;
    void initialize() override;
    void onActive() override;

    void processBehavior() override;
    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~GameScene();

};

}
#endif /*GAMESCENE_H_*/
