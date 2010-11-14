#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define ORDER_ID_STAGESCENE 11

GameMainScene* GameMainScene::_pGameMainScene = NULL;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameMainScene";

    _pFont16_SCORE = NEW LabelGecchi16Font("SCORE");
    getLordActor()->addSubGroup(_pFont16_SCORE);
    _pFont16_RANK = NEW LabelGecchi16Font("RANK");
    getLordActor()->addSubGroup(_pFont16_RANK);
    _pFont16_STAMINA = NEW LabelGecchi16Font("STAMINA");
    getLordActor()->addSubGroup(_pFont16_STAMINA);
    _pFont1601 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pFont1601);
    _pFont1602 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pFont1602);
    _pFont8_JIKI_X = NEW LabelGecchi8Font("JIKI_X");
    getLordActor()->addSubGroup(_pFont8_JIKI_X);
    _pFont8_JIKI_Y = NEW LabelGecchi8Font("JIKI_Y");
    getLordActor()->addSubGroup(_pFont8_JIKI_Y);
    _pFont8_JIKI_Z = NEW LabelGecchi8Font("JIKI_Z");
    getLordActor()->addSubGroup(_pFont8_JIKI_Z);
    _pScene_Stage01 = NULL;
    _pScene_Stage02 = NULL;
    _pScene_Stage03 = NULL;
    _pScene_Stage04 = NULL;
    _pScene_Stage05 = NULL;

    _pSceneMainCannnel = NULL;

    GameMainScene::_pGameMainScene = this;
}

void GameMainScene::reset() {
    changeProgress(GAMEMAIN_PROG_INIT);
}

void GameMainScene::ready(int prm_stage) {
    _stage = prm_stage;
    _had_ready_stage = true;
    _frame_ready_stage = 0;
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage01Scene, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage02Scene, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage03Scene, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage04Scene, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage05Scene, "Stage05");
            break;
        default:
            break;
    }
}

void GameMainScene::initialize() {

    changeProgress(GAMEMAIN_PROG_INIT);
    //initialize()����inactive()�ł��邱�Ƃɒ��ӂ��鎖
}

void GameMainScene::processBehavior() {
    if (getProgress() == GAMEMAIN_PROG_INIT) {
        VB_UI->clear();
        VB_PLAY->clear();
        P_GOD->setVB(VB_PLAY); //�ۑ��̂��߃v���C�p�ɕύX
        GgafScene* pCommon = P_COMMON_SCENE->extract();
        addSubLast(pCommon); // ���ʃV�[����z���Ɉړ��i�ꎞ��~�����܂����䂳���邽�߁I�j
        changeProgress(GAMEMAIN_PROG_BEGIN);
        if (_pSceneMainCannnel) {
            //2�ʖڈȍ~�͂��̃^�C�~���O�őO�X�e�[�W��end
            _TRACE_("_pSceneMainCannnel="<<_pSceneMainCannnel->getName()<<" end()");
            _pSceneMainCannnel->end();
        }
    }

    //GAMEMAIN_PROG_BEGIN
    if (onActiveProgress(GAMEMAIN_PROG_BEGIN)) {
        _pFont1601->update(300, 300, "GAME_MAIN_SCENE BEGIN");
        _pFont1602->update(300, 350, "DESTOROY ALL THEM!!");



        _pSceneMainCannnel = (StageScene*)obtainSceneFromFactory(ORDER_ID_STAGESCENE);
        addSubLast(_pSceneMainCannnel); //�X�e�[�W�V�[���ǉ�

        _had_ready_stage = false;
        _frame_Begin = 0;
    }
    if (getProgress() == GAMEMAIN_PROG_BEGIN) {
        //�������[�v
        _frame_Begin++;

        if (_frame_Begin == 180) {
            changeProgress(GAMEMAIN_PROG_PLAY); //
        }
    }

    //GAMEMAIN_PROG_PLAY
    if (onActiveProgress(GAMEMAIN_PROG_PLAY)) {
        _pFont1601->update(300, 300, "");
        _pFont1602->update(300, 350, "");

    }
    if (getProgress() == GAMEMAIN_PROG_PLAY) {
        //�������[�v
        if (_had_ready_stage) {
            _frame_ready_stage++;
            if (_frame_ready_stage == 5*60) {
                _TRACE_("�V�X�e�[�WCOMEING!!");
                changeProgress(GAMEMAIN_PROG_BEGIN);
            }
        }
    }

    //GAMEMAIN_PROG_END �I������
    if (onActiveProgress(GAMEMAIN_PROG_END)) {
         VB_UI->clear();
         P_GOD->setVB(VB_UI);  //�߂�
        _TRACE_("�I���^");
        //�����ŃR���e�j���[���f
        inactivateDelay(180);
    }
    if (getProgress() == GAMEMAIN_PROG_END) {
        //GAMEMAIN_PROG_END���͂Ȃɂ��ł��Ȃ�
    }


    //SCORE�\��
    sprintf(_buf, "SCORE %07u", _SCORE_);
    _pFont16_SCORE->update(550, 1, _buf);
    sprintf(_buf, "RANK %.7f", _RANK_);
    _pFont16_RANK->update(550, 20, _buf);
    sprintf(_buf, "STAMINA %7d", P_MYSHIP->_pStatus->get(STAT_Stamina));
    _pFont16_STAMINA->update(550, 40, _buf);

    sprintf(_buf, "X:%8d", P_MYSHIP->_X);
    _pFont8_JIKI_X->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*3-1, _buf);
    sprintf(_buf, "Y:%8d", P_MYSHIP->_Y);
    _pFont8_JIKI_Y->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*2-1, _buf);
    sprintf(_buf, "Z:%8d", P_MYSHIP->_Z);
    _pFont8_JIKI_Z->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*1-1, _buf);

    if (getProgress() == GAMEMAIN_PROG_PLAY || getProgress() == GAMEMAIN_PROG_BEGIN) {

        //�ꎞ��~
        if (VB_PLAY->isReleasedUp(VB_PAUSE) || P_GAME_SCENE->_is_frame_advance) {
            P_GAME_SCENE->_is_frame_advance = false;
            _TRACE_("PAUSE!");
            P_GOD->setVB(VB_UI);  //���͂͂t�h�ɐ؂�ւ�
            pause();     //���g�z�����ꎞ��~����B�ꎞ��~������GameScene�ōs����
            P_UNIVERSE->pushCameraWork("PauseCamWorker");
//            P_ACTIVE_CAMWORKER->pause();
            P_MYSHIP->pause();
        }
    }
}

void GameMainScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
//������Myship�̃C�x���g�͂��Ȃ���I
//    if (prm_no == EVENT_ALL_MY_SHIP_WAS_DESTROYED) {
//        _TRACE_("GameMainScene EVENT_ALL_MY_SHIP_WAS_DESTROYED was Catch!!");
//        changeProgress(GAMEMAIN_PROG_END);
//    } else if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
//        _TRACE_("GameMainScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");
//    } else if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_FINISH) {
//        _TRACE_("GameMainScene EVENT_MY_SHIP_WAS_DESTROYED_FINISH was Catch!!");
//    }


    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        //���̃X�e�[�W���H��ɒ������Ă�����Ƃ����C�x���g
        _TRACE_("GameMainScene::catchEvent() EVENT_PREPARE_NEXT_STAGE��������");
        if (_stage < 5) {
            _stage++;
            ready(_stage);

        } else {
            _TRACE_("�ŏI�ʃN���A");
            changeProgress(GAMEMAIN_PROG_END);
            //TODO:�G�f�j���O�H
        }
    }

//    if (prm_no == EVENT_JUST_GAME_OVER) {
//
//    }

}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}

