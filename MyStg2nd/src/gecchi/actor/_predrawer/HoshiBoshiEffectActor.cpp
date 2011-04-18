#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;



HoshiBoshiEffectActor::HoshiBoshiEffectActor(const char* prm_name) :
        GgafDx9PointSpriteActor(prm_name,
                               "HoshiBoshiEffectActor",
                               "HoshiBoshiEffect",
                               "HoshiBoshiTechnique",
                               NULL ) {
    _class_name = "HoshiBoshiEffectActor";
    _h_fX_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fX_MyShip" );
    _h_fY_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fY_MyShip" );
    _h_fZ_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fZ_MyShip" );

    changeEffectTechnique("DestBlendOne"); //���Z����
    setHitAble(false);
    _CAM_ZF = abs(P_CAM->_zf * PX_UNIT * LEN_UNIT);
    _TRACE_("HoshiBoshiEffectActor::HoshiBoshiEffectActor _CAM_ZF="<<_CAM_ZF);
    //�Ǝ����[���h�ϊ�
    defineRotMvWorldMatrix(HoshiBoshiEffectActor::setWorldMatrix_HoshiBoshiEffectActor);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-10);//�Ő[���̎����炢�ɁE�E
    //����DIRECTX����-1.0�`1.0�Ɏ��܂��Ă���O��ŁA
    //����Ԃ̑傫���ɎU��΂点��
    _SX = _SY = _SZ =  P_CAM->_zf*1000;
}

int HoshiBoshiEffectActor::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool HoshiBoshiEffectActor::isOutOfUniverse() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}
void HoshiBoshiEffectActor::initialize() {

}

void HoshiBoshiEffectActor::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiEffectActor::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 1000;
    }
    _pUvFlipper->behave();
}

void HoshiBoshiEffectActor::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDx9GeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //���[���h�ϊ�
}

void HoshiBoshiEffectActor::processJudgement() {
}

void HoshiBoshiEffectActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_h_fX_MyShip, P_MYSHIP->_fX);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_h_fX_MyShip) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_h_fY_MyShip, P_MYSHIP->_fY);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_h_fY_MyShip) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_h_fZ_MyShip, P_MYSHIP->_fZ);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_h_fZ_MyShip) �Ɏ��s���܂����B");
    GgafDx9PointSpriteActor::processDraw();
}


void HoshiBoshiEffectActor::drawHitArea() {
}

HoshiBoshiEffectActor::~HoshiBoshiEffectActor() {
}

void HoshiBoshiEffectActor::setWorldMatrix_HoshiBoshiEffectActor(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx * cosRz *cosRy;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = Sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    out_matWorld._22 = Sy * cosRx *  cosRz;
    out_matWorld._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    out_matWorld._32 = Sz * -sinRx *  cosRz;
    out_matWorld._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}