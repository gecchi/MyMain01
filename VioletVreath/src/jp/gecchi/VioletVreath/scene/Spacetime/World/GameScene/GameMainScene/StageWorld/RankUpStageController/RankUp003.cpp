#include "RankUp003.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/ggaf/lib/util/SceneProgress.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
	orderActorToFactory(100000000, EnemyTamago01, "EnemyTamago01-100000000");
	orderActorToFactory(100000001, EnemyTamago01, "EnemyTamago01-100000001");
	orderActorToFactory(100000002, EnemyTamago01, "EnemyTamago01-100000002");
	orderActorToFactory(100000003, EnemyTamago01, "EnemyTamago01-100000003");
	orderActorToFactory(100000004, EnemyTamago01, "EnemyTamago01-100000004");
	orderActorToFactory(100000005, EnemyTamago01, "EnemyTamago01-100000005");
	orderActorToFactory(100000006, EnemyTamago01, "EnemyTamago01-100000006");
	orderActorToFactory(100000007, EnemyTamago01, "EnemyTamago01-100000007");
	orderActorToFactory(100000008, EnemyTamago01, "EnemyTamago01-100000008");
	orderActorToFactory(100000009, EnemyTamago01, "EnemyTamago01-100000009");
	orderActorToFactory(100000010, EnemyTamago01, "EnemyTamago01-100000010");
	orderActorToFactory(100000011, EnemyTamago01, "EnemyTamago01-100000011");
	orderActorToFactory(100000012, EnemyTamago01, "EnemyTamago01-100000012");
	orderActorToFactory(100000013, EnemyTamago01, "EnemyTamago01-100000013");
	orderActorToFactory(100000014, EnemyTamago01, "EnemyTamago01-100000014");
	orderActorToFactory(100000015, EnemyTamago01, "EnemyTamago01-100000015");
	orderActorToFactory(100000016, EnemyTamago01, "EnemyTamago01-100000016");
	orderActorToFactory(100000017, EnemyTamago01, "EnemyTamago01-100000017");
	orderActorToFactory(100000018, EnemyTamago01, "EnemyTamago01-100000018");
	orderActorToFactory(100000019, EnemyTamago01, "EnemyTamago01-100000019");
	orderActorToFactory(100000020, EnemyTamago01, "EnemyTamago01-100000020");
	orderActorToFactory(100000021, EnemyTamago01, "EnemyTamago01-100000021");
	orderActorToFactory(100000022, EnemyTamago01, "EnemyTamago01-100000022");
	orderActorToFactory(100000023, EnemyTamago01, "EnemyTamago01-100000023");
	orderActorToFactory(100000024, EnemyTamago01, "EnemyTamago01-100000024");
	orderActorToFactory(100000025, EnemyTamago01, "EnemyTamago01-100000025");
	orderActorToFactory(100000026, EnemyTamago01, "EnemyTamago01-100000026");
    // gen01 end

    getConductor()->ready(0, "OGG_RANKUP003_THEMA");
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
				orderActorToFactory(100000027, EnemyTamago01, "EnemyTamago01-100000027");
				break;
			}
			case 80: {
				orderActorToFactory(100000028, EnemyTamago01, "EnemyTamago01-100000028");
				break;
			}
			case 140: {
				orderActorToFactory(100000029, EnemyTamago01, "EnemyTamago01-100000029");
				break;
			}
			case 200: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000000);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				orderActorToFactory(100000030, EnemyTamago01, "EnemyTamago01-100000030");
				break;
			}
			case 260: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000001);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 320: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000002);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 380: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000003);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 440: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000004);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 500: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000005);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 560: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000006);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 620: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000007);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 680: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000008);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 740: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000009);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 800: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000010);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 860: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000011);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 920: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000012);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 980: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000013);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1040: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000014);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1100: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000015);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1160: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000016);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1220: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000017);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1280: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000018);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1340: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000019);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1400: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000020);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1460: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000021);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1520: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000022);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1580: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000023);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1640: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000024);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1700: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000025);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1760: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000026);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1820: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000027);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1880: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000028);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 1940: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000029);
				bringSceneMediator()->addSubGroup(pActor);
				all_hit_num_ ++;
				break;
			}
			case 2000: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(100000030);
				bringSceneMediator()->addSubGroup(pActor);
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

void RankUp003::processJudgement() {
}


void RankUp003::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp003::~RankUp003() {

}
