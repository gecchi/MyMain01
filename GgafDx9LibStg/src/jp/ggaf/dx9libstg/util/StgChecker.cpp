#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

int StgChecker::_num_check = 0;

StgChecker::StgChecker(GgafDx9GeometricActor* prm_pActor) : GgafDx9Checker(prm_pActor) {
    _pHitAreaBoxs = NULL;
    _iStaminaPointOriginally = 1;//Œ³—ˆ‚Ì‘Ï‹v—Í
    _iScorePointOriginally = 0; //Œ³—ˆ‚Ì“¾“_
    _iStaminaPoint = 1; //‘Ï‹v—Í
    _iScorePoint = 0; //“¾“_
    _iAttackPoint = 0; //UŒ‚—Í
    _iDefensePoint = 0; //–hŒä—Í
}

void StgChecker::useHitAreaBoxNum(int n) {
    if (_pHitAreaBoxs == NULL) {
        _pHitAreaBoxs = NEW HitAreaBoxs(n);
    } else {
        throwGgafCriticalException("StgChecker::useHitAreaBoxNum HitAreaBoxs‚ÍŠù‚É new ‚³‚ê‚Ä‚¢‚Ü‚·B");
    }
}

void StgChecker::setHitAreaBox(int prm_index,
                               int x1,
                               int y1,
                               int z1,
                               int x2,
                               int y2,
                               int z2,
                               bool rotX,
                               bool rotY,
                               bool rotZ) {
    if (_pHitAreaBoxs == NULL) {
        throwGgafCriticalException("StgChecker::setHitAreaBox ‚Ü‚¸ useHitAreaBoxNum ‚ðŽÀs‚µ‚ÄA—v‘f”‚ðéŒ¾‚µ‚Ä‚­‚¾‚³‚¢B");
    } else {
        _pHitAreaBoxs->setBox(prm_index, x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);
    }
}

void StgChecker::behave() {
    if (_pActor == NULL || _pHitAreaBoxs == NULL) {
        return;
    }

    static int cx, cy, cz;
    static s_ang s_RX, s_RY, s_RZ;
    s_RX = _pActor->_RX / ANGLE_RATE;
    s_RY = _pActor->_RY / ANGLE_RATE;
    s_RZ = _pActor->_RZ / ANGLE_RATE;

    for (int i = 0; i < _pHitAreaBoxs->_iAreaNum; i++) {
        if (!_pHitAreaBoxs->_paBase[i].rotX && !_pHitAreaBoxs->_paBase[i].rotY && !_pHitAreaBoxs->_paBase[i].rotZ) {
            continue;
        }
        cx = _pHitAreaBoxs->_paBase[i].cx;
        cy = _pHitAreaBoxs->_paBase[i].cy;
        cz = _pHitAreaBoxs->_paBase[i].cz;

        if (_pHitAreaBoxs->_paBase[i].rotX) {
            _pHitAreaBoxs->_paHitArea[i].cy = (cy * GgafDx9Util::COS[s_RX]) - (cz * GgafDx9Util::SIN[s_RX]);
            _pHitAreaBoxs->_paHitArea[i].cz = (cy * GgafDx9Util::SIN[s_RX]) + (cz * GgafDx9Util::COS[s_RX]);
            cy = _pHitAreaBoxs->_paHitArea[i].cy;
            cz = _pHitAreaBoxs->_paHitArea[i].cz;
        }

        if (_pHitAreaBoxs->_paBase[i].rotY) {
            _pHitAreaBoxs->_paHitArea[i].cz = (cz * GgafDx9Util::COS[s_RY]) - (cx * GgafDx9Util::SIN[s_RY]);
            _pHitAreaBoxs->_paHitArea[i].cx = (cz * GgafDx9Util::SIN[s_RY]) + (cx * GgafDx9Util::COS[s_RY]);
            cz = _pHitAreaBoxs->_paHitArea[i].cz;
            cx = _pHitAreaBoxs->_paHitArea[i].cx;
        }

        if (_pHitAreaBoxs->_paBase[i].rotZ) {
            _pHitAreaBoxs->_paHitArea[i].cx = (cx * GgafDx9Util::COS[s_RZ]) - (cy * GgafDx9Util::SIN[s_RZ]);
            _pHitAreaBoxs->_paHitArea[i].cy = (cx * GgafDx9Util::SIN[s_RZ]) + (cy * GgafDx9Util::COS[s_RZ]);
            cx = _pHitAreaBoxs->_paHitArea[i].cx;
            cy = _pHitAreaBoxs->_paHitArea[i].cy;
        }

        _pHitAreaBoxs->_paHitArea[i].x1 = cx - _pHitAreaBoxs->_paBase[i].hdx;
        _pHitAreaBoxs->_paHitArea[i].y1 = cy - _pHitAreaBoxs->_paBase[i].hdy;
        _pHitAreaBoxs->_paHitArea[i].z1 = cz - _pHitAreaBoxs->_paBase[i].hdz;
        _pHitAreaBoxs->_paHitArea[i].x2 = cx + _pHitAreaBoxs->_paBase[i].hdx;
        _pHitAreaBoxs->_paHitArea[i].y2 = cy + _pHitAreaBoxs->_paBase[i].hdy;
        _pHitAreaBoxs->_paHitArea[i].z2 = cz + _pHitAreaBoxs->_paBase[i].hdz;

    }

}

bool StgChecker::isBump(GgafDx9Checker* prm_pOtherChecker) {

    static GgafDx9GeometricActor* pOtherActor;
    static HitAreaBoxs* pOtherHitAreaBoxs;

    pOtherActor = prm_pOtherChecker->getTargetActor();
    pOtherHitAreaBoxs = ((StgChecker*)prm_pOtherChecker)->getHitAreaBoxs();
    if (_pActor == NULL || pOtherActor == NULL || _pHitAreaBoxs == NULL || pOtherHitAreaBoxs == NULL ||
        _pActor->isOffscreen() > 0 || pOtherActor->isOffscreen() > 0 ||
        _pHitAreaBoxs->_paHitArea->active == false || pOtherHitAreaBoxs->_paHitArea->active == false) {
        return false;
    } else {

        //Ž©•ª‚Ì” ‚Æ‘ŠŽè‚Ì” 

        for (int i = 0; i < _pHitAreaBoxs->_iAreaNum; i++) {
            for (int j = 0; j < pOtherHitAreaBoxs->_iAreaNum; j++) {
                StgChecker::_num_check++;
                if (_pActor->_Z + _pHitAreaBoxs->_paHitArea[i].z2 >= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[j].z1) {
                    if (_pActor->_Z + _pHitAreaBoxs->_paHitArea[i].z1 <= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[j].z2) {
                        if (_pActor->_X + _pHitAreaBoxs->_paHitArea[i].x2 >= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[j].x1) {
                            if (_pActor->_X + _pHitAreaBoxs->_paHitArea[i].x1 <= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[j].x2) {
                                if (_pActor->_Y + _pHitAreaBoxs->_paHitArea[i].y2 >= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[j].y1) {
                                    if (_pActor->_Y + _pHitAreaBoxs->_paHitArea[i].y1 <= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[j].y2) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    return false;
}

StgChecker::~StgChecker() {
    TRACE("StgChecker::~StgChecker() _pActor="<<_pActor->getName());
    DELETE_POSSIBLE_NULL(_pHitAreaBoxs);
}
