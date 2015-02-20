#include "jp/ggaf/core/actor/ex/GgafTreeFormation.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafTreeFormation::GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafFormation(prm_name, prm_offset_frames_end)
{
    _class_name = "GgafTreeFormation";
    _pIte = nullptr;
    _can_call_up = true;
    _is_addmember_experienced = false;
}

void GgafTreeFormation::addFormationMember(GgafActor* prm_pSub) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        throwGgafCriticalException("GgafTreeFormation::addSubLast("<<prm_pSub->getName()<<") 既に死にゆく定めのFormationです。サブに追加することはおかしいでしょう。this="<<getName());
    }
#endif
    _num_formation_member++;
    if (_pSubFirst == nullptr) {
        //団長に種別を正しく伝えるために、初回追加の種別を、自身の種別に上書（GgafTreeFormation）きする
        actorkind kind = prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND);
        getStatus()->set(STAT_DEFAULT_ACTOR_KIND, kind);
        //メンバー無しの GgafTreeFormation を、addSubGroup した後に addFormationMember を行った場合、
        //まずメンバー無しの GgafTreeFormation を、addSubGroup した直後は、種別=0なので、作成された団長の種別も0で作成されてしまう。
        //その後にaddFormationMemberを行っても、種別0に属してしまうという問題が有る。
        //そこで、自身（GgafTreeFormation）が既に団長に属している場合。種別が異なれば、新たな団長の配下に所属し直す。
        GgafGroupHead* myGroupHead = getMyGroupHead(); //団長
        if (myGroupHead) {
            //既に所属してしまっている。（シーンに属している）
            if (myGroupHead->_kind != kind) {
                //種別が変わったので、この団長の配下にはもういられない！
                GgafActor* pGroupHeadParent = myGroupHead->getParent();
                if (pGroupHeadParent->instanceOf(Obj_GgafMainActor)) {
                    this->extract();
                    GgafMainActor* pGroupHeadParentMainActor = (GgafMainActor*)pGroupHeadParent;
                    pGroupHeadParentMainActor->addSubGroup(this);
                    _TRACE_("GgafTreeFormation::addFormationMember "<<getName()<<"("<<this<<") は、所属済み団長の種別(＝自身の種別)"<<myGroupHead->_kind<<"と、追加メンバーの種別"<<kind<<"が異なるので、"<<
                            "団長をすげ替えました。旧団長="<<myGroupHead->getName()<<"("<<myGroupHead<<") → 新団長="<<getMyGroupHead()->getName()<<"("<<getMyGroupHead()<<")。（ちなみに親はGgafMainActorでした。)");
                } else if (pGroupHeadParent->instanceOf(Obj_GgafSceneDirector)) {
                    this->extract();
                    GgafSceneDirector* pMySceneDirector = (GgafSceneDirector*)pGroupHeadParent;
                    pMySceneDirector->addSubGroup(this);
                    _TRACE_("GgafTreeFormation::addFormationMember "<<getName()<<"("<<this<<") は、所属済み団長の種別(＝自身の種別)"<<myGroupHead->_kind<<"と、追加メンバーの種別"<<kind<<"が異なるので、"<<
                            "団長をすげ替えました。旧団長="<<myGroupHead->getName()<<"("<<myGroupHead<<") → 新団長="<<getMyGroupHead()->getName()<<"("<<getMyGroupHead()<<")。（ちなみに親はGgafSceneDirectorでした。)");
                } else {
                    throwGgafCriticalException(
                            "GgafTreeFormation::addFormationMember "<<getName()<<"("<<this<<") は、所属済み団長の種別(＝自身の種別)"<<myGroupHead->_kind<<"と、追加メンバーの種別"<<kind<<"が異なるので、"<<
                            "団長の変更を試みましたが、団長の親が GgafMainActor でも GgafSceneDirector でも無いので、諦めました。");
                }
            }
        } else {
            //団長がいない＝シーンには未所属なので、
            //シーンに所属時に自身の種別で団長が作成されるのでよし。
        }
    } else {
#ifdef MY_DEBUG
        if (getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND) != prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)) {
            throwGgafCriticalException("GgafTreeFormation::addSubLast 異なる種別のアクターを登録しようとしています。 \n"<<
                                       "想定="<<getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"[_pSubFirst="<<_pSubFirst->getName()<<"] \n"<<
                                       "引数="<<prm_pSub->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND)<<"["<<prm_pSub->getName()<<"]");
        }
#endif
    }
    prm_pSub->_pFormation = this; //メンバーへフォーメーションを設定
    GgafFormation::addSubLast(prm_pSub);
    prm_pSub->inactivate(); //フォーメーションなのでcallUpまで非活動。
    _is_addmember_experienced = true;
}

void GgafTreeFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
    } else {
        if (getSubFirst() == nullptr) {  //配下がない場合、フォーメーションはなかったことになり、自身を終了かな？
            if (_is_addmember_experienced) {
                onSayonaraAll(); //コールバック
                sayonara(_offset_frames_end);
                _was_all_sayonara = true;
            } else {
                //だがしかし、まだ一回もaddFormationMember()を経験していないので終了しない。
                //TreeFormationとしての役割を果たすまでは死ねない。
            }
        }
    }
}

void GgafTreeFormation::onEnd() {
    GgafFormation::onEnd();
}

GgafActor* GgafTreeFormation::callUpMember() {
    if (wasDeclaredEnd() || _will_inactivate_after_flg) {
        //終了を待つのみ
        return nullptr;
    }
    if (_can_call_up) {
        if (_pIte) {
            _pIte = _pIte->getNext();
            if (_pIte == getSubFirst()) { //１周した
                _can_call_up = false;
                return nullptr;
            }
        } else {
            _pIte = getSubFirst(); //初回はサブ先頭
        }
        _pIte->activate();
        if (_pIte->getNext() == getSubFirst()) {
            //最後の１つ
            _can_call_up = false;
        }
        return _pIte;
    } else {
        return nullptr;
    }
}

GgafTreeFormation::~GgafTreeFormation() {

}
