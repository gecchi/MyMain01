#ifndef STAGECONTROLLER_H_
#define STAGECONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../StageWorld.h"
#include "../StageWorld/StageController/Stage.h"
#include "../StageWorld/StageController/TransitStage.h"

#ifdef pSTAGE_WORLD
    #define pSTAGE_CTRLER (pSTAGE_WORLD->pStageCtrler_)
#else
    #error pSTAGE_WORLD isnt define
#endif
DECLARE_EVENT_VAL(EVENT_STAGEDEBUG_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE01_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE02_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE03_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE04_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE05_WAS_FINISHED);

DECLARE_EVENT_VAL(EVENT_TRANSIT_WAS_END);

namespace VioletVreath {

/**
 * �Q�[�����C���V�[���̃R���g���[���[ .
 * ��Ȏd���̓��C���X�e�[�W�̐؂�ւ��A
 * �����N�A�b�v�V�[���̍����ł��B
 * @version 1.00
 * @since 2011/07/17
 * @author Masatoshi Tsuge
 */
class StageController : public VvScene<GgafLib::DefaultScene> {

public:
    char buf_[60];
    /** ���C���X�e�[�W(���݃A�N�e�B�u�Ȗʂ̃V�[���|�C���^�j */
    Stage* pStageMainCannel_;
    /** �ʉ߃X�e�[�W�V�[�� */
    TransitStage* pTransitStage_;

    LabelSceneSymbol* _pSceneSymbol;

    int loop_;
    int main_stage_;

public:
    StageController(const char* prm_name);

    void onReset() override;
    void readyStage(int prm_main_stage);
    void initialize() override;
    void processBehavior() override;
    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~StageController();

};

}
#endif /*STAGECONTROLLER_H_*/
