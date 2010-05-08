#ifndef GGAFDX9LIBSTGHEADER_H_
#define GGAFDX9LIBSTGHEADER_H_
#include "GgafDx9CommonHeader.h"

namespace GgafDx9LibStg {

class DefaultGod;
class DefaultUniverse;
class StgUtil;
class VirtualButton;
class VBRecorder;
class GeoElement;
class GeometryChain;
class DefaultScene;
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
class FormationActor;
//class FontSpriteString;
class CubeEx;
class SphereEx;
class SpriteMeshActor;
class SpriteMeshSetActor;
class ColliAAB;
class ColliSphere;
class LinearOctreeForActor;
class LinearOctreeActorElem;
class CollisionChecker;
}

#include "jp/ggaf/dx9libstg/DefaultGod.h"
#include "jp/ggaf/dx9libstg/util/StgUtil.h"

#include "jp/ggaf/dx9libstg/util/VirtualButton.h"
#include "jp/ggaf/dx9libstg/util/VBRecorder.h"
#include "jp/ggaf/dx9libstg/util/GeoElement.h"
#include "jp/ggaf/dx9libstg/util/GeometryChain.h"
#include "jp/ggaf/dx9libstg/scene/DefaultScene.h"
#include "jp/ggaf/dx9libstg/scene/DefaultUniverse.h"
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
#include "jp/ggaf/dx9libstg/actor/FormationActor.h"
#include "jp/ggaf/dx9libstg/actor/CubeEx.h"
#include "jp/ggaf/dx9libstg/actor/SphereEx.h"
#include "jp/ggaf/dx9libstg/actor/SpriteMeshActor.h"
#include "jp/ggaf/dx9libstg/actor/SpriteMeshSetActor.h"
#include "jp/ggaf/dx9libstg/util/FontSpriteString.h"
#include "jp/ggaf/dx9libstg/util/ColliAAB.h"
#include "jp/ggaf/dx9libstg/util/ColliSphere.h"
#include "jp/ggaf/dx9libstg/util/LinearOctreeForActor.h"
#include "jp/ggaf/dx9libstg/util/LinearOctreeActorElem.h"
#include "jp/ggaf/dx9libstg/util/CollisionChecker.h"



#define DISP_HITAREA 1

#define COLLI_AAB 1
#define COLLI_SPHERE 2


#endif /*GGAFDX9LIBSTGHEADER_H_*/
