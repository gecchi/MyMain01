#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafActor::GgafActor(const char* prm_name) :
    GgafElement<GgafActor> (prm_name) {
    TRACE("GgafActor::GgafActor("<<this<<") "<<prm_name);
    _class_name = "GgafActor";
    _pStatus = NEW GgafStatus(10);
    _pScene_Platform = NULL;
    _pGod = NULL;
    setHitAble(false);
    _use_octree = false;
    _actor_class = 0;
    _pDependenceDispcher = NULL;
#ifdef MY_DEBUG
    _TRACE_("new "<<_class_name<<"("<<this<<")["<<prm_name<<"]");
#else

#endif

}

GgafActor::~GgafActor() {
    DELETE_IMPOSSIBLE_NULL(_pStatus);
#ifdef MY_DEBUG
    _TRACE_("delete "<<_class_name<<"("<<this<<")["<<getName()<<"]");
#else
    OutputDebugStringA("*\n");
#endif
}

void GgafActor::setScenePlatform(GgafScene* prm_pScene_Platform) {
    _pScene_Platform = prm_pScene_Platform;
    if (_pSubFirst != NULL) {
        _pActor_tmp = _pSubFirst;
        while (true) {
            _pActor_tmp->setScenePlatform(prm_pScene_Platform);
            if (_pActor_tmp->_is_last_flg) {
                break;
            } else {
                _pActor_tmp = _pActor_tmp->_pNext;
            }
        }
    }
}

void GgafActor::setHitAble(bool prm_can_hit_flg) {
    TRACE("GgafActor::setHitAble() " << getName());
    _can_hit_flg = prm_can_hit_flg;
}

void GgafActor::setHitAbleTree(bool prm_can_hit_flg) {
    TRACE("GgafActor::setHitAble() " << getName());
    _can_hit_flg = prm_can_hit_flg;
    if (_pSubFirst != NULL) {
        _pActor_tmp = _pSubFirst;
        while (true) {
            _pActor_tmp->setHitAble(prm_can_hit_flg);
            if (_pActor_tmp->_is_last_flg) {
                break;
            } else {
                _pActor_tmp = _pActor_tmp->_pNext;
            }
        }
    }
}




GgafScene* GgafActor::getPlatformScene() {
    if (_pScene_Platform == NULL) {
        _pScene_Platform = getParent()->getPlatformScene();
    }
    return _pScene_Platform;
}

void GgafActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving<<
                                                                               ","<<
                                                                               _can_hit_flg<<
                                                                               ","<<
                                                                               _is_active_flg<<
                                                                               _was_paused_flg<<
                                                                               _can_live_flg<<
                                                                               ","<<
                                                                               _is_active_flg_in_next_frame<<
                                                                               _was_paused_flg_in_next_frame<<
                                                                               _can_live_flg_in_next_frame<<
                                                                               ","<<
                                                                               _will_activate_after_flg<<
                                                                               "("<<_frame_of_life_when_activation<<")");

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\tÅb");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"("<<this<<")["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_("\t\t\t\t\t\t\t\tÑ§Ñü");
                break;
            }
        }
    }
}

void GgafActor::dump(string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"("<<this<<")["<<getName()<<"]@"<<_frame_of_behaving<<
                                                                         ","<<
                                                                         _can_hit_flg<<
                                                                         ","<<
                                                                         _is_active_flg<<
                                                                         _was_paused_flg<<
                                                                         _can_live_flg<<
                                                                         ","<<
                                                                         _is_active_flg_in_next_frame<<
                                                                         _was_paused_flg_in_next_frame<<
                                                                         _can_live_flg_in_next_frame<<","<<
                                                                         _will_activate_after_flg<<
                                                                         "("<<_frame_of_life_when_activation<<")");
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump(prm_parent + "Åb");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"("<<this<<")["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_(prm_parent+"Ñ§Ñü");
                break;
            }
        }
    }
}

