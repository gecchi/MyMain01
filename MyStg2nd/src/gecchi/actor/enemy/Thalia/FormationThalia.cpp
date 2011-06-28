#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationThalia::FormationThalia(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationThalia";
    _num_Thalia      = 7+_RANK_*4;         //�ґ��̃^���A�̐�
    _interval_frames = 2+(20-_RANK_*5);    //�e�^���A�̏o���Ԋu(frame)
    _mv_velo         = 14000+_RANK_*10000; //�e�^���A�̈ړ����x

    _pDpcon = (StoreConnection*)(P_GOD->_pStoreManager->getConnection("StCon_Shot004"));
    //�ґ��쐬
    _papThalia = NEW EnemyThalia*[_num_Thalia];
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i] = NEW EnemyThalia("Thalia01");
        //�X�v���C���ړ��v���O�����ݒ�
        _papThalia[i]->setSplineProgram(NULL);
        _papThalia[i]->setStore_Shot(_pDpcon->refer()); //�e�ݒ�
        _papThalia[i]->inactivateImmediately();
        addSubLast(_papThalia[i]);
    }
}

void FormationThalia::initialize() {

}

void FormationThalia::onActive() {
    for (int i = 0; i < _num_Thalia; i++) {
        _papThalia[i]->locate(MyShip::_lim_behaind, -2000000 + (i * 400000), 0);
        _papThalia[i]->_pKurokoA->setRzRyMvAng(0,0);
        _papThalia[i]->_pKurokoA->setMvVelo(80000);
        _papThalia[i]->activateDelay(i*_interval_frames + 1);//_interval_frames�Ԋu��Active�ɂ���B
    }
}

FormationThalia::~FormationThalia() {
    _pDpcon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papThalia);
}
