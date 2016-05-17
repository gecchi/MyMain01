#ifndef GGAFDXCORE_GGAFDXMASSBOARDEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSBOARDEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassBoard�p���f���N���X.
 * @version 1.00
 * @since 2015/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassBoardEffect : public GgafDxMassEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxMassBoardEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxEffectManager�ł���<BR>
     */
    virtual ~GgafDxMassBoardEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXMASSBOARDEFFECT_H_*/
