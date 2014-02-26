#ifndef GGAFDXCORE_GGAFDXALPHAFADER_H_
#define GGAFDXCORE_GGAFDXALPHAFADER_H_
#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"

namespace GgafDxCore {

/**
 * �t�F�[�f�B���O�x���N���X .
 * GgafDxDrawableActor �̃����o��
 * _alpha(�A�N�^�[�̃����x)���Ȃ߂炩�ɕω������A<BR>
 * �t�F�[�f�B���O���s�����Ƃ���ȖړI<BR>
 * @version 1.00
 * @since 2010/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaFader : public GgafCore::GgafValueTransitioner<float, 1 > {

public:
    /** [r]�ΏۃA�N�^�[ */
    GgafDxDrawableActor* const _pActor;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    GgafDxAlphaFader(GgafDxDrawableActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~GgafDxAlphaFader();
};

}
#endif /*GGAFDXCORE_GGAFDXALPHAFADER_H_*/

