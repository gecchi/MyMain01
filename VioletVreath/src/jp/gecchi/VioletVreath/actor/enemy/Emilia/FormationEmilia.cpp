#include "FormationEmilia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmilia.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEmilia::FormationEmilia(const char* prm_name)
   : DefaultGeometricActor(prm_name) {
    _class_name = "FormationEmilia";
    pConn_depo_Emilia_ = getConnection_DepositoryManager("Emilia");
}

void FormationEmilia::updateRankParameter() {
    R_interval_frames_   = RF_FormationEmilia_LaunchInterval(G_RANK); //ŠÔŠu
    R_mv_velo_           = RF_FormationEmilia_MvVelo(G_RANK);         //‘¬“x
}

void FormationEmilia::initialize() {

}

void FormationEmilia::onActive() {
    updateRankParameter();
}

void FormationEmilia::processBehavior() {
    updateRankParameter();
    if (getActiveFrame() >= RF_FormationEmilia_DurationFrames(G_RANK)) { //oŒ»‚µ‘±‚¯‚éŽžŠÔ
        sayonara(20*60);
    } else {
        if (getActiveFrame() % R_interval_frames_ == 0) {
            EnemyEmilia* pEmilia = (EnemyEmilia*)(pConn_depo_Emilia_->peek()->dispatch());
            if (pEmilia) {
                const coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
                const coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
                Spacetime* pSpacetime =  P_GOD->getSpacetime();
                pEmilia->position(pSpacetime->_x_bound_right,
                                  RND(-(appearances_renge_y/2) , +(appearances_renge_y/2)),
                                  RND(-(appearances_renge_z/2) , +(appearances_renge_z/2)) );
                pEmilia->getKuroko()->setMvVelo(R_mv_velo_);
            }
        }
    }
}

FormationEmilia::~FormationEmilia() {
    pConn_depo_Emilia_->close();
}
