#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEunomia";

    //GEm~AÒàpf|Wg
    pDepoCon_Eunomia_ = connectDepositoryManager("DpCon_EnemyEunomia4Formation", this);
    setFormationAbleActorDepository(pDepoCon_Eunomia_->fetch());

    //XvCè`t@CðÇÝÞ
    papSplManufCon_ = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //á"FormationEunomia001_0"
        papSplManufCon_[i] = connectSplineManufactureManager(spl_id.str().c_str());
    }
    pCon_ShotDepo_ = connectDepositoryManager("DpCon_Shot004", NULL); //EunomiaÌe;
    pDepo_Shot_ = pCon_ShotDepo_->fetch();
    updateRankParameter();
}

void FormationEunomia::updateRankParameter() {
    R_num_formation_col_ = R_FormationEunomia001_Col;            //Òàñ
    R_num_formation_row_ = R_FormationEunomia001_Num;            //PñÌÒà
    R_interval_frames_   = R_FormationEunomia001_LaunchInterval; //GEm~AÌÔu(frame)
    R_mv_velo_           = R_FormationEunomia001_MvVelo;         //¬x
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
        pTurbo002->locatedBy((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
    //ÒàSÅACeo»
    Item* pItem = employFromCommon(MagicPointItem002);
    if (pItem) {
        pItem->locatedBy((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
}


void FormationEunomia::processBehavior() {
    if (! isAllCalledUp() && (getActivePartFrame() % R_interval_frames_ == 0)) {
        for (int i = 0; i < R_num_formation_col_; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUpUntil(R_num_formation_col_*R_num_formation_row_);
            if (pEunomia) {
                SplineSequence* pSplSeq = papSplManufCon_[i]->fetch()->
                                              createSplineSequence(pEunomia->_pKurokoA);
                pEunomia->config(pSplSeq, NULL, NULL);
                pEunomia->_pKurokoA->setMvVelo(R_mv_velo_);
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
                pShot->locatedBy(pEunomia);
                pShot->_pKurokoA->setMvAng(pMy);
                pShot->_pKurokoA->setMvVelo(PXCO(10));
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
    if (pCon_ShotDepo_) {
        pCon_ShotDepo_->close();
    }
}
