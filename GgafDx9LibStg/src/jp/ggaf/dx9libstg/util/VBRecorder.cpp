#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

VBRecorder::VBRecorder(VirtualButton* prm_vb) : GgafObject() {
    _vb = prm_vb;
    _pFirstVBNote = NULL;
    _p = NULL;
}

void VBRecorder::write() {

    if (_vb->_pVBMap_Active->_state != _vb->_pVBMap_Active->_prev->_state) { //‰‰ñ‚ð‚Ì‚¼‚­‚É‚ÍH
        VBStateNote* pVBNote = NEW VBStateNote(_vb->_pVBMap_Active->_prev->_state, _nframe);
        if (_pFirstVBNote) {
            _p->_pNext = pVBNote;
            _p = pVBNote;
        } else {
            _pFirstVBNote = pVBNote;
            _p = pVBNote;
        }
        _nframe = 0;
    } else {
        _nframe++;
    }
}

VBRecorder::~VBRecorder() {
}
