#include "jp/ggaf/core/actor/ex/TreeFormation.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

TreeFormation::TreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        Formation(prm_name, prm_offset_frames_end)
{
    _class_name = "TreeFormation";
    _pIte = nullptr;
    _can_summon = true;
    _is_append_member_experienced = false;
}

void TreeFormation::appendFormationMember(Actor* prm_pChild) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd()) {
        //終了を待つのみ
        _TRACE_("【警告】 TreeFormation::appendChild("<<NODE_INFO_P(prm_pChild)<<") 既に死にゆく定めのFormationです。子に追加することはおかしいのではないか？いいのか？。this="<<NODE_INFO);
    }
#endif
    _num_formation_member++;
//    if (_pChildFirst == nullptr) {
//        //団長に種別を正しく伝えるために、初回追加の種別を、自身の種別に上書（TreeFormation）きする
//        //kind_t kind = prm_pChild->getCheckerKind();
//        //getStatus()->set(STAT_DEFAULT_ACTOR_KIND, kind);
//        setDefaultKind(prm_pChild->getCheckerKind());
//    } else {
//#ifdef MY_DEBUG
//        if (getCheckerKind() != prm_pChild->getCheckerKind()) {
//            throwCriticalException("異なる種別のアクターを登録しようとしています。 \n"
//                                       "想定="<<getCheckerKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
//                                       "引数="<<prm_pChild->getCheckerKind()<<"["<<prm_pChild->getName()<<"]");
//        }
//#endif
//    }
    prm_pChild->_pFormation = this; //メンバーへフォーメーションを設定
    Formation::appendChild(prm_pChild);
    prm_pChild->inactivate(); //フォーメーションなのでsummonまで非活動。
    _is_append_member_experienced = true;
}

void TreeFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
    } else {
        if (getChildFirst() == nullptr) {  //配下がない場合、フォーメーションはなかったことになり、自身を終了かな？
            if (_is_append_member_experienced) {
                onSayonaraAll(); //コールバック
                sayonara(_offset_frames_end);
                _was_all_sayonara = true;
            } else {
                //だがしかし、まだ一回もappendFormationMember()を経験していないので終了しない。
                //TreeFormationとしての役割を果たすまでは死ねない。
            }
        }
    }
}

void TreeFormation::onEnd() {
    Formation::onEnd();
}

Actor* TreeFormation::summonMember(int prm_formation_child_num) {
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //終了を待つのみ
        return nullptr;
    }
    if (prm_formation_child_num > 0) {


        if (_can_summon) {
            if (_pIte) {
                //初回以降は next
                _pIte = _pIte->getNext();
            } else {
                //初回は子先頭
                _pIte = getChildFirst();
                if (!_pIte) {
                    //メンバーが追加されてない
                    _TRACE_("【警告】 TreeFormation::summonMember() メンバーが追加されてません。おかしいのでは？。this="<<NODE_INFO);
                    _can_summon = false; //次回から summonMember() 不可
                    _num_formation_member = 0;
                    return nullptr;
                }
            }

            _num_summon++;
            _pIte->activate();

            if (_pIte->getNext() == getChildFirst()) {
                //最後の１つ
                _can_summon = false; //次回から summonMember() 不可
                _num_formation_member = _num_summon; //destroyedFollower 編隊全滅判定の為再設定
            }
            if (prm_formation_child_num <= _num_summon) {
                //上限数に達した
                _can_summon = false; //次回から summonMember() 不可
                _num_formation_member = _num_summon; //destroyedFollower 編隊全滅判定の為再設定
            }

            return _pIte;
        } else {
            return nullptr;
        }
    } else {
        _can_summon = false; //次回から summonMember() 不可
        _num_formation_member = _num_summon; //destroyedFollower 編隊全滅判定の為再設定
        return nullptr;
    }
}

TreeFormation::~TreeFormation() {

}
