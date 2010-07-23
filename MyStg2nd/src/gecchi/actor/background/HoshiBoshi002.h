#ifndef HOSHIBOSHI002_H_
#define HOSHIBOSHI002_H_
namespace MyStg2nd {
//���ݖ��g�p
/**
 * �����G�t�F�N�g�X�v���C�g002
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshi002 : public GgafDx9LibStg::DefaultPointSpriteActor {

public:
    int _CAM_ZF;

    HoshiBoshi002(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    void processPreDraw() override;

    int isOffscreen() override;

    bool isOutOfGameSpace() override;

    virtual ~HoshiBoshi002();
};

}
#endif /*HOSHIBOSHI002_H_*/

