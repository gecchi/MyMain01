#include "EnemyErelmanController.h"

#include "jp/ggaf/core/Element.hpp"
#include "jp/ggaf/core/Phase.h"
#include "FormationErelman001.h"
#include "FormationErelman002.h"
#include "EnemyErelmanCore.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_ENTRY_CORE ,
    PHASE_WAIT01 ,
    PHASE_ENTRY_FORMATION ,
    PHASE_WAIT02 ,
    PHASE_BANPEI,
};

EnemyErelmanController::EnemyErelmanController(const char* prm_name, EnemyErelmanCore* prm_pCore,
                                                                   FormationErelman* prm_pFormation) :
  GgafCore::DestructActor(prm_name) {
    _class_name = "EnemyErelmanController";

    pErelmanCore_ = prm_pCore;
    pErelmanCore_->inactivate();
    appendChild(pErelmanCore_);

    pFormationErelman_ = prm_pFormation;
    pFormationErelman_->inactivate();
    appendChild(pFormationErelman_);
}

void EnemyErelmanController::initialize() {
}

void EnemyErelmanController::onActive() {
    getPhase()->reset(PHASE_INIT);
}

void EnemyErelmanController::processBehavior() {
    if (pErelmanCore_) {
        if (pErelmanCore_->wasDeclaredEnd()) {
            pErelmanCore_ = nullptr;
        }
    }
    if (pFormationErelman_) {
        if (pFormationErelman_->wasDeclaredEnd()) {
            pFormationErelman_ = nullptr;
        }
    }

    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY_CORE: {
            if (pPhase->hasJustChanged()) {
                if (pErelmanCore_) {
                    pErelmanCore_->setPositionAt(&entry_pos_);
                    pErelmanCore_->activate();
                }
            }
            pPhase->changeNext();
            break;
        }

        case PHASE_WAIT01: {
            if (pPhase->hasJustChanged()) {
            }
            if (pPhase->hasArrivedFrameAt(120)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_ENTRY_FORMATION: {
            if (pPhase->hasJustChanged()) {
                if (pFormationErelman_) {
                    pFormationErelman_->activate();
                }
            }

            if (pPhase->hasArrivedFrameAt(600)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_WAIT02: {
            if (pPhase->hasJustChanged()) {
            }
            if (!pErelmanCore_) {
                //コアがいなくなったら散り散りに
                if (pFormationErelman_) {
                    pFormationErelman_->scatterMember();
                }
                pPhase->changeNothing(); //おしまい
            }
            break;
        }

        default :
            break;
    }

    //コアとフォーメーションの座標と向きの同期を取る
    if (pErelmanCore_ && pFormationErelman_) {
        pFormationErelman_->setPosition(pErelmanCore_->_x,
                                        pErelmanCore_->_y,
                                        pErelmanCore_->_z );
        pFormationErelman_->setAng(pErelmanCore_->_rx,
                                   pErelmanCore_->_ry,
                                   pErelmanCore_->_rz);
    }

}

EnemyErelmanController::~EnemyErelmanController() {
}
