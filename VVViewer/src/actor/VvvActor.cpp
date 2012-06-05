#include "stdafx.h"
using namespace GgafLib;
using namespace VVViewer;

VvvActor::VvvActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void VvvActor::initialize() {
    //座標設定
    _X = _Y = _Z = 0; //(0,0,0) は画面の中心
}

void VvvActor::processBehavior() {
    //キャラをボタン入力で移動
    VirtualButton* vb = P_WORLD->vb_;
    if (vb->isBeingPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb->isBeingPressed(VB_UP)) {
            _Z += PX_C(2); //奥
        }
        if (vb->isBeingPressed(VB_DOWN)) {
            _Z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb->isBeingPressed(VB_RIGHT)) {
            _X += PX_C(2); //右
        }
        if (vb->isBeingPressed(VB_LEFT)) {
            _X -= PX_C(2); //左
        }
        if (vb->isBeingPressed(VB_UP)) {
            _Y += PX_C(2); //上
        }
        if (vb->isBeingPressed(VB_DOWN)) {
            _Y -= PX_C(2); //下
        }
    }
}

VvvActor::~VvvActor() {
}
