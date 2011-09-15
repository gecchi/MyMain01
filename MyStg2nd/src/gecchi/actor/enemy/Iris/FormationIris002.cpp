#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationIris002::FormationIris002(const char* prm_name) :
        FormationActor(prm_name, 30*60) { //30*60���end()����B�����J����������� Depository �̐ڑ����؂�邽�߁B
    _class_name = "FormationIris002";
    _num_Iris        = R_FormationIris002_Num;    //�ґ���
    _interval_frames = R_FormationIris002_LaunchInterval;   //�C���X�̊Ԋu(frame)
    _mv_velo         = R_FormationIris002_MvVelo; //���x
    //�X�v���C���ړ��̒�`
    _pSplLineCon = connectSplineLineManager("SpCon_002_02");
    _pDepoCon = connectDepositoryManager("DpCon_Shot002", NULL);
    //�C���X�ґ��쐬
    _papIris = NEW EnemyIris*[_num_Iris];
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i] = NEW EnemyIris("Iris01");
        //�X�v���C���ړ��v���O�����ݒ�
        SplineSequence* pProgram = NEW FixedVelocitySplineSequence(_papIris[i]->_pKurokoA, _pSplLineCon->use(), 10000); //�ړ����x�Œ�
        _papIris[i]->config(NULL, pProgram, _pDepoCon->use(), NULL);
        _papIris[i]->inactivateImmediately();
        addSubLast(_papIris[i]);
    }
}

void FormationIris002::initialize() {

}

void FormationIris002::onActive() {
    for (int i = 0; i < _num_Iris; i++) {
        _papIris[i]->locate(MyShip::_lim_behaind - 500000, 0, MyShip::_lim_zright * 0.8);
        _papIris[i]->_pKurokoA->setMvVelo(_mv_velo);
        _papIris[i]->activateDelay(i*_interval_frames + 1);//_interval_frames�Ԋu��Active�ɂ���B
    }
}

FormationIris002::~FormationIris002() {
    _pSplLineCon->close();
    _pDepoCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_papIris);
}
