#ifndef GGAFDXCORE_GGAFDXCOLORIST_H_
#define GGAFDXCORE_GGAFDXCOLORIST_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"

namespace GgafDxCore {

/**
 * �J���[���X�g����.
 * @version 1.00
 * @since 2011/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxColorist : public GgafCore::GgafValueEnveloper<float, 3 > {

public:
    /** �ΏۃA�N�^�[ */
    GgafDxFigureActor* const _pActor;
    float* _pa_diffuse[3];

    enum {
        RED = 0,
        GREEN = 1,
        BLUE = 2,
    };

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    explicit GgafDxColorist(GgafDxFigureActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    void flush(float prm_flush_max_color, frame prm_flush_freames, frame prm_rest_freames, double prm_flush_num);

    virtual ~GgafDxColorist();
};

}
#endif /*GGAFDXCORE_GGAFDXCOLORIST_H_*/

