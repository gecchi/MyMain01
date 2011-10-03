#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

IFormationAble::IFormationAble() {
    _pFormation = NULL;
}

void IFormationAble::informDestroyedFollower() {
#ifdef MY_DEBUG
    if (_pFormation) {
        //OK
    } else {
        throwGgafCriticalException("IFormationAble::informDestroyedFollower() _pFormation �� NULL�ł��B"<<
                                   "�Ή����� FormationActor �ɂ�� addSubLast() ������ callUp() �ɂ��AIFormationAble�A�N�^�[���ݒ肳��Ă��܂���Bthis="<<this);
    }
#endif
    _pFormation->_num_destory++;
    if (_pFormation->_num_sub == _pFormation->_num_destory) {
        _pFormation->_was_all_destroyed = true;
        GgafDxGeometricActor* pActor = dynamic_cast<GgafDxGeometricActor*>(this);
#ifdef MY_DEBUG
        if (pActor == NULL) {
            throwGgafCriticalException("IFormationAble::informDestroyedFollower() GgafDxGeometricActor*�փN���X�L���X�g���s�Bthis="<<this<<" �̃N���X���� GgafDxGeometricActor �������܂���Bthis�̃A�N�^�[�� IFormationAble ��public �p�����Ă��邩�m�F���ĉ������B_pFormation="<<_pFormation->getName());
        }
#endif
        _pFormation->onDestroyedFormation(pActor);
    }
}

IFormationAble::~IFormationAble() {
}
