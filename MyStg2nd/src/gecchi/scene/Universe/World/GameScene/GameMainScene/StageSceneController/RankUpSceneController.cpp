#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    RANKUPCONTROLLER_PROG_INIT = 1,
    RANKUPCONTROLLER_PROG_PLAY    ,
    RANKUPCONTROLLER_PROG_FINISH  ,
};
#define ORDER_ID_RANKUP 80

RankUpSceneController::RankUpSceneController(const char* prm_name) : StageScene(prm_name) {
    _class_name = "RankUpSceneController";
    _TRACE_("RankUpSceneController::RankUpSceneController("<<prm_name<<")");
    useProgress(RANKUPCONTROLLER_PROG_FINISH);
    readyStage(_RANK_LEVEL_ + 1);
}
void RankUpSceneController::execute() {
    readyStage(_RANK_LEVEL_ + 1); //���̃V�[�����s�\��
    _pLastRankUpScene = (RankUpScene*)obtainSceneFromFactory(ORDER_ID_RANKUP+_RANK_LEVEL_);
    _pLastRankUpScene->fadeoutScene(0);
    addSubLast(_pLastRankUpScene);
    _pLastRankUpScene->fadeinSceneTree(180);

    //�X���[�_�E��

}
void RankUpSceneController::slowdown(RankUpScene* prm_pLastAdded) {
    //�X���[�_�E��
    if (getSubFirst()) {
        //����
        P_STAGE_CONTROLLER->setRunFrameOnceTree(2);
    } else {
        //�A�`����
        P_STAGE_CONTROLLER->setRunFrameOnceTree(P_STAGE_CONTROLLER->_n_once*2);
        RankUpScene* pRankUpScene = (RankUpScene*)_pSubFirst;
        while(true) {
            pRankUpScene->setRunFrameOnceTree(pRankUpScene->_n_once*2);
            if (pRankUpScene == prm_pLastAdded) {
                //�ǉ������ẴV�[���͓���
                break;
            } else {
                pRankUpScene = (RankUpScene*)(pRankUpScene->_pNext);
            }
        }
    }
}

void RankUpSceneController::slowRelease(RankUpScene* prm_pInactive) {
    RankUpScene* pRankUpScene = prm_pInactive;
    while(true) {
        pRankUpScene->setRunFrameOnceTree(pRankUpScene->_n_once/2);
        if (pRankUpScene->_is_first_flg) {
            //�ǉ������ẴV�[���͓���
            ((RankUpScene*)(pRankUpScene->_pPrev))->setRunFrameOnceTree(pRankUpScene->_n_once/2);
            break;
        } else {
            pRankUpScene = (RankUpScene*)(pRankUpScene->_pPrev);
        }
    }
    P_STAGE_CONTROLLER->setRunFrameOnceTree(P_STAGE_CONTROLLER->_n_once/2);
}
void RankUpSceneController::onReset() {
    _pProg->set(RANKUPCONTROLLER_PROG_INIT);
}

void RankUpSceneController::readyStage(int prm_rank_level) {
    switch (prm_rank_level) {
        case 1:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp001, "RankUp001");
            break;
//        case 2:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage02, "Stage02");
//            break;
//        case 3:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage03, "Stage03");
//            break;
//        case 4:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage04, "Stage04");
//            break;
//        case 5:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage05, "Stage05");
//            break;
        default:
            break;
    }
}

void RankUpSceneController::initialize() {
}

void RankUpSceneController::processBehavior() {
    switch (_pProg->get()) {
        case RANKUPCONTROLLER_PROG_INIT: {
            _pProg->change(RANKUPCONTROLLER_PROG_PLAY);
            break;
        }


        case RANKUPCONTROLLER_PROG_PLAY: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        case RANKUPCONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        default:
            break;
    }

}
void RankUpSceneController::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
//    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
//        //���̃X�e�[�W���H��ɒ������Ă�����Ƃ����C�x���g
//        _TRACE_("RankUpSceneController::onCatchEvent() EVENT_PREPARE_NEXT_STAGE ��������");
//        if (_rank <= 5) {
//            readyStage(_rank+1);
//        } else {
////            _TRACE_("�ŏI�ʃN���A");
////            _pProg->change(RANKUPCONTROLLER_PROG_END);
//            //TODO:�G�f�j���O�H
//        }
//    }
//
//    if (prm_no == EVENT_STG01_WAS_END) {
//        _TRACE_("RankUpSceneController::onCatchEvent() EVENT_STG01_WAS_END");
//        _pRankUpSceneMainCannel->end(60*60);
//        _pProg->change(RANKUPCONTROLLER_PROG_FINISH);
//    }
//    if (prm_no == EVENT_STG02_WAS_END) {
//        _TRACE_("RankUpSceneController::onCatchEvent() EVENT_STG01_WAS_END");
//        _pRankUpSceneMainCannel->end(60*60);
//        _pProg->change(RANKUPCONTROLLER_PROG_FINISH);
//    }


}
void RankUpSceneController::processFinal() {
}

RankUpSceneController::~RankUpSceneController() {
}

