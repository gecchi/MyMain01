#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxSeTransmitter::GgafDxSeTransmitter() : GgafObject() {
    _se_num = 0;
    _papSeCon = NULL;
}

void GgafDxSeTransmitter::declareSeNum(int prm_se_num) {
    _se_num = prm_se_num;
    _papSeCon = NEW GgafDxSeConnection*[_se_num];
    for (int i = 0; i < _se_num; i++) {
        _papSeCon[i] = NULL;
    }
}

void GgafDxSeTransmitter::set(int prm_id, const char* prm_se_name, int prm_cannel) {

//    if (_se_num <= 0) {
//        throwGgafCriticalException("GgafDxSeTransmitter::set() useSeで使用するSe数を事前に宣言してください。prm_id="<<prm_id);
//    }
    if (_papSeCon == NULL) {
        declareSeNum(3); //declareSeNumしない場合は3個まで
    }
    if (prm_id < 0) {
        throwGgafCriticalException("GgafDxSeTransmitter::set() IDが範囲外です。正の数でお願いします。 prm_id="<<prm_id);
    } else if (prm_id >= _se_num) {
        //_papSeCon[] を拡張する。
        GgafDxSeConnection** papSeCon = NEW GgafDxSeConnection*[_se_num];
        for (int i = 0; i < _se_num; i++) {
            papSeCon[i] = _papSeCon[i];
        }
        DELETEARR_POSSIBLE_NULL(_papSeCon);
        int wk_se_num = _se_num;
        declareSeNum(_se_num+2); //2個拡張
        for (int i = 0; i < wk_se_num; i++) {
            _papSeCon[i] = papSeCon[i];
        }
        DELETEARR_POSSIBLE_NULL(papSeCon);
    }

    char idstr[129];
    sprintf(idstr, "%d/%s", prm_cannel, prm_se_name); //資源コネクションの識別ID名を 「チャンネル番号 + "/" + wave識別名」
                                                      //とすることにより、チャンネル番号が同じならば new されない。
    _papSeCon[prm_id] = connectToSeManager(idstr);
}

void GgafDxSeTransmitter::play(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
#endif
    _papSeCon[prm_id]->fetch()->play(GGAF_MAX_VOLUME, 0.0);
}

GgafDxSe* GgafDxSeTransmitter::get(int prm_id) {
#ifdef MY_DEBUG
    if (prm_id < 0 || prm_id >= _se_num) {
        throwGgafCriticalException("GgafDxSeTransmitter::play() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_id="<<prm_id);
    }
#endif
    return _papSeCon[prm_id]->fetch();
}


GgafDxSeTransmitter::~GgafDxSeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_papSeCon[i]) {
            _papSeCon[i]->close();
        }
    }
    DELETEARR_POSSIBLE_NULL(_papSeCon);
}

