#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionTorpedoController::MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption)
                                                                                  : GgafDummyActor(prm_name) {
    _class_name = "MyOptionTorpedoController";
    _firing_num = 0;
    _in_firing = false;
    _pMyOption = prm_pMyOption;

    _papMyTorpedo = NEW MyTorpedo*[MyOption::_max_lockon_num];
    for (int i = 0; i < MyOption::_max_lockon_num; i++) {
        stringstream name;
        name <<  "MYOPTION"<<(prm_pMyOption->_no)<<"'s Torpedo["<<i<<"]";
        _papMyTorpedo[i] = NEW MyTorpedo(name.str().c_str(), this);
        _papMyTorpedo[i]->inactivateImmediately();
        addSubGroup(_papMyTorpedo[i]);
    }

    _pDispatcher_TorpedoBlast = NEW GgafActorDispatcher("DP_TorpedoBlast");
    for (int i = 0; i < MyOption::_max_lockon_num*2; i++) {
        MyTorpedoBlast* pTorpedoBlast = NEW MyTorpedoBlast("TorpedoBlast");
        pTorpedoBlast->inactivateImmediately();
        _pDispatcher_TorpedoBlast->addSubLast(pTorpedoBlast);
    }
    addSubGroup(_pDispatcher_TorpedoBlast);

}

void MyOptionTorpedoController::initialize() {
}

void MyOptionTorpedoController::processBehavior() {
    if (_in_firing) {
        _in_firing = false;
        for (int i = 0; i < _firing_num; i++) {
            if (_papMyTorpedo[i]->isActive()) {
                _in_firing = true;
                break;
            }
        }
    }
}

void MyOptionTorpedoController::processJudgement() {
}

void MyOptionTorpedoController::fire() {
    if (!_in_firing) {
        _in_firing = true;
        int target_num = _pMyOption->_pLockonController->_pRingTarget->length();
        _firing_num = MyOption::_max_lockon_num; //target_num == 0 ? MyOption::_max_lockon_num : target_num;
        angle angBegin = ANGLE90;
        angle angRenge  = ANGLE360 / _pMyOption->_pMyOptionController->_now_option_num;
        angle angFireCenter = angBegin + (ANGLE360*(_pMyOption->_no-1) / _pMyOption->_pMyOptionController->_now_option_num);
        angle out_rz,out_ry,out_dz,out_dy;
        angle* pa_angWay = NEW angle[ _firing_num+2];
        GgafDx9Util::getWayAngle2D(angFireCenter, _firing_num+1, angRenge / _firing_num, pa_angWay);
        for (int i = 0; i < _firing_num; i++) { //—¼’[‚Ì•ûŒü‚Í•s—v
            _papMyTorpedo[i]->setCoordinate(pMYSHIP);
            if (target_num == 0) {
                _papMyTorpedo[i]->_pTarget = NULL;
            } else {
                _papMyTorpedo[i]->_pTarget = _pMyOption->_pLockonController->_pRingTarget->getNext(i);
            }
            _papMyTorpedo[i]->_pMover->setRzRyMvAng(0, 0);
            _papMyTorpedo[i]->_pMover->getRzRyMvAngDistance(TURN_CLOSE_TO,
                                                             pa_angWay[i], ANGLE90,
                                                             out_dz, out_dy,
                                                             out_rz, out_ry
                                                            );
            _papMyTorpedo[i]->_pMover->setRzRyMvAng(out_rz, out_ry);
            _papMyTorpedo[i]->activate();
        }
        DELETEARR_IMPOSSIBLE_NULL(pa_angWay);
    }
}


MyOptionTorpedoController::~MyOptionTorpedoController() {
    DELETEARR_IMPOSSIBLE_NULL(_papMyTorpedo);
}
