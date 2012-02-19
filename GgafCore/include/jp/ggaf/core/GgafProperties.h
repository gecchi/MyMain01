#ifndef GGAFPROPERTIES_H_
#define GGAFPROPERTIES_H_

#ifdef GGAF_PROPERTY
    #undef GGAF_PROPERTY
#endif
#define GGAF_PROPERTY(X) (GgafCore::GgafProperties::X)

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
    static UINT32 MAX_SKIP_FRAME;
    /** [r/w] 60fps��40fps�̏����������o���s�����ǂ����̋��E�B1�t���[������������`��񐔂Őݒ� */
    static int DRAWNUM_TO_SLOWDOWN1;
    /** [r/w] 40fps��30fps�̏����������o���s�����ǂ����̋��E�B1�t���[������������`��񐔂Őݒ� */
    static int DRAWNUM_TO_SLOWDOWN2;
    /** [r/w] �S�~����|��(�C���X�^���X���)���s�����Ƃ��o����FPS */
    static float FPS_TO_CLEAN_GARBAGE_BOX;
    /** [r] �ێ��v���p�e�BMAP */
    static GgafStrMap* _pMapProperties;

    /**
     * �O���v���p�e�B�t�@�C�����疢���[�h�Ȃ烍�[�h���ăv���p�e�B�ێ� .
     * @param prm_properties_filename �v���p�e�B�t�@�C��
     */
    static void load(std::string prm_properties_filename);

    /**
     * �ێ��v���p�e�B����� .
     */
    static void clean();

    /**
     * �ێ��v���p�e�B�ɃL�[�����݂��邩���ׂ� .
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
     * �L�[�ɑ΂���v���p�e�B�l�� float �Ŏ擾 .
     * ������ atoi() ���g�p�B
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(int)
     */
    static int getInt(std::string prm_key);

    /**
     * �L�[�ɑ΂���v���p�e�B�l�� UINT32 �Ŏ擾 .
     * ������ _atoi64() ���āAUINT32�ɃL���X�g
     * @param prm_key �L�[������
     * @return �v���p�e�B�l(UINT32)
     */
    static UINT32 getUInt(std::string prm_key);

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

};

}
#endif /*GGAFPROPERTIES_H_*/

