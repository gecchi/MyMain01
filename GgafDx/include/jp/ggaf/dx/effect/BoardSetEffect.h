#ifndef GGAF_DX_BOARDSETEFFECT_H_
#define GGAF_DX_BOARDSETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * BoardSet�p���f���N���X.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class BoardSetEffect : public Effect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_colMaterialDiffuse;
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
    BoardSetEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�EffectManager�ł���<BR>
     */
    virtual ~BoardSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_BOARDSETEFFECT_H_*/
