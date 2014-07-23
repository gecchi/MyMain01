#ifndef GGAFLIBHEADER_H_
#define GGAFLIBHEADER_H_
#include "GgafDxCommonHeader.h"



#define DISP_HITAREA 1

#define COLLI_AAB     (0x1)  //0b 00000000 00000000 00000000 00000001
#define COLLI_SPHERE  (0x2)  //0b 00000000 00000000 00000000 00000010
#define COLLI_AAPRISM (0x4)  //0b 00000000 00000000 00000000 00000100


#define Obj_DefaultScene         (0x80000040U)     //0b 10000000 00000000 00000000 01000000
#define Obj_WalledScene          (0x80000080U)     //0b 10000000 00000000 00000000 10000000

#define Obj_LaserChip            (0x10000000U)     //0b 00010000 00000000 00000000 00000000
#define Obj_WallPartsActor       (0x20000000U)     //0b 00100000 00000000 00000000 00000000
#define Obj_IFormationAble       (0x40000000U)     //0b 01000000 00000000 00000000 00000000

//ëOï˚êÈåæ(forward declaration)
namespace GgafLib {

class DefaultGod;
class DefaultUniverse;
class DefaultCamera;
class StgUtil;
class VirtualButton;
class VBReplayRecorder;
class PxQuantity;

class DefaultScene;
class SceneProgress;
class FormationTableScene;
class WalledScene;
class WalledSectionScene;

class GgafLibProperties;
class TreeFormation;
class FkFormation;
class DepositoryFormation;
class DefaultGeometricActor;
class DefaultD3DXMeshActor;
class DefaultD3DXAniMeshActor;
class DefaultMeshActor;
class DefaultMeshSetActor;
class CubeMapMeshActor;
class CubeMapMeshSetActor;
class DefaultMorphMeshActor;
class CubeMapMorphMeshActor;
class DefaultDynaD3DXMeshActor;
class DefaultSpriteActor;
class DefaultSpriteSetActor;
class DefaultBoardActor;
class DefaultBoardSetActor;
class DefaultPointSpriteActor;
class ColliAABActor;
class ColliAAPrismActor;
class ColliSphereActor;
class SpriteMeshActor;
class SpriteMeshSetActor;
class StringBoardActor;
class StringSpriteActor;
class WallPartsActor;
class WallAABctor;
class WallAAPrismActor;
class GraphBarActor;
class CappedGraphBarActor;

class SpriteMeshWorldBoundActor;
class WorldBoundActor;
class ColliAAB;
class ColliSphere;
class ColliAAPrism;
class LinearOctreeForActor;
class LinearOctreeActorElem;
class CollisionChecker3D;

class SplineLine;
class SplineKurokoLeader;
class FixedFrameSplineKurokoLeader;
class FixedVelocitySplineKurokoLeader;
class SteppedCoordSplineKurokoLeader;
class SplineManufacture;
class SplineSource;
class FixedFrameSplineManufacture;
class FixedVelocitySplineManufacture;
class SteppedCoordSplineManufacture;
class SplineSourceManager;
class SplineSourceConnection;
class SplineManufactureManager;
class SplineManufactureConnection;
class LaserChip;
class WateringLaserChip;
class HomingLaserChip;
class StraightLaserChip;
class RefractionLaserChip;
class LaserChipDepository;
}

#endif /*GGAFLIBHEADER_H_*/
