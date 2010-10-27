#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

WalledScene::WalledScene(const char* prm_name) : DefaultScene(prm_name) {
    WallActor* pWallActor;
    GgafActorDispatcher* _pDispatcher_Wall = NEW GgafActorDispatcher("Dp_Wall");
    for (int i = 0; i < 3000; i++) {
        pWallActor =  NEW GroundBoxActor("GroundBox");
        pWallActor->inactivateTreeImmediately();
        _pDispatcher_Wall->addSubLast(pWallActor);
    }
    getLordActor()->addSubGroup(_pDispatcher_Wall);

    WalledSectionScene* pSection01 = NEW GroundBoxScene("01");
    WalledSectionScene* pSection02 = NEW GroundBoxScene("02");
    WalledSectionScene* pSection03 = NEW GroundBoxScene("03");
    addSubLast(pSection01);
    addSubLast(pSection02);
    addSubLast(pSection03);
    pSection01->config(_pDispatcher_Wall,
                       800000, 200000,200000,
                       5000, 1);
    pSection02->config(_pDispatcher_Wall,
                       800000, 200000,200000,
                       5000, 1);
    pSection03->config(_pDispatcher_Wall,
                       800000, 200000,200000,
                       5000, 1);

    pSection01->inactivateImmediately();
    pSection02->inactivateImmediately();
    pSection03->inactivateImmediately();


    _pRingSection = NEW GgafLinkedListRing<WalledSectionScene>();
    _pRingSection->addLast(pSection01, false);
    _pRingSection->addLast(pSection02, false);
    _pRingSection->addLast(pSection03, false);
    _pRingSection->first();
}

void WalledScene::initialize() {

}
void WalledScene::onActive() {
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    pCurrentSection->activate();
}

void WalledScene::processBehavior() {
    WalledSectionScene* pCurrentSection = _pRingSection->getCurrent();
    if (pCurrentSection->_cnt_loop >= pCurrentSection->_loop_num) {
        _TRACE_("NewSection!!!!!!!!!!!!!");
        WalledSectionScene* pNewSection = _pRingSection->next();
        pNewSection->activate();
        pCurrentSection->inactivateDelay(
                (GgafDx9Universe::_X_goneRight - GgafDx9Universe::_X_goneLeft) / pCurrentSection->_ground_speed
             );
    }
}

void WalledScene::processFinal() {
}

WalledScene::~WalledScene() {

}
