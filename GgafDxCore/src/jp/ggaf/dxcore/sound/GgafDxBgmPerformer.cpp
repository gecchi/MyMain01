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
}

void GgafDxBgmPerformer::ready(int prm_bgm_no, const char* prm_bgm_name) {
    int bgm_num = _vecBgmConnection.size();
    if (prm_bgm_no >= bgm_num) {
        for (int i = bgm_num; i <= prm_bgm_no; i++) {
            _vecBgmConnection.push_back(nullptr);
            _vec_volume.push_back(GGAF_MAX_VOLUME);
            _vec_pan.push_back(0);
        }
        _bgm_num = _vecBgmConnection.size();
    }

    if (_vecBgmConnection[prm_bgm_no]) {
        _TRACE_("【警告】GgafDxBgmPerformer::ready() IDが使用済みです、上書きしますが意図してますか？？。prm_bgm_no="<<prm_bgm_no<<" prm_bgm_name="<<prm_bgm_name);
        _vecBgmConnection[prm_bgm_no]->close();
        _vec_volume[prm_bgm_no] = GGAF_MAX_VOLUME;
        _vec_pan[prm_bgm_no] = 0;
    }
    _vecBgmConnection[prm_bgm_no] = connectToBgmManager(prm_bgm_name);
    GgafDxBgm* pBgm = _vecBgmConnection[prm_bgm_no]->peek();
    pBgm->stop();
    pBgm->setVolume(_vec_volume[prm_bgm_no]);
    pBgm->setPan(_vec_pan[prm_bgm_no]);
}

void GgafDxBgmPerformer::play(int prm_bgm_no, bool prm_is_loop) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no<<"");
    }
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    GgafDxBgm* pBgm = getBgm(prm_bgm_no);
    pBgm->setVolume(_vec_volume[prm_bgm_no]);
    pBgm->setPan(_vec_pan[prm_bgm_no]);
    pBgm->play(prm_is_loop);
//    GgafDxBgmPerformer::_active_bgm_bpm = _vecBgmConnection[prm_bgm_no]->peek()->_bpm; //最新のBGMのBPMリズム
}

void GgafDxBgmPerformer::stop(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no);
    }
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
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
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->pause();
    _TRACE_("GgafDxBgmPerformer::pause("<<prm_bgm_no<<"):"<<_vecBgmConnection[prm_bgm_no]->getIdStr()<<" をpause()しました。");
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
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("曲がセットされてません。prm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->unpause();
    _TRACE_("GgafDxBgmPerformer::unpause("<<prm_bgm_no<<"):"<<_vecBgmConnection[prm_bgm_no]->getIdStr()<<" unpause()しました。");
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

bool GgafDxBgmPerformer::isPlaying(int prm_bgm_no) {
    return getBgm(prm_bgm_no)->isPlaying();
}

bool GgafDxBgmPerformer::isPause(int prm_bgm_no) {
    return getBgm(prm_bgm_no)->isPause();
}
bool GgafDxBgmPerformer::isStopping(int prm_bgm_no) {
    return getBgm(prm_bgm_no)->isStopping();
}
void GgafDxBgmPerformer::setVolume(int prm_bgm_no, double prm_volume) {
    _vec_volume[prm_bgm_no] = prm_volume;
    getBgm(prm_bgm_no)->setVolume((int)(_vec_volume[prm_bgm_no]));
}

void GgafDxBgmPerformer::setPan(int prm_bgm_no, float prm_pan) {
    _vec_pan[prm_bgm_no] = prm_pan;
    getBgm(prm_bgm_no)->setPan(_vec_pan[prm_bgm_no]);
}

GgafDxBgm* GgafDxBgmPerformer::getBgm(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_bgm_num-1)<<"でお願いします。prm_bgm_no="<<prm_bgm_no);
    }
#endif
    return _vecBgmConnection[prm_bgm_no]->peek();
}
GgafDxBgmPerformer::~GgafDxBgmPerformer() {
    for (int i = 0; i < _bgm_num; i++) {
        if (_vecBgmConnection[i]) {
            _vecBgmConnection[i]->close();
        }
    }
}
