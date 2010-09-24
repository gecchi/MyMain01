#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameScene::GameScene(const char* prm_name) : DefaultScene(prm_name) {
    GameGlobal::_pSceneGame = this;

    _pCommonScene = NEW CommonScene("Common");
    addSubLast(_pCommonScene);

    _pScene_GameDemo = NEW GameDemoScene("GameDemo");
    addSubLast(_pScene_GameDemo);

    _pScene_GameBeginning = NEW GameBeginningScene("GameBeginning");
    addSubLast(_pScene_GameBeginning);

    _pScene_GameMain = NEW GameMainScene("GameMain");
    addSubLast(_pScene_GameMain);

    _pScene_GameEnding = NEW GameEndingScene("GameEnding");
    addSubLast(_pScene_GameEnding);

    _pScene_GameDemo->inactivateImmediately();        //最初のアクティブなサブシーンはデモシーン
    _pScene_GameBeginning->inactivateImmediately();
    _pScene_GameMain->inactivateImmediately();
    _pScene_GameEnding->inactivateImmediately();

    //たまご
    //addSubLast(NEW TamagoScene("TamagoScene"));

    _is_frame_advance = false;

}

void GameScene::initialize() {
    _TRACE_("GameScene::initialize() いきますよDemoSceneさん");
    _pScene_GameDemo->reset();
    _pSceneCannel = _pScene_GameDemo;
}

void GameScene::processBehavior() {
#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
    if (VB->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDx9God::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDx9God::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif
//    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
//        fadeinSceneTree(2*60);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//        fadeoutSceneTree(2*60);
//    }

    //一時停止解除
    if (_pScene_GameMain->wasPause()) {
        if (VB_UI->isReleasedUp(VB_PAUSE) || _is_frame_advance) {
            pGOD->setVB(VB_PLAY);
            _pScene_GameMain->unpause();     //GameMainSceneでの一時停止解除
        }
    }

     //おまけ機能。一時停止していれば、カメラ操作できる。
     if (_pScene_GameMain->canBehave() ) {
         //一時停止していない状態。
         //スルー
     } else {
         //コマ送り
         if (VB_UI->isPushedDown(VB_BUTTON7)) {
             _is_frame_advance = true;
         }


         //一時停止してい状態
         GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
         if (GgafDx9Input::isBeingPressedKey(DIK_V)) {
             //V＋方向で注視点操作
             if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
                 pVP->_Y += 8000;
             } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
                 pVP->_Y -= 8000;
             } else {

             }

             if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
                 pVP->_X += 8000;
             } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
                 pVP->_X -= 8000;
             } else {
             }

             if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
                 pVP->_Z += 8000;
             } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
                 pVP->_Z -= 8000;
             } else {
             }
         } else if (GgafDx9Input::isBeingPressedKey(DIK_C)) {
             //C＋方向でカメラ操作
             if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
                 pCAM->_Y += 8000;
             } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
                 pCAM->_Y -= 8000;
             } else {

             }

             if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
                 pCAM->_X += 8000;
             } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
                 pCAM->_X -= 8000;
             } else {
             }

             if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
                 pCAM->_Z += 8000;
             } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
                 pCAM->_Z -= 8000;
             } else {
             }
         }
     }

    //サブシーンの切替えや平行実行のための、初期化、事前処理、フラグ処理等
    if (_pSceneCannel == _pScene_GameDemo) {
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_BEGIN) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameBeginning->reset();
            _pScene_GameBeginning->ready();
        }
        if (_pScene_GameDemo->getProgressOnChange() == GAMEDEMO_PROG_DECIDE) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameBeginning->activate();
            _pSceneCannel = _pScene_GameBeginning;
        }

    } else if (_pSceneCannel == _pScene_GameBeginning) {
        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_BEGIN) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameMain->reset();
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_DECIDE) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _stage = _pScene_GameBeginning->_selected_stage;
            _pScene_GameMain->ready(_stage); //先行準備
        }

        if (_pScene_GameBeginning->getProgressOnChange() == GAMEBEGINNING_PROG_END) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameMain->activate();
            _pSceneCannel = _pScene_GameMain;
        }

    } else if (_pSceneCannel == _pScene_GameMain) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_BEGIN) {
//            VB_UI->clear();
//            VB_PLAY->clear();
//            pGOD->setVB(VB_PLAY); //保存のためプレイ用に変更
            _pScene_GameEnding->reset();
            _pScene_GameEnding->ready();
        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEMAIN_PROG_END) {
//            VB_UI->clear();
//            pGOD->setVB(VB_UI);  //戻す
            _pScene_GameEnding->activate();
            _pSceneCannel = _pScene_GameEnding;
        }

    } else if (_pSceneCannel == _pScene_GameEnding) {
        if (_pScene_GameMain->getProgressOnChange() == GAMEENDING_PROG_BEGIN) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameEnding->reset();
            _pScene_GameEnding->ready();
        }
        if (_pScene_GameMain->getProgressOnChange() == GAMEENDING_PROG_END) {
            VB_UI->clear();
            pGOD->setVB(VB_UI);
            _pScene_GameEnding->activate();
            _pSceneCannel = _pScene_GameEnding;
        }

    }

}

void GameScene::processJudgement() {

    if (getBehaveingFrame() >= 120) {
        CollisionChecker::_num_check = 0;

//        if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
//            CollisionChecker::_pLinearOctree->putTree();
//        }

        //八分木アルゴリズムで所属シーンの所属アクター全ヒットチェック
        //詳細は 「シーンCreater.xls」 の 「種別相関」 シート参照
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_MY_SHOT|KIND_MY_BODY,
        KIND_ENEMY_BODY|KIND_OTHER|KIND_CHIKEI
        );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_ENEMY_SHOT,
        KIND_MY_BODY|KIND_OTHER|KIND_CHIKEI
        );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA,
        KIND_CHIKEI|KIND_OTHER
        );
        CollisionChecker::_pLinearOctree->executeAllHitChk(
        KIND_ENEMY_BODY_CHIKEI_NOMAL|KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA|KIND_CHIKEI|KIND_OTHER,
        KIND_OTHER
        );

    }
}

void GameScene::processFinal() {

    if (getBehaveingFrame() == 120) {
        //デモ開始
        _pScene_GameDemo->activate();
    }

}

GameScene::~GameScene() {
}
