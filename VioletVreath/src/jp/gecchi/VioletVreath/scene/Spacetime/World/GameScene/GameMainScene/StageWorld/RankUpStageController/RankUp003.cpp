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
	orderActorToFactory(110000000, EnemyTamago01, "EnemyTamago01-110000000");
	orderActorToFactory(110000001, EnemyTamago01, "EnemyTamago01-110000001");
	orderActorToFactory(110000002, EnemyTamago01, "EnemyTamago01-110000002");
	orderActorToFactory(110000003, EnemyTamago01, "EnemyTamago01-110000003");
	orderActorToFactory(110000004, EnemyTamago01, "EnemyTamago01-110000004");
	orderActorToFactory(110000005, EnemyTamago01, "EnemyTamago01-110000005");
	orderActorToFactory(110000006, EnemyTamago01, "EnemyTamago01-110000006");
	orderActorToFactory(110000007, EnemyTamago01, "EnemyTamago01-110000007");
	orderActorToFactory(110000008, EnemyTamago01, "EnemyTamago01-110000008");
	orderActorToFactory(110000009, EnemyTamago01, "EnemyTamago01-110000009");
	orderActorToFactory(110000010, EnemyTamago01, "EnemyTamago01-110000010");
	orderActorToFactory(110000011, EnemyTamago01, "EnemyTamago01-110000011");
	orderActorToFactory(110000012, EnemyTamago01, "EnemyTamago01-110000012");
	orderActorToFactory(110000013, EnemyTamago01, "EnemyTamago01-110000013");
	orderActorToFactory(110000014, EnemyTamago01, "EnemyTamago01-110000014");
	orderActorToFactory(110000015, EnemyTamago01, "EnemyTamago01-110000015");
	orderActorToFactory(110000016, EnemyTamago01, "EnemyTamago01-110000016");
	orderActorToFactory(110000017, EnemyTamago01, "EnemyTamago01-110000017");
	orderActorToFactory(110000018, EnemyTamago01, "EnemyTamago01-110000018");
	orderActorToFactory(110000019, EnemyTamago01, "EnemyTamago01-110000019");
	orderActorToFactory(110000020, EnemyTamago01, "EnemyTamago01-110000020");
	orderActorToFactory(110000021, EnemyTamago01, "EnemyTamago01-110000021");
	orderActorToFactory(110000022, EnemyTamago01, "EnemyTamago01-110000022");
	orderActorToFactory(110000023, EnemyTamago01, "EnemyTamago01-110000023");
	orderActorToFactory(110000024, EnemyTamago01, "EnemyTamago01-110000024");
	orderActorToFactory(110000025, EnemyTamago01, "EnemyTamago01-110000025");
	orderActorToFactory(110000026, EnemyTamago01, "EnemyTamago01-110000026");
    // gen01 end

    getBgmConductor()->ready(0, "OGG_RANKUP003_THEMA");
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
				orderActorToFactory(110000027, EnemyTamago01, "EnemyTamago01-110000027");
				break;
			}
			case 80: {
				orderActorToFactory(110000028, EnemyTamago01, "EnemyTamago01-110000028");
				break;
			}
			case 140: {
				orderActorToFactory(110000029, EnemyTamago01, "EnemyTamago01-110000029");
				break;
			}
			case 200: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000000);
				bringSceneMediator()->addSubGroup(pActor);
				orderActorToFactory(110000030, EnemyTamago01, "EnemyTamago01-110000030");
				break;
			}
			case 260: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000001);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 320: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000002);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 380: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000003);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 440: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000004);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 500: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000005);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 560: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000006);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 620: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000007);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 680: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000008);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 740: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000009);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 800: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000010);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 860: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000011);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 920: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000012);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 980: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000013);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1040: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000014);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1100: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000015);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1160: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000016);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1220: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000017);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1280: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000018);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1340: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000019);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1400: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000020);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1460: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000021);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1520: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000022);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1580: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000023);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1640: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000024);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1700: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000025);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1760: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000026);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1820: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000027);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1880: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000028);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 1940: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000029);
				bringSceneMediator()->addSubGroup(pActor);
				break;
			}
			case 2000: {
				EnemyTamago01* pActor = (EnemyTamago01*)obtainActorFromFactory(110000030);
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

void RankUp003::processJudgement() {
}


void RankUp003::onCatchEvent(hashval prm_no, void* prm_pSource) {
}


RankUp003::~RankUp003() {

}
