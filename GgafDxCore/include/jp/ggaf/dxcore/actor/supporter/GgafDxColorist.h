#ifndef GGAFDXCORE_GGAFDXCOLORIST_H_
#define GGAFDXCORE_GGAFDXCOLORIST_H_
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"

namespace GgafDxCore {

/**
 * カラーリストさん.
 * @version 1.00
 * @since 2011/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxColorist : public GgafCore::GgafValueTransitioner<float, 3 > {

public:
    /** 対象アクター */
    GgafDxDrawableActor* const _pActor;
    float* _apDiffuse[3];

    enum {
        RED = 0,
        GREEN = 1,
        BLUE = 2,
    };
public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    GgafDxColorist(GgafDxDrawableActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~GgafDxColorist();
};

}
#endif /*GGAFDXCORE_GGAFDXCOLORIST_H_*/

