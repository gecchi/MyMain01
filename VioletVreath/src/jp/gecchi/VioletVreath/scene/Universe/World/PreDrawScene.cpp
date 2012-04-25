#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ID_ORDER_BEGIN 11
PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";
    order_id_begin_ = ID_ORDER_BEGIN;
    int id = order_id_begin_;
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
    order_id_end_ = id - 1;
    useProgress();
    _pProg->set(PreDrawScene::PROG_INIT);
}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
    _id = 0;


//    GgafDxDrawableActor* x;
//    x = (GgafDxDrawableActor*)(new MenuActor<CubeMapMeshActor       >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<CubeMapMeshSetActor    >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<CubeMapMorphMeshActor  >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultD3DXAniMeshActor>("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultBoardActor      >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultBoardSetActor   >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultMeshActor       >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultMeshSetActor    >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultMorphMeshActor  >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultPointSpriteActor>("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultSpriteActor     >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<DefaultSpriteSetActor  >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<SpriteMeshActor        >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<SpriteMeshSetActor     >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<StringBoardActor       >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<WallAABActor           >("aaa","bbb"));
//    x = (GgafDxDrawableActor*)(new MenuActor<WallAAPrismActor       >("aaa","bbb"));

}

void PreDrawScene::processBehavior() {
    switch (_pProg->get()) {
        case PreDrawScene::PROG_INIT: {
            if (_pProg->getFrameInProgress() % 20 == 0 && P_GOD->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                if (_id > order_id_end_-order_id_begin_) {
                    _pProg->changeNext();
                } else {
                    GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)obtainActorFromFactory(_id+order_id_begin_);
                    pActor->locate(PX_C(_id*70 - 500), PX_C(-100), 0);
                    getDirector()->addSubGroup(pActor);  _id++;
                }
            }
            break;
        }
        case PreDrawScene::PROG_CALM: {
            if (_pProg->getFrameInProgress() >= 60 && P_GOD->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                fadeoutSceneTree(120);
                _pProg->changeNext();
            }
            break;
        }
        case PreDrawScene::PROG_WAIT: {
            break;
        }
    }

//
    if (_pProg->get() == 1) {

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

PreDrawScene::~PreDrawScene() {
}
