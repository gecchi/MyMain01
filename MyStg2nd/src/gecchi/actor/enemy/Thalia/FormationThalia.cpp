#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationThalia::FormationThalia(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationThalia";
    _num_Thalia     = 8+_RANK_*8;    //�ґ���
    _frame_interval = 20-_RANK_*5;  //�^���A�̊Ԋu(frame)
    _mv_velo        = 10000+_RANK_*10000; //���x
    //�ґ��쐬
    _papThalia = NEW EnemyThalia*[_num_Thalia];
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i] = NEW EnemyThalia("Thalia01");
        //�X�v���C���ړ��v���O�����ݒ�
        _papThalia[i]->setSplineProgram(NULL);
        _papThalia[i]->setDispatcher_Shot(NULL); //�e�ݒ�
        _papThalia[i]->inactivateImmediately();
        addSubLast(_papThalia[i]);
    }
}

void FormationThalia::initialize() {

}

void FormationThalia::onActive() {
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i]->setGeometry(MyShip::_lim_behaind, 300000, -2000000 + (i * 500000));
        _papThalia[i]->_pMover->setRzRyMvAng(0,0);
        _papThalia[i]->_pMover->setMvVelo(80000);
        _papThalia[i]->activateDelay(i*_frame_interval + 1);//_frame_interval�Ԋu��Active�ɂ���B
    }
}

FormationThalia::~FormationThalia() {
    DELETEARR_IMPOSSIBLE_NULL(_papThalia);
}
