#include "StageController.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "StageController/StageDebug.h"
#include "StageController/StageDebug/StageDebugPartController.h"
#include "StageController/Stage01.h"
#include "StageController/Stage01/Stage01PartController.h"
#include "StageController/Stage02.h"
#include "StageController/Stage02/Stage02PartController.h"
#include "StageController/Stage03.h"
#include "StageController/Stage04.h"
#include "StageController/Stage05.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_STAGE 11

enum {
    PHASE_INIT        ,
    PHASE_BEGIN       ,
    PHASE_PLAY_STAGE  ,
    PHASE_PLAY_TRANSIT,
    PHASE_PLAY_RANKUP ,
    PHASE_FINISH      ,
    PHASE_BANPEI,
};

StageController::StageController(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "StageController";

    _TRACE_("StageController::StageController("<<prm_name<<")");
//    had_ready_main_stage_ = false;
    loop_ = 1;
    main_stage_ = 0; //stage0�̓f�o�b�O
    pStageMainCannel_ = nullptr;

    pTransitStage_ = NEW TransitStage("TransitStage");
    pTransitStage_->inactivate();
    appendChild(pTransitStage_);

    _pSceneSymbol = NEW LabelSceneSymbol("LabelSceneSymbol");
    getSceneChief()->appendChild(_pSceneSymbol);
}

void StageController::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    loop_ = 1;
    main_stage_ = 0; //stage0�̓f�o�b�O
    if (pStageMainCannel_) {
        pStageMainCannel_->inactivate();
    }
    //���ʃV�[���A���@�V�[����z���Ɉ��������Ă���
    pCOMMON_SCENE->resetTree();
    pCOMMON_SCENE->activateImmed();
    appendChild(pCOMMON_SCENE->extract());
    getPhase()->reset(PHASE_INIT);
}
//void StageController::readyNextStage() {
//    main_stage_++;
//    readyStage(main_stage_);
//}


void StageController::readyStage(int prm_main_stage) {
    _TRACE_("StageController::readyStage("<<prm_main_stage<<")");
    //�ő僉���N�𒲐��A����ɂ���ĕω��BTODO:��Փx���x���Ƃ��� G_MIN_RANK ��グ�Ƃ�
    G_MAX_RANK = 1.0 + ((loop_-1) * 0.2);


    switch (prm_main_stage) {
        case 0:
            requestScene(ORDER_ID_STAGE+prm_main_stage, StageDebug);
            break;
        case 1:
            requestScene(ORDER_ID_STAGE+prm_main_stage, Stage01);
            break;
        case 2:
            requestScene(ORDER_ID_STAGE+prm_main_stage, Stage02);
            break;
        case 3:
            requestScene(ORDER_ID_STAGE+prm_main_stage, Stage03);
            break;
        case 4:
            requestScene(ORDER_ID_STAGE+prm_main_stage, Stage04);
            break;
        case 5:
            requestScene(ORDER_ID_STAGE+prm_main_stage, Stage05);
            break;
        default:
            break;
    }
}

void StageController::initialize() {
}

void StageController::processBehavior() {
    //SCORE�\��
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            _TRACE_(FUNC_NAME<<" Phase is PHASE_INIT");

            readyStage(main_stage_);
            pPhase->change(PHASE_BEGIN);
            break;
        }

        case PHASE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed to PHASE_BEGIN");
                _TRACE_(FUNC_NAME<<" main_stage_="<<main_stage_);
            }
            if (pPhase->hasArrivedFrameAt(120)) { //�Q�b�V��
                pPhase->change(PHASE_PLAY_STAGE);
            }
            break;
        }

        case PHASE_PLAY_STAGE: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed to PHASE_PLAY_STAGE");
                _TRACE_(FUNC_NAME<<" main_stage_="<<main_stage_);
                readyStage(main_stage_); //�O�̂��߂ɌĂԁB�ʏ�͂��������ł��Ă���n�Y�B
                //�X�e�[�W�V�[���ǉ�
                if (pStageMainCannel_) {
                    _TRACE_("�����̂��I PHASE_PLAY_STAGE: �� pStageMainCannel_="<<pStageMainCannel_->getName()<<"");
                }
                pStageMainCannel_ = (Stage*)receiveScene(ORDER_ID_STAGE+main_stage_);
                _TRACE_("PHASE_PLAY_STAGE: �V pStageMainCannel_="<<pStageMainCannel_->getName()<<"");
                pStageMainCannel_->fadeoutSceneWithBgm(0);

                appendChild(pStageMainCannel_);
                pStageMainCannel_->fadeinScene(180);
            }
            break;
        }

        case PHASE_PLAY_TRANSIT: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed to PHASE_PLAY_TRANSIT");
                _TRACE_(FUNC_NAME<<" main_stage_="<<main_stage_);
                pTransitStage_->fadeoutSceneWithBgmTree(0);
                _TRACE_(FUNC_NAME<<" pTransitStage_->setStage("<<main_stage_<<")");
                pTransitStage_->setStage(main_stage_);
                pTransitStage_->reset();
                pTransitStage_->activate();
                pTransitStage_->fadeinScene(180);
            }
            //EVENT_TRANSIT_WAS_END�C�x���g�҂�
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed to PHASE_FINISH");
                _TRACE_(FUNC_NAME<<" main_stage_="<<main_stage_);
                main_stage_ = pTransitStage_->next_main_stage_; //���̃X�e�[�W
                _TRACE_(FUNC_NAME<<" main_stage_ = pTransitStage_->next_main_stage_;");
                _TRACE_(FUNC_NAME<<" �X�V���ꂽ main_stage_="<<main_stage_);
                pPhase->change(PHASE_BEGIN); //���[�v
            }
            break;
        }

        default: {
            break;
        }
    }


/*
    //�����N�A�b�v�V�[����������
    if (G_RANK_DISP % 10 == 0) {
        if (can_rank_up_) {
            can_rank_up_ = false;
            G_RANKUP_LEVEL++;
            pRankUpStageCtrler_->execute();
        } else {
            //�X���[
        }
    } else {
        can_rank_up_ = false;
    }
*/
//    _non_rtti_object_
//    http://msdn.microsoft.com/en-us/library/cby9kycs.aspx

}
void StageController::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    if (prm_event_val == EVENT_PREPARE_TRANSIT_STAGE) {
        _TRACE_("StageController::onCatchEvent(EVENT_PREPARE_TRANSIT_STAGE)");
        pTransitStage_->ready(main_stage_);
    }

    if (prm_event_val == EVENT_PREPARE_NEXT_STAGE) {
        _TRACE_("StageController::onCatchEvent(EVENT_PREPARE_NEXT_STAGE)");
        int next_stage = *((int*)(prm_pSource));
        readyStage(next_stage);//���̃X�e�[�W����
//            _TRACE_("�ŏI�ʃN���A");
//            pPhase->change(PHASE_END);
            //TODO:�G�f�j���O�H
//        }
    }
    ScenePhase* pPhase = getPhase();
    if (prm_event_val == EVENT_STAGEDEBUG_WAS_FINISHED) {
        _TRACE_("StageController::onCatchEvent(EVENT_STAGEDEBUG_WAS_FINISHED)");
        pStageMainCannel_->sayonara(SEC_F(3));
        pStageMainCannel_->fadeoutSceneWithBgmTree(SEC_F(3));
        pPhase->change(PHASE_PLAY_TRANSIT);
    }

    if (prm_event_val == EVENT_STAGE01_WAS_FINISHED) {
        _TRACE_("StageController::onCatchEvent(EVENT_STAGE01_WAS_FINISHED)");
        pStageMainCannel_->sayonara(SEC_F(3));
        pStageMainCannel_->fadeoutSceneWithBgmTree(SEC_F(3));
        pPhase->change(PHASE_PLAY_TRANSIT);
    }
    if (prm_event_val == EVENT_STAGE02_WAS_FINISHED) {
        _TRACE_("StageController::onCatchEvent(EVENT_STAGE02_WAS_FINISHED)");
        pStageMainCannel_->sayonara(SEC_F(3));
        pStageMainCannel_->fadeoutSceneWithBgmTree(SEC_F(3));
        pPhase->change(PHASE_PLAY_TRANSIT);
    }
    if (prm_event_val == EVENT_TRANSIT_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_TRANSIT_WAS_END)");
        pTransitStage_->inactivateDelay(SEC_F(3));
        pTransitStage_->fadeoutSceneWithBgmTree(SEC_F(3));
        pPhase->change(PHASE_FINISH);
    }

}

StageController::~StageController() {
}

