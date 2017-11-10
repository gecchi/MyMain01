#include "jp/ggaf/dxcore/sound/GgafDxSeTransmitter.h"

#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include <stdio.h>

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSeTransmitter::GgafDxSeTransmitter() : GgafObject() {
    _se_num = 0;
    _pa_volume = nullptr;
    _pa_pan = nullptr;
    _papSeConnection = nullptr;
}

void GgafDxSeTransmitter::declareSeNum(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeConnection = NEW GgafDxSeConnection*[_se_num];
    _pa_volume = NEW double[_se_num];
    _pa_pan = NEW float[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeConnection[i] = nullptr;
        _pa_volume[i] = GGAF_MAX_VOLUME;
        _pa_pan[i] = 0;
    }
}

void GgafDxSeTransmitter::set(int prm_se_no, const char* prm_se_key, int prm_cannel) {
    if (_papSeConnection == nullptr) {
        declareSeNum(prm_se_no+1); //declareSeNumしない場合はprm_id+1個まで
    }
    if (prm_se_no < 0) {
        throwGgafCriticalException("IDが範囲外です。正の数でお願いします。 prm_se_no="<<prm_se_no);
    } else if (prm_se_no >= _se_num) {
        //拡張する。
        int wk_se_num = _se_num;
        GgafDxSeConnection** papSeConnection = NEW GgafDxSeConnection*[_se_num];
        double* pa_volume = NEW double[_se_num];
        float*  pa_pan    = NEW float[_se_num];
        for (int i = 0; i < wk_se_num; i++) { //退避
            papSeConnection[i] = _papSeConnection[i];
            pa_volume[i] = _pa_volume[i];
            pa_pan[i] = _pa_pan[i];
        }
        GGAF_DELETEARR_NULLABLE(_papSeConnection);
        GGAF_DELETEARR_NULLABLE(_pa_volume);
        GGAF_DELETEARR_NULLABLE(_pa_pan);
        declareSeNum(prm_se_no+1); //prm_se_no+1 へ個拡張。この時点で _se_num も prm_se_no+1 で更新される
        for (int i = 0; i < wk_se_num; i++) { //引き継ぐ（退避を戻し）
            _papSeConnection[i] = papSeConnection[i];
            _pa_volume[i] = pa_volume[i];
            _pa_pan[i] = pa_pan[i];
        }
        GGAF_DELETEARR_NULLABLE(papSeConnection);
        GGAF_DELETEARR_NULLABLE(pa_volume);
        GGAF_DELETEARR_NULLABLE(pa_pan);
    }
    if (strlen(prm_se_key) > 128) {
        throwGgafCriticalException("SE識別IDが長過ぎます。128文字に抑えて下さい。prm_se_key="<<prm_se_key);
    }
    std::string idstr =  XTOS(prm_cannel) + "/" + prm_se_key; //資源コネクションの識別ID名を 「チャンネル番号 + "/" + wave識別名」
                                                              //とすることにより、チャンネル番号が同じならば new されない。
    if (_papSeConnection[prm_se_no]) {
        _TRACE_("＜警告＞ 既にID="<<prm_se_no<<" にはSE("<<(_papSeConnection[prm_se_no]->getIdStr())<<")が設定済みでした。資源接続を close 後、新しいSE("<<idstr<<")を上書きします。意図してますか？");
        _papSeConnection[prm_se_no]->close();
    }
    _papSeConnection[prm_se_no] = connectToSeManager(idstr.c_str());
    stop(prm_se_no);
    setVolume(prm_se_no, _pa_volume[prm_se_no]);
    setPan(prm_se_no, _pa_pan[prm_se_no]);
}

void GgafDxSeTransmitter::setVolume(int prm_se_no, double prm_volume) {
    _pa_volume[prm_se_no] = prm_volume;
    getSe(prm_se_no)->setVolume((int)(_pa_volume[prm_se_no]));
}

void GgafDxSeTransmitter::setPan(int prm_se_no, float prm_pan) {
    _pa_pan[prm_se_no] = prm_pan;
    getSe(prm_se_no)->setPan(_pa_pan[prm_se_no]);
}

void GgafDxSeTransmitter::play(int prm_se_no, bool prm_can_looping) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    GgafDxSe* pSe = getSe(prm_se_no);
    pSe->setVolume(_pa_volume[prm_se_no]);
    pSe->setPan(_pa_pan[prm_se_no]);
    pSe->play(prm_can_looping);
}

void GgafDxSeTransmitter::stop(int prm_se_no) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    getSe(prm_se_no)->stop();
}

GgafDxSe* GgafDxSeTransmitter::getSe(int prm_se_no) const {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    return _papSeConnection[prm_se_no]->peek();
}


GgafDxSeTransmitter::~GgafDxSeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_papSeConnection[i]) {
            _papSeConnection[i]->close();
        }
    }
    GGAF_DELETEARR_NULLABLE(_papSeConnection);
    GGAF_DELETEARR_NULLABLE(_pa_volume);
    GGAF_DELETEARR_NULLABLE(_pa_pan);
}

