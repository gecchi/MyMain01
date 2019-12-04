#ifndef GGAFLIBHEADER_H_
#define GGAFLIBHEADER_H_
#include "GgafDxCommonHeader.h"

#define DISP_HITAREA 1

#define COLLI_AABOX     (0x1)  //0b 00000000 00000000 00000000 00000001
#define COLLI_SPHERE    (0x2)  //0b 00000000 00000000 00000000 00000010
#define COLLI_AAPRISM   (0x4)  //0b 00000000 00000000 00000000 00000100
#define COLLI_AAPYRAMID (0x8)  //0b 00000000 00000000 00000000 00001000

#define Obj_DefaultScene  ( (0x40ULL) | Obj_SceneBit)    //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 01000000
#define Obj_WallScene     ((0x100ULL) | Obj_SceneBit)    //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000001 00000000

#define Obj_LaserChip               (0x1000000000ULL)    //0b 00000000 00000000 00000001 00000000 00000000 00000000 00000000 00000000
#define Obj_WallPartsActor          (0x2000000000ULL)    //0b 00000000 00000000 00000010 00000000 00000000 00000000 00000000 00000000
#define Obj_IFormationAble          (0x4000000000ULL)    //0b 00000000 00000000 00000100 00000000 00000000 00000000 00000000 00000000
#define Obj_MassWallActor           (0x8000000000ULL)    //0b 00000000 00000000 00001000 00000000 00000000 00000000 00000000 00000000
#define Obj_CubeMapMassWallActor   (0x10000000000ULL)    //0b 00000000 00000000 00010000 00000000 00000000 00000000 00000000 00000000

typedef int_fast32_t dir26;
typedef int_fast32_t dir8;

//�O���錾(forward declaration)
namespace GgafLib {

class DefaultGod;
class DefaultSpacetime;
class CameraWorker;
class AroundViewCamWorker;
class DefaultCamera;
class DefaultCameraViewPoint;
class DefaultCameraUpVector;
class StgUtil;
class VirtualButton;
class VBReplayRecorder;

class DefaultScene;
class SceneProgress;
class FormationTableScene;
class WallScene;
class WallSectionScene;

class LibConfig;

class DefaultSceneMediator;
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
class DefaultMassMorphMeshActor;
class CubeMapMorphMeshActor;
class DefaultDynaD3DXMeshActor;
class DefaultSpriteActor;
class DefaultSpriteSetActor;
class DefaultMassSpriteActor;
class DefaultBoardActor;
class DefaultBoardSetActor;
class DefaultMassBoardActor;
class DefaultPointSpriteActor;
class DefaultMassPointSpriteActor;
class DefaultPointSpriteSetActor;
class DefaultFramedBoardActor;
class DefaultRegularPolygonBoardActor;
class DefaultRegularPolygonSpriteActor;
class DefaultAniMeshActor;

class ColliAABoxActor;
class ColliAAPrismActor;
class ColliAAPyramidActor;
class ColliSphereActor;
class SpriteMeshActor;
class SpriteMeshSetActor;
class FontSpriteActor;
class FontBoardActor;
class WallPartsActor;
class WallAABctor;
class WallAAPrismActor;
class WallAAPyramidActor;
class GraphBarActor;
class CappedGraphBarActor;
class MassWallActor;
class FramedHorizontalBarActor;
class PieGraphSpriteActor;

class SpriteMeshWorldBoundActor;
class WorldBoundActor;
class ColliAABox;
class ColliSphere;
class ColliAAPrism;
class ColliAAPyramid;
class CollisionChecker;
class CollisionChecker3D;
class CollisionChecker2D;

class SplineLeader;
class FixedFrameSplineRikishaLeader;
class FixedVelocitySplineRikishaLeader;
class SteppedCoordSplineRikishaLeader;
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
class NomalLaserChip;
class LaserChipDepository;

class DefaultEffectManager;
class MassWallEffect;

class CameraWorkerManager;
class CameraWorkerConnection;
class CameraWorkerChanger;
class DefaultCamWorker;

}

#endif /*GGAFLIBHEADER_H_*/
