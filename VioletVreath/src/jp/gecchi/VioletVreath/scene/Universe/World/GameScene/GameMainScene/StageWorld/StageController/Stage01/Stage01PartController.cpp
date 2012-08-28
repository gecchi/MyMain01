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
	frame f[] = {1,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,500,600,700};
	_paFrame_NextEvent = new frame[32];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 32;
	orderActorToFactory(10000000, EnemyAdrastea, "Adrastea_1");
	orderActorToFactory(10000001, EnemyAdrastea, "Adrastea_2");
	orderActorToFactory(10000002, EnemyAdrastea, "Adrastea_3");
	orderActorToFactory(10000003, TestGu, "TestGu_4");
	orderActorToFactory(10000004, TestGu, "TestGu_5");
	orderActorToFactory(10000005, TestGu, "TestGu_6");
	orderActorToFactory(10000006, TestGu, "TestGu_7");
	orderActorToFactory(10000007, TestGu, "TestGu_8");
	orderActorToFactory(10000008, TestGu, "TestGu_9");
	orderActorToFactory(10000009, TestGu, "TestGu_10");
	orderActorToFactory(10000010, TestChoki, "TestChoki_11");
	orderActorToFactory(10000011, TestChoki, "TestChoki_12");
	orderActorToFactory(10000012, TestChoki, "TestChoki_13");
	orderActorToFactory(10000013, TestChoki, "TestChoki_14");
	orderActorToFactory(10000014, TestChoki, "TestChoki_15");
	orderActorToFactory(10000015, TestChoki, "TestChoki_16");
	orderActorToFactory(10000016, TestChoki, "TestChoki_17");
	orderActorToFactory(10000017, TestPa, "TestPa_18");
	orderActorToFactory(10000018, TestPa, "TestPa_19");
	orderActorToFactory(10000019, TestPa, "TestPa_20");
	orderActorToFactory(10000020, TestPa, "TestPa_21");
	orderActorToFactory(10000021, TestPa, "TestPa_22");
	orderActorToFactory(10000022, TestPa, "TestPa_23");
	orderActorToFactory(10000023, TestPa, "TestPa_24");
	orderActorToFactory(10000024, TestNomal, "TestNomal_25");
	orderActorToFactory(10000025, TestNomal, "TestNomal_26");
	orderActorToFactory(10000026, TestNomal, "TestNomal_27");
	orderActorToFactory(10000027, TestNomal, "TestNomal_28");
	orderActorToFactory(10000028, TestNomal, "TestNomal_29");
	orderActorToFactory(10000029, TestNomal, "TestNomal_30");
	orderActorToFactory(10000030, TestNomal, "TestNomal_31");
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
			case 100: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000003);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = 100000;
				break;
			}
			case 101: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = 100000;
				break;
			}
			case 102: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = 100000;
				break;
			}
			case 103: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = 100000;
				break;
			}
			case 104: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = 100000;
				break;
			}
			case 105: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000008);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = 100000;
				break;
			}
			case 106: {
				TestGu* p = (TestGu*)obtainActorFromFactory(10000009);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = 100000;
				break;
			}
			case 107: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000010);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = 0;
				break;
			}
			case 108: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000011);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = 0;
				break;
			}
			case 109: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000012);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = 0;
				break;
			}
			case 110: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000013);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = 0;
				break;
			}
			case 111: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000014);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = 0;
				break;
			}
			case 112: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000015);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = 0;
				break;
			}
			case 113: {
				TestChoki* p = (TestChoki*)obtainActorFromFactory(10000016);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = 0;
				break;
			}
			case 114: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000017);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = -100000;
				break;
			}
			case 115: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000018);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = -100000;
				break;
			}
			case 116: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000019);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = -100000;
				break;
			}
			case 117: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000020);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = -100000;
				break;
			}
			case 118: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000021);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = -100000;
				break;
			}
			case 119: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000022);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = -100000;
				break;
			}
			case 120: {
				TestPa* p = (TestPa*)obtainActorFromFactory(10000023);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = -100000;
				break;
			}
			case 121: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000024);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 300000;
				p->_Z = -200000;
				break;
			}
			case 122: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000025);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 200000;
				p->_Z = -200000;
				break;
			}
			case 123: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000026);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 100000;
				p->_Z = -200000;
				break;
			}
			case 124: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000027);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = 0;
				p->_Z = -200000;
				break;
			}
			case 125: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000028);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -100000;
				p->_Z = -200000;
				break;
			}
			case 126: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000029);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -200000;
				p->_Z = -200000;
				break;
			}
			case 127: {
				TestNomal* p = (TestNomal*)obtainActorFromFactory(10000030);
				getDirector()->addSubGroup(p);
				p->_X = 500000;
				p->_Y = -300000;
				p->_Z = -200000;
				break;
			}
			case 500: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(10000000);
				getDirector()->addSubGroup(p);
				break;
			}
			case 600: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(10000001);
				getDirector()->addSubGroup(p);
				break;
			}
			case 700: {
				EnemyAdrastea* p = (EnemyAdrastea*)obtainActorFromFactory(10000002);
				getDirector()->addSubGroup(p);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 32-1 ? _cnt_event+1 : _cnt_event);
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
