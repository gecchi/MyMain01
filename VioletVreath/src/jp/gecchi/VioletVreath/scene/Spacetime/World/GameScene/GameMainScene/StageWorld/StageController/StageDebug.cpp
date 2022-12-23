#include "StageDebug.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/util/CmRandomNumberGenerator.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi001.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBound001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageController.h"
#include "StageDebug/StageDebugPartController.h"


#include "jp/ggaf/core/util/Util.h"



using namespace GgafLib;
using namespace VioletVreath;

StageDebug::StageDebug(const char* prm_name) : Stage(prm_name) {
    _class_name = "StageDebug";

    pScene_StagePartCtrler_ = NEW StageDebugPartController("StageDebugPartController");
    pScene_StagePartCtrler_->inactivate();
    appendChild(pScene_StagePartCtrler_);
    Sleep(2);
    pWorldBound_  = NEW WorldBound001("BG_SPACE");
    bringSceneMediator()->appendGroupChild(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    bringSceneMediator()->appendGroupChild(pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("StageDebugMsg");
    bringSceneMediator()->appendGroupChild(pMessage_);
    pMessage_->inactivate();


    pPlanet_ = NEW Planet001("Planet001");
    bringSceneMediator()->appendGroupChild(KIND_EFFECT, pPlanet_);
//    pHorizon_ = NEW Horizon001("Horizon001");
//    bringSceneMediator()->appendGroupChild(KIND_CHIKEI, pHorizon_);

    //debug ---->
//    EnemyHisbe* pTest = NEW EnemyHisbe("tst");
//    pTest->setPosition(PX_C(0),PX_C(0), PX_C(100));
//    pTest->setFaceAngTwd(PX_C(100), PX_C(100), PX_C(100));
//    pTest->getVecVehicle()->behave();
//    bringSceneMediator()->appendGroupChild(pTest);
    //<-----debug

    fadeoutSceneWithBgm(0); //�ŏ��͔�\��
}

void StageDebug::initialize() {
    Stage::initialize();
}

void StageDebug::processBehavior() {
    Stage::processBehavior();
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case Stage::PHASE_INIT: {
            pPhase->change(Stage::PHASE_BEGIN);
            break;
        }
        case Stage::PHASE_BEGIN: {
            if (pPhase->hasArrivedFrameAt(180)) { //�X�e�[�W�P�J�n�I
                pMessage_->activateImmed();
                pWorldBound_->activateTree();    //�w�iON
                pHoshiBoshi_->activateTree();    //�w�iON
                pScene_StagePartCtrler_->activate();

                pPlanet_->activate();

                fadeinScene(360);
                pPhase->change(Stage::PHASE_PLAYING);
            }
            break;
        }
        case Stage::PHASE_PLAYING: {
            if (pPhase->hasArrivedFrameAt(60)) { //�X�e�[�W�P�J�n�I
                pMessage_->update(PX_C(300), PX_C(300), "SCENE DEBUG START!");
                pMessage_->inactivateDelay(240);
            }
            //EVENT_STAGEDEBUG_PART_CTRLER_WAS_END�C�x���g�҂�
            break;
        }
        case Stage::PHASE_END: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<"  Stage::PHASE_END�ɂȂ�܂����I");
                throwEventUpperTree(EVENT_PREPARE_TRANSIT_STAGE); //�ʉ߃X�e�[�W������
            }

            if (pPhase->hasArrivedFrameAt(60)) {
                pMessage_->activateImmed();
                pMessage_->update(PX_C(300), PX_C(300), "SCENE DEBUG CLEAR!!");
                pMessage_->inactivateDelay(120);
                fadeoutSceneWithBgm(300);
            }
            if (pPhase->hasArrivedFrameAt(300)) {
                throwEventUpperTree(EVENT_STAGEDEBUG_WAS_FINISHED);
            }
            break;
        }
        default: {
            break;
        }
    }

}

void StageDebug::processJudgement() {
}

void StageDebug::onCatchEvent(hashval prm_no, void* prm_pSource) {
    ScenePhase* pPhase = getPhase();
    if (prm_no == EVENT_STAGEDEBUG_PART_CTRLER_WAS_END ) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CTRLER_WAS_END ���L���b�`�B�X�e�[�^�X��Stage::PHASE_END��");
        pScene_StagePartCtrler_->sayonara(SEC_F(60));
        pPhase->change(Stage::PHASE_END);
    } else {

    }
}


StageDebug::~StageDebug() {

}
