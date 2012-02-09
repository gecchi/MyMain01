#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


#define ORDER_ID_STAGE 11

StageController::StageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageController";

    _TRACE_("StageController::StageController("<<prm_name<<")");
//    _had_ready_main_stage = false;
    _loop = 1;
    _main_stage = 1;
    _pStageMainCannel = NULL;

    _pTransitStage = NEW TransitStage("TransitStage");
    _pTransitStage->inactivateImmed();
    addSubLast(_pTransitStage);

    useProgress(StageController::PROG_FINISH);
}

void StageController::onReset() {
    _TRACE_("StageController::onReset()");
    if (_pStageMainCannel) {
        _pStageMainCannel->inactivate();
    }
    //���ʃV�[���A���@�V�[����z���Ɉ��������Ă���
    P_COMMON_SCENE->resetTree();
    P_COMMON_SCENE->activateImmed();
    addSubLast(P_COMMON_SCENE->extract());
    _pProg->set(StageController::PROG_INIT);
}
//void StageController::readyNextStage() {
//    _main_stage++;
//    readyStage(_main_stage);
//}


void StageController::readyStage(int prm_main_stage) {
    _TRACE_("StageController::readyStage("<<prm_main_stage<<")");
    switch (prm_main_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage01, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage02, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage03, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage04, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage05, "Stage05");
            break;
        default:
            break;
    }
}

void StageController::initialize() {
}

void StageController::processBehavior() {
    //SCORE�\��
    switch (_pProg->get()) {
        case StageController::PROG_INIT: {
            readyStage(_main_stage);
            _pProg->change(StageController::PROG_BEGIN);
            break;
        }

        case StageController::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_BEGIN) is Just Changed");
            }

            if (_pProg->getFrameInProgress() == 120) { //�Q�b�V��
                _pProg->change(StageController::PROG_PLAY_STAGE);
            }
            break;
        }

        case StageController::PROG_PLAY_STAGE: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_PLAY_STAGE) is Just Changed. _main_stage="<<_main_stage);
                readyStage(_main_stage); //�O�̂��߂ɌĂԁB�ʏ�͂��������ł��Ă���n�Y�B
                //�X�e�[�W�V�[���ǉ�
                _pStageMainCannel = (Stage*)obtainSceneFromFactory(ORDER_ID_STAGE+_main_stage);
                _pStageMainCannel->fadeoutScene(0);
                addSubLast(_pStageMainCannel);
                _pStageMainCannel->fadeinSceneTree(180);
            }
            break;
        }

        case StageController::PROG_PLAY_TRANSIT: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_PLAY_TRANSIT) is Just Changed. _main_stage="<<_main_stage);
                _pTransitStage->fadeoutSceneTree(0);
                _TRACE_("StageController::processBehavior() _pTransitStage->setStage("<<_main_stage<<")");
                _pTransitStage->setStage(_main_stage);
                _pTransitStage->reset();
                _pTransitStage->activate();
                _pTransitStage->fadeinSceneTree(180);
            }
            //EVENT_TRANSIT_WAS_END�C�x���g�҂�

            break;
        }


        case StageController::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_FINISH) is Just Changed _pTransitStage->_next_main_stage="<<_pTransitStage->_next_main_stage);
                _main_stage = _pTransitStage->_next_main_stage; //���̃X�e�[�W
                _pProg->change(StageController::PROG_BEGIN); //���[�v
            }
            break;
        }

        default:
            break;
    }


/*
    //�����N�A�b�v�V�[����������
    if (_RANK_DISP_ % 10 == 0) {
        if (_can_rank_up) {
            _can_rank_up = false;
            _RANK_UP_LEVEL_++;
            _pRankUpStageController->execute();
        } else {
            //�X���[
        }
    } else {
        _can_rank_up = false;
    }
*/
//    __non_rtti_object
//    http://msdn.microsoft.com/en-us/library/cby9kycs.aspx

}
void StageController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREPARE_TRANSIT_STAGE) {
        _TRACE_("StageController::onCatchEvent(EVENT_PREPARE_TRANSIT_STAGE)");
        _pTransitStage->ready(_main_stage);
    }

    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        _TRACE_("StageController::onCatchEvent(EVENT_PREPARE_NEXT_STAGE)");
        readyStage(_pTransitStage->_next_main_stage);//���̃X�e�[�W����
//            _TRACE_("�ŏI�ʃN���A");
//            _pProg->change(StageController::PROG_END);
            //TODO:�G�f�j���O�H
//        }
    }

    if (prm_no == EVENT_STG01_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_STG01_WAS_END)");
        _pStageMainCannel->end(180);
        _pStageMainCannel->fadeoutSceneTree(180);
        _pProg->change(StageController::PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_STG02_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_STG02_WAS_END)");
        _pStageMainCannel->end(180);
        _pStageMainCannel->fadeoutSceneTree(180);
        _pProg->change(StageController::PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_TRANSIT_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_TRANSIT_WAS_END)");
        _pTransitStage->inactivateDelay(180);
        _pTransitStage->fadeoutSceneTree(180);
        _pProg->change(StageController::PROG_FINISH);
    }

}

StageController::~StageController() {
}

