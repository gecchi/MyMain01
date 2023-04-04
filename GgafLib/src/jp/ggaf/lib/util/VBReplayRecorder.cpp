#include "jp/ggaf/lib/util/VBReplayRecorder.h"



using namespace GgafLib;

VBReplayRecorder::VBReplayRecorder() : GgafCore::Object() {
    _pFirstVBNote = nullptr;
    _pRecNote = nullptr;
    _pRecNote_read_prev = nullptr;
    _write_realtime = false;
    _frame_of_the_same_vb_sta_reading = 0;
}

bool VBReplayRecorder::setRealtimeOutputFile(const char* prm_filename) {
    _write_realtime = true;
    _ofs_realtime.open(prm_filename);
    if (_ofs_realtime.fail()) {
        _TRACE_(FUNC_NAME<<" "<<prm_filename<<" が開けません");
        return false;
    } else {
        _ofs_realtime << std::unitbuf; //逐次バッファフラッシュ
        return true;
    }
}

void VBReplayRecorder::first() {
    _pRecNote = _pFirstVBNote;
    _frame_of_the_same_vb_sta_reading = 0;
}

vb_sta VBReplayRecorder::read() {
    if (_pRecNote) {
        vb_sta r = _pRecNote->_p1_state;
        _frame_of_the_same_vb_sta_reading++;
        if (_pRecNote->_frame_of_keeping == _frame_of_the_same_vb_sta_reading) {
            _frame_of_the_same_vb_sta_reading = 0;
            _pRecNote_read_prev = _pRecNote; //保存
            _pRecNote = _pRecNote->_pNext;
        }
        return r;
    } else {
        return 0;
    }
}

void VBReplayRecorder::write(vb_sta prm_state) {
    if (_write_realtime) {
        _ofs_realtime << prm_state << " 1" << std::endl;
    }

    if (_pFirstVBNote == nullptr) {
        //新規
        _pFirstVBNote = NEW VBRecordNote(prm_state, 1);
        _pRecNote = _pFirstVBNote;
        _pRecNote_read_prev = nullptr;
        return;
    } else {
        if (_pRecNote_read_prev) {
            //read → 0 → write 続きから追記(要検証)
            _pRecNote = _pRecNote_read_prev;
            _pRecNote_read_prev = nullptr;
        }

        if (_pRecNote->_p1_state != prm_state) {
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
        ofs << p->_p1_state << " " << p->_frame_of_keeping << std::endl;
        p = p ->_pNext;
    }
    if (_write_realtime) {
        _ofs_realtime.flush();
    }
}

bool VBReplayRecorder::importFile(const char* prm_filename) {
    std::ifstream ifs(prm_filename);
    if (ifs.fail()) {
        _TRACE_(FUNC_NAME<<" "<<prm_filename<<" が開けません");
        return false;
    }
    VBRecordNote* p = NEW VBRecordNote();
    _pFirstVBNote = p;
    _pRecNote = p;
    ifs >> (p->_p1_state) >> (p->_frame_of_keeping);

    vb_sta in_state;
    frame in_frame_of_keeping;
    while (!ifs.eof()) {
        ifs >> in_state >> in_frame_of_keeping;
        if (ifs.fail()) {
            break;
        }
        p->_pNext = NEW VBRecordNote();
        p = p->_pNext;
        p->_p1_state = in_state;
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

