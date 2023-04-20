#ifndef GGAF_DX_COLORIST_H_
#define GGAF_DX_COLORIST_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ValueTransitioner.hpp"

namespace GgafDx {

/**
 * カラーリストさん.
 * @version 1.00
 * @since 2011/07/28
 * @author Masatoshi Tsuge
 */
class Colorist : public GgafCore::ValueTransitioner<float, 3 > {

public:
    /** 対象アクター */
    FigureActor* const _pActor;
    float* _pa_diffuse[3];

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用対象のActor
     */
    explicit Colorist(FigureActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    /**
     * ピカピカとフラッシュします。
     * @param prm_flush_max_color 一番明るい色の強度を指定(0.0～1.0)
     * @param prm_flush_freames   一番明るい色で光っている時間（フレーム）
     * @param prm_rest_freames    消えている時間（フレーム）
     * @param prm_flush_num       点滅回数
     */
    void flush(float prm_flush_max_color, frame prm_flush_freames, frame prm_rest_freames, double prm_flush_num);

    virtual ~Colorist();
};

}
#endif /*GGAF_DX_COLORIST_H_*/

