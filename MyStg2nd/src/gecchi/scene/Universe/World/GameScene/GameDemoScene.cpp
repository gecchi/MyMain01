#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";

    changeProgress(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");
}
void GameDemoScene::reset() {
    changeProgress(GAMEDEMO_SCENE_PROG_INIT);
}
void GameDemoScene::onActive() {
    reset();
}
void GameDemoScene::initialize() {
}

void GameDemoScene::processBehavior() {

    //GAMEDEMO_SCENE_PROG_INIT ���̏���
    if (onActiveProgress(GAMEDEMO_SCENE_PROG_INIT)) {
    }
    if (getProgress() == GAMEDEMO_SCENE_PROG_INIT) {
        changeProgress(GAMEDEMO_SCENE_PROG_BEGIN);
    }
    if (onInactiveProgress(GAMEDEMO_SCENE_PROG_INIT)) {
    }


    //�^�C�g���O�f�� GAMEDEMO_SCENE_PROG_BEGIN ���̏���
    if (onActiveProgress(GAMEDEMO_SCENE_PROG_BEGIN)) {
    }
    if (getProgress() == GAMEDEMO_SCENE_PROG_BEGIN) {
    }
    if (onInactiveProgress(GAMEDEMO_SCENE_PROG_BEGIN)) {
    }

    //�^�C�g�� GAMEDEMO_SCENE_PROG_TITLE ���̏���
    if (onActiveProgress(GAMEDEMO_SCENE_PROG_TITLE)) {
    }
    if (getProgress() == GAMEDEMO_SCENE_PROG_TITLE) {
    }
    if (onInactiveProgress(GAMEDEMO_SCENE_PROG_TITLE)) {
    }

    //�f���v���C GAMEDEMO_SCENE_PROG_DEMOPLAY ���̏���
    if (onActiveProgress(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
    }
    if (getProgress() == GAMEDEMO_SCENE_PROG_DEMOPLAY) {
    }
    if (onInactiveProgress(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
    }

    //�����L���O GAMEDEMO_SCENE_PROG_RANKING ���̏���
    if (onActiveProgress(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
    }
    if (getProgress() == GAMEDEMO_SCENE_PROG_DEMOPLAY) {
    }
    if (onInactiveProgress(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
    }











//    if (getProgress() == GAMEDEMO_SCENE_PROG_INIT) {
////        P_CAM->setDefaultPosition();
//
////        TamagoActor* pActor = (TamagoActor*)obtainActorFromFactory(111111);
////        getLordActor()->addSubGroup(KIND_ENEMY_BODY, pActor);
//
//        //���@�\��
//        P_MYSHIP->activate(); //���ʂɃI�v�V�����������邵
//
//        //TODO:kesu
//        //�e�X�g
////        TamagoActor* pActor = (TamagoActor*)obtainActorFromFactory(1111);
////        getLordActor()->addSubGroup(KIND_ENEMY_BODY,  pActor);
//
//        changeProgress(GAMEDEMO_SCENE_PROG_BEGIN);
//    }
//
//    if (onActiveProgress(GAMEDEMO_SCENE_PROG_BEGIN)) {
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE BEGIN");
//        _pStringBoard02->update(100, 150, "HAJIMARI HAJIMARI!");
//        _frame_Begin = 0;
//    } else if (getProgress() == GAMEDEMO_SCENE_PROG_BEGIN) {
//        //�^�C�g���������[�v
//        _frame_Begin++;
//
//        if (_frame_Begin == 120) {
//            changeProgress(GAMEDEMO_SCENE_PROG_TITLE); //�^�C�g����
//        }
//    }
//
//
//    //���[�v----->
//
//    if (onActiveProgress(GAMEDEMO_SCENE_PROG_TITLE)) {
//         //�^�C�g���J�n
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE TITLE");
//        _pStringBoard02->update(100, 150, "PUSH A UI_EXECUTE BUTTON");
//        _pBgmPerformer->stop(0);
//        _pBgmPerformer->play(0, true);
//
//        _frame_Title = 0;
//    }
//    if (getProgress() == GAMEDEMO_SCENE_PROG_TITLE) {
//        //�^�C�g���������[�v
//        _frame_Title++;
//
//        //�����ɏ���
//        if (VB->isPushedDown(VB_UI_EXECUTE)) {
//            changeProgress(GAMEDEMO_SCENE_PROG_DECIDE);
//        }
//
//        if (_frame_Title == 600) {
//            changeProgress(GAMEDEMO_SCENE_PROG_DEMOPLAY); //�f����
//        }
//    }
//
//    if (onActiveProgress(GAMEDEMO_SCENE_PROG_DEMOPLAY)) {
//        //�f���v���C�J�n
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DEMOPLAY");
//        _pStringBoard02->update(100, 150, "GAME OVER");
//       changeProgress(GAMEDEMO_SCENE_PROG_DEMOPLAY);
//        _frame_Demoplay = 0;
//
//        _pBgmPerformer->fadeout_stop(0, 180);//�^�C�g��BGM�����Ă���Ώ���
//
//    } else if (getProgress() == GAMEDEMO_SCENE_PROG_DEMOPLAY) {
//        //�f���v���C�������[�v
//        _frame_Demoplay++;
//
//        //�����ɏ���
//        if (_frame_Demoplay == 300) {
//            changeProgress(GAMEDEMO_SCENE_PROG_RANKING); //�����L���O��
//        }
//    }
//
//
//
//    if (onActiveProgress(GAMEDEMO_SCENE_PROG_RANKING)) {
//        //�����L���O�\��
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE RANKING");
//        _pStringBoard02->update(100, 150, "WE ARE THE WORLD. DESTORY ALL THEM. POWER UP");
//        _frame_Ranking = 0;
//    }
//    if (getProgress() == GAMEDEMO_SCENE_PROG_RANKING) {
//        //�����L���O�������[�v
//        _frame_Ranking++;
//
//        //�����ɏ���
//
//
//        if (_frame_Ranking == 300) {
//            changeProgress(GAMEDEMO_SCENE_PROG_TITLE); //�^�C�g����
//        }
//    }
//
//    //<-----���[�v
//    //�f���v���C�������L���O��
//    if (GAMEDEMO_SCENE_PROG_DEMOPLAY <= getProgress() && getProgress() <= GAMEDEMO_SCENE_PROG_RANKING) {
//        if (VB->isPushedDown(VB_UI_EXECUTE)) { //VB_UI_EXECUTE�Ń^�C�g����
//            changeProgress(GAMEDEMO_SCENE_PROG_TITLE);
//        }
//    }
//
//
//    //�Q�[���X�^�[�g
//    if (onActiveProgress(GAMEDEMO_SCENE_PROG_DECIDE)) {
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE DECIDE");
//        _pStringBoard02->update(100, 150, "OK HJIMARIMASU!");
//        _frame_Decide = 0;
//    } else if (getProgress() == GAMEDEMO_SCENE_PROG_DECIDE) {
//        //�������[�v
//        _frame_Decide++;
//
//        if (_frame_Decide == 120) {
//            _pBgmPerformer->fadeout_stop(0, 180);
//            changeProgress(GAMEDEMO_SCENE_PROG_END); //���I��
//        }
//    }
//
//    if (onActiveProgress(GAMEDEMO_SCENE_PROG_END)) {
//        _pStringBoard01->update(100, 100, "GAME_DEMO_SCENE END");
//        _pStringBoard02->update(100, 150, "SRABA");
//        inactivateDelay(200);
//    }



}

void GameDemoScene::processFinal() {

}

GameDemoScene::~GameDemoScene() {
}
