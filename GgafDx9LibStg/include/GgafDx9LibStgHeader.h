#ifndef GGAFDX9LIBSTGHEADER_H_
#define GGAFDX9LIBSTGHEADER_H_
#include "GgafDx9CommonHeader.h"

namespace GgafDx9LibStg {

#define DISP_HITAREA 1

#define COLLI_AAB 1
#define COLLI_SPHERE 2
#define COLLI_AAPRISM 3

#define Obj_LaserChip                    (0x10000000)     //0b 00010000 00000000 00000000 00000000
#define Obj_WallPartsActor               (0x20000000)     //0b 00100000 00000000 00000000 00000000

#undef P_GOD
#define P_GOD ((GgafDx9LibStg::DefaultGod*)GgafCore::GgafGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((GgafDx9LibStg::DefaultUniverse*)(P_GOD->_pUniverse))




class DefaultGod;
class DefaultUniverse;
class DefaultCamera;
class StgUtil;
class VirtualButton;
class VBReplayRecorder;
class AmountGraph;

class DefaultScene;
class ActorTableScene;
class ScrolledScene;
class WalledScene;
class WalledSectionScene;



class StgProperties;



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
class FontSpriteActor;
//class FontSpriteString;
class ColliAABActor;
class ColliAAPrismActor;
class ColliSphereActor;
class SpriteMeshActor;
class SpriteMeshSetActor;
class StringBoardActor;
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
class CollisionChecker;
class CollisionCheckerLaserChip;


class Spline3D;
class SplineProgram;
class FixedFrameSplineProgram;
class FixedVelocitySplineProgram;
class SplineSource;
class SplineManager;
class SplineConnection;

class LaserChip;
class WateringLaserChip;
class HomingLaserChip;
class StraightLaserChip;
class RefractionLaserChip;
class LaserChipStore;
class LaserChipStoreDispatcher;
}

#include "jp/ggaf/dx9libstg/DefaultGod.h"
#include "jp/ggaf/dx9libstg/util/CollisionChecker.h"
#include "jp/ggaf/dx9libstg/util/CollisionCheckerLaserChip.h"
#include "jp/ggaf/dx9libstg/util/ColliAAB.h"
#include "jp/ggaf/dx9libstg/util/ColliSphere.h"
#include "jp/ggaf/dx9libstg/util/ColliAAPrism.h"
#include "jp/ggaf/dx9libstg/util/StgUtil.h"
#include "jp/ggaf/dx9libstg/util/SceneProgress.h"

#include "jp/ggaf/dx9libstg/util/VirtualButton.h"
#include "jp/ggaf/dx9libstg/util/VBReplayRecorder.h"
#include "jp/ggaf/dx9libstg/util/AmountGraph.h"

#include "jp/ggaf/dx9libstg/scene/DefaultScene.h"
#include "jp/ggaf/dx9libstg/scene/ActorTableScene.h"
#include "jp/ggaf/dx9libstg/scene/ScrolledScene.h"
#include "jp/ggaf/dx9libstg/scene/WalledScene.h"
#include "jp/ggaf/dx9libstg/scene/WalledSectionScene.h"

#include "jp/ggaf/dx9libstg/StgProperties.h"

#include "jp/ggaf/dx9libstg/scene/DefaultUniverse.h"
#include "jp/ggaf/dx9libstg/actor/DefaultCamera.h"
#include "jp/ggaf/dx9libstg/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultD3DXMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultD3DXAniMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/dx9libstg/actor/CubeMapMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/CubeMapMeshSetActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/CubeMapMorphMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultDynaD3DXMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultBoardActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultPointSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/FontSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/ColliAABActor.h"
#include "jp/ggaf/dx9libstg/actor/ColliAAPrismActor.h"
#include "jp/ggaf/dx9libstg/actor/ColliSphereActor.h"
#include "jp/ggaf/dx9libstg/actor/SpriteMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/SpriteMeshSetActor.h"
#include "jp/ggaf/dx9libstg/actor/StringBoardActor.h"
#include "jp/ggaf/dx9libstg/actor/WallPartsActor.h"
#include "jp/ggaf/dx9libstg/actor/WallAABActor.h"
#include "jp/ggaf/dx9libstg/actor/WallAAPrismActor.h"
#include "jp/ggaf/dx9libstg/actor/SpriteMeshWorldBoundActor.h"
#include "jp/ggaf/dx9libstg/actor/WorldBoundActor.h"
#include "jp/ggaf/dx9libstg/util/FontSpriteString.h"
#include "jp/ggaf/dx9libstg/util/LinearOctreeForActor.h"
#include "jp/ggaf/dx9libstg/util/LinearOctreeActorElem.h"

#include "jp/ggaf/dx9libstg/util/spline/Spline3D.h"
#include "jp/ggaf/dx9libstg/util/spline/SplineProgram.h"
#include "jp/ggaf/dx9libstg/util/spline/FixedFrameSplineProgram.h"
#include "jp/ggaf/dx9libstg/util/spline/FixedVelocitySplineProgram.h"
#include "jp/ggaf/dx9libstg/util/spline/SplineSource.h"
#include "jp/ggaf/dx9libstg/manager/SplineManager.h"
#include "jp/ggaf/dx9libstg/manager/SplineConnection.h"

#include "jp/ggaf/dx9libstg/actor/laserchip/LaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/WateringLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/HomingLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/RefractionLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/LaserChipStore.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/LaserChipStoreDispatcher.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/SingleLaser.h"




#endif /*GGAFDX9LIBSTGHEADER_H_*/
