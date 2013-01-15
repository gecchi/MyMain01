#ifndef GGAFLIBHEADER_H_
#define GGAFLIBHEADER_H_
#include "GgafDxCommonHeader.h"

namespace GgafLib {

#define DISP_HITAREA 1

#define COLLI_AAB     (0x1)  //0b 00000000 00000000 00000000 00000001
#define COLLI_SPHERE  (0x2)  //0b 00000000 00000000 00000000 00000010
#define COLLI_AAPRISM (0x4)  //0b 00000000 00000000 00000000 00000100

#define Obj_LaserChip                    (0x10000000)     //0b 00010000 00000000 00000000 00000000
#define Obj_WallPartsActor               (0x20000000)     //0b 00100000 00000000 00000000 00000000
#define Obj_IFormationAble               (0x40000000)     //0b 01000000 00000000 00000000 00000000

#undef P_GOD
#define P_GOD ((GgafLib::DefaultGod*)GgafCore::GgafGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((GgafLib::DefaultUniverse*)(P_GOD->_pUniverse))




class DefaultGod;
class DefaultUniverse;
class DefaultCamera;
class StgUtil;
class VirtualButton;
class VBReplayRecorder;
class AmountGraph;

class DefaultScene;
class FormationTableScene;
class ScrolledScene;
class WalledScene;
class WalledSectionScene;



class GgafLibProperties;
class TreeFormation;
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
class WallAAPrismctor;
class SpriteMeshWorldBoundActor;
class WorldBoundActor;
class ColliAAB;
class ColliSphere;
class ColliAAPrism;
class LinearOctreeForActor;
class LinearOctreeActorElem;
class CollisionChecker3D;

class SplineLine;
class SplineSequence;
class FixedFrameSplineSequence;
class FixedVelocitySplineSequence;
class SteppedCoordSplineSequence;
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
class LaserChipDepositoryStore;
}

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliAAB.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/SceneProgress.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"
#include "jp/ggaf/lib/util/AmountGraph.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/scene/FormationTableScene.h"
#include "jp/ggaf/lib/scene/ScrolledScene.h"
#include "jp/ggaf/lib/scene/WalledScene.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"

#include "jp/ggaf/lib/GgafLibProperties.h"

#include "jp/ggaf/lib/scene/DefaultUniverse.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"
#include "jp/ggaf/lib/actor/DepositoryFormation.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"
#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultDynaD3DXMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"
#include "jp/ggaf/lib/actor/ColliAABActor.h"
#include "jp/ggaf/lib/actor/ColliAAPrismActor.h"
#include "jp/ggaf/lib/actor/ColliSphereActor.h"
#include "jp/ggaf/lib/actor/SpriteMeshActor.h"
#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"
#include "jp/ggaf/lib/actor/SingleLaser.h"
#include "jp/ggaf/lib/actor/StringBoardActor.h"
#include "jp/ggaf/lib/actor/StringSpriteActor.h"
#include "jp/ggaf/lib/actor/WallPartsActor.h"
#include "jp/ggaf/lib/actor/WallAABActor.h"
#include "jp/ggaf/lib/actor/WallAAPrismActor.h"
#include "jp/ggaf/lib/actor/SpriteMeshWorldBoundActor.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/util/LinearOctreeActorElem.h"

#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSequence.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineSequence.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineSequence.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineSequence.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

#include "jp/ggaf/lib/manager/SplineSourceManager.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"
#include "jp/ggaf/lib/manager/SplineManufactureManager.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"

#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepositoryStore.h"

#include "jp/ggaf/lib/actor/menu/MenuActor.hpp"
























#endif /*GGAFLIBHEADER_H_*/
