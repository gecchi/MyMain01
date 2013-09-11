#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace GgafLib {

/**
 * ���̐��ʃo�[ .
 * �iVV�̃N���X���珸�i�j
 * @version 1.00
 * @since 2012/09/11
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

public:
    /** ���e�� */
    AmountGraph* pAmount_;
    /** �����s�N�Z�� */
    float chip_width_;
    float rate_org_chip_width_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config�ς݂� AmountGraph�I�u�W�F�N�g�̎Q��
     */
    GraphBarActor(const char* prm_name, const char* prm_model, AmountGraph* prm_pAmount);

    void processBehavior() override;
    void processDraw() override;
    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

