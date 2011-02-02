#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001::FormationPallas001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas001";
    _num_Pallas     = 12+_RANK_*8;    //編隊数
    _frame_interval = 10-_RANK_*5;  //パラスの間隔(frame)
    _mv_velo        = 10000+_RANK_*10000; //速度
    //パラス編隊作成
    _pSplineCon     = (SplineConnection*)(P_GOD->_pSplineManager->getConnection("Pallas01")); //スプライン定義
    _pDispatcherCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        _papPallas[i]->config(_pSplineCon->refer()->makeSplineProgram(_papPallas[i]), NULL, NULL);
        //_papPallas[i]->setDispatcher_Shot(_pDispatcherCon->refer()); //弾設定
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}
void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    GgafMainActor* pActor = getSubFirst();
    EnemyPallas* pPallas = NULL;
    int t = 0;
    do {
        pPallas = (EnemyPallas*)pActor;
        pPallas->setCoordinate(_pSplineCon->refer()->_pSp->_X_basepoint[0], 0, 0);
        pPallas->_pMover->setMvVelo(_mv_velo);
        pPallas->activateDelay(t*_frame_interval + 1);//_frame_interval間隔でActiveにする。
        t++;
        pActor = pActor->getNext();
    } while (!pActor->isFirst());


}
void FormationPallas001::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //編隊消滅時の実験
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDispatcher_EffectTurbo002->employForce();
    if (pTurbo002) {
        pTurbo002->setCoordinateBy(prm_pActorLast);
        pTurbo002->activate();
    }
}

void FormationPallas001::processBehavior() {
}

FormationPallas001::~FormationPallas001() {
    _pSplineCon->close();
    if (_pDispatcherCon) {
        _pDispatcherCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
