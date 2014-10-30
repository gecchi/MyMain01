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

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,40,100,220,340,460,580,700,820,940};
	_paFrame_NextEvent = new frame[10];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 10;
	orderActorToFactory(10000000, FormationOebius002, "FormationOebius002-1");
	orderActorToFactory(10000001, FormationOebius002, "FormationOebius002-2");
	orderActorToFactory(10000002, FormationOebius002, "FormationOebius002-3");
	orderActorToFactory(10000003, FormationOebius002, "FormationOebius002-4");
	orderActorToFactory(10000004, FormationOebius002, "FormationOebius002-5");
	orderActorToFactory(10000005, FormationOebius002, "FormationOebius002-6");
	orderActorToFactory(10000006, FormationOebius002, "FormationOebius002-7");
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
			case 40: {
				orderActorToFactory(10000007, FormationOebius002, "FormationOebius002-8");
				break;
			}
			case 100: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000000);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 220: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000001);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 340: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000002);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 460: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000003);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 580: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000004);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 700: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000005);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 820: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000006);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			case 940: {
				FormationOebius002* pF = (FormationOebius002*)obtainActorFromFactory(10000007);
				getSceneDirector()->addSubGroup(pF);
				pF->position(RND_AROUND(PX_C(2300), PX_C(2000)), RND_AROUND(0, PX_C(2000)), RND_AROUND(0, PX_C(2000)) );
				pF->setRzRyAng(RND(0, D_ANG(360)), RND(0, D_ANG(360)));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 10-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->isJustChanged()) {
                //STG01Climax_�I���̏���
                _DTRACE_("STG01Climax_�I����Stage01PartController::PROG_FAINAL����");
            }

            if (pProg->getFrameInProgress() == 60) {
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
        _DTRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _DTRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _DTRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _DTRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _DTRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE01PARTCONTROLLER_ENDING�𓊂���");
        ((DefaultScene*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //�i����Stage01PartController::PROG_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
