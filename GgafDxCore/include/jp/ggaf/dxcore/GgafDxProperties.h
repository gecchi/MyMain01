#ifndef GGAFDXPROPERTIES_H_
#define GGAFDXPROPERTIES_H_

#ifdef CFG_PROPERTY
    #undef CFG_PROPERTY
#endif
#define CFG_PROPERTY(X) (GgafDxCore::GgafDxProperties::X)

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
    static float GAME_SPACE_DEPTH;
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
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̂P��ʖڃX�N���[���̉𑜓x(�c) */
    static pixcoord DUAL_VIEW_FULL_SCREEN2_HEIGHT;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̗���ʂ̃X�N���[���̉𑜓x(��) */
    static pixcoord DUAL_VIEW_FULL_SCREEN_WIDTH;
    /** [r] �Q��ʃt���X�N���[�����[�h�������ꍇ�̗���ʂ̃X�N���[���̉𑜓x(�c) */
    static pixcoord DUAL_VIEW_FULL_SCREEN_HEIGHT;
    /** [r/w] �Q�[���\���̈�A�X�y�N�g����Œ肷�邩�ǂ��� */
    static bool FIXED_GAME_VIEW_ASPECT;
    /** [r/w] �Q��ʃ��[�h���A�P��ʖڂƂQ��ʖڂ����ւ��邩�ǂ��� */
    static bool SWAP_GAME_VIEW;
    /** [r/w] �P��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int SINGLE_VIEW_DRAW_POSITION;
    /** [r/w] �Q��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�P��ʖڂ̕\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int DUAL_VIEW_DRAW_POSITION1;
    /** [r/w] �Q��ʃ��[�h�����Q�[���\���̈�A�X�y�N�g����Œ莞�A�Q��ʖڂ̕\���̈�ꏊ���w��(�ꏊ���e���L�[�̐��l) */
    static int DUAL_VIEW_DRAW_POSITION2;
    /** [r/w] �Q�[���\���̈�A�X�y�N�g����Œ莞�A�Q�[���\���̈�O�̔w�i�F */
    static std::string BG_COLOR;
    /** [r/w] �}�X�^�[�{�����[��(0�`100) */
    static int MASTER_VOLUME;
    /** [r/w] BGM �{�����[��(0�`100) */
    static int BGM_VOLUME;
    /** [r/w] SoundEffect �{�����[��(0�`100) */
    static int SE_VOLUME;
    /** [r] ���b�V�����f���̒�`�t�@�C��(X�t�@�C��)�̊i�[�f�B���N�g�� */
    static std::string DIR_MESH_MODEL;
    /** [r] 2D�X�v���C�g���f���̒�`�t�@�C��(sprx)�̊i�[�f�B���N�g�� */
    static std::string DIR_SPRITE_MODEL;
    /** [r] �e�N�X�`���t�@�C���̊i�[�f�B���N�g�� */
    static std::string DIR_TEXTURE;
    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�̊i�[�f�B���N�g�� */
    static std::string DIR_EFFECT;
    /** [r] BGM�t�@�C��(ogg�t�@�C��)�̊i�[�f�B���N�g�� */
    static std::string DIR_OGG;
    /** [r] SoundEffect�t�@�C��(wave�t�@�C��)�̊i�[�f�B���N�g�� */
    static std::string DIR_WAVE;
    /** [r] �G�t�F�N�g�t�@�C��(fx�t�@�C��)�����s���ɃR���p�C�����邩�ǂ��� */
    static bool REALTIME_EFFECT_COMPILE;

    static void load(std::string prm_ini_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*GGAFDXPROPERTIES_H_*/
