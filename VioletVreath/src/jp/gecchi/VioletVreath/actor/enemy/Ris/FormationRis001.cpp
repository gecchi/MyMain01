#include "FormationRis001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ris/EnemyRis.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationRis001::FormationRis001(const char* prm_name) : TreeFormation(prm_name) {
    _class_name = "FormationRis001";
    num_Ris_         = RF_FormationRis001_Num(G_RANK);    //�ґ���
    interval_frames_ = RF_FormationRis001_LaunchInterval(G_RANK);   //���X�̊Ԋu(frame)
    velo_mv_         = RF_FormationRis001_MvVelo(G_RANK); //���x
    //���X�ґ��쐬
    pSplSrcConnection_ = connectToSplineSourceManager("Spl_00201_"); //�X�v���C����`
    pConn_depo_ = connectToDepositoryManager("Shot001");
    pManufacture_ = NEW FixedVelocitySplineManufacture(pSplSrcConnection_->peek(), 10000);

    for (int i = 0; i < num_Ris_; i++) {
        EnemyRis* pRis = NEW EnemyRis("Ris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineLeader* pProgram = NEW FixedVelocitySplineKurokoLeader(pManufacture_, pRis->getKuroko()); //�ړ����x�Œ�
        pRis->config(pProgram, pConn_depo_->peek(), nullptr);
        appendFormationMember(pRis);
    }
}

void FormationRis001::initialize() {
}

void FormationRis001::onActive() {
}

void FormationRis001::processBehavior() {
    if (canCallUp() && (getActiveFrame()-1) % interval_frames_ == 0) {
        EnemyRis* pRis = (EnemyRis*)callUpMember();
        if (pRis) {
            pRis->setPosition(MyShip::lim_x_behaind_ - 500000, 0, MyShip::lim_z_left_ * 0.8);
            pRis->getKuroko()->setMvVelo(velo_mv_);
        }
    }
}

void FormationRis001::onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) {
    UTIL::performFormationDestroyAll((GgafDxFigureActor*)prm_pActor_last_destroyed);
}

FormationRis001::~FormationRis001() {
    GGAF_DELETE(pManufacture_);
    pSplSrcConnection_->close();
    pConn_depo_->close();
}
