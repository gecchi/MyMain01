#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(3);
    _pBgmPerformer->set(0, "BGM_01_01");
    _pBgmPerformer->set(1, "BGM_01_02");
    _pBgmPerformer->set(2, "BGM_01_03");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,400,1000,1600,2200,2800,3400,4000,4600,5200,5800,6400,7000,7600,8200,8800,9400,10000};
	_paFrame_NextEvent = new frame[18];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 18;
	orderActorToFactory(10000000, EnemyHesperia, "EnemyHesperia_1");
	orderActorToFactory(10000001, EnemyHesperia, "EnemyHesperia_2");
	orderActorToFactory(10000002, EnemyHesperia, "EnemyHesperia_3");
    // gen01 end
    useProgress(Stage01PartController::PROG_FAINAL);
}

void Stage01PartController::initialize() {
    _pProg->set(Stage01PartController::PROG_INIT);
}

void Stage01PartController::processBehavior() {
    // �ȉ��� gen02 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen02 start
	if (getActivePartFrame() == _paFrame_NextEvent[_cnt_event]) {
		switch (getActivePartFrame()) {
			case 1: {
				break;
			}
			case 400: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000000);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000003, EnemyHesperia, "EnemyHesperia_4");
				break;
			}
			case 1000: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000001);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000004, EnemyHesperia, "EnemyHesperia_5");
				break;
			}
			case 1600: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000002);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000005, EnemyHesperia, "EnemyHesperia_6");
				break;
			}
			case 2200: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000003);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000006, EnemyHesperia, "EnemyHesperia_7");
				break;
			}
			case 2800: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000007, EnemyHesperia, "EnemyHesperia_8");
				break;
			}
			case 3400: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000008, EnemyHesperia, "EnemyHesperia_9");
				break;
			}
			case 4000: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000009, EnemyHesperia, "EnemyHesperia_10");
				break;
			}
			case 4600: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000010, EnemyHesperia, "EnemyHesperia_11");
				break;
			}
			case 5200: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000008);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000011, EnemyHesperia, "EnemyHesperia_12");
				break;
			}
			case 5800: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000009);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000012, EnemyHesperia, "EnemyHesperia_13");
				break;
			}
			case 6400: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000010);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000013, EnemyHesperia, "EnemyHesperia_14");
				break;
			}
			case 7000: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000011);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000014, EnemyHesperia, "EnemyHesperia_15");
				break;
			}
			case 7600: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000012);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000015, EnemyHesperia, "EnemyHesperia_16");
				break;
			}
			case 8200: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000013);
				getDirector()->addSubGroup(p);
				orderActorToFactory(10000016, EnemyHesperia, "EnemyHesperia_17");
				break;
			}
			case 8800: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000014);
				getDirector()->addSubGroup(p);
				break;
			}
			case 9400: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000015);
				getDirector()->addSubGroup(p);
				break;
			}
			case 10000: {
				EnemyHesperia* p = (EnemyHesperia*)obtainActorFromFactory(10000016);
				getDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 18-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case Stage01PartController::PROG_INIT: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01PartController::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
            }
            //�i���X�V�҂�
            break;
        }

        //Stage01_01
        case Stage01PartController::PROG_STG01_01_BEGIN: {
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play_fadein(0, 420);
            _pProg->changeNext();
            break;
        }
        case Stage01PartController::PROG_STG01_01_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_02
        case Stage01PartController::PROG_STG01_02_BEGIN: {
            //BGM�O�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(0);
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play_fadein(1);
            _pProg->changeNext();
            break;
        }
        case Stage01PartController::PROG_STG01_02_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_03
        case Stage01PartController::PROG_STG01_03_BEGIN: {
            _pProg->changeNext();
            break;
        }
        case Stage01PartController::PROG_STG01_03_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_Climax
        case Stage01PartController::PROG_STG01_CLIMAX_BEGIN: {
            //BGM�P�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(1);
            //BGM�Q�ԃt�F�[�h�C��
            _pBgmPerformer->play_fadein(2);
            _pProg->changeNext();
            break;
        }
        case Stage01PartController::PROG_STG01_CLIMAX_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_Climax �̌�
        case Stage01PartController::PROG_FAINAL: {
            if (_pProg->isJustChanged()) {
                //STG01Climax_�I���̏���
                _TRACE_("STG01Climax_�I����Stage01PartController::PROG_FAINAL����");
            }

            if (_pProg->getFrameInProgress() == 60) {
                _pBgmPerformer->fadeout_stop(2); //BGM2�ԃt�F�[�h�A�E�g
                fadeoutScene(300);
                throwEventToUpperTree(EVENT_STG01_CTRLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
            }
            //�C�x���g�����҂�
            break;
        }
        default :
            break;
    }
}

void Stage01PartController::onCatchEvent(hashval prm_no, void* prm_pSource) {
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
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE01PARTCONTROLLER_ENDING�𓊂���");
        ((Stage01_Climax*)prm_pSource)->end(60*60);
        _pProg->change(Stage01PartController::PROG_FAINAL); //�i����Stage01PartController::PROG_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
