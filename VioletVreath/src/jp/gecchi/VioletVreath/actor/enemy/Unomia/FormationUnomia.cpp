#include "stdafx.h"
#include "FormationUnomia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/EnemyUnomia.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia::FormationUnomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationUnomia";

    //�E�[�m�~�A�ґ��p�f�|�W�g��
    pDepoConnection_Unomia_ = connect_DepositoryManager("EnemyUnomia4Formation");
    setFormationMember(pDepoConnection_Unomia_->peek());

    //�X�v���C����`�t�@�C����ǂݍ���
    papSplManufConnection_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        std::stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //���၄"FormationUnomia001_0"
        papSplManufConnection_[i] = connect_SplineManufactureManager(spl_id.str().c_str());
    }
    pDepo_Shot_ = getCommonDepository(Shot004);
    updateRankParameter();

}

void FormationUnomia::updateRankParameter() {
    RF_num_formation_col_ = RF_FormationUnomia001_Col(G_RANK);            //�ґ���
    RF_num_formation_row_ = RF_FormationUnomia001_Num(G_RANK);            //�P��̕ґ���
    RF_interval_frames_   = RF_FormationUnomia001_LaunchInterval(G_RANK); //�E�[�m�~�A�̊Ԋu(frame)
    RF_mv_velo_           = RF_FormationUnomia001_MvVelo(G_RANK);         //���x
}

void FormationUnomia::initialize() {
//    if (pDepoConnection_Unomia_->chkFirstConnectionIs(this)) {
//        _TRACE_("pDepoConnection_Unomia_ �́A���V("<<this<<")����Ă��G�w���I")
//        getPlatformScene()->getSceneDirector()->addSubGroup(
//                pDepoConnection_Unomia_->peek()->extract()
//                );
//    }
}

void FormationUnomia::onActive() {
    updateRankParameter();
}

void FormationUnomia::onDestroyAll(GgafActor* prm_pActor_last_destroyed) {
    UTIL::proceedFormationDestroyAll((GgafDxDrawableActor*)prm_pActor_last_destroyed);
}

void FormationUnomia::processBehavior() {
    if (canCallUp() && (getActiveFrame() % RF_interval_frames_ == 0)) {
        for (int i = 0; i < RF_num_formation_col_; i++) {
            EnemyUnomia* pUnomia = (EnemyUnomia*)callUpMember(RF_num_formation_col_*RF_num_formation_row_);
            if (pUnomia) {
                SplineKurokoLeader* pKurokoLeader = papSplManufConnection_[i]->peek()->
                                              createKurokoLeader(pUnomia->getKuroko());
                pUnomia->config(pKurokoLeader, nullptr, nullptr);
                pUnomia->getKuroko()->setMvVelo(RF_mv_velo_);
                onCallUpUnomia(pUnomia, i); //�t�H�[���[�V�����ʎ����̏���
            }
        }
    }

    if (getActiveFrame() == 60 * 20) {
        MyShip* pMy = P_MYSHIP;
        GgafActor* pFollower = _listFollower.getCurrent();
        int num_follwer = _listFollower.length();
        EnemyUnomia* pUnomia;
        GgafDxGeometricActor* pShot;
        for (int i = 0; i < num_follwer; i++) {
            pUnomia = (EnemyUnomia*)pFollower;
            pShot = (GgafDxGeometricActor*)pDepo_Shot_->dispatch();
            if (pShot) {
                pShot->positionAs(pUnomia);
                GgafDxKuroko* pShot_pKuroko = pShot->getKuroko();
                pShot_pKuroko->setMvAngTwd(pMy);
                pShot_pKuroko->setMvVelo(PX_C(10));
                pShot_pKuroko->setMvAcce(0);
            }
            pFollower = _listFollower.next();
        }
    }
}

FormationUnomia::~FormationUnomia() {
    pDepoConnection_Unomia_->close();
    for (int i = 0; i < 7; i++) {
        papSplManufConnection_[i]->close();
    }
    GGAF_DELETEARR(papSplManufConnection_);
}
