#include "Planet001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "Planet001Atmosphere.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Planet001::Planet001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001", nullptr) {
    _class_name = "Planet001";
    setHitAble(false);
    setZEnable(true);        //Zバッファは考慮
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND-3);
    drawAnyFar(true);//遠くても表示
    //大気圏エフェクトスプライト
    pAtmosphere_ = NEW Planet001Atmosphere("P001ATMOS");
    addSubLast(pAtmosphere_);
}

void Planet001::onCreateModel() {
}

void Planet001::initialize() {
    setAlpha(0.99);
    _x = (GgafDxUniverse::_x_gone_right*10);
    setScale(1000*1000);
    setRzFaceAng(D90ANG - D_ANG(30));
    setRyFaceAng(D45ANG);
    getKuroko()->setFaceAngVelo(AXIS_X, 500); //自転の速さ

    pAtmosphere_->setScale(_sx);
    pAtmosphere_->positionAs(this);
}
void Planet001::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();

    //巨大オブジェクト移動テスト
    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
        _x += PX_C(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_O)) {
        _x += PX_C(1000);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_U)) {
        _x -= PX_C(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_Y)) {
        _x -= PX_C(1000);
    }

    if (GgafDxInput::isBeingPressedKey(DIK_8)) {
        _y += PX_C(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_J)) {
        _y -= PX_C(100);
    }

    if (GgafDxInput::isBeingPressedKey(DIK_M)) {
        _y -= PX_C(1000);
    }


    if (GgafDxInput::isBeingPressedKey(DIK_9)) {
        _z += PX_C(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_K)) {
        _z -= PX_C(100);
    }

    if (GgafDxInput::isBeingPressedKey(DIK_0)) {
        addScale(10000);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_L)) {
        addScale(-10000);
    }

    if (GgafDxInput::isPushedDownKey(DIK_O)) {
        _TRACE_("Planet001  "<<_x<<","<<_y<<","<<_z<<" scale="<<_rx);
    }
    //_x = _x - PX_C(1);
    pKuroko->behave();

    pAtmosphere_->setScale(_sx);
    pAtmosphere_->positionAs(this);
}

Planet001::~Planet001() {
}

