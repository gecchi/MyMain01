#ifndef HOSHIBOSHIRANKUP_H_
#define HOSHIBOSHIRANKUP_H_
namespace VioletVreath {

/**
 * �����N�A�b�v�X�e�[�W�̐��X .
 * @version 1.00
 * @since 2011/10/18
 * @author Masatoshi Tsuge
 */
class HoshiBoshiRankUp : public HoshiBoshi {

public:
    HoshiBoshiRankUp(const char* prm_name);

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~HoshiBoshiRankUp();



};

}
#endif /*HOSHIBOSHITRANSIT_H_*/

