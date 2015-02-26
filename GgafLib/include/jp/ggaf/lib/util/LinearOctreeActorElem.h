#ifndef GGAFLIB_LINEAROCTREEACTORELEM_H_
#define GGAFLIB_LINEAROCTREEACTORELEM_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"

namespace GgafLib {

/**
 * GgafLinearOctreeElem用の要素クラス .
 * GgafActorを要素することに特化しています
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LinearOctreeActorElem : public GgafCore::GgafLinearOctreeElem {

public:
    GgafCore::GgafActor* const _pActor;

public:
    LinearOctreeActorElem(GgafCore::GgafLinearOctree* prm_pLinearOctree, GgafCore::GgafObject* prm_pObject, uint32_t prm_kindbit) :
        GgafCore::GgafLinearOctreeElem(prm_pLinearOctree, prm_pObject,prm_kindbit) ,
        _pActor((GgafCore::GgafActor*)prm_pObject) {
    }
};

}
#endif /*GGAFLIB_LINEAROCTREEACTORELEM_H_*/

