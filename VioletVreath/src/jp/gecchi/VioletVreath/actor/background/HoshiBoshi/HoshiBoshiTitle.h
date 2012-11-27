#ifndef HOSHIBOSHITITLE_H_
#define HOSHIBOSHITITLE_H_

namespace VioletVreath {

/**
 * ���X�|�C���g�X�v���C�g�^�C�g���p .
 * @version 1.00
 * @since 2012/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshiTitle : public HoshiBoshi {

public:
    HoshiBoshiTitle(const char* prm_name);

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void fadein();

    virtual ~HoshiBoshiTitle();
};

}

#endif /*HOSHIBOSHITITLE_H_*/
