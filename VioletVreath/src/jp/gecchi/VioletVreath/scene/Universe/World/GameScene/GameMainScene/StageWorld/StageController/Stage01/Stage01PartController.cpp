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
	frame f[] = {1,100,120,8200,10000,13200,15000,28200,30000,38200,40000};
	_paFrame_NextEvent = new frame[11];
	memcpy(_paFrame_NextEvent, f, sizeof(f));
	_event_num = 11;
	orderSceneToFactory(10000000, Stage01_01, "Stage01_01");
	orderActorToFactory(10000005, EnemyAstraea, "Astraea_1");
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
				Stage01_01* pScene = (Stage01_01*)obtainSceneFromFactory(10000000);
				addSubLast(pScene);
				_pProg->change(Stage01PartController::PROG_STG01_01_BEGIN);
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
				_pProg->change(Stage01PartController::PROG_STG01_02_BEGIN);
				break;
			}
			case 13200: {
				orderSceneToFactory(10000002, Stage01_03, "Stage01_03");
				break;
			}
			case 15000: {
				Stage01_03* pScene = (Stage01_03*)obtainSceneFromFactory(10000002);
				addSubLast(pScene);
				_pProg->change(Stage01PartController::PROG_STG01_03_BEGIN);
				break;
			}
			case 28200: {
				orderSceneToFactory(10000003, Stage01WalledScene, "GroStage01WalledScene");
				break;
			}
			case 30000: {
				Stage01WalledScene* pScene = (Stage01WalledScene*)obtainSceneFromFactory(10000003);
				addSubLast(pScene);
				break;
			}
			case 38200: {
				orderSceneToFactory(10000004, Stage01_Climax, "Stage01_Climax");
				break;
			}
			case 40000: {
				Stage01_Climax* pScene = (Stage01_Climax*)obtainSceneFromFactory(10000004);
				addSubLast(pScene);
				_pProg->change(Stage01PartController::PROG_STG01_CLIMAX_BEGIN);
				break;
			}
			default :
				break;
		}
		_cnt_event = (_cnt_event < 11-1 ? _cnt_event+1 : _cnt_event);
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
