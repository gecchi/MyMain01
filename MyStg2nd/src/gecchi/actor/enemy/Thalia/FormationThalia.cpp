#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationThalia::FormationThalia(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationThalia";
    _num_Thalia       = 7*_RANK_;    //編隊数
    _frame_interval = 25/_RANK_+5;   //間隔(frame)
    _mv_velo  = 300000*_RANK_;         //初期速度
    //編隊作成
    _papThalia = NEW EnemyThalia*[_num_Thalia];
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i] = NEW EnemyThalia("Thalia01");
        //スプライン移動プログラム設定
        _papThalia[i]->setSplineProgram(NULL);
        _papThalia[i]->setDispatcher_Shot(NULL); //弾設定
        _papThalia[i]->inactivateImmediately();
        addSubLast(_papThalia[i]);
    }
}

void FormationThalia::initialize() {

}

void FormationThalia::onActive() {
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i]->setGeometry(MyShip::_lim_behaind - 500000, 300000, -2000000 + (i * 500000));
        _papThalia[i]->_pMover->setRzRyMvAng(0,0);
        _papThalia[i]->_pMover->setMvVelo(_mv_velo);
        _papThalia[i]->activateDelay(i*_frame_interval + 1);//_frame_interval間隔でActiveにする。
    }
}

FormationThalia::~FormationThalia() {
    DELETEARR_IMPOSSIBLE_NULL(_papThalia);
}
