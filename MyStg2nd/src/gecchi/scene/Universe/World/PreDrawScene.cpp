#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";
    int id = 11;
    orderActorToFactory(id, CubeMapMeshEffectActor       , "CubeMapMeshEffectActor");             id++;
    for (int i = 0; i < 30; i++) {
        orderActorToFactory(id, CubeMapMeshSetEffectActor    , "CubeMapMeshSetEffectActor"); id++;
    }
    orderActorToFactory(id, CubeMapMorphMeshEffectActor  , "CubeMapMorphMeshEffectActor");        id++;
//    orderActorToFactory(id, DefaultD3DXAniMeshEffectActor    , "DefaultD3DXAniMeshEffectActor");id++;
//    orderActorToFactory(id, DefaultBoardEffectActor      , "DefaultBoardEffectActor");          id++;
//    orderActorToFactory(id, DefaultBoardSetEffectActor   , "DefaultBoardSetEffectActor");       id++;
//    orderActorToFactory(id, DefaultMeshEffectActor       , "DefaultMeshEffectActor");           id++;
//    orderActorToFactory(id, DefaultMeshSetEffectActor    , "DefaultMeshSetEffectActor");        id++;
//    orderActorToFactory(id, DefaultMorphMeshEffectActor  , "DefaultMorphMeshEffectActor");      id++;
//    orderActorToFactory(id, DefaultPointSpriteEffectActor, "DefaultPointSpriteEffectActor");    id++;
//    orderActorToFactory(id, DefaultSpriteEffectActor     , "DefaultSpriteEffectActor");         id++;
//    orderActorToFactory(id, DefaultSpriteSetEffectActor  , "DefaultSpriteSetEffectActor");      id++;
//    orderActorToFactory(id, GroundMeshEffectActor        , "GroundMeshEffectActor");            id++;
//    orderActorToFactory(id, HoshiBoshiEffectActor        , "HoshiBoshiEffectActor");            id++;
//    orderActorToFactory(id, LaserChipEffectActor         , "LaserChipEffectActor");             id++;
//    orderActorToFactory(id, SingleLaserEffectActor       , "SingleLaserEffectActor");           id++;
//    orderActorToFactory(id, SpriteMeshEffectActor        , "SpriteMeshEffectActor");            id++;
//    orderActorToFactory(id, SpriteMeshSetEffectActor     , "SpriteMeshSetEffectActor");         id++;
//    orderActorToFactory(id, StringBoardEffectActor       , "StringBoardEffectActor");           id++;
//    orderActorToFactory(id, WallAABEffectActor           , "WallAABEffectActor");               id++;
//    orderActorToFactory(id, WallAAPrismEffectActor       , "WallAAPrismEffectActor");           id++;

}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
    GgafDx9Input::updateMouseState();
    GgafDx9Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    P_UNIVERSE->switchCameraWork("PauseCamWorker");
}

void PreDrawScene::processBehavior() {
    if (getActivePartFrame() == 1) {
        int id = 11;
        GgafDx9DrawableActor* pActor;

        getLordActor()->addSubGroup(obtainActorFromFactory(id));    id++;

        for (int i = 0; i < 30; i++) {
            pActor = (GgafDx9DrawableActor*)obtainActorFromFactory(id);   id++;
            pActor->locate((-(30/2)*5000) + (i * 50000), 200*1000, -50*1000);
            getLordActor()->addSubGroup(pActor);
        }

        getLordActor()->addSubGroup(obtainActorFromFactory(id));    id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getLordActor()->addSubGroup(obtainActorFromFactory(id));  id++;

    }
}

void PreDrawScene::processFinal() {
}

PreDrawScene::~PreDrawScene() {
}
