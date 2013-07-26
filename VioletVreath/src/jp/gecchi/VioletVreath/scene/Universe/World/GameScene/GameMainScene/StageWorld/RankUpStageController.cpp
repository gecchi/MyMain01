#include "stdafx.h"
#include "RankUpStageController.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp001.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp002.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp003.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp100.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


#define ORDER_ID_RANKUP 80

RankUpStageController::RankUpStageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpStageController";
    _TRACE_("RankUpStageController::RankUpStageController("<<prm_name<<")");

    for (int i = 0; i < MAX_RANKUP_SCENE; i ++) {
        apRankUpStage_[i] = nullptr;
    }

    pSeConn_RankUpStageExec_ = connect_SeManager("WAVE_RANK_UP_STAGE_EXEC");

    useProgress(RankUpStageController::PROG_FINISH);
    ready(G_RANKUP_LEVEL + 1);
}
void RankUpStageController::startRunkUpStage(int prm_rank_up_level) {
    pSeConn_RankUpStageExec_->peek()->play(); //ランクアップステージ開始SE！
    ready(prm_rank_up_level);     //これはパスされるはずであるが、念のため。
    ready(prm_rank_up_level + 1); //次のシーンを先行予約
    pNowRankUpStage_ = (RankUpStage*)obtainSceneFromFactory(ORDER_ID_RANKUP+prm_rank_up_level);
    _TRACE_("RankUpStageController::execute() pNowRankUpStage_="<<pNowRankUpStage_);
    GgafScene* pRankUpStage = getSubFirst();
    if (pRankUpStage) {
        //他のランクアップ中
        //既存ランクアップシーンをスローにする
        while (1) {
            pRankUpStage->addRunFrameOnce(3);
            if (pRankUpStage->isLast()) {
                break;
            } else {
                pRankUpStage = pRankUpStage->getNext();
            }
        }
    }
    addSubLast(pNowRankUpStage_);
    pNowRankUpStage_->fadeoutSceneWithBgm(0);
    pNowRankUpStage_->fadeinSceneTree(240);
    apRankUpStage_[prm_rank_up_level-1] = pNowRankUpStage_;
    //スローダウン
}

void RankUpStageController::onReset() {
    _pProg->reset(RankUpStageController::PROG_INIT);
}

void RankUpStageController::ready(int prm_rank_up_level) {
    switch (prm_rank_up_level) {
        case 1:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp001, "RankUp001");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp002, "RankUp002");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp003, "RankUp003");
            break;
//        case 4:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp004, "RankUp004");
//            break;
//        case 5:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp005, "RankUp005");
//            break;
//        case 6:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp006, "RankUp006");
//            break;
//        case 7:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp007, "RankUp007");
//            break;
//        case 8:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp008, "RankUp008");
//            break;
//        case 9:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp009, "RankUp009");
//            break;
//        case 10:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp010, "RankUp010");
//            break;
//        case 11:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp011, "RankUp011");
//            break;
//        case 12:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp012, "RankUp012");
//            break;
//        case 13:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp013, "RankUp013");
//            break;
//        case 14:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp014, "RankUp014");
//            break;
//        case 15:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp015, "RankUp015");
//            break;
//        case 16:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp016, "RankUp016");
//            break;
//        case 17:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp017, "RankUp017");
//            break;
//        case 18:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp018, "RankUp018");
//            break;
//        case 19:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp019, "RankUp019");
//            break;
//        case 20:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp020, "RankUp020");
//            break;
//        case 21:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp021, "RankUp021");
//            break;
//        case 22:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp022, "RankUp022");
//            break;
//        case 23:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp023, "RankUp023");
//            break;
//        case 24:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp024, "RankUp024");
//            break;
//        case 25:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp025, "RankUp025");
//            break;
//        case 26:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp026, "RankUp026");
//            break;
//        case 27:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp027, "RankUp027");
//            break;
//        case 28:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp028, "RankUp028");
//            break;
//        case 29:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp029, "RankUp029");
//            break;
//        case 30:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp030, "RankUp030");
//            break;
//        case 31:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp031, "RankUp031");
//            break;
//        case 32:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp032, "RankUp032");
//            break;
//        case 33:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp033, "RankUp033");
//            break;
//        case 34:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp034, "RankUp034");
//            break;
//        case 35:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp035, "RankUp035");
//            break;
//        case 36:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp036, "RankUp036");
//            break;
//        case 37:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp037, "RankUp037");
//            break;
//        case 38:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp038, "RankUp038");
//            break;
//        case 39:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp039, "RankUp039");
//            break;
//        case 40:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp040, "RankUp040");
//            break;
//        case 41:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp041, "RankUp041");
//            break;
//        case 42:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp042, "RankUp042");
//            break;
//        case 43:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp043, "RankUp043");
//            break;
//        case 44:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp044, "RankUp044");
//            break;
//        case 45:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp045, "RankUp045");
//            break;
//        case 46:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp046, "RankUp046");
//            break;
//        case 47:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp047, "RankUp047");
//            break;
//        case 48:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp048, "RankUp048");
//            break;
//        case 49:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp049, "RankUp049");
//            break;
//        case 50:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp050, "RankUp050");
//            break;
//        case 51:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp051, "RankUp051");
//            break;
//        case 52:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp052, "RankUp052");
//            break;
//        case 53:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp053, "RankUp053");
//            break;
//        case 54:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp054, "RankUp054");
//            break;
//        case 55:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp055, "RankUp055");
//            break;
//        case 56:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp056, "RankUp056");
//            break;
//        case 57:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp057, "RankUp057");
//            break;
//        case 58:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp058, "RankUp058");
//            break;
//        case 59:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp059, "RankUp059");
//            break;
//        case 60:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp060, "RankUp060");
//            break;
//        case 61:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp061, "RankUp061");
//            break;
//        case 62:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp062, "RankUp062");
//            break;
//        case 63:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp063, "RankUp063");
//            break;
//        case 64:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp064, "RankUp064");
//            break;
//        case 65:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp065, "RankUp065");
//            break;
//        case 66:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp066, "RankUp066");
//            break;
//        case 67:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp067, "RankUp067");
//            break;
//        case 68:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp068, "RankUp068");
//            break;
//        case 69:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp069, "RankUp069");
//            break;
//        case 70:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp070, "RankUp070");
//            break;
//        case 71:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp071, "RankUp071");
//            break;
//        case 72:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp072, "RankUp072");
//            break;
//        case 73:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp073, "RankUp073");
//            break;
//        case 74:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp074, "RankUp074");
//            break;
//        case 75:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp075, "RankUp075");
//            break;
//        case 76:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp076, "RankUp076");
//            break;
//        case 77:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp077, "RankUp077");
//            break;
//        case 78:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp078, "RankUp078");
//            break;
//        case 79:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp079, "RankUp079");
//            break;
//        case 80:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp080, "RankUp080");
//            break;
//        case 81:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp081, "RankUp081");
//            break;
//        case 82:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp082, "RankUp082");
//            break;
//        case 83:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp083, "RankUp083");
//            break;
//        case 84:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp084, "RankUp084");
//            break;
//        case 85:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp085, "RankUp085");
//            break;
//        case 86:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp086, "RankUp086");
//            break;
//        case 87:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp087, "RankUp087");
//            break;
//        case 88:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp088, "RankUp088");
//            break;
//        case 89:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp089, "RankUp089");
//            break;
//        case 90:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp090, "RankUp090");
//            break;
//        case 91:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp091, "RankUp091");
//            break;
//        case 92:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp092, "RankUp092");
//            break;
//        case 93:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp093, "RankUp093");
//            break;
//        case 94:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp094, "RankUp094");
//            break;
//        case 95:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp095, "RankUp095");
//            break;
//        case 96:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp096, "RankUp096");
//            break;
//        case 97:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp097, "RankUp097");
//            break;
//        case 98:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp098, "RankUp098");
//            break;
//        case 99:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp099, "RankUp099");
//            break;
//        case 100:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100, "RankUp100");
//            break;
        default:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100, "RankUp100");
            break;
    }
}

void RankUpStageController::initialize() {
}

void RankUpStageController::processBehavior() {
//    switch (_pProg->get()) {
//        case RankUpStageController::PROG_INIT: {
//            _pProg->change(RankUpStageController::PROG_PLAY);
//            break;
//        }
//
//
//        case RankUpStageController::PROG_PLAY: {
//            if (_pProg->isJustChanged()) {
//            }
//            break;
//        }
//
//        case RankUpStageController::PROG_FINISH: {
//            if (_pProg->isJustChanged()) {
//            }
//            break;
//        }
//
//        default:
//            break;
//    }

}
void RankUpStageController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_RANKUP_WAS_END) {
        _TRACE_("RankUpStageController::onCatchEvent() EVENT_RANKUP_WAS_END prm_pSource="<<prm_pSource);
        RankUpStage* pScene = (RankUpStage*)prm_pSource; //終了宣言したRankUpStage
        pScene->fadeoutSceneWithBgm(240);
        pScene->sayonara(240);
    }

    if (prm_no == EVENT_RANKUP_ON_GARBAGED) {
        _TRACE_("RankUpStageController::onCatchEvent() EVENT_RANKUP_ON_GARBAGED prm_pSource="<<prm_pSource);
        //スロー回復
        GgafScene* pRankUpStage = getSubFirst();
        if (pRankUpStage) {
            //他のランクアップ中
            //既存ランクアップシーンをスロー回復
            while (1) {
                if (pRankUpStage == prm_pSource) {
                    break;
                } else {
                    pRankUpStage->addRunFrameOnce(-1); //スロー回復
                    _TRACE_("pRankUpStage="<<pRankUpStage->getName()<<"をスロー回復");
                    pRankUpStage = pRankUpStage->getNext();
                }
            }
        } else {
            throwGgafCriticalException("RankUpStageController::onCatchEvent EVENT_RANKUP_WAS_END サブがnullptr"<<
                                       "this="<<this<<"["<<getName()<<"] prm_pSource="<<prm_pSource);
        }
    }
}
void RankUpStageController::sayonaraRankUpStages() {
    GgafScene* pRankUpStage = getSubFirst()->getPrev();//last
    if (pRankUpStage) {
        while (1) {
            pRankUpStage->sayonara();
            if (pRankUpStage == getSubFirst()) {
                break;
            } else {
                pRankUpStage = pRankUpStage->getPrev();
            }
        }
    }
}

RankUpStageController::~RankUpStageController() {
    pSeConn_RankUpStageExec_->close();
}

