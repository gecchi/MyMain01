#ifndef GGAF_DX_ALPHAFADER_H_
#define GGAF_DX_ALPHAFADER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/TransitionValueSet.hpp"

namespace GgafDx {

/**
 * �t�F�[�f�B���O�x���N���X .
 * �A�N�^�[�̃����x���Ȃ߂炩�ɕω������A<BR>
 * �t�F�[�f�B���O���s�����Ƃ���ȖړI<BR>
 * @version 1.00
 * @since 2010/07/28
 * @author Masatoshi Tsuge
 */
class AlphaFader : public GgafCore::TransitionValueSet<float, 1 > {

public:
    /** [r]�ΏۃA�N�^�[ */
    FigureActor* const _pActor;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    explicit AlphaFader(FigureActor* prm_pActor);

    void reset() override;

    float getValue(int idx) override;

    void setValue(int idx, float value) override;

    virtual ~AlphaFader();
};

}
#endif /*GGAF_DX_ALPHAFADER_H_*/

