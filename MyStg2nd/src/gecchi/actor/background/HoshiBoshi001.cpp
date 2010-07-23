#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

HoshiBoshi001::HoshiBoshi001(const char* prm_name) :
        GgafDx9PointSpriteActor(prm_name,
                               "hoshitest",
                               "HoshiBoshiEffect",
                               "HoshiBoshiTechnique",
                               NULL ) {
    _class_name = "HoshiBoshi001";
    _hMyShip_fX  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_MyShip_fX" );
    _hMyShip_fY  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_MyShip_fY" );
    _hMyShip_fZ  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_MyShip_fZ" );


    _frame_offset = 0;
    _pScaler = NEW GgafDx9GeometryScaler(this);


    //chengeEffectTechnique("DestBlendOne"); //���Z����
    setHitAble(false);
    _CAM_ZF = abs(pCAM->_zf * PX_UNIT * LEN_UNIT);
    _TRACE_("HoshiBoshi001::HoshiBoshi001 _CAM_ZF="<<_CAM_ZF);
    //�Ǝ����[���h�ϊ�
    defineRotMvWorldMatrix(HoshiBoshi001::setWorldMatrix_HoshiBoshi001);

}

int HoshiBoshi001::isOffscreen() {
    //��ʊO���薳��
    return 0;
}

bool HoshiBoshi001::isOutOfGameSpace() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}
void HoshiBoshi001::initialize() {

}

void HoshiBoshi001::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
}

void HoshiBoshi001::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 1000;
    }

    _pUvFlipper->behave();
}

void HoshiBoshi001::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDx9GeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //���[���h�ϊ��s��

}

void HoshiBoshi001::processJudgement() {
}

void HoshiBoshi001::processPreDraw() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDx9DrawableActor::processPreDraw() �Ɠ�������鎖�I
    GgafDx9Universe::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL - 10,this); //�Ő[��

//    //�ꎞ�e�N�j�b�N���ԃ`�F�b�N
//    if (_is_temp_technique) {
//        if (_frame_temp_technique <= _frame_of_behaving) {
//            //�ꎞ�e�N�j�b�N���Ԗ����B���ɖ߂�
//            _hash_technique = _hash_technique_temp;
//            strcpy(_technique, _technique_temp);
//            _is_temp_technique = false;
//            //����̓_���B�z��̈悪�ǂ����ɂ������߁B_technique_temp = "";
//            _hash_technique_temp = 0;
//        }
//    }
}

void HoshiBoshi001::processDraw() {
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_hMyShip_fX, pMYSHIP->_fX);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_hMyShip_fX) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_hMyShip_fY, pMYSHIP->_fY);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_hMyShip_fY) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_hMyShip_fZ, pMYSHIP->_fZ);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_hMyShip_fZ) �Ɏ��s���܂����B");
    GgafDx9PointSpriteActor::processDraw();
}


void HoshiBoshi001::drawHitArea() {
    //CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}


HoshiBoshi001::~HoshiBoshi001() {
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}



void HoshiBoshi001::setWorldMatrix_HoshiBoshi001(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ 2�{Z����] �~ 2�{Y����] �~ 1/2�{���s�ړ� �̕ϊ��s���ݒ�<BR>
    static float sinRx, cosRx, sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;
    sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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
