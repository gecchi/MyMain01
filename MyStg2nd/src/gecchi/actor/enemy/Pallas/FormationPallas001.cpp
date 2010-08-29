#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas001::FormationPallas001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas001";
    _num_Pallas     = 12*_RANK_;    //�ґ���
    _frame_interval = 5/_RANK_+5;  //�p���X�̊Ԋu(frame)
    _mv_velo        = 10000*_RANK_; //���x
    //�p���X�ґ��쐬
    _pSplineCon     = (Spline3DConnection*)(pGOD->_pSpline3DManager->getConnection("SpCon_Pallas01")); //�X�v���C����`
    //_pDispatcherCon = (DispatcherConnection*)(pGOD->_pDispatcherManager->getConnection("DpCon_Shot001")); //�p���X�e�̃f�B�X�p�b�`���[
    _pDispatcherCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //�X�v���C���ړ��v���O�����ݒ�
        //GgafDx9SplineProgram* pProgram = NEW GgafDx9FixedVelocitySplineProgram(_papPallas[i], _pSplineCon->refer(), 7000); //�ړ����x�Œ�
        GgafDx9SplineProgram* pProgram = NEW GgafDx9FixedFrameSplineProgram(_papPallas[i], _pSplineCon->refer(), 3600, 6000); //�ړ��t���[�����Œ�
        _papPallas[i]->config(pProgram, NULL, NULL);
        //_papPallas[i]->setDispatcher_Shot(_pDispatcherCon->refer()); //�e�ݒ�
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}
void FormationPallas001::initialize() {
//    GgafMainActor* pActor = getSubFirst();
//    EnemyPallas* pPallas = NULL;
//    int t = 0;
//    do {
//        pPallas = (EnemyPallas*)pActor;
//        pPallas->setGeometry(_pSplineCon->refer()->_X_basepoint[0], 0, 0);
//        pPallas->_pMover->setMvVelo(_mv_velo);
//        pPallas->activateAfter(t*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
//        t++;
//        pActor = pActor->getNext();
//    } while (!pActor->isFirst());

//
//    for (GgafMainActor* pActor = getSubFirst(); i < _num_Pallas; i++) {
//        _papPallas[i]->setGeometry(_pSplineCon->refer()->_X_basepoint[0] ,
//                                   0,
//                                   0);
//        _papPallas[i]->_pMover->setMvVelo(_mv_velo);
//        _papPallas[i]->activateAfter(i*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
//    }
}

void FormationPallas001::onActive() {
    GgafMainActor* pActor = getSubFirst();
    EnemyPallas* pPallas = NULL;
    int t = 0;
    do {
        pPallas = (EnemyPallas*)pActor;
        pPallas->setGeometry(_pSplineCon->refer()->_X_basepoint[0], 0, 0);
        pPallas->_pMover->setMvVelo(_mv_velo);
        pPallas->activateAfter(t*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
        t++;
        pActor = pActor->getNext();
    } while (!pActor->isFirst());


}
void FormationPallas001::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //�ґ����Ŏ��̎���
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)pCOMMONSCENE->_pDispatcher_EffectTurbo002->employForce();
     if (pTurbo002 != NULL) {
         pTurbo002->setGeometry(prm_pActorLast);
         pTurbo002->activate();
     }
}

void FormationPallas001::processBehavior() {


}


FormationPallas001::~FormationPallas001() {
    _pSplineCon->close();
    if (_pDispatcherCon) {
        _pDispatcherCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
