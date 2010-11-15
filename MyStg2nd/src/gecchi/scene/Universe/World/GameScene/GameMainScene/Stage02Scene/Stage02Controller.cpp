#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage02Controller::Stage02Controller(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage02Controller";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
    frame f[] = {1,3,1200,3000};
    _paFrame_NextEvent = new frame[4];
    for (int i = 0; i < 4; i++) {
        _paFrame_NextEvent[i] = f[i];
    }
    orderSceneToFactory(510273, Stage02_01, "Stage02_01");
    // gen01 end
}

void Stage02Controller::initialize() {
    _pBgmPerformer->play(0, DSBVOLUME_MIN, true);
    _pBgmPerformer->fadein(0, 420);
    changeProgress(STAGE02CONTROLLER_SCENE_PROG_INIT);
}

void Stage02Controller::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
        switch (getActivePartFrame()) {
            case 1:
                break;
            case 3:
                {
                Stage02_01* pScene = (Stage02_01*)obtainSceneFromFactory(510273);
                addSubLast(pScene);
                changeProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_01_BEGIN);
                }
                break;
            case 1200:
                orderSceneToFactory(510373000, Stage02_Climax, "Stage01_Climax");
                break;
            case 3000:
                {
                Stage02_Climax* pScene = (Stage02_Climax*)obtainSceneFromFactory(510373000);
                addSubLast(pScene);
                changeProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_CLIMAX_BEGIN);
                }
                break;
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end

    if (onActiveProgress(STAGE02CONTROLLER_SCENE_PROG_INIT)) {
        _TRACE_("Stage02Controller::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");

    }

    if (onActiveProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_01_BEGIN)) {
        //STG02_01�J�n����

        changeProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_01_PLAYING);
    } else if (getProgress() == STAGE02CONTROLLER_SCENE_PROG_STG02_01_PLAYING) {
        //STG02_01�Œ��̏���

    }

//    if (onActiveProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_02_BEGIN)) {
//        //STG02_02�J�n����
//        _pBgmPerformer->fadeout_stop(0, 420);        //BGM�O�ԃt�F�[�h�A�E�g
//        _pBgmPerformer->play(1, DSBVOLUME_MIN, true);//BGM�P�ԃt�F�[�h�C��
//        _pBgmPerformer->fadein(1, 420);
//        changeProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_02_PLAYING);
//    } else if (getProgress() == STAGE02CONTROLLER_SCENE_PROG_STG02_02_PLAYING) {
//        //STG02_02�Œ��̏���
//
//    }
//
//    if (onActiveProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_03_BEGIN)) {
//        //STG02_03�J�n����
//
//        changeProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_03_PLAYING);
//    } else if (getProgress() == STAGE02CONTROLLER_SCENE_PROG_STG02_03_PLAYING) {
//        //STG02_03�Œ��̏���
//
//    }

    if (onActiveProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_CLIMAX_BEGIN)) {
        //STG02_Climax�J�n����
        _pBgmPerformer->fadeout_stop(1, 420);  //BGM�P�ԃt�F�[�h�A�E�g
        _pBgmPerformer->play(2, DSBVOLUME_MIN, true); //BGM�Q�ԃt�F�[�h�C��
        _pBgmPerformer->fadein(2, 420);
        changeProgress(STAGE02CONTROLLER_SCENE_PROG_STG02_CLIMAX_PLAYING);
    } else if (getProgress() == STAGE02CONTROLLER_SCENE_PROG_STG02_CLIMAX_PLAYING) {
        //STG02_Climax�Œ��̏���

    }

    if (onActiveProgress(STAGE02CONTROLLER_SCENE_PROG_FAINAL)) {
        //STG02_Climax�I���̏���
        _TRACE_("STG02_Climax�I����STAGE02CONTROLLER_SCENE_PROG_FAINAL����");
        _pBgmPerformer->fadeout_stop(2, 420); //BGM�P�ԃt�F�[�h�A�E�g
        _frame_prog_fainal = 0;
    } else if (getProgress() == STAGE02CONTROLLER_SCENE_PROG_FAINAL) {
        //STG02_Climax�I���Œ��̏���
        _frame_prog_fainal++;

        if (_frame_prog_fainal == 420) { //BGM�t�F�[�h�A�E�g��҂B
            throwEventToUpperTree(EVENT_STAGE02CONTROLLER_WAS_END, this); //�X�e�[�W�G���h����ʂɓ`����
        }
    }

    if (getBehaveingFrame() == 2) {

    }

}

void Stage02Controller::processFinal() {
}

void Stage02Controller::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG02_01_WAS_BROKEN) {
        _TRACE_("Stage02Controller::catchEvent() EVENT_STG02_01_WAS_BROKEN");
        ((Stage02_01*)prm_pSource)->end(30*60);
    } else if (prm_no == EVENT_STG02_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage02Controller::catchEvent() EVENT_STG02_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE02CONTROLLER_ENDING�𓊂���");
        ((Stage02_Climax*)prm_pSource)->end(30*60);
        changeProgress(STAGE02CONTROLLER_SCENE_PROG_FAINAL); //�i����STAGE02CONTROLLER_SCENE_PROG_FAINAL�ɐ؂�ւ���
    } else {

    }
}

Stage02Controller::~Stage02Controller() {

}
