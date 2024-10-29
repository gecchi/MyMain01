#include "jp/ggaf/core/actor/ex/DepositoryFormation.h"

#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"


using namespace GgafCore;

DepositoryFormation::DepositoryFormation(const char* prm_name, frame prm_offset_frames_end) :
        Formation(prm_name, prm_offset_frames_end)
{
    _class_name = "DepositoryFormation";
    _pDepo = nullptr;
    _can_called_up = true;
}
void DepositoryFormation::setFormationMember(ActorDepository* prm_pDepo) {
#ifdef MY_DEBUG
    if (_pDepo) {
        throwCriticalException("既にデポジトリは登録済み("<<_pDepo->getName()<<")です。\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
    if (prm_pDepo) {
        //OK
    } else {
        throwCriticalException("不正なデポジトリです。\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
    if (prm_pDepo->getChildFirst()) {
        //OK
    } else {
        throwCriticalException("引数デポジトリの子が存在しません。\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
    if (prm_pDepo->getSceneChief()) {
        //OK
    } else {
        throwCriticalException("引数デポジトリがシーンに未所属(SceneChiefが見えない)です。\n"
                                   "this="<<NODE_INFO<<" prm_pDepo="<<NODE_INFO_P(prm_pDepo)<<"");
    }
#endif
    _pDepo = prm_pDepo;
    _num_formation_member = _pDepo->getNumChild();
    //団長に種別を正しく伝えるためにデポジトリ種別引継ぎ
    //getStatus()->set(STAT_DEFAULT_ACTOR_KIND, _pDepo->getCheckerKind());
    //TODO:↑必要だっただろうか、Treeじゃないので不要ではないか？？2015/02/20

    //setDefaultKind(prm_pDepo->getCheckerKind());
}

void DepositoryFormation::processFinal() {
//    _TRACE_("processFinal() "<<getActiveFrame()<<":before----->");
//    for (int i = 0; i < _listFollower.length(); i++) {
//        _TRACE_("processFinal() _listFollower["<<i<<"]="<<_listFollower.getFromFirst(i)->getName()<<"("<<_listFollower.getFromFirst(i)<<")");
//    }
//    _TRACE_("processFinal() "<<getActiveFrame()<<"<-----");

    int n = _listFollower.length();
    Actor* pFollower;
    for (int i = 0; i < n; i++) {
        pFollower = _listFollower.getCurrent();
        if (pFollower->isActive() || pFollower->isActivateScheduled()) {
            _listFollower.next();
        } else {
            //編隊メンバーから外す
            _listFollower.remove()->_pFormation = nullptr; //remove() 時、新たなカレント要素は next の要素になる。
        }
    }

    if (_listFollower.length() == 0) {
        if (_can_called_up == false && _was_all_sayonara == false) {
            //編隊メンバーが0かつ、
            //もうこれ以上 calledUp 不可で、onSayonaraAll()コールバック未実行の場合
            onSayonaraAll(); //コールバック
            sayonara(_offset_frames_end); //編隊自体がさよなら。
            _was_all_sayonara = true;
        }
    }

//    if (_listFollower.length() > 0) {
//        //編隊メンバー状況チェック
//        Actor* pFollower;
//        for (int i = 0; i < _listFollower.length(); i++) { //ループで _listFollower.remove() するので、ローカルに落とせない
//            pFollower = _listFollower.getCurrent();
//            if (_can_live_flg) {
//                if (pFollower->_is_active_flg) {
//                    _listFollower.next();
//                } else if (pFollower->isActivateScheduled()) {
//                    //未来に活動予定でも残す
//                    _listFollower.next();
//                } else {
//                    //編隊メンバーから外す
////                    _TRACE_("i="<<i<<" 今メンバー数"<<_listFollower.length()<<" そしてこれから"<<_listFollower.getCurrent()->getName()<<"をメンバーから外します！(X)");
//                    _listFollower.getCurrent()->_pFormation = nullptr;
//                    _listFollower.remove(); //remove() 時、新たなカレント要素は next の要素になる。
//                }
//            } else {
//                //編隊メンバーから外す
////                 _TRACE_("i="<<i<<" 今メンバー数"<<_listFollower.length()<<" そして"<<_listFollower.getCurrent()->getName()<<"をメンバーから外します！(A)");
//                _listFollower.getCurrent()->_pFormation = nullptr;
//                _listFollower.remove();//remove() 時、新たなカレント要素は next の要素になる。
//            }
//        }
//    }

//    if (_listFollower.length() == 0) {
//        if (_can_called_up == false && _was_all_sayonara == false) {
//            //編隊メンバーが0かつ、
//            //もうこれ以上 calledUp 不可で、onSayonaraAll()コールバック未実行の場合
//            onSayonaraAll(); //コールバック
//            sayonara(_offset_frames_end); //編隊自体がさよなら。
//            _was_all_sayonara = true;
//        }
//    }
}

Actor* DepositoryFormation::calledUpMember(int prm_formation_child_num) {
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
        return nullptr;
    }
#ifdef MY_DEBUG
    if (!_pDepo) {
        throwCriticalException(getName()<<"は、Depositoryが指定されてません。setFormationMemberが必要です。"
                                   "this="<<getName()<<" _num_formation_member="<<_num_formation_member);
    }
#endif
    if (prm_formation_child_num	> 0) {
        if (_can_called_up) {
            MainActor* pActor = _pDepo->dispatch();
            if (pActor) {
                _can_called_up = true;
                _num_called_up++;
                pActor->_pFormation = this;
                _listFollower.addLast(pActor, false);
                if (prm_formation_child_num <= _num_called_up) {
                    _can_called_up = false; //次回から calledUpMember() 不可
                    _num_formation_member = _num_called_up; //destroyedFollower 編隊全滅判定の為再設定
                }
                return (Actor*)pActor;
            } else {
                _can_called_up = false; //次回から calledUpMember() 不可
                _num_formation_member = _num_called_up; //destroyedFollower 編隊全滅判定の為再設定
                return nullptr; //もうこれ以上calledUpUntil不可
            }

        } else {
            return nullptr;
        }
    } else {
        _can_called_up = false; //次回から calledUpMember() 不可
        _num_formation_member = _num_called_up; //destroyedFollower 編隊全滅判定の為再設定
        return nullptr; //もうこれ以上calledUpUntil不可
    }
}

bool DepositoryFormation::canCalledUp() const {
    return _can_called_up;
}

void DepositoryFormation::onEnd() {
    Formation::onEnd();
    sayonaraFollwer();
}

void DepositoryFormation::sayonaraFollwer() {
    int n = _listFollower.length();
    Actor* pFollower;
    for (int i = 0; i < n; i++) {
#ifdef MY_DEBUG
        if (_listFollower.getCurrent()->_pFormation != this) {
            throwCriticalException("_listFollowerに自身のformation管理ではないメンバーがいました。なんか壊れてます。\n"
                                       " this="<<NODE_INFO<<" \n"
                                       " _listFollower.getCurrent()="<<(_listFollower.getCurrent()->getName())<<"("<<(_listFollower.getCurrent())<<") \n"
                                       " _listFollower.getCurrent()->_pFormation="<<(_listFollower.getCurrent()->_pFormation->getName())<<"("<<(_listFollower.getCurrent()->_pFormation)<<") ");

        }
#endif
        pFollower = _listFollower.remove();
        pFollower->_pFormation = nullptr;
        pFollower->sayonara();

    }


//    if (_listFollower.length() == 0) {
//        return;
//    }
//    while (_listFollower.length() > 0) {
//        if (_listFollower.getCurrent()->_pFormation == this) {
//            _listFollower.getCurrent()->sayonara();
//            _listFollower.getCurrent()->_pFormation = nullptr;
//        } else {
//            throwCriticalException("_listFollowerに自身のformation管理ではないメンバーがいました！\n"
//                                       " this="<<NODE_INFO<<" \n"
//                                       " _listFollower.getCurrent()="<<(_listFollower.getCurrent()->getName())<<"("<<(_listFollower.getCurrent())<<") \n"
//                                       " _listFollower.getCurrent()->_pFormation="<<(_listFollower.getCurrent()->_pFormation->getName())<<"("<<(_listFollower.getCurrent()->_pFormation)<<") ");
//        }
//        _listFollower.remove();
//    }

}

DepositoryFormation::~DepositoryFormation() {

}
