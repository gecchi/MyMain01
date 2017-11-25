#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage01.h"
#include "part/Stage01_01.h"
#include "part/Stage01_02.h"
#include "part/Stage01_03.h"
#include "part/Stage01_Climax.h"
#include "part/Stage01WalledScene.h"
#include "part/Stage01WallScene.h"

#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshTestActor.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,100,300,500,600,1000,9100,10000,19700,20300,29100,30000,39100,39700,40000,40300};
	_paFrame_NextEvent = new frame[16];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 16;
	orderSceneToFactory(10000004, Stage01WallScene, "Stage01WallScene-10000004");
	orderActorToFactory(10000005, EnemyOebiusController001, "EnemyOebiusController001-10000005");
	orderActorToFactory(10000006, EnemyOebiusController002, "EnemyOebiusController002-10000006");
	orderActorToFactory(10000007, EnemyErmione, "EnemyErmione-10000007");
    // gen01 end
    useProgress(Stage01PartController::PROG_BANPEI-1);
}

void Stage01PartController::initialize() {
    getProgress()->reset(Stage01PartController::PROG_INIT);
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
			case 100: {
				orderSceneToFactory(10000000, Stage01_01, "Stage01_01-10000000");
				break;
			}
			case 300: {
				addSubLast(obtainSceneFromFactory(10000004));
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000007);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 500: {
				EnemyOebiusController001* p1 = (EnemyOebiusController001*)obtainActorFromFactory(10000005);
				bringDirector()->addSubGroup(p1);
				p1->setPosition(PX_C(800), PX_C(100), PX_C(400) );
				break;
			}
			case 600: {
				EnemyOebiusController002* p2 = (EnemyOebiusController002*)obtainActorFromFactory(10000006);
				bringDirector()->addSubGroup(p2);
				p2->setPosition(PX_C(800), PX_C(400), PX_C(100) );
				break;
			}
			case 1000: {
				addSubLast(obtainSceneFromFactory(10000000));
				break;
			}
			case 9100: {
				orderSceneToFactory(10000001, Stage01_02, "Stage01_02-10000001");
				break;
			}
			case 10000: {
				addSubLast(obtainSceneFromFactory(10000001));
				break;
			}
			case 19700: {
				orderActorToFactory(10000008, EnemyErmione, "EnemyErmione-10000008");
				break;
			}
			case 20300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000008);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			case 29100: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03-10000002");
				break;
			}
			case 30000: {
				addSubLast(obtainSceneFromFactory(10000002));
				break;
			}
			case 39100: {
				orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax-10000003");
				break;
			}
			case 39700: {
				orderActorToFactory(10000009, EnemyErmione, "EnemyErmione-10000009");
				break;
			}
			case 40000: {
				addSubLast(obtainSceneFromFactory(10000003));
				break;
			}
			case 40300: {
				EnemyErmione* pE = (EnemyErmione*)obtainActorFromFactory(10000009);
				bringDirector()->addSubGroup(pE);
				pE->_x = RND(1000000,4000000);
				pE->_y = RND(-6000000,6000000);
				pE->_z = RND(-6000000,6000000);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 16-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->hasJustChanged()) {
                //STG01Climax_�I���̏���
                _TRACE_("STG01Climax_�I����Stage01PartController::PROG_FAINAL����");
            }

            if (pProg->hasArrivedAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
            }
            //�C�x���g�����҂�
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_01_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_02_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_03_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_WALLED_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_(FUNC_NAME<<" EVENT_STG01_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE01PARTCONTROLLER_ENDING�𓊂���");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //�i����Stage01PartController::PROG_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
