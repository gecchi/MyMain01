#include "stdafx.h"
using namespace std;
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
    frame f[] = {1,3,100,1200,3000};
    _paFrame_NextEvent = new frame[5];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 5;
    orderSceneToFactory(60000000, Stage02_01, "Stage02_01");
    orderActorToFactory(60000002, EnemyAstraea, "Astraea_1");
    // gen01 end
    useProgress(Stage02PartController::PROG_FAINAL);
}

void Stage02PartController::initialize() {
    _pBgmPerformer->play(0, GGAF_MIN_VOLUME, true);
    _pBgmPerformer->fadein(0, 420);
    _pProg->change(Stage02PartController::PROG_INIT);
}

void Stage02PartController::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
    if (getActivePartFrame() == _paFrame_NextEvent[_iCnt_Event]) {
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
            case 100: {
                EnemyAstraea* pActor = (EnemyAstraea*)obtainActorFromFactory(60000002);
                getDirector()->addSubGroup(pActor);
                pActor->_Z = -1800000;
                pActor->_Y = -100000;
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
        _iCnt_Event = (_iCnt_Event < 5-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_INIT)) {
        _TRACE_("Stage02PartController::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_01_BEGIN)) {
        //STG02_01�J�n����

        _pProg->change(Stage02PartController::PROG_STG02_01_PLAYING);
    } else if (_pProg->get() == Stage02PartController::PROG_STG02_01_PLAYING) {
        //STG02_01�Œ��̏���

    }

//    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_02_BEGIN)) {
//        //STG02_02�J�n����
//        _pBgmPerformer->fadeout_stop(0, 420);        //BGM�O�ԃt�F�[�h�A�E�g
//        _pBgmPerformer->play(1, GGAF_MIN_VOLUME, true);//BGM�P�ԃt�F�[�h�C��
//        _pBgmPerformer->fadein(1, 420);
//        _pProg->change(Stage02PartController::PROG_STG02_02_PLAYING);
//    } else if (_pProg->get() == Stage02PartController::PROG_STG02_02_PLAYING) {
//        //STG02_02�Œ��̏���
//
//    }
//
//    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_03_BEGIN)) {
//        //STG02_03�J�n����
//
//        _pProg->change(Stage02PartController::PROG_STG02_03_PLAYING);
//    } else if (_pProg->get() == Stage02PartController::PROG_STG02_03_PLAYING) {
//        //STG02_03�Œ��̏���
//
//    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_STG02_CLIMAX_BEGIN)) {
        //STG02_Climax�J�n����
        _pBgmPerformer->fadeout_stop(1, 420);  //BGM�P�ԃt�F�[�h�A�E�g
        _pBgmPerformer->play(2, GGAF_MIN_VOLUME, true); //BGM�Q�ԃt�F�[�h�C��
        _pBgmPerformer->fadein(2, 420);
        _pProg->change(Stage02PartController::PROG_STG02_CLIMAX_PLAYING);
    } else if (_pProg->get() == Stage02PartController::PROG_STG02_CLIMAX_PLAYING) {
        //STG02_Climax�Œ��̏���

    }

    if (_pProg->isJustChangedTo(Stage02PartController::PROG_FAINAL)) {
        //STG02_Climax�I���̏���
        _TRACE_("STG02_Climax�I����Stage02PartController::PROG_FAINAL����");
        _pBgmPerformer->fadeout_stop(2, 420); //BGM�P�ԃt�F�[�h�A�E�g
        _frame_prog_fainal = 0;
    } else if (_pProg->get() == Stage02PartController::PROG_FAINAL) {
        //STG02_Climax�I���Œ��̏���
        _frame_prog_fainal++;

        if (_frame_prog_fainal == 420) { //BGM�t�F�[�h�A�E�g��҂B
            fadeoutScene(300);
            throwEventToUpperTree(EVENT_STG02_CONTROLLER_WAS_END, this); //�X�e�[�W�G���h����ʂɓ`����
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
