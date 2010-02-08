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

//3D空間の座標単位１に対してのPG内での座標単位の比率（PG内での座標単位を LEN_UNITで割ると3D空間の座標単位１になる）
#define LEN_UNIT (1000)
//3D空間の座標単位１に対しての画面px数（画面高さなどを、PX_UNITで割ると3D空間の座標単位１になる）
#define PX_UNIT (10)
#define PI (3.14159265358979)

//ノードの happen 引数
#define GGAF_EVENT_ON_DEVICE_LOST 101
#define GGAF_EVENT_DEVICE_LOST_RESTORE 102
#define GGAF_EVENT_NOLOOP_ANIMATION_FINISHED 201



//シェーダー2.0の限界のモーフターゲットは6個だった
#define MAX_MORPH_TARGET 6

#include <dxerr.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dsound.h>
#include <dxfile.h>





//#include "ogg/os_types.h"
//#include "ogg/ogg.h"
//#include "vorbis/codec.h"
//#include "vorbis/vorbisenc.h"
//#include "vorbis/vorbisfile.h"

#include "OggDecoder.h"
#include "OggVorbisMemory.h"
#include "OggVorbisFile.h"
#include "PCMPlayer.h"
#include "DixSmartPtr.h"
#include "DixComPtr.h"

//class CWaveDecorder;
//class CC3DSound;
//class CC3DSoundBufferSE;
//class CC3DSoundSE;

//
//#include "jp/ggaf/dx9core/sound/wavedecorder.h"
//#include "jp/ggaf/dx9core/sound/c3dsound.h"


class CmRandomNumberGenerator;

typedef int angle;
typedef int s_ang;
typedef int velo;
typedef int acce;
typedef int jerk;
typedef int angvelo;
typedef int angacce;
typedef int angjerk;

enum GgafDx9AnimationMethod {
    ANIMATE_ORDER_LOOP,
    ANIMATE_REVERSE_LOOP,
    ANIMATE_OSCILLATE_LOOP,
    ANIMATE_ORDER_NOLOOP,
    ANIMATE_REVERSE_NOLOOP,
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
class GgafDx9SphereActor;
class GgafDx9SphereEx;
class GgafDx9SpriteActor;
class GgafDx9SpriteSetActor;
class GgafDx9Camera;
class GgafDx9CameraViewPoint;
class GgafDx9BoardActor;
class GgafDx9BoardSetActor;

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
class GgafDx9GeometryMorpher;
class GgafDx9TextureBlinker;
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

//class DixComPtr;
//class DixSmartPtr;
//class PCMDecoder;
//class PCMPlayer;
//class OggDecoder;
//class OggVorbisResource;
//class OggVorbisFile;
//class OggVorbisMemory;

#include "ToolBox/IOModel_X.h"
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
#include "jp/ggaf/dx9core/util/GgafDx9Spline3D.h"
#include "jp/ggaf/dx9core/util/GgafDx9SplineProgram.h"
#include "jp/ggaf/dx9core/util/GgafDx9FixedFrameSplineProgram.h"
#include "jp/ggaf/dx9core/util/GgafDx9FixedVelocitySplineProgram.h"

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
#include "jp/ggaf/dx9core/actor/ex/GgafDx9CubeActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9CubeEx.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SphereActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SphereEx.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SpriteMeshActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9SpriteActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9SpriteSetActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9Camera.h"
#include "jp/ggaf/dx9core/actor/GgafDx9CameraViewPoint.h"
#include "jp/ggaf/dx9core/actor/GgafDx9BoardActor.h"
#include "jp/ggaf/dx9core/actor/GgafDx9BoardSetActor.h"

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

#include "jp/ggaf/dx9core/effect/GgafDx9Effect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9MeshEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9D3DXAniMeshEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9MeshSetEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9MorphMeshEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9SpriteEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9SpriteSetEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9BoardEffect.h"
#include "jp/ggaf/dx9core/effect/GgafDx9BoardSetEffect.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9StringBoardActor.h"

#include "jp/ggaf/dx9core/scene/GgafDx9Scene.h"
#include "jp/ggaf/dx9core/scene/GgafDx9Universe.h"
#include "jp/ggaf/dx9core/util/GgafDx9Util.h"
#include "jp/ggaf/dx9core/util/GgafDx9SphereRadiusVectors.h"
#include "jp/ggaf/dx9core/util/GgafDx9Quaternion.h"
#include "jp/ggaf/dx9core/util/GgafDx9CollisionArea.h"
#include "jp/ggaf/dx9core/util/GgafDx9CollisionPart.h"
#include "jp/ggaf/dx9core/util/GgafDx9Properties.h"
#include "jp/ggaf/dx9core/util/GgafDx9GeometryMover.h"
#include "jp/ggaf/dx9core/util/GgafDx9Checker.h"
#include "jp/ggaf/dx9core/util/GgafDx9GeometryScaler.h"
#include "jp/ggaf/dx9core/util/GgafDx9GeometryMorpher.h"
#include "jp/ggaf/dx9core/util/GgafDx9TextureBlinker.h"



#include "jp/ggaf/dx9core/model/GgafDx9RectUV.h"



//#include "jp/ggaf/dx9core/sound/c3dsound.hpp"
//#include "jp/ggaf/dx9core/sound/oggdecorder.hpp"
//#include "jp/ggaf/dx9core/sound/wavedecorder.hpp"
//


/*

#include "jp/ggaf/dx9core/sound/PCMDecoder.h"
#include "jp/ggaf/dx9core/sound/PCMPlayer.h"
#include "jp/ggaf/dx9core/sound/OggDecoder.h"
#include "jp/ggaf/dx9core/sound/OggVorbisResource.h"
#include "jp/ggaf/dx9core/sound/OggVorbisFile.h"
#include "jp/ggaf/dx9core/sound/OggVorbisMemory.h"

*/
#include "jp/ggaf/dx9core/sound/CWaveDecorder.h"


#include "jp/ggaf/dx9core/sound/GgafDx9Se.h"
#include "jp/ggaf/dx9core/sound/GgafDx9Bgm.h"
#include "jp/ggaf/dx9core/manager/GgafDx9SeConnection.h"
#include "jp/ggaf/dx9core/manager/GgafDx9SeManager.h"
#include "jp/ggaf/dx9core/manager/GgafDx9BgmConnection.h"
#include "jp/ggaf/dx9core/manager/GgafDx9BgmManager.h"
#include "jp/ggaf/dx9core/sound/GgafDx9Sound.h"

#endif /*GGAFDX9COMMONHEADER_H_*/
