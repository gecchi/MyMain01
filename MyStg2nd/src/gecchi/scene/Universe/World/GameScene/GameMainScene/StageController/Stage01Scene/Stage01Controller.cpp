#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

enum {
    STAGE01CONTROLLER_PROG_INIT = 1            ,
    STAGE01CONTROLLER_PROG_STG01_01_BEGIN      ,
    STAGE01CONTROLLER_PROG_STG01_01_PLAYING    ,
    STAGE01CONTROLLER_PROG_STG01_02_BEGIN      ,
    STAGE01CONTROLLER_PROG_STG01_02_PLAYING    ,
    STAGE01CONTROLLER_PROG_STG01_03_BEGIN      ,
    STAGE01CONTROLLER_PROG_STG01_03_PLAYING    ,
    STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN  ,
    STAGE01CONTROLLER_PROG_STG01_CLIMAX_PLAYING,
    STAGE01CONTROLLER_PROG_FAINAL              ,
};


Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01Controller";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // 以下の gen01 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen01 start
	frame f[] = {1,100,500,1100,1200,1700,2300,2900,3000,3500,4100,4700,5300,5900,6500,7100,7700,8200,8300,8900,10000,13200,15000,18200,20000};
	_paFrame_NextEvent = new frame[25];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 25;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01");
	orderActorToFactory(10000005, EnemyAstraea, "Astraea_1");
	orderActorToFactory(10000006, EnemyAstraea, "Astraea_2");
	orderActorToFactory(10000007, EnemyAstraea, "Astraea_3");
	orderActorToFactory(10000008, EnemyAstraea, "Astraea_4");
    // gen01 end
    useProgress(STAGE01CONTROLLER_PROG_FAINAL);
}

void Stage01Controller::initialize() {
    _pProg->set(STAGE01CONTROLLER_PROG_INIT);
}

void Stage01Controller::processBehavior() {
    // 以下の gen02 start ～ end はExcelマクロにより自動生成されたコードです。
    // コードの変更は「シーンCreater.xls」から行う事とする（整合性確保のため）。
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 100: {
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				_pProg->change(STAGE01CONTROLLER_PROG_STG01_01_BEGIN);
				EnemyAstraea* pAstraea1 = (EnemyAstraea*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(pAstraea1);
				pAstraea1->_Z = -1800000;
				pAstraea1->_Y = -100000;
				break;
			}
			case 500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000009, EnemyAstraea, "Astraea_5");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 1100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000010, EnemyAstraea, "Astraea_6");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 1200: {
				orderSceneToFactory(10000001, Stage01WalledScene, "GroStage01WalledScene");
				break;
			}
			case 1700: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000008);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000011, EnemyAstraea, "Astraea_7");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 2300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000009);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000012, EnemyAstraea, "Astraea_8");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 2900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000010);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000013, EnemyAstraea, "Astraea_9");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 3000: {
				Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(10000001);
				addSubLast(pScene);
				break;
			}
			case 3500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000011);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000014, EnemyAstraea, "Astraea_10");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 4100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000012);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000015, EnemyAstraea, "Astraea_11");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 4700: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000013);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000016, EnemyAstraea, "Astraea_12");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 5300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000014);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000017, EnemyAstraea, "Astraea_13");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 5900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000015);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000018, EnemyAstraea, "Astraea_14");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 6500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000016);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000019, EnemyAstraea, "Astraea_15");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 7100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000017);
				getDirector()->addSubGroup(pAstraea2);
				orderActorToFactory(10000020, EnemyAstraea, "Astraea_16");
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 7700: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000018);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 8200: {
				orderSceneToFactory(10000002, Stage01_02, "Stage01_02");
				break;
			}
			case 8300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000019);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 8900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000020);
				getDirector()->addSubGroup(pAstraea2);
				pAstraea2->_Z = 1800000;
				pAstraea2->_Y = 100000;
				break;
			}
			case 10000: {
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				_pProg->change(STAGE01CONTROLLER_PROG_STG01_02_BEGIN);
				break;
			}
			case 13200: {
				orderSceneToFactory(10000003, Stage01_03, "Stage01_03");
				break;
			}
			case 15000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				_pProg->change(STAGE01CONTROLLER_PROG_STG01_03_BEGIN);
				break;
			}
			case 18200: {
				orderSceneToFactory(10000004, Stage01_Climax, "Stage01_Climax");
				break;
			}
			case 20000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000004);
				addSubLast(pScene);
				_pProg->change(STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 25-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case STAGE01CONTROLLER_PROG_INIT: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01Controller::processBehavior はいはいDemoさんありがとう、私も起動しましたよ");
            }
            //進捗更新待ち
            break;
        }

        //Stage01_01
        case STAGE01CONTROLLER_PROG_STG01_01_BEGIN: {
            //BGM１番フェードイン
            _pBgmPerformer->play(0, 0, true);
            _pBgmPerformer->fadein(0, 420);
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_01_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_02
        case STAGE01CONTROLLER_PROG_STG01_02_BEGIN: {
            //BGM０番フェードアウト
            _pBgmPerformer->fadeout_stop(0, 420);
            //BGM１番フェードイン
            _pBgmPerformer->play(1, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(1, 420);
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_02_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_03
        case STAGE01CONTROLLER_PROG_STG01_03_BEGIN: {
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_03_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_Climax
        case STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN: {
            //BGM１番フェードアウト
            _pBgmPerformer->fadeout_stop(1, 420);
            //BGM２番フェードイン
            _pBgmPerformer->play(2, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(2, 420);
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_CLIMAX_PLAYING: {
            //進捗更新待ち
            break;
        }

        //Stage01_Climax の後
        case STAGE01CONTROLLER_PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01_Climax終焉の処理
                _TRACE_("STG01_Climax終焉のSTAGE01CONTROLLER_PROG_FAINALきた");
                _pBgmPerformer->fadeout_stop(2, 420); //BGM１番フェードアウト
                _frame_prog_fainal = 0;
            }
            _frame_prog_fainal++;
            if (_frame_prog_fainal == 420) { //BGMフェードアウトを待つ。
                throwEventToUpperTree(EVENT_STAGE01CONTROLLER_WAS_END); //ステージエンドを上位に伝える
            }
            //イベント発生待ち
            break;
        }
        default :
            break;
    }
}

void Stage01Controller::processFinal() {
}

void Stage01Controller::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage01_01*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKENキャッチした。STAGE01CONTROLLER_ENDINGを投げる");
        ((Stage01_Climax*)prm_pSource)->end(60*60);
        _pProg->change(STAGE01CONTROLLER_PROG_FAINAL); //進捗をSTAGE01CONTROLLER_PROG_FAINALに切り替える
    } else {

    }

}

Stage01Controller::~Stage01Controller() {

}
