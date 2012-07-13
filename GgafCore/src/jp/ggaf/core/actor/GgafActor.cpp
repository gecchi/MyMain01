#include "stdafx.h"
using namespace GgafCore;

GgafActor::GgafActor(const char* prm_name, GgafStatus* prm_pStat) :
    GgafElement<GgafActor> (prm_name) {
    TRACE("GgafActor::GgafActor("<<this<<") "<<prm_name);
    _class_name = "GgafActor";
    _obj_class = Obj_GgafActor;
    if (prm_pStat) {
        _pStatus = prm_pStat;
    } else {
        _pStatus = NEW GgafStatus(12);
        _pStatus->set(0, 0);
    }
    _pScene_Platform = NULL;
    _pGod = NULL;
    _can_hit_flg = false;
    _can_hit_out_of_view = true;
    _pDependenceDepository = NULL;
    _pFormation = NULL;
    _TRACE_("new "<<_class_name<<"("<<this<<")["<<prm_name<<"]");
}

GgafActor::~GgafActor() {
    _pFormation = NULL;
    DELETE_IMPOSSIBLE_NULL(_pStatus);
    _TRACE_("delete "<<_class_name<<"("<<this<<")["<<getName()<<"]");
    //OutputDebugStringA("*");
}

void GgafActor::setPlatformScene(GgafScene* prm_pScene_Platform) {
    _pScene_Platform = prm_pScene_Platform;
    GgafActor* pActor_tmp;
    if (_pSubFirst) {
        pActor_tmp = _pSubFirst;
        while (true) {
            pActor_tmp->setPlatformScene(prm_pScene_Platform);
            if (pActor_tmp->_is_last_flg) {
                break;
            } else {
                pActor_tmp = pActor_tmp->_pNext;
            }
        }
    }
}

void GgafActor::setHitAble(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg) {
    TRACE("GgafActor::setHitAble() " << getName());
    _can_hit_flg = prm_can_hit_flg;
    _can_hit_out_of_view = prm_can_hit_out_of_view_flg;
}
void GgafActor::setHitAble(bool prm_can_hit_flg) {
    TRACE("GgafActor::setHitAble() " << getName());
    _can_hit_flg = prm_can_hit_flg;
}

void GgafActor::setHitAbleTree(bool prm_can_hit_flg, bool prm_can_hit_out_of_view_flg) {
    TRACE("GgafActor::setHitAble() " << getName());
    _can_hit_flg = prm_can_hit_flg;
    _can_hit_out_of_view = prm_can_hit_out_of_view_flg;
    GgafActor* pActor_tmp;
    if (_pSubFirst) {
        pActor_tmp = _pSubFirst;
        while (true) {
            pActor_tmp->setHitAble(prm_can_hit_flg, prm_can_hit_out_of_view_flg);
            if (pActor_tmp->_is_last_flg) {
                break;
            } else {
                pActor_tmp = pActor_tmp->_pNext;
            }
        }
    }
}

void GgafActor::setHitAbleTree(bool prm_can_hit_flg) {
    TRACE("GgafActor::setHitAble() " << getName());
    _can_hit_flg = prm_can_hit_flg;
    GgafActor* pActor_tmp;
    if (_pSubFirst) {
        pActor_tmp = _pSubFirst;
        while (true) {
            pActor_tmp->setHitAble(prm_can_hit_flg);
            if (pActor_tmp->_is_last_flg) {
                break;
            } else {
                pActor_tmp = pActor_tmp->_pNext;
            }
        }
    }
}


GgafScene* GgafActor::getPlatformScene() {
    if (_pScene_Platform == NULL) {
        if (getParent()) {
            _pScene_Platform = getParent()->getPlatformScene();
        } else {
            _pScene_Platform = NULL;
        }
    }
    return _pScene_Platform;
}

void GgafActor::sayonara(frame prm_offset_frames) {
    if (_pDependenceDepository) {
        inactivateDelay(prm_offset_frames);
    } else {
        end(prm_offset_frames);
    }
    GgafActor* pActor;
    if (_pSubFirst) {
        pActor = _pSubFirst;
        while (true) {
            pActor->sayonara(prm_offset_frames);
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->_pNext;
            }
        }
    }
}

GgafActor* GgafActor::extract() {
    GgafActor* pActor = GgafElement<GgafActor>::extract();
    pActor->setPlatformScene(NULL); //èäëÆÉVÅ[ÉìÉäÉZÉbÉg
    return pActor;
}

void GgafActor::notifyDestroyedToFormation() {
    if (_pFormation) {
        _pFormation->destroyedFollower(this);
    }
}

GgafFormation* GgafActor::getFormation() {
    return _pFormation;
}

void GgafActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]"<<DUMP_FLGS);

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\tÅb");
            if (pActor_tmp->_pNext) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"("<<this<<")["<<getName()<<"]ÇÃnextÇ™NULLÇ¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_("\t\t\t\t\t\t\t\tÑ§Ñü");
                break;
            }
        }
    }
}

void GgafActor::dump(std::string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]"<<DUMP_FLGS);
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst) {
        while (true) {
            pActor_tmp->dump(prm_parent + "Åb");
            if (pActor_tmp->_pNext) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"("<<this<<")["<<getName()<<"]ÇÃnextÇ™NULLÇ¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_(prm_parent+"Ñ§Ñü");
                break;
            }
        }
    }
}

