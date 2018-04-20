#include "RankUp100.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/ggaf/lib/util/SceneProgress.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
    wishActor(120000000, EnemyTamago01, "EnemyTamago01-120000000");
    wishActor(120000001, EnemyTamago01, "EnemyTamago01-120000001");
    wishActor(120000002, EnemyTamago01, "EnemyTamago01-120000002");
    wishActor(120000003, EnemyTamago01, "EnemyTamago01-120000003");
    wishActor(120000004, EnemyTamago01, "EnemyTamago01-120000004");
    wishActor(120000005, EnemyTamago01, "EnemyTamago01-120000005");
    wishActor(120000006, EnemyTamago01, "EnemyTamago01-120000006");
    wishActor(120000007, EnemyTamago01, "EnemyTamago01-120000007");
    wishActor(120000008, EnemyTamago01, "EnemyTamago01-120000008");
    wishActor(120000009, EnemyTamago01, "EnemyTamago01-120000009");
    wishActor(120000010, EnemyTamago01, "EnemyTamago01-120000010");
    wishActor(120000011, EnemyTamago01, "EnemyTamago01-120000011");
    wishActor(120000012, EnemyTamago01, "EnemyTamago01-120000012");
    wishActor(120000013, EnemyTamago01, "EnemyTamago01-120000013");
    wishActor(120000014, EnemyTamago01, "EnemyTamago01-120000014");
    wishActor(120000015, EnemyTamago01, "EnemyTamago01-120000015");
    wishActor(120000016, EnemyTamago01, "EnemyTamago01-120000016");
    wishActor(120000017, EnemyTamago01, "EnemyTamago01-120000017");
    wishActor(120000018, EnemyTamago01, "EnemyTamago01-120000018");
    wishActor(120000019, EnemyTamago01, "EnemyTamago01-120000019");
    wishActor(120000020, EnemyTamago01, "EnemyTamago01-120000020");
    wishActor(120000021, EnemyTamago01, "EnemyTamago01-120000021");
    wishActor(120000022, EnemyTamago01, "EnemyTamago01-120000022");
    wishActor(120000023, EnemyTamago01, "EnemyTamago01-120000023");
    wishActor(120000024, EnemyTamago01, "EnemyTamago01-120000024");
    wishActor(120000025, EnemyTamago01, "EnemyTamago01-120000025");
    wishActor(120000026, EnemyTamago01, "EnemyTamago01-120000026");
    // gen01 end
    getBgmConductor()->ready(0, "OGG_RANKUP100_THEMA");
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
                wishActor(120000027, EnemyTamago01, "EnemyTamago01-120000027");
                break;
            }
            case 80: {
                wishActor(120000028, EnemyTamago01, "EnemyTamago01-120000028");
                break;
            }
            case 140: {
                wishActor(120000029, EnemyTamago01, "EnemyTamago01-120000029");
                break;
            }
            case 200: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000000);
                bringSceneMediator()->addSubGroup(pActor);
                wishActor(120000030, EnemyTamago01, "EnemyTamago01-120000030");
                break;
            }
            case 260: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000001);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 320: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000002);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 380: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000003);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 440: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000004);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 500: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000005);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 560: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000006);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 620: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000007);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 680: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000008);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 740: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000009);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 800: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000010);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 860: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000011);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 920: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000012);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 980: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000013);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1040: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000014);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1100: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000015);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1160: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000016);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1220: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000017);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1280: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000018);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1340: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000019);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1400: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000020);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1460: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000021);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1520: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000022);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1580: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000023);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1640: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000024);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1700: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000025);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1760: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000026);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1820: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000027);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1880: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000028);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 1940: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000029);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            case 2000: {
                EnemyTamago01* pActor = (EnemyTamago01*)receiveActor(120000030);
                bringSceneMediator()->addSubGroup(pActor);
                break;
            }
            default :
                break;
        }
        _cnt_event = (_cnt_event < 35-1 ? _cnt_event+1 : _cnt_event);
    }
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case RankUpStage::PROG_PLAYING: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" RankUpStage::PROG_PLAYING になりますた！");
            }

            if (pProg->hasArrivedAt(_paFrame_NextEvent[_event_num-1]+600)) {
                _TRACE_(FUNC_NAME<<" RankUpStage::PROG_PLAYING おわった");
                pProg->change(RankUpStage::PROG_RESULT); //RankUpStageの共通処理へ
            }
            break;
        }
    }

}

void RankUp100::processJudgement() {
}


void RankUp100::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp100::~RankUp100() {

}
