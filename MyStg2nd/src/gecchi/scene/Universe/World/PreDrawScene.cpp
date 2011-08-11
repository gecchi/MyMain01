#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";
    int id = 11;

//    orderActorToFactory(id, CubeMapMeshTestActor       , "CubeMapMeshTestActor");             id++;
//    orderActorToFactory(id, CubeMapMeshSetTestActor    , "CubeMapMeshSetTestActor"); id++;
//    orderActorToFactory(id, CubeMapMorphMeshTestActor  , "CubeMapMorphMeshTestActor");        id++;
//    orderActorToFactory(id, DefaultD3DXAniMeshTestActor , "DefaultD3DXAniMeshTestActor");id++;
//    orderActorToFactory(id, DefaultBoardTestActor      , "DefaultBoardTestActor");          id++;
//    orderActorToFactory(id, DefaultBoardSetTestActor   , "DefaultBoardSetTestActor");       id++;
//    orderActorToFactory(id, DefaultMeshTestActor       , "DefaultMeshTestActor");           id++;
//    orderActorToFactory(id, DefaultMeshSetTestActor    , "DefaultMeshSetTestActor");        id++;
//    orderActorToFactory(id, DefaultMorphMeshTestActor  , "DefaultMorphMeshTestActor");      id++;
//    orderActorToFactory(id, DefaultPointSpriteTestActor, "DefaultPointSpriteTestActor");    id++;
//    orderActorToFactory(id, DefaultSpriteTestActor     , "DefaultSpriteTestActor");         id++;
//    orderActorToFactory(id, DefaultSpriteSetTestActor  , "DefaultSpriteSetTestActor");      id++;
//    orderActorToFactory(id, GroundMeshTestActor        , "GroundMeshTestActor");            id++;
//    orderActorToFactory(id, HoshiBoshiTestActor        , "HoshiBoshiTestActor");            id++;
//    orderActorToFactory(id, LaserChipTestActor         , "LaserChipTestActor");             id++;
//    orderActorToFactory(id, SingleLaserTestActor       , "SingleLaserTestActor");           id++;
//    orderActorToFactory(id, SpriteMeshTestActor        , "SpriteMeshTestActor");            id++;
//    orderActorToFactory(id, SpriteMeshSetTestActor     , "SpriteMeshSetTestActor");         id++;
//    orderActorToFactory(id, StringBoardTestActor       , "StringBoardTestActor");           id++;
//    orderActorToFactory(id, WallAABTestActor           , "WallAABTestActor");               id++;
//    orderActorToFactory(id, WallAAPrismTestActor       , "WallAAPrismTestActor");           id++;

}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
    GgafDx9Input::updateMouseState();
    GgafDx9Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void PreDrawScene::processBehavior() {
    if (getActivePartFrame() == 1) {
        int id = 11;
        GgafDx9DrawableActor* pActor;

//        getDirector()->addSubGroup(obtainActorFromFactory(id));    id++;
//
//        for (int i = 0; i < 30; i++) {
//            pActor = (GgafDx9DrawableActor*)obtainActorFromFactory(id);   id++;
//            pActor->locate((-(30/2)*5000) + (i * 50000), 200*1000, -50*1000);
//            getDirector()->addSubGroup(pActor);
//        }
//
//        getDirector()->addSubGroup(obtainActorFromFactory(id));    id++;



//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;
//        getDirector()->addSubGroup(obtainActorFromFactory(id));  id++;

    }
}

void PreDrawScene::processFinal() {
}

PreDrawScene::~PreDrawScene() {
}
