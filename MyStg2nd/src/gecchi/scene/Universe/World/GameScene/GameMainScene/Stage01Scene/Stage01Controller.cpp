#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01Controller";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,100,200,1000,1200,2000,2200,3000,4000};
	_paFrame_NextEvent = new frame[9];
	for (int i = 0; i < 9; i++) {
		_paFrame_NextEvent[i] = f[i];
	}
	orderSceneToFactory(11017100, Stage01_01, "Stage01_01");
	orderSceneToFactory(110271000, Stage01WalledScene, "GroStage01WalledScene");
	orderActorToFactory(11076100, EnemyAstraea, "Astraea_1");
    // gen01 end
    useProgress(10);
}

void Stage01Controller::initialize() {
    _pBgmPerformer->play(0, DSBVOLUME_MIN, true);
    _pBgmPerformer->fadein(0, 420);
    _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_INIT);
}

void Stage01Controller::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
		switch (getActivePartFrame()) {
			case 1:
				break;
			case 100:
				{
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(11017100);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN);
				}
				{
				EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(11076100);
				getLordActor()->addSubGroup(pActor);
				pActor->_Z = -1800000;
				pActor->_Y = -100000;
				}
				break;
			case 200:
				orderSceneToFactory(110372000, Stage01_02, "Stage01_02");
				break;
			case 1000:
				{
				Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(110271000);
				addSubLast(pScene);
				}
				break;
			case 1200:
				orderSceneToFactory(110473000, Stage01_03, "Stage01_03");
				break;
			case 2000:
				{
				Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(110372000);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN);
				}
				break;
			case 2200:
				orderSceneToFactory(110574000, Stage01_Climax, "Stage01_Climax");
				break;
			case 3000:
				{
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(110473000);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN);
				}
				break;
			case 4000:
				{
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(110574000);
				addSubLast(pScene);
				_pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN);
				}
				break;
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 9-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_INIT)) {
        _TRACE_("Stage01Controller::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN)) {
        //STG01_01�J�n����

        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING) {
        //STG01_01�Œ��̏���

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN)) {
        //STG01_02�J�n����
        _pBgmPerformer->fadeout_stop(0, 420);        //BGM�O�ԃt�F�[�h�A�E�g
        _pBgmPerformer->play(1, DSBVOLUME_MIN, true);//BGM�P�ԃt�F�[�h�C��
        _pBgmPerformer->fadein(1, 420);
        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING) {
        //STG01_02�Œ��̏���

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN)) {
        //STG01_03�J�n����

        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING) {
        //STG01_03�Œ��̏���

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN)) {
        //STG01_Climax�J�n����
        _pBgmPerformer->fadeout_stop(1, 420);  //BGM�P�ԃt�F�[�h�A�E�g
        _pBgmPerformer->play(2, DSBVOLUME_MIN, true); //BGM�Q�ԃt�F�[�h�C��
        _pBgmPerformer->fadein(2, 420);
        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING);
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING) {
        //STG01_Climax�Œ��̏���

    }

    if (_pProgress->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_FAINAL)) {
        //STG01_Climax�I���̏���
        _TRACE_("STG01_Climax�I����STAGE01CONTROLLER_SCENE_PROG_FAINAL����");
        _pBgmPerformer->fadeout_stop(2, 420); //BGM�P�ԃt�F�[�h�A�E�g
        _frame_prog_fainal = 0;
    } else if (_pProgress->get() == STAGE01CONTROLLER_SCENE_PROG_FAINAL) {
        //STG01_Climax�I���Œ��̏���
        _frame_prog_fainal++;

        if (_frame_prog_fainal == 420) { //BGM�t�F�[�h�A�E�g��҂B
            throwEventToUpperTree(EVENT_STAGE01CONTROLLER_WAS_END, this); //�X�e�[�W�G���h����ʂɓ`����
        }
    }

    if (getBehaveingFrame() == 2) {

    }

}

void Stage01Controller::processFinal() {
}

void Stage01Controller::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage01_01*)prm_pSource)->end(3000*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->end(30*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->end(30*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE01CONTROLLER_ENDING�𓊂���");
        ((Stage01_Climax*)prm_pSource)->end(30*60);
        _pProgress->change(STAGE01CONTROLLER_SCENE_PROG_FAINAL); //�i����STAGE01CONTROLLER_SCENE_PROG_FAINAL�ɐ؂�ւ���
    } else {

    }
}

Stage01Controller::~Stage01Controller() {

}
