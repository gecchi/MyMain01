#ifndef GGAF_DX_CONFIG_H_
#define GGAF_DX_CONFIG_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Config.h"

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG GgafDx::Config

#define MAX_SCREENS 16
namespace GgafDx {

class Config: public GgafCore::Config {
public:
    template <class T>
    struct GGAFRECT {
      T LEFT;
      T TOP;
      T WIDTH;
      T HEIGHT;
    };
    template <class T>
    struct GGAFSIZE {
      T WIDTH;
      T HEIGHT;
    };

    /** [r] �t���X�N���[�����[�h�ł��邩�ǂ���Config */
    static bool FULL_SCREEN;
    /** [r] ����ʎg�p���邩(1�`) */
    static int NUMBER_OF_SCREENS_USED;
    /** [r] �Q�[����ԗ̈敝�̊�l */
    static pixcoord GAME_BUFFER_WIDTH;
    /** [r] �Q�[����ԗ̈捂����l */
    static pixcoord GAME_BUFFER_HEIGHT;
    /** [r] �Q�[����ԗ̈�[�������̊�l */
    static double GAME_SPACE_DEPTH;
    /** [r] �ʏ�̒i�K�����_�����O�[�x�̐�(�f�t�H���g256) */
    static int RENDER_DEPTH_INDEXS_NUM;
    /** [r] ���ʂɑO�ʂɕ`�悷��i�K�����_�����O�[�x�̐�(�f�t�H���g10) */
    static int RENDER_DEPTH_INDEXS_NUM_EX_NEAR;
    /** [r] ���ʂɔw�ʂɕ`�悷��i�K�����_�����O�[�x�̐�(�f�t�H���g10) */
    static int RENDER_DEPTH_INDEXS_NUM_EX_FAR;
    /** [r]  �ʏ�̒i�K�����_�����O���J�n����J��������ŉ��_�̋����̊��� */
    static double RENDER_DEPTH_STAGE_RATIO;
    /** [r] �ˉe�ϊ��𐳎ˉe�ōs���ꍇ��true�B�f�t�H���g��false */
    static bool PRJ_2D_MODE;
    /** [r] �`���T�[�t�F�C�X���̃s�N�Z���T�C�Y */
    static pixcoord RENDER_TARGET_BUFFER_WIDTH;
    /** [r] �`���T�[�t�F�C�X�����̃s�N�Z���T�C�Y */
    static pixcoord RENDER_TARGET_BUFFER_HEIGHT;

    /** [r] �t���X�N���[�����[�h���A�Q�[�����[n]��ʖڂ̃f�C�X�v���C�ԍ�(n:0�`) */
    static int SCREEN_DISPLAY_NO[MAX_SCREENS];
    /** [r] �`���T�[�t�F�C�X�iRENDER_TARGET_BUFFER�j�̒�����A�Q�[�����[n]��ʖڂ̎��ۂɃQ�[���ɕ\������R�s�[���o�b�t�@�̃N���b�s���O�̈�(LEFT/TOP/WIDTH/HEIGHT) */
    static GGAFRECT<pixcoord> SCREEN_RENDER_BUFFER_SOURCE[MAX_SCREENS];
    /** [r] �E�B���h�E���[�h�������ꍇ�́A�Q�[�����[n]��ʖڂ̃E�B���h�E�̏������T�C�Y(WIDTH/HEIGHT) */
    static GGAFSIZE<pixcoord> SCREEN_WINDOW[MAX_SCREENS];
    /** [r] �t���X�N���[�����[�h�������ꍇ�́A�Q�[�����[n]��ʖڃX�N���[���̉�ʉ𑜓x(WIDTH/HEIGHT) */
    static GGAFSIZE<pixcoord> SCREEN_FULL_SCREEN[MAX_SCREENS];
    /** [r] �t���X�N���[�����[�h�������ꍇ�́A�Q�[�����[n]��ʖڃX�N���[���́u�␳�O�v�̉𑜓x(WIDTH/HEIGHT) */
    static GGAFSIZE<pixcoord> SCREEN_FULL_SCREEN_BK[MAX_SCREENS];

    /** [r/w] �Q�[�����[n]��ʖڕ\���̈�A�X�y�N�g����Q�[���o�b�t�@�̏c����ŌŒ�ɂ��邩�ǂ���(true=�Œ�/false=�Œ�ɂ��Ȃ�) */
    static bool SCREEN_ASPECT_RATIO_FIXED[MAX_SCREENS];
    /** [r] �Q�[���\���̈�A�X�y�N�g����Œ莞�A�Q�[�����[n]��ʖڂ̕\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int SCREEN_PRESENT_POSITION[MAX_SCREENS];
    /** [r/w] �Q�[���\���̈�A�X�y�N�g��Œ�̏ꍇ�A�Q�[�����[n]��ʖڂ̕\���̈�̉��������旦 */
    static GGAFSIZE<double> SCREEN_RATIO[MAX_SCREENS];



    /** [r/w] �Q�[���\���̈�A�X�y�N�g����Œ莞�A�Q�[���\���̈�O�̔w�i�F */
    static std::string BORDER_COLOR;
    /** [r/w] �Q�[���\���̈���̔w�i�F */
    static std::string BG_COLOR;
    /** [r/w] �}�X�^�[�{�����[��(GGAF_MIN_VOLUME �` GGAF_MAX_VOLUME) */
    static int MASTER_VOLUME;
    /** [r/w] BGM �{�����[��(GGAF_MIN_VOLUME �` GGAF_MAX_VOLUME) */
    static int BGM_VOLUME;
    /** [r/w] SoundEffect �{�����[��(GGAF_MIN_VOLUME �` GGAF_MAX_VOLUME) */
    static int SE_VOLUME;
    /** [r/w] SE�ő哯��������(1�`64) */
    static int MAX_SE_AT_ONCE;
    /** [r/w] �Q�[����ԂŃJ��������̍ŉ�����(zf)�̂Ɉʒu�����A�N�^�[��SE�����x���~���b�� */
    static int FRAME_OF_SE_DELAY_MAX_DEPTH;
    /** [r/w] �Q�[����ԂŃJ��������̍ŉ�����(zf)�̂Ɉʒu�����A�N�^�[��SE�����{�����[���̌������� */
    static double SE_VOLUME_RATE_MAX_DEPTH;

    /** [r] 3D���f���̒�`�t�@�C��(modelx�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_MODEL;
    /** [r] 3D���b�V������`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_MODELXXX_MESH;
    /** [r] 3D�|�C���g�X�v���C�g��`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_MODELXXX_POINT_SPRITE3D;
    /** [r] 2D�X�v���C�g���f���̒�`�t�@�C��(sprx)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_MODELXXX_SPRITE;
    /** [r] �e�N�X�`���t�@�C���̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_TEXTURE;
    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_EFFECT;
    /** [r] BGM�t�@�C��(ogg�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_BGM;
    /** [r] SoundEffect�t�@�C��(wave�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKINXXX_SE;

    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�����s���ɃR���p�C�����邩�ǂ��� */
    static bool REALTIME_EFFECT_COMPILE;

    /** [r] �s���ȏꍇ�ɑ���ɓ\��t������e�N�X�`���t�@�C�� */
    static std::string ILLIGAL_TEXTURE;
    /** [r] �s���ȏꍇ�ɑ���ɓ\��t��������}�b�v�e�N�X�`���t�@�C�� */
    static std::string ILLIGAL_CUBEMAP_TEXTURE;
    /** [r] �������������ꍇ�ɓ\��t�����锒���n�̃e�N�X�`�� */
    static std::string WHITE_TEXTURE;
    /** [r] AABox�����蔻��v�f�\���p�̃��f�� */
    static std::string COLI_AABOX_MODEL;
    /** [r] AAPrism�����蔻��v�f�\���p�̃��f�� */
    static std::string COLI_AAPRISM_MODEL;
    /** [r] AAPyramid�����蔻��v�f�\���p�̃��f�� */
    static std::string COLI_AAPYRAMID_MODEL;
    /** [r] ���̓����蔻��v�f�\���p�̃��f�� */
    static std::string COLI_SPHERE_MODEL;
    static std::string COLI_AABOARDRECT_MODEL;
    ////// �ȉ��́A��L�v���p�e�B���琶�������ǂݏo����p�v���p�e�B ////////
    /** [r] 3D���f����`�t�@�C��(modelx�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_MODEL[3];
    /** [r] 3D���b�V����`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_MESH[3];
    /** [r] 3D���b�V����`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_POINT_SPRITE3D[3];
    /** [r] 2D�X�v���C�g��`�t�@�C��(sprx�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_SPRITE[3];
    /** [r] �e�N�X�`���t�@�C���̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_TEXTURE[3];
    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_EFFECT[3];
    /** [r] BGM�t�@�C��(ogg�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_BGM[3];
    /** [r] SoundEffect�t�@�C��(wave�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_SE[3];

    /** [r] �X�v���C���Ȑ����W���t�@�C��(dat�t�@�C��)�i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_CURVE;
    /** [r] �X�v���C���Ȑ����W���t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_CURVE;

    /** [r] ���[���h�q�b�g�`�F�b�N�̔����؋�ԃ��x���� */
    static int WORLD_HIT_CHECK_OCTREE_LEVEL;
    /** [r] ���[���h�q�b�g�`�F�b�N�̎l���؋�ԃ��x���� */
    static int WORLD_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] �r���[�q�b�g�`�F�b�N�̎l���؋�ԃ��x���� */
    static int VIEW_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] �q�b�g�`�F�b�N�Ɏg�p�����ԕ����Atrue�F�l���؏ꍇ�^false�F�����؁i�f�t�H���g�j */
    static bool ENABLE_WORLD_HIT_CHECK_2D;

    static int P1_JOY_STICK_DEVICE_NO;
    static int P2_JOY_STICK_DEVICE_NO;
    /** [r] �J�����\���͈͂̐[�x(zn)�̂ǂ̊�����艜�̃I�u�W�F�N�g���A���t�@�t�H�O�łڂ₷��(0.0�`1.0)�B���̐�(-1.0)�ŕK���\���B */
    static double DEFAULT_DRAW_FAR_RATE;

public:
    static void loadProperties(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAF_DX_CONFIG_H_*/

