#ifndef GGAFDX9LIBSTGHEADER_H_
#define GGAFDX9LIBSTGHEADER_H_
#include "GgafDx9CommonHeader.h"

namespace GgafDx9LibStg {

#define DISP_HITAREA 1

#define COLLI_AAB 1
#define COLLI_SPHERE 2

#define Obj_LaserChip     (0x1000000)      //0b 00000001 00000000 00000000 00000000
#define Obj_WallActor     (0x2000000)      //0b 00000010 00000000 00000000 00000000



class DefaultGod;
class DefaultUniverse;
class DefaultCamera;
class StgUtil;
class VirtualButton;
class VBRecorder;
class GeoElement;
class GeometryChain;
class DefaultScene;
class ActorTableScene;
class ScrolledScene;
class WalledSectionScene;



class StgProperties;

class DefaultGeometricActor;
class DefaultD3DXMeshActor;
class DefaultD3DXAniMeshActor;
class DefaultMeshActor;
class DefaultMeshSetActor;
class DefaultMorphMeshActor;
class DefaultDynaD3DXMeshActor;
class DefaultCubeActor;
class DefaultSpriteActor;
class DefaultSpriteSetActor;
class DefaultBoardActor;
class DefaultBoardSetActor;
class DefaultPointSpriteActor;
class FontSpriteActor;
//class FontSpriteString;
class CubeEx;
class SphereEx;
class SpriteMeshActor;
class SpriteMeshSetActor;
class StringBoardActor;
class WallActor;
class WorldBoundActor;
class ColliAAB;
class ColliSphere;
class LinearOctreeForActor;
class LinearOctreeActorElem;
class CollisionChecker;
class CollisionCheckerLaserChip;

class LaserChip;
class CurveLaserChip;
class HomingLaserChip;
class StraightLaserChip;
class RefractionLaserChip;
class LaserChipDispatcher;
class LaserChipDispatcherDispatcher;
}

#include "jp/ggaf/dx9libstg/DefaultGod.h"
#include "jp/ggaf/dx9libstg/util/StgUtil.h"

#include "jp/ggaf/dx9libstg/util/VirtualButton.h"
#include "jp/ggaf/dx9libstg/util/VBRecorder.h"
#include "jp/ggaf/dx9libstg/util/GeoElement.h"
#include "jp/ggaf/dx9libstg/util/GeometryChain.h"
#include "jp/ggaf/dx9libstg/scene/DefaultScene.h"
#include "jp/ggaf/dx9libstg/scene/ActorTableScene.h"
#include "jp/ggaf/dx9libstg/scene/ScrolledScene.h"
#include "jp/ggaf/dx9libstg/scene/WalledSectionScene.h"

#include "jp/ggaf/dx9libstg/StgProperties.h"

#include "jp/ggaf/dx9libstg/scene/DefaultUniverse.h"
#include "jp/ggaf/dx9libstg/actor/DefaultCamera.h"
#include "jp/ggaf/dx9libstg/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultD3DXMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultD3DXAniMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultDynaD3DXMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultCubeActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultBoardActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/DefaultPointSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/FontSpriteActor.h"
#include "jp/ggaf/dx9libstg/actor/CubeEx.h"
#include "jp/ggaf/dx9libstg/actor/SphereEx.h"
#include "jp/ggaf/dx9libstg/actor/SpriteMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/SpriteMeshSetActor.h"
#include "jp/ggaf/dx9libstg/actor/StringBoardActor.h"
#include "jp/ggaf/dx9libstg/actor/WallActor.h"
#include "jp/ggaf/dx9libstg/actor/WorldBoundActor.h"
#include "jp/ggaf/dx9libstg/util/FontSpriteString.h"
#include "jp/ggaf/dx9libstg/util/ColliAAB.h"
#include "jp/ggaf/dx9libstg/util/ColliSphere.h"
#include "jp/ggaf/dx9libstg/util/LinearOctreeForActor.h"
#include "jp/ggaf/dx9libstg/util/LinearOctreeActorElem.h"
#include "jp/ggaf/dx9libstg/util/CollisionChecker.h"
#include "jp/ggaf/dx9libstg/util/CollisionCheckerLaserChip.h"

#include "jp/ggaf/dx9libstg/actor/laserchip/LaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/CurveLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/HomingLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/StraightLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/RefractionLaserChip.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/LaserChipDispatcher.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/LaserChipDispatcherDispatcher.h"
#include "jp/ggaf/dx9libstg/actor/laserchip/SingleLaser.h"






#endif /*GGAFDX9LIBSTGHEADER_H_*/
