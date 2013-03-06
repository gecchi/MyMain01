#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ID_ORDER_BEGIN 11
PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";
    _id_ = 0;
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
    _id_ = 0;


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
            if (_pProg->getFrameInProgress() % 20 == 0 && P_GOD->_fps > PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                if (_id_ > order_id_end_-order_id_begin_) {
                    _pProg->changeNext();
                } else {
                    GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)obtainActorFromFactory(_id_+order_id_begin_);
                    pActor->locate(PX_C(_id_*70 - 500), PX_C(-100), 0);
                    getDirector()->addSubGroup(pActor);  _id_++;
                }
            }
            break;
        }
        case PreDrawScene::PROG_CALM: {
            if (_pProg->getFrameInProgress() >= 60 && P_GOD->_fps > PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                fadeoutSceneWithBgmTree(120);
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
            fadeoutSceneWithBgmTree(120);
            //end(120);
        }
    }
//
//    if (getActivePartFrame() == 1) {
////
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMeshTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMeshSetTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //CubeMapMorphMeshTestActor
//        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultD3DXAniMeshTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultBoardTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultBoardSetTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMeshTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMeshSetTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultMorphMeshTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultPointSpriteTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultSpriteTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //DefaultSpriteSetTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //HoshiBoshiTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //LaserChipTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SingleLaserTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SpriteMeshTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //SpriteMeshSetTestActor
//////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //StringBoardTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //WallAABTestActor
////        getDirector()->addSubGroup(obtainActorFromFactory(_id_));  _id_++;     //WallAAPrismTestActor
//    }

}

PreDrawScene::~PreDrawScene() {
}
