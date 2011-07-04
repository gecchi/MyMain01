#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001::FormationPallas001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas001";
    _num_Pallas      = R_FormationPallas001_Num;    //�ґ���
    _interval_frames = R_FormationPallas001_LaunchInterval;  //�p���X�̊Ԋu(frame)
    _mv_velo         = R_FormationPallas001_MvVelo; //���x
    //�p���X�ґ��쐬
    _pSplineCon     = (SplineConnection*)(P_GOD->_pSplineManager->getConnection("Pallas01")); //�X�v���C����`
    _pStoreCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //�X�v���C���ړ��v���O�����ݒ�
        _papPallas[i]->config(_pSplineCon->refer()->makeSplineProgram(_papPallas[i]), NULL, NULL);
        //_papPallas[i]->setStore_Shot(_pStoreCon->refer()); //�e�ݒ�
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}
void FormationPallas001::initialize() {
}

void FormationPallas001::onActive() {
    GgafMainActor* pActor = getSubFirst();
    EnemyPallas* pPallas = NULL;
    int t = 0;
    do {
        pPallas = (EnemyPallas*)pActor;
        pPallas->locate(_pSplineCon->refer()->_pSp->_X_basepoint[0], 0, 0);
        pPallas->_pKurokoA->setMvVelo(_mv_velo);
        pPallas->activateDelay(t*_interval_frames + 1);//_interval_frames�Ԋu��Active�ɂ���B
        t++;
        pActor = pActor->getNext();
    } while (!pActor->isFirst());
}

void FormationPallas001::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //�ґ����Ŏ��̎���
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pStore_EffectTurbo002->employForce();
    if (pTurbo002) {
        pTurbo002->locateAs(prm_pActorLast);
        pTurbo002->activate();
    }
}

void FormationPallas001::processBehavior() {
}

FormationPallas001::~FormationPallas001() {
    _pSplineCon->close();
    if (_pStoreCon) {
        _pStoreCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
