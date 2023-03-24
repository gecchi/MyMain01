#ifndef STAGE01PART_H_
#define STAGE01PART_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "../Stage01PartController.h"
namespace VioletVreath {

/**
 * ステージデバッグパート基底 .
 * @version 1.00
 * @since 2018/09/19
 * @author Masatoshi Tsuge
 */
template<class T>
class Stage01Part :  public VvScene<T> {

public:
    enum {
        PHASE_INIT    ,
        PHASE_BEGIN   ,
        PHASE_PLAYING ,
        PHASE_END     ,
        PHASE_BANPEI,
    };

    eventval event_part_finish_;
    frame frame_of_last_event_;
    frame last_event_delay_frames_;
public:
    Stage01Part(const char* prm_name, eventval prm_event_part_finish = 0): VvScene<T>(prm_name, nullptr) {
        event_part_finish_ = prm_event_part_finish;
        last_event_delay_frames_ = SEC_F(60);
        frame_of_last_event_ = MAX_FRAME - last_event_delay_frames_;
    }

    virtual void processJudgement() override {
        frame frame_of_behaving = this->getBehaveingFrame();
        frame frame_of_last_event = this->getLastEventFrame();
        GgafDx::BgmConductor* pBgm = this->getBgmConductor();

        if (frame_of_behaving == 1) {
            if (pBgm->isReady(0)) {
                //兄弟シーンのBGMを全てフェードアウト
                Stage01PartController* pStagePartController = (Stage01PartController*)(this->getParent());
                pStagePartController->fadeoutBgmTree(300);
                //自分のシーンBGMを演奏開始！
                pBgm->performFromTheBegining(0);
            }
            frame_of_last_event_ = this->getLastEventFrame();
        }

        if (frame_of_last_event > 0 && frame_of_behaving == frame_of_last_event_ + last_event_delay_frames_) {
            if (pBgm->isReady(0)) {
                //BGMをフェードアウト
                pBgm->fadeoutStop(0, SEC_F(2));
            }
            //シーン終了のイベントを通知
            this->throwEventUpperTree(event_part_finish_);
        }
    }


    virtual ~Stage01Part() {

    }
};

}
#endif /*STAGE_H_*/
