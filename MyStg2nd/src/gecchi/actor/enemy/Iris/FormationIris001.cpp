#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationIris001::FormationIris001(const char* prm_name) : FormationActor(prm_name, 30*60) {
    _class_name = "FormationIris001";
    _num_Iris        = R_FormationIris001_Num;    //編隊数
    _interval_frames = R_FormationIris001_LaunchInterval;   //イリスの間隔(frame)
    _mv_velo         = R_FormationIris001_MvVelo; //速度
    //イリス編隊作成
    _pSplLineCon   = connectSplineLineManager("SpCon_002_01"); //スプライン定義
    _pDepoCon = connectDepositoryManager("DpCon_Shot001", NULL);
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        //スプライン移動プログラム設定
        SplineSequence* pProgram = NEW FixedVelocitySplineSequence(_papIris[i]->_pKurokoA, _pSplLineCon->use(), 10000); //移動速度固定
        _papIris[i]->config(NULL, pProgram, _pDepoCon->use(), NULL);
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
        _papIris[i]->locate(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zleft * 0.8);
        _papIris[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papIris[i]->activateDelay(i*_interval_frames + 1);//_interval_frames間隔でActiveにする。
    }
}

FormationIris001::~FormationIris001() {
    _pSplLineCon->close();
    _pDepoCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
