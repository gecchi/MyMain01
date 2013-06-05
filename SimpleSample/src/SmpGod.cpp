#include "stdafx.h"
#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpUniverse.h"

using namespace SimpleSample;

SmpGod::SmpGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* SmpGod::createUniverse() {
    //この世の作成のサンプル
    SmpCamera* pCam = new SmpCamera("SIMPLE_CAMERA");                  //カメラ作成し、
    SmpUniverse* pUniverse = new SmpUniverse("SIMPLE_UNIVERSE", pCam); //この世を生成。
    return pUniverse;
}

SmpGod::~SmpGod() {
}

