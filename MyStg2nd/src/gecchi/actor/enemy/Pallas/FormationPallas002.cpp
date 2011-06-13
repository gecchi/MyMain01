#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas002::FormationPallas002(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas002";
    _num_Pallas     = 12+_RANK_*8;    //編隊数
    _interval_frames = 2 + (10-_RANK_*5);  //パラスの間隔(frame)
    _mv_velo        = 10000+_RANK_*10000; //速度
    //パラス編隊作成
    _pSplineCon     = (Spline3DConnection*)(P_GOD->_pSpline3DManager->getConnection("SpCon_Pallas01")); //スプライン定義
    //_pDispatcherCon = (DispatcherConnection*)(P_GOD->_pDispatcherManager->getConnection("DpCon_Shot002"));
    _pDispatcherCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        GgafDx9SplineProgram* pProgram = NEW GgafDx9FixedVelocitySplineProgram(_papPallas[i], _pSplineCon->refer(), 8000); //移動速度固定
        _papPallas[i]->config(pProgram, NULL, NULL);
        //_papPallas[i]->setDispatcher_Shot(_pDispatcherCon->refer()); //弾設定
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}

void FormationPallas002::onActive() {
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i]->locate(MyShip::_lim_behaind *2 , P_MYSHIP->_Y+300000,  P_MYSHIP->_Z);
        _papPallas[i]->_pMvNavigator->setMvVelo(_mv_velo);
        _papPallas[i]->activateDelay(i*_interval_frames + 1);//_interval_frames間隔でActiveにする。
    }
}

FormationPallas002::~FormationPallas002() {
    _pSplineCon->close();
    if (_pDispatcherCon) {
        _pDispatcherCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
