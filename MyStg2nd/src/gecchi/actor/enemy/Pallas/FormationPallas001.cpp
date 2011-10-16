#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationPallas001::FormationPallas001(const char* prm_name) :
        TreeFormation(prm_name, 30*60) {
    _class_name = "FormationPallas001";
    _num_Pallas      = R_FormationPallas001_Num;    //�ґ���
    _interval_frames = R_FormationPallas001_LaunchInterval;  //�p���X�̊Ԋu(frame)
    _mv_velo         = R_FormationPallas001_MvVelo; //���x
    //�p���X�ґ��쐬
    _pSplManufCon = connectSplineManufactureManager("Pallas01");
    _pDepoCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    SplineSequence* pSplSeq;
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //�X�v���C���ړ��v���O�����ݒ�
        pSplSeq = _pSplManufCon->use()->createSplineSequence(_papPallas[i]->_pKurokoA);
        _papPallas[i]->config(pSplSeq, NULL, NULL);
        //_papPallas[i]->setDepository_Shot(_pDepoCon->use()); //�e�ݒ�
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}
void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    GgafActor* pActor = getSubFirst();
    EnemyPallas* pPallas = NULL;
    int t = 0;
    do {
        pPallas = (EnemyPallas*)pActor;
        pPallas->_pSplSeq->setAbsoluteBeginCoordinate();
        pPallas->_pKurokoA->setMvVelo(_mv_velo);
        pPallas->activateDelay(t*_interval_frames + 1);//_interval_frames�Ԋu��Active�ɂ���B
        t++;
        pActor = pActor->getNext();
    } while (!pActor->isFirst());
}

void FormationPallas001::onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) {
    //�ґ����Ŏ��̎���
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDepo_EffectTurbo002->dispatchForce();
    if (pTurbo002) {
		pTurbo002->locateAs((GgafDxGeometricActor*)prm_pActor_LastDestroyed);
        pTurbo002->activate();
    }
}

void FormationPallas001::processBehavior() {
}

FormationPallas001::~FormationPallas001() {
    _pSplManufCon->close();
    if (_pDepoCon) {
        _pDepoCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
