#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

RankUp001::RankUp001(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp001";

    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
	_paFrame_NextEvent = new frame[35];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 35;
	orderActorToFactory(80000000, EnemyCirce, "EnemyCirce_1");
	orderActorToFactory(80000001, EnemyCirce, "EnemyCirce_2");
	orderActorToFactory(80000002, EnemyCirce, "EnemyCirce_3");
	orderActorToFactory(80000003, EnemyCirce, "EnemyCirce_4");
	orderActorToFactory(80000004, EnemyCirce, "EnemyCirce_5");
	orderActorToFactory(80000005, EnemyCirce, "EnemyCirce_6");
	orderActorToFactory(80000006, EnemyCirce, "EnemyCirce_7");
	orderActorToFactory(80000007, EnemyCirce, "EnemyCirce_8");
	orderActorToFactory(80000008, EnemyCirce, "EnemyCirce_9");
	orderActorToFactory(80000009, EnemyCirce, "EnemyCirce_10");
	orderActorToFactory(80000010, EnemyCirce, "EnemyCirce_11");
	orderActorToFactory(80000011, EnemyCirce, "EnemyCirce_12");
	orderActorToFactory(80000012, EnemyCirce, "EnemyCirce_13");
	orderActorToFactory(80000013, EnemyCirce, "EnemyCirce_14");
	orderActorToFactory(80000014, EnemyCirce, "EnemyCirce_15");
	orderActorToFactory(80000015, EnemyCirce, "EnemyCirce_16");
	orderActorToFactory(80000016, EnemyCirce, "EnemyCirce_17");
	orderActorToFactory(80000017, EnemyCirce, "EnemyCirce_18");
	orderActorToFactory(80000018, EnemyCirce, "EnemyCirce_19");
	orderActorToFactory(80000019, EnemyCirce, "EnemyCirce_20");
	orderActorToFactory(80000020, EnemyCirce, "EnemyCirce_21");
	orderActorToFactory(80000021, EnemyCirce, "EnemyCirce_22");
	orderActorToFactory(80000022, EnemyCirce, "EnemyCirce_23");
	orderActorToFactory(80000023, EnemyCirce, "EnemyCirce_24");
	orderActorToFactory(80000024, EnemyCirce, "EnemyCirce_25");
	orderActorToFactory(80000025, EnemyCirce, "EnemyCirce_26");
	orderActorToFactory(80000026, EnemyCirce, "EnemyCirce_27");
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
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 20: {
				orderActorToFactory(80000027, EnemyCirce, "EnemyCirce_28");
				break;
			}
			case 80: {
				orderActorToFactory(80000028, EnemyCirce, "EnemyCirce_29");
				break;
			}
			case 140: {
				orderActorToFactory(80000029, EnemyCirce, "EnemyCirce_30");
				break;
			}
			case 200: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000000);
				getDirector()->addSubGroup(p);
				orderActorToFactory(80000030, EnemyCirce, "EnemyCirce_31");
				break;
			}
			case 260: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000001);
				getDirector()->addSubGroup(p);
				break;
			}
			case 320: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000002);
				getDirector()->addSubGroup(p);
				break;
			}
			case 380: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000003);
				getDirector()->addSubGroup(p);
				break;
			}
			case 440: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000004);
				getDirector()->addSubGroup(p);
				break;
			}
			case 500: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000005);
				getDirector()->addSubGroup(p);
				break;
			}
			case 560: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000006);
				getDirector()->addSubGroup(p);
				break;
			}
			case 620: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000007);
				getDirector()->addSubGroup(p);
				break;
			}
			case 680: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000008);
				getDirector()->addSubGroup(p);
				break;
			}
			case 740: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000009);
				getDirector()->addSubGroup(p);
				break;
			}
			case 800: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000010);
				getDirector()->addSubGroup(p);
				break;
			}
			case 860: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000011);
				getDirector()->addSubGroup(p);
				break;
			}
			case 920: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000012);
				getDirector()->addSubGroup(p);
				break;
			}
			case 980: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000013);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1040: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000014);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1100: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000015);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1160: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000016);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1220: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000017);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1280: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000018);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1340: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000019);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1400: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000020);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1460: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000021);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1520: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000022);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1580: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000023);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1640: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000024);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1700: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000025);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1760: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000026);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1820: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000027);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1880: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000028);
				getDirector()->addSubGroup(p);
				break;
			}
			case 1940: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000029);
				getDirector()->addSubGroup(p);
				break;
			}
			case 2000: {
				EnemyCirce* p = (EnemyCirce*)obtainActorFromFactory(80000030);
				getDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 35-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case RankUpStage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp001::processBehavior() RankUpStage::PROG_PLAYING になりますた！");
            }

            if (_pProg->getFrameInProgress() == 2500) {
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
