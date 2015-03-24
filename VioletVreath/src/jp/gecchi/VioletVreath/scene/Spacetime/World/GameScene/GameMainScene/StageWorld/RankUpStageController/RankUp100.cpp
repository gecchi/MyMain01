#include "RankUp100.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/util/SceneProgress.h"
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
    orderActorToFactory(100000000, EnemyTamago01, "EnemyTamago01-1");
    orderActorToFactory(100000001, EnemyTamago01, "EnemyTamago01-2");
    orderActorToFactory(100000002, EnemyTamago01, "EnemyTamago01-3");
    orderActorToFactory(100000100, EnemyTamago01, "EnemyTamago01-4");
    orderActorToFactory(100000004, EnemyTamago01, "EnemyTamago01-5");
    orderActorToFactory(100000005, EnemyTamago01, "EnemyTamago01-6");
    orderActorToFactory(100000006, EnemyTamago01, "EnemyTamago01-7");
    orderActorToFactory(100000007, EnemyTamago01, "EnemyTamago01-8");
    orderActorToFactory(100000008, EnemyTamago01, "EnemyTamago01-9");
    orderActorToFactory(100000009, EnemyTamago01, "EnemyTamago01-10");
    orderActorToFactory(100000010, EnemyTamago01, "EnemyTamago01-11");
    orderActorToFactory(100000011, EnemyTamago01, "EnemyTamago01-12");
    orderActorToFactory(100000012, EnemyTamago01, "EnemyTamago01-13");
    orderActorToFactory(100000013, EnemyTamago01, "EnemyTamago01-14");
    orderActorToFactory(100000014, EnemyTamago01, "EnemyTamago01-15");
    orderActorToFactory(100000015, EnemyTamago01, "EnemyTamago01-16");
    orderActorToFactory(100000016, EnemyTamago01, "EnemyTamago01-17");
    orderActorToFactory(100000017, EnemyTamago01, "EnemyTamago01-18");
    orderActorToFactory(100000018, EnemyTamago01, "EnemyTamago01-19");
    orderActorToFactory(100000019, EnemyTamago01, "EnemyTamago01-20");
    orderActorToFactory(100000020, EnemyTamago01, "EnemyTamago01-21");
    orderActorToFactory(100000021, EnemyTamago01, "EnemyTamago01-22");
    orderActorToFactory(100000022, EnemyTamago01, "EnemyTamago01-23");
    orderActorToFactory(100000023, EnemyTamago01, "EnemyTamago01-24");
    orderActorToFactory(100000024, EnemyTamago01, "EnemyTamago01-25");
    orderActorToFactory(100000025, EnemyTamago01, "EnemyTamago01-26");
    orderActorToFactory(100000026, EnemyTamago01, "EnemyTamago01-27");
    // gen01 end
    getBGMer()->ready(0, "OGG_RANKUP100_THEMA");
}

void RankUp100::initialize() {
    RankUpStage::initialize();
}

void RankUp100::processBehavior() {
    RankUpStage::processBehavior();

    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
    if (getActiveFrame() == _paFrame_NextEvent[_cnt_event]) {
        switch (getActiveFrame()) {
            case 1: {
                break;
            }
            case 20: {
                orderActorToFactory(100000027, EnemyTamago01, "EnemyTamago01-28");
                break;
            }
            case 80: {
                orderActorToFactory(100000028, EnemyTamago01, "EnemyTamago01-29");
                break;
            }
            case 140: {
                orderActorToFactory(100000029, EnemyTamago01, "EnemyTamago01-30");
                break;
            }
            case 200: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000000);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                orderActorToFactory(100001000, EnemyTamago01, "EnemyTamago01-31");
                break;
            }
            case 260: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000001);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 320: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000002);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 380: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000100);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 440: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000004);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 500: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000005);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 560: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000006);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 620: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000007);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 680: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000008);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 740: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000009);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 800: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000010);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 860: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000011);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 920: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000012);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 980: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000013);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1040: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000014);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1100: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000015);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1160: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000016);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1220: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000017);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1280: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000018);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1340: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000019);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1400: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000020);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1460: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000021);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1520: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000022);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1580: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000023);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1640: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000024);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1700: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000025);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1760: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000026);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1820: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000027);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1880: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000028);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 1940: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000029);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
                break;
            }
            case 2000: {
                EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100001000);
                bringDirector()->addSubGroup(pActor);
                all_hit_num_ ++;
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
            if (pProg->isJustChanged()) {
                _TRACE_("RankUp100::processBehavior() RankUpStage::PROG_PLAYING になりますた！");
            }

            if (pProg->hasArrivedAt(_paFrame_NextEvent[_event_num-1]+600)) {
                _TRACE_("RankUp100::processBehavior() RankUpStage::PROG_PLAYING おわった");
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
