#ifndef GGAFCORE_GGAFPROPERTIES_H_
#define GGAFCORE_GGAFPROPERTIES_H_
#include "GgafCommonHeader.h"

#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/core/util/GgafRgb.h"

#ifdef PROPERTY
    #undef PROPERTY
#endif
#define PROPERTY GgafCore::GgafProperties

namespace GgafCore {

/**
 * �v���p�e�B�N���X .
 * �O���t�@�C�����烍�[�h���A�A�v���̊��ϐ��Ƃ��ĕێ����܂��B
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class GgafProperties {


public:
    /** [r/w] �ō��t���[���X�L�b�v���B�܂�ǂ�Ȃɏd�����Œ�`�悷��t���[���Ԋu�B*/
    static uint32_t MAX_SKIP_FRAME;
    /** [r/w] 60fps��40fps�̏����������o���s�����ǂ����̋��E�B1�t���[������������`��񐔂Őݒ� */
    static int DRAWNUM_TO_SLOWDOWN1;
    /** [r/w] 40fps��30fps�̏����������o���s�����ǂ����̋��E�B1�t���[������������`��񐔂Őݒ� */
    static int DRAWNUM_TO_SLOWDOWN2;
    /** [r/w] �S�~����|��(�C���X�^���X���)���s�����Ƃ��o����FPS */
    static float FPS_TO_CLEAN_GARBAGE_BOX;
    /** [r] �A�v���P�[�V�����̃��\�[�X�f�B���N�g�� */
    static std::string DIR_RESOURCE;
    /** [r] �A�v���P�[�V�����̃X�L���t�H���_��(���\�[�X�f�B���N�g���z��) */
    static std::string DIRNAME_RESOURCE_SKIN;
    /** [r] �A�v���P�[�V�����̃X�L���t�H���_�̃f�t�H���g�X�L����(���\�[�X�f�B���N�g���̃X�L���t�H���_�z��) */
    static std::string DIRNAME_RESOURCE_SKIN_DEFAULT;
    /** [r] �A�v���P�[�V�����̃X�L���t�H���_�̃��[�U�[�X�L����(���\�[�X�f�B���N�g���̃X�L���t�H���_�z��) */
    static std::string DIRNAME_RESOURCE_SKIN_USER;

    ////// �ȉ��́A��L�v���p�e�B���琶�������ǂݏo����p�v���p�e�B ////////

    /** [r] �A�v���P�[�V�����̃X�L���f�B���N�g�� */
    static std::string DIR_SKIN;
    /** [r] �A�v���P�[�V�����̃f�t�H���g�X�L���f�B���N�g��(0:default/1:���[�U�[/2:�J�����g) */
    static std::string DIR_SKIN_KIND[3];




    /** [r] �ێ��v���p�e�BMAP */
    static GgafStrMap* _pMapProperties;

public:
    /**
     * �O���v���p�e�B�t�@�C�����疢���[�h�Ȃ烍�[�h���ĕێ��v���p�e�BMAP�֐ݒ�A�����o�ϐ��ɔ��f .
     * @param prm_properties_filename �v���p�e�B�t�@�C��
     */
    static void load(std::string prm_properties_filename);

    /**
     * �ێ��v���p�e�BMAP���A�O���v���p�e�B�t�@�C���֕ۑ� .
     * @param prm_properties_filename �v���p�e�B�t�@�C��
     */
    static void save(std::string prm_properties_filename);

    /**
     * �ێ��v���p�e�B����� .
     */
    static void clean();

    /**
     * �ێ��v���p�e�BMAP�ɃL�[�����݂��邩���ׂ� .
     * @param prm_key �L�[������
     * @return true:�L�[������ / false:���݂��Ȃ�
     */
    static bool isExistKey(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� string �Ŏ擾 .
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(string)
     */
    static std::string getStr(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l��bool�Ŏ擾 .
     * true, on, yes �̕�����̏ꍇ true �Ƃ݂Ȃ��A����ȊO�� false�B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(bool)
     */
    static bool getBool(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� float �Ŏ擾 .
     * ������ atof() ���g�p�B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(float)
     */
    static float getFloat(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� int �Ŏ擾 .
     * ������ atoi() ���g�p�B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(int)
     */
    static int getInt(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� uint32_t �Ŏ擾 .
     * ������ _atoi64() ���āAuint32_t�ɃL���X�g
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(uint32_t)
     */
    static uint32_t getUInt(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� double �Ŏ擾 .
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(double)
     */
    static double getDouble(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� GgafRgb �Ŏ擾 .
     * GgafRgb �́A"#FFFFFF"�i#�ȗ��j�`���̕����񂩂�AR�l�AG�l�AB�l�ɕϊ����ĕێ����܂��B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(GgafRgb)
     */
    static GgafRgb getRGB(std::string prm_key);

    /**
     * �ێ��v���p�e�BMAP�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, int prm_value);

    /**
     * �ێ��v���p�e�BMAP�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, uint32_t prm_value);

    /**
     * �ێ��v���p�e�BMAP�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, std::string prm_value);

    /**
     * �ێ��v���p�e�BMAP�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, float prm_value);

    /**
     * �ێ��v���p�e�BMAP�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, double prm_value);

    /**
     * �ێ��v���p�e�BMAP�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, bool prm_value);

    /**
     * �ێ��v���p�e�BMAP�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    static void setValue(std::string prm_key, GgafRgb prm_value);

};

}
#endif /*GGAFCORE_GGAFPROPERTIES_H_*/

