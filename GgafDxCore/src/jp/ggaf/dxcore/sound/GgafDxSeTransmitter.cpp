#include "stdafx.h"
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

void GgafDxSeTransmitter::set(int prm_id, const char* prm_se_key, int prm_cannel) {

//    if (_se_num <= 0) {
//        throwGgafCriticalException("GgafDxSeTransmitter::set() useSeで使用するSe数を事前に宣言してください。prm_id="<<prm_id);
//    }
    if (_papSeConnection == nullptr) {
        declareSeNum(prm_id+1); //declareSeNumしない場合はprm_id+1個まで
    }
    if (prm_id < 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() IDが範囲外です。正の数でお願いします。 prm_id="<<prm_id);
    } else if (prm_id >= _se_num) {
        //_papSeConnection[] を拡張する。
        GgafDxSeConnection** papSeConnection = NEW GgafDxSeConnection*[_se_num];
        for (int i = 0; i < _se_num; i++) { //退避
            papSeConnection[i] = _papSeConnection[i];
        }
        GGAF_DELETEARR_NULLABLE(_papSeConnection);
        int wk_se_num = _se_num;
        declareSeNum(prm_id+1); //prm_id+1 へ個拡張。この時点で _se_num も prm_id+1 で更新される
        for (int i = 0; i < wk_se_num; i++) { //引き継ぐ（退避を戻し）
            _papSeConnection[i] = papSeConnection[i];
        }
        GGAF_DELETEARR_NULLABLE(papSeConnection);
    }
    if (strlen(prm_se_key) > 128) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() SE識別IDが長過ぎます。128文字に抑えて下さい。prm_se_key="<<prm_se_key);
    }
    char idstr[140];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_key); //資源コネクションの識別ID名を 「チャンネル番号 + "/" + wave識別名」
                                                      //とすることにより、チャンネル番号が同じならば new されない。
    if (_papSeConnection[prm_id]) {
        _TRACE_("GgafDxSeTransmitter::set() ＜警告＞ 既にID="<<prm_id<<" にはSE("<<(_papSeConnection[prm_id]->getIdStr())<<")が設定済みでした。資源接続を close 後、新しいSE("<<idstr<<")を上書きします。意図してますか？");
        _papSeConnection[prm_id]->close();
    }
    _papSeConnection[prm_id] = connectToSeManager(idstr);
}


void GgafDxSeTransmitter::play(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
#endif
    _papSeConnection[prm_id]->peek()->play(GGAF_MAX_VOLUME, 0.0);
}

GgafDxSe* GgafDxSeTransmitter::get(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
#endif
    return _papSeConnection[prm_id]->peek();
}


GgafDxSeTransmitter::~GgafDxSeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_papSeConnection[i]) {
            _papSeConnection[i]->close();
        }
    }
    GGAF_DELETEARR_NULLABLE(_papSeConnection);
}

