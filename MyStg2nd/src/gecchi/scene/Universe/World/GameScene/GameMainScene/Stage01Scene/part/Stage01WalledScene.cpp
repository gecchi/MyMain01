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
        pWallActor =  NEW GroundBoxActor("GroundBox");
        pWallActor->inactivateTreeImmediately();
        _pDispatcher_Wall->addSubLast(pWallActor);
    }
    getLordActor()->addSubGroup(_pDispatcher_Wall);

    WalledSectionScene* pSection01 = NEW GroundBoxScene("01", this);
    WalledSectionScene* pSection02 = NEW GroundBoxScene("02", this);
    WalledSectionScene* pSection03 = NEW GroundBoxScene("03", this);
    addSubLast(pSection01);
    addSubLast(pSection02);
    addSubLast(pSection03);
    pSection01->config(_pDispatcher_Wall,
                       800000, 200000,200000, 2);
    pSection02->config(_pDispatcher_Wall,
                       800000, 200000,200000, 2);
    pSection03->config(_pDispatcher_Wall,
                       800000, 200000,200000, 2);

    pSection01->inactivateImmediately();
    pSection02->inactivateImmediately();
    pSection03->inactivateImmediately();


    _pRingSection = NEW GgafLinkedListRing<WalledSectionScene>();
    _pRingSection->addLast(pSection01, false);
    _pRingSection->addLast(pSection02, false);
    _pRingSection->addLast(pSection03, false);
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


    if (getActivePartFrame() % 1100 == 0) {
        _ground_speed = 10000;
    }

    if (getActivePartFrame() % 1300 == 0) {
        _ground_speed = 2000;
    }


    if (getActivePartFrame() % 1800 == 0) {
        _ground_speed = 5000;
    }
}

void Stage01WalledScene::processFinal() {
}

Stage01WalledScene::~Stage01WalledScene() {

}
