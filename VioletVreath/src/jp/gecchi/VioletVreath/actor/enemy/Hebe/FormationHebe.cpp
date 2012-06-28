#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationHebe::FormationHebe(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationHebe";

    //ヘーベ編隊用デポジトリ
    pDepoCon_Hebe_ = connectDepositoryManager("DpCon_EnemyHebe4Formation", this);
    setFormationAbleActorDepository(pDepoCon_Hebe_->fetch());

    //スプライン定義ファイルを読み込む
    pSplManufCon_ = connectSplineManufactureManager("hilbert");
    pCon_ShotDepo_ = connectDepositoryManager("DpCon_Shot004", NULL); //Hebeの弾;
    pDepo_Shot_ = pCon_ShotDepo_->fetch();
    updateRankParameter();
}

void FormationHebe::updateRankParameter() {
    r_num_formation_     = R_FormationHebe_Num;            //編隊数
    r_interval_frames_   = R_FormationHebe_LaunchInterval; //ヘーベの間隔(frame)
    r_mv_velo_           = R_FormationHebe_MvVelo;         //速度


}

void FormationHebe::initialize() {
}

void FormationHebe::onActive() {
    updateRankParameter();
}

void FormationHebe::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    //編隊消滅時の実験
    EffectTurbo002* pTurbo002 = employFromCommon(EffectTurbo002);
    if (pTurbo002) {
        pTurbo002->locateWith((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
    //編隊全滅アイテム出現
    Item* pItem = employFromCommon(MagicPointItem002);
    if (pItem) {
        pItem->locateWith((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
}


void FormationHebe::processBehavior() {
    if (! isAllCalledUp() && (getActivePartFrame() % r_interval_frames_ == 0)) {
        EnemyHebe* pHebe = (EnemyHebe*)callUpUntil(r_num_formation_);
        if (pHebe) {
            SplineSequence* pSplSeq = pSplManufCon_->fetch()->
                                          createSplineSequence(pHebe->_pKurokoA);
            pHebe->config(pSplSeq, NULL, NULL);
            pHebe->_pKurokoA->setMvVelo(r_mv_velo_);
            processOnActiveHebe(pHebe); //フォーメーション個別実装の処理
        }
    }


    if (getActivePartFrame() == 60 * 20) {
        MyShip* pMy = P_MYSHIP;
        GgafActor* pFllower = _listFllower.getCurrent();
        int num_follwer = _listFllower.length();
        EnemyHebe* pHebe;
        GgafDxGeometricActor* pShot;
        for (int i = 0; i < num_follwer; i++) {
            pHebe = (EnemyHebe*)pFllower;
            pShot = (GgafDxGeometricActor*)pDepo_Shot_->dispatch();
            if (pShot) {
                pShot->locateWith(pHebe);
                pShot->_pKurokoA->setMvAng(pMy);
                pShot->_pKurokoA->setMvVelo(PX_C(10));
                pShot->_pKurokoA->setMvAcce(0);
            }
            pFllower = _listFllower.next();
        }
    }
}

FormationHebe::~FormationHebe() {
    pDepoCon_Hebe_->close();
    pSplManufCon_->close();
    if (pCon_ShotDepo_) {
        pCon_ShotDepo_->close();
    }
}
