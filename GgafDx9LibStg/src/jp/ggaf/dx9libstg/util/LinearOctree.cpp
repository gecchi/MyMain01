#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

LinearOctree::LinearOctree(int prm_level, int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) : GgafObject() {
    _level = prm_level;
    //�ׂ���쐬
    _paPow = NEW int[_level+1];
    _paPow[0] = 1;
    for(int i = 1; i < _level + 1; i++) {
        _paPow[i] = _paPow[i-1]*8;
    }

    //���`�W���ؔz��쐬
    _num_space = (_paPow[_level+1] -1) / 7; //��Ԑ�
    _papSpace = NEW Space*[_num_space];
    for (int i = 0; i < _num_space; i++) {
        _papSpace[i] = NEW Space();
    }

    _X1 = X1;
    _Y1 = Y1;
    _Z1 = Z1;
    _X2 = X2;
    _Y2 = Y2;
    _Z2 = Z2;
    _min_dX = (_X2-_X1) / ((float)(1<<Level));
    _min_dY = (_Y2-_Y1) / ((float)(1<<Level));
    _min_dZ = (_Z2-_Z1) / ((float)(1<<Level));



}

void LinearOctree::regist(GgafDx9Core::GgafDx9GeometricActor* prm_pActer, StgChecker* prm_pStgChecker) {
    // �I�u�W�F�N�g�̋��E�͈͂���o�^���[�g���ԍ����Z�o
    DWORD Elem = GetMortonNumber( Min, Max );
}

LinearOctree::~LinearOctree() {
}
