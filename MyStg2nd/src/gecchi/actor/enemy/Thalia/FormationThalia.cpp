#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationThalia::FormationThalia(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationThalia";
    _num_Thalia      = R_FormationThalia_Num;         //編隊のタリアの数
    _interval_frames = R_FormationThalia_LaunchInterval;    //各タリアの出現間隔(frame)
    _mv_velo         = R_FormationThalia_MvVelo; //各タリアの移動速度

    _pDpcon = connectDepositoryManager("DpCon_Shot004", NULL);
    //編隊作成
    _papThalia = NEW EnemyThalia*[_num_Thalia];
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i] = NEW EnemyThalia("Thalia01");
        //スプライン移動プログラム設定
        _papThalia[i]->setSplineSequence(NULL);
        _papThalia[i]->setDepository_Shot(_pDpcon->use()); //弾設定
        _papThalia[i]->inactivateImmed();
        addSubLast(_papThalia[i]);
    }
}

void FormationThalia::initialize() {

}

void FormationThalia::onActive() {
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i]->locate(MyShip::_lim_behaind, -2000000 + (i * 400000), 0);
        _papThalia[i]->_pKurokoA->setRzRyMvAng(0,0);
        _papThalia[i]->_pKurokoA->setMvVelo(80000);
        _papThalia[i]->activateDelay(i*_interval_frames + 1);//_interval_frames間隔でActiveにする。
    }
}

FormationThalia::~FormationThalia() {
    _pDpcon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papThalia);
}
