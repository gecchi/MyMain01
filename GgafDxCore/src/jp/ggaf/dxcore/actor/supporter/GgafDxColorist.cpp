#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxColorist.h"

#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxColorist::GgafDxColorist(GgafDxDrawableActor* prm_pActor) : GgafValueTransitioner<float, 3 > (),
_pActor(prm_pActor) {
    _pa_diffuse[0] = &(prm_pActor->_paMaterial[0].Diffuse.r);
    _pa_diffuse[1] = &(prm_pActor->_paMaterial[0].Diffuse.g);
    _pa_diffuse[2] = &(prm_pActor->_paMaterial[0].Diffuse.b);
    forceRange(0, 1.0);
}

void GgafDxColorist::reset() {
    GgafValueTransitioner<float, 3 >::reset();
    forceRange(0, 1.0);
}

float GgafDxColorist::getValue(int idx) {
    return (*(_pa_diffuse[idx]));
}

void GgafDxColorist::setValue(int idx, float value) {
    int num_materials = _pActor->getModel()->_num_materials;
    D3DMATERIAL9* paMaterial = _pActor->_paMaterial;
    switch (idx) {
        case 0: //RED
            for (int i = 0; i < num_materials; i++) {
                paMaterial[i].Ambient.r = value;
                paMaterial[i].Diffuse.r = value;
            }
            break;
        case 1: //GREEN
            for (int i = 0; i < num_materials; i++) {
                paMaterial[i].Ambient.g = value;
                paMaterial[i].Diffuse.g = value;
            }
            break;
        case 2: //BRUE
            for (int i = 0; i < num_materials; i++) {
                paMaterial[i].Ambient.b = value;
                paMaterial[i].Diffuse.b = value;
            }
            break;
        default: {
            break;
        }
    }
}

GgafDxColorist::~GgafDxColorist() {
}
