#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafActor::GgafActor(const char* prm_name) :
    GgafElement<GgafActor> (prm_name) {
    TRACE("GgafActor::GgafActor("<<prm_name<<")");
    _class_name = "GgafActor";
    _pNext_TheSameDrawDepthLevel = NULL;
    _can_bump_flg = true;
    _pScene_Platform = NULL;
    _pGod = NULL;
}

GgafActor::~GgafActor() {
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

void GgafActor::setBumpable(bool prm_can_bump_flg) {
    TRACE("GgafActor::setBumpable() " << getName());
    _can_bump_flg = prm_can_bump_flg;
}

void GgafActor::setBumpableTree(bool prm_can_bump_flg) {
    TRACE("GgafActor::setBumpable() " << getName());
    _can_bump_flg = prm_can_bump_flg;
    if (_pSubFirst != NULL) {
        _pActor_tmp = _pSubFirst;
        while (true) {
            _pActor_tmp->setBumpable(prm_can_bump_flg);
            if (_pActor_tmp->_is_last_flg) {
                break;
            } else {
                _pActor_tmp = _pActor_tmp->_pNext;
            }
        }
    }
}

bool GgafActor::canBump() {
    if (isActive() && _can_bump_flg) {
        return true;
    } else {
        return false;
    }
}

void GgafActor::executeBumpChk_MeAnd(GgafActor* prm_pActor_Opponent) {
    if (prm_pActor_Opponent == this) {
        return;
    } else {
        if (_can_bump_flg && prm_pActor_Opponent->_can_bump_flg && _can_live_flg && prm_pActor_Opponent->_can_live_flg && _is_active_flg
                && prm_pActor_Opponent->_is_active_flg) {
            if (processBumpChkLogic(prm_pActor_Opponent)) { //自身のヒットチェック
                processOnHit(prm_pActor_Opponent); //自分のヒット時の振る舞い
                prm_pActor_Opponent->processOnHit(this); //相手のヒット時の振る舞い
            }
        }
    }
}

void GgafActor::executeBumpChk_WeAnd(GgafActor* prm_pActor_Opponent) {
    executeBumpChk_MeAnd(prm_pActor_Opponent);
    if (_pSubFirst != NULL) {
        _pActor_tmp3 = _pSubFirst;
        while (true) {
            _pActor_tmp3->executeBumpChk_WeAnd(prm_pActor_Opponent);
            if (_pActor_tmp3->_is_last_flg) {
                break;
            } else {
                _pActor_tmp3 = _pActor_tmp3->_pNext;
            }
        }
    }
}

void GgafActor::executeBumpChkRoundRobin(GgafActor* prm_pActor_Opponent) {
    executeBumpChk_WeAnd(prm_pActor_Opponent);
    if (prm_pActor_Opponent->_pSubFirst != NULL) {
        GgafActor* _pActor_tmpZ = prm_pActor_Opponent->_pSubFirst;
        while (true) {
            executeBumpChkRoundRobin(_pActor_tmpZ);
            if (_pActor_tmpZ->_is_last_flg) {
                break;
            } else {
                _pActor_tmpZ = _pActor_tmpZ->_pNext;
            }
        }
    }
}

bool GgafActor::executeBumpChk2_MeAnd(GgafActor* prm_pActor_Opponent) {
    if (prm_pActor_Opponent == this) {
        return true;
    } else {
        if (_can_bump_flg && prm_pActor_Opponent->_can_bump_flg && _can_live_flg && prm_pActor_Opponent->_can_live_flg && _is_active_flg
                && prm_pActor_Opponent->_is_active_flg) {
            if (processBumpChkLogic(prm_pActor_Opponent)) { //自身のヒットチェック
                processOnHit(prm_pActor_Opponent); //自分のヒット時の振る舞い
                prm_pActor_Opponent->processOnHit(this); //相手のヒット時の振る舞い
            }
        }
        return false;
    }
}

bool GgafActor::executeBumpChk2_WeAnd(GgafActor* prm_pActor_Opponent) {
    bool ret1 = executeBumpChk2_MeAnd(prm_pActor_Opponent);
    bool ret2;
    if (ret1) {
        return true;
    } else {
        if (_pSubFirst != NULL) {
            _pActor_tmp4 = _pSubFirst;
            while (true) {
                ret2 = _pActor_tmp4->executeBumpChk2_WeAnd(prm_pActor_Opponent);
                if (ret2) {
                    return true;
                } else {
                    if (_pActor_tmp4->_is_last_flg) {
                        break;
                    } else {
                        _pActor_tmp4 = _pActor_tmp4->_pNext;
                    }
                }
            }
        }
        return false;
    }
}

void GgafActor::executeBumpChkRoundRobin2(GgafActor* prm_pActor_Opponent) {
    executeBumpChk2_WeAnd(prm_pActor_Opponent);
    if (prm_pActor_Opponent->_pSubFirst != NULL) {
        GgafActor* _pActor_tmpZ2 = prm_pActor_Opponent->_pSubFirst;
        while (true) {
            executeBumpChkRoundRobin2(_pActor_tmpZ2);
            if (_pActor_tmpZ2->_is_last_flg) {
                break;
            } else {
                _pActor_tmpZ2 = _pActor_tmpZ2->_pNext;
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
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"["<<getName()<<"]@"<<_lifeframe<<","<<_can_bump_flg<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_a_few_frames_flg<<"("<<_frame_of_activation<<")");

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\t｜");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<_class_name<<"["<<getName()<<"]のnextがNULLにっています");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_("\t\t\t\t\t\t\t\t└─");
                break;
            }
        }
    }
}

void GgafActor::dump(string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"["<<getName()<<"]@"<<_lifeframe<<","<<_can_bump_flg<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_a_few_frames_flg<<"("<<_frame_of_activation<<")");
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump(prm_parent + "｜");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("【警告】"<<_class_name<<"["<<getName()<<"]のnextがNULLにっています");
                break;
            }
            if (pActor_tmp->_is_first_flg) {
                _TRACE_(prm_parent+"└─");
                break;
            }
        }
    }
}

