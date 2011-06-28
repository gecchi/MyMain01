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

#define GGAF_MAX_VOLUME (100)
#define GGAF_MIN_VOLUME (0)

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

//プリズム位置定数
#define POS_PRISM_XY_nn   (0x11) //0b 0010001
#define POS_PRISM_XY_np   (0x12) //0b 0010010
#define POS_PRISM_XY_pn   (0x14) //0b 0010100
#define POS_PRISM_XY_pp   (0x18) //0b 0011000
#define POS_PRISM_YZ_nn   (0x21) //0b 0100001
#define POS_PRISM_YZ_np   (0x22) //0b 0100010
#define POS_PRISM_YZ_pn   (0x24) //0b 0100100
#define POS_PRISM_YZ_pp   (0x28) //0b 0101000
#define POS_PRISM_ZX_nn   (0x41) //0b 1000001
#define POS_PRISM_ZX_np   (0x42) //0b 1000010
#define POS_PRISM_ZX_pn   (0x44) //0b 1000100
#define POS_PRISM_ZX_pp   (0x48) //0b 1001000

#define POS_PRISM_nn      (0x1)  //0b 0000001
#define POS_PRISM_np      (0x2)  //0b 0000010
#define POS_PRISM_pn      (0x4)  //0b 0000100
#define POS_PRISM_pp      (0x8)  //0b 0001000
#define POS_PRISM_XY      (0x10) //0b 0010000
#define POS_PRISM_YZ      (0x20) //0b 0100000
#define POS_PRISM_ZX      (0x40) //0b 1000000

//DirectXの3D空間の座標単位１に対しての原点付近の画面px相当数（画面高さ(px)などを、PX_UNITで割ると3D空間の座標単位１になる）
#define PX_UNIT (10)
//原点付近の画面上の１px相当に対してのPG内での座標単位の比率（PG内での座標単位を LEN_UNITで割ると3D空間のpxになる）
#define LEN_UNIT (1000)
#define PI (3.14159265358979)
//#define MAX_DRAW_DEPTH_LEVEL 1000
#define MAX_DRAW_DEPTH_LEVEL 220

#define MAX_SE_AT_ONCE 10
#define MAX_SE_DELAY 240

//イベント用 UINT32 数値宣言
AVAILABLE_EVENT(GGAF_EVENT_ON_DEVICE_LOST);
AVAILABLE_EVENT(GGAF_EVENT_DEVICE_LOST_RESTORE);


#ifdef MY_DEBUG
    #define checkDxException(HR, OKVAL, X) { \
        if (HR != OKVAL) { \
            std::stringstream ss; \
            ss <<__FILE__<<"("<<__LINE__<<") : " << X; \
            throw GgafDx9Core::GgafDx9CriticalException(ss.str(),HR); \
        } \
    }
#else
    #define checkDxException(HR, OKVAL, X)
#endif

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

typedef int appangle;
typedef int angvelo;
typedef int angacce;
typedef int angjerk;
typedef int s_ang;

typedef int appcoord;
typedef int velo;
typedef int acce;
typedef int jerk;

typedef int axisid;

typedef int appscale;

typedef int pixcoord;
typedef float dxcoord;


#define cnvCoordApp2Dx(X)  ((dxcoord)(1.0f * (X) / LEN_UNIT / PX_UNIT))
#define cnvCoordDx2App(X)  ((appcoord)((X) * LEN_UNIT * PX_UNIT))
#define cnvCoordDx2Pix(X)  ((X) * PX_UNIT)
#define cnvCoordPix2Dx(X)  (1.0f * (X) / PX_UNIT)
#define cnvCoordApp2Pix(X) (1.0f * (X) / LEN_UNIT)
#define cnvCoordPix2App(X) ((X) * LEN_UNIT)


#define cnvScaleApp2Rate(X) (1.0f * (X) / LEN_UNIT)
#define cnvScaleRate2App(X) ((X) * LEN_UNIT)
#define cnvAppang2Sin(X) (GgafDx9Core::GgafDx9Util::SIN[(X) / ANGLE_RATE])
#define cnvAppang2Cos(X) (GgafDx9Core::GgafDx9Util::COS[(X) / ANGLE_RATE])


enum GgafDx9UvFlipMethod {
    FLIP_ORDER_LOOP,
    FLIP_REVERSE_LOOP,
    FLIP_OSCILLATE_LOOP,
    FLIP_ORDER_NOLOOP,
    FLIP_REVERSE_NOLOOP,
    FLIP_CUSTOMIZED_LOOP,    //!< TODO:実装したが未検証
    FLIP_CUSTOMIZED_NOLOOP,  //!< TODO:実装したが未検証
    NOT_ANIMATED
};

enum GgafDx9ScaleMethod {
    NOSCALE,
    TARGET_SCALE_LINER,
    BEAT_SCALE_LINER,
    BEAT_SCALE_TRIANGLEWAVE,
    TARGET_SCALE_SIN,          //!< TODO:未実装
    BEAT_SCALE_SIN,            //!< TODO:未実装
    TARGET_SCALE_ACCELERATION,
    BEAT_SCALE_PARABOLA,       //!< TODO:未実装
    TARGET_SCALE_PARABOLA_REV, //!< TODO:未実装
    BEAT_SCALE_PARABOLA_REV    //!< TODO:未実装
};

enum GgafDx9MorphMethod {
    NOMORPH,
    TARGET_MORPH_LINER,
    LOOP_MORPH_LINER,
    LOOP_MORPH_TRIANGLEWAVE,
    TARGET_MORPH_SIN,          //!< TODO:未実装
    LOOP_MORPH_SIN,            //!< TODO:未実装
    TARGET_MORPH_ACCELERATION,
    LOOP_MORPH_PARABOLA,       //!< TODO:未実装
    TARGET_MORPH_PARABOLA_REV, //!< TODO:未実装
    LOOP_MORPH_PARABOLA_REV    //!< TODO:未実装
};

enum GgafDx9BlinkerMethod {
    NOBLINK,
    TARGET_BLINK_LINER,
    BEAT_BLINK_LINER,
    BEAT_BLINK_TRIANGLEWAVE,
    TARGET_BLINK_SIN,          //!< TODO:未実装
    BEAT_BLINK_SIN,            //!< TODO:未実装
    TARGET_BLINK_ACCELERATION,
    BEAT_BLINK_PARABOLA,       //!< TODO:未実装
    TARGET_BLINK_PARABOLA_REV, //!< TODO:未実装
    BEAT_BLINK_PARABOLA_REV    //!< TODO:未実装
};

enum GgafDx9PuppeteerPlayMethod {
    NO_CHENGE = 0,
    PLAY_LOOPING = 1,
    PLAY_OSCILLATING = 2
};

enum GgafDx9PuppeteerStick {
    LEFT_HAND  = 0,
    RIGHT_HAND = 1
};


#define Obj_GgafDx9Scene                 (0x80000010)     //0b 10000000 00000000 00000000 00010000
#define Obj_GgafDx9Universe              (0x80000020)     //0b 10000000 00000000 00000000 00100000

#define Obj_GgafDx9BaseActor             (0x80)           //0b 00000000 00000000 00000000 10000000
#define Obj_GgafDx9GeometricActor        (0x100)          //0b 00000000 00000000 00000001 00000000
#define Obj_GgafDx9DrawableActor         (0x200)          //0b 00000000 00000000 00000010 00000000
#define Obj_GgafDx9MeshActor             (0x400)          //0b 00000000 00000000 00000100 00000000
#define Obj_GgafDx9MeshSetActor          (0x800)          //0b 00000000 00000000 00001000 00000000
#define Obj_GgafDx9MorphMeshActor        (0x1000)         //0b 00000000 00000000 00010000 00000000
#define Obj_GgafDx9D3DXMeshActor         (0x2000)         //0b 00000000 00000000 00100000 00000000
#define Obj_GgafDx9DynaD3DXMeshActor     (0x4000)         //0b 00000000 00000000 01000000 00000000
#define Obj_GgafDx9D3DXAniMeshActor      (0x8000)         //0b 00000000 00000000 10000000 00000000
#define Obj_GgafDx9SpriteMeshActor       (0x10000)        //0b 00000000 00000001 00000000 00000000
#define Obj_GgafDx9SpriteMeshSetActor    (0x20000)        //0b 00000000 00000010 00000000 00000000
#define Obj_GgafDx9CubeMapMeshActor      (0x40000)        //0b 00000000 00000100 00000000 00000000
#define Obj_GgafDx9CubeMapMeshSetActor   (0x80000)        //0b 00000000 00001000 00000000 00000000
#define Obj_GgafDx9CubeMapMorphMeshActor (0x100000)       //0b 00000000 00010000 00000000 00000000
#define Obj_GgafDx9WorldBoundActor       (0x200000)       //0b 00000000 00100000 00000000 00000000
#define Obj_GgafDx9SpriteActor           (0x400000)       //0b 00000000 01000000 00000000 00000000
#define Obj_GgafDx9SpriteSetActor        (0x800000)       //0b 00000000 10000000 00000000 00000000
#define Obj_GgafDx9BoardActor            (0x1000000)      //0b 00000001 00000000 00000000 00000000
#define Obj_GgafDx9BoardSetActor         (0x2000000)      //0b 00000010 00000000 00000000 00000000
#define Obj_GgafDx9PointSpriteActor      (0x4000000)      //0b 00000100 00000000 00000000 00000000
#define Obj_GgafDx9FormationActor        (0x8000000)      //0b 00001000 00000000 00000000 00000000
#undef P_GOD
#define P_GOD ((GgafDx9Core::GgafDx9God*)GgafDx9Core::GgafDx9God::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((GgafDx9Core::GgafDx9Universe*)(P_GOD->_pUniverse))

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

class GgafDx9ICubeMapActor;

class GgafDx9BaseActor;
class GgafDx9GeometricActor;
class GgafDx9DrawableActor;
class GgafDx9MeshActor;
class GgafDx9MeshSetActor;
class GgafDx9MorphMeshActor;
class GgafDx9D3DXMeshActor;
class GgafDx9DynaD3DXMeshActor;
class GgafDx9D3DXAniMeshActor;

class GgafDx9SpriteMeshActor;
class GgafDx9SpriteMeshSetActor;
class GgafDx9CubeMapMeshActor;
class GgafDx9CubeMapMeshSetActor;
class GgafDx9CubeMapMorphMeshActor;
class GgafDx9WorldBoundActor;

class GgafDx9AABActor;
class GgafDx9AAPrismActor;
class GgafDx9SphereActor;

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
class GgafDx9CubeMapMeshModel;
class GgafDx9CubeMapMeshSetModel;
class GgafDx9CubeMapMorphMeshModel;
class GgafDx9WorldBoundModel;
class GgafDx9BoardModel;
class GgafDx9BoardSetModel;
class GgafDx9PointSpriteModel;

class GgafDx9Effect;
class GgafDx9MeshEffect;
class GgafDx9D3DXAniMeshEffect;
class GgafDx9MeshSetEffect;
class GgafDx9MorphMeshEffect;
class GgafDx9CubeMapMeshEffect;
class GgafDx9CubeMapMeshSetEffect;
class GgafDx9CubeMapMorphMeshEffect;
class GgafDx9WorldBoundEffect;
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
class GgafDx9GeoElem;
class GgafDx9GeoChain;
class GgafDx9KurokoA;
class GgafDx9KurokoB;
class GgafDx9Checker;
class GgafDx9Scaler;
class GgafDx9Morpher;
class GgafDx9SeTransmitter;
class GgafDx9BgmPerformer;
class GgafDx9AlphaCurtain;
class GgafDx9TextureBlinker;
class GgafDx9UvFlipper;
class GgafDx9Puppeteer;
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

#include "jp/ggaf/dx9core/util/XFile/framework/frm_mesh.h"
#include "jp/ggaf/dx9core/util/XFile/framework/Frm_Tbuff.h"
#include "jp/ggaf/dx9core/util/XFile/ToolBox/IOModel_X.h"
#include "jp/ggaf/dx9core/util/XFile/ToolBox/IOTexture_Bmp.h"
#include "jp/ggaf/dx9core/util/XFile/ToolBox/TBox_Textures.h"

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

#include "jp/ggaf/dx9core/actor/interface/GgafDx9ICubeMapActor.h"
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
#include "jp/ggaf/dx9core/actor/ex/GgafDx9AABActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9AAPrismActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SphereActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SpriteMeshActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9SpriteMeshSetActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9StringBoardActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9StringSpriteActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9CubeMapMeshActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9CubeMapMeshSetActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9CubeMapMorphMeshActor.h"
#include "jp/ggaf/dx9core/actor/ex/GgafDx9WorldBoundActor.h"

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
#include "jp/ggaf/dx9core/model/ex/GgafDx9CubeMapMeshModel.h"
#include "jp/ggaf/dx9core/model/ex/GgafDx9CubeMapMeshSetModel.h"
#include "jp/ggaf/dx9core/model/ex/GgafDx9CubeMapMorphMeshModel.h"
#include "jp/ggaf/dx9core/model/ex/GgafDx9WorldBoundModel.h"

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
#include "jp/ggaf/dx9core/effect/ex/GgafDx9CubeMapMeshEffect.h"
#include "jp/ggaf/dx9core/effect/ex/GgafDx9CubeMapMeshSetEffect.h"
#include "jp/ggaf/dx9core/effect/ex/GgafDx9CubeMapMorphMeshEffect.h"
#include "jp/ggaf/dx9core/effect/ex/GgafDx9WorldBoundEffect.h"

#include "jp/ggaf/dx9core/texture/GgafDx9Texture.h"

#include "jp/ggaf/dx9core/scene/GgafDx9Scene.h"
#include "jp/ggaf/dx9core/scene/GgafDx9Universe.h"

#include "jp/ggaf/dx9core/GgafDx9Util.h"
#include "jp/ggaf/dx9core/util/GgafDx9SphereRadiusVectors.h"
#include "jp/ggaf/dx9core/util/GgafDx9Quaternion.h"
#include "jp/ggaf/dx9core/util/GgafDx9CollisionArea.h"
#include "jp/ggaf/dx9core/util/GgafDx9CollisionPart.h"
#include "jp/ggaf/dx9core/util/GgafDx9Properties.h"
#include "jp/ggaf/dx9core/util/GgafDx9GeoElem.h"
#include "jp/ggaf/dx9core/util/GgafDx9GeoChain.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9KurokoA.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9KurokoB.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9Checker.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9Scaler.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9Morpher.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9SeTransmitter.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9UvFlipper.h"
#include "jp/ggaf/dx9core/actor/supporter/GgafDx9Puppeteer.h"
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
