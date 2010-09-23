#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationIris002::FormationIris002(const char* prm_name) :
        GgafDx9FormationActor(prm_name, 30*60) { //30*60後にend()する。早く開放しすぎると Dispatcher の接続が切れるため。
    _class_name = "FormationIris002";
    _num_Iris       = 10*_RANK_;    //編隊数
    _frame_interval = 20/_RANK_+5;   //イリスの間隔(frame)
    _mv_velo  = 16000*_RANK_; //速度
    //スプライン移動の定義
    _pSplineCon = (Spline3DConnection*)(pGOD->_pSpline3DManager->getConnection("SpCon_002_02"));
    _pDispatcherCon = (DispatcherConnection*)(pGOD->_pDispatcherManager->getConnection("DpCon_Shot002"));
    //イリス編隊作成
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        GgafDx9SplineProgram* pProgram = NEW GgafDx9FixedVelocitySplineProgram(_papIris[i], _pSplineCon->refer(), 4000); //移動速度固定
        _papIris[i]->setSplineProgram(pProgram);
        _papIris[i]->setDispatcher_Shot(_pDispatcherCon->refer());
        _papIris[i]->inactivateImmediately();
        addSubLast(_papIris[i]);
    }
}

void FormationIris002::initialize() {

}

void FormationIris002::onActive() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->setGeometry(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zright * 0.8);
        _papIris[i]->_pMover->setMvVelo(_mv_velo);
        _papIris[i]->activateDelay(i*_frame_interval + 1);//_frame_interval間隔でActiveにする。
    }
}

FormationIris002::~FormationIris002() {
    _pSplineCon->close();
    _pDispatcherCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
