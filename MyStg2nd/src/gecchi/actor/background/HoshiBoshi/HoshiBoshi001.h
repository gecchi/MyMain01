#ifndef HOSHIBOSHI001_H_
#define HOSHIBOSHI001_H_
namespace MyStg2nd {

/**
 * ���X�|�C���g�X�v���C�g001 .
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi001 : public HoshiBoshi {

public:
    HoshiBoshi001(const char* prm_name);

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~HoshiBoshi001();



};

}
#endif /*HOSHIBOSHI001_H_*/
