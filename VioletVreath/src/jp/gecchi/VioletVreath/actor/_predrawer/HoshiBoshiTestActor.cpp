#include "HoshiBoshiTestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/effect/HoshiboshiEffect.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiTestActor::HoshiBoshiTestActor(const char* prm_name) :
        HoshiBoshi(prm_name, "_chk_HoshiBoshiTestModel") {
    _class_name = "HoshiBoshiTestActor";
    setFarRate(30.0f);
}

void HoshiBoshiTestActor::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTestActor::processBehavior() {
    _x -= 1000*getFarRate();
    getUvFlipper()->behave();
}

void HoshiBoshiTestActor::processJudgement() {
}

void HoshiBoshiTestActor::processDraw() {
    HoshiboshiEffect* pHoshiboshiEffect = (HoshiboshiEffect*)_pPointSpriteEffect;
    ID3DXEffect* const pID3DXEffect = pHoshiboshiEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_fX_MyShip_, 0);
    checkDxException(hr, D3D_OK, "SetFloat(h_fX_MyShip_) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_fY_MyShip_, 0);
    checkDxException(hr, D3D_OK, "SetFloat(h_fY_MyShip_) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_fZ_MyShip_, 0);
    checkDxException(hr, D3D_OK, "SetFloat(h_fZ_MyShip_) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_far_rate_, far_rate_);
    checkDxException(hr, D3D_OK, "SetFloat(h_far_rate_) �Ɏ��s���܂����B");
    GgafDxPointSpriteActor::processDraw();
}

HoshiBoshiTestActor::~HoshiBoshiTestActor() {
}

