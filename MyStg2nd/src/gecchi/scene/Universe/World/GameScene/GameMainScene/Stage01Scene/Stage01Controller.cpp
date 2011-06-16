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
	frame f[] = {1,500,1100,1700,2300,2900,3500,4100,4700,5300,5900,6500,7100,7700,8300,8900};
	_paFrame_NextEvent = new frame[16];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 16;
	orderActorToFactory(10000000, EnemyAstraea, "Astraea_1");
	orderActorToFactory(10000001, EnemyAstraea, "Astraea_2");
	orderActorToFactory(10000002, EnemyAstraea, "Astraea_3");
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
			case 500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000000);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000003, EnemyAstraea, "Astraea_4");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 1100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000001);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000004, EnemyAstraea, "Astraea_5");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 1700: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000002);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000005, EnemyAstraea, "Astraea_6");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 2300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000003);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000006, EnemyAstraea, "Astraea_7");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 2900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000004);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000007, EnemyAstraea, "Astraea_8");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 3500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000005);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000008, EnemyAstraea, "Astraea_9");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 4100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000006);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000009, EnemyAstraea, "Astraea_10");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 4700: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000007);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000010, EnemyAstraea, "Astraea_11");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 5300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000008);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000011, EnemyAstraea, "Astraea_12");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 5900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000009);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000012, EnemyAstraea, "Astraea_13");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 6500: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000010);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000013, EnemyAstraea, "Astraea_14");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 7100: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000011);
				getLordActor()->addSubGroup(pAstraea2);
				orderActorToFactory(10000014, EnemyAstraea, "Astraea_15");
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 7700: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000012);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 8300: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000013);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			case 8900: {
				EnemyAstraea* pAstraea2 = (EnemyAstraea*)obtainActorFromFactory(10000014);
				getLordActor()->addSubGroup(pAstraea2);
				pAstraea2->_Z = LONG_RND(-1800000, 1800000);
				pAstraea2->_Y = LONG_RND(-1000000, 1000000);
				break;
			}
			default :
				break;
		}
		_iCnt_Event = (_iCnt_Event < 16-1 ? _iCnt_Event+1 : _iCnt_Event);
	}
    // gen02 end


    switch (_pPrg->get()) {
        case STAGE01CONTROLLER_SCENE_PROG_INIT: {
            if (_pPrg->isJustChanged()) {
                _TRACE_("Stage01Controller::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
            }
            //�i���X�V�҂�
            break;
        }

        //Stage01_01
        case STAGE01CONTROLLER_SCENE_PROG_STG01_01_BEGIN: {
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play(0, 0, true);
            _pBgmPerformer->fadein(0, 420);
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_01_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_02
        case STAGE01CONTROLLER_SCENE_PROG_STG01_02_BEGIN: {
            //BGM�O�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(0, 420);
            //BGM�P�ԃt�F�[�h�C��
            _pBgmPerformer->play(1, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(1, 420);
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_02_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_03
        case STAGE01CONTROLLER_SCENE_PROG_STG01_03_BEGIN: {
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_03_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_Climax
        case STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_BEGIN: {
            //BGM�P�ԃt�F�[�h�A�E�g
            _pBgmPerformer->fadeout_stop(1, 420);
            //BGM�Q�ԃt�F�[�h�C��
            _pBgmPerformer->play(2, GGAF_MIN_VOLUME, true);
            _pBgmPerformer->fadein(2, 420);
            _pPrg->changeNext();
            break;
        }
        case STAGE01CONTROLLER_SCENE_PROG_STG01_CLIMAX_PLAYING: {
            //�i���X�V�҂�
            break;
        }

        //Stage01_Climax �̌�
        case STAGE01CONTROLLER_SCENE_PROG_FAINAL: {
            if (_pPrg->isJustChanged()) {
                //STG01_Climax�I���̏���
                _TRACE_("STG01_Climax�I����STAGE01CONTROLLER_SCENE_PROG_FAINAL����");
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
