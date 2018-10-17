#include "StageDebugPartController.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../StageDebug.h"
#include "part/StageDebugPart01.h"
#include "part/StageDebugPart02.h"
#include "part/StageDebugPart03.h"
#include "part/StageDebugPartClimax.h"
#include "part/StageDebugPartWall.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_FAINAL ,
    PROG_BANPEI,
};

StageDebugPartController::StageDebugPartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "StageDebugPartController";

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,5,105,205,305,400,405,500,505,605,705,805,905,1005,1105};
	_paFrame_NextEvent = new frame[15];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 15;
	requestScene(10000000, StageDebugPartClimax, "StageDebugPartClimax-10000000");
	requestActor(10000001, EnemyErelmanController003, "EnemyErelmanController003-10000001");
	requestActor(10000002, EnemyEtis, "EnemyEtis-10000002");
	requestActor(10000003, EnemyEtis, "EnemyEtis-10000003");
	requestActor(10000004, EnemyEtis, "EnemyEtis-10000004");
	requestActor(10000005, EnemyEtis, "EnemyEtis-10000005");
	requestActor(10000006, EnemyEtis, "EnemyEtis-10000006");
	requestActor(10000007, EnemyEtis, "EnemyEtis-10000007");
    // gen01 end
    useProgress(PROG_BANPEI);
}

void StageDebugPartController::initialize() {
    getProgress()->reset(PROG_INIT);
}

void StageDebugPartController::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 5: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000002);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000008, EnemyEtis, "EnemyEtis-10000008");
				break;
			}
			case 105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000003);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000009, EnemyEtis, "EnemyEtis-10000009");
				break;
			}
			case 205: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000004);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000010, EnemyEtis, "EnemyEtis-10000010");
				break;
			}
			case 305: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000005);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000011, EnemyEtis, "EnemyEtis-10000011");
				break;
			}
			case 400: {
				EnemyErelmanController003* p1 = (EnemyErelmanController003*)receiveActor(10000001);
				bringSceneMediator()->appendGroupChild(p1);
				p1->setPosition(PX_C(2400), PX_C(0), PX_C(0) );
				break;
			}
			case 405: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000006);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000012, EnemyEtis, "EnemyEtis-10000012");
				break;
			}
			case 500: {
				appendChild(receiveScene(10000000));
				break;
			}
			case 505: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000007);
				bringSceneMediator()->appendGroupChild(pEtis);
				requestActor(10000013, EnemyEtis, "EnemyEtis-10000013");
				break;
			}
			case 605: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000008);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 705: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000009);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 805: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000010);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 905: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000011);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 1005: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000012);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			case 1105: {
				EnemyEtis* pEtis = (EnemyEtis*)receiveActor(10000013);
				bringSceneMediator()->appendGroupChild(pEtis);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 15-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->hasJustChanged()) {
                //STGDBGClimax_�I���̏���
                _TRACE_("STGDBGClimax_�I����StageDebugPartController::PROG_FAINAL����");
            }

            if (pProg->hasArrivedAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STAGEDEBUG_PART_CTRLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
            }
            //�C�x���g�����҂�
            break;
        }
        default :
            break;
    }
}

void StageDebugPartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STAGEDEBUG_PART_01_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_01_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //�i����StageDebugPartController::PROG_FAINAL�ɐ؂�ւ���
    } else {

    }

}

StageDebugPartController::~StageDebugPartController() {

}
