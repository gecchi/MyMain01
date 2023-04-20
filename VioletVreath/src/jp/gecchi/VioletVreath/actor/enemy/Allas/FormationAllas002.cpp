#include "FormationAllas002.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas002::FormationAllas002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationAllas002";
    num_Allas_       = 0;
    interval_frames_ = 0;
    velo_mv_         = 0;

    //�A���X�ґ��쐬
    pConn_pCurveManuf_ = connectToCurveManufactureManager("Allas02");
    pConn_depo_ = nullptr;
    int max_num_Allas = RF_FormationAllas002_Num(G_MAX_RANK);  //�ő�ґ���
    for (int i = 0; i < max_num_Allas; i++) {
        EnemyAllas* pAllas = NEW EnemyAllas("Allas01");
        pAllas->config(pConn_pCurveManuf_->peek(), nullptr, nullptr);
        //pAllas->setDepository_Shot(pConn_depo_->peek()); //�e�ݒ�
        appendFormationMember(pAllas);
    }
}

void FormationAllas002::onActive() {

    num_Allas_       = RF_FormationAllas002_Num(G_RANK);  //�ґ���
    interval_frames_ = RF_FormationAllas002_LaunchInterval(G_RANK);  //�A���X�̊Ԋu(frame)
    velo_mv_         = RF_FormationAllas002_MvVelo(G_RANK); //���x


    for (int i = 0; i < num_Allas_; i++) {
        EnemyAllas* pAllas = (EnemyAllas*)calledUpMember(num_Allas_);
        if (pAllas) {
            pAllas->setPosition(MyShip::lim_x_behaind_ *2 , pMYSHIP->_y+300000,  pMYSHIP->_z);
            pAllas->getLocoVehicle()->setMvVelo(velo_mv_);
            pAllas->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
        }
    }
}

void FormationAllas002::onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDx::FigureActor*)prm_pActor_last_destroyed);
}

FormationAllas002::~FormationAllas002() {
    pConn_pCurveManuf_->close();
    if (pConn_depo_) {
        pConn_depo_->close();
    }
}
