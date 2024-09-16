#ifndef GGAFDXCOMMONHEADER_H_
#define GGAFDXCOMMONHEADER_H_
#include "jp/ggaf/GgafCommonHeader.h"

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

#define Obj_GgafDx_Scene        ((0x10ULL) | Obj_SceneBit)  //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00010000
#define Obj_GgafDx_Spacetime    ((0x20ULL) | Obj_SceneBit)  //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00100000

//#define Obj_GgafDx_BaseActor                         (0x100ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000001 00000000
#define Obj_GgafDx_SceneChief                     (0x200ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000010 00000000
#define Obj_GgafDx_GeometricActor                    (0x400ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000100 00000000
#define Obj_GgafDx_FigureActor                       (0x800ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00001000 00000000
#define Obj_GgafDx_IAlignAbleActor                  (0x1000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00010000 00000000
#define Obj_GgafDx_MeshActor                        (0x2000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00100000 00000000
#define Obj_GgafDx_MeshSetActor                     (0x4000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 01000000 00000000
#define Obj_GgafDx_MorphMeshActor                   (0x8000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 10000000 00000000
#define Obj_GgafDx_D3DXMeshActor                   (0x10000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000001 00000000 00000000
#define Obj_GgafDx_DynaD3DXMeshActor               (0x20000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000010 00000000 00000000
#define Obj_GgafDx_D3DXAniMeshActor                (0x40000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000100 00000000 00000000
#define Obj_GgafDx_SpriteMeshActor                 (0x80000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00001000 00000000 00000000
#define Obj_GgafDx_SpriteMeshSetActor             (0x100000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00010000 00000000 00000000
#define Obj_GgafDx_CubeMapMeshActor               (0x200000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00100000 00000000 00000000
#define Obj_GgafDx_CubeMapMeshSetActor            (0x400000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 01000000 00000000 00000000
#define Obj_GgafDx_CubeMapMorphMeshActor          (0x800000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 10000000 00000000 00000000
#define Obj_GgafDx_WorldBoundActor               (0x1000000ULL)  //0b 00000000 00000000 00000000 00000000 00000001 00000000 00000000 00000000
#define Obj_GgafDx_SpriteActor                   (0x2000000ULL)  //0b 00000000 00000000 00000000 00000000 00000010 00000000 00000000 00000000
#define Obj_GgafDx_SpriteSetActor                (0x4000000ULL)  //0b 00000000 00000000 00000000 00000000 00000100 00000000 00000000 00000000
#define Obj_GgafDx_BoardActor                    (0x8000000ULL)  //0b 00000000 00000000 00000000 00000000 00001000 00000000 00000000 00000000
#define Obj_GgafDx_BoardSetActor                (0x10000000ULL)  //0b 00000000 00000000 00000000 00000000 00010000 00000000 00000000 00000000
#define Obj_GgafDx_PointSpriteActor             (0x20000000ULL)  //0b 00000000 00000000 00000000 00000000 00100000 00000000 00000000 00000000
#define Obj_GgafDx_MassActor                    (0x40000000ULL)  //0b 00000000 00000000 00000000 00000000 01000000 00000000 00000000 00000000
#define Obj_GgafDx_MassMeshActor                (0x80000000ULL)  //0b 00000000 00000000 00000000 00000000 10000000 00000000 00000000 00000000
#define Obj_GgafDx_MassBoardActor              (0x100000000ULL)  //0b 00000000 00000000 00000000 00000001 00000000 00000000 00000000 00000000
#define Obj_GgafDx_MassSpriteActor             (0x200000000ULL)  //0b 00000000 00000000 00000000 00000010 00000000 00000000 00000000 00000000
#define Obj_GgafDx_MassMorphMeshActor          (0x400000000ULL)  //0b 00000000 00000000 00000000 00000100 00000000 00000000 00000000 00000000
#define Obj_GgafDx_MassPointSpriteActor        (0x800000000ULL)  //0b 00000000 00000000 00000000 00001000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_PointSpriteSetActor        (0x1000000000ULL)  //0b 00000000 00000000 00000000 00010000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_FramedBoardActor           (0x2000000000ULL)  //0b 00000000 00000000 00000000 00100000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonSpriteActor  (0x4000000000ULL)  //0b 00000000 00000000 00000000 01000000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonBoardActor   (0x8000000000ULL)  //0b 00000000 00000000 00000000 10000000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_BoneAniMeshActor          (0x10000000000ULL)  //0b 00000000 00000000 00000001 00000000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_SkinAniMeshActor          (0x20000000000ULL)  //0b 00000000 00000000 00000010 00000000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_FramedSpriteActor         (0x40000000000ULL)  //0b 00000000 00000000 00000100 00000000 00000000 00000000 00000000 00000000


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

//AABBプリズム姿勢(位置)定数
//＜例＞
//POS_PRISM_YZ_NN
//＜意味＞
//"POS_PRISM_" + どの平面にスライスを入れるか + "_" + スライスの仕方
//[どの平面にスライスを入れるか]
//XY ・・・ AABのXY平面に垂直にスライス
//YZ ・・・ AABのYZ平面に垂直にスライス
//ZX ・・・ AABのZX平面に垂直にスライス
//[スライスの仕方]
// n(negative)は負方向、p(positive)は正方向、という意味を持たしている
//nn ・・・ 直角三角形の直角の部分が先の平面座標系の (負方向, 負方向) と言う意味
//np ・・・ 直角三角形の直角の部分が先の平面座標系の (負方向, 正方向) と言う意味
//pn ・・・ 直角三角形の直角の部分が先の平面座標系の (正方向, 負方向) と言う意味
//pp ・・・ 直角三角形の直角の部分が先の平面座標系の (正方向, 正方向) と言う意味
#define POS_PRISM_XY_NN   (0x11) //!< プリズムの3直角の辺の位置は、-X, -Y 方向 （0b 00010001)
#define POS_PRISM_XY_NP   (0x12) //!< プリズムの3直角の辺の位置は、-X, +Y 方向 （0b 00010010)
#define POS_PRISM_XY_PN   (0x14) //!< プリズムの3直角の辺の位置は、+X, -Y 方向 （0b 00010100)
#define POS_PRISM_XY_PP   (0x18) //!< プリズムの3直角の辺の位置は、+X, +Y 方向 （0b 00011000)
#define POS_PRISM_YZ_NN   (0x21) //!< プリズムの3直角の辺の位置は、-Y, -Z 方向 （0b 00100001)
#define POS_PRISM_YZ_NP   (0x22) //!< プリズムの3直角の辺の位置は、-Y, +Z 方向 （0b 00100010)
#define POS_PRISM_YZ_PN   (0x24) //!< プリズムの3直角の辺の位置は、+Y, -Z 方向 （0b 00100100)
#define POS_PRISM_YZ_PP   (0x28) //!< プリズムの3直角の辺の位置は、+Y, +Z 方向 （0b 00101000)
#define POS_PRISM_ZX_NN   (0x41) //!< プリズムの3直角の辺の位置は、-Z, -X 方向 （0b 01000001)
#define POS_PRISM_ZX_NP   (0x42) //!< プリズムの3直角の辺の位置は、-Z, +X 方向 （0b 01000010)
#define POS_PRISM_ZX_PN   (0x44) //!< プリズムの3直角の辺の位置は、+Z, -X 方向 （0b 01000100)
#define POS_PRISM_ZX_PP   (0x48) //!< プリズムの3直角の辺の位置は、+Z, +X 方向 （0b 01001000)

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

//AABBピラミッド姿勢(位置)定数
//直角の頂点の位置をネガポジ
//＜例＞
//POS_PYRAMID_NPN
//＜意味＞
//"POS_PYRAMID_" + どの頂点が３直角の頂点か
//スライスされる前の立方体が原点にあったとして、
//スライスされて出来上がった直角三角柱の３直角の頂点の位置を表している。
//n(negative)は負方向、p(positive)は正方向、という意味を持たしている
//POS_PYRAMID_NPN の "npn" の３文字の部分は、
//１文字目はX軸の正負,２文字目はY軸の正負、３文字目はZ軸の正負
//を表し、例の "npn" は (x, y, z) = (-, +, -) の象限に３直角の頂点があるよ
//という意味
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
typedef uint_fast32_t ucoord;
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
#define ANG_RAD(X) (GgafDx::Util::RAD[(int)((X) * 0.1)])
/** アプリのアングル値→正弦 変換 */
#define ANG_SIN(X) (GgafDx::Util::SIN[(int)((X) * 0.1)])
/** アプリのアングル値→余弦 変換 */
#define ANG_COS(X) (GgafDx::Util::COS[(int)((X) * 0.1)])
/** アプリのスケール値 → 拡大率 変換 */
#define SC_R(X) ( (float)((X) * (1.0 / LEN_UNIT)) )
/** 拡大率 → アプリのスケール値 変換 */
#define R_SC(X) ( (scale)((X) * LEN_UNIT) )

enum UvFlippingMethod {
    FLIP_ORDER_LOOP,
    FLIP_REVERSE_LOOP,
    FLIP_OSCILLATE_LOOP,
    FLIP_ORDER_NOLOOP,
    FLIP_REVERSE_NOLOOP,
    FLIP_CUSTOMIZED_LOOP,
    FLIP_CUSTOMIZED_NOLOOP,
    NOT_ANIMATED
};

enum PuppeteerMethod {
    NO_CHENGE = 0,
    PLAY_LOOPING = 1,
    //PLAY_OSCILLATING = 2
};

enum PuppeteerStick {
    MAIN  = 0,
    SUB = 1
};


enum Align {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT,
};
enum Valign {
    VALIGN_TOP,
    VALIGN_MIDDLE,
    VALIGN_BOTTOM,
};

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
namespace GgafDx {

class CriticalException;
class Config;
class Caretaker;
class Input;
class Sound;

class TextureConnection;
class TextureManager;
class ModelConnection;
class ModelManager;
class EffectConnection;
class EffectManager;

class AllocHierarchy;
class BoneAniMeshAllocHierarchy;
class BoneAniMeshFrame;
class BoneAniMeshContainer;
class BoneAniMeshWorldMatStack;
class SkinAniMeshAllocHierarchy;
class SkinAniMeshFrame;
class SkinAniMeshContainer;
class SkinAniMeshWorldMatStack;

class ICubeMapActor;
class IBumpMapActor;


class SceneChief;
class GeometricActor;
class FigureActor;
class IAlignAbleActor;
class MassActor;
class MeshActor;
class MeshSetActor;
class MassMeshActor;
class MorphMeshActor;
class MassMorphMeshActor;
class D3DXMeshActor;
class DynaD3DXMeshActor;
class D3DXAniMeshActor;
class SpriteMeshActor;
class SpriteMeshSetActor;
class CubeMapMeshActor;
class CubeMapMeshSetActor;
class CubeMapMorphMeshActor;
class WorldBoundActor;
class AABoardRectActor;
class AABActor;
class AAPrismActor;
class AAPyramidActor;
class SphereActor;
class SpriteActor;
class SpriteSetActor;
class MassSpriteActor;
class Camera;
class CameraViewPoint;
class CameraUpVector;
class BoardActor;
class BoardSetActor;
class MassBoardActor;
class PointSpriteActor;
class MassPointSpriteActor;
class PointSpriteSetActor;
class FramedBoardActor;
class FramedSpriteActor;
class RegularPolygonSpriteActor;
class RegularPolygonBoardActor;
class BoneAniMeshActor;
class SkinAniMeshActor;

class Model;
class MassModel;
class D3DXMeshModel;
class D3DXAniMeshModel;
class IPlaneModel;
class SpriteModel;
class SpriteSetModel;
class MassSpriteModel;
class MeshModel;
class MeshSetModel;
class MassMeshModel;
class MorphMeshModel;
class MassMorphMeshModel;
class CubeMapMeshModel;
class CubeMapMeshSetModel;
class CubeMapMorphMeshModel;
class WorldBoundModel;
class BoardModel;
class BoardSetModel;
class MassBoardModel;
class PointSpriteModel;
class MassPointSpriteModel;
class PointSpriteSetModel;
class FramedBoardModel;
class FramedSpriteModel;
class RegularPolygonSpriteModel;
class RegularPolygonBoardModel;
class BoneAniMeshModel;
class SkinAniMeshModel;

class Effect;
class Fix2DimEffect;
class World3DimEffect;
class IPlaneEffect;

class MeshEffect;
class D3DXAniMeshEffect;
class MeshSetEffect;
class MassMeshEffect;
class MorphMeshEffect;
class MassMorphMeshEffect;
class CubeMapMeshEffect;
class CubeMapMeshSetEffect;
class CubeMapMorphMeshEffect;
class WorldBoundEffect;
class SpriteEffect;
class SpriteSetEffect;
class MassSpriteEffect;
class BoardEffect;
class BoardSetEffect;
class MassBoardEffect;
class PointSpriteEffect;
class MassPointSpriteEffect;
class PointSpriteSetEffect;
class FramedBoardEffect;
class FramedSpriteEffect;
class RegularPolygonSpriteEffect;
class RegularPolygonBoardEffect;
class BoneAniMeshEffect;
class SkinAniMeshEffect;

class Texture;

class Scene;
class Spacetime;

class Util;
class SphereRadiusVectors;
class CollisionArea;
class CollisionPart;
class GeoElem;

class ActorVehicle;
class LocusVehicle;
class LocusVehicleMvAssistant;
class LocusVehicleFaceAngAssistant;
class LocusVehicleMvAngAssistant;
class CoordVehicle;
class CoordVehicleAssistant;
class NaviVehicle;
class CollisionChecker;
class Scaler;
class AlphaFader;
class Colorist;
class SeTransmitter;
class SeTransmitterForActor;
class BgmConductor;
class AlphaCurtain;
class SceneCurtain;
class TextureBlinker;
class UvFlipper;
class Puppeteer;

class Se;
class Bgm;
class SeConnection;
class SeManager;
class BgmConnection;
class BgmManager;
class Sound;
class CWaveDecorder;

class VehicleLeader;
class FixedFrameCurveLocusVehicleLeader;
class FixedVelocityCurveLocusVehicleLeader;
class SteppedCoordCurveLocusVehicleLeader;
class CurveManufacture;
class CurveSource;
class FixedFrameCurveManufacture;
class FixedVelocityCurveManufacture;
class SteppedCoordCurveManufacture;
class CurveSourceManager;
class CurveSourceConnection;
class CurveManufactureManager;
class CurveManufactureConnection;

}

#endif /*GGAFDXCOMMONHEADER_H_*/
