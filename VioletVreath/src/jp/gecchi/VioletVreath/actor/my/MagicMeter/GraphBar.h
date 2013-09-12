#ifndef GRAPHBAR_H_
#define GRAPHBAR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

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
    GgafLib::PxQuantity* pPxQuantity_;
    /** �����s�N�Z�� */
    pixcoord org_width_;
    double rate_org_width_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    GraphBar(const char* prm_name, const char* prm_model, GgafLib::PxQuantity* prm_pPxQuantity);

    void processBehavior() override;
    void processDraw() override;
    virtual ~GraphBar();
};

}
#endif /*GRAPHBAR_H_*/

