#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardSetActor(prm_name, "title") {
    _class_name = "TitleBoard";
    //_z = 0.9999999f;  //���Ԃ�Ŕw�� �i0 <= _z < 1.0�jZ=(0�`+1)
    useProgress(10);
}
void TitleBoard::initialize() {
}

void TitleBoard::onActive() {
//    _pPrg->change(TITLEBOARD_PROG_INIT);
}

void TitleBoard::processBehavior() {
//    if (_pPrg->get() == TITLEBOARD_PROG_INIT) {
//        _pPrg->change(TITLEBOARD_PROG_ENTRANCE);
//    }
//
//    //�^�C�g���\���A�N�V���� TITLEBOARD_PROG_ENTRANCE ���̏���
//    if (_pPrg->isJustChangedTo(TITLEBOARD_PROG_ENTRANCE)) {
//        locate(200, 1000);
//    }
//    if (_pPrg->get() == TITLEBOARD_PROG_ENTRANCE) {
//        _y -= 1;
//        if (_y <= 150) {
//            _pPrg->change(TITLEBOARD_PROG_DISP);
//        }
//    }
//    if (_pPrg->isJustChangedFrom(TITLEBOARD_PROG_ENTRANCE)) {
//    }
//
//    //�^�C�g���\���Î~ TITLEBOARD_PROG_DISP ���̏���
//    if (_pPrg->isJustChangedTo(TITLEBOARD_PROG_DISP)) {
//        locate(200, 150);
//    }
//    if (_pPrg->get() == TITLEBOARD_PROG_DISP) {
//    }
//    if (_pPrg->isJustChangedFrom(TITLEBOARD_PROG_DISP)) {
//    }


}

void TitleBoard::processJudgement() {
}


TitleBoard::~TitleBoard() {
}
