#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define ID_ORDER_BEGIN 11
PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";
    _order_id_begin = ID_ORDER_BEGIN;
    int id = _order_id_begin;
    orderActorToFactory(id, CubeMapMeshTestActor       , "CubeMapMeshTestActor");           id++;
    orderActorToFactory(id, CubeMapMeshSetTestActor    , "CubeMapMeshSetTestActor");        id++;
    orderActorToFactory(id, CubeMapMorphMeshTestActor  , "CubeMapMorphMeshTestActor");      id++;
    orderActorToFactory(id, DefaultD3DXAniMeshTestActor , "DefaultD3DXAniMeshTestActor");   id++;
//    orderActorToFactory(id, DefaultBoardTestActor      , "DefaultBoardTestActor");          id++;
//    orderActorToFactory(id, DefaultBoardSetTestActor   , "DefaultBoardSetTestActor");       id++;
    orderActorToFactory(id, DefaultMeshTestActor       , "DefaultMeshTestActor");           id++;
    orderActorToFactory(id, DefaultMeshSetTestActor    , "DefaultMeshSetTestActor");        id++;
    orderActorToFactory(id, DefaultMorphMeshTestActor  , "DefaultMorphMeshTestActor");      id++;
//    orderActorToFactory(id, DefaultPointSpriteTestActor, "DefaultPointSpriteTestActor");    id++;
//    orderActorToFactory(id, DefaultSpriteTestActor     , "DefaultSpriteTestActor");         id++;
//    orderActorToFactory(id, DefaultSpriteSetTestActor  , "DefaultSpriteSetTestActor");      id++;
//    orderActorToFactory(id, HoshiBoshiTestActor        , "HoshiBoshiTestActor");            id++;
    orderActorToFactory(id, LaserChipTestActor         , "LaserChipTestActor");             id++;
    orderActorToFactory(id, SingleLaserTestActor       , "SingleLaserTestActor");           id++;
    orderActorToFactory(id, SpriteMeshTestActor        , "SpriteMeshTestActor");            id++;
    orderActorToFactory(id, SpriteMeshSetTestActor     , "SpriteMeshSetTestActor");         id++;
//    orderActorToFactory(id, StringBoardTestActor       , "StringBoardTestActor");           id++;
    orderActorToFactory(id, WallAABTestActor           , "WallAABTestActor");               id++;
    orderActorToFactory(id, WallAAPrismTestActor       , "WallAAPrismTestActor");           id++;
    _order_id_end = id - 1;
    useProgress();
}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
    GgafDx9Input::updateMouseState();
    GgafDx9Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    _id = 0;
    _pProg->set(1);
}

void PreDrawScene::processBehavior() {


//
    if (_pProg->get() == 1) {
        if (getActivePartFrame() % 10 == 0) {
            if (_id > _order_id_end-_order_id_begin) {
                _pProg->changeNext();
            } else {
                GgafDx9GeometricActor* pActor = (GgafDx9GeometricActor*)obtainActorFromFactory(_id+_order_id_begin);
                pActor->locate(_id*50*1000,0,0);
                getDirector()->addSubGroup(pActor);  _id++;
            }
        }
    }

    if (_pProg->get() == 2) {
        if (_pProg->isJustChanged()) {
            fadeoutSceneTree(120);
            //end(120);
        }
    }
//
//    if (getActivePartFrame() == 1) {
////
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //CubeMapMeshTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //CubeMapMeshSetTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //CubeMapMorphMeshTestActor
//        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultD3DXAniMeshTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultBoardTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultBoardSetTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultMeshTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultMeshSetTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultMorphMeshTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultPointSpriteTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultSpriteTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //DefaultSpriteSetTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //HoshiBoshiTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //LaserChipTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //SingleLaserTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //SpriteMeshTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //SpriteMeshSetTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //StringBoardTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //WallAABTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id));  _id++;     //WallAAPrismTestActor
//    }

}

void PreDrawScene::processFinal() {
}

PreDrawScene::~PreDrawScene() {
}
