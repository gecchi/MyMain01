#ifndef GGAF_DX_CONFIG_H_
#define GGAF_DX_CONFIG_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Config.h"

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG GgafDx::Config

namespace GgafDx {

class Config: public GgafCore::Config {
public:
    /** [r] �t���X�N���[�����[�h�ł��邩�ǂ���Config */
    static bool FULL_SCREEN;
    /** [r] �Q��ʃ��[�h�ł��邩�ǂ��� */
    static bool DUAL_VIEW;
    /** [r] �Q�[����ԗ̈敝�̊�l */
    static pixcoord GAME_BUFFER_WIDTH;
    /** [r] �Q�[����ԗ̈捂����l */
    static pixcoord GAME_BUFFER_HEIGHT;
    /** [r] �Q�[����ԗ̈�[�������̊�l */
    static double GAME_SPACE_DEPTH;
    /** [r] �i�K�����_�����O�[�x�̐� */
    static int RENDER_DEPTH_INDEXS_NUM;
    /** [r] �i�K�����_�����O���s���J��������ŉ��_�̋����̊��� */
    static double RENDER_DEPTH_STAGE_RATIO;
    /** [r] �ˉe�ϊ��𐳎ˉe�ōs���ꍇ��true�B�f�t�H���g��false */
    static bool PRJ_2D_MODE;
    /** [r] �`���T�[�t�F�C�X���̃s�N�Z���T�C�Y */
    static pixcoord RENDER_TARGET_BUFFER_WIDTH;
    /** [r] �`���T�[�t�F�C�X�����̃s�N�Z���T�C�Y */
    static pixcoord RENDER_TARGET_BUFFER_HEIGHT;

    /** [r] �`���T�[�t�F�C�X�iRENDER_TARGET_BUFFER�j�̒�����A���ۂɃQ�[���ɕ\�������ʗ̈�i�N���b�s���O�j */
//    static pixcoord RENDER_BUFFER_SOURCE1_LEFT;
//    static pixcoord RENDER_BUFFER_SOURCE1_TOP;
//    static pixcoord RENDER_BUFFER_SOURCE1_WIDTH;
//    static pixcoord RENDER_BUFFER_SOURCE1_HEIGHT;

    static pixcoord RENDER_BUFFER_SOURCE1_LEFT;
    static pixcoord RENDER_BUFFER_SOURCE1_TOP;
    static pixcoord RENDER_BUFFER_SOURCE1_WIDTH;
    static pixcoord RENDER_BUFFER_SOURCE1_HEIGHT;

    static pixcoord RENDER_BUFFER_SOURCE2_LEFT;
    static pixcoord RENDER_BUFFER_SOURCE2_TOP;
    static pixcoord RENDER_BUFFER_SOURCE2_WIDTH;
    static pixcoord RENDER_BUFFER_SOURCE2_HEIGHT;


//    /** [r] �P��ʃE�B���h�E���[�h�������ꍇ�̃E�B���h�E�̏������T�C�Y */
//    static pixcoord WINDOW1_WIDTH;
//    /** [r] �P��ʃE�B���h�E���[�h�������ꍇ�̃E�B���h�E�̏��������T�C�Y */
//    static pixcoord WINDOW1_HEIGHT;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂P��ʖڂ̃E�B���h�E�̏������T�C�Y */
    static pixcoord WINDOW1_WIDTH;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂P��ʖڂ̃E�B���h�E�̏��������T�C�Y */
    static pixcoord WINDOW1_HEIGHT;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂Q��ʖڂ̃E�B���h�E�̏������T�C�Y */
    static pixcoord WINDOW2_WIDTH;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂Q��ʖڂ̃E�B���h�E�̏��������T�C�Y */
    static pixcoord WINDOW2_HEIGHT;
//    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̉𑜓x(��) */
//    static pixcoord FULL_SCREEN1_WIDTH;
//    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̉𑜓x(�c) */
//    static pixcoord FULL_SCREEN1_HEIGHT;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̉𑜓x(��) */
    static pixcoord FULL_SCREEN1_WIDTH;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̉𑜓x(�c) */
    static pixcoord FULL_SCREEN1_HEIGHT;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̉𑜓x(��) */
    static pixcoord FULL_SCREEN2_WIDTH;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̉𑜓x(�c) */
    static pixcoord FULL_SCREEN2_HEIGHT;
    /** [r/w] �\���̈�T�C�Y�ώ��A�\���̈�A�X�y�N�g����Q�[���o�b�t�@�̏c����ŌŒ�ɂ��邩�ǂ���(true=�Œ�/false=�Œ�ɂ��Ȃ�) */
    static bool FIXED_GAME_VIEW_ASPECT;
    /** [r/w] �Q��ʃt���X�N���[�����[�h���A�P��ʖڂ̃f�C�X�v���C�ԍ�(0�`) */
    static int PRIMARY_ADAPTER_NO;
    /** [r/w] �Q��ʃt���X�N���[�����[�h���A�Q��ʖڂ̃f�C�X�v���C�ԍ�(0�`) */
    static int SECONDARY_ADAPTER_NO;
    /** [r/w] �Q��ʃ��[�h���A�P��ʖڂƂQ��ʖڂ����ւ��邩�ǂ��� */
    static bool SWAP_GAME_VIEW;
//    /** [r] �P��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
//    static int PRESENT_POSITION1;
    /** [r] �Q��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�P��ʖڂ̕\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int PRESENT_POSITION1;
    /** [r] �Q��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�Q��ʖڂ̕\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int PRESENT_POSITION2;
    /** [r/w] �A�X�y�N�g��Œ�̏ꍇ�A�Q�[���\���̈�̉��������旦�i�P��ʖځj */
    static double VIEW1_WIDTH_RATIO;
    /** [r/w] �A�X�y�N�g��Œ�̏ꍇ�A�Q�[���\���̈�̍��������旦�i�P��ʖځj */
    static double VIEW1_HEIGHT_RATIO;
    /** [r/w] �A�X�y�N�g��Œ�̏ꍇ�A�Q�[���\���̈�̉��������旦�i�Q��ʖځj */
    static double VIEW2_WIDTH_RATIO;
    /** [r/w] �A�X�y�N�g��Œ�̏ꍇ�A�Q�[���\���̈�̍��������旦�i�Q��ʖځj */
    static double VIEW2_HEIGHT_RATIO;

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
    /** [r/w] �Q�[����ԂŃJ��������̍ŉ�����(zf)�̂Ɉʒu�����A�N�^�[��SE�����x�����[���� */
    static int SE_DELAY_MAX_DEPTH;
    /** [r/w] �Q�[����ԂŃJ��������̍ŉ�����(zf)�̂Ɉʒu�����A�N�^�[��SE�����{�����[���̌������� */
    static double SE_VOLUME_RATE_MAX_DEPTH;

    /** [r] ���b�V�����f���̒�`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_MESH;
    /** [r] 2D�X�v���C�g���f���̒�`�t�@�C��(sprx)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_MODEL;
    /** [r] �e�N�X�`���t�@�C���̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_TEXTURE;
    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_EFFECT;
    /** [r] BGM�t�@�C��(ogg�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_BGM;
    /** [r] SoundEffect�t�@�C��(wave�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_SE;

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

    ////// �ȉ��́A��L�v���p�e�B���琶�������ǂݏo����p�v���p�e�B ////////

    /** [r] ���b�V�����f���̒�`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_MESH[3];
    /** [r] �A�N�^�[�̒�`�t�@�C���̊i�[�f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_MODEL[3];
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

//    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̕␳�O�𑜓x(��) */
//    static pixcoord FULL_SCREEN1_WIDTH_BK;
//    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̕␳�O�𑜓x(�c) */
//    static pixcoord FULL_SCREEN1_HEIGHT_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̕␳�O�𑜓x(��) */
    static pixcoord FULL_SCREEN1_WIDTH_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̕␳�O�𑜓x(�c) */
    static pixcoord FULL_SCREEN1_HEIGHT_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̕␳�O�𑜓x(��) */
    static pixcoord FULL_SCREEN2_WIDTH_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̕␳�O�𑜓x(�c) */
    static pixcoord FULL_SCREEN2_HEIGHT_BK;

public:
    static void loadProperties(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAF_DX_CONFIG_H_*/

