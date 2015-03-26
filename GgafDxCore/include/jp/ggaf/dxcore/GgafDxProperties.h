#ifndef GGAFDXCORE_GGAFDXPROPERTIES_H_
#define GGAFDXCORE_GGAFDXPROPERTIES_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafProperties.h"

#ifdef PROPERTY
    #undef PROPERTY
#endif
#define PROPERTY GgafDxCore::GgafDxProperties

namespace GgafDxCore {

class GgafDxProperties: public GgafCore::GgafProperties {
public:
    /** [r] �t���X�N���[�����[�h�ł��邩�ǂ��� */
    static bool FULL_SCREEN;
    /** [r] �Q��ʃ��[�h�ł��邩�ǂ��� */
    static bool DUAL_VIEW;
    /** [r] �Q�[����ԗ̈敝�̊�l */
    static pixcoord GAME_BUFFER_WIDTH;
    /** [r] �Q�[����ԗ̈捂����l */
    static pixcoord GAME_BUFFER_HEIGHT;
    /** [r] �Q�[����ԗ̈�[�������̊�l */
    static double GAME_SPACE_DEPTH;
    /** [r] �ˉe�ϊ��𐳎ˉe�ōs���ꍇ��true�B�f�t�H���g��false */
    static bool PRJ_2D_MODE;
    /** [r] �`���T�[�t�F�C�X���̃s�N�Z���T�C�Y */
    static pixcoord RENDER_TARGET_BUFFER_WIDTH;
    /** [r] �`���T�[�t�F�C�X�����̃s�N�Z���T�C�Y */
    static pixcoord RENDER_TARGET_BUFFER_HEIGHT;
    /** [r] �P��ʃE�B���h�E���[�h�������ꍇ�̃E�B���h�E�̏������T�C�Y */
    static pixcoord SINGLE_VIEW_WINDOW_WIDTH;
    /** [r] �P��ʃE�B���h�E���[�h�������ꍇ�̃E�B���h�E�̏��������T�C�Y */
    static pixcoord SINGLE_VIEW_WINDOW_HEIGHT;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂P��ʖڂ̃E�B���h�E�̏������T�C�Y */
    static pixcoord DUAL_VIEW_WINDOW1_WIDTH;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂P��ʖڂ̃E�B���h�E�̏��������T�C�Y */
    static pixcoord DUAL_VIEW_WINDOW1_HEIGHT;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂Q��ʖڂ̃E�B���h�E�̏������T�C�Y */
    static pixcoord DUAL_VIEW_WINDOW2_WIDTH;
    /** [r] �Q��ʃE�B���h�E���[�h�������ꍇ�̂Q��ʖڂ̃E�B���h�E�̏��������T�C�Y */
    static pixcoord DUAL_VIEW_WINDOW2_HEIGHT;
    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̉𑜓x(��) */
    static pixcoord SINGLE_VIEW_FULL_SCREEN_WIDTH;
    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̉𑜓x(�c) */
    static pixcoord SINGLE_VIEW_FULL_SCREEN_HEIGHT;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̉𑜓x(��) */
    static pixcoord DUAL_VIEW_FULL_SCREEN1_WIDTH;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̉𑜓x(�c) */
    static pixcoord DUAL_VIEW_FULL_SCREEN1_HEIGHT;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̉𑜓x(��) */
    static pixcoord DUAL_VIEW_FULL_SCREEN2_WIDTH;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̉𑜓x(�c) */
    static pixcoord DUAL_VIEW_FULL_SCREEN2_HEIGHT;
    /** [r/w] �\���̈�ŁARENDER_TARGET_BUFFER�̃T�C�Y�̂܂ܕ\�����邩�ǂ����B(true=RENDER_TARGET_BUFFER�T�C�Y�\��/false=�\���̈�̓T�C�Y��) */
    static bool VIEW_AS_RENDER_TARGET_BUFFER_SIZE;
    /** [r/w] �\���̈�T�C�Y�ώ��A�\���̈�A�X�y�N�g����Q�[���o�b�t�@�̏c����ŌŒ�ɂ��邩�ǂ���(true=�Œ�/false=�Œ�ɂ��Ȃ�) */
    static bool FIXED_GAME_VIEW_ASPECT;
    /** [r/w] �Q��ʃ��[�h���A�P��ʖڂƂQ��ʖڂ����ւ��邩�ǂ��� */
    static bool SWAP_GAME_VIEW;
    /** [r/w] �P��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int SINGLE_VIEW_DRAW_POSITION;
    /** [r/w] �Q��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�P��ʖڂ̕\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int DUAL_VIEW_DRAW_POSITION1;
    /** [r/w] �Q��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�Q��ʖڂ̕\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int DUAL_VIEW_DRAW_POSITION2;
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
    /** [r/w] SE�����`����܂ł́A�Œጻ�K�v�ȃt���[���� */
    static int MAX_SE_DELAY;

    /** [r] ���b�V�����f���̒�`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_MESH;
    /** [r] 2D�X�v���C�g���f���̒�`�t�@�C��(sprx)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_SPRITE;
    /** [r] �e�N�X�`���t�@�C���̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_TEXTURE;
    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_EFFECT;
    /** [r] BGM�t�@�C��(ogg�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_OGG;
    /** [r] SoundEffect�t�@�C��(wave�t�@�C��)�̊i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SKIN_XXX_WAVE;

    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�����s���ɃR���p�C�����邩�ǂ��� */
    static bool REALTIME_EFFECT_COMPILE;

    /** [r] �s���ȏꍇ�ɑ���ɓ\��t������e�N�X�`���t�@�C�� */
    static std::string ILLIGAL_TEXTURE;
    /** [r] �s���ȏꍇ�ɑ���ɓ\��t��������}�b�v�e�N�X�`���t�@�C�� */
    static std::string ILLIGAL_CUBEMAP_TEXTURE;
    /** [r] �������������ꍇ�ɓ\��t�����锒���n�̃e�N�X�`�� */
    static std::string WHITE_TEXTURE;
    /** [r] AABox�����蔻��v�f�\���p�̃��f�� */
    static std::string COLI_AAB_MODEL;
    /** [r] AAPrism�����蔻��v�f�\���p�̃��f�� */
    static std::string COLI_AAPRISM_MODEL;
    /** [r] ���̓����蔻��v�f�\���p�̃��f�� */
    static std::string COLI_SPHERE_MODEL;

    ////// �ȉ��́A��L�v���p�e�B���琶�������ǂݏo����p�v���p�e�B ////////

    /** [r] ���b�V�����f���̒�`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g��(0:default/1:���[�U�[/2:�J�����g) */
    static std::string DIR_MESH_MODEL[3];
    /** [r] 2D�X�v���C�g���f���̒�`�t�@�C��(sprx)�̊i�[�f�B���N�g��(0:default/1:���[�U�[/2:�J�����g) */
    static std::string DIR_SPRITE_MODEL[3];
    /** [r] �e�N�X�`���t�@�C���̊i�[�f�B���N�g��(0:default/1:���[�U�[/2:�J�����g) */
    static std::string DIR_TEXTURE[3];
    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�̊i�[�f�B���N�g��(0:default/1:���[�U�[/2:�J�����g) */
    static std::string DIR_EFFECT[3];
    /** [r] BGM�t�@�C��(ogg�t�@�C��)�̊i�[�f�B���N�g��(0:default/1:���[�U�[/2:�J�����g) */
    static std::string DIR_OGG[3];
    /** [r] SoundEffect�t�@�C��(wave�t�@�C��)�̊i�[�f�B���N�g��(0:default/1:���[�U�[/2:�J�����g) */
    static std::string DIR_WAVE[3];
    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̕␳�O�𑜓x(��) */
    static pixcoord SINGLE_VIEW_FULL_SCREEN_WIDTH_BK;
    /** [r] �P��ʃt���X�N���[�����[�h�������ꍇ�̃X�N���[���̕␳�O�𑜓x(�c) */
    static pixcoord SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̕␳�O�𑜓x(��) */
    static pixcoord DUAL_VIEW_FULL_SCREEN1_WIDTH_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̕␳�O�𑜓x(�c) */
    static pixcoord DUAL_VIEW_FULL_SCREEN1_HEIGHT_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̕␳�O�𑜓x(��) */
    static pixcoord DUAL_VIEW_FULL_SCREEN2_WIDTH_BK;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂Q��ʖڃX�N���[���̕␳�O�𑜓x(�c) */
    static pixcoord DUAL_VIEW_FULL_SCREEN2_HEIGHT_BK;

public:
    static void load(std::string prm_properties_filename); //shadows
    static void clean();                                   //shadows
};

}
#endif /*GGAFDXCORE_GGAFDXPROPERTIES_H_*/

