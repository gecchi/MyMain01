#include "jp/ggaf/dx/actor/supporter/Colorist.h"

#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "d3d9types.h"


using namespace GgafDx;


enum {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
};

Colorist::Colorist(FigureActor* prm_pActor) : GgafCore::ValueTransitioner<float, 3 > (),
_pActor(prm_pActor) {
    _pa_diffuse[RED]   = &(_pActor->_paMaterial[0].Diffuse.r);
    _pa_diffuse[GREEN] = &(_pActor->_paMaterial[0].Diffuse.g);
    _pa_diffuse[BLUE]  = &(_pActor->_paMaterial[0].Diffuse.b);
    setRange(0, 1.0);
}

void Colorist::reset() {
    GgafCore::ValueTransitioner<float, 3 >::reset();
}

float Colorist::getValue(int idx) {
    return (*(_pa_diffuse[idx]));
}

void Colorist::setValue(int idx, float value) {
    int num_materials = _pActor->getModel()->_num_materials;
    D3DMATERIAL9* paMaterial = _pActor->_paMaterial;
    switch (idx) {
        case RED:
            for (int i = 0; i < num_materials; i++) {
                paMaterial[i].Ambient.r = value;
                paMaterial[i].Diffuse.r = value;
            }
            break;
        case GREEN:
            for (int i = 0; i < num_materials; i++) {
                paMaterial[i].Ambient.g = value;
                paMaterial[i].Diffuse.g = value;
            }
            break;
        case BLUE:
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

void Colorist::flush(float prm_flush_max_color, frame prm_flush_freames, frame prm_rest_freames, double prm_flush_num) {
    D3DMATERIAL9* paMaterial_default = _pActor->getModel()->_paMaterial_default;
    float default_red   = paMaterial_default[0].Diffuse.r;
    float default_green = paMaterial_default[0].Diffuse.g;
    float default_blue  = paMaterial_default[0].Diffuse.b;
    setRange(RED  , default_red  , prm_flush_max_color);
    setRange(GREEN, default_green, prm_flush_max_color);
    setRange(BLUE , default_blue , prm_flush_max_color);
    beat(prm_flush_freames + prm_rest_freames, 0, prm_flush_freames, 0, prm_flush_num);
}

Colorist::~Colorist() {
}
