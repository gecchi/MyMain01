#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    STAGE01CONTROLLER_PROG_INIT = 1            ,
    STAGE01CONTROLLER_PROG_STG01_01_BEGIN      ,
    STAGE01CONTROLLER_PROG_STG01_01_PLAYING    ,
    STAGE01CONTROLLER_PROG_STG01_02_BEGIN      ,
    STAGE01CONTROLLER_PROG_STG01_02_PLAYING    ,
    STAGE01CONTROLLER_PROG_STG01_03_BEGIN      ,
    STAGE01CONTROLLER_PROG_STG01_03_PLAYING    ,
    STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN  ,
    STAGE01CONTROLLER_PROG_STG01_CLIMAX_PLAYING,
    STAGE01CONTROLLER_PROG_FAINAL              ,
};


Stage01PartController::Stage01PartController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
    frame f[] = {1,100,120,8200,10000,13200,15000,18200,20000,21200,23000};
    _paFrame_NextEvent = new frame[11];
    memcpy(_paFrame_NextEvent, f, sizeof(f));
    _event_num = 11;
    orderSceneToFactory(10000000, Stage01_01, "Stage01_01");
    orderActorToFactory(10000005, EnemyAstraea, "Astraea_1");
    // gen01 end
    useProgress(STAGE01CONTROLLER_PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->set(STAGE01CONTROLLER_PROG_INIT);
}

void Stage01PartController::processBehavior() {
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
                _pProg->change(STAGE01CONTROLLER_PROG_STG01_01_BEGIN);
                break;
            }
            case 120: {
                EnemyAstraea* pAstraea1 = (EnemyAstraea*)obtainActorFromFactory(10000005);
                getDirector()->addSubGroup(pAstraea1);
                pAstraea1->locate(3000000,0,0);
                break;
            }
            case 8200: {
                orderSceneToFactory(10000001, Stage01_02, "Stage01_02");
                break;
            }
            case 10000: {
                Stage01_02* pScene = (Stage01_02*)obtainSceneFromFactory(10000001);
                addSubLast(pScene);
                _pProg->change(STAGE01CONTROLLER_PROG_STG01_02_BEGIN);
                break;
            }
            case 13200: {
                orderSceneToFactory(10000002, Stage01_03, "Stage01_03");
                break;
            }
            case 15000: {
                Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
                addSubLast(pScene);
                _pProg->change(STAGE01CONTROLLER_PROG_STG01_03_BEGIN);
                break;
            }
            case 18200: {
                orderSceneToFactory(10000003, Stage01_Climax, "Stage01_Climax");
                break;
            }
            case 20000: {
                Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000003);
                addSubLast(pScene);
                _pProg->change(STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN);
                break;
            }
            case 21200: {
                orderSceneToFactory(10000004, Stage01WalledScene, "GroStage01WalledScene");
                break;
            }
            case 23000: {
                Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(10000004);
                addSubLast(pScene);
                break;
            }
            default :
                break;
        }
        _iCnt_Event = (_iCnt_Event < 11-1 ? _iCnt_Event+1 : _iCnt_Event);
    }
    // gen02 end


    switch (_pProg->get()) {
        case STAGE01CONTROLLER_PROG_INIT: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01PartController::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
            }
            //�i���X�V�҂�
            break;
        }

        //Stage01_01
        case STAGE01CONTROLLER_PROG_STG01_01_BEGIN: {
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play(0, 0, true);
            _pBgmPerformer->fadein(0, 420);
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_01_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_02
        case STAGE01CONTROLLER_PROG_STG01_02_BEGIN: {
            //BGM�O�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(0, 420);
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play(1, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(1, 420);
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_02_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_03
        case STAGE01CONTROLLER_PROG_STG01_03_BEGIN: {
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_03_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_Climax
        case STAGE01CONTROLLER_PROG_STG01_CLIMAX_BEGIN: {
            //BGM�P�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(1, 420);
            //BGM�Q�ԃt�F�[�h�C��
            _pBgmPerformer->play(2, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(2, 420);
            _pProg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_PROG_STG01_CLIMAX_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_Climax �̌�
        case STAGE01CONTROLLER_PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01_Climax�I���̏���
                _TRACE_("STG01_Climax�I����STAGE01CONTROLLER_PROG_FAINAL����");
            }

            if (_pProg->getFrameInProgress() == 60) {
                _pBgmPerformer->fadeout_stop(2, 60*60); //BGM�P�ԃt�F�[�h�A�E�g
                fadeoutScene(300);
                throwEventToUpperTree(EVENT_STG01_CONTROLLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
            }
            //�C�x���g�����҂�
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::processFinal() {
}

void Stage01PartController::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage01_01*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE01CONTROLLER_ENDING�𓊂���");
        ((Stage01_Climax*)prm_pSource)->end(60*60);
        _pProg->change(STAGE01CONTROLLER_PROG_FAINAL); //�i����STAGE01CONTROLLER_PROG_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
