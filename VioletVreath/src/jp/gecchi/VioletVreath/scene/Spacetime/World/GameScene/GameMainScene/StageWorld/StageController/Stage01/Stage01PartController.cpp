#include "Stage01PartController.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/sound/BgmConductor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
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
	frame f[] = {1,300};
	_paFrame_NextEvent = new frame[2];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 2;
	requestScene(10000000, Stage01PartWall, "Stage01PartWall-10000000");
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
			case 300: {
				appendChild(receiveScene(10000000));
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 2-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
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
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_no == EVENT_STAGE01_PART_02_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_02_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_no == EVENT_STAGE01_PART_03_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_03_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_no == EVENT_STAGE01_PART_WALL_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_WALL_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
    } else if (prm_no == EVENT_STAGE01_PART_CLIMAX_WAS_FINISHED) {
        _TRACE_(FUNC_NAME<<" EVENT_STAGE01_PART_CLIMAX_WAS_FINISHED");
        ((DefaultScene*)prm_pSource)->sayonara(SEC_F(60));
        pPhase->change(PHASE_FAINAL); //�t�F�[�Y��Stage01PartController::PHASE_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
