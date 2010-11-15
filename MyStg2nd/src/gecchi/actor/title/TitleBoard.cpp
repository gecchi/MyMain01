#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


TitleBoard::TitleBoard(const char* prm_name) : DefaultBoardSetActor(prm_name, "title") {
    _class_name = "TitleBoard";
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
    _z = 0.9999999f;
}
void TitleBoard::initialize() {
}

void TitleBoard::onActive() {
    setAlpha(0.0);
    changeProgress(TITLEBOARD_PROG_INIT);
}

void TitleBoard::processBehavior() {
    if (getProgress() == TITLEBOARD_PROG_INIT) {
        changeProgress(TITLEBOARD_PROG_ENTRANCE);
    }

    //タイトル表示アクション TITLEBOARD_PROG_ENTRANCE 時の処理
    if (onActiveProgress(TITLEBOARD_PROG_ENTRANCE)) {
        setAlpha(0.0);
        setCoordinate(200, 1000);
    }
    if (getProgress() == TITLEBOARD_PROG_ENTRANCE) {
        addAlpha(0.01);
        _y -= 1;
        if (_y <= 150) {
            changeProgress(TITLEBOARD_PROG_DISP);
        }
    }
    if (onInactiveProgress(TITLEBOARD_PROG_ENTRANCE)) {
    }

    //タイトル表示静止 TITLEBOARD_PROG_DISP 時の処理
    if (onActiveProgress(TITLEBOARD_PROG_DISP)) {
        setAlpha(1.0);
        setCoordinate(200, 150);
    }
    if (getProgress() == TITLEBOARD_PROG_DISP) {
    }
    if (onInactiveProgress(TITLEBOARD_PROG_DISP)) {
    }


}

void TitleBoard::processJudgement() {
}


TitleBoard::~TitleBoard() {
}
