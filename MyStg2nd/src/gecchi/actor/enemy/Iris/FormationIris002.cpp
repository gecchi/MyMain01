#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GgafDx9Spline3D FormationIris002::_sp;

FormationIris002::FormationIris002(const char* prm_name) :
        FormationActor(prm_name, 30*60) { //30*60���adios()����B�����J����������� Dispatcher �̐ڑ����؂�邽�߁B
    _class_name = "FormationIris002";
    _num_Iris       = 10*_RANK_;    //�ґ���
    _frame_interval = 20*_RANK_;   //�C���X�̊Ԋu(frame)
    _move_velocity  = 16000*_RANK_; //���x
    //�X�v���C���ړ��̒�`
    if (FormationIris002::_sp._num_basepoint == 0) {
        //�������
        double p[][3] = { //           X  ,                          Y ,                         Z
           { MyShip::_lim_behaind - 500000 ,                       0.0 , MyShip::_lim_zright * 0.8 },
           {      MyShip::_lim_front * 0.5 , MyShip::_lim_bottom * 0.2 ,                       0.0 },
           {      MyShip::_lim_front * 1.5 , MyShip::_lim_bottom * 0.5 ,  MyShip::_lim_zleft * 0.3 },
           {      MyShip::_lim_front * 1.2 , MyShip::_lim_bottom * 1.0 ,                       0.0 },
           {      MyShip::_lim_front * 1.0 ,                       0.0 ,                       0.0 }
        };
        FormationIris002::_sp.init(p, 5, 0.2); //���x 0.2
    }

    //�C���X�ґ��쐬
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        _papIris[i]->_pProgram_IrisMove =
                NEW GgafDx9FixedVelocitySplineProgram(&FormationIris002::_sp, 4000); //�ړ����x�Œ�
        _papIris[i]->inactivateImmediately();
        addSubGroup(KIND_ENEMY_BODY, _papIris[i]);
    }

    _pDispatcherCon = (DispatcherConnection*)God::_dispatcherManager.connect("DpCon_Shot002");

}

void FormationIris002::initialize() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->setGeometry(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zright * 0.8);
        _papIris[i]->_pMover->setMoveVelocity(_move_velocity);
        _papIris[i]->setDispatcher_Shot(_pDispatcherCon->view());
        _papIris[i]->activateAfter(i*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
    }
}

FormationIris002::~FormationIris002() {
    _pDispatcherCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
