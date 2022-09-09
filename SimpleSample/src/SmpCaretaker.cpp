#include "SmpCaretaker.h"

#include "actor/SmpCamera.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpCaretaker::SmpCaretaker() : GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* SmpCaretaker::createSpacetime() {
    //「この世」の作成処理をオーバーライドし、実装してください。
    SmpCamera* pCam = new SmpCamera("SMP_CAM"); //カメラ作成し、
    SmpSpacetime* pSpacetime = new SmpSpacetime("SMP_SPACETIME", pCam); //カメラを引数に「この世」を生成し、
    return pSpacetime; //生成した「この世」を返値とします。
}

SmpCaretaker::~SmpCaretaker() {
}


