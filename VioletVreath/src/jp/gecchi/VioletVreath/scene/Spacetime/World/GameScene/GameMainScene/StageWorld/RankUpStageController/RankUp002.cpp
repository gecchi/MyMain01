#include "RankUp002.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/ggaf/lib/util/ScenePhase.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

RankUp002::RankUp002(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp002";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
    _paFrame_NextEvent = new frame[35];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 35;
    requestActor(100000000, EnemyTamago01, "EnemyTamago01-100000000");
    requestActor(100000001, EnemyTamago01, "EnemyTamago01-100000001");
    requestActor(100000002, EnemyTamago01, "EnemyTamago01-100000002");
    requestActor(100000003, EnemyTamago01, "EnemyTamago01-100000003");
    requestActor(100000004, EnemyTamago01, "EnemyTamago01-100000004");
    requestActor(100000005, EnemyTamago01, "EnemyTamago01-100000005");
    requestActor(100000006, EnemyTamago01, "EnemyTamago01-100000006");
    requestActor(100000007, EnemyTamago01, "EnemyTamago01-100000007");
    requestActor(100000008, EnemyTamago01, "EnemyTamago01-100000008");
    requestActor(100000009, EnemyTamago01, "EnemyTamago01-100000009");
    requestActor(100000010, EnemyTamago01, "EnemyTamago01-100000010");
    requestActor(100000011, EnemyTamago01, "EnemyTamago01-100000011");
    requestActor(100000012, EnemyTamago01, "EnemyTamago01-100000012");
    requestActor(100000013, EnemyTamago01, "EnemyTamago01-100000013");
    requestActor(100000014, EnemyTamago01, "EnemyTamago01-100000014");
    requestActor(100000015, EnemyTamago01, "EnemyTamago01-100000015");
    requestActor(100000016, EnemyTamago01, "EnemyTamago01-100000016");
    requestActor(100000017, EnemyTamago01, "EnemyTamago01-100000017");
    requestActor(100000018, EnemyTamago01, "EnemyTamago01-100000018");
    requestActor(100000019, EnemyTamago01, "EnemyTamago01-100000019");
    requestActor(100000020, EnemyTamago01, "EnemyTamago01-100000020");
    requestActor(100000021, EnemyTamago01, "EnemyTamago01-100000021");
    requestActor(100000022, EnemyTamago01, "EnemyTamago01-100000022");
    requestActor(100000023, EnemyTamago01, "EnemyTamago01-100000023");
    requestActor(100000024, EnemyTamago01, "EnemyTamago01-100000024");
    requestActor(100000025, EnemyTamago01, "EnemyTamago01-100000025");
    requestActor(100000026, EnemyTamago01, "EnemyTamago01-100000026");
    // gen01 end

    getBgmConductor()->ready(0, "BGM_RANKUP002_THEMA");
}

void RankUp002::initialize() {
    RankUpStage::initialize();
}

void RankUp002::processBehavior() {
    RankUpStage::processBehavior();

    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getBehaveingFrame()) {
            case 1: {
                break;
            }
            case 20: {
                requestActor(100000027, EnemyTamago01, "EnemyTamago01-100000027");
                break;
            }
            case 80: {
                requestActor(100000028, EnemyTamago01, "EnemyTamago01-100000028");
                break;
            }
            case 140: {
                requestActor(100000029, EnemyTamago01, "EnemyTamago01-100000029");
                break;
            }
            case 200: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000000);
                getSceneChief()->appendGroupChild(pActor);
                requestActor(100000030, EnemyTamago01, "EnemyTamago01-100000030");
                break;
            }
            case 260: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000001);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 320: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000002);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 380: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000003);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 440: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000004);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 500: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000005);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 560: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000006);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 620: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000007);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 680: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000008);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 740: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000009);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 800: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000010);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 860: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000011);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 920: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000012);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 980: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000013);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1040: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000014);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1100: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000015);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1160: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000016);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1220: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000017);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1280: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000018);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1340: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000019);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1400: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000020);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1460: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000021);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1520: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000022);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1580: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000023);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1640: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000024);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1700: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000025);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1760: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000026);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1820: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000027);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1880: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000028);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 1940: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000029);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            case 2000: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(100000030);
                getSceneChief()->appendGroupChild(pActor);
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 35-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case RankUpStage::PHASE_PLAYING: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" RankUpStage::PHASE_PLAYING になりますた！");
            }

            if (pPhase->hasArrivedFrameAt(_paFrame_NextEvent[_event_num-1]+600)) {
                _TRACE_(FUNC_NAME<<" RankUpStage::PHASE_PLAYING おわった");
                pPhase->change(RankUpStage::PHASE_RESULT); //RankUpStageの共通処理へ
            }
            break;
        }
    }

}

void RankUp002::processJudgement() {
}


void RankUp002::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}


RankUp002::~RankUp002() {

}
