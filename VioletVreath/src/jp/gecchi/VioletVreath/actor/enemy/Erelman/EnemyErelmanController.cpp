#include "EnemyErelmanController.h"

#include "jp/ggaf/core/Element.hpp"
#include "jp/ggaf/core/Progress.h"
#include "FormationErelman001.h"
#include "FormationErelman002.h"
#include "EnemyErelmanCore.h"



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

EnemyErelmanController::EnemyErelmanController(const char* prm_name, EnemyErelmanCore* prm_pCore,
                                                                   FormationErelman* prm_pFormation) :
  GgafCore::DestructActor(prm_name) {
    _class_name = "EnemyErelmanController";
    useProgress(PROG_BANPEI);

    pErelmanCore_ = prm_pCore;
    pErelmanCore_->inactivate();
    appendGroupChild(pErelmanCore_);

    pFormationErelman_ = prm_pFormation;
    pFormationErelman_->inactivate();
    appendGroupChild(pFormationErelman_);
}

void EnemyErelmanController::initialize() {
}

void EnemyErelmanController::onActive() {
    getProgress()->reset(PROG_INIT);
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

    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY_CORE: {
            if (pProg->hasJustChanged()) {
                if (pErelmanCore_) {
                    pErelmanCore_->setPositionAt(&entry_pos_);
                    pErelmanCore_->activate();
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
                if (pFormationErelman_) {
                    pFormationErelman_->activate();
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
            if (!pErelmanCore_) {
                //コアがいなくなったら散り散りに
                if (pFormationErelman_) {
                    pFormationErelman_->scatterMember();
                }
                pProg->changeNothing(); //おしまい
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
