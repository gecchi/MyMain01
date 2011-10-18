#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

bool RankUpScene::_pause = false;

RankUpScene::RankUpScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpScene";
    useProgress(RANKUPSCENE_PROG_END);
}

void RankUpScene::initialize() {
    _pProg->set(RANKUPSCENE_PROG_INIT);
}
void RankUpScene::processBehavior() {

    switch (_pProg->get()) {
        case RANKUPSCENE_PROG_INIT: {
            _pProg->change(RANKUPSCENE_PROG_BEGIN);
            break;
        }
        case RANKUPSCENE_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUpScene::processBehavior() ["<<getName()<<"] RANKUPSCENE_PROG_BEGIN !");
                _pMessage->update(Px2Co(500), Px2Co(500), "RANKUPSCENE_PROG_BEGIN");
            }

            if (_pProg->getFrameInProgress() == 180) { //�X�e�[�W�J�n�I
                _pProg->change(RANKUPSCENE_PROG_PLAYING);
            }
            break;
        }
        case RANKUPSCENE_PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                P_RANK_UP_CONTROLLER->slowdown(this); //�X���[�_�E��
                _pMessage->update("RANKUPSCENE_PROG_PLAYING");
                _TRACE_("RankUpScene::processBehavior() ["<<getName()<<"] RANKUPSCENE_PROG_BEGIN !");
            }
            //�p�������N���X��RANKUPSCENE_PROG_RESULT�֐i���X�V�҂��C�x���g�҂�
            break;
        }
        case RANKUPSCENE_PROG_RESULT: {
            if (_pProg->isJustChanged()) {
                _pMessage->update("RANKUPSCENE_PROG_RESULT");
                _TRACE_("RankUpScene::processBehavior() ["<<getName()<<"] RANKUPSCENE_PROG_RESULT !");
            }

            //���ʕ\���H
            if (_pProg->getFrameInProgress() == 180) {
                _pMessage->update("KEKKA HAPYOU!!!");
            }
            break;
        }
        case RANKUPSCENE_PROG_END: {
            if (_pProg->isJustChanged()) {
                P_RANK_UP_CONTROLLER->slowRelease(this); //�X���[��
                _TRACE_("RankUp001::processBehavior()  RANKUPSCENE_PROG_END�ɂȂ�܂����I");
                _pMessage->update("RANKUPSCENE_PROG_END");
            }

            if (_pProg->getFrameInProgress() == 180) {
                _pMessage->update("BYBY!");
            }

            break;
        }
        default:
            break;

    }

}

void RankUpScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}
void RankUpScene::processFinal() {
}

//
//void RankUpScene::initialize() {
//}
//
//
//void RankUpScene::processJudgement() {
//}
//
//void RankUpScene::processFinal() {
//    //�ꎞ��~
//    if (VB->isPushedDown(VB_UI_CANCEL)) {
//        if (_pause) {
//            pauseTree();
//        } else {
//            unpauseTree();
//        }
//    }
//}

RankUpScene::~RankUpScene() {
}
