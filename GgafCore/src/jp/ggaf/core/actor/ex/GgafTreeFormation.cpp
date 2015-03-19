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
    if (wasDeclaredEnd()) {
        //終了を待つのみ
        _TRACE_("＜警告＞ GgafTreeFormation::addSubLast("<<NODE_INFO_P(prm_pSub)<<") 既に死にゆく定めのFormationです。サブに追加することはおかしいのではないか？いいのか？。this="<<NODE_INFO);
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
        //そこで、団長の種別0だった場合、種別を無理やり更新する。
        GgafGroupHead* myGroupHead = getMyGroupHead(); //団長
        if (myGroupHead) {
            //既に所属してしまっている。（シーンに属している）
            if (myGroupHead->_kind == kind) {
                //だが、種別に整合性があるので問題なし。
            } else {
                //種別が変わっている。この団長の種別を無理やり変更できるか？
                if (myGroupHead->_kind == 0) {
                    //種別0だったので無理やり団長の種別を書き換えてしまおう。
                    _TRACE_("GgafTreeFormation::addFormationMember "<<NODE_INFO<<" は、所属済み団長の種別(＝自身の種別)"<<myGroupHead->_kind<<"と、追加メンバーの種別"<<kind<<"が異なります。"<<
                            "幸いにも、団長種別が 0 だったので、無理やり更新しました。旧団長種別="<<myGroupHead->_kind<<" → 新団長種別="<<kind<<"");
                    myGroupHead->setKind(kind);
                } else {
                    _TRACE_("GgafTreeFormation::addFormationMember "<<NODE_INFO<<" は、所属済み団長の種別(＝自身の種別)"<<myGroupHead->_kind<<"と、追加メンバーの種別"<<kind<<"が異なります。");
                    _TRACE_("所属済み団長配下の状態は以下です");
                    myGroupHead->dump();
                    throwGgafCriticalException(
                            "GgafTreeFormation::addFormationMember "<<NODE_INFO<<" は、所属済み団長の種別(＝自身の種別)"<<myGroupHead->_kind<<"と、追加メンバーの種別"<<kind<<"が異なります。");
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
    if (_was_all_sayonara || wasDeclaredEnd() || willInactivateAfter()) {
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
    if (wasDeclaredEnd() || willInactivateAfter()) {
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
