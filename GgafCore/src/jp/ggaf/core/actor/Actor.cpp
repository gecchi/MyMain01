#include "jp/ggaf/core/actor/Actor.h"

#include "jp/ggaf/core/God.h"
#include "jp/ggaf/core/actor/ex/Formation.h"
using namespace GgafCore;

#ifdef MY_DEBUG
unsigned int Actor::_num_actors = 0;
#endif
Actor::Actor(const char* prm_name) :
Element<Actor>(prm_name),
_pDependenceDepository(nullptr),
_pFormation(nullptr),
_can_hit_flg(false),
_can_hit_out_of_view(true)
{
    _class_name = "Actor";
    _obj_class = Obj_ggaf_Actor;
    _pStatus = NEW Status();
    getStatus()->set(STAT_DEFAULT_ACTOR_KIND, 0);
    _pProg = Element<Actor>::createProgress();
#ifdef MY_DEBUG
    Actor::_num_actors++;
#endif
    _TRACE_("new "<<NODE_INFO<<" _id="<<getId());
}

Actor::~Actor() {
    _pFormation = nullptr;
    GGAF_DELETE(_pStatus);
    if (pGOD->_is_loving_flg) {
        pGOD->pardon(this); //���g���]�񂾖���j��
    } else {
        //�A�v���I���������̂��߁A��������Ȃ��|������邽�ߍl���s�v
    }
#ifdef MY_DEBUG
    Actor::_num_actors--;
#endif
    _TRACE_("delete "<<NODE_INFO<<" _id="<<getId());
    //OutputDebugStringA("*");
}

void Actor::setHitAble(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg) {
    _can_hit_flg = prm_can_hit_flg;
    _can_hit_out_of_view = prm_can_hit_out_of_view_flg;
}

void Actor::setHitAbleTree(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg) {
    _can_hit_flg = prm_can_hit_flg;
    _can_hit_out_of_view = prm_can_hit_out_of_view_flg;
    Actor* pActor_tmp = _pChildFirst;
    while (pActor_tmp) {
        pActor_tmp->setHitAble(prm_can_hit_flg, prm_can_hit_out_of_view_flg);
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

void Actor::notifyDestroyedToFormation() {
    if (_pFormation) {
        _pFormation->destroyedFollower(this);
    }
}

void Actor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<DUMP_FLGS);

    Actor* pActor_tmp = _pChildFirst;
    while (pActor_tmp) {
        pActor_tmp->dump("\t\t\t\t\t\t\t\t�b");
        if (pActor_tmp->_pNext) {
            pActor_tmp = pActor_tmp->_pNext;
        } else {
            _TRACE_("�y�x���z"<<NODE_INFO<<" ��next��nullptr���Ă��܂�");
            break;
        }
        if (pActor_tmp->_is_first_flg) {
            _TRACE_("\t\t\t\t\t\t\t\t����");
            break;
        }
    }
}

void Actor::dump(std::string prm_parent) {
    _TRACE_(prm_parent <<NODE_INFO<<DUMP_FLGS);
    Actor* pActor_tmp = _pChildFirst;
    while (pActor_tmp) {
        pActor_tmp->dump(prm_parent + "�b");
        if (pActor_tmp->_pNext) {
            pActor_tmp = pActor_tmp->_pNext;
        } else {
            _TRACE_("�y�x���z"<<NODE_INFO<<"��next��nullptr���Ă��܂�");
            break;
        }
        if (pActor_tmp->_is_first_flg) {
            _TRACE_(prm_parent+"����");
            break;
        }
    }
}
