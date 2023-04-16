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

void VBReplayRecorder::readNextFrameStatus(vb_sta* prm_pa_vb_sta) {
    if (_pRecNote) {
        for (int p = 0; p < MAX_JOY_STICK_NUM; p++) {
            prm_pa_vb_sta[p] = _pRecNote->_vb_state[p];
        }
        _frame_of_the_same_vb_sta_reading++;
        if (_pRecNote->_frame_of_keeping == _frame_of_the_same_vb_sta_reading) {
            _frame_of_the_same_vb_sta_reading = 0;
            _pRecNote_read_prev = _pRecNote; //保存
            _pRecNote = _pRecNote->_pNext;
        }
    }
}

void VBReplayRecorder::write(vb_sta* prm_pa_vb_sta) {
    if (_write_realtime) {
        _ofs_realtime << prm_pa_vb_sta[0] << " " << prm_pa_vb_sta[1] << " 1" << std::endl;
    }

    if (_pFirstVBNote == nullptr) {
        //新規
        _pFirstVBNote = NEW VBRecordNote(prm_pa_vb_sta, 1);
        _pRecNote = _pFirstVBNote;
        _pRecNote_read_prev = nullptr;
        return;
    } else {
        if (_pRecNote_read_prev) {
            //read → 0 → write 続きから追記(要検証)
            _pRecNote = _pRecNote_read_prev;
            _pRecNote_read_prev = nullptr;
        }

        if (_pRecNote->_vb_state[0] != prm_pa_vb_sta[0] || _pRecNote->_vb_state[1] != prm_pa_vb_sta[1]) {
            _pRecNote->_pNext = NEW VBRecordNote(prm_pa_vb_sta, 1);
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
        ofs << p->_vb_state[0] << " " << p->_vb_state[1] << " " << p->_frame_of_keeping << std::endl;
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
    ifs >> (p->_vb_state[0]) >> (p->_vb_state[1]) >> (p->_frame_of_keeping);

    vb_sta in_state[MAX_JOY_STICK_NUM];
    frame in_frame_of_keeping;
    while (!ifs.eof()) {
        ifs >> in_state[0] >> in_state[1] >> in_frame_of_keeping;
        if (ifs.fail()) {
            break;
        }
        p->_pNext = NEW VBRecordNote();
        p = p->_pNext;
        for (int n = 0; n < MAX_JOY_STICK_NUM; n++) {
            p->_vb_state[n] = in_state[n];
        }
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

