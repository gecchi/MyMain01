#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia001::FormationEunomia001(const char* prm_name) : GgafDx9FormationActor(prm_name, 30*60) {
    _class_name = "FormationEunomia001";

    _num_formation_col = 4+_RANK_*2;   //�ґ���
    _num_formation_row = 10+_RANK_*10; //�P��̕ґ���
    _frame_interval    = 10-_RANK_*5;  //�G�E�m�~�A�̊Ԋu(frame)
    _mv_velo           = 10000+_RANK_*10000; //���x
    _n = 0;
    //�G�E�m�~�A�ґ��쐬
    //�X�v���C����`�t�@�C����ǂݍ���
    _papSplineCon = NEW SplineConnection*[_num_formation_col];
    for (int i = 0; i < _num_formation_col; i++) {
        stringstream spl_id;
        spl_id << "FormationEunomia001_" << i;
        _papSplineCon[i] = (SplineConnection*)(P_GOD->_pSplineManager->getConnection(spl_id.str().c_str()));
    }

    _papapEunomia = NEW EnemyEunomia**[_num_formation_col]; //n��xN�@�̕ґ���g��
    for (int i = 0; i < _num_formation_col; i++) {
        _papapEunomia[i] = NEW EnemyEunomia*[_num_formation_row];
        for (int j = 0; j < _num_formation_row; j++) {
            _papapEunomia[i][j] = NEW EnemyEunomia("EUNOMIA");
            _papapEunomia[i][j]->config(_papSplineCon[i]->refer()->makeSplineProgram(_papapEunomia[i][j]), NULL, NULL);
            _papapEunomia[i][j]->inactivateImmediately();
            addSubLast(_papapEunomia[i][j]);
        }
    }


    _pDispatcherCon = NULL;
}
void FormationEunomia001::initialize() {
    _n = 0;
}

void FormationEunomia001::onActive() {
}
void FormationEunomia001::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //�ґ����Ŏ��̎���
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDispatcher_EffectTurbo002->employForce();
    if (pTurbo002) {
        pTurbo002->setCoordinateBy(prm_pActorLast);
        pTurbo002->activate();
    }
}

void FormationEunomia001::processBehavior() {
    if (_n < _num_formation_row && getActivePartFrame() % _frame_interval == 0) {
        for (int i = 0; i < _num_formation_col; i++) {
            processOnActiveEunomia(_papapEunomia[i][_n], i); //�ʎ����̏���
            _papapEunomia[i][_n]->activate();
        }
        _n++;
    }
}

FormationEunomia001::~FormationEunomia001() {
    for (int i = 0; i < _num_formation_col; i++) {
        _papSplineCon[i]->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_papSplineCon);

    if (_pDispatcherCon) {
        _pDispatcherCon->close();
    }
    for (int i = 0; i < _num_formation_col; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapEunomia[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapEunomia);
}
