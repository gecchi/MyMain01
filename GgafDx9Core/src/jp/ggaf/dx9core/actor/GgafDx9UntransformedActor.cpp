#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9UntransformedActor::GgafDx9UntransformedActor(const char* prm_name,
                                                     GgafDx9GeometryMover* prm_pGeoMover,
                                                     GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9BaseActor(prm_name),
_X_OffScreenLeft((int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2)),
_X_OffScreenRight((int)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2)),
_Y_OffScreenTop((int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2)),
_Y_OffScreenBottom((int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2))
{
    _class_name = "GgafDx9UntransformedActor";
    _X = _Y = _Z = 0;
    _RX = _RY = _RZ = 0;
    _SX = _SY = _SZ = LEN_UNIT;
    _pGeoMover = prm_pGeoMover;
    _pGeoChecker = prm_pGeoChecker;
    _fAlpha = 1.0f;
}

bool GgafDx9UntransformedActor::processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
    GgafDx9UntransformedActor* pActor_Opponent = dynamic_cast<GgafDx9UntransformedActor*> (prm_pActor_Opponent);
    if (pActor_Opponent != NULL) {
        return _pGeoChecker->isBump(pActor_Opponent->_pGeoChecker);
    } else {
        return false;
    }
}

void GgafDx9UntransformedActor::processDrawPrior() {
    //TODO:óvåüèÿ
    if (_is_active_flg && !_was_hidden_flg && _can_live_flg) {
        if (getAlpha() < 1.0) {
            //ìßñæÇÃèÍçáÇÕÅAZé≤ílÇ≈âìÇ≠Ç©ÇÁï`âÊÇ∑ÇÈÇÊÇ§Ç…ê›íËÅB
            //_Z Ç™ ÉJÉÅÉâà íu Å` ÉJÉÅÉâ+2000,000 ÇÃä‘Ç≈Ç†ÇÍÇŒíiäKÉåÉìÉ_ÉäÉìÉOÇÇ∑ÇÈÇ±Ç∆Ç∆Ç∑ÇÈÅB
            //ëeÇ≥ÇÕ 2000,000/MAX_DRAW_DEPTH_LEVELÅBÅ©Ç±ÇÃîÕàÕÇÃZÇÕìØàÍê[ìxÇ∆Ç»ÇÈÅB
            //TODO: ÉJÉÅÉâÇ™ÇÆÇËÇÆÇËìÆÇ≠Ç∆îgèÛÇ∑ÇÈÅBê≥ÇµÇ≠ÇÕÉJÉÅÉâç¿ïWÇ©ÇÁÇÃãóó£Ç≈É\Å[ÉgÇ∑Ç◊Ç´ÅBÅEÅEÅEÇªÇÃì‡Ç‚ÇÎÇ§ÅB
            GgafDx9World::setDrawDepthLevel(
              (_Z-(GgafDx9God::_pVecCamFromPoint->z*LEN_UNIT*PX_UNIT)) / (2000000/MAX_DRAW_DEPTH_LEVEL),
              this
            );
        } else {
            //ïsìßñæÇÃèÍçáÇÕèâÇﬂÇ…ï`âÊÇ∑ÇÈÇÊÇ§Ç…ê›íËÅB
            //ÉåÉìÉ_ÉäÉìÉOéûç≈âìÇ©ÇÁï`âÊÇ∑ÇÈÇÃÇ≈ÅAê[ìxÉåÉxÉãÇÕMAX
            GgafDx9World::setDrawDepthMaxLevel(this);
        }
    }
}
void GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //WORLDïœä∑
    //íPà çsóÒ Å~ Xé≤âÒì] Å~ Zé≤âÒì] Å~ Yé≤âÒì] Å~ ägëÂèkè¨ Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    //Å¶XYZÇÃèáÇ≈Ç»Ç¢Ç±Ç∆Ç…íçà”
    // |                         cosRZ*cosRY*sx,          sinRZ*sy,                         cosRZ*-sinRY*sz,   0  |
    // | ( cosRX*-sinRZ*cosRY + sinRX*sinRY)*sx,    cosRX*cosRZ*sy, ( cosRX*-sinRZ*-sinRY + sinRX*cosRY)*sz,   0  |
    // | (-sinRX*-sinRZ*cosRY + cosRX*sinRY)*sx,   -sinRX*cosRZ*sy, (-sinRX*-sinRZ*-sinRY + cosRX*cosRY)*sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
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

    out_matWorld._41 = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    out_matWorld._42 = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    out_matWorld._43 = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);
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

void GgafDx9UntransformedActor::getWorldTransformBillBoardScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
    static float sx, sy, sz;
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = GgafDx9God::_vMatrixView._11 * sx;
    out_matWorld._12 = GgafDx9God::_vMatrixView._21 * sy;
    out_matWorld._13 = GgafDx9God::_vMatrixView._31 * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = GgafDx9God::_vMatrixView._12 * sx;
    out_matWorld._22 = GgafDx9God::_vMatrixView._22 * sy;
    out_matWorld._23 = GgafDx9God::_vMatrixView._32 * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = GgafDx9God::_vMatrixView._13 * sx;
    out_matWorld._32 = GgafDx9God::_vMatrixView._23 * sy;
    out_matWorld._33 = GgafDx9God::_vMatrixView._33 * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    out_matWorld._42 = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    out_matWorld._43 = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);
    out_matWorld._44 = 1.0f;
}

void GgafDx9UntransformedActor::getWorldTransformRxRyRzScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //WORLDïœä∑
    //íPà çsóÒ Å~ Xé≤âÒì] Å~ Yé≤âÒì] Å~ Zé≤âÒì] Å~ ägëÂèkè¨ Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    //    |                           cosRY*cosRZ*sx,                        cosRY*sinRZ*sy  ,      -sinRY*sz,  0 |
    //    | ((sinRX*sinRY*cosRZ +  cosRX*-sinRZ)*sx), ((sinRX*sinRY*sinRZ +  cosRX*cosRZ)*sy), sinRX*cosRY*sz,  0 |
    //    | ((cosRX*sinRY*cosRZ + -sinRX*-sinRZ)*sx), ((cosRX*sinRY*sinRZ + -sinRX*cosRZ)*sy), cosRX*cosRY*sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
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

    out_matWorld._41 = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    out_matWorld._42 = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    out_matWorld._43 = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);
    out_matWorld._44 = 1.0f;
}






void GgafDx9UntransformedActor::getWorldTransformRxRzRxScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //WORLDïœä∑
    //íPà çsóÒ Å~ Xé≤âÒì] Å~ Zé≤âÒì] Å~ Xé≤âÒì] Å~ ägëÂèkè¨ Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨.
    //Å¶Yé≤âÒì]Ç™Ç†ÇËÇ‹ÇπÇÒÅBRYÇ™ÇQâÒñ⁄ÇÃXé≤âÒì]Ç∆Ç»ÇÈ
    //|         cosRZ*sx,                          sinRZ*cosRY*sy ,                          sinRZ*sinRY*sz, 0 |
    //|  cosRX*-sinRZ*sx, (( cosRX*cosRZ*cosRY + sinRX*-sinRY)*sy), (( cosRX*cosRZ*sinRY + sinRX*cosRY)*sz), 0 |
    //| -sinRX*-sinRZ*sx, ((-sinRX*cosRZ*cosRY + cosRX*-sinRY)*sy), ((-sinRX*cosRZ*sinRY + cosRX*cosRY)*sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    static float sinRX, cosRX, sinRY, cosRY, sinRZ, cosRZ;
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
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

    out_matWorld._41 = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    out_matWorld._42 = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    out_matWorld._43 = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);
    out_matWorld._44 = 1.0f;
}





void GgafDx9UntransformedActor::getWorldTransformRzMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //WORLDïœä∑
    //íPà çsóÒ Å~ Zé≤âÒì] Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy	 , dz , 1  |
    static s_ang s_RZ;
    s_RZ = prm_pActor->_RZ / ANGLE_RATE;

    out_matWorld._11 = GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0;
    out_matWorld._14 = 0.0;

    out_matWorld._21 = (float)(-1.0 * GgafDx9Util::SIN[s_RZ]);
    out_matWorld._22 = GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0;
    out_matWorld._24 = 0.0;

    out_matWorld._31 = 0.0;
    out_matWorld._32 = 0.0;
    out_matWorld._33 = 1.0;
    out_matWorld._34 = 0.0;

    out_matWorld._41 = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    out_matWorld._42 = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    out_matWorld._43 = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);
    out_matWorld._44 = 1;
}

void GgafDx9UntransformedActor::getWorldTransformScRzMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {

    //WORLDïœä∑
    //íPà çsóÒ Å~ ägëÂèkè¨ Å~ Zé≤âÒì] Å~ ïΩçsà⁄ìÆÅ@ÇÃïœä∑çsóÒÇçÏê¨
    // |sx*cosZ , sx*sinZ , 0    , 0  |
    // |sy*-sinZ, sy*cosZ , 0    , 0  |
    // |0       , 0       , sz   , 0  |
    // |dx      , dy	  , dz   , 1  |
    static float fRateScale = 1.0 * LEN_UNIT * PX_UNIT;
    static s_ang s_RZ;
    static float sx, sy, sz;

    s_RZ = prm_pActor->_RZ / ANGLE_RATE;
    sx = prm_pActor->_SX / fRateScale;
    sy = prm_pActor->_SY / fRateScale;
    sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = sx * GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = sx * GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0;
    out_matWorld._14 = 0.0;

    out_matWorld._21 = sy * -1.0 * GgafDx9Util::SIN[s_RZ];
    out_matWorld._22 = sy * GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0;
    out_matWorld._24 = 0.0;

    out_matWorld._31 = 0.0;
    out_matWorld._32 = 0.0;
    out_matWorld._33 = sz;
    out_matWorld._34 = 0.0;

    out_matWorld._41 = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    out_matWorld._42 = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    out_matWorld._43 = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);
    out_matWorld._44 = 1.0;
}


void GgafDx9UntransformedActor::updateWorldTransformMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = (float)(1.0 * prm_pActor->_X / LEN_UNIT / PX_UNIT);
    out_matWorld._42 = (float)(1.0 * prm_pActor->_Y / LEN_UNIT / PX_UNIT);
    out_matWorld._43 = (float)(1.0 * prm_pActor->_Z / LEN_UNIT / PX_UNIT);
    out_matWorld._44 = 1.0;
}



GgafDx9UntransformedActor::~GgafDx9UntransformedActor() {
    DELETE_POSSIBLE_NULL(_pGeoMover);
    DELETE_POSSIBLE_NULL(_pGeoChecker);
}
