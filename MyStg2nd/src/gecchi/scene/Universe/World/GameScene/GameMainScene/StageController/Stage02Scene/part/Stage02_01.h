#ifndef STAGE02_01_H_
#define STAGE02_01_H_
namespace MyStg2nd {

/**
 * �X�e�[�W2�|�P .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage02_01 : public GgafDx9LibStg::DefaultScene {


public:

    Stage02_01(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage02_01();
};

}
#endif /*STAGE02_01_H_*/
