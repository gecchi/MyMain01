#ifndef HOSHIBOSHIEFFECT_H_
#define HOSHIBOSHIEFFECT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/dx/effect/PointSpriteEffect.h"

namespace VioletVreath {

/**
 * Hoshiboshi�p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class HoshiboshiEffect : public GgafDx::PointSpriteEffect {
    friend class EffectManager;

public:
    D3DXHANDLE h_fX_MyShip_;
    D3DXHANDLE h_fY_MyShip_;
    D3DXHANDLE h_fZ_MyShip_;
    D3DXHANDLE h_far_rate_;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g���ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     * @return
     */
    HoshiboshiEffect(const char* prm_effect_name);


    virtual ~HoshiboshiEffect();

};

}
#endif /*HOSHIBOSHIEFFECT_H_*/
