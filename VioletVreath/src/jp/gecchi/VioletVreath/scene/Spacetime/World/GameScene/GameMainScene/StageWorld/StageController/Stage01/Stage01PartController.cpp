#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01.h"
#include "part/Stage01Part01.h"
#include "part/Stage01Part02.h"
#include "part/Stage01Part03.h"
#include "part/Stage01PartClimax.h"
#include "part/Stage01PartWall.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_FAINAL ,
    PHASE_BANPEI,
};

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,5,100,105,205,300,305,400,405,500,505,605,705,805,905,1005,1105,3200,4100,7200,8100,9000,19700,20300,39700,40300};
	_paFrame_NextEvent = new frame[26];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 26;
	requestScene(10000000, Stage01Part01, "Stage01Part01-10000000");
	requestActor(10000004, EnemyOebiusController001, "EnemyOebiusController001-10000004");
	requestActor(10000005, EnemyErelmanController003, "EnemyErelmanController003-10000005");
	requestActor(10000006, EnemyErmione, "EnemyErmione-10000006");
	requestActor(10000009, EnemyEtis, "EnemyEtis-10000009");
	requestActor(10000010, EnemyEtis, "EnemyEtis-10000010");
	requestActor(10000011, EnemyEtis, "EnemyEtis-10000011");
	requestActor(10000012, EnemyEtis, "EnemyEtis-10000012");
	requestActor(10000013, EnemyEtis, "EnemyEtis-10000013");
	requestActor(10000014, EnemyEtis, "EnemyEtis-10000014");
    // gen01 end
}

void Stage01PartController::initialize() {
    getPhase()->reset(PHASE_INIT);
}

void Stage01PartController::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 5: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000009);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000015, EnemyEtis, "EnemyEtis-10000015");
				break;
			}
			case 100: {
				appendChild(receiveScene(10000000));
				break;
			}
			case 105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000010);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000016, EnemyEtis, "EnemyEtis-10000016");
				break;
			}
			case 205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000011);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000017, EnemyEtis, "EnemyEtis-10000017");
				break;
			}
			case 300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000006);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000012);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000018, EnemyEtis, "EnemyEtis-10000018");
				break;
			}
			case 400: {
				EnemyErelmanController003* p1 = (EnemyErelmanController003*)receiveActor(10000005);
				bringSceneMediator()->appendGroupChild(p1);
				p1->setPosition(PX_C(2400), PX_C(0), PX_C(0) );
				break;
			}
			case 405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000013);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000019, EnemyEtis, "EnemyEtis-10000019");
				break;
			}
			case 500: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)receiveActor(10000004);
				bringSceneMediator()->appendGroupChild(p1);
				p1->setPosition(PX_C(1400), PX_C(500), PX_C(500) );
				break;
			}
			case 505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000014);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000020, EnemyEtis, "EnemyEtis-10000020");
				break;
			}
			case 605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000015);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000016);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000017);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000018);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 1005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000019);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 1105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000020);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 3200: {
				requestScene(10000001, Stage01Part02, "Stage01Part02-10000001");
				break;
			}
			case 4100: {
				appendChild(receiveScene(10000001));
				break;
			}
			case 7200: {
				requestScene(10000002, Stage01Part03, "Stage01Part03-10000002");
				break;
			}
			case 8100: {
				appendChild(receiveScene(10000002));
				requestScene(10000003, Stage01PartClimax, "Stage01PartClimax-10000003");
				break;
			}
			case 9000: {
				appendChild(receiveScene(10000003));
				break;
			}
			case 19700: {
				requestActor(10000007, EnemyErmione, "EnemyErmione-10000007");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000007);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 39700: {
				requestActor(10000008, EnemyErmione, "EnemyErmione-10000008");
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)receiveActor(10000008);
				bringSceneMediator()->appendGroupChild(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 26-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    ScenePhase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_FAINAL: {
            if (pPhase->hasJustChanged()) {
                //STGDBGClimax_�I���̏���
                _TRACE_("STGDBGClimax_�I����Stage01PartController::PHASE_FAINAL����");
            }

            if (pPhase->hasArrivedFrameAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STAGE01_PART_CTRLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
            }
            //�C�x���g�����҂�
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    ScenePhase* pPhase = getPhase();
    if (prm_no == EVENT_STAGE01_PART_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_01_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE01_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE01_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE01_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGE01_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pPhase->change(PHASE_FAINAL); //�t�F�[�Y��Stage01PartController::PHASE_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
