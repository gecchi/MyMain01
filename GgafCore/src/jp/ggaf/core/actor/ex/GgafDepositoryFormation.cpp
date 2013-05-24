#include "stdafx.h"
#include "jp/ggaf/core/actor/ex/GgafDepositoryFormation.h"

#include "jp/ggaf/core/util/GgafStatus.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"


using namespace GgafCore;

GgafDepositoryFormation::GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafDepositoryFormation";
    _pDepo = nullptr;
    _can_call_up = true;
    _was_all_destroyed = false;
}
void GgafDepositoryFormation::setFormationMember(GgafActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember 既にデポジトリは登録済み("<<_pDepo->getName()<<")です。\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember 不正なデポジトリです。\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo->getSubFirst()) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember("<<prm_pDepo->getName()<<") 引数デポジトリのサブが存在しません。\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
    if (prm_pDepo->getPlatformScene()) {
        //OK
    } else {
        throwGgafCriticalException("GgafDepositoryFormation::setFormationMember("<<prm_pDepo->getName()<<") 引数デポジトリがシーンに未所属です。\n"<<
                                   "this="<<this<<"("<<getName()<<") prm_pDepo="<<prm_pDepo);
    }
#endif
    _pDepo = prm_pDepo;
    //団長に種別を正しく伝えるためにデポジトリ種別引継ぎ
    _pStatus->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->_pStatus->get(STAT_DEFAULT_ACTOR_KIND));
}

void GgafDepositoryFormation::processFinal() {
//    _TRACE_("processFinal() "<<getActiveFrame()<<":before----->");
//    for (int i = 0; i < _listFollower.length(); i++) {
//        _TRACE_("processFinal() _listFollower["<<i<<"]="<<_listFollower.getFromFirst(i)->getName()<<"("<<_listFollower.getFromFirst(i)<<")");
//    }
//    _TRACE_("processFinal() "<<getActiveFrame()<<"<-----");
    if (_listFollower.length() > 0) {
        //編隊メンバー状況チェック
        GgafActor* pFollower;
        for (int i = 0; i < _listFollower.length(); i++) { //
            pFollower = _listFollower.getCurrent();
            if (_can_live_flg) {
                if (pFollower->_is_active_flg) {
                    _listFollower.next();
                } else if (pFollower->_will_activate_after_flg && (pFollower->_frame_of_life <= pFollower->_frame_of_life_when_activation)) {
                    //未来に活動予定でも残す
                    _listFollower.next();
                } else {
                    //編隊メンバーから外す
//                    _TRACE_("i="<<i<<" 今メンバー数"<<_listFollower.length()<<" そしてこれから"<<_listFollower.getCurrent()->getName()<<"をメンバーから外します！(X)");
                    _listFollower.getCurrent()->_pFormation = nullptr;
                    _listFollower.remove(); //remove() 時、新たなカレント要素は next の要素になる。
                }
            } else {
                //編隊メンバーから外す
//                 _TRACE_("i="<<i<<" 今メンバー数"<<_listFollower.length()<<" そして"<<_listFollower.getCurrent()->getName()<<"をメンバーから外します！(A)");
                _listFollower.getCurrent()->_pFormation = nullptr;
                _listFollower.remove();//remove() 時、新たなカレント要素は next の要素になる。
            }
        }
    }

    if (_listFollower.length() == 0) {
        if (_can_call_up == false && _was_all_sayonara == false) {
            //編隊メンバーが0かつ、
            //もうこれ以上 callUp 不可で、onSayonaraAll()コールバック未実行の場合
            onSayonaraAll(); //コールバック
            sayonara(_offset_frames_end); //編隊自体がさよなら。
            _was_all_sayonara = true;
        }
    }
}

GgafActor* GgafDepositoryFormation::callUpMember(int prm_formation_sub_num) {
    if (_can_call_up == false || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return nullptr;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwGgafCriticalException("GgafDepositoryFormation::callUpUntil "<<getName()<<"は、Depositoryが指定されてません。setFormationMemberが必要です。"<<
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
        if (_listFollower.getCurrent()->_pFormation == this) {
            _listFollower.getCurrent()->sayonara();
            _listFollower.getCurrent()->_pFormation = nullptr;
        } else {
            throwGgafCriticalException("GgafDepositoryFormation::sayonaraFollwer() _listFollowerに自身のformation管理ではないメンバーがいました！\n"<<
                                       " this="<<getName()<<"("<<this<<") \n"<<
                                       " _listFollower.getCurrent()="<<(_listFollower.getCurrent()->getName())<<"("<<(_listFollower.getCurrent())<<") \n"<<
                                       " _listFollower.getCurrent()->_pFormation="<<(_listFollower.getCurrent()->_pFormation->getName())<<"("<<(_listFollower.getCurrent()->_pFormation)<<") ");
        }
        _listFollower.remove();
    }

}

GgafDepositoryFormation::~GgafDepositoryFormation() {

}
