#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia::FormationEunomia(const char* prm_name, const char* prm_spl_id) : FormationActor(prm_name, 20*60) {
    _class_name = "FormationEunomia";
    _num_formation_col = 7;   //�ґ���
    _num_formation_row = 1;  //�P��̕ґ���
    _interval_frames   = R_FormationEunomia001_LaunchInterval;  //�G�E�m�~�A�̊Ԋu(frame)
    _mv_velo           = 10; //���x
    _n = 0;

    //�G�E�m�~�A�ґ��쐬
    _pDepoCon_Eunomia = connectDepositoryManager("DpCon_EnemyEunomia4Formation", this);
    setActorDepository(_pDepoCon_Eunomia->use());


    //�X�v���C����`�t�@�C����ǂݍ���
    _papSplManufCon = NEW SplineManufactureConnection*[_num_formation_col];
    for (int i = 0; i < _num_formation_col; i++) {
        stringstream spl_id;
        spl_id << prm_spl_id << "_" << i;  //���၄"FormationEunomia001_0"
        _papSplManufCon[i] = connectSplineManufactureManager(spl_id.str().c_str());
    }

//    _papapEunomia = NEW EnemyEunomia**[_num_formation_col]; //n��xN�@�̕ґ���g��
//    for (int i = 0; i < _num_formation_col; i++) {
//        _papapEunomia[i] = NEW EnemyEunomia*[_num_formation_row];
//        for (int j = 0; j < _num_formation_row; j++) {
//            stringstream nm;
//            nm << "EUNOMIA_col" << i << "_row" << j;
//            _papapEunomia[i][j] = NEW EnemyEunomia(nm.str().c_str());
//            SplineSequence* pSplSeq = _papSplManufCon[i]->use()->
//                                            createSplineSequence(_papapEunomia[i][j]->_pKurokoA);
//            _papapEunomia[i][j]->config(this, pSplSeq, NULL, NULL);
//            _papapEunomia[i][j]->inactivateImmediately();
//            addSubLast(_papapEunomia[i][j]);
//        }
//    }
    _pDepoCon_shot = NULL;
}

void FormationEunomia::initialize() {
    _n = 0;
}


void FormationEunomia::processBehavior() {

    if (_n < _num_formation_row && getActivePartFrame() % _interval_frames == 0) {
        _num_formation_col = R_FormationEunomia001_Col;   //�ґ���
        _num_formation_row = R_FormationEunomia001_Num;  //�P��̕ґ���
        _interval_frames   = R_FormationEunomia001_LaunchInterval;   //�G�E�m�~�A�̊Ԋu(frame)
        _mv_velo           = R_FormationEunomia001_MvVelo; //���x
        for (int i = 0; i < _num_formation_col; i++) {
            EnemyEunomia* pEunomia = (EnemyEunomia*)callUp();
            if (pEunomia) {
                SplineSequence* pSplSeq = _papSplManufCon[i]->use()->
                                              createSplineSequence(pEunomia->_pKurokoA);
                pEunomia->config(this, pSplSeq, NULL, NULL);
                pEunomia->_pKurokoA->setMvVelo(_mv_velo);
    //            _papapEunomia[i][_n]->activate();
                processOnActiveEunomia(pEunomia, i); //�t�H�[���[�V�����ʎ����̏���
            }
        }
        _n++;
    }
}

FormationEunomia::~FormationEunomia() {
    _pDepoCon_Eunomia->close();

    for (int i = 0; i < 7; i++) {
        _papSplManufCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplManufCon);

    if (_pDepoCon_shot) {
        _pDepoCon_shot->close();
    }
//    for (int i = 0; i < _num_formation_col; i++) {
//        DELETEARR_IMPOSSIBLE_NULL(_papapEunomia[i]);
//    }
//    DELETEARR_IMPOSSIBLE_NULL(_papapEunomia);
}
