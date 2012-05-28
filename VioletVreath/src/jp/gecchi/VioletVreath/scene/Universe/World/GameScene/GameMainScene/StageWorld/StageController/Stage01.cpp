#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01::Stage01(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage01";

    pScene_Stage01PartCtrlr_ = NEW Stage01PartController("Stage01PartController");
    pScene_Stage01PartCtrlr_->inactivate();
    addSubLast(pScene_Stage01PartCtrlr_);
    Sleep(2);
    pWorldBoundSpace_  = NEW WorldBoundSpace001("BG_SPACE");
    getDirector()->addSubGroup(pWorldBoundSpace_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    getDirector()->addSubGroup(pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("Stage01Msg");
    getDirector()->addSubGroup(pMessage_);
    pMessage_->inactivate();


    pPlanet_ = NEW Planet001("Planet001");
    getDirector()->addSubGroup(KIND_EFFECT, pPlanet_);

    fadeoutScene(0); //�ŏ��͔�\��
    useProgress(10);
}

void Stage01::initialize() {
    Stage::initialize();
    CmRandomNumberGenerator::getInstance()->changeSeed(P_MYSHIP->_Y);
}

void Stage01::processBehavior() {
    Stage::processBehavior();

    switch (_pProg->get()) {
        case Stage::PROG_INIT: {
            _pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (_pProg->getFrameInProgress() == 180) { //�X�e�[�W�P�J�n�I
                pMessage_->activateImmed();
                pWorldBoundSpace_->activateTree();    //�w�iON
                pHoshiBoshi_->activateTree();    //�w�iON
                pScene_Stage01PartCtrlr_->activate();

                pPlanet_->activate();

                fadeinSceneTree(360);
                _pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (_pProg->getFrameInProgress() == 60) { //�X�e�[�W�P�J�n�I
                pMessage_->update(PX_C(300), PX_C(300), "SCENE 01 START!");
                pMessage_->inactivateDelay(240);
            }
            //EVENT_STG01_CTRLER_WAS_END�C�x���g�҂�
            break;
        }
        case Stage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01::processBehavior()  Stage::PROG_END�ɂȂ�܂����I");
                throwEventToUpperTree(EVENT_PREPARE_TRANSIT_STAGE, this); //�ʉ߃X�e�[�W������
            }

            if (_pProg->getFrameInProgress() == 60) {
                pMessage_->activateImmed();
                pMessage_->update(PX_C(300), PX_C(300), "SCENE 01 CLEAR!!");
                pMessage_->inactivateDelay(120);
                fadeoutScene(300);
            }
            if (_pProg->getFrameInProgress() == 300) {
                throwEventToUpperTree(EVENT_STG01_WAS_END);
            }


            break;
        }
        default:
            break;

    }

}

void Stage01::processJudgement() {
}

void Stage01::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CTRLER_WAS_END ) {
        _TRACE_("Stage01::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��Stage::PROG_END��");
        pScene_Stage01PartCtrlr_->end(60*60);
        _pProg->change(Stage::PROG_END);
    } else {

    }
}


Stage01::~Stage01() {

}
