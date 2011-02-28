#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationThalia::FormationThalia(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationThalia";
    _num_Thalia     = 1+_RANK_*4;    //編隊数
    _frame_interval = 20-_RANK_*5;  //タリアの間隔(frame)
    _mv_velo        = 14000+_RANK_*10000; //速度

    _pDpcon = (DispatcherConnection*)(P_GOD->_pDispatcherManager->getConnection("DpCon_Shot004"));
    //編隊作成
    _papThalia = NEW EnemyThalia*[_num_Thalia];
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i] = NEW EnemyThalia("Thalia01");
        //スプライン移動プログラム設定
        _papThalia[i]->setSplineProgram(NULL);
        _papThalia[i]->setDispatcher_Shot(_pDpcon->refer()); //弾設定
        _papThalia[i]->inactivateImmediately();
        addSubLast(_papThalia[i]);
    }
}

void FormationThalia::initialize() {

}

void FormationThalia::onActive() {
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i]->locate(MyShip::_lim_behaind, -2000000 + (i * 400000), 0);
        _papThalia[i]->_pKuroko->setRzRyMvAng(0,0);
        _papThalia[i]->_pKuroko->setMvVelo(80000);
        _papThalia[i]->activateDelay(i*_frame_interval + 1);//_frame_interval間隔でActiveにする。
    }
}

FormationThalia::~FormationThalia() {
    _pDpcon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papThalia);
}
