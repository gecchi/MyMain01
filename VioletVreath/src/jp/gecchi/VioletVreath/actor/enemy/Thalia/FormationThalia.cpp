#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThalia::FormationThalia(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationThalia";
    num_Thalia_      = R_FormationThalia_Num;         //編隊のタリアの数
    interval_frames_ = R_FormationThalia_LaunchInterval;    //各タリアの出現間隔(frame)
    velo_mv_         = R_FormationThalia_MvVelo; //各タリアの移動速度

    pDpcon_ = connectToDepositoryManager("DpCon_Shot004", NULL);
    //編隊作成
    papThalia_ = NEW EnemyThalia*[num_Thalia_];
    for (int i = 0; i < num_Thalia_; i++) {
        papThalia_[i] = NEW EnemyThalia("Thalia01");
        //スプライン移動プログラム設定
        papThalia_[i]->setSplineSequence(NULL);
        papThalia_[i]->setDepository_Shot(pDpcon_->use()); //弾設定
        papThalia_[i]->inactivateImmed();
        addSubLast(papThalia_[i]);
    }
}

void FormationThalia::initialize() {

}

void FormationThalia::onActive() {
    for (int i = 0; i < num_Thalia_; i++) {
        papThalia_[i]->locate(MyShip::lim_behaind_, -2000000 + (i * 400000), 0);
        papThalia_[i]->_pKurokoA->setRzRyMvAng(0,0);
        papThalia_[i]->_pKurokoA->setMvVelo(80000);
        papThalia_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_間隔でActiveにする。
    }
}

FormationThalia::~FormationThalia() {
    pDpcon_->close();
    DELETEARR_IMPOSSIBLE_NULL(papThalia_);
}
