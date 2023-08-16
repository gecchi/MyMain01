#include "jp/ggaf/dx/effect/interface/IPlaneEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

IPlaneEffect::IPlaneEffect(Effect* prm_pEffect) {
    //Effect�� adjustDotByDot() �p
    ID3DXEffect* pID3DXEffect = prm_pEffect->_pID3DXEffect;

    _h_dbd_offset_x = pID3DXEffect->GetParameterByName( nullptr, "g_dbd_offset_x" );
    //pID3DXEffect->SetFloat(_h_dbd_offset_x, (2.0 / CONFIG::RENDER_TARGET_BUFFER_WIDTH ) * 0.5); //�ˉe�ϊ����1px�̕�  * 0.5 (2.0 �� -1 �` +1 �̋���)
    pID3DXEffect->SetFloat(_h_dbd_offset_x, (1.0 / CONFIG::RENDER_TARGET_BUFFER_WIDTH ));
    _h_dbd_offset_y = pID3DXEffect->GetParameterByName( nullptr, "g_dbd_offset_y" );
    //pID3DXEffect->SetFloat(_h_dbd_offset_y, (2.0 / CONFIG::RENDER_TARGET_BUFFER_HEIGHT) * 0.5);  //�ˉe�ϊ����1px�̍��� * 0.5(2.0 �� -1 �` +1 �̋���)
    pID3DXEffect->SetFloat(_h_dbd_offset_y, (1.0 / CONFIG::RENDER_TARGET_BUFFER_HEIGHT));

}

IPlaneEffect::~IPlaneEffect() {
}

