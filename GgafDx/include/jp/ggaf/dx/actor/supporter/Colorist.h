#ifndef GGAF_DX_COLORIST_H_
#define GGAF_DX_COLORIST_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/TransitionValueSet.hpp"

namespace GgafDx {

/**
 * �J���[���X�g����.
 * @version 1.00
 * @since 2011/07/28
 * @author Masatoshi Tsuge
 */
class Colorist : public GgafCore::TransitionValueSet<float, 3 > {

public:
    /** �ΏۃA�N�^�[ */
    FigureActor* const _pActor;
    float* _pa_diffuse[3];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    explicit Colorist(FigureActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    /**
     * �s�J�s�J�ƃt���b�V�����܂��B
     * @param prm_flush_max_color ��Ԗ��邢�F�̋��x���w��(0.0�`1.0)
     * @param prm_flush_freames   ��Ԗ��邢�F�Ō����Ă��鎞�ԁi�t���[���j
     * @param prm_rest_freames    �����Ă��鎞�ԁi�t���[���j
     * @param prm_flush_num       �_�ŉ�
     */
    void flush(float prm_flush_max_color, frame prm_flush_freames, frame prm_rest_freames, double prm_flush_num);

    virtual ~Colorist();
};

}
#endif /*GGAF_DX_COLORIST_H_*/

