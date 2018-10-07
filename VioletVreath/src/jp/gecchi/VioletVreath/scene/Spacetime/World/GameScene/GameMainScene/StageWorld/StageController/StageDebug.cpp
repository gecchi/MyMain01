#include "StageDebug.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/core/util/CmRandomNumberGenerator.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi001.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBound001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageController.h"
#include "StageDebug/StageDebugPartController.h"


#include "jp/ggaf/core/util/GgafUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

StageDebug::StageDebug(const char* prm_name) : Stage(prm_name) {
    _class_name = "StageDebug";

    pScene_StagePartCtrler_ = NEW StageDebugPartController("StageDebugPartController");
    pScene_StagePartCtrler_->inactivate();
    addSubLast(pScene_StagePartCtrler_);
    Sleep(2);
    pWorldBound_  = NEW WorldBound001("BG_SPACE");
    bringSceneMediator()->addSubGroup(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    bringSceneMediator()->addSubGroup(pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("StageDebugMsg");
    bringSceneMediator()->addSubGroup(pMessage_);
    pMessage_->inactivate();


    pPlanet_ = NEW Planet001("Planet001");
    bringSceneMediator()->addSubGroup(KIND_EFFECT, pPlanet_);
//    pHorizon_ = NEW Horizon001("Horizon001");
//    bringSceneMediator()->addSubGroup(KIND_CHIKEI, pHorizon_);

    //debug ---->
//    EnemyHisbe* pTest = NEW EnemyHisbe("tst");
//    pTest->setPosition(PX_C(0),PX_C(0), PX_C(100));
//    pTest->setFaceAngTwd(PX_C(100), PX_C(100), PX_C(100));
//    pTest->getKuroko()->behave();
//    bringSceneMediator()->addSubGroup(pTest);
    //<-----debug

    fadeoutSceneWithBgm(0); //�ŏ��͔�\��
}

void StageDebug::initialize() {
    Stage::initialize();
}

void StageDebug::processBehavior() {
    Stage::processBehavior();
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case Stage::PROG_INIT: {
            pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (pProg->hasArrivedAt(180)) { //�X�e�[�W�P�J�n�I
                pMessage_->activateImmed();
                pWorldBound_->activateTree();    //�w�iON
                pHoshiBoshi_->activateTree();    //�w�iON
                pScene_StagePartCtrler_->activate();

                pPlanet_->activate();

                fadeinScene(360);
                pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (pProg->hasArrivedAt(60)) { //�X�e�[�W�P�J�n�I
                pMessage_->update(PX_C(300), PX_C(300), "SCENE DEBUG START!");
                pMessage_->inactivateDelay(240);
            }
            //EVENT_STAGEDEBUG_PART_CTRLER_WAS_END�C�x���g�҂�
            break;
        }
        case Stage::PROG_END: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<"  Stage::PROG_END�ɂȂ�܂����I");
                throwEventUpperTree(EVENT_PREPARE_TRANSIT_STAGE); //�ʉ߃X�e�[�W������
            }

            if (pProg->hasArrivedAt(60)) {
                pMessage_->activateImmed();
                pMessage_->update(PX_C(300), PX_C(300), "SCENE DEBUG CLEAR!!");
                pMessage_->inactivateDelay(120);
                fadeoutSceneWithBgm(300);
            }
            if (pProg->hasArrivedAt(300)) {
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
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STAGEDEBUG_PART_CTRLER_WAS_END ) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CTRLER_WAS_END ���L���b�`�B�X�e�[�^�X��Stage::PROG_END��");
        pScene_StagePartCtrler_->sayonara(60*60);
        pProg->change(Stage::PROG_END);
    } else {

    }
}


StageDebug::~StageDebug() {

}