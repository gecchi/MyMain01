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
    frame f[] = {1,100,2200,4000};
    _paFrame_NextEvent = new frame[4];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 4;
    orderSceneToFactory(10000000, Stage01_01, "Stage01_01");
    // gen01 end
    useProgress(10);
}

void Stage01Controller::initialize() {
    _pPrg->set(STAGE01CONTROLLER_SCENE_PROG_INIT);
}

void Stage01Controller::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
        switch (getActivePartFrame()) {
            case 1: {
                break;
            }
            case 100: {
                Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
                addSubLast(pScene);
                _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN);
                break;
            }
            case 2200: {
                orderSceneToFactory(10000001, Stage01_02, "Stage01_02");
                break;
            }
            case 4000: {
                Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
                addSubLast(pScene);
                _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN);
                break;
            }
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 4-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end


    switch (_pPrg->get()) {
        case STAGE01CONTROLLER_SCENE_PROG_INIT: {
            _TRACE_("Stage01Controller::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
            //�i���X�V�҂�
        }

        case STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN: {
            //STG01_01�J�n������
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play(0, 0, true);
            _pBgmPerformer->fadein(0, 420);
            _pPrg->changeNext();
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING: {
            //STG01_01�Œ��̏���������΂����ɋL�q
            //�i���X�V�҂�
        }


        case STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN: {
            //STG01_02�J�n������
            //BGM�O�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(0, 420);
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play(1, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(1, 420);
            _pPrg->changeNext();
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING: {
            //STG01_02�Œ��̏���������΂����ɋL�q
            //�i���X�V�҂�
        }


        case STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN: {
            //STG01_03�J�n������������΂����ɋL�q
            _pPrg->changeNext();
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING: {
            //STG01_03�Œ��̏���������΂����ɋL�q
            //�i���X�V�҂�
        }


        case STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN: {
            //STG01_Climax �J�n������
            //BGM�P�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(1, 420);
            //BGM�Q�ԃt�F�[�h�C��
            _pBgmPerformer->play(2, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(2, 420);
            _pPrg->changeNext();
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING: {
            //STG01_Climax �Œ��̏���������΂����ɋL�q
            //�i���X�V�҂�
        }


        case STAGE01CONTROLLER_SCENE_PROG_FAINAL: {
            //STG01_03�J�n������������΂����ɋL�q
            if (_pPrg->isJustChanged()) {
                //STG01_Climax�I���̏���
                _TRACE_("STG01_Climax�I����STAGE01CONTROLLER_SCENE_PROG_FAINAL����");
                _pBgmPerformer->fadeout_stop(2, 420); //BGM�P�ԃt�F�[�h�A�E�g
                _frame_prog_fainal = 0;
            }

            //STG01_Climax�I���Œ��̏���
            _frame_prog_fainal++;
            if (_frame_prog_fainal == 420) { //BGM�t�F�[�h�A�E�g��҂B
                throwEventToUpperTree(EVENT_STAGE01CONTROLLER_WAS_END, this); //�X�e�[�W�G���h����ʂɓ`����
            }
            //�C�x���g�����҂�
        }

        default :
            break;
    }


//    if (_pPrg->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_INIT)) {
//        _TRACE_("Stage01Controller::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
//
//    }
//
//    if (_pPrg->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN)) {
//        //STG01_01�J�n����
//
//        _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING);
//    } else if (_pPrg->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING) {
//        //STG01_01�Œ��̏���
//
//    }
//
//    if (_pPrg->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN)) {
//        //STG01_02�J�n����
//        _pBgmPerformer->fadeout_stop(0, 420);        //BGM�O�ԃt�F�[�h�A�E�g
//        _pBgmPerformer->play(1, GGAF_MIN_VOLUME, true);//BGM�P�ԃt�F�[�h�C��
//        _pBgmPerformer->fadein(1, 420);
//        _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING);
//    } else if (_pPrg->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING) {
//        //STG01_02�Œ��̏���
//
//    }
//
//    if (_pPrg->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN)) {
//        //STG01_03�J�n����
//
//        _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING);
//    } else if (_pPrg->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING) {
//        //STG01_03�Œ��̏���
//
//    }
//
//    if (_pPrg->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN)) {
//        //STG01_Climax�J�n����
//        _pBgmPerformer->fadeout_stop(1, 420);  //BGM�P�ԃt�F�[�h�A�E�g
//        _pBgmPerformer->play(2, GGAF_MIN_VOLUME, true); //BGM�Q�ԃt�F�[�h�C��
//        _pBgmPerformer->fadein(2, 420);
//        _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING);
//    } else if (_pPrg->get() == STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING) {
//        //STG01_Climax�Œ��̏���
//
//    }
//
//    if (_pPrg->wasChangedTo(STAGE01CONTROLLER_SCENE_PROG_FAINAL)) {
//        //STG01_Climax�I���̏���
//        _TRACE_("STG01_Climax�I����STAGE01CONTROLLER_SCENE_PROG_FAINAL����");
//        _pBgmPerformer->fadeout_stop(2, 420); //BGM�P�ԃt�F�[�h�A�E�g
//        _frame_prog_fainal = 0;
//    } else if (_pPrg->get() == STAGE01CONTROLLER_SCENE_PROG_FAINAL) {
//        //STG01_Climax�I���Œ��̏���
//        _frame_prog_fainal++;
//
//        if (_frame_prog_fainal == 420) { //BGM�t�F�[�h�A�E�g��҂B
//            throwEventToUpperTree(EVENT_STAGE01CONTROLLER_WAS_END, this); //�X�e�[�W�G���h����ʂɓ`����
//        }
//    }
//
//    if (getBehaveingFrame() == 2) {
//
//    }

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
        _pPrg->change(STAGE01CONTROLLER_SCENE_PROG_FAINAL); //�i����STAGE01CONTROLLER_SCENE_PROG_FAINAL�ɐ؂�ւ���
    } else {

    }
}

Stage01Controller::~Stage01Controller() {

}
