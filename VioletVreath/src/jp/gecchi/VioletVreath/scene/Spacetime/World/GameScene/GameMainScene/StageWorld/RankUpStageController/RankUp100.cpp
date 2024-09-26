#include "RankUp100.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/ggaf/lib/util/ScenePhase.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

RankUp100::RankUp100(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp100";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
    _paFrame_NextEvent = new frame[35];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 35;
    requestActor(120000000, EnemyTamago01, "EnemyTamago01-120000000");
    requestActor(120000001, EnemyTamago01, "EnemyTamago01-120000001");
    requestActor(120000002, EnemyTamago01, "EnemyTamago01-120000002");
    requestActor(120000003, EnemyTamago01, "EnemyTamago01-120000003");
    requestActor(120000004, EnemyTamago01, "EnemyTamago01-120000004");
    requestActor(120000005, EnemyTamago01, "EnemyTamago01-120000005");
    requestActor(120000006, EnemyTamago01, "EnemyTamago01-120000006");
    requestActor(120000007, EnemyTamago01, "EnemyTamago01-120000007");
    requestActor(120000008, EnemyTamago01, "EnemyTamago01-120000008");
    requestActor(120000009, EnemyTamago01, "EnemyTamago01-120000009");
    requestActor(120000010, EnemyTamago01, "EnemyTamago01-120000010");
    requestActor(120000011, EnemyTamago01, "EnemyTamago01-120000011");
    requestActor(120000012, EnemyTamago01, "EnemyTamago01-120000012");
    requestActor(120000013, EnemyTamago01, "EnemyTamago01-120000013");
    requestActor(120000014, EnemyTamago01, "EnemyTamago01-120000014");
    requestActor(120000015, EnemyTamago01, "EnemyTamago01-120000015");
    requestActor(120000016, EnemyTamago01, "EnemyTamago01-120000016");
    requestActor(120000017, EnemyTamago01, "EnemyTamago01-120000017");
    requestActor(120000018, EnemyTamago01, "EnemyTamago01-120000018");
    requestActor(120000019, EnemyTamago01, "EnemyTamago01-120000019");
    requestActor(120000020, EnemyTamago01, "EnemyTamago01-120000020");
    requestActor(120000021, EnemyTamago01, "EnemyTamago01-120000021");
    requestActor(120000022, EnemyTamago01, "EnemyTamago01-120000022");
    requestActor(120000023, EnemyTamago01, "EnemyTamago01-120000023");
    requestActor(120000024, EnemyTamago01, "EnemyTamago01-120000024");
    requestActor(120000025, EnemyTamago01, "EnemyTamago01-120000025");
    requestActor(120000026, EnemyTamago01, "EnemyTamago01-120000026");
    // gen01 end
    getBgmConductor()->ready(0, "BGM_RANKUP100_THEMA");
}

void RankUp100::initialize() {
    RankUpStage::initialize();
}

void RankUp100::processBehavior() {
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
                requestActor(120000027, EnemyTamago01, "EnemyTamago01-120000027");
                break;
            }
            case 80: {
                requestActor(120000028, EnemyTamago01, "EnemyTamago01-120000028");
                break;
            }
            case 140: {
                requestActor(120000029, EnemyTamago01, "EnemyTamago01-120000029");
                break;
            }
            case 200: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000000);
                getSceneChief()->appendChild(pActor);
                requestActor(120000030, EnemyTamago01, "EnemyTamago01-120000030");
                break;
            }
            case 260: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000001);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 320: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000002);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 380: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000003);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 440: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000004);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 500: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000005);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 560: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000006);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 620: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000007);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 680: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000008);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 740: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000009);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 800: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000010);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 860: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000011);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 920: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000012);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 980: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000013);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1040: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000014);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1100: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000015);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1160: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000016);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1220: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000017);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1280: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000018);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1340: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000019);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1400: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000020);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1460: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000021);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1520: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000022);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1580: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000023);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1640: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000024);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1700: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000025);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1760: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000026);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1820: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000027);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1880: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000028);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 1940: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000029);
                getSceneChief()->appendChild(pActor);
                break;
            }
            case 2000: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000030);
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

void RankUp100::processJudgement() {
}


void RankUp100::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}


RankUp100::~RankUp100() {

}
