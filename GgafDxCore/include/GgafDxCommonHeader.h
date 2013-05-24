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




/** 回転方法定数、近い方向に回転 */
#define TURN_CLOSE_TO 0
/** 回転方法定数、遠い方向に回転 */
#define TURN_ANTICLOSE_TO 2
/** 回転方法定数、時計回りに回転 */
#define TURN_CLOCKWISE (-1)
/** 回転方法定数、反時計回りに回転 */
#define TURN_COUNTERCLOCKWISE 1
/** 回転方法定数、どちらかの回転（いずれの回転でも） */
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
#define PI  (3.14159265358979323846)
#define PI2 (6.28318530717958647692)
//#define MAX_DRAW_DEPTH_LEVEL 1000
#define MAX_DRAW_DEPTH_LEVEL 500
#define DRAW_DEPTH_LEVEL_WORLDBOUND (MAX_DRAW_DEPTH_LEVEL)
#define MAX_SE_AT_ONCE 15
#define MAX_SE_DELAY 240


//シェーダー2.0の限界のモーフターゲットは6個だった
#define MAX_MORPH_TARGET 6

/** アプリケーション座標単位 (目安： 1 coord  =  0.001 pixcoord  =  0.00001 dxcoord  ) */
typedef int coord;
/** アプリケーション座標単位系の速度 */
typedef int velo;
/**  アプリケーション座標単位系の加速度 */
typedef int acce;
/**  アプリケーション座標単位系の躍度(TODO:現在未使用) */
typedef int jerk;

/** ピクセル座標単位 (目安： 1 pixcoord  =  1000 coord   =  0.1 dxcoord ) */
typedef int pixcoord;
/** DirectX座標単位  (目安： 1 dxcoord   =  10 pixcoord  =  10000 coord ) */
typedef float dxcoord;

/** アプリケーションスケール単位 (目安： 1 scale  =  0.001 倍) */
typedef int scale;

/** アプリケーション角度単位 (目安： 1 angle  =  0.001 度) */
typedef int angle;
/** アプリケーション角度単位系の角速度 */
typedef int angvelo;
/** アプリケーション角度単位系の角加速度 */
typedef int angacce;
/** アプリケーション角度単位系の角加加速度 */
typedef int angjerk;

/** アプリケーション内部の角度精度単位(フレームワーク用) */
typedef int s_ang;

/** 軸型(AXIS_X / AXIS_Y / AXIS_Z) */
enum GgafDxAxis {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_Z
};

typedef GgafDxAxis axis;


/** アプリの座標 → DirectX座標 変換 */
#define C_DX(X)  ( ((dxcoord)(X)) / (LEN_UNIT * PX_UNIT) )
/** DirectX座標 → アプリの座標 変換 */
#define DX_C(X)  ( (coord)((X) * (LEN_UNIT * PX_UNIT)) )
/** DirectX座標 → ピクセル座標(初期カメラ位置の時) 変換 */
#define DX_PX(X) ( (pixcoord)((X) * PX_UNIT) )
/** ピクセル座標(初期カメラ位置の時) →DirectX座標 変換 */
#define PX_DX(X) ( ((dxcoord)(X)) / PX_UNIT )
/** アプリの座標 → ピクセル座標(初期カメラ位置の時) 変換 */
#define C_PX(X)  ( (pixcoord)((X) / LEN_UNIT) )
/** ピクセル座標(初期カメラ位置の時) → アプリの座標 変換 */
#define PX_C(X)  ( (coord)((X) * LEN_UNIT) )

/** アプリのアングル値→度数法角度 変換 */
#define ANG_D(X) ((int)((X) / 1000))
/** 度数法角度→アプリのアングル値 変換 */
#define D_ANG(X) ((angle)((X) * 1000))
///** アプリのアングル値→ラジアン 変換 */
//#define ANG_RAD(X) (GgafDxCore::GgafDxUtil::RAD[(X) / SANG_RATE])
/** アプリのアングル値→正弦 変換 */
#define ANG_SIN(X) (GgafDxCore::GgafDxUtil::SIN[(int)((X) / SANG_RATE)])
/** アプリのアングル値→余弦 変換 */
#define ANG_COS(X) (GgafDxCore::GgafDxUtil::COS[(int)((X) / SANG_RATE)])
/** アプリのスケール値 → 拡大率 変換 */
#define SC_R(X) ( ((float)(X)) / LEN_UNIT )
/** 拡大率 → アプリのスケール値 変換 */
#define R_SC(X) ( (scale)((X) * LEN_UNIT) )

/** 度数法 0 度に対応するアプリのアングル値定数 */
#define D0ANG   (0)
/** 度数法 360 度に対応するアプリのアングル値定数 */
#define D360ANG (360000)
/** 度数法 45 度に対応するアプリのアングル値定数 */
#define D45ANG  (45000)
/** 度数法 90 度に対応するアプリのアングル値定数 */
#define D90ANG  (90000)
/** 度数法 135 度に対応するアプリのアングル値定数 */
#define D135ANG (135000)
/** 度数法 180 度に対応するアプリのアングル値定数 */
#define D180ANG (180000)
/** 度数法 255 度に対応するアプリのアングル値定数 */
#define D255ANG (225000)
/** 度数法 270 度に対応するアプリのアングル値定数 */
#define D270ANG (270000)
/** 度数法 315 度に対応するアプリのアングル値定数 */
#define D315ANG (315000)
/** ラジアンのπ に対応するアプリのアングル値定数 */
#define PI_Ang (180000)

#define D0SANG   (0)
#define D360SANG (3600)
#define D45SANG  (450)
#define D90SANG  (900)
#define D135SANG (1350)
#define D180SANG (1800)
#define D225SANG (2250)
#define D270SANG (2700)
#define D315SANG (3150)
/** 内部精度角度単位 → アプリケーション角度単位 への倍率 */
#define SANG_RATE (100)


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

#define Obj_GgafDxBaseActor             (0x100)          //0b 00000000 00000000 00000001 00000000
#define Obj_GgafDxGeometricActor        (0x200)          //0b 00000000 00000000 00000010 00000000
#define Obj_GgafDxDrawableActor         (0x400)          //0b 00000000 00000000 00000100 00000000
#define Obj_GgafDxMeshActor             (0x800)          //0b 00000000 00000000 00001000 00000000
#define Obj_GgafDxMeshSetActor          (0x1000)         //0b 00000000 00000000 00010000 00000000
#define Obj_GgafDxMorphMeshActor        (0x2000)         //0b 00000000 00000000 00100000 00000000
#define Obj_GgafDxD3DXMeshActor         (0x4000)         //0b 00000000 00000000 01000000 00000000
#define Obj_GgafDxDynaD3DXMeshActor     (0x8000)         //0b 00000000 00000000 10000000 00000000
#define Obj_GgafDxD3DXAniMeshActor      (0x10000)        //0b 00000000 00000001 00000000 00000000
#define Obj_GgafDxSpriteMeshActor       (0x20000)        //0b 00000000 00000010 00000000 00000000
#define Obj_GgafDxSpriteMeshSetActor    (0x40000)        //0b 00000000 00000100 00000000 00000000
#define Obj_GgafDxCubeMapMeshActor      (0x80000)        //0b 00000000 00001000 00000000 00000000
#define Obj_GgafDxCubeMapMeshSetActor   (0x100000)       //0b 00000000 00010000 00000000 00000000
#define Obj_GgafDxCubeMapMorphMeshActor (0x200000)       //0b 00000000 00100000 00000000 00000000
#define Obj_GgafDxWorldBoundActor       (0x400000)       //0b 00000000 01000000 00000000 00000000
#define Obj_GgafDxSpriteActor           (0x800000)       //0b 00000000 10000000 00000000 00000000
#define Obj_GgafDxSpriteSetActor        (0x1000000)      //0b 00000001 00000000 00000000 00000000
#define Obj_GgafDxBoardActor            (0x2000000)      //0b 00000010 00000000 00000000 00000000
#define Obj_GgafDxBoardSetActor         (0x4000000)      //0b 00000100 00000000 00000000 00000000
#define Obj_GgafDxPointSpriteActor      (0x8000000)      //0b 00001000 00000000 00000000 00000000

#undef P_GOD
#define P_GOD ((GgafDxCore::GgafDxGod*)GgafDxCore::GgafDxGod::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((GgafDxCore::GgafDxUniverse*)(P_GOD->_pUniverse))



//前方宣言(forward declaration)
namespace IkdLib {
//「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html
// の主、Ikd さん作のoggファイル再生ライブラリ
class PCMPlayer;
class OggVorbisResource;
class PCMDecoder;
class OggDecoder;
class OggVorbisFile;
class OggVorbisMemory;
}
//#include "jp/ggaf/dxcore/sound/IkdLib/PCMPlayer.h"
//#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisResource.h"
//#include "jp/ggaf/dxcore/sound/IkdLib/PCMDecoder.h"
//#include "jp/ggaf/dxcore/sound/IkdLib/OggDecoder.h"
//#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisFile.h"
//#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisMemory.h"

//前方宣言(forward declaration)
namespace Frm {

class Model3D;
class Mesh;

}

//前方宣言(forward declaration)
namespace GgafDxCore {

class GgafDxCriticalException;
class GgafDxProperties;
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
class GgafDxIBumpMapActor;

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
class GgafDxAgainstWay;
class GgafDxSphereRadiusVectors;
class GgafDxQuaternion;
class GgafDxCollisionArea;
class GgafDxCollisionPart;
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
class GgafDxSeTransmitterForActor;
class GgafDxBgmPerformer;
class GgafDxAlphaCurtain;
class GgafDxBgmPerformerForScene;
class GgafDxTextureBlinker;
class GgafDxUvFlipper;
class GgafDxPuppeteer;

class GgafDxSe;
class GgafDxBgm;
class GgafDxSeConnection;
class GgafDxSeManager;
class GgafDxBgmConnection;
class GgafDxBgmManager;
class GgafDxSound;
class CWaveDecorder;

}


//#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
//#include "jp/ggaf/dxcore/GgafDxProperties.h"
//#include "jp/ggaf/dxcore/GgafDxGod.h"
//#include "jp/ggaf/dxcore/util/GgafDxInput.h"
//#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
//#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
//#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"
//#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
//#include "jp/ggaf/dxcore/manager/GgafDxEffectConnection.h"
//#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
//
//#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchy.h"
//#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"
//#include "jp/ggaf/dxcore/util/GgafDxWorldMatStack.h"
//
//#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"
//#include "jp/ggaf/dxcore/actor/interface/GgafDxIBumpMapActor.h"
//
//#include "jp/ggaf/dxcore/actor/GgafDxBaseActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
//
//#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxD3DXMeshActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxDynaD3DXMeshActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxSpriteActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxSpriteSetActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxCamera.h"
//#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
//#include "jp/ggaf/dxcore/actor/GgafDxBoardActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxBoardSetActor.h"
//#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"
//
//#include "jp/ggaf/dxcore/actor/ex/GgafDxAABActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxAAPrismActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxSphereActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxSpriteMeshSetActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxStringBoardActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxStringSpriteActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMeshActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMeshSetActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxCubeMapMorphMeshActor.h"
//#include "jp/ggaf/dxcore/actor/ex/GgafDxWorldBoundActor.h"
//
//#include "jp/ggaf/dxcore/model/GgafDxModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxD3DXMeshModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxSpriteModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
//#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"
//#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshModel.h"
//#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshSetModel.h"
//#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMorphMeshModel.h"
//#include "jp/ggaf/dxcore/model/ex/GgafDxWorldBoundModel.h"
//
//#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
//
//#include "jp/ggaf/dxcore/effect/GgafDxD3DXAniMeshEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxSpriteEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
//#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
//#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshEffect.h"
//#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMeshSetEffect.h"
//#include "jp/ggaf/dxcore/effect/ex/GgafDxCubeMapMorphMeshEffect.h"
//#include "jp/ggaf/dxcore/effect/ex/GgafDxWorldBoundEffect.h"
//
//#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
//
//#include "jp/ggaf/dxcore/scene/GgafDxScene.h"
//#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
//
//
//#include "jp/ggaf/dxcore/util/GgafDxAgainstWay.h"
//#include "jp/ggaf/dxcore/util/GgafDxSphereRadiusVectors.h"
//#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
//#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
//#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
//#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"
//#include "jp/ggaf/dxcore/util/GgafDxGeoChain.h"
//#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
//
//#include "jp/ggaf/dxcore/sound/CWaveDecorder.h"
//#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
//#include "jp/ggaf/dxcore/sound/GgafDxBgm.h"
//#include "jp/ggaf/dxcore/sound/GgafDxBgmPerformer.h"
//#include "jp/ggaf/dxcore/sound/GgafDxSeTransmitter.h"
//
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
//#include "jp/ggaf/dxcore/actor/supporter/GgafDxPuppeteer.h"
//
//#include "jp/ggaf/dxcore/scene/supporter/GgafDxAlphaCurtain.h"
//#include "jp/ggaf/dxcore/scene/supporter/GgafDxBgmPerformerForScene.h"
//
//#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
//
//#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"
//#include "jp/ggaf/dxcore/manager/GgafDxSeManager.h"
//#include "jp/ggaf/dxcore/manager/GgafDxBgmConnection.h"
//#include "jp/ggaf/dxcore/manager/GgafDxBgmManager.h"
//#include "jp/ggaf/dxcore/sound/GgafDxSound.h"


#endif /*GGAFDXCOMMONHEADER_H_*/
