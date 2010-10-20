#ifndef GGAFDX9COMMONHEADER_H_
#define GGAFDX9COMMONHEADER_H_
#include "GgafCommonHeader.h"


#define DIRECTINPUT_VERSION 0x0800

#ifndef DECLSPEC_DEPRECATED
#if (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#define DECLSPEC_DEPRECATED   __declspec(deprecated)
#define DEPRECATE_SUPPORTED
#else
#define DECLSPEC_DEPRECATED
#undef  DEPRECATE_SUPPORTED
#endif
#endif
//http://www.ogre3d.org/forums/viewtopic.php?f=2&t=45140
//意味を忘れたら、参照せよ



#define ANGLE0 (0)
#define ANGLE360 (360000)
#define ANGLE45 (45000)
#define ANGLE90 (90000)
#define ANGLE135 (135000)
#define ANGLE180 (180000)
#define ANGLE225 (225000)
#define ANGLE270 (270000)
#define ANGLE315 (315000)


#define S_ANG0 (0)
#define S_ANG360 (3600)
#define S_ANG45 (450)
#define S_ANG90 (900)
#define S_ANG135 (1350)
#define S_ANG180 (1800)
#define S_ANG225 (2250)
#define S_ANG270 (2700)
#define S_ANG315 (3150)

#define ANGLE_RATE (100)

#define ANGLE_PI (180000)
#define ANGLE_2PI (360000)


//DirectXの3D空間の座標単位１に対しての原点付近の画面px相当数（画面高さ(px)などを、PX_UNITで割ると3D空間の座標単位１になる）
#define PX_UNIT (10)
//原点付近の画面上の１px相当に対してのPG内での座標単位の比率（PG内での座標単位を LEN_UNITで割ると3D空間のpxになる）
#define LEN_UNIT (1000)
#define PI (3.14159265358979)

//イベント用 UINT32 数値宣言
AVAILABLE_EVENT(GGAF_EVENT_ON_DEVICE_LOST)
AVAILABLE_EVENT(GGAF_EVENT_DEVICE_LOST_RESTORE)
AVAILABLE_EVENT(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED)



//シェーダー2.0の限界のモーフターゲットは6個だった
#define MAX_MORPH_TARGET 6

#include <dxerr.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
#include <dxfile.h>
namespace Dix {
class PCMPlayer;
class OggVorbisResource;
class PCMDecoder;
class OggDecoder;
class OggVorbisFile;
class OggVorbisMemory;
}
#include "jp/ggaf/dx9core/sound/IkdLib/PCMPlayer.h"
#include "jp/ggaf/dx9core/sound/IkdLib/OggVorbisResource.h"
#include "jp/ggaf/dx9core/sound/IkdLib/PCMDecoder.h"
#include "jp/ggaf/dx9core/sound/IkdLib/OggDecoder.h"
#include "jp/ggaf/dx9core/sound/IkdLib/OggVorbisFile.h"
#include "jp/ggaf/dx9core/sound/IkdLib/OggVorbisMemory.h"










class CmRandomNumberGenerator;

typedef int angle;
typedef int s_ang;
typedef int velo;
typedef int acce;
typedef int jerk;
typedef int angvelo;
typedef int angacce;
typedef int angjerk;

enum GgafDx9UvFlipMethod {
    FLIP_ORDER_LOOP,
    FLIP_REVERSE_LOOP,
    FLIP_OSCILLATE_LOOP,
    FLIP_ORDER_NOLOOP,
    FLIP_REVERSE_NOLOOP,
    FLIP_CUSTOMIZED_LOOP,
    FLIP_CUSTOMIZED_NOLOOP,
    NOT_ANIMATED
};

enum GgafDx9ScaleMethod {
    NOSCALE,                  //!< NOSCALE
    TARGET_SCALE_LINER,       //!< TARGET_SCALE_LINER
    BEAT_SCALE_LINER,         //!< BEAT_SCALE_LINER
    BEAT_SCALE_TRIANGLEWAVE,  //!< BEAT_SCALE_TRIANGLEWAVE
    TARGET_SCALE_SIN,         //!< TARGET_SCALE_SIN
    BEAT_SCALE_SIN,           //!< BEAT_SCALE_SIN
    TARGET_SCALE_ACCELERATION,//!< TARGET_SCALE_ACCELERATION
    BEAT_SCALE_PARABOLA,      //!< BEAT_SCALE_PARABOLA
    TARGET_SCALE_PARABOLA_REV,//!< TARGET_SCALE_PARABOLA_REV
    BEAT_SCALE_PARABOLA_REV   //!< BEAT_SCALE_PARABOLA_REV
};

enum GgafDx9MorphMethod {
    NOMORPH,
    TARGET_MORPH_LINER,
    LOOP_MORPH_LINER,
    LOOP_MORPH_TRIANGLEWAVE,
    TARGET_MORPH_SIN,
    LOOP_MORPH_SIN,
    TARGET_MORPH_ACCELERATION,
    LOOP_MORPH_PARABOLA,
    TARGET_MORPH_PARABOLA_REV,
    LOOP_MORPH_PARABOLA_REV
};

enum GgafDx9BlinkerMethod {
    NOBLINK,                  //!< NOBLINK
    TARGET_BLINK_LINER,       //!< TARGET_BLINK_LINER
    BEAT_BLINK_LINER,         //!< BEAT_BLINK_LINER
    BEAT_BLINK_TRIANGLEWAVE,  //!< BEAT_BLINK_TRIANGLEWAVE
    TARGET_BLINK_SIN,         //!< TARGET_BLINK_SIN
    BEAT_BLINK_SIN,           //!< BEAT_BLINK_SIN
    TARGET_BLINK_ACCELERATION,//!< TARGET_BLINK_ACCELERATION
    BEAT_BLINK_PARABOLA,      //!< BEAT_BLINK_PARABOLA
    TARGET_BLINK_PARABOLA_REV,//!< TARGET_BLINK_PARABOLA_REV
    BEAT_BLINK_PARABOLA_REV   //!< BEAT_BLINK_PARABOLA_REV
};

#define Obj_GgafDx9Scene                (0x10)             //&B 00000000 00000000 00000000 00010000
#define Obj_GgafDx9Universe             (0x20)             //&B 00000000 00000000 00000000 00100000

#define Obj_GgafDx9BaseActor            (0x80)             //&B 00000000 00000000 00000000 10000000
#define Obj_GgafDx9GeometricActor       (0x100)            //&B 00000000 00000000 00000001 00000000
#define Obj_GgafDx9DrawableActor        (0x200)            //&B 00000000 00000000 00000010 00000000
#define Obj_GgafDx9MeshActor            (0x400)            //&B 00000000 00000000 00000100 00000000
#define Obj_GgafDx9MeshSetActor         (0x800)            //&B 00000000 00000000 00001000 00000000
#define Obj_GgafDx9MorphMeshActor       (0x1000)           //&B 00000000 00000000 00010000 00000000
#define Obj_GgafDx9D3DXMeshActor        (0x2000)           //&B 00000000 00000000 00100000 00000000
#define Obj_GgafDx9DynaD3DXMeshActor    (0x4000)           //&B 00000000 00000000 01000000 00000000
#define Obj_GgafDx9D3DXAniMeshActor     (0x8000)           //&B 00000000 00000000 10000000 00000000
#define Obj_GgafDx9SpriteMeshActor      (0x10000)          //&B 00000000 00000001 00000000 00000000
#define Obj_GgafDx9SpriteMeshSetActor   (0x20000)          //&B 00000000 00000010 00000000 00000000
#define Obj_GgafDx9SphereActor          (0x40000)          //&B 00000000 00000100 00000000 00000000
#define Obj_GgafDx9SphereEx             (0x80000)          //&B 00000000 00001000 00000000 00000000
#define Obj_GgafDx9SpriteActor          (0x100000)         //&B 00000000 00010000 00000000 00000000
#define Obj_GgafDx9SpriteSetActor       (0x200000)         //&B 00000000 00100000 00000000 00000000
#define Obj_GgafDx9Camera               (0x400000)         //&B 00000000 01000000 00000000 00000000
#define Obj_GgafDx9CameraViewPoint      (0x800000)         //&B 00000000 10000000 00000000 00000000
#define Obj_GgafDx9BoardActor           (0x1000000)        //&B 00000001 00000000 00000000 00000000
#define Obj_GgafDx9BoardSetActor        (0x2000000)        //&B 00000010 00000000 00000000 00000000
#define Obj_GgafDx9PointSpriteActor     (0x4000000)        //&B 00000100 00000000 00000000 00000000
#define Obj_GgafDx9StringBoardActor     (0x8000000)        //&B 00001000 00000000 00000000 00000000
#define Obj_GgafDx9StringSpriteActor    (0x10000000)       //&B 00010000 00000000 00000000 00000000
#define Obj_GgafDx9FormationActor       (0x20000000)       //&B 00100000 00000000 00000000 00000000
namespace GgafDx9Core {

class GgafDx9CriticalException;
class GgafDx9God;
class GgafDx9Input;
class GgafDx9Sound;

class GgafDx9TextureConnection;
class GgafDx9TextureManager;
class GgafDx9ModelConnection;
class GgafDx9ModelManager;
class GgafDx9EffectConnection;
class GgafDx9EffectManager;

class GgafDx9Spline3D;
class GgafDx9SplineProgram;
class GgafDx9FixedFrameSplineProgram;
class GgafDx9FixedVelocitySplineProgram;

class GgafDx9AllocHierarchy;
class D3DXFRAME_WORLD;
class GgafDx9AllocHierarchyWorldFrame;
class GgafDx9WorldMatStack;

class GgafDx9BaseActor;
class GgafDx9GeometricActor;
class GgafDx9DrawableActor;
class GgafDx9MeshActor;
class GgafDx9MeshSetActor;
class GgafDx9MorphMeshActor;
class GgafDx9D3DXMeshActor;
class GgafDx9DynaD3DXMeshActor;
class GgafDx9D3DXAniMeshActor;
class GgafDx9CubeActor;
class GgafDx9CubeEx;
class GgafDx9SpriteMeshActor;
class GgafDx9SpriteMeshSetActor;
class GgafDx9SphereActor;
class GgafDx9SphereEx;
class GgafDx9SpriteActor;
class GgafDx9SpriteSetActor;
class GgafDx9Camera;
class GgafDx9CameraViewPoint;
class GgafDx9BoardActor;
class GgafDx9BoardSetActor;
class GgafDx9PointSpriteActor;
class GgafDx9FormationActor;

class GgafDx9Model;
class GgafDx9D3DXMeshModel;
class GgafDx9D3DXAniMeshModel;
class GgafDx9SpriteModel;
class GgafDx9SpriteSetModel;
class GgafDx9MeshModel;
class GgafDx9MeshSetModel;
class GgafDx9MorphMeshModel;
class GgafDx9BoardModel;
class GgafDx9BoardSetModel;
class GgafDx9PointSpriteModel;

class GgafDx9Effect;
class GgafDx9MeshEffect;
class GgafDx9D3DXAniMeshEffect;
class GgafDx9MeshSetEffect;
class GgafDx9MorphMeshEffect;
class GgafDx9SpriteEffect;
class GgafDx9SpriteSetEffect;
class GgafDx9BoardEffect;
class GgafDx9BoardSetEffect;
class GgafDx9StringBoardActor;
class GgafDx9StringSpriteActor;
class GgafDx9PointSpriteEffect;

class GgafDx9Texture;

class GgafDx9Scene;
class GgafDx9Universe;

class GgafDx9Util;
class GgafDx9SphereRadiusVectors;
class GgafDx9Quaternion;
class GgafDx9CollisionArea;
class GgafDx9CollisionPart;
class GgafDx9Properties;
class GgafDx9GeometryMover;
class GgafDx9Checker;
class GgafDx9GeometryScaler;
class GgafDx9Morpher;
class GgafDx9SeTransmitter;
class GgafDx9BgmPerformer;
class GgafDx9AlphaCurtain;
class GgafDx9TextureBlinker;
class GgafDx9UvFlipper;
class GgafDx9RectUV;

class GgafDx9Se;
class GgafDx9Bgm;
class GgafDx9SeConnection;
class GgafDx9SeManager;
class GgafDx9BgmConnection;
class GgafDx9BgmManager;
class GgafDx9Sound;
class CWaveDecorder;

}



#include "jp/ggaf/dx9core/exception/GgafDx9CriticalException.h"
#include "jp/ggaf/dx9core/util/CmRandomNumberGenerator.h"
#include "jp/ggaf/dx9core/GgafDx9God.h"
#include "jp/ggaf/dx9core/util/GgafDx9Input.h"
#include "jp/ggaf/dx9core/manager/GgafDx9TextureConnection.h"
#include "jp/ggaf/dx9core/manager/GgafDx9TextureManager.h"
#include "jp/ggaf/dx9core/manager/GgafDx9ModelConnection.h"
#include "jp/ggaf/dx9core/manager/GgafDx9ModelManager.h"
#include "jp/ggaf/dx9core/manager/GgafDx9EffectConnection.h"
#include "jp/ggaf/dx9core/manager/GgafDx9EffectManager.h"
#include "jp/ggaf/dx9core/util/spline/GgafDx9Spline3D.h"
#include "jp/ggaf/dx9core/util/spline/GgafDx9SplineProgram.h"
#include "jp/ggaf/dx9core/util/spline/GgafDx9FixedFrameSplineProgram.h"
#include "jp/ggaf/dx9core/util/spline/GgafDx9FixedVelocitySplineProgram.h"

#include "jp/ggaf/dx9core/util/GgafDx9AllocHierarchy.h"
#include "jp/ggaf/dx9core/util/GgafDx9AllocHierarchyWorldFrame.h"
#include "jp/ggaf/dx9core/util/GgafDx9WorldMatStack.h"


#include "jp/ggaf/dx9core/actor/GgafDx9BaseActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9GeometricActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9DrawableActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9MeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9MeshSetActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9D3DXMeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9D3DXAniMeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9MorphMeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9DynaD3DXMeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9SpriteActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9SpriteSetActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9Camera.h"
#include "jp/ggaf/dx9core/actor/GgafDx9CameraViewPoint.h"
#include "jp/ggaf/dx9core/actor/GgafDx9BoardActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9BoardSetActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9PointSpriteActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9FormationActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9CubeActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9CubeEx.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SphereActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SphereEx.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SpriteMeshActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SpriteMeshSetActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9StringBoardActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9StringSpriteActor.h"

#include "jp/ggaf/dx9core/model/GgafDx9Model.h"
#include "jp/ggaf/dx9core/model/GgafDx9D3DXMeshModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9D3DXAniMeshModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9SpriteModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9SpriteSetModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9MeshModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9MeshSetModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9MorphMeshModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9BoardModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9BoardSetModel.h"
#include "jp/ggaf/dx9core/model/GgafDx9PointSpriteModel.h"

#include "jp/ggaf/dx9core/effect/GgafDx9Effect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9MeshEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9D3DXAniMeshEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9MeshSetEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9MorphMeshEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9SpriteEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9SpriteSetEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9BoardEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9BoardSetEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9PointSpriteEffect.h"

#include "jp/ggaf/dx9core/texture/GgafDx9Texture.h"

#include "jp/ggaf/dx9core/scene/GgafDx9Scene.h"
#include "jp/ggaf/dx9core/scene/GgafDx9Universe.h"

#include "jp/ggaf/dx9core/GgafDx9Util.h"
#include "jp/ggaf/dx9core/util/GgafDx9SphereRadiusVectors.h"
#include "jp/ggaf/dx9core/util/GgafDx9Quaternion.h"
#include "jp/ggaf/dx9core/util/GgafDx9CollisionArea.h"
#include "jp/ggaf/dx9core/util/GgafDx9CollisionPart.h"
#include "jp/ggaf/dx9core/util/GgafDx9Properties.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9GeometryMover.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9Checker.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9GeometryScaler.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9Morpher.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9SeTransmitter.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9UvFlipper.h"
#include "jp/ggaf/dx9core/scene/supporter/GgafDx9BgmPerformer.h"
#include "jp/ggaf/dx9core/scene/supporter/GgafDx9AlphaCurtain.h"
#include "jp/ggaf/dx9core/model/supporter/GgafDx9TextureBlinker.h"

#include "jp/ggaf/dx9core/model/GgafDx9RectUV.h"

#include "jp/ggaf/dx9core/sound/CWaveDecorder.h"
#include "jp/ggaf/dx9core/sound/GgafDx9Se.h"
#include "jp/ggaf/dx9core/sound/GgafDx9Bgm.h"
#include "jp/ggaf/dx9core/manager/GgafDx9SeConnection.h"
#include "jp/ggaf/dx9core/manager/GgafDx9SeManager.h"
#include "jp/ggaf/dx9core/manager/GgafDx9BgmConnection.h"
#include "jp/ggaf/dx9core/manager/GgafDx9BgmManager.h"
#include "jp/ggaf/dx9core/sound/GgafDx9Sound.h"

#endif /*GGAFDX9COMMONHEADER_H_*/
