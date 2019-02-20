#include "RankUpStageController.h"

#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp001.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp002.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp003.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp100.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/manager/SeConnection.h"



using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_RANKUP (80)

enum {
    PROG_INIT  ,
    PROG_PLAY  ,
    PROG_FINISH,
    PROG_BANPEI,
};

RankUpStageController::RankUpStageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpStageController";
    _TRACE_("RankUpStageController::RankUpStageController("<<prm_name<<")");

    for (int i = 0; i < MAX_RANKUP_SCENE; i ++) {
        apRankUpStage_[i] = nullptr;
    }

    pSeConn_RankUpStageExec_ = connectToSeManager("WAVE_RANK_UP_STAGE_EXEC");
    ready(G_RANKUP_LEVEL + 1);
}
void RankUpStageController::startRunkUpStage(int prm_rank_up_level) {
    pSeConn_RankUpStageExec_->peek()->play(); //�����N�A�b�v�X�e�[�W�J�nSE�I
    ready(prm_rank_up_level);     //����̓p�X�����͂��ł��邪�A�O�̂��߁B
    ready(prm_rank_up_level + 1); //���̃V�[�����s�\��
    pNowRankUpStage_ = (RankUpStage*)receiveScene(ORDER_ID_RANKUP+prm_rank_up_level);
    _TRACE_(FUNC_NAME<<" pNowRankUpStage_="<<pNowRankUpStage_);
    GgafCore::Scene* pRankUpStage = getChildFirst();
    if (pRankUpStage) {
        //���̃����N�A�b�v��
        //���������N�A�b�v�V�[��������ɃX���[�ɂ���
        while (1) {
            pRankUpStage->addRunFrameOnce(SLOW_FRAME_RANKUP);
            if (pRankUpStage->isLast()) {
                break;
            } else {
                pRankUpStage = pRankUpStage->getNext();
            }
        }
    }
    appendChild(pNowRankUpStage_);
    pNowRankUpStage_->fadeoutSceneWithBgm(0);
    pNowRankUpStage_->fadeinScene(240);
    apRankUpStage_[prm_rank_up_level-1] = pNowRankUpStage_;
    //�X���[�_�E��
}

void RankUpStageController::onReset() {
    getProgress()->reset(PROG_INIT);
}

void RankUpStageController::ready(int prm_rank_up_level) {
    switch (prm_rank_up_level) {
        case 1:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp001);
            break;
        case 2:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp002);
            break;
        case 3:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp003);
            break;
//        case 100:
//            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100);
//            break;
        default:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100);
            break;
    }
}

void RankUpStageController::initialize() {
    getProgress()->reset(PROG_INIT);
}

void RankUpStageController::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }

        case PROG_PLAY: {
            if (pProg->hasJustChanged()) {
            }
            break;
        }

        case PROG_FINISH: {
            if (pProg->hasJustChanged()) {
            }
            break;
        }

        default:
            break;
    }

}
void RankUpStageController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_RANKUP_WAS_END) {
        _TRACE_(FUNC_NAME<<" EVENT_RANKUP_WAS_END prm_pSource="<<prm_pSource);
        RankUpStage* pScene = (RankUpStage*)prm_pSource; //�I���錾����RankUpStage
        pScene->fadeoutSceneWithBgm(240);
        pScene->sayonara(240);

        //�X���[��
        GgafCore::Scene* pRankUpStage = getChildFirst();
        if (pRankUpStage) {
            //���̃����N�A�b�v��
            //���������N�A�b�v�V�[�����X���[��
            while (1) {
                if (pRankUpStage == pScene) {
                    break;
                } else {
                    pRankUpStage->addRunFrameOnce(-SLOW_FRAME_RANKUP); //�X���[��
                    _TRACE_("pRankUpStage="<<pRankUpStage->getName()<<"���X���[��");
                    pRankUpStage = pRankUpStage->getNext();
                }
            }
        } else {
            throwCriticalException("EVENT_RANKUP_WAS_END �q��nullptr�B"
                                       "this="<<NODE_INFO<<" prm_pSource="<<prm_pSource);
        }
    }
}

void RankUpStageController::sayonaraRankUpStages() {
    if (getChildFirst()) {
        GgafCore::Scene* pRankUpStage = getChildFirst()->getPrev();//last
        if (pRankUpStage) {
            while (1) {
                _TRACE_(FUNC_NAME<<" pRankUpStage("<<pRankUpStage->getName()<<")->sayonara()");
                pRankUpStage->sayonara();
                if (pRankUpStage == getChildFirst()) {
                    break;
                } else {
                    pRankUpStage = pRankUpStage->getPrev();
                }
            }
        }
    }
}

RankUpStageController::~RankUpStageController() {
    pSeConn_RankUpStageExec_->close();
}

