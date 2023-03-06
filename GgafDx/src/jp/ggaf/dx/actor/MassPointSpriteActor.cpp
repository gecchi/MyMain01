#include "jp/ggaf/dx/actor/MassPointSpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/MassPointSpriteEffect.h"
#include "jp/ggaf/dx/model/MassPointSpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

MassPointSpriteActor::MassPointSpriteActor(const char* prm_name,
                                           const char* prm_model,
                                           const char* prm_effect_id,
                                           const char* prm_technique,
                                           CollisionChecker* prm_pChecker) :

                                             MassActor(prm_name,
                                                       prm_model,
                                                       TYPE_MASSPOINTSPRITE_MODEL,
                                                       prm_effect_id,
                                                       TYPE_MASSPOINTSPRITE_EFFECT,
                                                       prm_technique,
                                                       prm_pChecker),
_pMassPointSpriteModel((MassPointSpriteModel*)_pModel),
_pMassPointSpriteEffect((MassPointSpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek()))
{
    _obj_class |= Obj_GgafDx_MassPointSpriteActor;
    _class_name = "MassPointSpriteActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _pUvFlipper->locatePatternNo(_pMassPointSpriteModel->_texture_split_rowcol,
                             _pMassPointSpriteModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

void MassPointSpriteActor::changeModel(int prm_model_index) {
    FigureActor::changeModel(prm_model_index);
    _pMassPointSpriteModel = (MassPointSpriteModel*)_pModel;
}

MassPointSpriteActor::~MassPointSpriteActor() {
    delete _pUvFlipper;
}
