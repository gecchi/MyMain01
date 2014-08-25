#include "FormationEmilia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmilia.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEmilia::FormationEmilia(const char* prm_name)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEmilia";
    pConn_depo_Emilia_ = getConnection_DepositoryManager("Emilia");
    pConn_depo_Fragment_ = getConnection_DepositoryManager("EmiliaFragment");
    pConn_depo_Fragment_2_ = getConnection_DepositoryManager("EmiliaFragment2");
    pConn_depo_Fragment_3_ = getConnection_DepositoryManager("EmiliaFragment3");
    setFormationMember(pConn_depo_Emilia_->peek());
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

void FormationEmilia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

void FormationEmilia::processBehavior() {
    updateRankParameter();
    if (getActiveFrame() >= RF_FormationEmilia_DurationFrames(G_RANK)) {
        sayonara(20*60);
    } else {
        if (canCallUp() && (getActiveFrame() % R_interval_frames_ == 0)) {
            EnemyEmilia* pEmilia = (EnemyEmilia*)callUpMember();
            if (pEmilia) {
                pEmilia->getKuroko()->setMvVelo(R_mv_velo_);
            }
        }
    }
}

FormationEmilia::~FormationEmilia() {
    pConn_depo_Emilia_->close();
    pConn_depo_Fragment_->close();
    pConn_depo_Fragment_2_->close();
    pConn_depo_Fragment_3_->close();
}
