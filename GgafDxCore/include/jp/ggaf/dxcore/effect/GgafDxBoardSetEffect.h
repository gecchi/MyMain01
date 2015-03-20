#ifndef GGAFDXCORE_GGAFDXBOARDSETEFFECT_H_
#define GGAFDXCORE_GGAFDXBOARDSETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxBoardSet�p���f���N���X.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDxBoardSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _ah_offset_u[28];
    D3DXHANDLE _ah_offset_v[28];
    D3DXHANDLE _ah_transformed_x[28];
    D3DXHANDLE _ah_transformed_y[28];
    D3DXHANDLE _ah_alpha[28];
    D3DXHANDLE _ah_depth_z[28];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    GgafDxBoardSetEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxEffectManager�ł���<BR>
     */
    virtual ~GgafDxBoardSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCORE_GGAFDXBOARDSETEFFECT_H_*/
