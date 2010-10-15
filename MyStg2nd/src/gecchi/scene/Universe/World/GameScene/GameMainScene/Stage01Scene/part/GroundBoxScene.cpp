#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;



GroundBoxScene::GroundBoxActor::GroundBoxActor(const char* prm_name) :
    WallActor(prm_name, "16/g_box001") {
    _class_name = "GroundBoxActor";
    MyStgUtil::resetGroundBoxActorStatus(_pStatus);
    setHitAble(true);
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
}


void GroundBoxScene::GroundBoxActor::initialize() {
    _SX=_SY=_SZ = 2000;
    setBoundingSphereRadiusRate(2.0);
}


GroundBoxScene::GroundBoxScene(const char* prm_name) : WalledScene(prm_name,
                                                                   "../MyStg2nd/stage_data.txt",
                                                                   800000, 200000,200000,
                                                                   32000
                                                                   ) {
//gecchi@dv9200-xp ~/workspace/MyStg2nd (520)$ ruby tool/script/make_stage_data.rb > stage_data.txt

    for (int i = 0; i < 4000; i++) {
        GroundBoxActor* pGroundBoxActor =  NEW GroundBoxActor("GroundBox");
        pGroundBoxActor->enableFrontAlpha(pMYSHIP);
        pGroundBoxActor->inactivateTreeImmediately();
        _pDispatcher_Wall->addSubLast(pGroundBoxActor);
    }

}

GroundBoxScene::~GroundBoxScene() {

}
