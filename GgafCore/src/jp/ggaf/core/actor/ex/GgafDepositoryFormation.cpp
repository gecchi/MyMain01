#include "stdafx.h"
using namespace std;
using namespace GgafCore;

GgafDepositoryFormation::GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, NULL)
{
    _class_name = "GgafDepositoryFormation";
    _pDepo = NULL;
    _is_called_up = false;
    _is_all_called_up = false;
}
void GgafDepositoryFormation::setFormationAbleActorDepository(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationAbleActorDepository 既にデポジトリは登録済みです。\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo && prm_pDepo->_pSubFirst) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationAbleActorDepository 不正なデポジトリです。\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);

    }

#endif
    _pDepo = prm_pDepo;
    //団長に種別を正しく伝えるためにデポジトリ種別引継ぎ
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));

    if (_pDepo->getSubFirst()) {

    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationAbleActorDepository("<<prm_pDepo->getName()<<") 引数デポジトリのサブが存在しません this="<<getName());
    }
}


GgafActor* GgafDepositoryFormation::callUpUntil(int prm_formation_sub_num) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return NULL;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::callUpUntil "<<getName()<<"は、Depositoryが指定されてません。setFormationAbleActorDepositoryが必要です。"<<
                                   "this="<<getName()<<" _num_sub="<<_num_sub);
    }
#endif
    _is_called_up = true;
    if (prm_formation_sub_num < _num_sub) {
        _is_all_called_up = true;
        return NULL; //もうこれ以上callUpUntil不可
    } else {
        GgafMainActor* pActor = _pDepo->dispatch();
        if (pActor) {
            _num_sub++;
            _is_all_called_up = false;
            pActor->_pFormation = this;
            _listFllower.addLast(pActor, false);
            return (GgafActor*)pActor;
        } else {
            _is_all_called_up = true;
            return NULL; //もうこれ以上callUpUntil不可
        }
    }
}

void GgafDepositoryFormation::processJudgement() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    }

    if (_listFllower.length() == 0) {
        if (_is_all_called_up) {
            //もうこれ以上callUpUntil不可で
            //メンバーが0の場合はさよなら
            sayonara(_offset_frames_end);
        } else {
            //メンバーが0だが、まだ追加中。
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
void GgafDepositoryFormation::onEnded() {
    GgafFormation::onEnded();
    sayonaraFollwer();
}
void GgafDepositoryFormation::sayonaraFollwer() {
    if (_listFllower.length() == 0) {
        return;
    }
    while (_listFllower.length() > 0) {
        GgafActor* pFllower =  _listFllower.getCurrent();
        if (pFllower->_pFormation == this) {
            _TRACE_("GgafDepositoryFormation::sayonaraFollwer _listFllowerの"<<_listFllower.getCurrent()->getName()<<"をsayonaraします。");
            _listFllower.getCurrent()->sayonara();
        }
        _listFllower.remove();
    }

}

GgafDepositoryFormation::~GgafDepositoryFormation() {

}
