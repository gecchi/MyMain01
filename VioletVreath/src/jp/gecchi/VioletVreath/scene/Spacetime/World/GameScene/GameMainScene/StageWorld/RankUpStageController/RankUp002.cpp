#include "RankUp002.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/ggaf/lib/util/SceneProgress.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
	orderActorToFactory(90000000, EnemyTamago01, "EnemyTamago01-90000000");
	orderActorToFactory(90000001, EnemyTamago01, "EnemyTamago01-90000001");
	orderActorToFactory(90000002, EnemyTamago01, "EnemyTamago01-90000002");
	orderActorToFactory(90000003, EnemyTamago01, "EnemyTamago01-90000003");
	orderActorToFactory(90000004, EnemyTamago01, "EnemyTamago01-90000004");
	orderActorToFactory(90000005, EnemyTamago01, "EnemyTamago01-90000005");
	orderActorToFactory(90000006, EnemyTamago01, "EnemyTamago01-90000006");
	orderActorToFactory(90000007, EnemyTamago01, "EnemyTamago01-90000007");
	orderActorToFactory(90000008, EnemyTamago01, "EnemyTamago01-90000008");
	orderActorToFactory(90000009, EnemyTamago01, "EnemyTamago01-90000009");
	orderActorToFactory(90000010, EnemyTamago01, "EnemyTamago01-90000010");
	orderActorToFactory(90000011, EnemyTamago01, "EnemyTamago01-90000011");
	orderActorToFactory(90000012, EnemyTamago01, "EnemyTamago01-90000012");
	orderActorToFactory(90000013, EnemyTamago01, "EnemyTamago01-90000013");
	orderActorToFactory(90000014, EnemyTamago01, "EnemyTamago01-90000014");
	orderActorToFactory(90000015, EnemyTamago01, "EnemyTamago01-90000015");
	orderActorToFactory(90000016, EnemyTamago01, "EnemyTamago01-90000016");
	orderActorToFactory(90000017, EnemyTamago01, "EnemyTamago01-90000017");
	orderActorToFactory(90000018, EnemyTamago01, "EnemyTamago01-90000018");
	orderActorToFactory(90000019, EnemyTamago01, "EnemyTamago01-90000019");
	orderActorToFactory(90000020, EnemyTamago01, "EnemyTamago01-90000020");
	orderActorToFactory(90000021, EnemyTamago01, "EnemyTamago01-90000021");
	orderActorToFactory(90000022, EnemyTamago01, "EnemyTamago01-90000022");
	orderActorToFactory(90000023, EnemyTamago01, "EnemyTamago01-90000023");
	orderActorToFactory(90000024, EnemyTamago01, "EnemyTamago01-90000024");
	orderActorToFactory(90000025, EnemyTamago01, "EnemyTamago01-90000025");
	orderActorToFactory(90000026, EnemyTamago01, "EnemyTamago01-90000026");
    // gen01 end

    getBgmPerformer()->ready(0, "OGG_RANKUP002_THEMA");
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
				orderActorToFactory(90000027, EnemyTamago01, "EnemyTamago01-90000027");
				break;
			}
			case 80: {
				orderActorToFactory(90000028, EnemyTamago01, "EnemyTamago01-90000028");
				break;
			}
			case 140: {
				orderActorToFactory(90000029, EnemyTamago01, "EnemyTamago01-90000029");
				break;
			}
			case 200: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000000);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				orderActorToFactory(90000030, EnemyTamago01, "EnemyTamago01-90000030");
				break;
			}
			case 260: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000001);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 320: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000002);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 380: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000003);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 440: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000004);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 500: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000005);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 560: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000006);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 620: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000007);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 680: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000008);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 740: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000009);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 800: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000010);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 860: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000011);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 920: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000012);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 980: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000013);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1040: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000014);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1100: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000015);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1160: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000016);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1220: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000017);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1280: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000018);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1340: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000019);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1400: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000020);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1460: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000021);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1520: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000022);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1580: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000023);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1640: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000024);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1700: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000025);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1760: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000026);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1820: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000027);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1880: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000028);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1940: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000029);
				bringDirector()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 2000: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(90000030);
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

void RankUp002::processJudgement() {
}


void RankUp002::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp002::~RankUp002() {

}
