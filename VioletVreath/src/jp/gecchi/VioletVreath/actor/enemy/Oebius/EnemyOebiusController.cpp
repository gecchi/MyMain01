#include "EnemyOebiusController.h"

#include "jp/ggaf/core/Element.hpp"
#include "jp/ggaf/core/Phase.h"
#include "FormationOebius001.h"
#include "FormationOebius002.h"
#include "EnemyOebiusCore.h"



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

EnemyOebiusController::EnemyOebiusController(const char* prm_name, EnemyOebiusCore* prm_pCore,
                                                                   FormationOebius* prm_pFormation) :
  GgafCore::DestructActor(prm_name) {
    _class_name = "EnemyOebiusController";

    pOebiusCore_ = prm_pCore;
    pOebiusCore_->inactivate();
    appendChild(pOebiusCore_);

    pFormationOebius_ = prm_pFormation;
    pFormationOebius_->inactivate();
    appendChild(pFormationOebius_);
}

void EnemyOebiusController::initialize() {
}

void EnemyOebiusController::onActive() {
    getPhase()->reset(PHASE_INIT);
}

void EnemyOebiusController::processBehavior() {
    if (pOebiusCore_) {
        if (pOebiusCore_->wasDeclaredEnd()) {
            pOebiusCore_ = nullptr;
        }
    }
    if (pFormationOebius_) {
        if (pFormationOebius_->wasDeclaredEnd()) {
            pFormationOebius_ = nullptr;
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
                if (pOebiusCore_) {
                    pOebiusCore_->setPositionAt(&entry_pos_);
                    pOebiusCore_->activate();
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
                if (pFormationOebius_) {
                    pFormationOebius_->activate();
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
            if (!pOebiusCore_) {
                //コアがいなくなったら散り散りに
                if (pFormationOebius_) {
                    pFormationOebius_->scatterMember();
                }
                pPhase->changeNothing(); //おしまい
            }
            break;
        }

        default :
            break;
    }

    //コアとフォーメーションの座標と向きの同期を取る
    if (pOebiusCore_ && pFormationOebius_) {
        pFormationOebius_->setPosition(pOebiusCore_->_x,
                                       pOebiusCore_->_y,
                                       pOebiusCore_->_z );
        pFormationOebius_->setAng(pOebiusCore_->_rx,
                                  pOebiusCore_->_ry,
                                  pOebiusCore_->_rz);
    }

}

EnemyOebiusController::~EnemyOebiusController() {
}
