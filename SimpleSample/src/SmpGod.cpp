#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpGod::SmpGod() : GgafLib::DefaultGod() {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = キーボード↑ または、Y軸－ とする。
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = キーボード↓ または、Y軸＋ とする。
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = キーボード← または、X軸－ とする。
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = キーボード→ または、X軸＋ とする。
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = スペースキー または ジョイスティックボタン１ とする。
}

GgafCore::Spacetime* SmpGod::createSpacetime() {
    //「この世」の作成処理をオーバーライドし、実装してください。
    SmpCamera* pCam = new SmpCamera("SMP_CAM"); //カメラ作成し、
    SmpSpacetime* pSpacetime = new SmpSpacetime("SMP_SPACETIME", pCam); //カメラを引数に「この世」を生成し、
    return pSpacetime; //生成した「この世」を返値とします。
}

SmpGod::~SmpGod() {
}

