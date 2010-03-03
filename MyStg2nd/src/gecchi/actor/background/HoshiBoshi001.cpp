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


    //chengeEffectTechnique("DestBlendOne"); //加算合成
    setHitAble(false);
    _CAM_ZF = abs(pCAM->_zf * PX_UNIT * LEN_UNIT);
    _TRACE_("HoshiBoshi001::HoshiBoshi001 _CAM_ZF="<<_CAM_ZF);
}

int HoshiBoshi001::isOffscreen() {
    //画面外判定無し
    return 0;
}

bool HoshiBoshi001::isOutOfGameSpace() {
    //ゲーム座標範囲外判定無し
    return false;
}
void HoshiBoshi001::initialize() {

}

void HoshiBoshi001::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void HoshiBoshi001::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void HoshiBoshi001::processPreJudgement() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDx9GeometricActor::processPreJudgement() と同期を取る事！
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
}

void HoshiBoshi001::processJudgement() {
}

void HoshiBoshi001::processPreDraw() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDx9DrawableActor::processPreDraw() と同期を取る事！
    GgafDx9Universe::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL ,this); //最深部

//    //一時テクニック期間チェック
//    if (_is_temp_technique) {
//        if (_frame_temp_technique <= _frame_of_behaving) {
//            //一時テクニック期間満了。元に戻す
//            _hash_technique = _hash_technique_temp;
//            strcpy(_technique, _technique_temp);
//            _is_temp_technique = false;
//            //これはダメ。配列領域がどこかにいくため。_technique_temp = "";
//            _hash_technique_temp = 0;
//        }
//    }
}

void HoshiBoshi001::processDraw() {
    ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_hMyShip_fX, pMYSHIP->_fX);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_hMyShip_fX) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_hMyShip_fY, pMYSHIP->_fY);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_hMyShip_fY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_hMyShip_fZ, pMYSHIP->_fZ);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_hMyShip_fZ) に失敗しました。");
    GgafDx9PointSpriteActor::processDraw();
}


void HoshiBoshi001::drawHitArea() {
    //CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}


HoshiBoshi001::~HoshiBoshi001() {
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
