#ifndef GGAF_LIB_HITAREA2D_H_
#define GGAF_LIB_HITAREA2D_H_
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

#include "jp/ggaf/dx/actor/supporter/Checker.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/LibConfig.h"

namespace GgafLib {


/**
 * 2D“–‚½‚è”»’è—p .
 * @version 1.00
 * @since 2022/08/09
 * @author Masatoshi Tsuge
 */
template<class T>
class HitArea2D : public DefaultGeometricActor {

protected:

    T* _pActor2D;

public:

    HitArea2D(T* prm_pActor2D) :
        DefaultGeometricActor("HitArea2D", UTIL::createChecker(this))
    {
        _pActor2D = prm_pActor2D;
    }

    virtual void processPreJudgement() override {
        if (_pChecker) {
            if (_can_hit_flg) {
                //–Ø“o˜^
                static coord w = PX_C(CONFIG::RENDER_TARGET_BUFFER_WIDTH);
                static coord h = PX_C(CONFIG::RENDER_TARGET_BUFFER_HEIGHT);
                coord left = -(w/2);
                coord top =  h/2;
                _x = left + _pActor2D->_x;
                _y = top  + (-1 * _pActor2D->_y);
                _pChecker->updateHitArea();
            }
        }
    }
    virtual void onHit(const Actor* prm_pOtherActor) override {
        _TRACE_("HitArea2D::onHit!!!!");
    }

    virtual ~HitArea2D() {
    }
};

}
#endif /*GGAF_LIB_HITAREA2D_H_*/

