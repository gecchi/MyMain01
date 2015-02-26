#ifndef GGAFLIB_LINEAROCTREEACTORELEM_H_
#define GGAFLIB_LINEAROCTREEACTORELEM_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"

namespace GgafLib {

/**
 * GgafLinearOctreeElem�p�̗v�f�N���X .
 * GgafActor��v�f���邱�Ƃɓ������Ă��܂�
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

