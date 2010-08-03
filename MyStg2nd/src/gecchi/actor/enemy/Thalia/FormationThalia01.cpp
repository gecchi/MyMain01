#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationThalia001::FormationThalia001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationThalia001";
    _num_Thalia       = 7*_RANK_;    //編隊数
    _frame_interval = 25/_RANK_+5;   //イリスの間隔(frame)
    _mv_velo  = 8000*_RANK_; //速度
    //イリス編隊作成
    _pSplineCon     = (Spline3DConnection*)(pGOD->_pSpline3DManager->getConnection("SpCon_002_01")); //スプライン定義
    _pDispatcherCon = (DispatcherConnection*)(pGOD->_pDispatcherManager->getConnection("DpCon_Shot001"));
    _papThalia = NEW EnemyThalia*[_num_Thalia];
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i] = NEW EnemyThalia("Thalia01");
        //スプライン移動プログラム設定
        GgafDx9SplineProgram* pProgram = NEW GgafDx9FixedVelocitySplineProgram(_papThalia[i], _pSplineCon->refer(), 4000); //移動速度固定
        _papThalia[i]->setSplineProgram(pProgram);
        _papThalia[i]->setDispatcher_Shot(_pDispatcherCon->refer()); //弾設定
        _papThalia[i]->inactivateImmediately();
        addSubLast(_papThalia[i]);
    }
}

void FormationThalia001::initialize() {
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i]->setGeometry(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zleft * 0.8);
        _papThalia[i]->_pMover->setMvVelo(_mv_velo);
        _papThalia[i]->activateAfter(i*_frame_interval + 1);//_frame_interval間隔でActiveにする。
    }
}

FormationThalia001::~FormationThalia001() {
    _pSplineCon->close();
    _pDispatcherCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papThalia);
}
