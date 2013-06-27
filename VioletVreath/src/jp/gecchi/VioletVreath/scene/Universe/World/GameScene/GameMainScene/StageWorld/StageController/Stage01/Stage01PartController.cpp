#include "stdafx.h"
#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(4);
    _pBgmPerformer->set(0, "OGG_BGM_01_01");
    _pBgmPerformer->set(1, "OGG_BGM_01_02");
    _pBgmPerformer->set(2, "OGG_BGM_01_03");
    _pBgmPerformer->set(3, "OGG_BGM_01_CLIMAX");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,120,300,540,780,1020,1200,2300,3200,4300,5200,6300,7200,8300,9200,10300,11200,12300,13200,14300,15200,16300,17200,18300,19200,20300,21200,22300,23200,24300,25200,26300,27200,28300,29200};
	_paFrame_NextEvent = new frame[35];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 35;
	orderActorToFactory(10000000, FormationAida001, "FormationAida001-1");
	orderActorToFactory(10000016, FormationSappho001a, "FormationSappho001a-2");
	orderActorToFactory(10000017, FormationSappho001b, "FormationSappho001b-3");
	orderActorToFactory(10000018, FormationSappho001a, "FormationSappho001a-4");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->reset(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActiveFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActiveFrame()) {
			case 1: {
				break;
			}
			case 120: {
				orderActorToFactory(10000019, FormationSappho001b, "FormationSappho001b-5");
				break;
			}
			case 300: {
				FormationAida001* p = (FormationAida001*)obtainActorFromFactory(10000000);
				getSceneDirector()->addSubGroup(p);
				p->getFkBase()->locate(PX_C(800), 0, 0);
				orderActorToFactory(10000001, EnemyHermione, "EnemyHermione-6");
				FormationSappho001a* pFSap = (FormationSappho001a*)obtainActorFromFactory(10000016);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 540: {
				FormationSappho001b* pFSap = (FormationSappho001b*)obtainActorFromFactory(10000017);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 780: {
				FormationSappho001a* pFSap = (FormationSappho001a*)obtainActorFromFactory(10000018);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 1020: {
				FormationSappho001b* pFSap = (FormationSappho001b*)obtainActorFromFactory(10000019);
				getSceneDirector()->addSubGroup(pFSap);
				break;
			}
			case 1200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000001);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 2300: {
				orderActorToFactory(10000002, EnemyHermione, "EnemyHermione-7");
				break;
			}
			case 3200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000002);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 4300: {
				orderActorToFactory(10000003, EnemyHermione, "EnemyHermione-8");
				break;
			}
			case 5200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000003);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 6300: {
				orderActorToFactory(10000004, EnemyHermione, "EnemyHermione-9");
				break;
			}
			case 7200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 8300: {
				orderActorToFactory(10000005, EnemyHermione, "EnemyHermione-10");
				break;
			}
			case 9200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 10300: {
				orderActorToFactory(10000006, EnemyHermione, "EnemyHermione-11");
				break;
			}
			case 11200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 12300: {
				orderActorToFactory(10000007, EnemyHermione, "EnemyHermione-12");
				break;
			}
			case 13200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 14300: {
				orderActorToFactory(10000008, EnemyHermione, "EnemyHermione-13");
				break;
			}
			case 15200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000008);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 16300: {
				orderActorToFactory(10000009, EnemyHermione, "EnemyHermione-14");
				break;
			}
			case 17200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000009);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 18300: {
				orderActorToFactory(10000010, EnemyHermione, "EnemyHermione-15");
				break;
			}
			case 19200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000010);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 20300: {
				orderActorToFactory(10000011, EnemyHermione, "EnemyHermione-16");
				break;
			}
			case 21200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000011);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 22300: {
				orderActorToFactory(10000012, EnemyHermione, "EnemyHermione-17");
				break;
			}
			case 23200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000012);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 24300: {
				orderActorToFactory(10000013, EnemyHermione, "EnemyHermione-18");
				break;
			}
			case 25200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000013);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 26300: {
				orderActorToFactory(10000014, EnemyHermione, "EnemyHermione-19");
				break;
			}
			case 27200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000014);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			case 28300: {
				orderActorToFactory(10000015, EnemyHermione, "EnemyHermione-20");
				break;
			}
			case 29200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000015);
				getSceneDirector()->addSubGroup(p);
				p->_X = RND(000000,1000000);
				p->_Y = RND(-600000,600000);
				p->_Z = RND(-600000,600000);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 35-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01Climax_終焉の処理
                _TRACE_("STG01Climax_終焉のStage01PartController::PROG_FAINALきた");
            }

            if (_pProg->getFrameInProgress() == 60) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((Stage*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
