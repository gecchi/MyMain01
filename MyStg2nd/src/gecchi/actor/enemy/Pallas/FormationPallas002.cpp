#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas002::FormationPallas002(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas002";
    _num_Pallas      = R_FormationPallas002_Num;  //�ґ���
    _interval_frames = R_FormationPallas002_LaunchInterval;  //�p���X�̊Ԋu(frame)
    _mv_velo         = R_FormationPallas002_MvVelo; //���x
    //�p���X�ґ��쐬
    _pSplManufCon = connectSplineManufactureManager("Pallas02");
//    _pSplCon     = (Spline3DConnection*)(P_GOD->_pSpl3DManager->connect("SpCon_Pallas01")); //�X�v���C����`
    //_pDepoCon = connectDepositoryManager("StCon_Shot002", NULL);
    _pDepoCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineSequence* pProgram = _pSplManufCon->use()->createSplineSequence(_papPallas[i]->_pKurokoA); //�ړ����x�Œ�
        _papPallas[i]->config(pProgram, NULL, NULL);
        //_papPallas[i]->setDepository_Shot(_pDepoCon->use()); //�e�ݒ�
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}

void FormationPallas002::onActive() {
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i]->locate(MyShip::_lim_behaind *2 , P_MYSHIP->_Y+300000,  P_MYSHIP->_Z);
        _papPallas[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papPallas[i]->activateDelay(i*_interval_frames + 1);//_interval_frames�Ԋu��Active�ɂ���B
    }
}

FormationPallas002::~FormationPallas002() {
    _pSplManufCon->close();
    if (_pDepoCon) {
        _pDepoCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
