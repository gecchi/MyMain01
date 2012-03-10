#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

RankUp002::RankUp002(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp002";

    // 以下の gen01 start 〜 end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,20,80,140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040,1100,1160,1220,1280,1340,1400,1460,1520,1580,1640,1700,1760,1820,1880,1940,2000};
	_paFrame_NextEvent = new frame[35];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 35;
	orderActorToFactory(90000000, EnemyTamago01, "EnemyTamago01_1");
	orderActorToFactory(90000001, EnemyTamago01, "EnemyTamago01_2");
	orderActorToFactory(90000002, EnemyTamago01, "EnemyTamago01_3");
	orderActorToFactory(90000003, EnemyTamago01, "EnemyTamago01_4");
	orderActorToFactory(90000004, EnemyTamago01, "EnemyTamago01_5");
	orderActorToFactory(90000005, EnemyTamago01, "EnemyTamago01_6");
	orderActorToFactory(90000006, EnemyTamago01, "EnemyTamago01_7");
	orderActorToFactory(90000007, EnemyTamago01, "EnemyTamago01_8");
	orderActorToFactory(90000008, EnemyTamago01, "EnemyTamago01_9");
	orderActorToFactory(90000009, EnemyTamago01, "EnemyTamago01_10");
	orderActorToFactory(90000010, EnemyTamago01, "EnemyTamago01_11");
	orderActorToFactory(90000011, EnemyTamago01, "EnemyTamago01_12");
	orderActorToFactory(90000012, EnemyTamago01, "EnemyTamago01_13");
	orderActorToFactory(90000013, EnemyTamago01, "EnemyTamago01_14");
	orderActorToFactory(90000014, EnemyTamago01, "EnemyTamago01_15");
	orderActorToFactory(90000015, EnemyTamago01, "EnemyTamago01_16");
	orderActorToFactory(90000016, EnemyTamago01, "EnemyTamago01_17");
	orderActorToFactory(90000017, EnemyTamago01, "EnemyTamago01_18");
	orderActorToFactory(90000018, EnemyTamago01, "EnemyTamago01_19");
	orderActorToFactory(90000019, EnemyTamago01, "EnemyTamago01_20");
	orderActorToFactory(90000020, EnemyTamago01, "EnemyTamago01_21");
	orderActorToFactory(90000021, EnemyTamago01, "EnemyTamago01_22");
	orderActorToFactory(90000022, EnemyTamago01, "EnemyTamago01_23");
	orderActorToFactory(90000023, EnemyTamago01, "EnemyTamago01_24");
	orderActorToFactory(90000024, EnemyTamago01, "EnemyTamago01_25");
	orderActorToFactory(90000025, EnemyTamago01, "EnemyTamago01_26");
	orderActorToFactory(90000026, EnemyTamago01, "EnemyTamago01_27");
    // gen01 end
}

void RankUp002::initialize() {
    RankUpStage::initialize();
}

void RankUp002::processBehavior() {
    RankUpStage::processBehavior();

    // 以下の gen02 start 〜 end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 20: {
				orderActorToFactory(90000027, EnemyTamago01, "EnemyTamago01_28");
				break;
			}
			case 80: {
				orderActorToFactory(90000028, EnemyTamago01, "EnemyTamago01_29");
				break;
			}
			case 140: {
				orderActorToFactory(90000029, EnemyTamago01, "EnemyTamago01_30");
				break;
			}
			case 200: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000000);
				getDirector()->addSubGroup(pActor);
				orderActorToFactory(90000030, EnemyTamago01, "EnemyTamago01_31");
				break;
			}
			case 260: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000001);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 320: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000002);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 380: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000003);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 440: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000004);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 500: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000005);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 560: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000006);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 620: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000007);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 680: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000008);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 740: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000009);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 800: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000010);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 860: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000011);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 920: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000012);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 980: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000013);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1040: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000014);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1100: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000015);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1160: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000016);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1220: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000017);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1280: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000018);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1340: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000019);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1400: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000020);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1460: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000021);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1520: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000022);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1580: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000023);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1640: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000024);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1700: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000025);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1760: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000026);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1820: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000027);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1880: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000028);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 1940: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000029);
				getDirector()->addSubGroup(pActor);
				break;
			}
			case 2000: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000030);
				getDirector()->addSubGroup(pActor);
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
                _TRACE_("RankUp002::processBehavior() RankUpStage::PROG_PLAYING になりますた！");
            }

            if (_pProg->getFrameInProgress() == 2500) {
                _TRACE_("RankUp002::processBehavior() RankUpStage::PROG_PLAYING おわった");
                _pProg->change(RankUpStage::PROG_RESULT); //RankUpStageの共通処理へ
            }
            break;
        }
    }

}

void RankUp002::processJudgement() {
}


void RankUp002::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp002::~RankUp002() {

}
