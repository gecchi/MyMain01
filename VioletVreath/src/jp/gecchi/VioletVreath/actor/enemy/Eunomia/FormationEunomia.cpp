#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEunomia";

    //GEm~AÒàpf|Wg
    pDepoCon_Eunomia_ = connectToDepositoryManager("Conn_EnemyEunomia4Formation", this);
    setFormationAbleActorDepository(pDepoCon_Eunomia_->fetch());

    //XvCè`t@CðÇÝÞ
    papSplManufCon_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        std::stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //á"FormationEunomia001_0"
        papSplManufCon_[i] = connectToSplineManufactureManager(spl_id.str().c_str());
    }
    pConn_ShotDepo_ = connectToDepositoryManager("Conn_Shot004", NULL); //EunomiaÌe;
    pDepo_Shot_ = pConn_ShotDepo_->fetch();
    updateRankParameter();
}

void FormationEunomia::updateRankParameter() {
    RR_num_formation_col_ = RR_FormationEunomia001_Col(_RANK_);            //Òàñ
    RR_num_formation_row_ = RR_FormationEunomia001_Num(_RANK_);            //PñÌÒà
    RR_interval_frames_   = RR_FormationEunomia001_LaunchInterval(_RANK_); //GEm~AÌÔu(frame)
    RR_mv_velo_           = RR_FormationEunomia001_MvVelo(_RANK_);         //¬x
}

void FormationEunomia::initialize() {
}

void FormationEunomia::onActive() {
    updateRankParameter();
}

void FormationEunomia::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    //ÒàÁÅÌÀ±
    EffectTurbo002* pTurbo002 = employFromCommon(EffectTurbo002);
    if (pTurbo002) {
        pTurbo002->locateWith((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
    //ÒàSÅACeo»
    Item* pItem = employFromCommon(MagicPointItem002);
    if (pItem) {
        pItem->locateWith((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
}


void FormationEunomia::processBehavior() {
    if (! isAllCalledUp() && (getActivePartFrame() % RR_interval_frames_ == 0)) {
        for (int i = 0; i < RR_num_formation_col_; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUpUntil(RR_num_formation_col_*RR_num_formation_row_);
            if (pEunomia) {
                SplineSequence* pSplSeq = papSplManufCon_[i]->fetch()->
                                              createSplineSequence(pEunomia->_pKurokoA);
                pEunomia->config(pSplSeq, NULL, NULL);
                pEunomia->_pKurokoA->setMvVelo(RR_mv_velo_);
                processOnActiveEunomia(pEunomia, i); //tH[[VÂÊÀÌ
            }
        }
    }


    if (getActivePartFrame() == 60 * 20) {
        MyShip* pMy = P_MYSHIP;
        GgafActor* pFllower = _listFllower.getCurrent();
        int num_follwer = _listFllower.length();
        EnemyEunomia* pEunomia;
        GgafDxGeometricActor* pShot;
        for (int i = 0; i < num_follwer; i++) {
            pEunomia = (EnemyEunomia*)pFllower;
            pShot = (GgafDxGeometricActor*)pDepo_Shot_->dispatch();
            if (pShot) {
                pShot->locateWith(pEunomia);
                pShot->_pKurokoA->setMvAng(pMy);
                pShot->_pKurokoA->setMvVelo(PX_C(10));
                pShot->_pKurokoA->setMvAcce(0);
            }
            pFllower = _listFllower.next();
        }
    }
}

FormationEunomia::~FormationEunomia() {
    pDepoCon_Eunomia_->close();
    for (int i = 0; i < 7; i++) {
        papSplManufCon_[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(papSplManufCon_);
    if (pConn_ShotDepo_) {
        pConn_ShotDepo_->close();
    }
}
