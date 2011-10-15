#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafDeositoryFormation::GgafDeositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, NULL)
{
    _class_name = "GgafDeositoryFormation";
    _pDepo = NULL;
    _is_called_up = false;
}
void GgafDeositoryFormation::setFormationAbleActorDepository(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDeositoryFormation::setFormationAbleActorDepository 既にデポジトリは登録済みです。\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo && _pDepo->_pSubFirst) {
        //OK
    } else {
        throwGgafCriticalException("GgafDeositoryFormation::setFormationAbleActorDepository 不正なデポジトリです。\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);

    }

#endif
    _pDepo = prm_pDepo;
    //デポジトリ種別引継ぎ
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));


    GgafActor* pActor = _pDepo->getSubFirst();
    if (pActor) {

    } else {
        throwGgafCriticalException("GgafDeositoryFormation::setFormationAbleActorDepository("<<prm_pDepo->getName()<<") 引数デポジトリのサブが存在しません this="<<getName());
    }
}


GgafActor* GgafDeositoryFormation::callUp() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDeositoryFormation::callUp "<<getName()<<"は、Depositoryが指定されてません。setFormationAbleActorDepositoryが必要です。"<<
                                   "this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    GgafActor* pActor = _pDepo->dispatch();
    if (pActor) {
        _num_sub++;

        pActor->_pFormation = this;
        _listFllower.addLast(pActor, false);
    }
    _is_called_up = true;
    return (GgafActor*)pActor;
}

void GgafDeositoryFormation::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        if (_is_called_up && _num_sub == 0) { //デポジトリモード時、いきなり借りれない場合、フォーメーションはなかったことになり、自身を終了
            sayonara(_offset_frames_end);
        }
    }

    if (_listFllower.length() == 0) {
        if (_num_sub > 0) {
            //過去に１度でも追加した後、メンバーが0の場合はさよなら
            sayonara(_offset_frames_end);
        } else {
            //メンバーが0だが、過去に１度も追加していない。
            //つまり、生成直後であるのでそのまま。
            return;
        }
    } else {
        //不正ポインタのチェック
        GgafActor* pFllower = _listFllower.getCurrent();
        int num_follwer = _listFllower.length();
        for (int i = 0; i < num_follwer; i++) {
            if (_can_live_flg && (pFllower->_is_active_flg || pFllower->_will_activate_after_flg)) {
                pFllower = _listFllower.next();
            } else {
                _listFllower.remove();
            }
        }
    }


}
void GgafDeositoryFormation::onGarbaged() {
    GgafActor::onGarbaged();
    sayonaraFollwer();
}
void GgafDeositoryFormation::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
    while (_listFllower.length() > 0) {
        GgafActor* pFllower =  _listFllower.getCurrent();
        if (pFllower->_pFormation == this) {
            _TRACE_("GgafFormation::sayonaraFollwer _listFllowerの"<<_listFllower.getCurrent()->getName()<<"をsayonaraします。");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

GgafDeositoryFormation::~GgafDeositoryFormation() {

}
