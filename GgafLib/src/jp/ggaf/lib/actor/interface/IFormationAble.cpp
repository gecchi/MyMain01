#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

IFormationAble::IFormationAble() {
    _pFormation = NULL;
}

void IFormationAble::informDestroyedFollower() {
    _pFormation->_num_destory++;
	
	_TRACE_("_pFormation="<<_pFormation->getName()<<": _pFormation->_num_sub="<<_pFormation->_num_sub<<" _pFormation->_num_destory="<<_pFormation->_num_destory);

    if (_pFormation->_num_sub == _pFormation->_num_destory) {
        _pFormation->_was_all_destroyed = true;
		_TRACE_("_pFormation="<<_pFormation->getName()<<": onDestroyedFormation!!");
        _pFormation->onDestroyedFormation(((GgafDxGeometricActor*)this));
    }
}

IFormationAble::~IFormationAble() {
}
