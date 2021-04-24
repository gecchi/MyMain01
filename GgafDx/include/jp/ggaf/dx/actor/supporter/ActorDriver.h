#ifndef GGAF_DX_ACTORDRIVER_H_
#define GGAF_DX_ACTORDRIVER_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/dx/util/GeoElem.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * �A�N�^�[�̉^�]�� .
 * @version 1.00
 * @since 2021/03/29
 * @author Masatoshi Tsuge
 */
class ActorDriver : public GgafCore::Object {

private:

public:
    /** [r]�ΏۃA�N�^�[ */
    GeometricActor* const _pActor;


public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    explicit ActorDriver(GeometricActor* prm_pActor);

    virtual void behave() = 0;

    virtual ~ActorDriver();
};

}
#endif /*GGAF_DX_ACTORDRIVER_H_*/

