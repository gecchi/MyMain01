#ifndef STAGE03_H_
#define STAGE03_H_
namespace VioletVreath {

/**
 * �X�e�[�W03 .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Stage03 : public Stage {

public:
    Stage03(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage03();
};

}
#endif /*STAGE03_H_*/
