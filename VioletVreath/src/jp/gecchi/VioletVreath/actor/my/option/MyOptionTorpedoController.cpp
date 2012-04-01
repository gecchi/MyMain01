#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyOptionTorpedoController::MyOptionTorpedoController(const char* prm_name, MyOption* prm_pOption) :
        GgafDummyActor(prm_name, NULL) {
    _class_name = "MyOptionTorpedoController";
    firing_num_ = 0;
    in_firing_ = false;
    pOption_ = prm_pOption;

    papTorpedo_ = NEW MyTorpedo*[MyOption::max_lockon_num_];
    for (int i = 0; i < MyOption::max_lockon_num_; i++) {
        stringstream name;
        name <<  "MYOPTION"<<(prm_pOption->no_)<<"'s Torpedo["<<i<<"]";
        papTorpedo_[i] = NEW MyTorpedo(name.str().c_str(), this);
        papTorpedo_[i]->inactivateImmed();
        addSubGroup(papTorpedo_[i]);
    }

    pDepo_TorpedoBlast_ = NEW GgafActorDepository("DP_TorpedoBlast");
    for (int i = 0; i < MyOption::max_lockon_num_*2; i++) {
        MyTorpedoBlast* pTorpedoBlast = NEW MyTorpedoBlast("TorpedoBlast");
        pTorpedoBlast->inactivateImmed();
        pDepo_TorpedoBlast_->addSubLast(pTorpedoBlast);
    }
    addSubGroup(pDepo_TorpedoBlast_);

}

void MyOptionTorpedoController::initialize() {
}
void MyOptionTorpedoController::onActive() {
    in_firing_ = false;
    for (int i = 0; i < MyOption::max_lockon_num_; i++) {
        papTorpedo_[i]->pTarget_ = NULL;
        papTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}
void MyOptionTorpedoController::processBehavior() {
    if (in_firing_) {
        in_firing_ = false;
        for (int i = 0; i < firing_num_; i++) {
            if (papTorpedo_[i]->isActiveInTheTree()) {
                in_firing_ = true;
                break;
            }
        }
    }
}

void MyOptionTorpedoController::processJudgement() {
}
void MyOptionTorpedoController::onInactive() {
    in_firing_ = false;
    for (int i = 0; i < MyOption::max_lockon_num_; i++) {
        papTorpedo_[i]->pTarget_ = NULL;
        papTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}
void MyOptionTorpedoController::fire() {
    if (!in_firing_) {
        in_firing_ = true;
        int target_num = pOption_->pLockonCtrlr_->pRingTarget_->length();
        firing_num_ = target_num == 0 ? 1 : target_num;
                 // = MyOption::max_lockon_num_;
                 // = target_num == 0 ? MyOption::max_lockon_num_ : target_num;
        angle angBegin = D90ANG;
        angle angRenge  = D360ANG / MyOptionController::now_option_num_;
        angle angFireCenter = angBegin + (D360ANG*(pOption_->no_-1) / MyOptionController::now_option_num_);
        angle out_rz,out_ry,out_dz,out_dy;
        angle* paAng_way = NEW angle[ firing_num_+2];
        GgafDxUtil::getWayAngle2D(angFireCenter, firing_num_+1, angRenge / firing_num_, paAng_way);
        for (int i = 0; i < firing_num_; i++) { //—¼’[‚Ì•ûŒü‚Í•s—v
            papTorpedo_[i]->locatedBy(P_MYSHIP);
            if (target_num == 0) {
                papTorpedo_[i]->pTarget_ = NULL;
            } else {
                papTorpedo_[i]->pTarget_ = pOption_->pLockonCtrlr_->pRingTarget_->getNext(i);
            }
            papTorpedo_[i]->_pKurokoA->setRzRyMvAng(0, 0);
            papTorpedo_[i]->_pKurokoA->getRzRyMvAngDistance(TURN_CLOSE_TO,
                                                             paAng_way[i], D135ANG, //D135ANGŒã‚ëŽÎ‚ß‚S‚T“x
                                                             out_dz, out_dy,
                                                             out_rz, out_ry
                                                            );
            papTorpedo_[i]->_pKurokoA->setRzRyMvAng(out_rz, out_ry);
            papTorpedo_[i]->activate();
        }
        DELETEARR_IMPOSSIBLE_NULL(paAng_way);
    }
}


MyOptionTorpedoController::~MyOptionTorpedoController() {
    DELETEARR_IMPOSSIBLE_NULL(papTorpedo_);
}
