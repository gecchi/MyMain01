#ifndef GGAFDXCOMMONHEADER_H_
#define GGAFDXCOMMONHEADER_H_
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


//近い方向に回転
#define TURN_CLOSE_TO 0
//遠い方向に回転
#define TURN_ANTICLOSE_TO 2
//時計回りに回転
#define TURN_CLOCKWISE (-1)
//反時計回りに回転
#define TURN_COUNTERCLOCKWISE 1
//どちらかの回転（いずれの回転でも）
#define TURN_BOTH 0

//プリズム姿勢(位置)定数
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


//プリズムは、どの面から向かってスライスされたかを示す
/** XY平面に垂直にスライスした形である */
#define POS_PRISM_XY      (0x10) //0b 0010000
/** YZ平面に垂直にスライスした形である */
#define POS_PRISM_YZ      (0x20) //0b 0100000
/** ZX平面に垂直にスライスした形である */
#define POS_PRISM_ZX      (0x40) //0b 1000000

//スライスで出来るプリズム(４通り)の位置を、
//直角三角形の直角がある場所に注目し、
//平面座標の象限(軸座標の正負)で示す。
//n = negative(負), p = positive(正)
/** 直角がある場所 は, (負, 負)である */
#define POS_PRISM_nn      (0x1)  //0b 0000001
/** 直角がある場所 は, (負, 正)である */
#define POS_PRISM_np      (0x2)  //0b 0000010
/** 直角がある場所 は, (正, 負)である */
#define POS_PRISM_pn      (0x4)  //0b 0000100
/** 直角がある場所 は, (正, 正)である */
#define POS_PRISM_pp      (0x8)  //0b 0001000






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
DECLARE_CONST(GGAF_EVENT_ON_DEVICE_LOST);
DECLARE_CONST(GGAF_EVENT_DEVICE_LOST_REDEPOSITORY);


#ifdef MY_DEBUG
    #define checkDxException(HR, OKVAL, X) { \
        if (HR != OKVAL) { \
            std::stringstream ss; \
            ss <<__FILE__<<"("<<__LINE__<<") : " << X; \
            throw GgafDxCore::GgafDxCriticalException(ss.str(),HR); \
        } \
    }
#else
    #define checkDxException(HR, OKVAL, X)
#endif

#define throwGgafDxCriticalException(HR, X) { \
        std::stringstream ss; \
        ss <<__FILE__<<"("<<__LINE__<<") : " << X; \
        throw GgafDxCore::GgafDxCriticalException(ss.str(),HR); \
}


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
#include "jp/ggaf/dxcore/sound/IkdLib/PCMPlayer.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisResource.h"
#include "jp/ggaf/dxcore/sound/IkdLib/PCMDecoder.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggDecoder.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisFile.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisMemory.h"







//class CmRandomNumberGenerator;
/** 座標 (目安：10.0 dxcoord = 1 pixcoord = 1000 coord)  */
typedef int coord;
/** 速度 (座標に毎フレーム加算される座標差分) */
typedef int velo;
/** 加速度 (速度に毎フレーム加算される速度差分) */
typedef int acce;
typedef int jerk;

typedef int pixcoord;
typedef float dxcoord;

typedef int angle;
typedef int ang_velo;
typedef int ang_acce;
typedef int ang_jerk;
typedef int s_ang;

typedef int axis;

typedef int scale;



#define App2Dx(X)  ((dxcoord)(1.0f * (X) / LEN_UNIT / PX_UNIT))
#define Dx2App(X)  ((coord)((X) * LEN_UNIT * PX_UNIT))
#define Dx2Pix(X)  ((X) * PX_UNIT)
#define Pix2Dx(X)  (1.0f * (X) / PX_UNIT)
#define App2Pix(X) (1.0f * (X) / LEN_UNIT)
#define Pix2App(X) ((X) * LEN_UNIT)


#define cnvScaleApp2Rate(X) (1.0f * (X) / LEN_UNIT)
#define cnvScaleRate2App(X) ((X) * LEN_UNIT)
#define Angle2Sin(X) (GgafDxCore::GgafDxUtil::SIN[(X) / ANGLE_RATE])
#define Angle2Cos(X) (GgafDxCore::GgafDxUtil::COS[(X) / ANGLE_RATE])


enum GgafDxUvFlippingMethod {
    FLIP_ORDER_LOOP,
    FLIP_REVERSE_LOOP,
    FLIP_OSCILLATE_LOOP,
    FLIP_ORDER_NOLOOP,
    FLIP_REVERSE_NOLOOP,
    FLIP_CUSTOMIZED_LOOP,    //!< TODO:実装したが未検証
    FLIP_CUSTOMIZED_NOLOOP,  //!< TODO:実装したが未検証
    NOT_ANIMATED
};

enum GgafDxScalingMethod {
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

enum GgafDxColoringMethod {
    NOCOLOR,
    TARGET_COLOR_LINER,
    BEAT_COLOR_LINER,
    BEAT_COLOR_TRIANGLEWAVE,
    TARGET_COLOR_SIN,          //!< TODO:未実装
    BEAT_COLOR_SIN,            //!< TODO:未実装
    TARGET_COLOR_ACCELERATION,
    BEAT_COLOR_PARABOLA,       //!< TODO:未実装
    TARGET_COLOR_PARABOLA_REV, //!< TODO:未実装
    BEAT_COLOR_PARABOLA_REV    //!< TODO:未実装
};

enum GgafDxAlphaFadingMethod {
    NO_ALPHAFADE,
    TARGET_ALPHAFADE_LINER,
    BEAT_ALPHAFADE_LINER,
    BEAT_ALPHAFADE_TRIANGLEWAVE,
    TARGET_ALPHAFADE_SIN,          //!< TODO:未実装
    BEAT_ALPHAFADE_SIN,            //!< TODO:未実装
    TARGET_ALPHAFADE_ACCELERATION,
    BEAT_ALPHAFADE_PARABOLA,       //!< TODO:未実装
    TARGET_ALPHAFADE_PARABOLA_REV, //!< TODO:未実装
    BEAT_ALPHAFADE_PARABOLA_REV    //!< TODO:未実装
};

enum GgafDxMorphingMethod {
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

enum GgafDxBlinkingMethod {
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

enum GgafDxPuppeteerMethod {
    NO_CHENGE = 0,
    PLAY_LOOPING = 1,
    PLAY_OSCILLATING = 2
};

enum GgafDxPuppeteerStick {
    LEFT_HAND  = 0,
    RIGHT_HAND = 1
};


enum GgafDxAlign {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT,
};
enum GgafDxValign {
    VALIGN_TOP,
    VALIGN_MIDDLE,
    VALIGN_BOTTOM,
};



#define Obj_GgafDxScene                 (0x80000010)     //0b 10000000 00000000 00000000 00010000
#define Obj_GgafDxUniverse              (0x80000020)     //0b 10000000 00000000 00000000 00100000

#define Obj_GgafDxBaseActor             (0x80)           //0b 00000000 00000000 00000000 10000000
#define Obj_GgafDxGeometricActor        (0x100)          //0b 00000000 00000000 00000001 00000000
#define Obj_GgafDxDrawableActor         (0x200)          //0b 00000000 00000000 00000010 00000000
#define Obj_GgafDxMeshActor             (0x400)          //0b 00000000 00000000 00000100 00000000
#define Obj_GgafDxMeshSetActor          (0x800)          //0b 00000000 00000000 00001000 00000000
#define Obj_GgafDxMorphMeshActor        (0x1000)         //0b 00000000 00000000 00010000 00000000
#define Obj_GgafDxD3DXMeshActor         (0x2000)         //0b 00000000 00000000 00100000 00000000
#define Obj_GgafDxDynaD3DXMeshActor     (0x4000)         //0b 00000000 00000000 01000000 00000000
#define Obj_GgafDxD3DXAniMeshActor      (0x8000)         //0b 00000000 00000000 10000000 00000000
#define Obj_GgafDxSpriteMeshActor       (0x10000)        //0b 00000000 00000001 00000000 00000000
#define Obj_GgafDxSpriteMeshSetActor    (0x20000)        //0b 00000000 00000010 00000000 00000000
#define Obj_GgafDxCubeMapMeshActor      (0x40000)        //0b 00000000 00000100 00000000 00000000
#define Obj_GgafDxCubeMapMeshSetActor   (0x80000)        //0b 00000000 00001000 00000000 00000000
#define Obj_GgafDxCubeMapMorphMeshActor (0x100000)       //0b 00000000 00010000 00000000 00000000
#define Obj_GgafDxWorldBoundActor       (0x200000)       //0b 00000000 00100000 00000000 00000000
#define Obj_GgafDxSpriteActor           (0x400000)       //0b 00000000 01000000 00000000 00000000
#define Obj_GgafDxSpriteSetActor        (0x800000)       //0b 00000000 10000000 00000000 00000000
#define Obj_GgafDxBoardActor            (0x1000000)      //0b 00000001 00000000 00000000 00000000
#define Obj_GgafDxBoardSetActor         (0x2000000)      //0b 00000010 00000000 00000000 00000000
#define Obj_GgafDxPointSpriteActor      (0x4000000)      //0b 00000100 00000000 00000000 00000000
#define Obj_FormationActor        (0x8000000)      //0b 00001000 00000000 00000000 00000000
#undef P_GOD
#define P_GOD ((GgafDxCore::GgafDxGod*)GgafDxCore::GgafDxGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((GgafDxCore::GgafDxUniverse*)(P_GOD->_pUniverse))

namespace GgafDxCore {

class GgafDxCriticalException;
class GgafDxGod;
class GgafDxInput;
class GgafDxSound;

class GgafDxTextureConnection;
class GgafDxTextureManager;
class GgafDxModelConnection;
class GgafDxModelManager;
class GgafDxEffectConnection;
class GgafDxEffectManager;


class GgafDxAllocHierarchy;
class D3DXFRAME_WORLD;
class GgafDxAllocHierarchyWorldFrame;
class GgafDxWorldMatStack;

class GgafDxICubeMapActor;

class GgafDxBaseActor;
class GgafDxGeometricActor;
class GgafDxDrawableActor;
class GgafDxMeshActor;
class GgafDxMeshSetActor;
class GgafDxMorphMeshActor;
class GgafDxD3DXMeshActor;
class GgafDxDynaD3DXMeshActor;
class GgafDxD3DXAniMeshActor;

class GgafDxSpriteMeshActor;
class GgafDxSpriteMeshSetActor;
class GgafDxCubeMapMeshActor;
class GgafDxCubeMapMeshSetActor;
class GgafDxCubeMapMorphMeshActor;
class GgafDxWorldBoundActor;

class GgafDxAABActor;
class GgafDxAAPrismActor;
class GgafDxSphereActor;

class GgafDxSpriteActor;
class GgafDxSpriteSetActor;
class GgafDxCamera;
class GgafDxCameraViewPoint;
class GgafDxBoardActor;
class GgafDxBoardSetActor;
class GgafDxPointSpriteActor;

class GgafDxModel;
class GgafDxD3DXMeshModel;
class GgafDxD3DXAniMeshModel;
class GgafDxSpriteModel;
class GgafDxSpriteSetModel;
class GgafDxMeshModel;
class GgafDxMeshSetModel;
class GgafDxMorphMeshModel;
class GgafDxCubeMapMeshModel;
class GgafDxCubeMapMeshSetModel;
class GgafDxCubeMapMorphMeshModel;
class GgafDxWorldBoundModel;
class GgafDxBoardModel;
class GgafDxBoardSetModel;
class GgafDxPointSpriteModel;

class GgafDxEffect;
class GgafDxMeshEffect;
class GgafDxD3DXAniMeshEffect;
class GgafDxMeshSetEffect;
class GgafDxMorphMeshEffect;
class GgafDxCubeMapMeshEffect;
class GgafDxCubeMapMeshSetEffect;
class GgafDxCubeMapMorphMeshEffect;
class GgafDxWorldBoundEffect;
class GgafDxSpriteEffect;
class GgafDxSpriteSetEffect;
class GgafDxBoardEffect;
class GgafDxBoardSetEffect;
class GgafDxStringBoardActor;
class GgafDxStringSpriteActor;
class GgafDxPointSpriteEffect;

class GgafDxTexture;

class GgafDxScene;
class GgafDxUniverse;

class GgafDxUtil;
class GgafDxSphereRadiusVectors;
class GgafDxQuaternion;
class GgafDxCollisionArea;
class GgafDxCollisionPart;
class GgafDxProperties;
class GgafDxGeoElem;
class GgafDxGeoChain;
class GgafDxKurokoA;
class GgafDxKurokoB;
class GgafDxChecker;
class GgafDxScaler;
class GgafDxAlphaFader;
class GgafDxColorist;
class GgafDxMorpher;
class GgafDxSeTransmitter;
class GgafDxBgmPerformer;
class GgafDxAlphaCurtain;
class GgafDxTextureBlinker;
class GgafDxUvFlipper;
class GgafDxPuppeteer;
class GgafDxRectUV;

class GgafDxSe;
class GgafDxBgm;
class GgafDxSeConnection;
class GgafDxSeManager;
class GgafDxBgmConnection;
class GgafDxBgmManager;
class GgafDxSound;
class CWaveDecorder;

}

#include "jp/ggaf/dxcore/util/XFile/framework/frm_mesh.h"
#include "jp/ggaf/dxcore/util/XFile/framework/Frm_Tbuff.h"
#include "jp/ggaf/dxcore/util/XFile/ToolBox/IOModel_X.h"
#include "jp/ggaf/dxcore/util/XFile/ToolBox/IOTexture_Bmp.h"
#include "jp/ggaf/dxcore/util/XFile/ToolBox/TBox_Textures.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"

#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchy.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"
#include "jp/ggaf/dxcore/util/GgafDxWorldMatStack.h"

#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxBaseActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxD3DXMeshActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxDynaD3DXMeshActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxSpriteActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxSpriteSetActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxCamera.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardSetActor.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"

#include "jp/ggaf/dxcore/actor/ex/GgafDxAABActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPrismActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxSphereActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshSetActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxStringBoardActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxStringSpriteActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMeshActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMeshSetActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMorphMeshActor.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxWorldBoundActor.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteModel.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshSetModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMorphMeshModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxWorldBoundModel.h"

#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"

#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshSetEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMorphMeshEffect.h"
#include "jp/ggaf/dxcore/effect/ex/GgafDxWorldBoundEffect.h"

#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "jp/ggaf/dxcore/scene/GgafDxScene.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxSphereRadiusVectors.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/dxcore/util/GgafDxProperties.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoChain.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitter.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformer.h"
#include "jp/ggaf/dxcore/scene/supporter/GgafDxAlphaCurtain.h"

#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

#include "jp/ggaf/dxcore/model/GgafDxRectUV.h"

#include "jp/ggaf/dxcore/sound/CWaveDecorder.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"


#endif /*GGAFDXCOMMONHEADER_H_*/
