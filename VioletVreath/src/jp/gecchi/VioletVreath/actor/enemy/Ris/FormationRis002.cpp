#include "stdafx.h"
#include "FormationRis002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ris/EnemyRis.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationRis002::FormationRis002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationRis002";
    num_Ris_        = RF_FormationRis002_Num(G_RANK);    //�ґ���
    interval_frames_ = RF_FormationRis002_LaunchInterval(G_RANK);   //���X�̊Ԋu(frame)
    velo_mv_         = RF_FormationRis002_MvVelo(G_RANK); //���x
    //�X�v���C���ړ��̒�`
    pSplLineConnection_ = connect_SplineLineManager("Spl_00202_");
    pDepoConnection_ = connect_DepositoryManager("Shot002");
    //���X�ґ��쐬
    for (int i = 0; i < num_Ris_; i++) {
        EnemyRis* pRis = NEW EnemyRis("Ris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineKurokoLeader* pProgram = NEW FixedVelocitySplineKurokoLeader(
                                         pRis->_pKurokoA, pSplLineConnection_->peek(), 10000); //�ړ����x�Œ�
        pRis->config(pProgram, pDepoConnection_->peek(), nullptr);
        addFormationMember(pRis);
    }
}

void FormationRis002::initialize() {
}

void FormationRis002::onActive() {
}

void FormationRis002::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyRis* pRis = (EnemyRis*)callUpMember();
        if (pRis) {
            pRis->position(MyShip::lim_x_behaind_ - 500000, 0, MyShip::lim_z_right_ * 0.8);
            pRis->_pKurokoA->setMvVelo(velo_mv_);
        }
    }
}

void FormationRis002::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationRis002::~FormationRis002() {
    pSplLineConnection_->close();
    pDepoConnection_->close();
}
