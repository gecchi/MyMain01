#ifndef GAMESCENE_H_
#define GAMESCENE_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "../World.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"


namespace VioletVreath {

#define pGAME_SCENE (pCARETAKER->getSpacetime()->getWorld()->pGameScene_)

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
class GameScene : public VvScene<GgafLib::DefaultScene> {

public:
    /**
     * �Q�[���V�[���̃t�F�[�Y�ԍ� .
     */
    enum {
        PHASE_INIT      ,  //��������
        PHASE_PRE_TITLE ,  //�^�C�g���O
        PHASE_TITLE     ,  //�^�C�g��
        PHASE_DEMO      ,  //�f���v���C
        PHASE_BEGINNING ,  //�Q�[���J�n�i���[�h�I�𓙁j
        PHASE_MAIN      ,  //�Q�[�����C��
        PHASE_ENDING    ,  //�Q�[���I��
        PHASE_GAME_OVER ,  //�Q�[���I�[�o�[
        PHASE_FINISH    ,  //�Q�[���V�[���I��
        PHASE_BANPEI,
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

public:
    GameScene(const char* prm_name);

    void onReset() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    void pauseGame();

    virtual ~GameScene();

};

}
#endif /*GAMESCENE_H_*/
