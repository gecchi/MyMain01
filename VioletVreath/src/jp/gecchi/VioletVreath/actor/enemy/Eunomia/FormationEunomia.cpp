#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id)
   : DepositoryFormation(prm_name, 20*60) {
    _class_name = "FormationEunomia";

    //�G�E�m�~�A�ґ��p�f�|�W�g��
    _pDepoCon_Eunomia = connectToDepositoryManager("DpCon_EnemyEunomia4Formation", this);
    setFormationAbleActorDepository(_pDepoCon_Eunomia->use());

    //�X�v���C����`�t�@�C����ǂݍ���
    _papSplManufCon = NEW SplineManufactureConnection*[7];
    for (int i = 0; i < 7; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //���၄"FormationEunomia001_0"
        _papSplManufCon[i] = connectSplineManufactureManager(spl_id.str().c_str());
    }
    _pDepoCon_shot = NULL;
    updateRankParameter();
}

void FormationEunomia::updateRankParameter() {
    _R_num_formation_col = R_FormationEunomia001_Col;            //�ґ���
    _R_num_formation_row = R_FormationEunomia001_Num;            //�P��̕ґ���
    _R_interval_frames   = R_FormationEunomia001_LaunchInterval; //�G�E�m�~�A�̊Ԋu(frame)
    _R_mv_velo           = R_FormationEunomia001_MvVelo;         //���x
}

void FormationEunomia::initialize() {
}

void FormationEunomia::onActive() {
    updateRankParameter();
}

void FormationEunomia::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    //�ґ����Ŏ��̎���
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDepo_EffectTurbo002->dispatchForce();
    if (pTurbo002) {
        pTurbo002->locateAs((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
        pTurbo002->activate();
    }
    //�ґ��S�ŃA�C�e���o��
    Item* pItem = (Item*)P_COMMON_SCENE->_pDP_MagicPointItem002->dispatch();
    if (pItem) {
        pItem->locateAs((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
    }
}


void FormationEunomia::processBehavior() {
    if (! isAllCalledUp() && (getActivePartFrame() % _R_interval_frames == 0)) {
        for (int i = 0; i < _R_num_formation_col; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUpUntil(_R_num_formation_col*_R_num_formation_row);
            if (pEunomia) {
                SplineSequence* pSplSeq = _papSplManufCon[i]->use()->
                                              createSplineSequence(pEunomia->_pKurokoA);
                pEunomia->config(pSplSeq, NULL, NULL);
                pEunomia->_pKurokoA->setMvVelo(_R_mv_velo);
                processOnActiveEunomia(pEunomia, i); //�t�H�[���[�V�����ʎ����̏���
            }
        }
    }
}

FormationEunomia::~FormationEunomia() {
    _pDepoCon_Eunomia->close();
    for (int i = 0; i < 7; i++) {
        _papSplManufCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplManufCon);
    if (_pDepoCon_shot) {
        _pDepoCon_shot->close();
    }
}
