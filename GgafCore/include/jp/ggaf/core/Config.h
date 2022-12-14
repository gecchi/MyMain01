#ifndef GGAF_CORE_CONFIG_H_
#define GGAF_CORE_CONFIG_H_
#include "GgafCommonHeader.h"

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
    /** [r/w] �ō��t���[���X�L�b�v���B�܂�ǂ�Ȃɏd�����Œ�`�悷��t���[���Ԋu�B*/
    static uint32_t MAX_SKIP_FRAME;
    /** [r/w] 60fps��40fps�̏����������o���s�����ǂ����̋��E�B1�t���[������������`��񐔂Őݒ� */
    static uint32_t OBJNUM_TO_SLOWDOWN1;
    /** [r/w] 40fps��30fps�̏����������o���s�����ǂ����̋��E�B1�t���[������������`��񐔂Őݒ� */
    static uint32_t OBJNUM_TO_SLOWDOWN2;
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

