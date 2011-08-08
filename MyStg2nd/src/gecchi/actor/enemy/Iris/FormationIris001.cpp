#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationIris001::FormationIris001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationIris001";
    _num_Iris        = R_FormationIris001_Num;    //�ґ���
    _interval_frames = R_FormationIris001_LaunchInterval;   //�C���X�̊Ԋu(frame)
    _mv_velo         = R_FormationIris001_MvVelo; //���x
    //�C���X�ґ��쐬
    _pSplCon     = (Spline3DConnection*)(P_GOD->_pSpl3DManager->getConnection("SpCon_002_01")); //�X�v���C����`
    _pStoreCon = (StoreConnection*)(P_GOD->_pStoreManager->getConnection("StCon_Shot001"));
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineProgram* pProgram = NEW FixedVelocitySplineProgram(_papIris[i], _pSplCon->refer(), 4000); //�ړ����x�Œ�
        _papIris[i]->setSplineProgram(pProgram);
        _papIris[i]->setStore_Shot(_pStoreCon->refer()); //�e�ݒ�
        _papIris[i]->inactivateImmediately();
        addSubLast(_papIris[i]);
    }
}

void FormationIris001::initialize() {
    //�ґ��쐬��onActive()�ōs�키���ƁB
    //ActorTableScene �� active �ɂ����^�C�~���O�͕ϓ����邽��
}

void FormationIris001::onActive() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->locate(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zleft * 0.8);
        _papIris[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papIris[i]->activateDelay(i*_interval_frames + 1);//_interval_frames�Ԋu��Active�ɂ���B
    }
}

FormationIris001::~FormationIris001() {
    _pSplCon->close();
    _pStoreCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
