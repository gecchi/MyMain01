#ifndef STAGE01PART_H_
#define STAGE01PART_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "../Stage01PartController.h"
namespace VioletVreath {

/**
 * �X�e�[�W�f�o�b�O�p�[�g��� .
 * @version 1.00
 * @since 2018/09/19
 * @author Masatoshi Tsuge
 */
template<class T>
class Stage01Part :  public T {



public:
    enum {
        PROG_INIT    ,
        PROG_BEGIN   ,
        PROG_PLAYING ,
        PROG_END     ,
        PROG_BANPEI,
    };

    hashval event_part_finish_;
public:
    Stage01Part(const char* prm_name, hashval prm_event_part_finish): T(prm_name) {
        event_part_finish_ = prm_event_part_finish;
    }

    virtual void processJudgement() override {
        frame frame_of_behaving = this->getBehaveingFrame();
        frame frame_of_last_event = this->getLastEventFrame();
        GgafDx::BgmConductor* pBgm = this->getBgmConductor();

        if (frame_of_behaving == 1) {
            if (pBgm->isReady(0)) {
                //�Z��V�[����BGM��S�ăt�F�[�h�A�E�g
                Stage01PartController* pStagePartController = (Stage01PartController*)(this->getParent());
                pStagePartController->fadeoutBgmTree(300);
                //�����̃V�[��BGM�����t�J�n�I
                pBgm->performFromTheBegining(0);
            }
        }

        if (frame_of_last_event > 0 && frame_of_behaving == frame_of_last_event + 60*60) {
            if (pBgm->isReady(0)) {
                //BGM���t�F�[�h�A�E�g
                pBgm->fadeoutStop(0, 120);
            }
            //�V�[���I���̃C�x���g��ʒm
            this->throwEventUpperTree(event_part_finish_);
        }
    }


    virtual ~Stage01Part() {

    }
};

}
#endif /*STAGE_H_*/
