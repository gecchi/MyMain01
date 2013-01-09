#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
int MyTorpedoController::max_torpedo_num_ = 8;
int MyTorpedoController::torpedo_num_ = 0;

MyTorpedoController::MyTorpedoController(const char* prm_name,
                                         GgafDxCore::GgafDxGeometricActor* prm_pOrg,
                                         MyLockonController* prm_pLockonCtrler) :
        GgafDummyActor(prm_name, nullptr) {
    _class_name = "MyTorpedoController";
    firing_num_ = 0;
    in_firing_ = false;
    pOrg_ = prm_pOrg;
    pLockonCtrler_ = prm_pLockonCtrler;
    papTorpedo_ = NEW MyTorpedo*[max_torpedo_num_];
    for (int i = 0; i < max_torpedo_num_; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s Torpedo("+ITOS(i)+")";
        papTorpedo_[i] = NEW MyTorpedo(name.c_str(), this);
        papTorpedo_[i]->inactivateImmed();
        addSubGroup(papTorpedo_[i]);
    }

    pDepo_TorpedoBlast_ = NEW GgafActorDepository("DP_TorpedoBlast");
    for (int i = 0; i < max_torpedo_num_*2; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s TorpedoBlast("+ITOS(i)+")";
        MyTorpedoBlast* pTorpedoBlast = NEW MyTorpedoBlast(name.c_str());
        pTorpedoBlast->inactivateImmed();
        pDepo_TorpedoBlast_->addSubLast(pTorpedoBlast);
    }
    addSubGroup(pDepo_TorpedoBlast_);

}

void MyTorpedoController::initialize() {
}
void MyTorpedoController::onActive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}
void MyTorpedoController::processBehavior() {
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

void MyTorpedoController::processJudgement() {
}
void MyTorpedoController::onInactive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivateImmed();
    }
    pDepo_TorpedoBlast_->reset();
}
//bool MyTorpedoController::fire() {
//    if (!in_firing_ && MyTorpedoController::torpedo_num_ > 0) {
//        in_firing_ = true;
//        int target_num = pLockonCtrler_->pRingTarget_->length();
//        firing_num_ = MyTorpedoController::torpedo_num_; //target_num < 4 ? 4 : target_num;
//        angle* paAng_way = NEW angle[firing_num_];
//        UTIL::getRadialAngle2D(D45ANG, firing_num_, paAng_way);
//        GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[firing_num_];
//        angle expanse_rz = (D180ANG - D_ANG(90))/2;   //発射照射角度90度
//        coord r = PX_C(15);
//        D3DXMATRIX matWorldRot;
//        UTIL::setWorldMatrix_RzRy(UTIL::simplifyAng(pOrg_->_RZ - D90ANG),
//                                        pOrg_->_RY,
//                                        matWorldRot);
//        float vx, vy, vz;
//        coord X,Y,Z;
//        for (int i = 0; i < firing_num_; i++) {
//            UTIL::getNormalizeVectorZY(expanse_rz, paAng_way[i], vx, vy, vz);
//            X = vx * r;
//            Y = vy * r;
//            Z = vz * r;
//            paGeo[i]._X = X*matWorldRot._11 + Y*matWorldRot._21 + Z*matWorldRot._31;
//            paGeo[i]._Y = X*matWorldRot._12 + Y*matWorldRot._22 + Z*matWorldRot._32;
//            paGeo[i]._Z = X*matWorldRot._13 + Y*matWorldRot._23 + Z*matWorldRot._33;
//            UTIL::getRzRyAng(paGeo[i]._X , paGeo[i]._Y, paGeo[i]._Z,
//                             paGeo[i]._RZ, paGeo[i]._RY);
//        }
//        for (int i = 0; i < firing_num_; i++) {
//            MyTorpedo* pTorpedo = papTorpedo_[i];
//            pTorpedo->locate(pOrg_->_X + paGeo[i]._X,
//                             pOrg_->_Y + paGeo[i]._Y,
//                             pOrg_->_Z + paGeo[i]._Z);
//            if (target_num == 0) {
//                pTorpedo->pTarget_ = nullptr;
//            } else {
//                pTorpedo->pTarget_ = pLockonCtrler_->pRingTarget_->getNext(i);
//            }
//            pTorpedo->_pKurokoA->setRzRyMvAng(paGeo[i]._RZ, paGeo[i]._RY);
//            pTorpedo->activate();
//        }
//        DELETEARR_IMPOSSIBLE_NULL(paAng_way);
//        DELETEARR_IMPOSSIBLE_NULL(paGeo);
//        //pOrg_->_pSeTx->play3D(MyOption::SE_FIRE_TORPEDO);
//        return true;
//    } else {
//        return false;
//    }
//}

bool MyTorpedoController::fire() {
    if (!in_firing_ && MyTorpedoController::torpedo_num_ > 0) {
        //
        //      :
        //      :   ◎魚
        //      :  /
        //      : /
        //      :/
        //      オ θ … expanse        →前方
        //      :\
        //      : \
        //      :  \
        //      :   ◎魚
        //      :
        //
        in_firing_ = true;
        int target_num = pLockonCtrler_->pRingTarget_->length(); //ロックオン中のターゲット数
        firing_num_ = MyTorpedoController::torpedo_num_; //target_num < 4 ? 4 : target_num;
        static const angle expanse = D_ANG(90);       //発射照射範囲角度(上図のθ)
        static const angle expanse_rz = (D180ANG - expanse)/2;
        angle ang_way = D0ANG;                        //放射状魚雷の一つ目の開始アングル 0=真下から,90=右から,180=上から
        angle ang_way_offset = D360ANG / firing_num_; //放射状魚雷と魚雷の間のなすアングル
        static const coord r = PX_C(20);              //放射状魚雷出現時、オプションとの半径距離
        D3DXMATRIX matRotZ; //現在のオプションの向きから90度下に向く回転行列
        UTIL::setWorldMatrix_RzRy(UTIL::simplifyAng(pOrg_->_RZ - D90ANG), pOrg_->_RY,
                                  matRotZ);
        float vx, vy, vz;
        coord X1,Y1,Z1, X2, Y2, Z2;
        coord RZ,RY;
        for (int i = 0; i < firing_num_; i++) {
            UTIL::getNormalizeVectorZY(expanse_rz, ang_way, vx, vy, vz);
            X1 = vx * r;
            Y1 = vy * r;
            Z1 = vz * r;
            //(X1,Y1,Z1) はオプションの頭の上のメガホン上の座標、
            //これをRZを-90度回転させメガホンをオプションの前方に向ける→(X2,Y2,Z2)
            X2 = X1*matRotZ._11 + Y1*matRotZ._21 + Z1*matRotZ._31;
            Y2 = X1*matRotZ._12 + Y1*matRotZ._22 + Z1*matRotZ._32;
            Z2 = X1*matRotZ._13 + Y1*matRotZ._23 + Z1*matRotZ._33;
            papTorpedo_[i]->locate(pOrg_->_X + X2,
                                   pOrg_->_Y + Y2,
                                   pOrg_->_Z + Z2);
            if (target_num == 0) {
                papTorpedo_[i]->pTarget_ = nullptr;
            } else {
                papTorpedo_[i]->pTarget_ = pLockonCtrler_->pRingTarget_->getNext(i);
            }
            UTIL::getRzRyAng(X2, Y2, Z2, RZ, RY);
            papTorpedo_[i]->_pKurokoA->setRzRyMvAng(RZ, RY); //飛ぶ方向
            papTorpedo_[i]->activate();
            ang_way = UTIL::addAng(ang_way, ang_way_offset); //次の放射状の魚雷へ
        }
        return true;
    } else {
        return false;
    }
}
MyTorpedoController::~MyTorpedoController() {
    DELETEARR_IMPOSSIBLE_NULL(papTorpedo_);
}
