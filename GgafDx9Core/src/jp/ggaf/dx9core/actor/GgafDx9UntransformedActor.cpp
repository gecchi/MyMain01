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
    //TODO:�v����
    if (_isActiveFlg && !_wasHiddenFlg && _isAliveFlg) {
        if (getAlpha() < 1.0) {
            //�����̏ꍇ�́AZ���l�ŉ�������`�悷��悤�ɐݒ�B
            //_Z �� �J���� �` �J����+2000,000 �̊Ԃł���Βi�K�����_�����O�����邱�ƂƂ���B
            //�e���� 2000,000/MAX_DRAW_DEPTH_LEVEL�B�����͈̔͂�Z�͓���[�x�ƂȂ�B
            //TODO: �J���������肮�蓮���Ɣg�󂷂�B�������̓J�������W����̋����Ń\�[�g���ׂ��B�E�E�E���̓���낤�B
            GgafDx9World::setDrawDepthLevel(
              (_Z-(GgafDx9God::_pVecCamFromPoint->z*LEN_UNIT*PX_UNIT)) / (2000000/MAX_DRAW_DEPTH_LEVEL),
              this
            );
        } else {
            //�s�����̏ꍇ�͏��߂ɕ`�悷��悤�ɐݒ�B
            //�����_�����O���ŉ�����`�悷��̂ŁA�[�x���x����MAX
            GgafDx9World::setDrawDepthMaxLevel(this);
        }

    }
}
void GgafDx9UntransformedActor::getWorldTransformRxRzRyScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //WORLD�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬���f�o�C�X�ɐݒ� .
    //��XYZ�̏��łȂ����Ƃɒ���
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
     //�O�̂���
     float fRateScale = LEN_UNIT;
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
     D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
     D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}


void GgafDx9UntransformedActor::getWorldTransformRzMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //WORLD�ϊ�
    //�P�ʍs�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬���f�o�C�X�ɐݒ�
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

    //WORLD�ϊ�
    //�P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬���f�o�C�X�ɐݒ�
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

GgafDx9UntransformedActor::~GgafDx9UntransformedActor() {
    DELETE_POSSIBLE_NULL(_pGeoMover);
    DELETE_POSSIBLE_NULL(_pGeoChecker);
}
