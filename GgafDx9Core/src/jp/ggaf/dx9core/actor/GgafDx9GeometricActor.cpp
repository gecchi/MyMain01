#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9GeometricActor::GgafDx9GeometricActor(const char* prm_name,
                                             GgafDx9Checker* prm_pChecker) : GgafDx9BaseActor(prm_name) {
    _class_name = "GgafDx9GeometricActor";
    _isTransformed = false;
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _x = _y = _z = 0.0f;

    _max_radius = 0;
    if (prm_pChecker) {
        _pChecker = prm_pChecker;
        _delete_pChecker = false;
    } else {
        _pChecker = NEW GgafDx9Checker(this);
        _delete_pChecker = true;
    }
    _pMover = NEW GgafDx9GeometryMover(this);

    _offscreenkind = -1;
}


void GgafDx9GeometricActor::processPreJudgement() {
    if (_isTransformed == false) {
        _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
        _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
        _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);

        _fDistance_plnTop    = GgafDx9Universe::_pCamera->_plnTop.a*_fX +
                               GgafDx9Universe::_pCamera->_plnTop.b*_fY +
                               GgafDx9Universe::_pCamera->_plnTop.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnTop.d;

        _fDistance_plnBottom = GgafDx9Universe::_pCamera->_plnBottom.a*_fX +
                               GgafDx9Universe::_pCamera->_plnBottom.b*_fY +
                               GgafDx9Universe::_pCamera->_plnBottom.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnBottom.d;

        _fDistance_plnLeft   = GgafDx9Universe::_pCamera->_plnLeft.a*_fX +
                               GgafDx9Universe::_pCamera->_plnLeft.b*_fY +
                               GgafDx9Universe::_pCamera->_plnLeft.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnLeft.d;

        _fDistance_plnRight  = GgafDx9Universe::_pCamera->_plnRight.a*_fX +
                               GgafDx9Universe::_pCamera->_plnRight.b*_fY +
                               GgafDx9Universe::_pCamera->_plnRight.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnRight.d;

        _fDistance_plnFront  = GgafDx9Universe::_pCamera->_plnFront.a*_fX +
                               GgafDx9Universe::_pCamera->_plnFront.b*_fY +
                               GgafDx9Universe::_pCamera->_plnFront.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnFront.d;

        _fDistance_plnBack   = GgafDx9Universe::_pCamera->_plnBack.a*_fX +
                               GgafDx9Universe::_pCamera->_plnBack.b*_fY +
                               GgafDx9Universe::_pCamera->_plnBack.c*_fZ +
                               GgafDx9Universe::_pCamera->_plnBack.d;
        _offscreenkind = -1;
    }
    _pChecker->updateHitArea();
}



bool GgafDx9GeometricActor::processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
    if (_pChecker == NULL) {
        return false;
    } else {
//        GgafDx9GeometricActor* pActor_Opponent = dynamic_cast<GgafDx9GeometricActor*> (prm_pActor_Opponent);
//        if (pActor_Opponent != NULL && pActor_Opponent->_pChecker != NULL) {
//            return _pChecker->isBump(pActor_Opponent->_pChecker);
//        } else {
//            _TRACE_("GgafDx9GeometricActor::processBumpChkLogic prm_pActor_Opponent("<<(prm_pActor_Opponent->getName())<<") is not GgafDx9GeometricActor")
//            return false;
//        }

        //ñ{óàÇÕÅ™ÇÃÇÊÇ§Ç…Ç∑ÇÈÇÃÇ™îƒópìIÇ©Ç¬à¿ëSÅBÇµÇ©ÇµÅAdynamic_castÇè»Ç´ÇΩÇ¢Ç™ÇΩÇﬂÇ…ÅAäÎåØÇ»Ç±Ç∆ÇÇµÇƒÇ¢Ç‹Ç∑ÅB
        //âΩÇ©Ç®Ç©ÇµÇ¢Ç∆Ç®Ç‡Ç¡ÇΩÇÁÇ±Ç±Ç™âˆÇµÇ¢Ç©Ç‡ÇµÇÍÇ»Ç¢ÅBêˆç›ìIÇ»ÉoÉOÇÃâ¬î\ê´Ç†ÇËÅB
        //_can_bump_flg ÇñYÇÍÇ∏Ç…falseÇ…Ç∑ÇÈÇ±Ç∆Ç…ÇÊÇ¡ÇƒÅAÇ±Ç±ÇÃà¯êîÇ…GgafDx9GeometricActorÇ…ÉLÉÉÉXÉgÇ≈Ç´Ç»Ç¢É|ÉCÉìÉ^ÇÕóàÇ»Ç¢ÅB
        //ñYÇÍÇΩÇÁÇ‡Ç§ÇµÇÁÇÒÅB
        return _pChecker->isBump(((GgafDx9GeometricActor*)prm_pActor_Opponent)->_pChecker);
    }
}


void GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //Worldïœä∑
    //ägëÂèkè¨ Å~ Xé≤âÒì] Å~ Zé≤âÒì] Å~ Yé≤âÒì] Å~ ïΩçsà⁄ìÆ ÇÃïœä∑çsóÒÇê›íË<BR>
    //Å¶XYZÇÃèáÇ≈Ç»Ç¢Ç±Ç∆Ç…íçà”
    // | sx*cosRZ*cosRY                           , sx*sinRZ       , sx*cosRZ*-sinRY                           , 0|
    // | (sy* cosRX*-sinRZ*cosRY + sy*sinRX*sinRY), sy*cosRX*cosRZ , (sy* cosRX*-sinRZ*-sinRY + sy*sinRX*cosRY), 0|
    // | (sz*-sinRX*-sinRZ*cosRY + sz*cosRX*sinRY), sz*-sinRX*cosRZ, (sz*-sinRX*-sinRZ*-sinRY + sz*cosRX*cosRY), 0|
    // | dx                                       , dy             , dz                                        , 1|
    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = sx * cosRZ *cosRY;
    out_matWorld._12 = sx * sinRZ;
    out_matWorld._13 = sx * cosRZ * -sinRY;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (sy * cosRX * -sinRZ *  cosRY) + (sy * sinRX * sinRY);
    out_matWorld._22 = sy * cosRX *  cosRZ;
    out_matWorld._23 = (sy * cosRX * -sinRZ * -sinRY) + (sy * sinRX * cosRY);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (sz * -sinRX * -sinRZ *  cosRY) + (sz * cosRX * sinRY);
    out_matWorld._32 = sz * -sinRX *  cosRZ;
    out_matWorld._33 = (sz * -sinRX * -sinRZ * -sinRY) + (sz * cosRX * cosRY);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
    /*
     //ëOÇÃÇ‚ÇËï˚
     float fRateScale = LEN_UNIT;
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
     D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
     D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}





void GgafDx9GeometricActor::getWorldMatrix_ScRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    //sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    //cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = sx*cosRZ*cosRY;
    out_matWorld._12 = sx*sinRZ;
    out_matWorld._13 = sx*cosRZ*-sinRY;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*-sinRZ*cosRY;
    out_matWorld._22 = sy*cosRZ;
    out_matWorld._23 = sy*-sinRZ*-sinRY;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*sinRY;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = sz*cosRY;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}





void GgafDx9GeometricActor::getWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //Worldïœä∑
    //íPà çsóÒ Å~ Xé≤âÒì] Å~ Zé≤âÒì] Å~ Yé≤âÒì] Å~ ägëÂèkè¨ Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    //Å¶XYZÇÃèáÇ≈Ç»Ç¢Ç±Ç∆Ç…íçà”
    // |                         cosRZ*cosRY*sx,          sinRZ*sy,                         cosRZ*-sinRY*sz,   0  |
    // | ( cosRX*-sinRZ*cosRY + sinRX*sinRY)*sx,    cosRX*cosRZ*sy, ( cosRX*-sinRZ*-sinRY + sinRX*cosRY)*sz,   0  |
    // | (-sinRX*-sinRZ*cosRY + cosRX*sinRY)*sx,   -sinRX*cosRZ*sy, (-sinRX*-sinRZ*-sinRY + cosRX*cosRY)*sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRZ * cosRY * sx;
    out_matWorld._12 = sinRZ * sy;
    out_matWorld._13 = cosRZ * -sinRY * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((cosRX * -sinRZ * cosRY) + (sinRX * sinRY)) * sx;
    out_matWorld._22 = cosRX * cosRZ * sy;
    out_matWorld._23 = ((cosRX * -sinRZ * -sinRY) + (sinRX * cosRY)) * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((-sinRX * -sinRZ * cosRY) + (cosRX * sinRY)) * sx;
    out_matWorld._32 = -sinRX * cosRZ * sy;
    out_matWorld._33 = ((-sinRX * -sinRZ * -sinRY) + (cosRX * cosRY)) * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9GeometricActor::getWorldMatrix_BillBoardXYZ_ScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = pCAM->_vMatrixView._11 * sx;
    out_matWorld._12 = pCAM->_vMatrixView._21 * sy;
    out_matWorld._13 = pCAM->_vMatrixView._31 * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = pCAM->_vMatrixView._12 * sx;
    out_matWorld._22 = pCAM->_vMatrixView._22 * sy;
    out_matWorld._23 = pCAM->_vMatrixView._32 * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCAM->_vMatrixView._13 * sx;
    out_matWorld._32 = pCAM->_vMatrixView._23 * sy;
    out_matWorld._33 = pCAM->_vMatrixView._33 * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9GeometricActor::getWorldMatrix_BillBoardX_RzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //Worldïœä∑
    //íPà çsóÒ Å~ Xé≤âÒì] Å~ Zé≤âÒì] Å~ Yé≤âÒì] Å~ ägëÂèkè¨ Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    //Å¶XYZÇÃèáÇ≈Ç»Ç¢Ç±Ç∆Ç…íçà”
    // |                         cosRZ*cosRY*sx,          sinRZ*sy,                         cosRZ*-sinRY*sz,   0  |
    // | ( cosRX*-sinRZ*cosRY + sinRX*sinRY)*sx,    cosRX*cosRZ*sy, ( cosRX*-sinRZ*-sinRY + sinRX*cosRY)*sz,   0  |
    // | (-sinRX*-sinRZ*cosRY + cosRX*sinRY)*sx,   -sinRX*cosRZ*sy, (-sinRX*-sinRZ*-sinRY + cosRX*cosRY)*sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;

    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = pCAM->_vMatrixView._11 * sx;
    out_matWorld._12 = sinRZ * sy;
    out_matWorld._13 = cosRZ * -sinRY * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = pCAM->_vMatrixView._12 * sx;
    out_matWorld._22 = cosRX * cosRZ * sy;
    out_matWorld._23 = ((cosRX * -sinRZ * -sinRY) + (sinRX * cosRY)) * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCAM->_vMatrixView._13 * sx;
    out_matWorld._32 = -sinRX * cosRZ * sy;
    out_matWorld._33 = ((-sinRX * -sinRZ * -sinRY) + (cosRX * cosRY)) * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDx9GeometricActor::getWorldMatrix_BillBoardX_RyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;

    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = pCAM->_vMatrixView._11*cosRY*cosRZ*sx;
    out_matWorld._12 = pCAM->_vMatrixView._11*cosRY*sinRZ*sy;
    out_matWorld._13 = pCAM->_vMatrixView._11*-sinRY*sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (pCAM->_vMatrixView._12*cosRY*cosRZ + -sinRZ)*sx;
    out_matWorld._22 = (pCAM->_vMatrixView._12*cosRY*sinRZ + cosRZ)*sy;
    out_matWorld._23 = pCAM->_vMatrixView._12*-sinRY*sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((pCAM->_vMatrixView._13*cosRY + sinRY)*cosRZ)*sx;
    out_matWorld._32 = ((pCAM->_vMatrixView._13*cosRY + sinRY)*sinRZ)*sy;
    out_matWorld._33 = ((pCAM->_vMatrixView._13*-sinRY + cosRY))*sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9GeometricActor::getWorldMatrix_BillBoardXYZ_RzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    static float  sinRZ, cosRZ;

    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = (pCAM->_vMatrixView._11*cosRZ + pCAM->_vMatrixView._21*-sinRZ)*sx;
    out_matWorld._12 = (pCAM->_vMatrixView._11*sinRZ + pCAM->_vMatrixView._21*cosRZ)*sy;
    out_matWorld._13 = pCAM->_vMatrixView._31*sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (pCAM->_vMatrixView._12*cosRZ + pCAM->_vMatrixView._22*-sinRZ)*sx;
    out_matWorld._22 = (pCAM->_vMatrixView._12*sinRZ + pCAM->_vMatrixView._22*cosRZ)*sy;
    out_matWorld._23 = pCAM->_vMatrixView._32*sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (pCAM->_vMatrixView._13*cosRZ + pCAM->_vMatrixView._32*-sinRZ)*sx;
    out_matWorld._32 = (pCAM->_vMatrixView._13*sinRZ + pCAM->_vMatrixView._32*cosRZ)*sy;
    out_matWorld._33 = pCAM->_vMatrixView._33*sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9GeometricActor::getWorldMatrix_RxRyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //Worldïœä∑
    //íPà çsóÒ Å~ Xé≤âÒì] Å~ Yé≤âÒì] Å~ Zé≤âÒì] Å~ ägëÂèkè¨ Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    //    |                           cosRY*cosRZ*sx,                        cosRY*sinRZ*sy  ,      -sinRY*sz,  0 |
    //    | ((sinRX*sinRY*cosRZ +  cosRX*-sinRZ)*sx), ((sinRX*sinRY*sinRZ +  cosRX*cosRZ)*sy), sinRX*cosRY*sz,  0 |
    //    | ((cosRX*sinRY*cosRZ + -sinRX*-sinRZ)*sx), ((cosRX*sinRY*sinRZ + -sinRX*cosRZ)*sy), cosRX*cosRY*sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;

    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRY*cosRZ*sx;
    out_matWorld._12 = cosRY*sinRZ*sy;
    out_matWorld._13 = -sinRY*sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((sinRX*sinRY*cosRZ) + (cosRX*-sinRZ))*sx;
    out_matWorld._22 = ((sinRX*sinRY*sinRZ) + (cosRX*cosRZ))*sy;
    out_matWorld._23 = sinRX*cosRY*sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((cosRX*sinRY*cosRZ) + (-sinRX*-sinRZ))*sx;
    out_matWorld._32 = ((cosRX*sinRY*sinRZ) + (-sinRX* cosRZ))*sy;
    out_matWorld._33 = cosRX*cosRY*sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9GeometricActor::getWorldMatrix_RxRzRxScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //Worldïœä∑
    //íPà çsóÒ Å~ Xé≤âÒì] Å~ Zé≤âÒì] Å~ Xé≤âÒì] Å~ ägëÂèkè¨ Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨.
    //Å¶Yé≤âÒì]Ç™Ç†ÇËÇ‹ÇπÇÒÅBRYÇ™ÇQâÒñ⁄ÇÃXé≤âÒì]Ç∆Ç»ÇÈ
    //|         cosRZ*sx,                          sinRZ*cosRY*sy ,                          sinRZ*sinRY*sz, 0 |
    //|  cosRX*-sinRZ*sx, (( cosRX*cosRZ*cosRY + sinRX*-sinRY)*sy), (( cosRX*cosRZ*sinRY + sinRX*cosRY)*sz), 0 |
    //| -sinRX*-sinRZ*sx, ((-sinRX*cosRZ*cosRY + cosRX*-sinRY)*sy), ((-sinRX*cosRZ*sinRY + cosRX*cosRY)*sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;

    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRZ * sx;
    out_matWorld._12 = sinRZ * cosRY * sy;
    out_matWorld._13 = sinRZ * sinRY * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = cosRX * -sinRZ * sx;
    out_matWorld._22 = (( cosRX * cosRZ * cosRY) + (sinRX * -sinRY)) * sy;
    out_matWorld._23 = (( cosRX * cosRZ * sinRY) + (sinRX *  cosRY)) * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = -sinRX * -sinRZ * sx;
    out_matWorld._32 = ((-sinRX * cosRZ * cosRY) + (cosRX * -sinRY)) * sy;
    out_matWorld._33 = ((-sinRX * cosRZ * sinRY) + (cosRX *  cosRY)) * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9GeometricActor::getWorldMatrix_RzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //Worldïœä∑
    //íPà çsóÒ Å~ Zé≤âÒì] Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy	 , dz , 1  |
    static s_ang s_RZ;
    s_RZ = prm_pActor->_RZ / ANGLE_RATE;

    out_matWorld._11 = GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (float)(-1.0f * GgafDx9Util::SIN[s_RZ]);
    out_matWorld._22 = GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = 1.0f;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9GeometricActor::getWorldMatrix_ScRzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //Worldïœä∑
    //íPà çsóÒ Å~ ägëÂèkè¨ Å~ Zé≤âÒì] Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    // |sx*cosZ , sx*sinZ , 0    , 0  |
    // |sy*-sinZ, sy*cosZ , 0    , 0  |
    // |0       , 0       , sz   , 0  |
    // |dx      , dy	  , dz   , 1  |
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static s_ang s_RZ;
    static float sx, sy, sz;

    s_RZ = prm_pActor->_RZ / ANGLE_RATE;
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = sx * GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = sx * GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy * -1.0f * GgafDx9Util::SIN[s_RZ];
    out_matWorld._22 = sy * GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9GeometricActor::getWorldMatrix_ScMvRxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0f * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    static float dx, dy, dz;

    sinRX = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRX = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRZ = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;
    dx = prm_pActor->_fX;
    dy = prm_pActor->_fY;
    dz = prm_pActor->_fZ;

    out_matWorld._11 = sx*cosRZ*cosRY;
    out_matWorld._12 = sx*sinRZ;
    out_matWorld._13 = sx*cosRZ*-sinRY;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*cosRX*-sinRZ*cosRY + sy*sinRX*sinRY;
    out_matWorld._22 = sy*cosRX*cosRZ;
    out_matWorld._23 = sy*cosRX*-sinRZ*-sinRY + sy*sinRX*cosRY;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*-sinRX*-sinRZ*cosRY + sz*cosRX*sinRY;
    out_matWorld._32 = sz*-sinRX*cosRZ;
    out_matWorld._33 = sz*-sinRX*-sinRZ*-sinRY + sz*cosRX*cosRY;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = (dx*cosRZ + (dy*cosRX + dz*-sinRX)*-sinRZ)*cosRY + ((dy*sinRX + dz*cosRX))*sinRY;
    out_matWorld._42 = (dx*sinRZ + (dy*cosRX + dz*-sinRX)*cosRZ);
    out_matWorld._43 = (dx*cosRZ + (dy*cosRX + dz*-sinRX)*-sinRZ)*-sinRY + ((dy*sinRX + dz*cosRX))*cosRY;
    out_matWorld._44 = 1.0f;

}




void GgafDx9GeometricActor::updateWorldMatrix_Mv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



int GgafDx9GeometricActor::isOffscreen() {
    //_TRACE_("name="<<getName()<<" _max_radius="<<_max_radius);
    if (_offscreenkind == -1) {
        if ( _fDistance_plnTop <= _max_radius) {
            if ( _fDistance_plnBottom <= _max_radius) {
                if ( _fDistance_plnLeft <= _max_radius) {
                    if ( _fDistance_plnRight <= _max_radius) {
                        if ( _fDistance_plnFront <= _max_radius) {
                            if ( _fDistance_plnBack <= _max_radius) {
                                //ViewportîÕàÕì‡
                                _offscreenkind = 0;
                            } else {
                                //âúïΩñ ÇÊÇËâúÇ≈îÕàÕäO
                                _offscreenkind = 6;
                            }
                        } else {
                            //éËëOïΩñ ÇÊÇËéËëOÇ≈îÕàÕäO
                            _offscreenkind = 5;
                        }
                    } else {
                        //âEïΩñ ÇÊÇËâEÇ≈îÕàÕäO
                        _offscreenkind = 4;
                    }
                } else {
                    //ç∂ïΩñ ÇÊÇËç∂Ç≈îÕàÕäO
                    _offscreenkind = 3;
                }
            } else {
                //â∫ïΩñ ÇÊÇËâ∫Ç≈îÕàÕäO
                _offscreenkind = 2;
            }
        } else {
            //è„ïΩñ ÇÊÇËè„Ç≈îÕàÕäO
            _offscreenkind = 1;
        }
        //return (pCAM->canView(this) > 0);
    }
    return _offscreenkind;
}

int GgafDx9GeometricActor::wasGone() {
    if (GgafDx9Universe::_X_goneLeft < _X) {
        if (_X < GgafDx9Universe::_X_goneRight) {
            if (GgafDx9Universe::_Y_goneBottom < _Y) {
                 if (_Y < GgafDx9Universe::_Y_goneTop) {
                     if (GgafDx9Universe::_Z_goneFront < _Z) {
                          if (_Z < GgafDx9Universe::_Z_goneBack) {
                              return false;
                          }
                     }
                 }
            }
        }
    }
    return true;
}



GgafDx9GeometricActor::~GgafDx9GeometricActor() {
    if (_delete_pChecker) {
        DELETE_IMPOSSIBLE_NULL(_pChecker);
    }
    DELETE_IMPOSSIBLE_NULL(_pMover);
}



void GgafDx9GeometricActor::dump() {
    _TRACE_("\t\t\t\t\t\t\t\t"<<_class_name<<"["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")@"<<_lifeframe<<","<<_can_bump_flg<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_a_few_frames_flg<<"("<<_frame_of_activation<<")");

    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump("\t\t\t\t\t\t\t\tÅb");
            if (pActor_tmp->getNext() != NULL) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_("\t\t\t\t\t\t\t\tÑ§Ñü");
                break;
            }
        }
    }
}

void GgafDx9GeometricActor::dump(string prm_parent) {
    _TRACE_(prm_parent << _class_name<<"["<<getName()<<"]("<<_X<<","<<_Y<<","<<_Z<<")@"<<_lifeframe<<","<<_can_bump_flg<<","<<_is_active_flg<<_was_paused_flg<<_can_live_flg<<","<<_is_active_flg_in_next_frame<<_was_paused_flg_in_next_frame<<_can_live_flg_in_next_frame<<","<<_will_activate_after_a_few_frames_flg<<"("<<_frame_of_activation<<")");
    GgafActor* pActor_tmp = _pSubFirst;
    if (_pSubFirst != NULL) {
        while (true) {
            pActor_tmp->dump(prm_parent + "Åb");
            if (pActor_tmp->getNext() != NULL) {
                pActor_tmp = pActor_tmp->getNext();
            } else {
                _TRACE_("ÅyåxçêÅz"<<_class_name<<"["<<getName()<<"]ÇÃnextÇ™NULLÇ…Ç¡ÇƒÇ¢Ç‹Ç∑");
                break;
            }
            if (pActor_tmp->isFirst()) {
                _TRACE_(prm_parent+"Ñ§Ñü");
                break;
            }
        }
    }
}



