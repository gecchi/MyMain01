#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationPallas002::FormationPallas002(const char* prm_name) : FormationActor(prm_name, 30*60) {
    _class_name = "FormationPallas002";
    _num_Pallas       = 10*_RANK_;    //�ґ���
    _frame_interval = 25/_RANK_+5;   //�p���X�̊Ԋu(frame)
    _mv_velo  = 8000*_RANK_; //���x
    //�p���X�ґ��쐬
    _pSplineCon     = (Spline3DConnection*)(pGOD->_pSpline3DManager->connect("SpCon_Pallas01")); //�X�v���C����`
    //_pDispatcherCon = (DispatcherConnection*)(pGOD->_pDispatcherManager->connect("DpCon_Shot002"));
	_pDispatcherCon = NULL;
    _papPallas = NEW EnemyPallas*[_num_Pallas];
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i] = NEW EnemyPallas("Pallas01");
        //�X�v���C���ړ��v���O�����ݒ�
        GgafDx9SplineProgram* pProgram = NEW GgafDx9FixedVelocitySplineProgram(_papPallas[i], _pSplineCon->view(), 8000); //�ړ����x�Œ�
        _papPallas[i]->setSplineProgram(pProgram);
        //_papPallas[i]->setDispatcher_Shot(_pDispatcherCon->view()); //�e�ݒ�
        _papPallas[i]->inactivateImmediately();
        addSubLast(_papPallas[i]);
    }
}

void FormationPallas002::initialize() {
    for (int i = 0; i < _num_Pallas; i++) {
        _papPallas[i]->setGeometry(MyShip::_lim_behaind *2 , pMYSHIP->_Y+300000,  pMYSHIP->_Z);
        _papPallas[i]->_pMover->setMvVelo(_mv_velo);
        _papPallas[i]->activateAfter(i*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
    }
}

FormationPallas002::~FormationPallas002() {
    _pSplineCon->close();
	if (_pDispatcherCon) {
		_pDispatcherCon->close();
	}
    DELETEARR_IMPOSSIBLE_NULL(_papPallas);
}
