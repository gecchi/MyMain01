#include "RankUp003.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/ggaf/lib/util/ScenePhase.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

RankUp003::RankUp003(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp003";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
    _paFrame_NextEvent = new frame[35];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 35;
    requestActor(110000000, EnemyTamago01, "EnemyTamago01-110000000");
    requestActor(110000001, EnemyTamago01, "EnemyTamago01-110000001");
    requestActor(110000002, EnemyTamago01, "EnemyTamago01-110000002");
    requestActor(110000003, EnemyTamago01, "EnemyTamago01-110000003");
    requestActor(110000004, EnemyTamago01, "EnemyTamago01-110000004");
    requestActor(110000005, EnemyTamago01, "EnemyTamago01-110000005");
    requestActor(110000006, EnemyTamago01, "EnemyTamago01-110000006");
    requestActor(110000007, EnemyTamago01, "EnemyTamago01-110000007");
    requestActor(110000008, EnemyTamago01, "EnemyTamago01-110000008");
    requestActor(110000009, EnemyTamago01, "EnemyTamago01-110000009");
    requestActor(110000010, EnemyTamago01, "EnemyTamago01-110000010");
    requestActor(110000011, EnemyTamago01, "EnemyTamago01-110000011");
    requestActor(110000012, EnemyTamago01, "EnemyTamago01-110000012");
    requestActor(110000013, EnemyTamago01, "EnemyTamago01-110000013");
    requestActor(110000014, EnemyTamago01, "EnemyTamago01-110000014");
    requestActor(110000015, EnemyTamago01, "EnemyTamago01-110000015");
    requestActor(110000016, EnemyTamago01, "EnemyTamago01-110000016");
    requestActor(110000017, EnemyTamago01, "EnemyTamago01-110000017");
    requestActor(110000018, EnemyTamago01, "EnemyTamago01-110000018");
    requestActor(110000019, EnemyTamago01, "EnemyTamago01-110000019");
    requestActor(110000020, EnemyTamago01, "EnemyTamago01-110000020");
    requestActor(110000021, EnemyTamago01, "EnemyTamago01-110000021");
    requestActor(110000022, EnemyTamago01, "EnemyTamago01-110000022");
    requestActor(110000023, EnemyTamago01, "EnemyTamago01-110000023");
    requestActor(110000024, EnemyTamago01, "EnemyTamago01-110000024");
    requestActor(110000025, EnemyTamago01, "EnemyTamago01-110000025");
    requestActor(110000026, EnemyTamago01, "EnemyTamago01-110000026");
    // gen01 end

    getBgmConductor()->ready(0, "BGM_RANKUP003_THEMA");
}

void RankUp003::initialize() {
    RankUpStage::initialize();
}

void RankUp003::processBehavior() {
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
                requestActor(110000027, EnemyTamago01, "EnemyTamago01-110000027");
                break;
            }
            case 80: {
                requestActor(110000028, EnemyTamago01, "EnemyTamago01-110000028");
                break;
            }
            case 140: {
                requestActor(110000029, EnemyTamago01, "EnemyTamago01-110000029");
                break;
            }
            case 200: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000000);
                getSceneChief()->appendChild(pActor);
                requestActor(110000030, EnemyTamago01, "EnemyTamago01-110000030");
                break;
            }
            case 260: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000001);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 320: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000002);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 380: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000003);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 440: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000004);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 500: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000005);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 560: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000006);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 620: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000007);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 680: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000008);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 740: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000009);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 800: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000010);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 860: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000011);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 920: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000012);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 980: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000013);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1040: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000014);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1100: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000015);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1160: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000016);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1220: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000017);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1280: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000018);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1340: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000019);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1400: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000020);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1460: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000021);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1520: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000022);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1580: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000023);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1640: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000024);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1700: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000025);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1760: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000026);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1820: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000027);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1880: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000028);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1940: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000029);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 2000: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(110000030);
                getSceneChief()->appendChild(pActor);
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

void RankUp003::processJudgement() {
}


void RankUp003::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}


RankUp003::~RankUp003() {

}
