#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Magic::Magic(const char* prm_name,
             GgafDx9GeometricActor* prm_pCaster,
             GgafDx9GeometricActor* prm_pReceiver) : DefaultSpriteActor(prm_name, "magic") {
    _cost = 10000000;
    _cast_speed = 60;
    _duration = 1;
    _state = MAGIC_STAND_BY;
    _pCaster = prm_pCaster;
    _pReceiver = prm_pReceiver;
}

void Magic::processBehavior() {
    if (_pCaster->isActive() && _pReceiver->isActive() ) {
        switch (_state) {
            case MAGIC_STAND_BY:
                break;
            case MAGIC_CASTING:
                _cost = _cost - _dec_cost;
                if (_cost < 0) {
                    invoke();
                } else {
                    processCastingBehavior();
                }
                break;
            case MAGIC_INVOKEING:
                _duration --;
                if (_duration < 0) {
                    expire();
                } else {
                    processInvokeingBehavior();
                }
                break;
            case MAGIC_EXPIRING:
                processExpiringBehavior();
                break;
            default :
                _TRACE_("Magic::processBehavior おかしいですぜ _state="<<_state);
                break;
        }
    } else {
        if (_state != MAGIC_ABANDONING) {
            abandon();
        } else {
            processAbandoningBehavior();
        }
    }
}

Magic::~Magic() {
}
