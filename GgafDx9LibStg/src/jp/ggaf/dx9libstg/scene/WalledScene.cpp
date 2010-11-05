#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

WalledScene::WalledScene(const char* prm_name) : ScrolledScene(prm_name) {
    _class_name = "WalledScene";
    WallActor* pWallActor;
    _ground_speed = 5000;

    _pDispatcher_Wall = NULL;
    _pRingSection = NEW GgafLinkedListRing<WalledSectionScene>();
    _pFuncWallMove = NULL;
}

void WalledScene::build(
        int prm_wall_dep, int prm_wall_width, int prm_wall_height,
        WalledSectionScene** prm_papSection, int prm_section_num,
        GgafActorDispatcher* prm_pDispatcher_Wall, void (*prm_pFuncWallMove)(GgafObject*, void*, void*)) {

    _pDispatcher_Wall = prm_pDispatcher_Wall;
    getLordActor()->addSubGroup(_pDispatcher_Wall);

    _pRingSection = NEW GgafLinkedListRing<WalledSectionScene>();
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]);
        prm_papSection[i]->config(_pDispatcher_Wall, prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivateImmediately();
        _pRingSection->addLast(prm_papSection[i], false);
    }
    _pRingSection->first();

    _pFuncWallMove = prm_pFuncWallMove;
}

void WalledScene::initialize() {

}

void WalledScene::onActive() {
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    pCurrentSection->activate();
}

void WalledScene::processBehavior() {
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    if (!pCurrentSection->isLast()) {
        if (pCurrentSection->_is_loop_end) {
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

}

void WalledScene::processFinal() {
}

WalledScene::~WalledScene() {

}
