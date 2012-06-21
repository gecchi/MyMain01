#include "stdafx.h"
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
        std::stringstream name;
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
        firing_num_ = target_num < 4 ? 4 : target_num;
        angle* paAng_way = NEW angle[firing_num_];
        UTIL::getRadialAngle2D(D45ANG, firing_num_, paAng_way);
        GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[firing_num_];
        angle expanse_rz = (D180ANG - D_ANG(90))/2;   //”­ŽËÆŽËŠp“x90“x
        coord r = PX_C(15);
        D3DXMATRIX matWorldRot;
        UTIL::setWorldMatrix_RzRy(UTIL::simplifyAng(pOption_->_RZ - D90ANG),
                                        pOption_->_RY,
                                        matWorldRot);
        float vx, vy, vz;
        coord X,Y,Z;
        for (int i = 0; i < firing_num_; i++) {
            UTIL::getNormalizeVectorZY(expanse_rz, paAng_way[i], vx, vy, vz);
            X = vx * r;
            Y = vy * r;
            Z = vz * r;
            paGeo[i]._X = X*matWorldRot._11 + Y*matWorldRot._21 + Z*matWorldRot._31;
            paGeo[i]._Y = X*matWorldRot._12 + Y*matWorldRot._22 + Z*matWorldRot._32;
            paGeo[i]._Z = X*matWorldRot._13 + Y*matWorldRot._23 + Z*matWorldRot._33;
            UTIL::getRzRyAng(paGeo[i]._X , paGeo[i]._Y, paGeo[i]._Z,
                                   paGeo[i]._RZ, paGeo[i]._RY);

        }
        for (int i = 0; i < firing_num_; i++) {
            papTorpedo_[i]->locate(pOption_->_X + paGeo[i]._X,
                                   pOption_->_Y + paGeo[i]._Y,
                                   pOption_->_Z + paGeo[i]._Z);
            if (target_num == 0) {
                papTorpedo_[i]->pTarget_ = NULL;
            } else {
                papTorpedo_[i]->pTarget_ = pOption_->pLockonCtrlr_->pRingTarget_->getNext(i);
            }
            papTorpedo_[i]->_pKurokoA->setRzRyMvAng(paGeo[i]._RZ, paGeo[i]._RY);
            papTorpedo_[i]->activate();
        }
        DELETEARR_IMPOSSIBLE_NULL(paAng_way);
        DELETEARR_IMPOSSIBLE_NULL(paGeo);
        pOption_->_pSeTx->play3D(2);

    }
}


MyOptionTorpedoController::~MyOptionTorpedoController() {
    DELETEARR_IMPOSSIBLE_NULL(papTorpedo_);
}
