#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


#define ORDER_ID_RANKUP 80

RankUpStageController::RankUpStageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpStageController";
    _TRACE_("RankUpStageController::RankUpStageController("<<prm_name<<")");

    for (int i = 0; i < MAX_RANKUP_SCENE; i ++) {
        _apRankUpStage[i] = NULL;
    }
    useProgress(RankUpStageController::PROG_FINISH);
    ready(_RANK_UP_LEVEL_ + 1);
}
void RankUpStageController::execute() {
    ready(_RANK_UP_LEVEL_);     //これはパスされるはずであるが、念のため。
    ready(_RANK_UP_LEVEL_ + 1); //次のシーンを先行予約
    _pNowRankUpStage = (RankUpStage*)obtainSceneFromFactory(ORDER_ID_RANKUP+_RANK_UP_LEVEL_);
    _TRACE_("RankUpStageController::execute() _pNowRankUpStage="<<_pNowRankUpStage);
    GgafScene* pRankUpStage = getSubFirst();
    if (pRankUpStage) {
        //他のランクアップ中
        //既存ランクアップシーンをスローにする
        while (1) {
            pRankUpStage->addRunFrameOnce(1);
            if (pRankUpStage->isLast()) {
                break;
            } else {
                pRankUpStage = pRankUpStage->getNext();
            }
        }
    }
    addSubLast(_pNowRankUpStage);
    _pNowRankUpStage->fadeoutScene(0);
    _pNowRankUpStage->fadeinSceneTree(240);
    _apRankUpStage[_RANK_UP_LEVEL_-1] = _pNowRankUpStage;
    //スローダウン
}

void RankUpStageController::onReset() {
    _pProg->set(RankUpStageController::PROG_INIT);
}

void RankUpStageController::ready(int prm_rank_level) {
    switch (prm_rank_level) {
        case 1:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp001, "RankUp001");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp002, "RankUp002");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp003, "RankUp003");
            break;
//        case 4:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp004, "RankUp004");
//            break;
//        case 5:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp005, "RankUp005");
//            break;
//        case 6:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp006, "RankUp006");
//            break;
//        case 7:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp007, "RankUp007");
//            break;
//        case 8:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp008, "RankUp008");
//            break;
//        case 9:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp009, "RankUp009");
//            break;
//        case 10:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp010, "RankUp010");
//            break;
//        case 11:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp011, "RankUp011");
//            break;
//        case 12:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp012, "RankUp012");
//            break;
//        case 13:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp013, "RankUp013");
//            break;
//        case 14:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp014, "RankUp014");
//            break;
//        case 15:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp015, "RankUp015");
//            break;
//        case 16:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp016, "RankUp016");
//            break;
//        case 17:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp017, "RankUp017");
//            break;
//        case 18:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp018, "RankUp018");
//            break;
//        case 19:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp019, "RankUp019");
//            break;
//        case 20:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp020, "RankUp020");
//            break;
//        case 21:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp021, "RankUp021");
//            break;
//        case 22:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp022, "RankUp022");
//            break;
//        case 23:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp023, "RankUp023");
//            break;
//        case 24:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp024, "RankUp024");
//            break;
//        case 25:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp025, "RankUp025");
//            break;
//        case 26:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp026, "RankUp026");
//            break;
//        case 27:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp027, "RankUp027");
//            break;
//        case 28:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp028, "RankUp028");
//            break;
//        case 29:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp029, "RankUp029");
//            break;
//        case 30:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp030, "RankUp030");
//            break;
//        case 31:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp031, "RankUp031");
//            break;
//        case 32:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp032, "RankUp032");
//            break;
//        case 33:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp033, "RankUp033");
//            break;
//        case 34:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp034, "RankUp034");
//            break;
//        case 35:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp035, "RankUp035");
//            break;
//        case 36:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp036, "RankUp036");
//            break;
//        case 37:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp037, "RankUp037");
//            break;
//        case 38:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp038, "RankUp038");
//            break;
//        case 39:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp039, "RankUp039");
//            break;
//        case 40:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp040, "RankUp040");
//            break;
//        case 41:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp041, "RankUp041");
//            break;
//        case 42:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp042, "RankUp042");
//            break;
//        case 43:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp043, "RankUp043");
//            break;
//        case 44:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp044, "RankUp044");
//            break;
//        case 45:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp045, "RankUp045");
//            break;
//        case 46:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp046, "RankUp046");
//            break;
//        case 47:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp047, "RankUp047");
//            break;
//        case 48:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp048, "RankUp048");
//            break;
//        case 49:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp049, "RankUp049");
//            break;
//        case 50:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp050, "RankUp050");
//            break;
//        case 51:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp051, "RankUp051");
//            break;
//        case 52:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp052, "RankUp052");
//            break;
//        case 53:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp053, "RankUp053");
//            break;
//        case 54:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp054, "RankUp054");
//            break;
//        case 55:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp055, "RankUp055");
//            break;
//        case 56:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp056, "RankUp056");
//            break;
//        case 57:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp057, "RankUp057");
//            break;
//        case 58:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp058, "RankUp058");
//            break;
//        case 59:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp059, "RankUp059");
//            break;
//        case 60:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp060, "RankUp060");
//            break;
//        case 61:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp061, "RankUp061");
//            break;
//        case 62:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp062, "RankUp062");
//            break;
//        case 63:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp063, "RankUp063");
//            break;
//        case 64:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp064, "RankUp064");
//            break;
//        case 65:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp065, "RankUp065");
//            break;
//        case 66:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp066, "RankUp066");
//            break;
//        case 67:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp067, "RankUp067");
//            break;
//        case 68:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp068, "RankUp068");
//            break;
//        case 69:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp069, "RankUp069");
//            break;
//        case 70:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp070, "RankUp070");
//            break;
//        case 71:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp071, "RankUp071");
//            break;
//        case 72:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp072, "RankUp072");
//            break;
//        case 73:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp073, "RankUp073");
//            break;
//        case 74:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp074, "RankUp074");
//            break;
//        case 75:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp075, "RankUp075");
//            break;
//        case 76:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp076, "RankUp076");
//            break;
//        case 77:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp077, "RankUp077");
//            break;
//        case 78:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp078, "RankUp078");
//            break;
//        case 79:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp079, "RankUp079");
//            break;
//        case 80:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp080, "RankUp080");
//            break;
//        case 81:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp081, "RankUp081");
//            break;
//        case 82:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp082, "RankUp082");
//            break;
//        case 83:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp083, "RankUp083");
//            break;
//        case 84:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp084, "RankUp084");
//            break;
//        case 85:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp085, "RankUp085");
//            break;
//        case 86:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp086, "RankUp086");
//            break;
//        case 87:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp087, "RankUp087");
//            break;
//        case 88:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp088, "RankUp088");
//            break;
//        case 89:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp089, "RankUp089");
//            break;
//        case 90:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp090, "RankUp090");
//            break;
//        case 91:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp091, "RankUp091");
//            break;
//        case 92:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp092, "RankUp092");
//            break;
//        case 93:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp093, "RankUp093");
//            break;
//        case 94:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp094, "RankUp094");
//            break;
//        case 95:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp095, "RankUp095");
//            break;
//        case 96:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp096, "RankUp096");
//            break;
//        case 97:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp097, "RankUp097");
//            break;
//        case 98:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp098, "RankUp098");
//            break;
//        case 99:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp099, "RankUp099");
//            break;
//        case 100:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp100, "RankUp100");
//            break;
        default:
            orderSceneToFactory(ORDER_ID_RANKUP+100, RankUp100, "RankUp100");
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
        pScene->fadeoutScene(240);
        pScene->end(240);
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
            throwGgafCriticalException("RankUpStageController::onCatchEvent EVENT_RANKUP_WAS_END サブがNULL"<<
                                       "this="<<this<<"["<<getName()<<"] prm_pSource="<<prm_pSource);
        }
    }
}

RankUpStageController::~RankUpStageController() {
}

