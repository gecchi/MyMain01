#ifndef STAGECONTROLLER_H_
#define STAGECONTROLLER_H_

#ifdef P_STAGE_WORLD
    #define P_STAGE_CONTROLLER (P_STAGE_WORLD->_pStageController)
#else
    #error P_STAGE_WORLD isnt define
#endif

namespace MyStg2nd {

/**
 * �Q�[�����C���V�[���̃R���g���[���[ .
 * ��Ȏd���̓��C���X�e�[�W�̐؂�ւ��A
 * �����N�A�b�v�V�[���̍����ł��B
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class StageController : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_PLAY_STAGE,
        PROG_PLAY_TRANSIT,
        PROG_PLAY_RANKUP,
        PROG_FINISH  ,
    };

//    static StageController* _pStageController;

    char _buf[60];
    /** ���C���X�e�[�W(���݃A�N�e�B�u�Ȗʂ̃V�[���|�C���^�j */
    Stage* _pStageMainCannel;
    /** �ʉ߃X�e�[�W�V�[�� */
    TransitStage* _pTransitStage;

    int _loop;
    int _main_stage;

    StageController(const char* prm_name);


    void onReset() override;
    void readyStage(int prm_main_stage);
    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~StageController();

};

}
#endif /*STAGECONTROLLER_H_*/
