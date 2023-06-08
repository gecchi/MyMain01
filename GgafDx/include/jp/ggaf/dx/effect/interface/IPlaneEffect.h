#ifndef GGAF_DX_IPLANEEFFECT_H_
#define GGAF_DX_IPLANEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * ���ʃp�l���p�G�t�F�N�g�N���X .
 * @version 1.00
 * @since 2023/06/07
 * @author Masatoshi Tsuge
 */
class IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_dbd_offset_x;
    D3DXHANDLE _h_dbd_offset_y;


    /**
     * �R���X�g���N�^<BR>
     * @return
     */
    IPlaneEffect(Effect* prm_pEffect);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~IPlaneEffect();

};

}
#endif /*GGAF_DX_IPLANEEFFECT_H_*/
