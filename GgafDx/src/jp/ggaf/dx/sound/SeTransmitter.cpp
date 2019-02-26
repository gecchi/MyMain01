#include "jp/ggaf/dx/sound/SeTransmitter.h"

#include "jp/ggaf/dx/manager/SeManager.h"
#include "jp/ggaf/dx/manager/SeConnection.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/Se.h"
#include <stdio.h>


using namespace GgafDx;


SeTransmitter::SeTransmitter() : GgafCore::Object() {
    _se_num = 0;
    //大体5個ぐらいで；
    _vecSeConnection.reserve(5);
    _vec_volume.reserve(5);
    _vec_pan.reserve(5);
}

void SeTransmitter::set(int prm_se_no, const char* prm_se_key, int prm_cannel) {
    int se_num = _vecSeConnection.size();
    if (prm_se_no >= se_num) {
        for (int i = se_num; i <= prm_se_no; i++) {
            _vecSeConnection.push_back(nullptr);
            _vec_volume.push_back(GGAF_MAX_VOLUME);
            _vec_pan.push_back(0);
        }
        _se_num = _vecSeConnection.size();
    }

    if (strlen(prm_se_key) > 128) {
        throwCriticalException("SE識別IDが長過ぎます。128文字に抑えて下さい。prm_se_key="<<prm_se_key);
    }
    std::string idstr =  XTOS(prm_cannel) + "," + prm_se_key; //資源コネクションの識別ID名を 「チャンネル番号 + "," + wave識別名」
                                                              //とすることにより、チャンネル番号が同じならば new されない。
    if (_vecSeConnection[prm_se_no]) {
        _TRACE_("＜警告＞ 既にID="<<prm_se_no<<" にはSE("<<(_vecSeConnection[prm_se_no]->getIdStr())<<")が設定済みでした。資源接続を close 後、新しいSE("<<idstr<<")を上書きします。意図してますか？");
        _vecSeConnection[prm_se_no]->close();
    }
    _vecSeConnection[prm_se_no] = connectToSeManager(idstr.c_str());
    stop(prm_se_no);
    setVolume(prm_se_no, _vec_volume[prm_se_no]);
    setPan(prm_se_no, _vec_pan[prm_se_no]);
}

void SeTransmitter::setVolume(int prm_se_no, double prm_volume) {
    _vec_volume[prm_se_no] = prm_volume;
    getSe(prm_se_no)->setVolume((int)(_vec_volume[prm_se_no]));
}

void SeTransmitter::setPan(int prm_se_no, float prm_pan) {
    _vec_pan[prm_se_no] = prm_pan;
    getSe(prm_se_no)->setPan(_vec_pan[prm_se_no]);
}

void SeTransmitter::play(int prm_se_no, bool prm_can_looping) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwCriticalException("IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    Se* pSe = getSe(prm_se_no);
    pSe->setVolume(_vec_volume[prm_se_no]);
    pSe->setPan(_vec_pan[prm_se_no]);
    pSe->play(prm_can_looping);
}

void SeTransmitter::stop(int prm_se_no) {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwCriticalException("IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    getSe(prm_se_no)->stop();
}

Se* SeTransmitter::getSe(int prm_se_no) const {
#ifdef MY_DEBUG
    if (prm_se_no < 0 || prm_se_no >= _se_num) {
        throwCriticalException("getSe() IDが範囲外です。0~"<<(_se_num-1)<<"でお願いします。prm_se_no="<<prm_se_no);
    }
#endif
    if (_vecSeConnection[prm_se_no]) {
        return _vecSeConnection[prm_se_no]->peek();
    } else {
        throwCriticalException("_vecSeConnectionがありません。prm_se_no="<<prm_se_no);
    }
}


SeTransmitter::~SeTransmitter() {
    for (int i = 0; i < _se_num; i++) {
        if (_vecSeConnection[i]) {
            _vecSeConnection[i]->close();
        }
    }
}

