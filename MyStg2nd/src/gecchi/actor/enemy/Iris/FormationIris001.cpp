#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationIris001::FormationIris001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationIris001";
    _num_Iris       = 7+_RANK_*7;    //編隊数
    _frame_interval = 25-_RANK_*20;   //イリスの間隔(frame)
    _mv_velo  = 8000+_RANK_*8000; //速度
    //イリス編隊作成
    _pSplineCon     = (Spline3DConnection*)(pGOD->_pSpline3DManager->getConnection("SpCon_002_01")); //スプライン定義
    _pDispatcherCon = (DispatcherConnection*)(pGOD->_pDispatcherManager->getConnection("DpCon_Shot001"));
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        GgafDx9SplineProgram* pProgram = NEW GgafDx9FixedVelocitySplineProgram(_papIris[i], _pSplineCon->refer(), 4000); //移動速度固定
        _papIris[i]->setSplineProgram(pProgram);
        _papIris[i]->setDispatcher_Shot(_pDispatcherCon->refer()); //弾設定
        _papIris[i]->inactivateImmediately();
        addSubLast(_papIris[i]);
    }
}

void FormationIris001::initialize() {
    //編隊作成はonActive()で行わうこと。
    //ActorTableScene で active にされるタイミングは変動するため
}

void FormationIris001::onActive() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->setGeometry(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zleft * 0.8);
        _papIris[i]->_pMover->setMvVelo(_mv_velo);
        _papIris[i]->activateDelay(i*_frame_interval + 1);//_frame_interval間隔でActiveにする。
    }
}

FormationIris001::~FormationIris001() {
    _pSplineCon->close();
    _pDispatcherCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
