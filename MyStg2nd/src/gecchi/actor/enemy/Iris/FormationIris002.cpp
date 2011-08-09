#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationIris002::FormationIris002(const char* prm_name) :
        GgafDx9FormationActor(prm_name, 30*60) { //30*60後にend()する。早く開放しすぎると Store の接続が切れるため。
    _class_name = "FormationIris002";
    _num_Iris        = R_FormationIris002_Num;    //編隊数
    _interval_frames = R_FormationIris002_LaunchInterval;   //イリスの間隔(frame)
    _mv_velo         = R_FormationIris002_MvVelo; //速度
    //スプライン移動の定義
    _pSplCon = (Spline3DConnection*)(P_GOD->_pSpl3DManager->connect("SpCon_002_02"));
    _pStoreCon = (StoreConnection*)(P_GOD->_pStoreManager->connect("StCon_Shot002"));
    //イリス編隊作成
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = NEW FixedVelocitySplineSequence(_papIris[i], _pSplCon->use(), 4000); //移動速度固定
        _papIris[i]->setSplineSequence(pProgram);
        _papIris[i]->setStore_Shot(_pStoreCon->use());
        _papIris[i]->inactivateImmediately();
        addSubLast(_papIris[i]);
    }
}

void FormationIris002::initialize() {

}

void FormationIris002::onActive() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->locate(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zright * 0.8);
        _papIris[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papIris[i]->activateDelay(i*_interval_frames + 1);//_interval_frames間隔でActiveにする。
    }
}

FormationIris002::~FormationIris002() {
    _pSplCon->close();
    _pStoreCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
