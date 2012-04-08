#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



HoshiBoshiTestActor::HoshiBoshiTestActor(const char* prm_name) :
        GgafDxPointSpriteActor(prm_name,
                               "_chk_HoshiBoshiTestModel",
                               "HoshiBoshiEffect",
                               "HoshiBoshiTechnique",
                               NULL,
                               NULL ) {
    _class_name = "HoshiBoshiTestActor";
    h_fX_MyShip_  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fX_MyShip" );
    h_fY_MyShip_  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fY_MyShip" );
    h_fZ_MyShip_  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fZ_MyShip" );

    changeEffectTechnique("DestBlendOne"); //���Z����
    setHitAble(false);
    CAM_ZF_ = abs(P_CAM->_zf * PX_UNIT * LEN_UNIT);
    _TRACE_("HoshiBoshiTestActor::HoshiBoshiTestActor CAM_ZF_="<<CAM_ZF_);
    //�Ǝ����[���h�ϊ�
    defineRotMvWorldMatrix(HoshiBoshiTestActor::setWorldMatrix_HoshiBoshiTestActor);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL);//�Ő[���̎����炢�ɁE�E
    //����DIRECTX����-1.0�`1.0�Ɏ��܂��Ă���O��ŁA
    //����Ԃ̑傫���ɎU��΂点��
    _SX = _SY = _SZ =  P_CAM->_zf*1000;
}

int HoshiBoshiTestActor::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool HoshiBoshiTestActor::isOutOfUniverse() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

void HoshiBoshiTestActor::initialize() {

}

void HoshiBoshiTestActor::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTestActor::processBehavior() {
    if (_X < -CAM_ZF_) {
        _X += (CAM_ZF_*2);
    } else {
        _X -= 1000;
    }
    _pUvFlipper->behave();
}

void HoshiBoshiTestActor::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDxGeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //���[���h�ϊ�
}

void HoshiBoshiTestActor::processJudgement() {
}

void HoshiBoshiTestActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(h_fX_MyShip_, P_MYSHIP->_fX);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fX_MyShip_) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(h_fY_MyShip_, P_MYSHIP->_fY);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fY_MyShip_) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(h_fZ_MyShip_, P_MYSHIP->_fZ);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fZ_MyShip_) �Ɏ��s���܂����B");
    GgafDxPointSpriteActor::processDraw();
}


void HoshiBoshiTestActor::drawHitArea() {
}

HoshiBoshiTestActor::~HoshiBoshiTestActor() {
}

void HoshiBoshiTestActor::setWorldMatrix_HoshiBoshiTestActor(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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
