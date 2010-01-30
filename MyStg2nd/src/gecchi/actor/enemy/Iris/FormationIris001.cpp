#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GgafDx9Spline3D FormationIris001::_sp;

FormationIris001::FormationIris001(const char* prm_name) : FormationActor(prm_name, 30*60) {
    _class_name = "FormationIris001";
    _num_Iris       = 7*_RANK_;    //�ґ���
    _frame_interval = 25/_RANK_;   //�C���X�̊Ԋu(frame)
    _mv_velo  = 8000*_RANK_; //���x
    //�X�v���C���ړ��̒�`
    if (FormationIris001::_sp._num_basepoint == 0) {
        //�������
        double p[][3] = { //           X  ,                       Y ,                         Z
           { MyShip::_lim_behaind - 500000 ,                    0.0 ,  MyShip::_lim_zleft * 0.8 },
           {      MyShip::_lim_front * 1.5 , MyShip::_lim_top * 0.2 ,                       0.0 },
           {      MyShip::_lim_front * 2.5 , MyShip::_lim_top * 0.5 , MyShip::_lim_zright * 0.3 },
           {      MyShip::_lim_front * 2.2 , MyShip::_lim_top * 1.0 ,                       0.0 },
           {      MyShip::_lim_front * 2.0 ,                    0.0 ,                       0.0 }
        };
        FormationIris001::_sp.init(p, 5, 0.2); //���x 0.2
    }

    //�C���X�ґ��쐬
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        _papIris[i]->_pProgram_IrisMove =
                NEW GgafDx9FixedVelocitySplineProgram(&FormationIris001::_sp, 4000); //�ړ����x�Œ�
        _papIris[i]->inactivateImmediately();
        addSubLast(_papIris[i]);
    }

    _pDispatcherCon = (DispatcherConnection*)God::_dispatcherManager.connect("DpCon_Shot001");
}

void FormationIris001::initialize() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->setGeometry(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zleft * 0.8);
        _papIris[i]->_pMover->setMvVelo(_mv_velo);
        _papIris[i]->setDispatcher_Shot(_pDispatcherCon->view()); //�e�ݒ�
        _papIris[i]->activateAfter(i*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
    }
}

FormationIris001::~FormationIris001() {
    _pDispatcherCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
