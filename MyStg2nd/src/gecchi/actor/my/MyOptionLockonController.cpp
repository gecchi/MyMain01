#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionLockonController::MyOptionLockonController(const char* prm_name) : GgafDummyActor(prm_name) {
    _class_name = "MyOptionLockonController";
    //_pTarget = NULL;
    _max_lock_num = 5;
    setProgress(MyOptionLockonController_PROG_NOTHING);
}

void MyOptionLockonController::initialize() {
}


void MyOptionLockonController::processBehavior() {
    //ロックオンターゲット生存確認
    GgafDx9GeometricActor* pTarget = _ringTarget.get(); //メインロックオン
    for (int i = 0; i < _ringTarget.length(); i++) {
        if (pTarget->isActive()) {
            //OK
            _ringTarget.next(); //次へ
        } else {
            _ringTarget.remove(); //抜き出し
            i++;

        }
    }
}

void MyOptionLockonController::processJudgement() {
}


void MyOptionLockonController::lockOn(GgafDx9GeometricActor* prm_pTarget) {
    if (ringTarget.indexOf(prm_pTarget) >= 0) { //ロックオン済みに無ければ
        if (_ringTarget.length() < _max_lock_num) {
        _ringTarget.addPrev(prm_pTarget);
        _ringTarget.prev();
        //  s3  M   s1  s2
        //⇔○⇔●⇔○⇔○⇔
        //      ↓  addPrev(☆)   ☆＝prm_pTarget
        //⇔○⇔☆⇔●⇔○⇔○⇔
        //      ↓  prev()
        //⇔○⇔★⇔○⇔○⇔○⇔
        //  s4  M   s1  s2  s3
        //(塗り潰しはアクティブ要素)
    } else {
        //ロック数がMAXならば、一番古い順に上書きで消されていく
        _ringTarget.prev();
        _ringTarget.set(prm_pTarget);
        //  s3  s4  M   s1  s2
        //⇔○⇔○⇔●⇔○⇔○⇔
        //      ↓  prev()
        //⇔○⇔●⇔○⇔○⇔○⇔
        //      ↓  set(☆)   ☆＝prm_pTarget
        //⇔○⇔★⇔○⇔○⇔○⇔
    }
}


void MyOptionLockonController::releaseLockOn() {
    if (ringTarget.length() > 0) {
        ringTarget.remove();
        //F            L
        //⇔a⇔b⇔c⇔d!⇔f⇔g⇔
        //      ↓  remove()
        //⇔a⇔b⇔c⇔f!⇔g⇔
    }
}

MyOptionLockonController::~MyOptionLockonController() {
}

