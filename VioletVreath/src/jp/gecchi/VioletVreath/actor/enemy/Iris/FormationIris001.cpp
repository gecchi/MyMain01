#include "stdafx.h"
#include "FormationIris001.h"


#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/EnemyIris.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationIris001::FormationIris001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationIris001";
    num_Iris_        = RF_FormationIris001_Num(G_RANK);    //�ґ���
    interval_frames_ = RF_FormationIris001_LaunchInterval(G_RANK);   //�C���X�̊Ԋu(frame)
    velo_mv_         = RF_FormationIris001_MvVelo(G_RANK); //���x
    //�C���X�ґ��쐬
    pSplLineConnection_ = connect_SplineLineManager("Spl_00201_"); //�X�v���C����`
    pDepoConnection_ = connect_DepositoryManager("Shot001");
    for (int i = 0; i < num_Iris_; i++) {
        EnemyIris* pIris = NEW EnemyIris("Iris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineKurokoLeader* pProgram = NEW FixedVelocitySplineKurokoLeader(
                                         pIris->_pKurokoA, pSplLineConnection_->peek(), 10000); //�ړ����x�Œ�
        pIris->config(pProgram, pDepoConnection_->peek(), nullptr);
        addFormationMember(pIris);
    }
}

void FormationIris001::initialize() {
}

void FormationIris001::onActive() {
}

void FormationIris001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyIris* pIris = (EnemyIris*)callUpMember();
        if (pIris) {
            pIris->locate(MyShip::lim_X_behaind_ - 500000, 0, MyShip::lim_Z_left_ * 0.8);
            pIris->_pKurokoA->setMvVelo(velo_mv_);
        }
    }
}

void FormationIris001::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationIris001::~FormationIris001() {
    pSplLineConnection_->close();
    pDepoConnection_->close();
}
