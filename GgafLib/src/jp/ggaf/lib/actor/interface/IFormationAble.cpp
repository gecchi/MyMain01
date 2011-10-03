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
        throwGgafCriticalException("IFormationAble::informDestroyedFollower() _pFormation が NULLです。"<<
                                   "対応する FormationActor による addSubLast() 或いは callUp() により、IFormationAbleアクターが設定されていません。this="<<this);
    }
#endif
    _pFormation->_num_destory++;
    if (_pFormation->_num_sub == _pFormation->_num_destory) {
        _pFormation->_was_all_destroyed = true;
        GgafDxGeometricActor* pActor = dynamic_cast<GgafDxGeometricActor*>(this);
#ifdef MY_DEBUG
        if (pActor == NULL) {
            throwGgafCriticalException("IFormationAble::informDestroyedFollower() GgafDxGeometricActor*へクロスキャスト失敗。this="<<this<<" のクラスから GgafDxGeometricActor が見えません。thisのアクターが IFormationAble をpublic 継承しているか確認して下さい。_pFormation="<<_pFormation->getName());
        }
#endif
        _pFormation->onDestroyedFormation(pActor);
    }
}

IFormationAble::~IFormationAble() {
}
