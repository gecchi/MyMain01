#ifndef HOSHIBOSHI001_H_
#define HOSHIBOSHI001_H_
namespace MyStg2nd {

/**
 * ���X�|�C���g�X�v���C�g001 .
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshiTransit : public HoshiBoshi {

public:
    HoshiBoshiTransit(const char* prm_name);

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~HoshiBoshiTransit();



};

}
#endif /*HOSHIBOSHI001_H_*/

