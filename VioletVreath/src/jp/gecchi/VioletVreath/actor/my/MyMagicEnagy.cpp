#include "stdafx.h"
#include "MyMagicEnagy.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyMagicEnagy::MyMagicEnagy(const char* prm_name) :
        DefaultMeshActor(prm_name, "MagicEnagy", STATUS(MyMagicEnagy)) {
    _class_name = "MyMagicEnagy";
}

void MyMagicEnagy::initialize() {
    setHitAble(false);
    setAlpha(0.5);
}

void MyMagicEnagy::onActive() {
}

void MyMagicEnagy::processBehavior() {
    _pKurokoA->behave();
}

void MyMagicEnagy::processJudgement() {
}

int MyMagicEnagy::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool MyMagicEnagy::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}

void MyMagicEnagy::drawHitArea() {
    //ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

MyMagicEnagy::~MyMagicEnagy() {
}
