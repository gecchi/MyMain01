#include "jp/ggaf/dxcore/sound/GgafDxBgmConductor.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

//int GgafDxBgmConductor::_active_bgm_bpm = 120;

GgafDxBgmConductor::GgafDxBgmConductor() : GgafObject() {
    _bgm_num = 0;
}

void GgafDxBgmConductor::ready(int prm_bgm_no, const char* prm_bgm_name) {
    int bgm_num = _vecBgmConnection.size();
    if (prm_bgm_no >= bgm_num) {
        for (int i = bgm_num; i <= prm_bgm_no; i++) {
            _vecBgmConnection.push_back(nullptr);
            _vec_volume.push_back(GGAF_MAX_VOLUME);
            _vec_pan.push_back(0);
            _vec_is_fade.push_back(false);
            _vec_is_fadeafter_stop.push_back(true);
            _vec_target_volume.push_back(GGAF_MAX_VOLUME);
            _vec_inc_volume.push_back(0);
        }
        _bgm_num = _vecBgmConnection.size();
    }

    if (_vecBgmConnection[prm_bgm_no]) {
        _TRACE_("�y�x���zGgafDxBgmConductor::ready() ID���g�p�ς݂ł��A�㏑�����܂����Ӑ}���Ă܂����H�H�Bprm_bgm_no="<<prm_bgm_no<<" prm_bgm_name="<<prm_bgm_name);
        _vecBgmConnection[prm_bgm_no]->close();
        _vec_volume[prm_bgm_no] = GGAF_MAX_VOLUME;
        _vec_pan[prm_bgm_no] = 0;
        _vec_is_fade[prm_bgm_no] = false;
        _vec_is_fadeafter_stop[prm_bgm_no] = true;
        _vec_target_volume[prm_bgm_no] = GGAF_MAX_VOLUME;
        _vec_inc_volume[prm_bgm_no] = 0;
    }

    std::string idstr =  XTOS(getId()) + "/" + prm_bgm_name;
    _vecBgmConnection[prm_bgm_no] = connectToBgmManager(idstr.c_str());
    GgafDxBgm* pBgm = _vecBgmConnection[prm_bgm_no]->peek();
    pBgm->stop();
    pBgm->setVolume(_vec_volume[prm_bgm_no]);
    pBgm->setPan(_vec_pan[prm_bgm_no]);
}

void GgafDxBgmConductor::performFromTheBegining(int prm_bgm_no, bool prm_is_loop) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_bgm_no="<<prm_bgm_no<<"");
    }
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("�Ȃ��Z�b�g����Ă܂���Bprm_bgm_no="<<prm_bgm_no<<"");
    }
#endif

    _vec_volume[prm_bgm_no] = GGAF_MAX_VOLUME;
    _vec_pan[prm_bgm_no] = 0;
    _vec_is_fade[prm_bgm_no] = false;
    _vec_is_fadeafter_stop[prm_bgm_no] = true;
    _vec_target_volume[prm_bgm_no] = GGAF_MAX_VOLUME;
    _vec_inc_volume[prm_bgm_no] = 0;
    GgafDxBgm* pBgm = getBgm(prm_bgm_no);
    pBgm->stop();
    pBgm->setVolume(_vec_volume[prm_bgm_no]);
    pBgm->setPan(_vec_pan[prm_bgm_no]);
    pBgm->play(prm_is_loop);
//    GgafDxBgmConductor::_active_bgm_bpm = _vecBgmConnection[prm_bgm_no]->peek()->_bpm; //�ŐV��BGM��BPM���Y��
}

void GgafDxBgmConductor::perform(int prm_bgm_no, bool prm_is_loop) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_bgm_no="<<prm_bgm_no<<"");
    }
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("�Ȃ��Z�b�g����Ă܂���Bprm_bgm_no="<<prm_bgm_no<<"");
    }
#endif

    GgafDxBgm* pBgm = getBgm(prm_bgm_no);
    pBgm->setVolume(_vec_volume[prm_bgm_no]);
    pBgm->setPan(_vec_pan[prm_bgm_no]);
    pBgm->play(prm_is_loop);
//    GgafDxBgmConductor::_active_bgm_bpm = _vecBgmConnection[prm_bgm_no]->peek()->_bpm; //�ŐV��BGM��BPM���Y��
}

void GgafDxBgmConductor::stop(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_bgm_no="<<prm_bgm_no);
    }
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("�Ȃ��Z�b�g����Ă܂���Bprm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->stop();
    _vec_is_fade[prm_bgm_no] = false;
}

void GgafDxBgmConductor::pause(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_bgm_no="<<prm_bgm_no);
    }
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("�Ȃ��Z�b�g����Ă܂���Bprm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->pause();
    _TRACE_("GgafDxBgmConductor::pause("<<prm_bgm_no<<"):"<<_vecBgmConnection[prm_bgm_no]->getIdStr()<<" ��pause()���܂����B");
}

void GgafDxBgmConductor::pause() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        pause(bgm_no);
    }
}

void GgafDxBgmConductor::unpause(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_bgm_no="<<prm_bgm_no);
    }
    if (_vecBgmConnection[prm_bgm_no] == nullptr) {
        throwGgafCriticalException("�Ȃ��Z�b�g����Ă܂���Bprm_bgm_no="<<prm_bgm_no<<"");
    }
#endif
    getBgm(prm_bgm_no)->unpause();
    _TRACE_("GgafDxBgmConductor::unpause("<<prm_bgm_no<<"):"<<_vecBgmConnection[prm_bgm_no]->getIdStr()<<" unpause()���܂����B");
}

void GgafDxBgmConductor::unpause() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        unpause(bgm_no);
    }
}

void GgafDxBgmConductor::stop() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        stop(bgm_no);
    }
}

bool GgafDxBgmConductor::isPerforming(int prm_bgm_no) {
    return getBgm(prm_bgm_no)->isPlaying();
}

bool GgafDxBgmConductor::isPause(int prm_bgm_no) {
    return getBgm(prm_bgm_no)->isPause();
}
bool GgafDxBgmConductor::isStopping(int prm_bgm_no) {
    return getBgm(prm_bgm_no)->isStopping();
}
void GgafDxBgmConductor::setVolume(int prm_bgm_no, double prm_volume) {
    _vec_volume[prm_bgm_no] = prm_volume;
    getBgm(prm_bgm_no)->setVolume((int)(_vec_volume[prm_bgm_no]));
}

void GgafDxBgmConductor::setPan(int prm_bgm_no, float prm_pan) {
    _vec_pan[prm_bgm_no] = prm_pan;
    getBgm(prm_bgm_no)->setPan(_vec_pan[prm_bgm_no]);
}

GgafDxBgm* GgafDxBgmConductor::getBgm(int prm_bgm_no) {
#ifdef MY_DEBUG
    if (prm_bgm_no < 0 || prm_bgm_no >= _bgm_num) {
        throwGgafCriticalException("ID���͈͊O�ł��B0~"<<(_bgm_num-1)<<"�ł��肢���܂��Bprm_bgm_no="<<prm_bgm_no);
    }
#endif
    return _vecBgmConnection[prm_bgm_no]->peek();
}

void GgafDxBgmConductor::fade(int prm_bgm_no, frame prm_frame, int prm_target_volume) {
    //�����̃t�F�[�h���̏ꍇ
    //�t�F�[�h�������قȂ�ꍇ�͌㏟��
    //�t�F�[�h�����������ꍇ�́A�t�F�[�h�����̎c�t���[�������r���A������������ق�������
    double inc_volume = (prm_target_volume - getVolume(prm_bgm_no)) / (double)prm_frame;
    if (_vec_is_fade[prm_bgm_no]) {
        //�����t�F�[�h��
        int sgn_cur_inc_volume = SGN(_vec_inc_volume[prm_bgm_no]);
        int sgn_new_inc_volume = SGN(inc_volume);
        if (sgn_cur_inc_volume == sgn_new_inc_volume) {
            //�t�F�[�h����������
            //�c�t���[�����v�Z
            frame new_zan = ABS(prm_target_volume              - getVolume(prm_bgm_no)) / ABS(inc_volume);
            frame cur_zan = ABS(_vec_target_volume[prm_bgm_no] - getVolume(prm_bgm_no)) / ABS(_vec_inc_volume[prm_bgm_no]);
            if (cur_zan > new_zan) {
                //����w��t�F�[�h�̂ق��������������̂Ō㏟��
                _vec_target_volume[prm_bgm_no] = (double)prm_target_volume;
                _vec_inc_volume[prm_bgm_no] = inc_volume;
            } else {
                //����w��t�F�[�h�̂ق����x���̂ŁA����
                _TRACE_("GgafDxBgmConductor::fade prm_bgm_no="<<prm_bgm_no<<"("<<getBgm(prm_bgm_no)->_bgm_key<<")�̃t�F�[�h�w��́A"
                        "���Ƀt�F�[�h���̕���������������̂ŁA��������܂����B�����cf="<<cur_zan<<"/����ݒ�K�vf="<<new_zan);
            }
        } else {
            //�t�F�[�h�������قȂ�̂Ō㏟��
            _vec_target_volume[prm_bgm_no] = (double)prm_target_volume;
            _vec_inc_volume[prm_bgm_no] = inc_volume;
        }
    } else {
        //�����t�F�[�h�͖���
        _vec_is_fade[prm_bgm_no] = true;
        _vec_target_volume[prm_bgm_no] = (double)prm_target_volume;
        _vec_inc_volume[prm_bgm_no] = inc_volume;
    }
}

void GgafDxBgmConductor::performFadein(int prm_bgm_no, frame prm_frame) {
    setVolume(prm_bgm_no, GGAF_MIN_VOLUME);
    perform(prm_bgm_no, true);
    fade(prm_bgm_no, prm_frame, GGAF_MAX_VOLUME);
    _vec_is_fadeafter_stop[prm_bgm_no] = false;
}

void GgafDxBgmConductor::fadeoutStop(int prm_bgm_no, frame prm_frame) {
    fade(prm_bgm_no, prm_frame, GGAF_MIN_VOLUME);
    _vec_is_fadeafter_stop[prm_bgm_no] = true;
}

void GgafDxBgmConductor::fadeoutStopAll(frame prm_frame) {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        fadeoutStop(bgm_no, prm_frame);
    }
}

void GgafDxBgmConductor::behave() {
    for (int bgm_no = 0; bgm_no < _bgm_num; bgm_no++) {
        if (_vec_is_fade[bgm_no]) {
            if (isPerforming(bgm_no)) {
                //���ʃt�F�[�h
                addVolume(bgm_no, _vec_inc_volume[bgm_no]);
                if (_vec_inc_volume[bgm_no] > 0 && getVolume(bgm_no) >= _vec_target_volume[bgm_no]) {
                    //�����t�F�[�h������
                    setVolume(bgm_no, _vec_target_volume[bgm_no]);
                    _vec_is_fade[bgm_no] = false;
                } else if (_vec_inc_volume[bgm_no] < 0 && getVolume(bgm_no) <= _vec_target_volume[bgm_no]) {
                    //�����t�F�[�h������
                    setVolume(bgm_no, _vec_target_volume[bgm_no]);
                    _vec_is_fade[bgm_no] = false;
                    if (_vec_is_fadeafter_stop[bgm_no]) {
                        //�����t�F�[�h�������ɉ��t��~
                        stop(bgm_no);
                    }
                }
            }
        }
    }
}




GgafDxBgmConductor::~GgafDxBgmConductor() {
    for (int i = 0; i < _bgm_num; i++) {
        if (_vecBgmConnection[i]) {
            _vecBgmConnection[i]->close();
        }
    }
}
