#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GgafDx9Spline3D FormationIris001::_sp;

FormationIris001::FormationIris001(const char* prm_name) : FormationActor(prm_name, 30*60) {
    _class_name = "FormationIris001";
    _num_Iris       = 7*_RANK_;    //編隊数
    _frame_interval = 25/_RANK_;   //イリスの間隔(frame)
    _mv_velo  = 8000*_RANK_; //速度
    //スプライン移動の定義
    if (FormationIris001::_sp._num_basepoint == 0) {
        //後方から
        double p[][3] = { //           X  ,                       Y ,                         Z
           { MyShip::_lim_behaind - 500000 ,                    0.0 ,  MyShip::_lim_zleft * 0.8 },
           {      MyShip::_lim_front * 1.5 , MyShip::_lim_top * 0.2 ,                       0.0 },
           {      MyShip::_lim_front * 2.5 , MyShip::_lim_top * 0.5 , MyShip::_lim_zright * 0.3 },
           {      MyShip::_lim_front * 2.2 , MyShip::_lim_top * 1.0 ,                       0.0 },
           {      MyShip::_lim_front * 2.0 ,                    0.0 ,                       0.0 }
        };
        FormationIris001::_sp.init(p, 5, 0.2); //粒度 0.2
    }

    //イリス編隊作成
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        _papIris[i]->_pProgram_IrisMove =
                NEW GgafDx9FixedVelocitySplineProgram(&FormationIris001::_sp, 4000); //移動速度固定
        _papIris[i]->inactivateImmediately();
        addSubLast(_papIris[i]);
    }

    _pDispatcherCon = (DispatcherConnection*)God::_dispatcherManager.connect("DpCon_Shot001");
}

void FormationIris001::initialize() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->setGeometry(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zleft * 0.8);
        _papIris[i]->_pMover->setMvVelo(_mv_velo);
        _papIris[i]->setDispatcher_Shot(_pDispatcherCon->view()); //弾設定
        _papIris[i]->activateAfter(i*_frame_interval + 1);//_frame_interval間隔でActiveにする。
    }
}

FormationIris001::~FormationIris001() {
    _pDispatcherCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
