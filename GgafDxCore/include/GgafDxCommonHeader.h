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

#define GGAF_MAX_VOLUME (1000)
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

typedef uint_fast32_t pos_t;

//プリズム姿勢(位置)定数

#define POS_PRISM_XY_NN   (0x11) //0b 00010001
#define POS_PRISM_XY_NP   (0x12) //0b 00010010
#define POS_PRISM_XY_PN   (0x14) //0b 00010100
#define POS_PRISM_XY_PP   (0x18) //0b 00011000
#define POS_PRISM_YZ_NN   (0x21) //0b 00100001
#define POS_PRISM_YZ_NP   (0x22) //0b 00100010
#define POS_PRISM_YZ_PN   (0x24) //0b 00100100
#define POS_PRISM_YZ_PP   (0x28) //0b 00101000
#define POS_PRISM_ZX_NN   (0x41) //0b 01000001
#define POS_PRISM_ZX_NP   (0x42) //0b 01000010
#define POS_PRISM_ZX_PN   (0x44) //0b 01000100
#define POS_PRISM_ZX_PP   (0x48) //0b 01001000

//プリズムは、直方体をどの面から見て対角線に垂直にスライスされて出来上がった形かを示す
/** XY平面から見て対角線に垂直にスライスした形である */
#define POS_PRISM_XY_xx      (0x10) //0b 00010000
/** YZ平面から見て対角線に垂直にスライスした形である */
#define POS_PRISM_YZ_xx      (0x20) //0b 00100000
/** ZX平面から見て対角線に垂直にスライスした形である */
#define POS_PRISM_ZX_xx      (0x40) //0b 01000000

//スライスで出来るプリズム(４通り)の位置を、
//直角三角形の直角がある場所に注目し、
//平面座標の象限(軸座標の正負)で示す。
//n = negative(負), p = positive(正)
/** 直角がある方向は, (負, 負)である */
#define POS_PRISM_xx_NN      (0x1)  //0b 00000001
/** 直角がある方向は, (負, 正)である */
#define POS_PRISM_xx_NP      (0x2)  //0b 00000010
/** 直角がある方向は, (正, 負)である */
#define POS_PRISM_xx_PN      (0x4)  //0b 00000100
/** 直角がある方向は, (正, 正)である */
#define POS_PRISM_xx_PP      (0x8)  //0b 00001000

#define POS_PRISM_xx_xP (POS_PRISM_xx_NP | POS_PRISM_xx_PP)
#define POS_PRISM_xx_Px (POS_PRISM_xx_PN | POS_PRISM_xx_PP)

//2D直角三角形の当たり判定時に指定する定数
/** 直角がある方向は, (x, y) = (負, 負) 方向である */
#define POS_R_TRIANGLE_NN POS_PRISM_XY_NN
/** 直角がある方向は, (x, y) = (負, 正) 方向である */
#define POS_R_TRIANGLE_NP POS_PRISM_XY_NP
/** 直角がある方向は, (x, y) = (正, 負) 方向である */
#define POS_R_TRIANGLE_PN POS_PRISM_XY_PN
/** 直角がある方向は, (x, y) = (正, 正) 方向である */
#define POS_R_TRIANGLE_PP POS_PRISM_XY_PP

#define POS_R_TRIANGLE_xP POS_PRISM_xx_xP
#define POS_R_TRIANGLE_Px POS_PRISM_xx_Px

//直角の頂点の位置をネガポジ
//                  xyz
#define POS_PYRAMID_NNN   (0x8000) //0b  10000000 00000000
#define POS_PYRAMID_NNP   (0x8100) //0b  10000001 00000000
#define POS_PYRAMID_NPN   (0x8200) //0b  10000010 00000000
#define POS_PYRAMID_NPP   (0x8300) //0b  10000011 00000000
#define POS_PYRAMID_PNN   (0x8400) //0b  10000100 00000000
#define POS_PYRAMID_PNP   (0x8500) //0b  10000101 00000000
#define POS_PYRAMID_PPN   (0x8600) //0b  10000110 00000000
#define POS_PYRAMID_PPP   (0x8700) //0b  10000111 00000000

#define POS_PYRAMID_xxP   (0x100)  //0b  00000001 00000000
#define POS_PYRAMID_xPx   (0x200)  //0b  00000010 00000000
#define POS_PYRAMID_xPP   (0x300)  //0b  00000011 00000000
#define POS_PYRAMID_Pxx   (0x400)  //0b  00000100 00000000
#define POS_PYRAMID_PxP   (0x500)  //0b  00000101 00000000
#define POS_PYRAMID_PPx   (0x600)  //0b  00000110 00000000


//DirectXの3D空間の座標単位１に対しての原点付近の画面px相当数（画面高さ(px)などを、PX_UNITで割ると3D空間の座標単位１になる）
#define PX_UNIT (10)
//原点付近の画面上の１px相当に対してのPG内での座標単位の比率（PG内での座標単位を LEN_UNITで割ると3D空間のpxになる）
#define LEN_UNIT (1000)
#define PI  (3.14159265358979323846)
#define PI2 (6.28318530717958647692)

//シェーダー2.0の限界のモーフターゲットは6個だった
#define MAX_MORPH_TARGET 6

/** アプリケーション座標単位 (目安： 1 coord  =  0.001 pixcoord  =  0.0001 dxcoord  ) */
typedef int_fast32_t coord;
/** アプリケーション座標単位系の速度 */
typedef int_fast32_t velo;
/**  アプリケーション座標単位系の加速度 */
typedef int_fast32_t acce;
/**  アプリケーション座標単位系の躍度(TODO:現在未使用) */
typedef int_fast32_t jerk;

/** ピクセル座標単位 (目安： 1 pixcoord  =  1000 coord   =  0.1 dxcoord ) */
typedef int_fast32_t pixcoord;
/** DirectX座標単位  (目安： 1 dxcoord   =  10 pixcoord  =  10000 coord ) */
typedef float dxcoord;

/** アプリケーションスケール単位 (目安： 1 scale  =  0.001 倍) */
typedef int_fast32_t scale;
typedef int_fast32_t scalevelo;
typedef int_fast32_t scaleacce;
/** アプリケーション角度単位 (目安： 1 angle  =  0.001 度) */
typedef int_fast32_t angle;
/** アプリケーション角度単位系の角速度 */
typedef int_fast32_t angvelo;
/** アプリケーション角度単位系の角加速度 */
typedef int_fast32_t angacce;
/** アプリケーション角度単位系の角加加速度 */
typedef int_fast32_t angjerk;

/** アプリケーション内部の角度精度単位(フレームワーク用) */
typedef int_fast32_t s_ang;

/** 軸型(AXIS_X / AXIS_Y / AXIS_Z) */
enum {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_Z
};

typedef int_fast32_t axis;

#define MAX_SCALE (2147483647)

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

/** アプリの座標 → DirectX座標 変換 */
#define C_DX(X)  ( (dxcoord)((X) * (1.0 / (LEN_UNIT * PX_UNIT))) )
/** DirectX座標 → アプリの座標 変換 */
#define DX_C(X)  ( (coord)((X) * (LEN_UNIT * PX_UNIT)) )
/** DirectX座標 → ピクセル座標(初期カメラ位置の時) 変換 */
#define DX_PX(X) ( (pixcoord)((X) * PX_UNIT) )
/** ピクセル座標(初期カメラ位置の時) →DirectX座標 変換 */
#define PX_DX(X) ( (dxcoord)((X) * (1.0 / PX_UNIT)) )
/** アプリの座標 → ピクセル座標(初期カメラ位置の時) 変換 */
#define C_PX(X)  ( (pixcoord)((X) * (1.0 / LEN_UNIT)) )
/** ピクセル座標(初期カメラ位置の時) → アプリの座標 変換 */
#define PX_C(X)  ( (coord)((X) * LEN_UNIT) )

/** アプリのアングル値→度数法角度 変換 */
#define ANG_D(X) ((int)((X) * 0.001))
/** 度数法角度→アプリのアングル値 変換 */
#define D_ANG(X) ((angle)((X) * 1000))
///** アプリのアングル値→ラジアン 変換 */
#define ANG_RAD(X) (GgafDxCore::GgafDxUtil::RAD[(int)((X) * (1.0 / SANG_RATE))])
/** アプリのアングル値→正弦 変換 */
#define ANG_SIN(X) (GgafDxCore::GgafDxUtil::SIN[(int)((X) * (1.0 / SANG_RATE))])
/** アプリのアングル値→余弦 変換 */
#define ANG_COS(X) (GgafDxCore::GgafDxUtil::COS[(int)((X) * (1.0 / SANG_RATE))])
/** アプリのスケール値 → 拡大率 変換 */
#define SC_R(X) ( (float)((X) * (1.0 / LEN_UNIT)) )
/** 拡大率 → アプリのスケール値 変換 */
#define R_SC(X) ( (scale)((X) * LEN_UNIT) )

enum GgafDxUvFlippingMethod {
    FLIP_ORDER_LOOP,
    FLIP_REVERSE_LOOP,
    FLIP_OSCILLATE_LOOP,
    FLIP_ORDER_NOLOOP,
    FLIP_REVERSE_NOLOOP,
    FLIP_CUSTOMIZED_LOOP,
    FLIP_CUSTOMIZED_NOLOOP,
    NOT_ANIMATED
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


#define Obj_GgafDxScene        ((0x10ULL) | Obj_SceneBit)  //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00010000
#define Obj_GgafDxSpacetime    ((0x20ULL) | Obj_SceneBit)  //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00100000

#define Obj_GgafDxBaseActor                         (0x100ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000001 00000000
#define Obj_GgafDxSceneMediator                     (0x200ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000010 00000000
#define Obj_GgafDxGeometricActor                    (0x400ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000100 00000000
#define Obj_GgafDxFigureActor                       (0x800ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00001000 00000000
#define Obj_GgafDxMeshActor                        (0x1000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00010000 00000000
#define Obj_GgafDxMeshSetActor                     (0x2000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00100000 00000000
#define Obj_GgafDxMorphMeshActor                   (0x4000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 01000000 00000000
#define Obj_GgafDxD3DXMeshActor                    (0x8000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 10000000 00000000
#define Obj_GgafDxDynaD3DXMeshActor               (0x10000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000001 00000000 00000000
#define Obj_GgafDxD3DXAniMeshActor                (0x20000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000010 00000000 00000000
#define Obj_GgafDxSpriteMeshActor                 (0x40000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000100 00000000 00000000
#define Obj_GgafDxSpriteMeshSetActor              (0x80000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00001000 00000000 00000000
#define Obj_GgafDxCubeMapMeshActor               (0x100000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00010000 00000000 00000000
#define Obj_GgafDxCubeMapMeshSetActor            (0x200000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00100000 00000000 00000000
#define Obj_GgafDxCubeMapMorphMeshActor          (0x400000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 01000000 00000000 00000000
#define Obj_GgafDxWorldBoundActor                (0x800000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 10000000 00000000 00000000
#define Obj_GgafDxSpriteActor                   (0x1000000ULL)  //0b 00000000 00000000 00000000 00000000 00000001 00000000 00000000 00000000
#define Obj_GgafDxSpriteSetActor                (0x2000000ULL)  //0b 00000000 00000000 00000000 00000000 00000010 00000000 00000000 00000000
#define Obj_GgafDxBoardActor                    (0x4000000ULL)  //0b 00000000 00000000 00000000 00000000 00000100 00000000 00000000 00000000
#define Obj_GgafDxBoardSetActor                 (0x8000000ULL)  //0b 00000000 00000000 00000000 00000000 00001000 00000000 00000000 00000000
#define Obj_GgafDxPointSpriteActor             (0x10000000ULL)  //0b 00000000 00000000 00000000 00000000 00010000 00000000 00000000 00000000
#define Obj_GgafDxMassActor                    (0x20000000ULL)  //0b 00000000 00000000 00000000 00000000 00100000 00000000 00000000 00000000
#define Obj_GgafDxMassMeshActor                (0x40000000ULL)  //0b 00000000 00000000 00000000 00000000 01000000 00000000 00000000 00000000
#define Obj_GgafDxMassBoardActor               (0x80000000ULL)  //0b 00000000 00000000 00000000 00000000 10000000 00000000 00000000 00000000
#define Obj_GgafDxMassSpriteActor             (0x100000000ULL)  //0b 00000000 00000000 00000000 00000001 00000000 00000000 00000000 00000000
#define Obj_GgafDxMassMorphMeshActor          (0x200000000ULL)  //0b 00000000 00000000 00000000 00000010 00000000 00000000 00000000 00000000
#define Obj_GgafDxMassPointSpriteActor        (0x400000000ULL)  //0b 00000000 00000000 00000000 00000100 00000000 00000000 00000000 00000000
#define Obj_GgafDxPointSpriteSetActor         (0x800000000ULL)  //0b 00000000 00000000 00000000 00001000 00000000 00000000 00000000 00000000
#define Obj_GgafDxFramedBoardActor           (0x1000000000ULL)  //0b 00000000 00000000 00000000 00010000 00000000 00000000 00000000 00000000
#define Obj_GgafDxRegularPolygonSpriteActor  (0x2000000000ULL)  //0b 00000000 00000000 00000000 00100000 00000000 00000000 00000000 00000000

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
//前方宣言(forward declaration)
namespace Frm {
class Model3D;
class Mesh;
}

//前方宣言(forward declaration)
namespace GgafDxCore {

class GgafDxCriticalException;
class GgafDxConfig;
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
class GgafDxSceneMediator;
class GgafDxGeometricActor;
class GgafDxFigureActor;
class GgafDxMassActor;
class GgafDxMeshActor;
class GgafDxMeshSetActor;
class GgafDxMassMeshActor;
class GgafDxMorphMeshActor;
class GgafDxMassMorphMeshActor;
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
class GgafDxAAPyramidActor;
class GgafDxSphereActor;
class GgafDxSpriteActor;
class GgafDxSpriteSetActor;
class GgafDxMassSpriteActor;
class GgafDxCamera;
class GgafDxCameraViewPoint;
class GgafDxCameraUpVector;
class GgafDxBoardActor;
class GgafDxBoardSetActor;
class GgafDxMassBoardActor;
class GgafDxPointSpriteActor;
class GgafDxMassPointSpriteActor;
class GgafDxPointSpriteSetActor;
class GgafDxFramedBoardActor;
class GgafDxRegularPolygonSpriteActor;

class GgafDxModel;
class GgafDxMassModel;
class GgafDxD3DXMeshModel;
class GgafDxD3DXAniMeshModel;
class GgafDxSpriteModel;
class GgafDxSpriteSetModel;
class GgafDxMassSpriteModel;
class GgafDxMeshModel;
class GgafDxMeshSetModel;
class GgafDxMassMeshModel;
class GgafDxMorphMeshModel;
class GgafDxMassMorphMeshModel;
class GgafDxCubeMapMeshModel;
class GgafDxCubeMapMeshSetModel;
class GgafDxCubeMapMorphMeshModel;
class GgafDxWorldBoundModel;
class GgafDxBoardModel;
class GgafDxBoardSetModel;
class GgafDxMassBoardModel;
class GgafDxPointSpriteModel;
class GgafDxMassPointSpriteModel;
class GgafDxPointSpriteSetModel;
class GgafDxFramedBoardModel;
class GgafDxRegularPolygonSpriteModel;

class GgafDxEffect;
class GgafDxMassEffect;
class GgafDxMeshEffect;
class GgafDxD3DXAniMeshEffect;
class GgafDxMeshSetEffect;
class GgafDxMassMeshEffect;
class GgafDxMorphMeshEffect;
class GgafDxMassMorphMeshEffect;
class GgafDxCubeMapMeshEffect;
class GgafDxCubeMapMeshSetEffect;
class GgafDxCubeMapMorphMeshEffect;
class GgafDxWorldBoundEffect;
class GgafDxSpriteEffect;
class GgafDxSpriteSetEffect;
class GgafDxMassSpriteEffect;
class GgafDxBoardEffect;
class GgafDxBoardSetEffect;
class GgafDxMassBoardEffect;
class GgafDxPointSpriteEffect;
class GgafDxMassPointSpriteEffect;
class GgafDxPointSpriteSetEffect;
class GgafDxFramedBoardEffect;
class GgafDxRegularPolygonSpriteEffect;

class GgafDxTexture;

class GgafDxScene;
class GgafDxSpacetime;

class GgafDxUtil;
class GgafDxSphereRadiusVectors;
class GgafDxCollisionArea;
class GgafDxCollisionPart;
class GgafDxGeoElem;
class GgafDxKuroko;
class GgafDxKurokoMvAssistant;
class GgafDxKurokoFaceAngAssistant;
class GgafDxKurokoMvAngAssistant;
class GgafDxTrucker;
class GgafDxTruckerAssistantA;
class GgafDxChecker;
class GgafDxScaler;
class GgafDxAlphaFader;
class GgafDxColorist;
class GgafDxSeTransmitter;
class GgafDxSeTransmitterForActor;
class GgafDxBgmConductor;
class GgafDxAlphaCurtain;
class GgafDxSceneCurtain;
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

#endif /*GGAFDXCOMMONHEADER_H_*/
