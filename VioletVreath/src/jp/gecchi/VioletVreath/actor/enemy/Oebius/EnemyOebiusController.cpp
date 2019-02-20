#include "EnemyOebiusController.h"

#include "jp/ggaf/core/Element.hpp"
#include "jp/ggaf/core/Progress.h"
#include "FormationOebius001.h"
#include "FormationOebius002.h"
#include "EnemyOebiusCore.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_ENTRY_CORE ,
    PROG_WAIT01 ,
    PROG_ENTRY_FORMATION ,
    PROG_WAIT02 ,
    PROG_BANPEI,
};

EnemyOebiusController::EnemyOebiusController(const char* prm_name, EnemyOebiusCore* prm_pCore,
                                                                   FormationOebius* prm_pFormation) :
  GgafCore::DestructActor(prm_name) {
    _class_name = "EnemyOebiusController";

    pOebiusCore_ = prm_pCore;
    pOebiusCore_->inactivate();
    appendGroupChild(pOebiusCore_);

    pFormationOebius_ = prm_pFormation;
    pFormationOebius_->inactivate();
    appendGroupChild(pFormationOebius_);
}

void EnemyOebiusController::initialize() {
}

void EnemyOebiusController::onActive() {
    getProgress()->reset(PROG_INIT);
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

    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY_CORE: {
            if (pProg->hasJustChanged()) {
                if (pOebiusCore_) {
                    pOebiusCore_->setPositionAt(&entry_pos_);
                    pOebiusCore_->activate();
                }
            }
            pProg->changeNext();
            break;
        }

        case PROG_WAIT01: {
            if (pProg->hasJustChanged()) {
            }
            if (pProg->hasArrivedAt(120)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_ENTRY_FORMATION: {
            if (pProg->hasJustChanged()) {
                if (pFormationOebius_) {
                    pFormationOebius_->activate();
                }
            }

            if (pProg->hasArrivedAt(600)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_WAIT02: {
            if (pProg->hasJustChanged()) {
            }
            if (!pOebiusCore_) {
                //コアがいなくなったら散り散りに
                if (pFormationOebius_) {
                    pFormationOebius_->scatterMember();
                }
                pProg->changeNothing(); //おしまい
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
