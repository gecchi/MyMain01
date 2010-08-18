#ifndef STAGE01_03_H_
#define STAGE01_03_H_
namespace MyStg2nd {

/**
 * �X�e�[�W�P�|�R .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01_03 : public GgafDx9LibStg::DefaultScene {

    GgafDx9Core::GgafDx9Bgm* _bgm_st1;

public:

    Stage01_03(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01_03();
};

}
#endif /*STAGE01_03_H_*/