#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionTorpedoController::MyOptionTorpedoController(const char* prm_name, MyOption* prm_pMyOption)
                                                                                  : GgafDummyActor(prm_name) {
    _class_name = "MyOptionTorpedoController";




//    _length_MyTorpedoTailChip = 6;
//    _papMyTorpedoTailChipDispatcher = NEW LaserChipDispatcher*[MyOption::_max_lockon_num];
//    _pa_all_employed_MyTorpedoTailChip = NEW bool[MyOption::_max_lockon_num];
//    _papMyTorpedoTailChip_Head = NEW MyTorpedoTail*[MyOption::_max_lockon_num];
//    for (int i = 0; i < MyOption::_max_lockon_num; i++) {
//        _pa_all_employed_MyTorpedoTailChip[i] = false;
//        _papMyTorpedoTailChipDispatcher[i] = NEW LaserChipDispatcher("DP");
//        _papMyTorpedoTailChipDispatcher[i]->config(_length_MyTorpedoTailChip, 0, NULL);
//
//
//        for (int j = 0; j < _length_MyTorpedoTailChip; j++) {
//            stringstream name;
//            name <<  "MYOPTION"<<(prm_pMyOption->_no)<<"'s TorpedoTailEffect["<<i<<"]["<<j<<"]";
//            MyTorpedoTail* pChip = NEW MyTorpedoTail(name.str().c_str());
//            if (j == 0) {
//                //実質の先頭？
//
//            }
//            pChip->inactivateImmediately();
//            _papMyTorpedoTailChipDispatcher[i]->addSubLast(pChip);
//        }
//        addSubGroup(_papMyTorpedoTailChipDispatcher[i]);
//    }
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


//        for (int i = 0; i < _firing_num; i++) {
//            if (_pa_all_employed_MyTorpedoTailChip[i]) {
//                //発射後
//                if (_papMyTorpedoTailChipDispatcher[i]->_num_chip_active > 0) {
//                    _in_firing = true;
//                }
//            } else {
//                //発射中
//                _in_firing = true;
//                MyTorpedoTail* pTorpedoChip = (MyTorpedoTail*)_papMyTorpedoTailChipDispatcher[i]->employ();
//                if (pTorpedoChip) {
//                    pTorpedoChip->setGeometry(pMYSHIP);
//                    pTorpedoChip->activate();
//                    if (pTorpedoChip->_pChip_front &&  pTorpedoChip->_pChip_front->_pChip_front == NULL) {
//                        _papMyTorpedoTailChip_Head[i] = pTorpedoChip;
//                        _papMyTorpedo[i]->_pMyTorpedoTailChip_Head = pTorpedoChip;
//                        _papMyTorpedo[i]->setGeometry(pMYSHIP);
//                        _papMyTorpedo[i]->activate();
//                    }
//                } else {
//                    _pa_all_employed_MyTorpedoTailChip[i] = true;
//                }
//            }
//        }
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
        angle angRenge  = ANGLE360 / _pMyOption->_pMyOptionParent->_now_option_num;
        angle angFireCenter = angBegin + (ANGLE360*(_pMyOption->_no-1) / _pMyOption->_pMyOptionParent->_now_option_num);
        angle out_rz,out_ry,out_dz,out_dy;
        angle* pa_angWay = NEW angle[ _firing_num+2];
        GgafDx9Util::getWayAngle2D(angFireCenter, _firing_num+1, angRenge / _firing_num, pa_angWay);
        for (int i = 0; i < _firing_num; i++) { //両端の方向は不要
            _papMyTorpedo[i]->setGeometry(pMYSHIP);
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



//            _pa_all_employed_MyTorpedoTailChip[i] = false; //リセット
//            MyTorpedoTail* pHead = (MyTorpedoTail*)_papMyTorpedoTailChipDispatcher[i]->getSubFirst();
//            if (target_num == 0) {
//                pHead->_pTarget = NULL;
//            } else {
//                pHead->_pTarget = _pMyOption->_pLockonController->_pRingTarget->getNext(i);
//            }
//
//            pHead->_pMover->setRzRyMvAng(0, 0);
//            pHead->_pMover->getRzRyMvAngDistance(TURN_CLOSE_TO,
//                                                 pa_angWay[i], ANGLE90,
//                                                 out_dz, out_dy,
//                                                 out_rz, out_ry
//                                                );
//            pHead->_pMover->setRzRyMvAng(out_rz, out_ry);



        }
        DELETEARR_IMPOSSIBLE_NULL(pa_angWay);
    }
}


MyOptionTorpedoController::~MyOptionTorpedoController() {
//    DELETEARR_IMPOSSIBLE_NULL(_papMyTorpedoTailChipDispatcher);
//    DELETEARR_IMPOSSIBLE_NULL(_pa_all_employed_MyTorpedoTailChip);
//    DELETEARR_IMPOSSIBLE_NULL(_papMyTorpedoTailChip_Head);
}
