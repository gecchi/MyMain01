#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01WalledScene::Stage01WalledScene(const char* prm_name) : ScrolledScene(prm_name) {
    _class_name = "Stage01WalledScene";
    WallActor* pWallActor;
    _ground_speed = 5000;

    _pDispatcher_Wall = NEW GgafActorDispatcher("Dp_Wall");
    for (int i = 0; i < 4000; i++) {
		pWallActor =  NEW GroundBoxScene::GroundBoxActor("GroundBox");
		pWallActor->_SX = 4000;
		pWallActor->_SY = 4000;
		pWallActor->_SZ = 4000;
        pWallActor->inactivateTreeImmediately();
        _pDispatcher_Wall->addSubLast(pWallActor);
    }
    getLordActor()->addSubGroup(_pDispatcher_Wall);
    string section_dat[] = {
        "scene3_wall_0.dat",
        "scene3_wall_1.dat",
        "scene3_wall_2.dat",
        "scene3_wall_3.dat",
        "scene3_wall_4.dat"
    };

    _pRingSection = NEW GgafLinkedListRing<WalledSectionScene>();
    for (int i = 0; i < 5; i++) {
        WalledSectionScene* pSection = NEW GroundBoxScene("gbs", this, section_dat[i].c_str());
        addSubLast(pSection);
        pSection->config(_pDispatcher_Wall, 1600000, 400000, 400000);
        pSection->inactivateImmediately();
        _pRingSection->addLast(pSection, false);
    }
    _pRingSection->first();

    _pFuncWallMove = Stage01WalledScene::moveX;
}

void Stage01WalledScene::moveX(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->_obj_class >= Obj_GgafScene) {
        return; //ƒV[ƒ“‚È‚ç‚Î–³Ž‹
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
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    pCurrentSection->activate();
}

void Stage01WalledScene::processBehavior() {
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    if (!pCurrentSection->isLast()) {
//        _TRACE_("pCurrentSection->_cnt_loop="<<pCurrentSection->_cnt_loop<<" pCurrentSection->_loop_num="<<pCurrentSection->_loop_num );
        if (pCurrentSection->_is_loop_end) {
            _TRACE_("NewSection!!!!!!!!!!!!!");
            WalledSectionScene* pNewSection = _pRingSection->next();
            pNewSection->activate();
            pNewSection->_pWallLast = pCurrentSection->getLastWall();
            pCurrentSection->end(
                    120 + (GgafDx9Universe::_X_goneRight - GgafDx9Universe::_X_goneLeft) / _ground_speed
                 );
        }
    } else {
        if (pCurrentSection->_is_loop_end) {
            end(120 + (GgafDx9Universe::_X_goneRight - GgafDx9Universe::_X_goneLeft) / _ground_speed);
        }
    }


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
