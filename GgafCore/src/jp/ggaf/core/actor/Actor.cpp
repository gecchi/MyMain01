#include "jp/ggaf/core/actor/Actor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/core/util/Checker.h"
using namespace GgafCore;

#ifdef MY_DEBUG
unsigned int Actor::_num_actors = 0;
#endif
Actor::Actor(const char* prm_name) : Element<Actor>(prm_name),
_pDependenceDepository(nullptr),
_can_hit_flg(false),
_enable_out_of_view_hit_flg(true),
_pChecker(nullptr)
{
    _class_name = "Actor";
    _obj_class = Obj_ggaf_Actor;
    _pStatus = NEW Status();
#ifdef MY_DEBUG
    Actor::_num_actors++;
#endif
    _TRACE_("new "<<NODE_INFO<<" _id="<<getId());
}

Actor::~Actor() {
    GGAF_DELETE(_pStatus);
    GGAF_DELETE_NULLABLE(_pChecker);
    if (pCARETAKER->_is_loving_flg) {
        pCARETAKER->repent(this); //自身が望んだ命を破棄
    } else {
        //アプリ終了処理時のため、愛ももれなく掃除されるため考慮不要
    }
#ifdef MY_DEBUG
    Actor::_num_actors--;
#endif
    _TRACE_("delete "<<NODE_INFO<<" _id="<<getId());
    //OutputDebugStringA("*");
}

void Actor::setHitAbleTree(bool prm_can_hit_flg, bool prm_enable_out_of_view_hit_flg) {
    _can_hit_flg = prm_can_hit_flg;
    _enable_out_of_view_hit_flg = prm_enable_out_of_view_hit_flg;
    Actor* pActor_tmp = _pChildFirst;
    while (pActor_tmp) {
        pActor_tmp->setHitAble(prm_can_hit_flg, prm_enable_out_of_view_hit_flg);
        if (pActor_tmp->_is_last_flg) {
            break;
        } else {
            pActor_tmp = pActor_tmp->_pNext;
        }
    }
}

void Actor::setHitAbleTree(bool prm_can_hit_flg) {
    _can_hit_flg = prm_can_hit_flg;
    Actor* pActor_tmp = _pChildFirst;
    while (pActor_tmp) {
        pActor_tmp->setHitAble(prm_can_hit_flg);
        if (pActor_tmp->_is_last_flg) {
            break;
        } else {
            pActor_tmp = pActor_tmp->_pNext;
        }
    }
}

void Actor::sayonara(frame prm_offset_frames) {
    if (_pDependenceDepository) {
        inactivateDelay(prm_offset_frames);
    } else {
        end(prm_offset_frames);
    }
    Actor* pActor = _pChildFirst;
    while (pActor) {
        pActor->sayonara(prm_offset_frames);
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->_pNext;
        }
    }
}

Checker* Actor::createChecker(kind_t prm_kind) {
    return NEW Checker(this, prm_kind);
}

void Actor::appendChild(Actor* prm_pActor) {
    if (!_pChecker) {
        _pChecker = createChecker();
    }
    Element<Actor>::appendChild(prm_pActor);
}
kind_t Actor::getCheckerKind() {
    if (!_pChecker) {
        _pChecker = createChecker();
    }
    return _pChecker->_kind;
}
void Actor::setCheckerKind(kind_t prm_kind) {
    if (!_pChecker) {
        _pChecker = createChecker();
    }
    _pChecker->_kind = prm_kind;
}
//void Actor::setDefaultKind(kind_t prm_kind) {
//    getChecker()->_kind = prm_kind;
//    getStatus()->set(STAT_DEFAULT_ACTOR_KIND, prm_kind);
//}

void Actor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<DUMP_FLGS);

    Actor* pActor_tmp = _pChildFirst;
    while (pActor_tmp) {
        pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
        if (pActor_tmp->_pNext) {
            pActor_tmp = pActor_tmp->_pNext;
        } else {
            _TRACE_("【警告】"<<NODE_INFO<<" のnextがnullptrっています");
            break;
        }
        if (pActor_tmp->_is_first_flg) {
            _TRACE_("\t\t\t\t\t\t\t\t└─");
            break;
        }
    }
}

void Actor::dump(std::string prm_parent) {
    _TRACE_(prm_parent <<NODE_INFO<<DUMP_FLGS);
    Actor* pActor_tmp = _pChildFirst;
    while (pActor_tmp) {
        pActor_tmp->dump(prm_parent + "｜");
        if (pActor_tmp->_pNext) {
            pActor_tmp = pActor_tmp->_pNext;
        } else {
            _TRACE_("【警告】"<<NODE_INFO<<"のnextがnullptrっています");
            break;
        }
        if (pActor_tmp->_is_first_flg) {
            _TRACE_(prm_parent+"└─");
            break;
        }
    }
}

