#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

VBReplayRecorder::VBReplayRecorder() : GgafObject() {
    _pFirstVBNote = NULL;
    _pRecNote = NULL;
    _pRecNote_RreadPrev = NULL;
}

void VBReplayRecorder::first() {
    _pRecNote = _pFirstVBNote;
    _frame_of_the_same_vbsta_reading = 0;
}

vbsta VBReplayRecorder::read() {
    if (_pRecNote) {
        vbsta r = _pRecNote->_state;
        _frame_of_the_same_vbsta_reading++;
        if (_pRecNote->_frame_of_keeping == _frame_of_the_same_vbsta_reading) {
            _frame_of_the_same_vbsta_reading = 0;
            _pRecNote_RreadPrev = _pRecNote; //保存
            _pRecNote = _pRecNote->_pNext;
        }
        return r;
    } else {
        return 0;
    }
}

void VBReplayRecorder::write(vbsta prm_state) {
    if (_pFirstVBNote == NULL) {
        //新規
        _pFirstVBNote = NEW VBRecordNote(prm_state, 1);
        _pRecNote = _pFirstVBNote;
        _pRecNote_RreadPrev = NULL;
        return;
    } else {
        if (_pRecNote_RreadPrev) {
            //read → 0 → write 続きから追記(要検証)
            _pRecNote = _pRecNote_RreadPrev;
            _pRecNote_RreadPrev = NULL;
        }

        if (_pRecNote->_state != prm_state) {
            _pRecNote->_pNext = NEW VBRecordNote(prm_state, 1);
            _pRecNote = _pRecNote->_pNext;
            return;
        } else {
            _pRecNote->_frame_of_keeping++;
        }
    }
}
void VBReplayRecorder::outputFile(const char* prm_filename) {
    ofstream ofs(prm_filename);
    VBRecordNote* p = _pFirstVBNote;
    while (p != NULL) {
        ofs << p->_state << " " << p->_frame_of_keeping << endl;
        p = p ->_pNext;
    }
}

bool VBReplayRecorder::importFile(const char* prm_filename) {
    ifstream ifs(prm_filename);
    if (ifs.fail()) {
        _TRACE_("VBReplayRecorder::importFile "<<prm_filename<<" が開けません");
        return false;
    }
    VBRecordNote* p = NEW VBRecordNote();
    _pFirstVBNote = p;
    _pRecNote = p;
    ifs >> (p->_state) >> (p->_frame_of_keeping);

    vbsta in_state;
    frame in_frame_of_keeping;
    while (!ifs.eof()) {
        ifs >> in_state >> in_frame_of_keeping;
        if (ifs.fail()) {
            break;
        }
        p->_pNext = NEW VBRecordNote();
        p = p->_pNext;
        p->_state = in_state;
        p->_frame_of_keeping = in_frame_of_keeping;
    }
    this->first();
    return true;
}


VBReplayRecorder::~VBReplayRecorder() {
    VBRecordNote* p = _pFirstVBNote;
    VBRecordNote* w;
    while (p) {
        w = p ->_pNext;
        DELETE_IMPOSSIBLE_NULL(p);
        p = w;
    }

}
