#include "VecEyeActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"

#include "jp/ggaf/lib/util/RhombicuboctahedronUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

//Ternary numeral -1,0,1 の3数の3進法 を 配列要素のため正の10進数に変換するマクロ
#define TN(X,Y,Z) (((3*3)*((X)+1)) + (3*((Y)+1)) + ((Z)+1))

VecEyeActor::VecEyeActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "VecEye") {
    _hx = 1;
    _hy = 0;
    _hz = 0;
    _hx_prev = 0;
    _hy_prev = 0;
    _hz_prev = 0;
}

void VecEyeActor::initialize() {
    setScaleR(3.0);
}

void VecEyeActor::processBehavior() {

    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD7)) {
        _hx = -1;  _hy = 1;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD8)) {
        _hx = 0;   _hy = 1;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD9)) {
        _hx = 1;   _hy = 1;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD4)) {
        _hx = -1;   _hy = 0;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD5)) {
        _hx = 0;   _hy = 0;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD6)) {
        _hx = 1;   _hy = 0;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD1)) {
        _hx = -1;   _hy = -1;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD2)) {
        _hx = 0;   _hy = -1;
    }
    if (GgafDxInput::isBeingPressedKey(DIK_NUMPAD3)) {
        _hx = 1;   _hy = -1;
    }

    if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
        _hz = 1;
    } else if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
        _hz = -1;
    } else {
        _hz = 0;
    }

    if(_hx != _hx_prev || _hy != _hy_prev || _hz != _hz_prev) {
        float vx,vy,vz;
        RhombicuboctahedronUtil::cnvFaceNo2Vec(TN(_hx,_hy,_hz), vx, vy, vz);
        getKuroko()->asstB()->turnFaceAngByVdTwd(
                D_ANG(2),
                vx * PX_C(100), vy * PX_C(100), vz* PX_C(100), TURN_CLOSE_TO, true,
                0.3, 0.7, 0, true);
    }
    _hx_prev = _hx;
    _hy_prev = _hy;
    _hz_prev = _hz;
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

VecEyeActor::~VecEyeActor() {
}
