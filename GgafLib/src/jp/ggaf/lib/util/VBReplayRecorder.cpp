#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

VBReplayRecorder::VBReplayRecorder() : GgafObject() {
    _pFirstVBNote = nullptr;
    _pRecNote = nullptr;
    _pRecNote_RreadPrev = nullptr;
    _write_realtime = false;
    _frame_of_the_same_vbsta_reading = 0;
}

bool VBReplayRecorder::setRealtimeOutputFile(const char* prm_filename) {
    _write_realtime = true;
    _ofs_realtime.open(prm_filename);
    if (_ofs_realtime.fail()) {
        _TRACE_("VBReplayRecorder::setRealtimeOutputFile "<<prm_filename<<" が開けません");
        return false;
    } else {
        _ofs_realtime << std::unitbuf; //逐次バッファフラッシュ
        return true;
    }
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
    if (_write_realtime) {
        _ofs_realtime << prm_state << " 1" << std::endl;
    }

    if (_pFirstVBNote == nullptr) {
        //新規
        _pFirstVBNote = NEW VBRecordNote(prm_state, 1);
        _pRecNote = _pFirstVBNote;
        _pRecNote_RreadPrev = nullptr;
        return;
    } else {
        if (_pRecNote_RreadPrev) {
            //read → 0 → write 続きから追記(要検証)
            _pRecNote = _pRecNote_RreadPrev;
            _pRecNote_RreadPrev = nullptr;
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
    std::ofstream ofs(prm_filename);
    VBRecordNote* p = _pFirstVBNote;
    while (p != nullptr) {
        ofs << p->_state << " " << p->_frame_of_keeping << std::endl;
        p = p ->_pNext;
    }
    if (_write_realtime) {
        _ofs_realtime.flush();
    }
}

bool VBReplayRecorder::importFile(const char* prm_filename) {
    std::ifstream ifs(prm_filename);
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
        GGAF_DELETE(p);
        p = w;
    }

    if (_write_realtime) {
        _ofs_realtime.close();
    }

}
