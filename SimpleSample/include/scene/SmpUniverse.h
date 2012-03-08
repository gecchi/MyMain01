#ifndef SMPUNIVERSE_H_
#define SMPUNIVERSE_H_
namespace SimpleSample {

/**
 * �u���̐��v�̐��` .
 * GgafLib::DefaultUniverse ���p�����u���̐��v�N���X���쐬���ĉ������B
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpUniverse : public GgafLib::DefaultUniverse {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    SmpUniverse(const char* prm_name, SmpCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override {}

    virtual ~SmpUniverse();
};

}
#endif /*SMPUNIVERSE_H_*/
