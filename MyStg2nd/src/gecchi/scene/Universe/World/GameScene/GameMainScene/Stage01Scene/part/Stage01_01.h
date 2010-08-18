#ifndef STAGE01_01_H_
#define STAGE01_01_H_
namespace MyStg2nd {

/**
 * �X�e�[�W�P�|�P .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01_01 : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01_01(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01_01();
};

}
#endif /*STAGE01_01_H_*/
