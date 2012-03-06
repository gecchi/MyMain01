#ifndef UNIVERSE_H_
#define UNIVERSE_H_
namespace SimpleSample {

/**
 * �u���̐��v�̐��` .
 * GgafLib::DefaultUniverse ���p�����u���̐��v�N���X���쐬���ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class Universe : public GgafLib::DefaultUniverse {

public:

    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    Universe(const char* prm_name, Camera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override {}

    virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
