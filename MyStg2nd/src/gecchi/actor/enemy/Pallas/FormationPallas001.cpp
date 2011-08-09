#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001::FormationPallas001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas001";
    _num_Pallas      = R_FormationPallas001_Num;    //編隊数
    _interval_frames = R_FormationPallas001_LaunchInterval;  //パラスの間隔(frame)
    _mv_velo         = R_FormationPallas001_MvVelo; //速度
    //パラス編隊作成
    _pSplCon     = connectSplineSourceManager("Pallas01");
    //(SplineSourceConnection*)(P_GOD->_pSplSourceManager->connect("Pallas01")); //スプライン定義


//#ifdef getSplineSourceManager
//    #define getSplineSourceConnection(ID) ((GgafDx9LibStg::SplineSourceConnection*)(getSplineSourceManager()->connect(ID)))
//#else
//    P_SPLIN_MANAGER is not define !
//#endif


    _pStoreCon = NULL;

    _papPallas = NEW EnemyPallas*[_num_Pallas];
    SplineSequence* pSplSeq;
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
//        pSplSeq = _pSplCon->use()->createSplineSequence(_papPallas[i]);
        _papPallas[i]->config(pSplSeq, NULL, NULL);
        //_papPallas[i]->setStore_Shot(_pStoreCon->use()); //弾設定
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
        pPallas->locate(_pSplCon->use()->_pSp->_X_basepoint[0], 0, 0);
        pPallas->_pKurokoA->setMvVelo(_mv_velo);
        pPallas->activateDelay(t*_interval_frames + 1);//_interval_frames間隔でActiveにする。
        t++;
        pActor = pActor->getNext();
    } while (!pActor->isFirst());
}

void FormationPallas001::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //編隊消滅時の実験
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pStore_EffectTurbo002->dispatchForce();
    if (pTurbo002) {
        pTurbo002->locateAs(prm_pActorLast);
        pTurbo002->activate();
    }
}

void FormationPallas001::processBehavior() {
}

FormationPallas001::~FormationPallas001() {
    _pSplCon->close();
    if (_pStoreCon) {
        _pStoreCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
