#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage01PartController::Stage01PartController(const char* prm_name) : StagePartController(prm_name) {
    _class_name = "Stage01PartController";

    _pBgmPerformer->useBgm(4);
    _pBgmPerformer->set(0, "OGG_BGM_01_01");
    _pBgmPerformer->set(1, "OGG_BGM_01_02");
    _pBgmPerformer->set(2, "OGG_BGM_01_03");
    _pBgmPerformer->set(3, "OGG_BGM_01_CLIMAX");
    // �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
    // �R�[�h�̕ύX�́u�V�[��Creater.xls�v����s�����Ƃ���i�������m�ۂ̂��߁j�B
    // gen01 start
	frame f[] = {1,300,500,1200,2300,3200,4300,5200,6300,7200,8300,9200,10300,11200,12300,13200,14300,15200,16300,17200,18300,19200,20300,21200,22300,23200,24300,25200,26300,27200,28300,29200};
	_paFrame_NextEvent = new frame[32];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 32;
	orderActorToFactory(10000015, EnemyHermione, "EnemyHermione-1");
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
			case 300: {
				orderActorToFactory(10000000, EnemyHermione, "EnemyHermione-2");
				break;
			}
			case 500: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000015);
				getDirector()->addSubGroup(p);
				p->_X = 300000;
				p->_Y = 0;
				p->_Z = 0;
				break;
			}
			case 1200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000000);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 2300: {
				orderActorToFactory(10000001, EnemyHermione, "EnemyHermione-3");
				break;
			}
			case 3200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000001);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 4300: {
				orderActorToFactory(10000002, EnemyHermione, "EnemyHermione-4");
				break;
			}
			case 5200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000002);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 6300: {
				orderActorToFactory(10000003, EnemyHermione, "EnemyHermione-5");
				break;
			}
			case 7200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000003);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 8300: {
				orderActorToFactory(10000004, EnemyHermione, "EnemyHermione-6");
				break;
			}
			case 9200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000004);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 10300: {
				orderActorToFactory(10000005, EnemyHermione, "EnemyHermione-7");
				break;
			}
			case 11200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000005);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 12300: {
				orderActorToFactory(10000006, EnemyHermione, "EnemyHermione-8");
				break;
			}
			case 13200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000006);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 14300: {
				orderActorToFactory(10000007, EnemyHermione, "EnemyHermione-9");
				break;
			}
			case 15200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000007);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 16300: {
				orderActorToFactory(10000008, EnemyHermione, "EnemyHermione-10");
				break;
			}
			case 17200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000008);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 18300: {
				orderActorToFactory(10000009, EnemyHermione, "EnemyHermione-11");
				break;
			}
			case 19200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000009);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 20300: {
				orderActorToFactory(10000010, EnemyHermione, "EnemyHermione-12");
				break;
			}
			case 21200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000010);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 22300: {
				orderActorToFactory(10000011, EnemyHermione, "EnemyHermione-13");
				break;
			}
			case 23200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000011);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 24300: {
				orderActorToFactory(10000012, EnemyHermione, "EnemyHermione-14");
				break;
			}
			case 25200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000012);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 26300: {
				orderActorToFactory(10000013, EnemyHermione, "EnemyHermione-15");
				break;
			}
			case 27200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000013);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			case 28300: {
				orderActorToFactory(10000014, EnemyHermione, "EnemyHermione-16");
				break;
			}
			case 29200: {
				EnemyHermione* p = (EnemyHermione*)obtainActorFromFactory(10000014);
				getDirector()->addSubGroup(p);
				p->_X = RND(000000,300000);
				p->_Y = RND(-300000,300000);
				p->_Z = RND(-300000,300000);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 32-1 ? _cnt_event+1 : _cnt_event);
	}
    // gen02 end


    switch (_pProg->get()) {
        case PROG_FAINAL: {
            if (_pProg->hasJustChanged()) {
                //STG01Climax_�I���̏���
                _TRACE_("STG01Climax_�I����Stage01PartController::PROG_FAINAL����");
            }

            if (_pProg->getFrameInProgress() == 60) {
                fadeoutSceneWithBgm(300);
                throwEventUpperTree(EVENT_STG01_CTRLER_WAS_END); //�X�e�[�W�G���h����ʂɓ`����
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
        ((Stage01_01*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_02_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_02_WAS_BROKEN");
        ((Stage01_02*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_03_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_03_WAS_BROKEN");
        ((Stage01_03*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_WALLED_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_WALLED_WAS_BROKEN");
        ((Stage01WalledScene*)prm_pSource)->sayonara(60*60);
    } else if (prm_no == EVENT_STG01_CLIMAX_WAS_BROKEN) {
        _TRACE_("Stage01PartController::onCatchEvent() EVENT_STG01_CLIMAX_WAS_BROKEN�L���b�`�����BSTAGE01PARTCONTROLLER_ENDING�𓊂���");
        ((Stage01_Climax*)prm_pSource)->sayonara(60*60);
        _pProg->change(PROG_FAINAL); //�i����Stage01PartController::PROG_FAINAL�ɐ؂�ւ���
    } else {

    }

}

Stage01PartController::~Stage01PartController() {

}
