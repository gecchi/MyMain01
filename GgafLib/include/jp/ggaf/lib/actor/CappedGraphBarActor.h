#ifndef CAPPEDGRAPHBARACTOR_H_
#define CAPPEDGRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace GgafLib {

/**
 * ���ʃo�[(���[�e�N�X�`���L��) .
 * �e�N�X�`���̔ԍ��́A <=> �� "<" �̔ԍ��ɍ��킹�邱�ƁB
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class CappedGraphBarActor : public GraphBarActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @param prm_model
     * @param prm_pPxQty
     */
    CappedGraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQty);

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @param prm_model
     * @param prm_pPxQty
     */
    CappedGraphBarActor(const char* prm_name, const char* prm_model);

    void processDraw() override;

    virtual ~CappedGraphBarActor();
};

}
#endif /*CAPPEDGRAPHBARACTOR_H_*/

