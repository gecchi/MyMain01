#ifndef HOSHIBOSHITRANSIT_H_
#define HOSHIBOSHITRANSIT_H_
namespace VioletVreath {

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
#endif /*HOSHIBOSHITRANSIT_H_*/

