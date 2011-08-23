#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas002::FormationPallas002(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas002";
    _num_Pallas      = R_FormationPallas002_Num;  //編隊数
    _interval_frames = R_FormationPallas002_LaunchInterval;  //パラスの間隔(frame)
    _mv_velo         = R_FormationPallas002_MvVelo; //速度
    //パラス編隊作成
    _pSplManufCon = connectSplineManufactureManager("Pallas02");
//    _pSplCon     = (Spline3DConnection*)(P_GOD->_pSpl3DManager->connect("SpCon_Pallas01")); //スプライン定義
    //_pDepoCon = connectDepositoryManager("StCon_Shot002", NULL);
    _pDepoCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = _pSplManufCon->use()->createSplineSequence(_papPallas[i]->_pKurokoA); //移動速度固定
        _papPallas[i]->config(pProgram, NULL, NULL);
        //_papPallas[i]->setDepository_Shot(_pDepoCon->use()); //弾設定
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}

void FormationPallas002::onActive() {
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i]->locate(MyShip::_lim_behaind *2 , P_MYSHIP->_Y+300000,  P_MYSHIP->_Z);
        _papPallas[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papPallas[i]->activateDelay(i*_interval_frames + 1);//_interval_frames間隔でActiveにする。
    }
}

FormationPallas002::~FormationPallas002() {
    _pSplManufCon->close();
    if (_pDepoCon) {
        _pDepoCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
