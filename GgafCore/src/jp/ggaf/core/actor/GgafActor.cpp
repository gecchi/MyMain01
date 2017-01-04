#include "jp/ggaf/core/actor/GgafActor.h"

#include "jp/ggaf/core/actor/ex/GgafFormation.h"
#include "jp/ggaf/core/GgafFactory.h"
using namespace GgafCore;

#ifdef MY_DEBUG
unsigned int GgafActor::_num_actors = 0;
#endif
GgafActor::GgafActor(const char* prm_name, GgafStatus* prm_pStat) :
GgafElement<GgafActor>(prm_name),
_pScene_platform(nullptr),
_pDependenceDepository(nullptr),
_pFormation(nullptr),
_can_hit_flg(false),
_can_hit_out_of_view(true),
_pStatus(prm_pStat)
{
    _class_name = "GgafActor";
    _obj_class = Obj_GgafActor;
    if (_pStatus == nullptr) {
        _pStatus = NEW GgafStatus(12, nullptr);
        getStatus()->set(0, 0);
    }
#ifdef MY_DEBUG
    GgafActor::_num_actors++;
#endif
    _TRACE_("new "<<NODE_INFO<<" _id="<<getId());
}

GgafActor::~GgafActor() {
    _pFormation = nullptr;
    GGAF_DELETE(_pStatus);
    if (GgafFactory::_is_working_flg) {
        GgafFactory::removeOrder(this); //é©êgÇ™íçï∂ÇµÇ¡ÇœÇ»ÇµÇÃè§ïiÇë|èú
    } else {
        //ÉAÉvÉäèIóπèàóùéûÇÃÇΩÇﬂÅAçHèÍÇ‡Ç‡ÇÍÇ»Ç≠ë|èúÇ≥ÇÍÇÈÇΩÇﬂçló∂ïsóv
    }
#ifdef MY_DEBUG
    GgafActor::_num_actors--;
#endif
    _TRACE_("delete "<<NODE_INFO<<" _id="<<getId());
    //OutputDebugStringA("*");
}

void GgafActor::setPlatformScene(GgafScene* prm_pScene_platform) {
    _pScene_platform = prm_pScene_platform;
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->setPlatformScene(prm_pScene_platform);
        if (pActor_tmp->_is_last_flg) {
            break;
        } else {
            pActor_tmp = pActor_tmp->_pNext;
        }
    }
}

void GgafActor::setHitAble(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg) {
    _can_hit_flg = prm_can_hit_flg;
    _can_hit_out_of_view = prm_can_hit_out_of_view_flg;
}

void GgafActor::setHitAble(bool prm_can_hit_flg) {
    _can_hit_flg = prm_can_hit_flg;
}

void GgafActor::setHitAbleTree(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg) {
    _can_hit_flg = prm_can_hit_flg;
    _can_hit_out_of_view = prm_can_hit_out_of_view_flg;
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->setHitAble(prm_can_hit_flg, prm_can_hit_out_of_view_flg);
        if (pActor_tmp->_is_last_flg) {
            break;
        } else {
            pActor_tmp = pActor_tmp->_pNext;
        }
    }
}

void GgafActor::setHitAbleTree(bool prm_can_hit_flg) {
    _can_hit_flg = prm_can_hit_flg;
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->setHitAble(prm_can_hit_flg);
        if (pActor_tmp->_is_last_flg) {
            break;
        } else {
            pActor_tmp = pActor_tmp->_pNext;
        }
    }
}

GgafScene* GgafActor::getPlatformScene() {
    if (_pScene_platform == nullptr) {
        if (getParent()) {
            _pScene_platform = getParent()->getPlatformScene();
        } else {
            _pScene_platform = nullptr;
        }
    }
    return _pScene_platform;
}

void GgafActor::sayonara(frame prm_offset_frames) {
    if (_pDependenceDepository) {
        inactivateDelay(prm_offset_frames);
    } else {
        end(prm_offset_frames);
    }
    GgafActor* pActor = _pSubFirst;
    while (pActor) {
        pActor->sayonara(prm_offset_frames);
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->_pNext;
        }
    }
}

GgafActor* GgafActor::extract() {
    GgafActor* pActor = GgafElement<GgafActor>::extract();
    pActor->setPlatformScene(nullptr); //èäëÆÉVÅ[ÉìÉäÉZÉbÉg
    return pActor;
}

void GgafActor::notifyDestroyedToFormation() {
    if (_pFormation) {
        _pFormation->destroyedFollower(this);
    }
}

void GgafActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<NODE_INFO<<DUMP_FLGS);

    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->dump("\t\t\t\t\t\t\t\tÅb");
        if (pActor_tmp->_pNext) {
            pActor_tmp = pActor_tmp->_pNext;
        } else {
            _TRACE_("ÅyåxçêÅz"<<NODE_INFO<<" ÇÃnextÇ™nullptrÇ¡ÇƒÇ¢Ç‹Ç∑");
            break;
        }
        if (pActor_tmp->_is_first_flg) {
            _TRACE_("\t\t\t\t\t\t\t\tÑ§Ñü");
            break;
        }
    }
}

void GgafActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent <<NODE_INFO<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    while (pActor_tmp) {
        pActor_tmp->dump(prm_parent + "Åb");
        if (pActor_tmp->_pNext) {
            pActor_tmp = pActor_tmp->_pNext;
        } else {
            _TRACE_("ÅyåxçêÅz"<<NODE_INFO<<"ÇÃnextÇ™nullptrÇ¡ÇƒÇ¢Ç‹Ç∑");
            break;
        }
        if (pActor_tmp->_is_first_flg) {
            _TRACE_(prm_parent+"Ñ§Ñü");
            break;
        }
    }
}

