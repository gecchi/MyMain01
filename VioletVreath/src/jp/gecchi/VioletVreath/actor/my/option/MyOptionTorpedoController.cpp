#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyOptionTorpedoController::MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption) :
        GgafDummyActor(prm_name, NULL) {
    _class_name = "MyOptionTorpedoController";
    firing_num_ = 0;
    in_firing_ = false;
    pMyOption_ = prm_pMyOption;

    papMyTorpedo_ = NEW MyTorpedo*[MyOption::max_lockon_num_];
    for (int i = 0; i < MyOption::max_lockon_num_; i++) {
        stringstream name;
        name <<  "MYOPTION"<<(prm_pMyOption->no_)<<"'s Torpedo["<<i<<"]";
        papMyTorpedo_[i] = NEW MyTorpedo(name.str().c_str(), this);
        papMyTorpedo_[i]->inactivateImmed();
        addSubGroup(papMyTorpedo_[i]);
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
        papMyTorpedo_[i]->pTarget_ = NULL;
        papMyTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}
void MyOptionTorpedoController::processBehavior() {
    if (in_firing_) {
        in_firing_ = false;
        for (int i = 0; i < firing_num_; i++) {
            if (papMyTorpedo_[i]->isActiveInTheTree()) {
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
        papMyTorpedo_[i]->pTarget_ = NULL;
        papMyTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}
void MyOptionTorpedoController::fire() {
    if (!in_firing_) {
        in_firing_ = true;
        int target_num = pMyOption_->pLockonController_->pRingTarget_->length();
        firing_num_ = target_num == 0 ? 1 : target_num;
                 // = MyOption::max_lockon_num_;
                 // = target_num == 0 ? MyOption::max_lockon_num_ : target_num;
        angle angBegin = D90ANG;
        angle angRenge  = D360ANG / pMyOption_->pMyOptionController_->now_option_num_;
        angle angFireCenter = angBegin + (D360ANG*(pMyOption_->no_-1) / pMyOption_->pMyOptionController_->now_option_num_);
        angle out_rz,out_ry,out_dz,out_dy;
        angle* pa_angWay = NEW angle[ firing_num_+2];
        GgafDxUtil::getWayAngle2D(angFireCenter, firing_num_+1, angRenge / firing_num_, pa_angWay);
        for (int i = 0; i < firing_num_; i++) { //—¼’[‚Ì•ûŒü‚Í•s—v
            papMyTorpedo_[i]->locateAs(P_MYSHIP);
            if (target_num == 0) {
                papMyTorpedo_[i]->pTarget_ = NULL;
            } else {
                papMyTorpedo_[i]->pTarget_ = pMyOption_->pLockonController_->pRingTarget_->getNext(i);
            }
            papMyTorpedo_[i]->_pKurokoA->setRzRyMvAng(0, 0);
            papMyTorpedo_[i]->_pKurokoA->getRzRyMvAngDistance(TURN_CLOSE_TO,
                                                             pa_angWay[i], D135ANG, //D135ANGŒã‚ëŽÎ‚ß‚S‚T“x
                                                             out_dz, out_dy,
                                                             out_rz, out_ry
                                                            );
            papMyTorpedo_[i]->_pKurokoA->setRzRyMvAng(out_rz, out_ry);
            papMyTorpedo_[i]->activate();
        }
        DELETEARR_IMPOSSIBLE_NULL(pa_angWay);
    }
}


MyOptionTorpedoController::~MyOptionTorpedoController() {
    DELETEARR_IMPOSSIBLE_NULL(papMyTorpedo_);
}
