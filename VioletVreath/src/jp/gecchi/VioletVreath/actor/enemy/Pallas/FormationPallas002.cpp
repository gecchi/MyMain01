#include "stdafx.h"
#include "FormationPallas002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/EnemyPallas.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas002::FormationPallas002(const char* prm_name) :
        TreeFormation(prm_name) {
    _class_name = "FormationPallas002";
    num_Pallas_      = RF_FormationPallas002_Num(_RANK_);  //�ґ���
    interval_frames_ = RF_FormationPallas002_LaunchInterval(_RANK_);  //�p���X�̊Ԋu(frame)
    velo_mv_         = RF_FormationPallas002_MvVelo(_RANK_); //���x
    //�p���X�ґ��쐬
    pSplManufConnection_ = connectToSplineManufactureManager("Pallas02");
//    pSplLineConnection_     = connectToSplineLineManager("Spl_Pallas01"); //�X�v���C����`
    //pDepoConnection_ = connectToDepositoryManager("Shot002");
    pDepoConnection_ = nullptr;
    papPallas_ = NEW EnemyPallas*[num_Pallas_];
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i] = NEW EnemyPallas("Pallas01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineKurokoLeader* pProgram = pSplManufConnection_->peek()->createKurokoLeader(papPallas_[i]->_pKurokoA); //�ړ����x�Œ�
        papPallas_[i]->config(pProgram, nullptr, nullptr);
        //papPallas_[i]->setDepository_Shot(pDepoConnection_->peek()); //�e�ݒ�
        papPallas_[i]->inactivateImmed();
        addFormationMember(papPallas_[i]);
    }
}

void FormationPallas002::onActive() {
    for (int i = 0; i < num_Pallas_; i++) {
        papPallas_[i]->locate(MyShip::lim_behaind_ *2 , P_MYSHIP->_Y+300000,  P_MYSHIP->_Z);
        papPallas_[i]->_pKurokoA->setMvVelo(velo_mv_);
        papPallas_[i]->activateDelay(i*interval_frames_ + 1);//interval_frames_�Ԋu��Active�ɂ���B
    }
}

void FormationPallas002::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

FormationPallas002::~FormationPallas002() {
    pSplManufConnection_->close();
    if (pDepoConnection_) {
        pDepoConnection_->close();
    }
    GGAF_DELETEARR(papPallas_);
}
