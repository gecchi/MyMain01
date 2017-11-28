#include "EnemyOebiusController.h"

#include "jp/ggaf/core/GgafElement.hpp"
#include "jp/ggaf/core/GgafProgress.h"
#include "FormationOebius001.h"
#include "FormationOebius002.h"
#include "EnemyOebiusCore.h"

using namespace GgafCore;
using namespace GgafDxCore;
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
  GgafDestructActor(prm_name, nullptr) {
    _class_name = "EnemyOebiusController";
    useProgress(PROG_BANPEI);

    pOebiusCore_ = prm_pCore;
    pOebiusCore_->inactivate();
    addSubGroup(pOebiusCore_);

    pFormationOebius_ = prm_pFormation;
    pFormationOebius_->inactivate();
    addSubGroup(pFormationOebius_);
}

void EnemyOebiusController::initialize() {
}

void EnemyOebiusController::onActive() {
    getProgress()->reset(PROG_INIT);
}

void EnemyOebiusController::processBehavior() {

    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY_CORE: {
            if (pProg->hasJustChanged()) {
                pOebiusCore_->setPositionAt(&entry_pos_);
                pOebiusCore_->activate();
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
                if (pOebiusCore_) {
                    pFormationOebius_->setPosition(pOebiusCore_->_x,
                                                pOebiusCore_->_y,
                                                pOebiusCore_->_z  );
                    pFormationOebius_->setRzRyAng(pOebiusCore_->_rz, pOebiusCore_->_ry);
                    pFormationOebius_->activate();
                }
            }
            if (pProg->hasArrivedAt(300)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_WAIT02: {
            if (pProg->hasJustChanged()) {
            }
            if (pOebiusCore_ == nullptr) {
                //ƒRƒA‚ª‚¢‚È‚­‚È‚Á‚½‚çŽU‚èŽU‚è‚É
                scatterOebiusFormation();
                pProg->changeNothing(); //‚¨‚µ‚Ü‚¢
            }
            break;
        }

        default :
            break;
    }
}

void EnemyOebiusController::scatterOebiusFormation() {
    if (pFormationOebius_) {
        pFormationOebius_->scatterMember();
    }
}


EnemyOebiusController::~EnemyOebiusController() {
}
