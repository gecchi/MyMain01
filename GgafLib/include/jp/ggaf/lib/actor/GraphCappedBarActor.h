#ifndef GRAPHCAPPEDBARACTOR_H_
#define GRAPHCAPPEDBARACTOR_H_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace GgafLib {

/**
 * ���ʃo�[(���[�e�N�X�`���L��) .
 * @version 1.00
 * @since 2012/09/11
 * @author Masatoshi Tsuge
 */
class GraphCappedBarActor : public GraphBarActor {

public:

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @param prm_model
     * @param prm_pPxQuantity
     */
    GraphCappedBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity);

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @param prm_model
     * @param prm_pPxQuantity
     */
    GraphCappedBarActor(const char* prm_name, const char* prm_model);

    void processDraw() override;
    virtual ~GraphCappedBarActor();
};

}
#endif /*GRAPHCAPPEDBARACTOR_H_*/

