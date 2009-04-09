#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafActor::GgafActor(const char* prm_name) :
    GgafElement<GgafActor> (prm_name) {
    TRACE("GgafActor::GgafActor("<<prm_name<<")");
    _class_name = "GgafActor";
    _pNext_TheSameDrawDepthLevel = NULL;
    _canBumpFlg = true;
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
            if (_pActor_tmp->_isLastFlg) {
                break;
            } else {
                _pActor_tmp = _pActor_tmp->_pNext;
            }
        }
    }
}

void GgafActor::setBumpableAlone(bool prm_canBumpFlg) {
    TRACE("GgafActor::setBumpableAlone() " << getName());
    _canBumpFlg = prm_canBumpFlg;
}

void GgafActor::setBumpable(bool prm_canBumpFlg) {
    TRACE("GgafActor::setBumpable() " << getName());
    _canBumpFlg = prm_canBumpFlg;
    if (_pSubFirst != NULL) {
        _pActor_tmp = _pSubFirst;
        while (true) {
            _pActor_tmp->setBumpable(prm_canBumpFlg);
            if (_pActor_tmp->_isLastFlg) {
                break;
            } else {
                _pActor_tmp = _pActor_tmp->_pNext;
            }
        }
    }
}

bool GgafActor::canBump() {
    if (isActive() && _canBumpFlg) {
        return true;
    } else {
        return false;
    }
}

void GgafActor::executeBumpChk_MeAnd(GgafActor* prm_pActor_Opponent) {
    if (prm_pActor_Opponent == this) {
        return;
    } else {
        if (_canBumpFlg && prm_pActor_Opponent->_canBumpFlg && _canLiveFlg && prm_pActor_Opponent->_canLiveFlg && _isActiveFlg
                && prm_pActor_Opponent->_isActiveFlg) {
            if (processBumpChkLogic(prm_pActor_Opponent)) { //é©êgÇÃÉqÉbÉgÉ`ÉFÉbÉN
                processOnHit(prm_pActor_Opponent); //é©ï™ÇÃÉqÉbÉgéûÇÃêUÇÈïëÇ¢
                prm_pActor_Opponent->processOnHit(this); //ëäéËÇÃÉqÉbÉgéûÇÃêUÇÈïëÇ¢
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
            if (_pActor_tmp3->_isLastFlg) {
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
            if (_pActor_tmpZ->_isLastFlg) {
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
        if (_canBumpFlg && prm_pActor_Opponent->_canBumpFlg && _canLiveFlg && prm_pActor_Opponent->_canLiveFlg && _isActiveFlg
                && prm_pActor_Opponent->_isActiveFlg) {
            if (processBumpChkLogic(prm_pActor_Opponent)) { //é©êgÇÃÉqÉbÉgÉ`ÉFÉbÉN
                processOnHit(prm_pActor_Opponent); //é©ï™ÇÃÉqÉbÉgéûÇÃêUÇÈïëÇ¢
                prm_pActor_Opponent->processOnHit(this); //ëäéËÇÃÉqÉbÉgéûÇÃêUÇÈïëÇ¢
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
                    if (_pActor_tmp4->_isLastFlg) {
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
            if (_pActor_tmpZ2->_isLastFlg) {
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
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"["<<getName()<<"]@"<<_dwFrame<<","<<_canBumpFlg<<","<<_isActiveFlg<<_wasPausedFlg<<_wasHiddenFlg<<_canLiveFlg<<","<<_willActivateAtNextFrameFlg<<_willPauseAtNextFrameFlg<<_willBlindAtNextFrameFlg<<_willBeAliveAtNextFrameFlg<<","<<_willActivateAfterFrameFlg<<"("<<_dwGodFremeWhenActive<<")");

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\tÅb");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->_isFirstFlg) {
                _TRACE_("\t\t\t\t\t\t\t\tÑ§Ñü");
                break;
            }
        }
    }
}

void GgafActor::dump(string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"["<<getName()<<"]@"<<_dwFrame<<","<<_canBumpFlg<<","<<_isActiveFlg<<_wasPausedFlg<<_wasHiddenFlg<<_canLiveFlg<<","<<_willActivateAtNextFrameFlg<<_willPauseAtNextFrameFlg<<_willBlindAtNextFrameFlg<<_willBeAliveAtNextFrameFlg<<","<<_willActivateAfterFrameFlg<<"("<<_dwGodFremeWhenActive<<")");
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump(prm_parent + "Åb");
            if (pActor_tmp->_pNext != NULL) {
                pActor_tmp = pActor_tmp->_pNext;
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->_isFirstFlg) {
                _TRACE_(prm_parent+"Ñ§Ñü");
                break;
            }
        }
    }
}

