#ifndef GGAF_CORE_PROPERTIES_H_
#define GGAF_CORE_PROPERTIES_H_
#include "GgafCommonHeader.h"

#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/Rgb.h"

namespace GgafCore {

/**
 * �v���p�e�B�N���X .
 * �O���t�@�C�����烍�[�h���A�A�v���̊��ϐ��Ƃ��ĕێ����܂��B
 * @version 1.00
 * @since 2008/07/22
 * @author Masatoshi Tsuge
 */
class Properties : public Object {


public:
    /** [r] �ێ��v���p�e�B */
    StrMap _mapProperties;

public:
    Properties();

    Properties(std::string prm_properties_filename);

    /**
     * �O���v���p�e�B�t�@�C�����疢���[�h�Ȃ烍�[�h���ĕێ��v���p�e�B�֐ݒ�A�����o�ϐ��ɔ��f .
     * @param prm_properties_filename �v���p�e�B�t�@�C��
     */
    void read(std::string prm_properties_filename);

    void read(std::istream& is);

    /**
     * �ێ��v���p�e�B���A�O���v���p�e�B�t�@�C���֕ۑ� .
     * @param prm_properties_filename �v���p�e�B�t�@�C��
     */
    void write(std::string prm_properties_filename, const char *header = nullptr);

    void write(std::ostream &os, const char *header = nullptr);

    void print(std::ostream &os);


    /**
     * �ێ��v���p�e�B�ɃL�[�����݂��邩���ׂ� .
     * @param prm_key �L�[������
     * @return true:�L�[������ / false:���݂��Ȃ�
     */
    bool isExistKey(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� string �Ŏ擾 .
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(string)
     */
    std::string getStr(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l��bool�Ŏ擾 .
     * true, on, yes �̕�����̏ꍇ true �Ƃ݂Ȃ��A����ȊO�� false�B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(bool)
     */
    bool getBool(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� float �Ŏ擾 .
     * ������ atof() ���g�p�B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(float)
     */
    float getFloat(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� int �Ŏ擾 .
     * ������ atoi() ���g�p�B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(int)
     */
    int getInt(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� uint32_t �Ŏ擾 .
     * ������ _atoi64() ���āAuint32_t�ɃL���X�g
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(uint32_t)
     */
    uint32_t getUInt(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� double �Ŏ擾 .
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(double)
     */
    double getDouble(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� Rgb �Ŏ擾 .
     * Rgb �́A"#FFFFFF"�i#�ȗ��j�`���̕����񂩂�AR�l�AG�l�AB�l�ɕϊ����ĕێ����܂��B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(Rgb)
     */
    Rgb getRGB(std::string prm_key);

    /**
     * �ێ��v���p�e�B�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, int prm_value);

    /**
     * �ێ��v���p�e�B�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, uint32_t prm_value);

    /**
     * �ێ��v���p�e�B�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, std::string prm_value);

    /**
     * �ێ��v���p�e�B�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, float prm_value);

    /**
     * �ێ��v���p�e�B�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, double prm_value);

    /**
     * �ێ��v���p�e�B�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, bool prm_value);

    /**
     * �ێ��v���p�e�B�ɒl��ݒ�B
     * �ݒ肵�Ă������o�ɂ͂܂����f����܂���B
     * @param prm_key
     * @param prm_value
     */
    void setValue(std::string prm_key, Rgb prm_value);

};

}
#endif /*GGAF_CORE_PROPERTIES_H_*/
