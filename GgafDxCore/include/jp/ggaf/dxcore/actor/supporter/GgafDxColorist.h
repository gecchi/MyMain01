#ifndef GGAFDXCORE_GGAFDXCOLORIST_H_
#define GGAFDXCORE_GGAFDXCOLORIST_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"

namespace GgafDxCore {

/**
 * カラーリストさん.
 * @version 1.00
 * @since 2011/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxColorist : public GgafCore::GgafValueEnveloper<float, 3 > {

public:
    /** 対象アクター */
    GgafDxFigureActor* const _pActor;
    float* _pa_diffuse[3];

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
    explicit GgafDxColorist(GgafDxFigureActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    /**
     * ピカピカとフラッシュします。
     * @param prm_flush_max_color 一番明るい色の強度を指定(0.0〜1.0)
     * @param prm_flush_freames   一番明るい色で光っている時間（フレーム）
     * @param prm_rest_freames    消えている時間（フレーム）
     * @param prm_flush_num       点滅回数
     */
    void flush(float prm_flush_max_color, frame prm_flush_freames, frame prm_rest_freames, double prm_flush_num);

    virtual ~GgafDxColorist();
};

}
#endif /*GGAFDXCORE_GGAFDXCOLORIST_H_*/

