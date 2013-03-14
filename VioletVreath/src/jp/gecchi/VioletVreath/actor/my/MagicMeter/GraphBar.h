#ifndef GRAPHBAR_H_
#define GRAPHBAR_H_
namespace VioletVreath {

/**
 * �o�[��� .
 * @version 1.00
 * @since 2012/05/1
 * @author Masatoshi Tsuge
 */
class GraphBar : public GgafLib::DefaultBoardActor {

public:
    /** ���e�� */
    GgafLib::AmountGraph* pAmount_;
    /** �����s�N�Z�� */
    pixcoord org_width_;

    double rate_org_width_;

public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config�ς݂� AmountGraph�I�u�W�F�N�g�̎Q��
     */
    GraphBar(const char* prm_name, const char* prm_model, GgafLib::AmountGraph* prm_pAmount);

    virtual ~GraphBar();
};

}
#endif /*GRAPHBAR_H_*/

