#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PreDrawScene::PreDrawScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "PreDrawScene";

    orderActorToFactory(10, BackGroundStarEffectActor    , "BackGroundStarEffectActor");
    orderActorToFactory(11, CubeMapMeshEffectActor       , "CubeMapMeshEffectActor");
    orderActorToFactory(12, CubeMapMeshSetEffectActor    , "CubeMapMeshSetEffectActor");
    orderActorToFactory(13, CubeMapMorphMeshEffectActor  , "CubeMapMorphMeshEffectActor");
    orderActorToFactory(14, DefaultAniMeshEffectActor    , "DefaultAniMeshEffectActor");
    orderActorToFactory(15, DefaultBoardEffectActor      , "DefaultBoardEffectActor");
    orderActorToFactory(16, DefaultBoardSetEffectActor   , "DefaultBoardSetEffectActor");
    orderActorToFactory(17, DefaultMeshEffectActor       , "DefaultMeshEffectActor");
    orderActorToFactory(18, DefaultMeshSetEffectActor    , "DefaultMeshSetEffectActor");
    orderActorToFactory(19, DefaultMorphMeshEffectActor  , "DefaultMorphMeshEffectActor");
    orderActorToFactory(21, DefaultPointSpriteEffectActor, "DefaultPointSpriteEffectActor");
    orderActorToFactory(22, DefaultSpriteEffectActor     , "DefaultSpriteEffectActor");
    orderActorToFactory(23, DefaultSpriteSetEffectActor  , "DefaultSpriteSetEffectActor");
    orderActorToFactory(24, GroundMeshEffectActor        , "GroundMeshEffectActor");
    orderActorToFactory(25, HoshiBoshiEffectActor        , "HoshiBoshiEffectActor");
    orderActorToFactory(26, LaserChipEffectActor         , "LaserChipEffectActor");
    orderActorToFactory(27, SingleLaserEffectActor       , "SingleLaserEffectActor");
    orderActorToFactory(28, SpriteMeshEffectActor        , "SpriteMeshEffectActor");
    orderActorToFactory(29, SpriteMeshSetEffectActor     , "SpriteMeshSetEffectActor");
    orderActorToFactory(31, StringBoardEffectActor       , "StringBoardEffectActor");
    orderActorToFactory(32, WallAABEffectActor           , "WallAABEffectActor");
    orderActorToFactory(33, WallAAPrismEffectActor       , "WallAAPrismEffectActor");

}

void PreDrawScene::onReset() {
}
void PreDrawScene::ready() {
}

void PreDrawScene::initialize() {
}

void PreDrawScene::processBehavior() {
    if (getActivePartFrame() == 1) {
        getLordActor()->addSubGroup(obtainActorFromFactory(10));
        getLordActor()->addSubGroup(obtainActorFromFactory(11));
        getLordActor()->addSubGroup(obtainActorFromFactory(12));
        getLordActor()->addSubGroup(obtainActorFromFactory(13));
        getLordActor()->addSubGroup(obtainActorFromFactory(14));
        getLordActor()->addSubGroup(obtainActorFromFactory(15));
        getLordActor()->addSubGroup(obtainActorFromFactory(16));
        getLordActor()->addSubGroup(obtainActorFromFactory(17));
        getLordActor()->addSubGroup(obtainActorFromFactory(18));
        getLordActor()->addSubGroup(obtainActorFromFactory(19));
        getLordActor()->addSubGroup(obtainActorFromFactory(21));
        getLordActor()->addSubGroup(obtainActorFromFactory(22));
        getLordActor()->addSubGroup(obtainActorFromFactory(23));
        getLordActor()->addSubGroup(obtainActorFromFactory(24));
        getLordActor()->addSubGroup(obtainActorFromFactory(25));
        getLordActor()->addSubGroup(obtainActorFromFactory(26));
        getLordActor()->addSubGroup(obtainActorFromFactory(27));
        getLordActor()->addSubGroup(obtainActorFromFactory(28));
        getLordActor()->addSubGroup(obtainActorFromFactory(29));
        getLordActor()->addSubGroup(obtainActorFromFactory(31));
        getLordActor()->addSubGroup(obtainActorFromFactory(32));
        getLordActor()->addSubGroup(obtainActorFromFactory(33));

    }
}

void PreDrawScene::processFinal() {
}

PreDrawScene::~PreDrawScene() {
}
