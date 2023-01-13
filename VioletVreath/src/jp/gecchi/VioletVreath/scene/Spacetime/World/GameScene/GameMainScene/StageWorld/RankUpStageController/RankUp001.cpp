#include "RankUp001.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/ggaf/lib/util/ScenePhase.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"



using namespace GgafLib;
using namespace VioletVreath;

RankUp001::RankUp001(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp001";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
    frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
    _paFrame_NextEvent = new frame[35];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 35;
    requestActor(90000000, EnemyIrce, "EnemyIrce-90000000");
    requestActor(90000001, EnemyIrce, "EnemyIrce-90000001");
    requestActor(90000002, EnemyIrce, "EnemyIrce-90000002");
    requestActor(90000003, EnemyIrce, "EnemyIrce-90000003");
    requestActor(90000004, EnemyIrce, "EnemyIrce-90000004");
    requestActor(90000005, EnemyIrce, "EnemyIrce-90000005");
    requestActor(90000006, EnemyIrce, "EnemyIrce-90000006");
    requestActor(90000007, EnemyIrce, "EnemyIrce-90000007");
    requestActor(90000008, EnemyIrce, "EnemyIrce-90000008");
    requestActor(90000009, EnemyIrce, "EnemyIrce-90000009");
    requestActor(90000010, EnemyIrce, "EnemyIrce-90000010");
    requestActor(90000011, EnemyIrce, "EnemyIrce-90000011");
    requestActor(90000012, EnemyIrce, "EnemyIrce-90000012");
    requestActor(90000013, EnemyIrce, "EnemyIrce-90000013");
    requestActor(90000014, EnemyIrce, "EnemyIrce-90000014");
    requestActor(90000015, EnemyIrce, "EnemyIrce-90000015");
    requestActor(90000016, EnemyIrce, "EnemyIrce-90000016");
    requestActor(90000017, EnemyIrce, "EnemyIrce-90000017");
    requestActor(90000018, EnemyIrce, "EnemyIrce-90000018");
    requestActor(90000019, EnemyIrce, "EnemyIrce-90000019");
    requestActor(90000020, EnemyIrce, "EnemyIrce-90000020");
    requestActor(90000021, EnemyIrce, "EnemyIrce-90000021");
    requestActor(90000022, EnemyIrce, "EnemyIrce-90000022");
    requestActor(90000023, EnemyIrce, "EnemyIrce-90000023");
    requestActor(90000024, EnemyIrce, "EnemyIrce-90000024");
    requestActor(90000025, EnemyIrce, "EnemyIrce-90000025");
    requestActor(90000026, EnemyIrce, "EnemyIrce-90000026");
    requestActor(90000031, FormationThagoras001, "FormationThagoras001-90000031");
    // gen01 end

    getBgmConductor()->ready(0, "BGM_RANKUP001_THEMA");
}

void RankUp001::initialize() {
    RankUpStage::initialize();
}

void RankUp001::processBehavior() {
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
                requestActor(90000027, EnemyIrce, "EnemyIrce-90000027");
                break;
            }
            case 80: {
                requestActor(90000028, EnemyIrce, "EnemyIrce-90000028");
                break;
            }
            case 140: {
                requestActor(90000029, EnemyIrce, "EnemyIrce-90000029");
                break;
            }
            case 200: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000000);
                bringSceneMediator()->appendGroupChild(p);
                requestActor(90000030, EnemyIrce, "EnemyIrce-90000030");
                FormationThagoras001* pF1 = (FormationThagoras001*)receiveActor(90000031);
                bringSceneMediator()->appendGroupChild(pF1);
                pF1->setPosition(PX_C(-200), PX_C(  0), PX_C(500));
                break;
            }
            case 260: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000001);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 320: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000002);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 380: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000003);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 440: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000004);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 500: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000005);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 560: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000006);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 620: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000007);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 680: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000008);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 740: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000009);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 800: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000010);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 860: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000011);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 920: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000012);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 980: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000013);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1040: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000014);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1100: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000015);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1160: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000016);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1220: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000017);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1280: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000018);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1340: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000019);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1400: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000020);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1460: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000021);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1520: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000022);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1580: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000023);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1640: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000024);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1700: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000025);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1760: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000026);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1820: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000027);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1880: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000028);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 1940: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000029);
                bringSceneMediator()->appendGroupChild(p);
                break;
            }
            case 2000: {
                EnemyIrce* p = (EnemyIrce*)receiveActor(90000030);
                bringSceneMediator()->appendGroupChild(p);
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
                _TRACE_(FUNC_NAME<<" RankUpStage::PHASE_PLAYING になりますた！ getBehaveingFrame()="<<getBehaveingFrame());
            }

            if (pPhase->hasArrivedFrameAt(_paFrame_NextEvent[_event_num-1]+600)) { //最終のアクター出現から10秒後、強制終了。
                _TRACE_(FUNC_NAME<<" RankUpStage::PHASE_PLAYING おわった。 pPhase->getFrame()="<<pPhase->getFrame());
                pPhase->change(RankUpStage::PHASE_RESULT); //RankUpStageの共通処理へ
            }
            break;
        }
    }

}

void RankUp001::processJudgement() {
}

void RankUp001::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}


RankUp001::~RankUp001() {
        _TRACE_("RankUp001::~RankUp001() getBehaveingFrame()="<<getBehaveingFrame()<<" _cnt_event="<<_cnt_event);
}
