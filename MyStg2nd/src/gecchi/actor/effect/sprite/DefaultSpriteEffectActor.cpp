#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultSpriteEffectActor::DefaultSpriteEffectActor(const char* prm_name, const char* prm_model) :
    DefaultSpriteActor(prm_name, prm_model) {
    _class_name = "DefaultSpriteEffectActor";
    setCollisionable(false);
}
//オーバーライド
void DefaultSpriteEffectActor::processHappen(int prm_event) {
    switch (prm_event) {
        case GGAF_EVENT_NOLOOP_ANIMATION_FINISHED:
            //繰り返さないアニメーション終了時、共通処理
            inactivate();
            moveFirst();
            break;
        default:
            break;
    }
}

DefaultSpriteEffectActor::~DefaultSpriteEffectActor() {
}
