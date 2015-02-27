#include "RankUp001.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

#include "jp/ggaf/lib/util/SceneProgress.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
    orderActorToFactory(80000000, EnemyIrce, "EnemyIrce-1");
    orderActorToFactory(80000001, EnemyIrce, "EnemyIrce-2");
    orderActorToFactory(80000002, EnemyIrce, "EnemyIrce-3");
    orderActorToFactory(80000003, EnemyIrce, "EnemyIrce-4");
    orderActorToFactory(80000004, EnemyIrce, "EnemyIrce-5");
    orderActorToFactory(80000005, EnemyIrce, "EnemyIrce-6");
    orderActorToFactory(80000006, EnemyIrce, "EnemyIrce-7");
    orderActorToFactory(80000007, EnemyIrce, "EnemyIrce-8");
    orderActorToFactory(80000008, EnemyIrce, "EnemyIrce-9");
    orderActorToFactory(80000009, EnemyIrce, "EnemyIrce-10");
    orderActorToFactory(80000010, EnemyIrce, "EnemyIrce-11");
    orderActorToFactory(80000011, EnemyIrce, "EnemyIrce-12");
    orderActorToFactory(80000012, EnemyIrce, "EnemyIrce-13");
    orderActorToFactory(80000013, EnemyIrce, "EnemyIrce-14");
    orderActorToFactory(80000014, EnemyIrce, "EnemyIrce-15");
    orderActorToFactory(80000015, EnemyIrce, "EnemyIrce-16");
    orderActorToFactory(80000016, EnemyIrce, "EnemyIrce-17");
    orderActorToFactory(80000017, EnemyIrce, "EnemyIrce-18");
    orderActorToFactory(80000018, EnemyIrce, "EnemyIrce-19");
    orderActorToFactory(80000019, EnemyIrce, "EnemyIrce-20");
    orderActorToFactory(80000020, EnemyIrce, "EnemyIrce-21");
    orderActorToFactory(80000021, EnemyIrce, "EnemyIrce-22");
    orderActorToFactory(80000022, EnemyIrce, "EnemyIrce-23");
    orderActorToFactory(80000023, EnemyIrce, "EnemyIrce-24");
    orderActorToFactory(80000024, EnemyIrce, "EnemyIrce-25");
    orderActorToFactory(80000025, EnemyIrce, "EnemyIrce-26");
    orderActorToFactory(80000026, EnemyIrce, "EnemyIrce-27");
    orderActorToFactory(80000031, FormationThagoras001, "FormationThagoras001-28");
    // gen01 end

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
                orderActorToFactory(80000027, EnemyIrce, "EnemyIrce-29");
                break;
            }
            case 80: {
                orderActorToFactory(80000028, EnemyIrce, "EnemyIrce-30");
                break;
            }
            case 140: {
                orderActorToFactory(80000029, EnemyIrce, "EnemyIrce-31");
                break;
            }
            case 200: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000000);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                orderActorToFactory(80000030, EnemyIrce, "EnemyIrce-32");
                FormationThagoras001* pF1 = (FormationThagoras001*)obtainActorFromFactory(80000031);
                getSceneDirector()->addSubGroup(pF1);
                pF1->position(PX_C(-200), PX_C(  0), PX_C(500));
                all_hit_num_ += pF1->num_Thagoras_;
                break;
            }
            case 260: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000001);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 320: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000002);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 380: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000003);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 440: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000004);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 500: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000005);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 560: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000006);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 620: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000007);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 680: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000008);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 740: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000009);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 800: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000010);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 860: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000011);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 920: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000012);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 980: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000013);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1040: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000014);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1100: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000015);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1160: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000016);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1220: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000017);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1280: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000018);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1340: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000019);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1400: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000020);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1460: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000021);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1520: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000022);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1580: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000023);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1640: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000024);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1700: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000025);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1760: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000026);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1820: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000027);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1880: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000028);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 1940: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000029);
                getSceneDirector()->addSubGroup(p);
                all_hit_num_ ++;
                break;
            }
            case 2000: {
                EnemyIrce* p = (EnemyIrce*)obtainActorFromFactory(80000030);
                getSceneDirector()->addSubGroup(p);
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
                _TRACE_("RankUp001::processBehavior() RankUpStage::PROG_PLAYING になりますた！ getBehaveingFrame()="<<getBehaveingFrame());
            }

            if (pProg->arriveAtFrameOf(_paFrame_NextEvent[_event_num-1]+600)) {
                _TRACE_("RankUp001::processBehavior() RankUpStage::PROG_PLAYING おわった。 pProg->getFrame()="<<pProg->getFrame());
                pProg->change(RankUpStage::PROG_RESULT); //RankUpStageの共通処理へ
            }
            break;
        }
    }

}

void RankUp001::processJudgement() {
}

void RankUp001::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp001::~RankUp001() {
        _TRACE_("RankUp001::~RankUp001() getBehaveingFrame()="<<getBehaveingFrame()<<" _cnt_event="<<_cnt_event);
}
