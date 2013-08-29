#include "stdafx.h"
#include "actor/TestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace Mogera;

TestActor::TestActor(const char* prm_name) :
        GgafLib::DefaultSpriteActor(prm_name, "Ichimatsu") {
}

void TestActor::initialize() {
    //座標設定
    position(0, 0, 0); //(0,0,0) は画面の中心
}

void TestActor::processBehavior() {
    _pKurokoA->behave(); //黒衣Aを活動させる（Z軸回転する）
}

TestActor::~TestActor() {
}
