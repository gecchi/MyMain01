#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
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


Stage01Controller::Stage01Controller(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "Stage01Controller";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,200,560,800,1040,1280,1520,1760,2000};
	_paFrame_NextEvent = new frame[9];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 9;
	orderActorToFactory(10000000, FormationEunomia001a, "F001a_Eunomia_1");
	orderActorToFactory(10000001, FormationEunomia001b, "F001b_Eunomia_2");
	orderActorToFactory(10000002, FormationEunomia001a, "F001a_Eunomia_3");
	orderActorToFactory(10000003, FormationEunomia001b, "F001b_Eunomia_4");
	orderActorToFactory(10000004, FormationEunomia001a, "F001a_Eunomia_5");
	orderActorToFactory(10000005, FormationEunomia001b, "F001b_Eunomia_6");
	orderActorToFactory(10000006, FormationEunomia001a, "F001a_Eunomia_7");
    // gen01 end
    useProgress(STAGE01CONTROLLER_PROG_FAINAL);
}

void Stage01Controller::initialize() {
    _pProg->set(STAGE01CONTROLLER_PROG_INIT);
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
			case 200: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000000);
				getDirector()->addSubGroup(pFormation);
				orderActorToFactory(10000007, FormationEunomia001b, "F001b_Eunomia_8");
				break;
			}
			case 560: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000001);
				getDirector()->addSubGroup(pFormation);
				break;
			}
			case 800: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000002);
				getDirector()->addSubGroup(pFormation);
				break;
			}
			case 1040: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000003);
				getDirector()->addSubGroup(pFormation);
				break;
			}
			case 1280: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(pFormation);
				break;
			}
			case 1520: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(pFormation);
				break;
			}
			case 1760: {
				FormationEunomia001a* pFormation = (FormationEunomia001a*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(pFormation);
				break;
			}
			case 2000: {
				FormationEunomia001b* pFormation = (FormationEunomia001b*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(pFormation);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 9-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case STAGE01CONTROLLER_PROG_INIT: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01Controller::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
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
                _pBgmPerformer->fadeout_stop(2, 420); //BGM�P�ԃt�F�[�h�A�E�g
                _frame_prog_fainal = 0;
            }
            _frame_prog_fainal++;
            if (_frame_prog_fainal == 420) { //BGM�t�F�[�h�A�E�g��҂B
                throwEventToUpperTree(EVENT_STAGE01CONTROLLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
            }
            //�C�x���g�����҂�
            break;
        }
        default :
            break;
    }
}

void Stage01Controller::processFinal() {
}

void Stage01Controller::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_01_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_01_WAS_BROKEN");
        ((Stage01_01*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->end(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01Controller::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE01CONTROLLER_ENDING�𓊂���");
        ((Stage01_Climax*)prm_pSource)->end(60*60);
        _pProg->change(STAGE01CONTROLLER_PROG_FAINAL); //�i����STAGE01CONTROLLER_PROG_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01Controller::~Stage01Controller() {

}
