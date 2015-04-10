#include "Stage02PartController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "../Stage02.h"
#include "part/Stage02_01.h"
#include "part/Stage02_Climax.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02PartController::Stage02PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage02PartController";
    getBGMer()->ready(0, "OGG_BGM_01_01");
    getBGMer()->ready(1, "OGG_BGM_01_02");
    getBGMer()->ready(2, "OGG_BGM_01_03");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,3,2100,3000};
	_paFrame_NextEvent = new frame[4];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 4;
	orderSceneToFactory(60000000, Stage02_01, "Stage02_01-1");
    // gen01 end
    useProgress(Stage02PartController::PROG_BANPEI-1);
}

void Stage02PartController::initialize() {
    getBGMer()->play_fadein(0);
    getProgress()->change(Stage02PartController::PROG_INIT);
}

void Stage02PartController::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getBehaveingFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getBehaveingFrame()) {
			case 1: {
				break;
			}
			case 3: {
				Stage02_01* pScene = (Stage02_01*)obtainSceneFromFactory(60000000);
				addSubLast(pScene);
				_pBgmPerformer->play_fadein(0);
				break;
			}
			case 2100: {
				orderSceneToFactory(60000001, Stage02_Climax, "Stage02_Climax-2");
				break;
			}
			case 3000: {
				Stage02_Climax* pScene = (Stage02_Climax*)obtainSceneFromFactory(60000001);
				addSubLast(pScene);
				_pBgmPerformer->fadeout_stop(0);
				_pBgmPerformer->play_fadein(1);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FAINAL: {
            if (pProg->hasJustChanged()) {
                //STG01Climax_�I���̏���
                _TRACE_("Stage02PartController::PROG_FAINAL����");
            }
            if (pProg->hasArrivedAt(60)) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG02_CTRLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
            }
            break;
        }
        default :
            break;
    }

}


void Stage02PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STG02_01_WAS_BROKEN) {
        _TRACE_("Stage02PartController::onCatchEvent() EVENT_STG02_01_WAS_BROKEN");
        ((Stage*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG02_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage02PartController::onCatchEvent() EVENT_STG02_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE02PARTCONTROLLER_ENDING�𓊂���");
        ((Stage*)prm_pSource)->sayonara(60*60);
        pProg->change(PROG_FAINAL); //�i����Stage02PartController::PROG_FAINAL�ɐ؂�ւ���
    } else {

    }
}

Stage02PartController::~Stage02PartController() {

}
