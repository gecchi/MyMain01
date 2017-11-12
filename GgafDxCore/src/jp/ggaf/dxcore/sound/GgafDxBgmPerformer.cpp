#include "jp/ggaf/dxcore/sound/GgafDxBgmPerformer.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

//int GgafDxBgmPerformer::_active_bgm_bpm = 120;

GgafDxBgmPerformer::GgafDxBgmPerformer() : GgafObject() {
    _bgm_num = 0;
    _pa_volume = nullptr;
    _pa_pan = nullptr;
    _papBgmConnection = nullptr;
}

void GgafDxBgmPerformer::ready(int prm_bgm_no, const char* prm_bgm_name) {
    if (prm_bgm_no >= _bgm_num) {
        if (_bgm_num == 0) {
            //初回
            _bgm_num = prm_bgm_no + 1;
            _papBgmConnection = NEW GgafDxBgmConnection*[_bgm_num];
            _pa_volume = NEW double[_bgm_num];
            _pa_pan    = NEW float[_bgm_num];
            for (int i = 0; i < _bgm_num; i++) {
                _papBgmConnection[i] = nullptr;
                _pa_volume[i] = GGAF_MAX_VOLUME;
                _pa_pan[i] = 0;
            }
        } else {
            //拡張する。
            int old_bgm_num = _bgm_num;
            _bgm_num = prm_bgm_no + 1;
            GgafDxBgmConnection** new_papBgmConnection = NEW GgafDxBgmConnection*[_bgm_num];
            double* new_pa_volume = NEW double[_bgm_num];
            float*  new_pa_pan    = NEW float[_bgm_num];
            for (int i = 0; i < old_bgm_num; i++) { //旧をコピー
                new_papBgmConnection[i] = _papBgmConnection[i];
                new_pa_volume[i]  = _pa_volume[i];
                new_pa_pan[i]     = _pa_pan[i];
            }
            for (int i = old_bgm_num; i < _bgm_num; i++) {
                new_papBgmConnection[i] = nullptr;
                new_pa_volume[i]  = GGAF_MAX_VOLUME;
                new_pa_pan[i]     = 0;
            }
            GGAF_DELETEARR_NULLABLE(_papBgmConnection);
            GGAF_DELETEARR_NULLABLE(_pa_volume);
            GGAF_DELETEARR_NULLABLE(_pa_pan);
            _papBgmConnection = new_papBgmConnection;
            _pa_volume  = new_pa_volume;
            _pa_pan = new_pa_pan;
        }
    }

    if (_papBgmConnection[prm_bgm_no]) {
        _TRACE_("【警告】GgafDxBgmPerformer::set() IDが使用済みです、上書きしますが意図してますか？？。prm_bgm_no="<<prm_bgm_no<<" prm_bgm_name="<<prm_bgm_name);
        _papBgmConnection[prm_bgm_no]->close();
        _pa_volume[prm_bgm_no] = GGAF_MAX_VOLUME;
        _pa_pan[prm_bgm_no] = 0;
    }
    _papBgmConnection[prm_bgm_no] = connectToBgmManager(prm_bgm_name);
    GgafDxBgm* pBgm = _papBgmConnection[prm_bgm_no]->peek();
    pBgm->stop();
    pBgm->setVolume(_pa_volume[prm_bgm_no]);
    pBgm->setPan(_pa_pan[prm_bgm_no]);
}

void GgafDxBgmPerformer::play(int prm_bgm_no, bool prm_is_loop) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no<<"");
    }
    if (_papBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    GgafDxBgm* pBgm = getBgm(prm_bgm_no);
    pBgm->setVolume(_pa_volume[prm_bgm_no]);
    pBgm->setPan(_pa_pan[prm_bgm_no]);
    pBgm->play(prm_is_loop);
//    GgafDxBgmPerformer::_active_bgm_bpm = _papBgmConnection[prm_bgm_no]->peek()->_bpm; //最新のBGMのBPMリズム
}

void GgafDxBgmPerformer::stop(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no);
    }
    if (_papBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->stop();
}

void GgafDxBgmPerformer::pause(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no);
    }
    if (_papBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->pause();
}

void GgafDxBgmPerformer::pause() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        pause(bgm_no);
    }
}

void GgafDxBgmPerformer::unpause(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no);
    }
    if (_papBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->unpause();
}

void GgafDxBgmPerformer::unpause() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        unpause(bgm_no);
    }
}

void GgafDxBgmPerformer::stop() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        stop(bgm_no);
    }
}

void GgafDxBgmPerformer::setVolume(int prm_bgm_no, double prm_volume) {
    _pa_volume[prm_bgm_no] = prm_volume;
    getBgm(prm_bgm_no)->setVolume((int)(_pa_volume[prm_bgm_no]));
}

void GgafDxBgmPerformer::setPan(int prm_bgm_no, float prm_pan) {
    _pa_pan[prm_bgm_no] = prm_pan;
    getBgm(prm_bgm_no)->setPan(_pa_pan[prm_bgm_no]);
}

GgafDxBgm* GgafDxBgmPerformer::getBgm(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no);
    }
#endif
    return _papBgmConnection[prm_bgm_no]->peek();
}
GgafDxBgmPerformer::~GgafDxBgmPerformer() {
    if (_papBgmConnection) {
        for (int i = 0; i < _bgm_num; i++) {
            if (_papBgmConnection[i]) {
                _papBgmConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR_NULLABLE(_papBgmConnection);
    GGAF_DELETEARR_NULLABLE(_pa_volume);
    GGAF_DELETEARR_NULLABLE(_pa_pan);
}
