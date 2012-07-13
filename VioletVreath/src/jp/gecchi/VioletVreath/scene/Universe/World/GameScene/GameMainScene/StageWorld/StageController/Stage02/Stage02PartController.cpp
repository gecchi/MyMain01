#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02PartController::Stage02PartController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02PartController";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,3,1200,3000};
	_paFrame_NextEvent = new frame[4];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 4;
	orderSceneToFactory(60000000, Stage02_01, "Stage02_01");
    // gen01 end
    useProgress(Stage02PartController::PROG_FAINAL);
}

void Stage02PartController::initialize() {
    _pBgmPerformer->play_fadein(0, 420);
    _pProg->change(Stage02PartController::PROG_INIT);
}

void Stage02PartController::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 3: {
				Stage02_01* pScene = (Stage02_01*)obtainSceneFromFactory(60000000);
				addSubLast(pScene);
				_pProg->change(Stage02PartController::PROG_STG02_01_BEGIN);
				break;
			}
			case 1200: {
				orderSceneToFactory(60000001, Stage02_Climax, "Stage02_Climax");
				break;
			}
			case 3000: {
				Stage02_Climax* pScene = (Stage02_Climax*)obtainSceneFromFactory(60000001);
				addSubLast(pScene);
				_pProg->change(Stage02PartController::PROG_STG02_CLIMAX_BEGIN);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 4-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_INIT)) {
        _TRACE_("Stage02PartController::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_01_BEGIN)) {
        //STG0201_�J�n����

        _pProg->change(Stage02PartController::PROG_STG02_01_PLAYING);
    } else if (_pProg->get() == Stage02PartController::PROG_STG02_01_PLAYING) {
        //STG0201_�Œ��̏���

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_CLIMAX_BEGIN)) {
        //STG02Climax_�J�n����
        _pBgmPerformer->fadeout_stop(1);  //BGM�P�ԃt�F�[�h�A�E�g
        _pBgmPerformer->play_fadein(2);
        _pProg->change(Stage02PartController::PROG_STG02_CLIMAX_PLAYING);
    } else if (_pProg->get() == Stage02PartController::PROG_STG02_CLIMAX_PLAYING) {
        //STG02Climax_�Œ��̏���

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_FAINAL)) {
        //STG02Climax_�I���̏���
        _TRACE_("STG02Climax_�I����Stage02PartController::PROG_FAINAL����");
        _pBgmPerformer->fadeout_stop(2); //BGM�P�ԃt�F�[�h�A�E�g
        frame_prog_fainal_ = 0;
    } else if (_pProg->get() == Stage02PartController::PROG_FAINAL) {
        //STG02Climax_�I���Œ��̏���
        frame_prog_fainal_++;

        if (frame_prog_fainal_ == 420) { //BGM�t�F�[�h�A�E�g��҂B
            fadeoutScene(300);
            throwEventToUpperTree(EVENT_STG02_CTRLER_WAS_END, this); //�X�e�[�W�G���h����ʂɓ`����
        }
    }

    if (getBehaveingFrame() == 2) {

    }

}


void Stage02PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG02_01_WAS_BROKEN) {
        _TRACE_("Stage02PartController::onCatchEvent() EVENT_STG02_01_WAS_BROKEN");
        ((Stage02_01*)prm_pSource)->end(30*60);
    } else if (prm_no == EVENT_STG02_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage02PartController::onCatchEvent() EVENT_STG02_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE02PARTCONTROLLER_ENDING�𓊂���");
        ((Stage02_Climax*)prm_pSource)->end(30*60);
        _pProg->change(Stage02PartController::PROG_FAINAL); //�i����Stage02PartController::PROG_FAINAL�ɐ؂�ւ���
    } else {

    }
}

Stage02PartController::~Stage02PartController() {

}
