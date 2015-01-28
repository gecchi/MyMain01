#ifndef GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_
#define GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/GgafValueEnveloper.hpp"

namespace GgafDxCore {

/**
 * ����J���[�_�Ŏx���N���X.
 * GgafDxModel �̃����o�� _power_blink <BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 * �ŏI�I�Ƀs�N�Z���V�F�[�_�[�ŐF(float4)�ɏ悸��l�ƂȂ�B
 * �F���x 1.0 �͐F���x�����A
 * �F���x 2.0 �͐F���x�Q�{�B���邭�Ȃ�B
 * �F���x 0.5 �͐F���x1/�Q�{�B�Â��Ȃ�B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDxTextureBlinker : public GgafCore::GgafValueEnveloper<float, 1 > {

public:
    /** �ΏۃA�N�^�[ */
    GgafDxModel* const _pModel;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pModel  �K�p�Ώۂ�Model
     */
    GgafDxTextureBlinker(GgafDxModel* prm_pModel);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~GgafDxTextureBlinker();
};

}
#endif /*GGAFDXCORE_GGAFDXTEXTUREBLINKER_H_*/

