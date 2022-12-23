#ifndef STAGEDEBUGPART_H_
#define STAGEDEBUGPART_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "../StageDebugPartController.h"
namespace VioletVreath {

/**
 * ステージデバッグパート基底 .
 * @version 1.00
 * @since 2018/09/19
 * @author Masatoshi Tsuge
 */
template<class T>
class StageDebugPart :  public VvScene<T> {

public:
    enum {
        PHASE_INIT    ,
        PHASE_BEGIN   ,
        PHASE_PLAYING ,
        PHASE_END     ,
        PHASE_BANPEI,
    };

    hashval event_part_finish_;
    frame frame_of_last_event_;
    frame last_event_delay_frames_;
public:
    StageDebugPart(const char* prm_name, hashval prm_event_part_finish = 0): VvScene<T>(prm_name, nullptr) {
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
                StageDebugPartController* pStagePartController = (StageDebugPartController*)(this->getParent());
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


    virtual ~StageDebugPart() {

    }
};

}
#endif /*STAGEDEBUGPART_H_*/
