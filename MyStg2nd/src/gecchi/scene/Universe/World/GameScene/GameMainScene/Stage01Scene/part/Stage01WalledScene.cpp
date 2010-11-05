#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : WalledScene(prm_name) {
    _class_name = "Stage01WalledScene";

    _ground_speed = 5000;
    float scale_r = 4.0f; //壁ブロックの元モデルからの拡大率
    WallActor* pWallActor;
    GgafActorDispatcher* pDispatcher_Wall = NEW GgafActorDispatcher("Dp_Wall");
    for (int i = 0; i < 4000; i++) {
        pWallActor = NEW GroundBoxScene::GroundBoxActor("GroundBox");
        pWallActor->setScaleRate(scale_r);
        pWallActor->inactivateTreeImmediately();
        pDispatcher_Wall->addSubLast(pWallActor);
    }

    WalledSectionScene* apSection[] = {
      NEW GroundBoxScene("gbs", this, "scene3_wall_0.dat"),
      NEW GroundBoxScene("gbs", this, "scene3_wall_1.dat"),
      NEW GroundBoxScene("gbs", this, "scene3_wall_2.dat"),
      NEW GroundBoxScene("gbs", this, "scene3_wall_3.dat"),
      NEW GroundBoxScene("gbs", this, "scene3_wall_4.dat"),
    };

    WalledScene::build(
            400000*scale_r, 100000*scale_r, 100000*scale_r,
            (WalledSectionScene**)&apSection, 5,
            pDispatcher_Wall, Stage01WalledScene::moveX);
}

void Stage01WalledScene::moveX(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->_obj_class >= Obj_GgafScene) {
        return; //シーンならば無視
    }
    GgafActor* pActor = (GgafActor*)pThat;
    if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
        if (pActor->_obj_class & Obj_GgafDx9GeometricActor) {
            ((GgafDx9GeometricActor*)pActor)->_X -= (*((int*)p1));
        }
    }
}


void Stage01WalledScene::initialize() {

}



void Stage01WalledScene::onActive() {
    WalledScene::onActive();
}

void Stage01WalledScene::processBehavior() {
    WalledScene::processBehavior();

    if (getActivePartFrame() % 60 == 0) {
        if (_ground_speed < 200000) {
            _ground_speed += 1000;
        }
    }

//    if (getActivePartFrame() % 1300 == 0) {
//        _ground_speed = 2000;
//    }
//
//
//    if (getActivePartFrame() % 1800 == 0) {
//        _ground_speed = 5000;
//    }
}

void Stage01WalledScene::processFinal() {
}

Stage01WalledScene::~Stage01WalledScene() {

}
