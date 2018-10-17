#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../World.h"
#include "jp/gecchi/VioletVreath/God.h"


namespace VioletVreath {

#define pGAME_SCENE (pGOD->getSpacetime()->getWorld()->pGameScene_)

/**
 * �Q�[���V�[���N���X .
 * �w���̐�(Spacetime)�́A�Ƃ��鐢�E(World)�ŁA�Q�[�����s�Ȃ��Ă�����(GameScene)������܂����B�x<BR>
 * �Ƃ������T�O�̌��ɐ݌v���s���܂����B<BR>
 * �{�N���X�́A�Q�[���̑S�̓I�ȐU�镑�����������Ă��܂��B<BR>
 * ��ɁA�q�V�[���̐؂�ւ������s���܂��B<BR>
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT      ,
        PROG_PRE_TITLE ,
        PROG_TITLE     ,
        PROG_DEMO      ,
        PROG_BEGINNING ,
        PROG_MAIN      ,
        PROG_ENDING    ,
        PROG_GAME_OVER ,
        PROG_FINISH    ,
        PROG_BANPEI,
    };
    enum {
        BGM_DEMO,
    };

    CommonScene* pCommonScene_;
    MyShipScene* pMyShipScene_;

    MenuBoardPause* pMenuBoardPause_;
    /** GameMain�A�����́ADemo�̔z���ֈړ������ */
    StageWorld* pStageWorld_;

    /** �R�}����t���O */
    bool is_frame_advance_;
    /** �P�t���[���O�AGameMainScene���ꎞ��~��Ԃ��������ǂ��� */
    bool was_paused_flg_GameMainScene_prev_frame_;

    GgafLib::OctreeRounder* pHitCheckRounder_;
public:
    GameScene(const char* prm_name);

    void onReset() override;
    void initialize() override;
    void onActive() override;

    void processBehavior() override;
    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    void pauseGame();

    virtual ~GameScene();

};

}
#endif /*GAMESCENE_H_*/
