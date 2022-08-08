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
//�Ӗ���Y�ꂽ��A�Q�Ƃ���

#define GGAF_MAX_VOLUME (1000)
#define GGAF_MIN_VOLUME (0)

#define Obj_GgafDx_Scene        ((0x10ULL) | Obj_SceneBit)  //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00010000
#define Obj_GgafDx_Spacetime    ((0x20ULL) | Obj_SceneBit)  //0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00100000

#define Obj_GgafDx_BaseActor                         (0x100ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000001 00000000
#define Obj_GgafDx_SceneMediator                     (0x200ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000010 00000000
#define Obj_GgafDx_GeometricActor                    (0x400ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00000100 00000000
#define Obj_GgafDx_FigureActor                       (0x800ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00001000 00000000
#define Obj_GgafDx_MeshActor                        (0x1000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00010000 00000000
#define Obj_GgafDx_MeshSetActor                     (0x2000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 00100000 00000000
#define Obj_GgafDx_MorphMeshActor                   (0x4000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 01000000 00000000
#define Obj_GgafDx_D3DXMeshActor                    (0x8000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000000 10000000 00000000
#define Obj_GgafDx_DynaD3DXMeshActor               (0x10000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000001 00000000 00000000
#define Obj_GgafDx_D3DXAniMeshActor                (0x20000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000010 00000000 00000000
#define Obj_GgafDx_SpriteMeshActor                 (0x40000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00000100 00000000 00000000
#define Obj_GgafDx_SpriteMeshSetActor              (0x80000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00001000 00000000 00000000
#define Obj_GgafDx_CubeMapMeshActor               (0x100000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00010000 00000000 00000000
#define Obj_GgafDx_CubeMapMeshSetActor            (0x200000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 00100000 00000000 00000000
#define Obj_GgafDx_CubeMapMorphMeshActor          (0x400000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 01000000 00000000 00000000
#define Obj_GgafDx_WorldBoundActor                (0x800000ULL)  //0b 00000000 00000000 00000000 00000000 00000000 10000000 00000000 00000000
#define Obj_GgafDx_SpriteActor                   (0x1000000ULL)  //0b 00000000 00000000 00000000 00000000 00000001 00000000 00000000 00000000
#define Obj_GgafDx_SpriteSetActor                (0x2000000ULL)  //0b 00000000 00000000 00000000 00000000 00000010 00000000 00000000 00000000
#define Obj_GgafDx_BoardActor                    (0x4000000ULL)  //0b 00000000 00000000 00000000 00000000 00000100 00000000 00000000 00000000
#define Obj_GgafDx_BoardSetActor                 (0x8000000ULL)  //0b 00000000 00000000 00000000 00000000 00001000 00000000 00000000 00000000
#define Obj_GgafDx_PointSpriteActor             (0x10000000ULL)  //0b 00000000 00000000 00000000 00000000 00010000 00000000 00000000 00000000
#define Obj_GgafDx_MassActor                    (0x20000000ULL)  //0b 00000000 00000000 00000000 00000000 00100000 00000000 00000000 00000000
#define Obj_GgafDx_MassMeshActor                (0x40000000ULL)  //0b 00000000 00000000 00000000 00000000 01000000 00000000 00000000 00000000
#define Obj_GgafDx_MassBoardActor               (0x80000000ULL)  //0b 00000000 00000000 00000000 00000000 10000000 00000000 00000000 00000000
#define Obj_GgafDx_MassSpriteActor             (0x100000000ULL)  //0b 00000000 00000000 00000000 00000001 00000000 00000000 00000000 00000000
#define Obj_GgafDx_MassMorphMeshActor          (0x200000000ULL)  //0b 00000000 00000000 00000000 00000010 00000000 00000000 00000000 00000000
#define Obj_GgafDx_MassPointSpriteActor        (0x400000000ULL)  //0b 00000000 00000000 00000000 00000100 00000000 00000000 00000000 00000000
#define Obj_GgafDx_PointSpriteSetActor         (0x800000000ULL)  //0b 00000000 00000000 00000000 00001000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_FramedBoardActor           (0x1000000000ULL)  //0b 00000000 00000000 00000000 00010000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonSpriteActor  (0x2000000000ULL)  //0b 00000000 00000000 00000000 00100000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_RegularPolygonBoardActor   (0x4000000000ULL)  //0b 00000000 00000000 00000000 01000000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_BoneAniMeshActor           (0x8000000000ULL)  //0b 00000000 00000000 00000000 10000000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_SkinAniMeshActor          (0x10000000000ULL)  //0b 00000000 00000000 00000001 00000000 00000000 00000000 00000000 00000000
#define Obj_GgafDx_FramedSpriteActor         (0x20000000000ULL)  //0b 00000000 00000000 00000010 00000000 00000000 00000000 00000000 00000000


/** ��]���@�萔�A�߂������ɉ�] */
#define TURN_CLOSE_TO 0
/** ��]���@�萔�A���������ɉ�] */
#define TURN_ANTICLOSE_TO 2
/** ��]���@�萔�A���v���ɉ�] */
#define TURN_CLOCKWISE (-1)
/** ��]���@�萔�A�����v���ɉ�] */
#define TURN_COUNTERCLOCKWISE 1
/** ��]���@�萔�A�ǂ��炩�̉�]�i������̉�]�ł��j */
#define TURN_BOTH 0

typedef uint_fast32_t pos_t;

//�v���Y���p��(�ʒu)�萔

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

//�v���Y���́A�����̂��ǂ̖ʂ��猩�đΊp���ɐ����ɃX���C�X����ďo���オ�����`��������
/** XY���ʂ��猩�đΊp���ɐ����ɃX���C�X�����`�ł��� */
#define POS_PRISM_XY_xx      (0x10) //0b 00010000
/** YZ���ʂ��猩�đΊp���ɐ����ɃX���C�X�����`�ł��� */
#define POS_PRISM_YZ_xx      (0x20) //0b 00100000
/** ZX���ʂ��猩�đΊp���ɐ����ɃX���C�X�����`�ł��� */
#define POS_PRISM_ZX_xx      (0x40) //0b 01000000

//�X���C�X�ŏo����v���Y��(�S�ʂ�)�̈ʒu���A
//���p�O�p�`�̒��p������ꏊ�ɒ��ڂ��A
//���ʍ��W�̏ی�(�����W�̐���)�Ŏ����B
//n = negative(��), p = positive(��)
/** ���p�����������, (��, ��)�ł��� */
#define POS_PRISM_xx_NN      (0x1)  //0b 00000001
/** ���p�����������, (��, ��)�ł��� */
#define POS_PRISM_xx_NP      (0x2)  //0b 00000010
/** ���p�����������, (��, ��)�ł��� */
#define POS_PRISM_xx_PN      (0x4)  //0b 00000100
/** ���p�����������, (��, ��)�ł��� */
#define POS_PRISM_xx_PP      (0x8)  //0b 00001000

#define POS_PRISM_xx_xP (POS_PRISM_xx_NP | POS_PRISM_xx_PP)
#define POS_PRISM_xx_Px (POS_PRISM_xx_PN | POS_PRISM_xx_PP)

//2D���p�O�p�`�̓����蔻�莞�Ɏw�肷��萔
/** ���p�����������, (x, y) = (��, ��) �����ł��� */
#define POS_R_TRIANGLE_NN POS_PRISM_XY_NN
/** ���p�����������, (x, y) = (��, ��) �����ł��� */
#define POS_R_TRIANGLE_NP POS_PRISM_XY_NP
/** ���p�����������, (x, y) = (��, ��) �����ł��� */
#define POS_R_TRIANGLE_PN POS_PRISM_XY_PN
/** ���p�����������, (x, y) = (��, ��) �����ł��� */
#define POS_R_TRIANGLE_PP POS_PRISM_XY_PP

#define POS_R_TRIANGLE_xP POS_PRISM_xx_xP
#define POS_R_TRIANGLE_Px POS_PRISM_xx_Px

//���p�̒��_�̈ʒu���l�K�|�W
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


//DirectX��3D��Ԃ̍��W�P�ʂP�ɑ΂��Ă̌��_�t�߂̉��px�������i��ʍ���(px)�Ȃǂ��APX_UNIT�Ŋ����3D��Ԃ̍��W�P�ʂP�ɂȂ�j
#define PX_UNIT (10)
//���_�t�߂̉�ʏ�̂Ppx�����ɑ΂��Ă�PG���ł̍��W�P�ʂ̔䗦�iPG���ł̍��W�P�ʂ� LEN_UNIT�Ŋ����3D��Ԃ�px�ɂȂ�j
#define LEN_UNIT (1000)
#define PI  (3.14159265358979323846)
#define PI2 (6.28318530717958647692)

//�V�F�[�_�[2.0�̌��E�̃��[�t�^�[�Q�b�g��6������
#define MAX_MORPH_TARGET 6

/** �A�v���P�[�V�������W�P�� (�ڈ��F 1 coord  =  0.001 pixcoord  =  0.0001 dxcoord  ) */
typedef int_fast32_t coord;
typedef uint_fast32_t ucoord;
/** �A�v���P�[�V�������W�P�ʌn�̑��x */
typedef int_fast32_t velo;
/**  �A�v���P�[�V�������W�P�ʌn�̉����x */
typedef int_fast32_t acce;
/**  �A�v���P�[�V�������W�P�ʌn�̖��x(TODO:���ݖ��g�p) */
typedef int_fast32_t jerk;

/** �s�N�Z�����W�P�� (�ڈ��F 1 pixcoord  =  1000 coord   =  0.1 dxcoord ) */
typedef int_fast32_t pixcoord;
/** DirectX���W�P��  (�ڈ��F 1 dxcoord   =  10 pixcoord  =  10000 coord ) */
typedef float dxcoord;

/** �A�v���P�[�V�����X�P�[���P�� (�ڈ��F 1 scale  =  0.001 �{) */
typedef int_fast32_t scale;
typedef int_fast32_t scalevelo;
typedef int_fast32_t scaleacce;
/** �A�v���P�[�V�����p�x�P�� (�ڈ��F 1 angle  =  0.001 �x) */
typedef int_fast32_t angle;
/** �A�v���P�[�V�����p�x�P�ʌn�̊p���x */
typedef int_fast32_t angvelo;
/** �A�v���P�[�V�����p�x�P�ʌn�̊p�����x */
typedef int_fast32_t angacce;
/** �A�v���P�[�V�����p�x�P�ʌn�̊p�������x */
typedef int_fast32_t angjerk;

/** �A�v���P�[�V���������̊p�x���x�P��(�t���[�����[�N�p) */
typedef int_fast32_t s_ang;

/** ���^(AXIS_X / AXIS_Y / AXIS_Z) */
enum {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_Z
};

typedef int_fast32_t axis;

#define MAX_SCALE (2147483647)

/** �x���@ 0 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D0ANG   (0)
/** �x���@ 360 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D360ANG (360000)
/** �x���@ 45 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D45ANG  (45000)
/** �x���@ 90 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D90ANG  (90000)
/** �x���@ 135 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D135ANG (135000)
/** �x���@ 180 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D180ANG (180000)
/** �x���@ 255 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D255ANG (225000)
/** �x���@ 270 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D270ANG (270000)
/** �x���@ 315 �x�ɑΉ�����A�v���̃A���O���l�萔 */
#define D315ANG (315000)
/** ���W�A���̃� �ɑΉ�����A�v���̃A���O���l�萔 */
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
/** �������x�p�x�P�� �� �A�v���P�[�V�����p�x�P�� �ւ̔{�� */
#define SANG_RATE (100)

/** �A�v���̍��W �� DirectX���W �ϊ� */
#define C_DX(X)  ( (dxcoord)((X) * (1.0 / (LEN_UNIT * PX_UNIT))) )
/** DirectX���W �� �A�v���̍��W �ϊ� */
#define DX_C(X)  ( (coord)((X) * (LEN_UNIT * PX_UNIT)) )
/** DirectX���W �� �s�N�Z�����W(�����J�����ʒu�̎�) �ϊ� */
#define DX_PX(X) ( (pixcoord)((X) * PX_UNIT) )
/** �s�N�Z�����W(�����J�����ʒu�̎�) ��DirectX���W �ϊ� */
#define PX_DX(X) ( (dxcoord)((X) * (1.0 / PX_UNIT)) )
/** �A�v���̍��W �� �s�N�Z�����W(�����J�����ʒu�̎�) �ϊ� */
#define C_PX(X)  ( (pixcoord)((X) * (1.0 / LEN_UNIT)) )
/** �s�N�Z�����W(�����J�����ʒu�̎�) �� �A�v���̍��W �ϊ� */
#define PX_C(X)  ( (coord)((X) * LEN_UNIT) )

/** �A�v���̃A���O���l���x���@�p�x �ϊ� */
#define ANG_D(X) ((int)((X) * 0.001))
/** �x���@�p�x���A�v���̃A���O���l �ϊ� */
#define D_ANG(X) ((angle)((X) * 1000))
///** �A�v���̃A���O���l�����W�A�� �ϊ� */
#define ANG_RAD(X) (GgafDx::Util::RAD[(int)((X) * 0.1)])
/** �A�v���̃A���O���l������ �ϊ� */
#define ANG_SIN(X) (GgafDx::Util::SIN[(int)((X) * 0.1)])
/** �A�v���̃A���O���l���]�� �ϊ� */
#define ANG_COS(X) (GgafDx::Util::COS[(int)((X) * 0.1)])
/** �A�v���̃X�P�[���l �� �g�嗦 �ϊ� */
#define SC_R(X) ( (float)((X) * (1.0 / LEN_UNIT)) )
/** �g�嗦 �� �A�v���̃X�P�[���l �ϊ� */
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

//�O���錾(forward declaration)
namespace IkdLib {
//�u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html
// �̎�AIkd ������ogg�t�@�C���Đ����C�u����
class PCMPlayer;
class OggVorbisResource;
class PCMDecoder;
class OggDecoder;
class OggVorbisFile;
class OggVorbisMemory;
}
//�O���錾(forward declaration)
namespace Frm {
class Model3D;
class Mesh;
}

//�O���錾(forward declaration)
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

class BaseActor;
class SceneMediator;
class GeometricActor;
class FigureActor;
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
class MassEffect;
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
class VecVehicle;
class VecVehicleMvAssistant;
class VecVehicleFaceAngAssistant;
class VecVehicleMvAngAssistant;
class AxisVehicle;
class AxisVehicleAssistantA;
class GeoVehicle;
class Checker;
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
class FixedFrameCurveVecVehicleLeader;
class FixedVelocityCurveVecVehicleLeader;
class SteppedCoordCurveVecVehicleLeader;
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
