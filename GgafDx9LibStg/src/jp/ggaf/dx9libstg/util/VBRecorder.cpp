#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

VBRecorder::VBRecorder() : GgafObject() {
}

void VBRecorder::updete() {
    /*
    if (VirtualButton::_pVBMap_Active->_state != VirtualButton::_pVBMap_Active->_prev->_state) {
        VBStateNote* pNote = NEW VBStateNote(VirtualButton::_pVBMap_Active->_prev->_state, _frame_Immovable);
        _frame_Immovable = 0;

    } else {
        _frame_Immovable++;
    }
*/
}

VBRecorder::~VBRecorder() {
}
