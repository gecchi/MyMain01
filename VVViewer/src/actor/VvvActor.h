#ifndef SMPACTOR_H_
#define SMPACTOR_H_
namespace VVViewer {

/**
 * �e�X�g�L���� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvActor : public GgafLib::DefaultMeshActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    VvvActor(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~VvvActor();
};

}
#endif /*SMPACTOR_H_*/

