#include "stdafx.h"
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
	frame f[] = {1,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127};
	_paFrame_NextEvent = new frame[29];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 29;
	orderActorToFactory(10000000, TestGu, "TestGu-1");
	orderActorToFactory(10000001, TestGu, "TestGu-2");
	orderActorToFactory(10000002, TestGu, "TestGu-3");
	orderActorToFactory(10000003, TestGu, "TestGu-4");
	orderActorToFactory(10000004, TestGu, "TestGu-5");
	orderActorToFactory(10000005, TestGu, "TestGu-6");
	orderActorToFactory(10000006, TestGu, "TestGu-7");
	orderActorToFactory(10000007, TestChoki, "TestChoki-8");
	orderActorToFactory(10000008, TestChoki, "TestChoki-9");
	orderActorToFactory(10000009, TestChoki, "TestChoki-10");
	orderActorToFactory(10000010, TestChoki, "TestChoki-11");
	orderActorToFactory(10000011, TestChoki, "TestChoki-12");
	orderActorToFactory(10000012, TestChoki, "TestChoki-13");
	orderActorToFactory(10000013, TestChoki, "TestChoki-14");
	orderActorToFactory(10000014, TestPa, "TestPa-15");
	orderActorToFactory(10000015, TestPa, "TestPa-16");
	orderActorToFactory(10000016, TestPa, "TestPa-17");
	orderActorToFactory(10000017, TestPa, "TestPa-18");
	orderActorToFactory(10000018, TestPa, "TestPa-19");
	orderActorToFactory(10000019, TestPa, "TestPa-20");
	orderActorToFactory(10000020, TestPa, "TestPa-21");
	orderActorToFactory(10000021, TestNomal, "TestNomal-22");
	orderActorToFactory(10000022, TestNomal, "TestNomal-23");
	orderActorToFactory(10000023, TestNomal, "TestNomal-24");
	orderActorToFactory(10000024, TestNomal, "TestNomal-25");
	orderActorToFactory(10000025, TestNomal, "TestNomal-26");
	orderActorToFactory(10000026, TestNomal, "TestNomal-27");
	orderActorToFactory(10000027, TestNomal, "TestNomal-28");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->set(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000000);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = 100000;
				break;
			}
			case 101: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000001);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = 100000;
				break;
			}
			case 102: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000002);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = 100000;
				break;
			}
			case 103: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000003);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = 100000;
				break;
			}
			case 104: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = 100000;
				break;
			}
			case 105: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = 100000;
				break;
			}
			case 106: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = 100000;
				break;
			}
			case 107: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = 0;
				break;
			}
			case 108: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000008);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = 0;
				break;
			}
			case 109: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000009);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = 0;
				break;
			}
			case 110: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000010);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = 0;
				break;
			}
			case 111: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000011);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = 0;
				break;
			}
			case 112: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000012);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = 0;
				break;
			}
			case 113: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000013);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = 0;
				break;
			}
			case 114: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000014);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = -100000;
				break;
			}
			case 115: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000015);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = -100000;
				break;
			}
			case 116: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000016);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = -100000;
				break;
			}
			case 117: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000017);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = -100000;
				break;
			}
			case 118: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000018);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = -100000;
				break;
			}
			case 119: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000019);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = -100000;
				break;
			}
			case 120: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000020);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = -100000;
				break;
			}
			case 121: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000021);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = -200000;
				break;
			}
			case 122: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000022);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = -200000;
				break;
			}
			case 123: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000023);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = -200000;
				break;
			}
			case 124: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000024);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = -200000;
				break;
			}
			case 125: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000025);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = -200000;
				break;
			}
			case 126: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000026);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = -200000;
				break;
			}
			case 127: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000027);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = -200000;
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 29-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->hasJustChanged()) {
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
        ((Stage01_01*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((Stage01WalledScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01PARTCONTROLLER_ENDINGを投げる");
        ((Stage01_Climax*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //進捗をStage01PartController::PROG_FAINALに切り替える
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
