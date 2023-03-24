#ifndef GGAF_DX_ACTORVEHICLE_H_
#define GGAF_DX_ACTORVEHICLE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/dx/util/GeoElem.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * アクターの移動支援基底クラス .
 * @version 1.00
 * @since 2021/03/29
 * @author Masatoshi Tsuge
 */
class ActorVehicle : public GgafCore::Object {

private:

public:
    /** [r]対象アクター */
    GeometricActor* const _pActor;

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    explicit ActorVehicle(GeometricActor* prm_pActor);

    virtual void behave() = 0;

    virtual ~ActorVehicle();
};

}
#endif /*GGAF_DX_ACTORVEHICLE_H_*/
