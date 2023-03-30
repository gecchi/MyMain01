#ifndef GGAF_CORE_CONFIG_H_
#define GGAF_CORE_CONFIG_H_
#include "jp/ggaf/GgafCommonHeader.h"

#include "jp/ggaf/core/Properties.h"
#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/Rgb.h"
#ifndef _MSC_VER
    #include <atomic>
#endif

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG GgafCore::Config

/** �b �� �t���[���� �ϊ� */
#define SEC_F(X)  ( (frame)((X) * (CONFIG::FPS)) )
/** �~���b �� �t���[���� �ϊ� */
#define MSEC_F(X)  ( (frame)(((X) * 0.001) * (CONFIG::FPS)) )


/** ���ʒx������t���[�����i���G�t�F�N�g�ő�Đ����ԁj */
#define GGAF_END_DELAY (SEC_F(90))
//GGAF_END_DELAY�͑SElement���ʂ̉���x���t���[�����ŁA
//�A�N�^�[������A�����ɕs���|�C���^�ɂȂ�̂ł͂Ȃ��A���΂炭�Q�Ƃ��\�Ƃ��邽�߂̎d�g�݁B
//�������߂ɐݒ肵�Ȃ��ƁA���낢��s�s���������B
//�Ⴆ�΁A���Ō�̔���SE���ŁA3D���ʂ̂���SE���������W��񂪂��΂炭�K�v�Ƃ��A
//���Ō�̏��ŃA�N�^�[�z���ɑ����锭�˒e�i�q�A�N�^�[�j���A�e�A�N�^�[�̍��W���Q�Ƃ��Ă���ȂǁA
//���ł��Ă��A���΂炭�͎c�������Ȃ���΂����Ȃ��ꍇ�����X����B
//GGAF_END_DELAY�ɂ́A��{�I�ɁA��ʂ�����Ŋm�聨���S��delete�܂ł̃t���[���̍ő�t���[�����w�肷��B
//���݂�90�b�B
//�����AGGAF_END_DELAY��Z�߂ɐݒ肷��ƁA
//���Ō�̎q�̔��˒e�ɂ��ẮA�c���ꂽ���˒e���ˑR������̂ŏ����s���R�B�Ƃ������x�Ŗ��͂Ȃ��B
//�������ASE��3D���ʂ́A�G���[�ɂȂ邽�߁ASE�Đ����Ԃ̍ő�t���[������ݒ肵�Ȃ���΂����Ȃ��B
//�Ⴆ�Ό��ʉ���90�b�ȏォ����悤��WAVE����ł�����Ȃ�΁A90�b�ȏ��ݒ肵�Ȃ���΂Ȃ�Ȃ��B


namespace GgafCore {

/**
 * �v���p�e�B�N���X .
 * �O���t�@�C�����烍�[�h���A�A�v���̊��ϐ��Ƃ��ĕێ����܂��B
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class Config {

public:
    /** [r/w] FPS */
    static frame FPS;
    /** [r] 1�t���[���̕b�� */
    static double FRAME_SEC;

    /** [r/w] �ō��t���[���X�L�b�v���B�܂�ǂ�Ȃɏd�����Œ�`�悷��t���[���Ԋu�B*/
    static uint32_t MAX_SKIP_FRAME;
    /** [r/w] �����������o���s�����ǂ����̑��i�K�̋��E�B1�t���[��������̃A�N�e�B�u�ȃA�N�^�[���ݒ� */
    static uint32_t OBJNUM_TO_SLOWDOWN1;
    /** [r/w] �����������o���s�����ǂ����̑��i�K�̋��E�B1�t���[��������̃A�N�e�B�u�ȃA�N�^�[���ݒ� */
    static uint32_t OBJNUM_TO_SLOWDOWN2;

    /** [r/w] �����������o���s���i�K�̋��E���̏������������B���̑����̒x���{��(1.0�F���������Ȃ��^1.5�F1.5�{�̒x���^2.0:2�{�̒x��) */
    static double RATE_OF_SLOWDOWN1;
    /** [r/w] �����������o���s���i�K�̋��E���̏������������B���̑����̒x���{��(1.0�F���������Ȃ��^1.5�F1.5�{�̒x���^2.0:2�{�̒x��) */
    static double RATE_OF_SLOWDOWN2;

    /** [r/w] �S�~����|��(�C���X�^���X���)���s�����Ƃ��o����FPS */
    static float FPS_TO_CLEAN_GARBAGE_BOX;
    /** [r] �A�v���P�[�V�����̃��\�[�X�f�B���N�g�� */
    static std::string DIR_RESOURCE;
    /** [r] �A�v���P�[�V�����̃X�L���t�H���_��(���\�[�X�f�B���N�g���z��) */
    static std::string DIRNAME_RESOURCE_SKIN;
    /** [r] �A�v���P�[�V�����̃X�L���t�H���_�̃V�X�e���X�L����(���\�[�X�f�B���N�g���̃X�L���t�H���_�z��) */
    static std::string DIRNAME_RESOURCE_SKIN_SYSTEM;
    /** [r] �A�v���P�[�V�����̃X�L���t�H���_�̃��[�U�[�X�L����(���\�[�X�f�B���N�g���̃X�L���t�H���_�z��) */
    static std::string DIRNAME_RESOURCE_SKIN_USER;

    ////// �ȉ��́A��L�v���p�e�B���琶�������ǂݏo����p�v���p�e�B ////////

    /** [r] �A�v���P�[�V�����̃X�L���f�B���N�g�� */
    static std::string DIR_SKIN;
    /** [r] �A�v���P�[�V�����̃V�X�e���X�L���f�B���N�g��(0:�V�X�e��/1:���[�U�[/2:����) */
    static std::string DIR_SKIN_KIND[3];


#ifdef _MSC_VER
    //TODO:VC++2005�ȍ~(x86) �� volatile �́A�������o���A���ʂ�����i�Ǝv���j�B
    //gcc(x86)�́A�A�g�~�b�N�ۏ؂͖����� std::atomic ���g����BVC++�� atomic �����������܂ł͂Ƃ肠�����E�E�E�B
    static volatile bool _is_lock;
#else
    static volatile std::atomic<bool> _is_lock;
#endif

    /** [r] �ێ��v���p�e�B */
    static Properties _properties;


public:
    /**
     * �O���v���p�e�B�t�@�C�����烍�[�h���ĕێ��v���p�e�B�֐ݒ�A�����o�ϐ��ɔ��f .
     * @param prm_properties_filename �v���p�e�B�t�@�C��
     */
    static void loadProperties(std::string prm_properties_filename);

};

}
#endif /*GGAF_CORE_CONFIG_H_*/

