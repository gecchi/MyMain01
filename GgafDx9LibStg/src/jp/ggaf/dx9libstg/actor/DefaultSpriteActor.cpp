#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model) :
    GgafDx9SpriteActor(prm_name,
                       prm_model,
                       "S/DefaultSpriteEffect",
                       "DefaultSpriteTechnique",
                       NEW GgafDx9GeometryMover(this),
                       NEW StgChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _dwFrameOffset = 0;
    _pChecker = (StgChecker*)_pGeoChecker;
}

#ifdef OREDEBUG

void DefaultSpriteActor::processDrawTerminate() {
    //“–‚½‚è”»’è—Ìˆæ•\Ž¦
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    DelineateActor::get()->drawHitarea(_pChecker);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

#else

void DefaultSpriteActor::processDrawTerminate() {}

#endif

bool DefaultSpriteActor::isOffScreen() {
    if (_X < _X_OffScreenLeft) {
        return true;
    } else {
        if (_X > _X_OffScreenRight) {
            return true;
        } else {
            if (_Y > _Y_OffScreenTop) {
                return true;
            } else {
                if (_Y < _Y_OffScreenBottom) {
                    return true;
                } else {
                    if (_Z < GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                        return true;
                    } else {
                        if (_Z > -1 * GgafDx9God::_dCamZ * LEN_UNIT * 10) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }
    }
}
DefaultSpriteActor::~DefaultSpriteActor() {
    TRACE("DefaultSpriteActor::~DefaultSpriteActor() "<<getName()<<" start--->");TRACE("DefaultSpriteActor::~DefaultSpriteActor() "<<getName()<<" <---end");
}
