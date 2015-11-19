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
    _papSeConnection = nullptr;
}

void GgafDxSeTransmitter::declareSeNum(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeConnection = NEW GgafDxSeConnection*[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeConnection[i] = nullptr;
    }
}

void GgafDxSeTransmitter::set(int prm_se_no, const char* prm_se_key, int prm_cannel) {
    if (_papSeConnection == nullptr) {
        declareSeNum(prm_se_no+1); //declareSeNumしない場合はprm_id+1個まで
    }
    if (prm_se_no < 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() IDが範囲外です。正の数でお願いします。 prm_se_no="<<prm_se_no);
    } else if (prm_se_no >= _se_num) {
        //_papSeConnection[] を拡張する。
        int wk_se_num = _se_num;
        GgafDxSeConnection** papSeConnection = NEW GgafDxSeConnection*[_se_num];
        for (int i = 0; i < wk_se_num; i++) { //退避
            papSeConnection[i] = _papSeConnection[i];
        }
        GGAF_DELETEARR_NULLABLE(_papSeConnection);
        declareSeNum(prm_se_no+1); //prm_se_no+1 へ個拡張。この時点で _se_num も prm_se_no+1 で更新される
        for (int i = 0; i < wk_se_num; i++) { //引き継ぐ（退避を戻し）
            _papSeConnection[i] = papSeConnection[i];
        }
        GGAF_DELETEARR_NULLABLE(papSeConnection);
    }
    if (strlen(prm_se_key) > 128) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() SE識別IDが長過ぎます。128文字に抑えて下さい。prm_se_key="<<prm_se_key);
    }
    std::string idstr =  XTOS(prm_cannel) + "/" + prm_se_key; //資源コネクションの識別ID名を 「チャンネル番号 + "/" + wave識別名」
                                                              //とすることにより、チャンネル番号が同じならば new されない。
    if (_papSeConnection[prm_se_no]) {
        _TRACE_("GgafDxSeTransmitter::set() ＜警告＞ 既にID="<<prm_se_no<<" にはSE("<<(_papSeConnection[prm_se_no]->getIdStr())<<")が設定済みでした。資源接続を close 後、新しいSE("<<idstr<<")を上書きします。意図してますか？");
        _papSeConnection[prm_se_no]->close();
    }
    _papSeConnection[prm_se_no] = connectToSeManager(idstr.c_str());
}


void GgafDxSeTransmitter::play(int prm_se_no) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    _papSeConnection[prm_se_no]->peek()->play();
}

void GgafDxSeTransmitter::stop(int prm_se_no) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::stop() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    _papSeConnection[prm_se_no]->peek()->stop();
}

void GgafDxSeTransmitter::setLooping(int prm_se_no, bool prm_can_looping) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::setLooping() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    _papSeConnection[prm_se_no]->peek()->setLooping(prm_can_looping);
}

GgafDxSe* GgafDxSeTransmitter::get(int prm_se_no) const {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
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
}

