#include "stdafx.h"
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
	orderActorToFactory(80000000, EnemyCirce, "EnemyCirce-1");
	orderActorToFactory(80000001, EnemyCirce, "EnemyCirce-2");
	orderActorToFactory(80000002, EnemyCirce, "EnemyCirce-3");
	orderActorToFactory(80000003, EnemyCirce, "EnemyCirce-4");
	orderActorToFactory(80000004, EnemyCirce, "EnemyCirce-5");
	orderActorToFactory(80000005, EnemyCirce, "EnemyCirce-6");
	orderActorToFactory(80000006, EnemyCirce, "EnemyCirce-7");
	orderActorToFactory(80000007, EnemyCirce, "EnemyCirce-8");
	orderActorToFactory(80000008, EnemyCirce, "EnemyCirce-9");
	orderActorToFactory(80000009, EnemyCirce, "EnemyCirce-10");
	orderActorToFactory(80000010, EnemyCirce, "EnemyCirce-11");
	orderActorToFactory(80000011, EnemyCirce, "EnemyCirce-12");
	orderActorToFactory(80000012, EnemyCirce, "EnemyCirce-13");
	orderActorToFactory(80000013, EnemyCirce, "EnemyCirce-14");
	orderActorToFactory(80000014, EnemyCirce, "EnemyCirce-15");
	orderActorToFactory(80000015, EnemyCirce, "EnemyCirce-16");
	orderActorToFactory(80000016, EnemyCirce, "EnemyCirce-17");
	orderActorToFactory(80000017, EnemyCirce, "EnemyCirce-18");
	orderActorToFactory(80000018, EnemyCirce, "EnemyCirce-19");
	orderActorToFactory(80000019, EnemyCirce, "EnemyCirce-20");
	orderActorToFactory(80000020, EnemyCirce, "EnemyCirce-21");
	orderActorToFactory(80000021, EnemyCirce, "EnemyCirce-22");
	orderActorToFactory(80000022, EnemyCirce, "EnemyCirce-23");
	orderActorToFactory(80000023, EnemyCirce, "EnemyCirce-24");
	orderActorToFactory(80000024, EnemyCirce, "EnemyCirce-25");
	orderActorToFactory(80000025, EnemyCirce, "EnemyCirce-26");
	orderActorToFactory(80000026, EnemyCirce, "EnemyCirce-27");
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
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 20: {
				orderActorToFactory(80000027, EnemyCirce, "EnemyCirce-28");
				break;
			}
			case 80: {
				orderActorToFactory(80000028, EnemyCirce, "EnemyCirce-29");
				break;
			}
			case 140: {
				orderActorToFactory(80000029, EnemyCirce, "EnemyCirce-30");
				break;
			}
			case 200: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000000);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				orderActorToFactory(80000030, EnemyCirce, "EnemyCirce-31");
				break;
			}
			case 260: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000001);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 320: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000002);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 380: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000003);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 440: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000004);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 500: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000005);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 560: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000006);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 620: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000007);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 680: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000008);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 740: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000009);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 800: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000010);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 860: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000011);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 920: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000012);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 980: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000013);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1040: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000014);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1100: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000015);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1160: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000016);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1220: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000017);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1280: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000018);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1340: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000019);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1400: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000020);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1460: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000021);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1520: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000022);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1580: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000023);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1640: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000024);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1700: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000025);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1760: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000026);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1820: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000027);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1880: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000028);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 1940: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000029);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			case 2000: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000030);
				getDirector()->addSubGroup(p);
				all_hit_num_ ++;
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 35-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case RankUpStage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp001::processBehavior() RankUpStage::PROG_PLAYING になりますた！");
            }

            if (_pProg->getFrameInProgress() == _paFrame_NextEvent[_event_num-1]+600) {
                _TRACE_("RankUp001::processBehavior() RankUpStage::PROG_PLAYING おわった");
                _pProg->change(RankUpStage::PROG_RESULT); //RankUpStageの共通処理へ
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

}
