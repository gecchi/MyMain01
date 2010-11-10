#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    //壁ブロックディスパッチャー生成
    float scale_r = 4.0f; //壁ブロックの元モデルからの拡大率
    WallActor* pWallActor;
    GgafActorDispatcher* pDispatcher_Wall = NEW GgafActorDispatcher("Dp_Wall");
    for (int i = 0; i < 4000; i++) {
        pWallActor = NEW Wall001("GroundBox");
        pWallActor->setScaleRate(scale_r);
        pWallActor->inactivateTreeImmediately();
        pDispatcher_Wall->addSubLast(pWallActor);
    }

    //シーンセクション生成
    WalledSectionScene* apSection[] = {
      NEW Stage01WalledSection001("gbs", this, "scene3_wall_0.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene3_wall_1.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene3_wall_2.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene3_wall_3.dat"),
      NEW Stage01WalledSection001("gbs", this, "scene3_wall_4.dat"),
    };

    //構築
    buildWalledScene(
        400000*scale_r, 100000*scale_r, 100000*scale_r,
        (WalledSectionScene**)&apSection, 5,
        pDispatcher_Wall
    );

    //初期スクロールスピード
    setScroolSpeed(5000);


    orderActorToFactory(9999999+_id, FormationThalia, "FormationThalia_1");
}


void Stage01WalledScene::initialize() {
}



void Stage01WalledScene::onActive() {
    WalledScene::onActive();
}

void Stage01WalledScene::processBehavior() {
    WalledScene::processBehavior();

    if (getActivePartFrame() % 60 == 0) {
        if (getScroolSpeed() < 5000) {
            addScroolSpeed(1000);
        }
    }

    if (getActivePartFrame() == 10) {
    FormationThalia* pActor = (FormationThalia*)obtainActorFromFactory(9999999+_id);
    getLordActor()->addSubGroup(pActor);
    }

//    if (getActivePartFrame() % 1300 == 0) {
//        _scrool_speed = 2000;
//    }
//
//
//    if (getActivePartFrame() % 1800 == 0) {
//        _scrool_speed = 5000;
//    }
}

void Stage01WalledScene::processFinal() {
}

Stage01WalledScene::~Stage01WalledScene() {

}
