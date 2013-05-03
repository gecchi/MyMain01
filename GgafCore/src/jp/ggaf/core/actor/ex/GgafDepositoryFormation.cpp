#include "stdafx.h"
using namespace GgafCore;

GgafDepositoryFormation::GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafDepositoryFormation";
    _pDepo = nullptr;
    _can_call_up = true;
    _was_all_destroyed = false;
}
void GgafDepositoryFormation::setFormationMemberDepo(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepo 既にデポジトリは登録済みです。\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo && prm_pDepo->_pSubFirst) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepo 不正なデポジトリです。\n"<<
                                   "this="<<getName()<<" prm_pDepo="<<prm_pDepo);

    }
#endif
    _pDepo = prm_pDepo;
    //団長に種別を正しく伝えるためにデポジトリ種別引継ぎ
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
#ifdef MY_DEBUG
    if (_pDepo->getSubFirst()) {

    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMemberDepo("<<prm_pDepo->getName()<<") 引数デポジトリのサブが存在しません this="<<getName());
    }
#endif
}

void GgafDepositoryFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return;
    }

    if (_listFollower.length() == 0) {
        if (_can_call_up) {
            //編隊メンバーが0だが、まだ callUp の最中。
            return;
        } else {
            //編隊メンバーが0かつ、
            //もうこれ以上 callUp 不可は、
            //編隊自体がさよなら
            onSayonaraAll(); //コールバック
            sayonara(_offset_frames_end);
            _was_all_sayonara = true;
        }
    } else {
        //編隊メンバー状況チェック
        GgafActor* pFollower = _listFollower.getCurrent();
        for (int i = 0; i < _listFollower.length(); i++) {
            if (_can_live_flg) {
                if (pFollower->_is_active_flg) {
                    pFollower = _listFollower.next();
                } else if (pFollower->_will_activate_after_flg && (pFollower->_frame_of_life <= pFollower->_frame_of_life_when_activation)) {
                    //未来に活動予定でも残す
                    pFollower = _listFollower.next();
                } else {
                    //編隊メンバーから外す
//					_TRACE_("今メンバー数"<<_listFollower.length()<<" そしてこれから"<<_listFollower.getCurrent()->getName()<<"をメンバーから外します！(X)");
                    _listFollower.remove(); //remove() 時、新たなカレント要素は next の要素になる。
                }
            } else {
                //編隊メンバーから外す
//                 _TRACE_("今メンバー数"<<_listFollower.length()<<" そして"<<_listFollower.getCurrent()->getName()<<"をメンバーから外します！(A)");
                _listFollower.remove();//remove() 時、新たなカレント要素は next の要素になる。
            }
        }
    }
}

GgafActor* GgafDepositoryFormation::callUpMember(int prm_formation_sub_num) {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return nullptr;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::callUpUntil "<<getName()<<"は、Depositoryが指定されてません。setFormationMemberDepoが必要です。"<<
                                   "this="<<getName()<<" _num_formation_member="<<_num_formation_member);
    }
#endif
    if (prm_formation_sub_num <= _num_formation_member) {
        _can_call_up = false;
        return nullptr; //もうこれ以上callUpUntil不可
    } else {
        GgafMainActor* pActor = _pDepo->dispatch();
        if (pActor) {
            _num_formation_member++;
            _can_call_up = true;
            pActor->_pFormation = this;
            _listFollower.addLast(pActor, false);
            return (GgafActor*)pActor;
        } else {
            _can_call_up = false;
            return nullptr; //もうこれ以上callUpUntil不可
        }
    }
}

bool GgafDepositoryFormation::canCallUp() {
    return _can_call_up;
}

void GgafDepositoryFormation::onEnd() {
    GgafFormation::onEnd();
    sayonaraFollwer();
}
void GgafDepositoryFormation::sayonaraFollwer() {
    if (_listFollower.length() == 0) {
        return;
    }
    while (_listFollower.length() > 0) {
        GgafActor* pFollower =  _listFollower.getCurrent();
        if (pFollower->_pFormation == this) {
            _TRACE_("GgafDepositoryFormation::sayonaraFollwer _listFollowerの"<<_listFollower.getCurrent()->getName()<<"をsayonaraします。");
            _listFollower.getCurrent()->sayonara();
        }
        _listFollower.remove();
    }

}

GgafDepositoryFormation::~GgafDepositoryFormation() {

}
