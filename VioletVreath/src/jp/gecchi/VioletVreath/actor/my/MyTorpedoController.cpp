#include "MyTorpedoController.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "MyTorpedo.h"
#include "MyTorpedoBlast.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;
int MyTorpedoController::max_torpedo_num_ = 8;
int MyTorpedoController::torpedo_num_ = 0;

MyTorpedoController::MyTorpedoController(const char* prm_name,
                                         GgafDx::GeometricActor* prm_pOrg,
                                         MyLockonController* prm_pLockonCtrler) :
        GgafCore::DestructActor(prm_name) {
    _class_name = "MyTorpedoController";
    firing_num_ = 0;
    in_firing_ = false;
    pOrg_ = prm_pOrg;
    pLockonCtrler_ = prm_pLockonCtrler;
    papTorpedo_ = NEW MyTorpedo*[max_torpedo_num_];
    for (int i = 0; i < max_torpedo_num_; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s Torpedo("+XTOS(i)+")";
        papTorpedo_[i] = NEW MyTorpedo(name.c_str(), this);
        papTorpedo_[i]->inactivate();
        appendChild(papTorpedo_[i]);
    }

    pDepo_TorpedoBlast_ = NEW GgafCore::ActorDepository("DP_TorpedoBlast");
    for (int i = 0; i < max_torpedo_num_*2; i++) {
        std::string name = std::string(prm_pOrg->getName())+"'s TorpedoBlast("+XTOS(i)+")";
        pDepo_TorpedoBlast_->put(NEW MyTorpedoBlast(name.c_str()));
    }
    appendChild(pDepo_TorpedoBlast_);
}

void MyTorpedoController::initialize() {
}

void MyTorpedoController::onActive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivate();
    }
    pDepo_TorpedoBlast_->reset();
}

void MyTorpedoController::processBehavior() {
    in_firing_ = false;
    for (int i = 0; i < firing_num_; i++) {
        if (papTorpedo_[i]->isActive()) {
            in_firing_ = true;
            break;
        }
    }
}

void MyTorpedoController::processJudgement() {
}

void MyTorpedoController::onInactive() {
    in_firing_ = false;
    for (int i = 0; i < max_torpedo_num_; i++) {
        papTorpedo_[i]->pTarget_ = nullptr;
        papTorpedo_[i]->inactivate();
    }
    pDepo_TorpedoBlast_->reset();
}

bool MyTorpedoController::fire() {
    if (!in_firing_ && MyTorpedoController::torpedo_num_ > 0) {
        in_firing_ = true;
        int target_num = pLockonCtrler_->listTarget_.length(); //ロックオン中のターゲット数
        firing_num_ = MyTorpedoController::torpedo_num_; //target_num < 4 ? 4 : target_num;

        static const coord r = PX_C(20);              //放射状魚雷出現時、オプションとの半径距離

        if (MyTorpedoController::torpedo_num_ == 1) {
            //魚雷発射可能数 が 1の場合のみ、特別に前方（レーザー発射方向）に発射
            double vx, vy, vz;
            UTIL::convRzRyToVector(pOrg_->_rz, pOrg_->_ry, vx, vy, vz);
            papTorpedo_[0]->setPosition(pOrg_->_x + (vx * r),
                                        pOrg_->_y + (vy * r),
                                        pOrg_->_z + (vz * r));
            if (target_num == 0) {
                papTorpedo_[0]->pTarget_ = nullptr;
            } else {
                papTorpedo_[0]->pTarget_ = pLockonCtrler_->listTarget_.getNext(0);
            }
            papTorpedo_[0]->getLocusVehicle()->setRzRyMvAng(pOrg_->_rz, pOrg_->_ry); //飛ぶ方向
            papTorpedo_[0]->activate();

        } else {
            static const angle expanse = D_ANG(90);       //発射照射範囲角度(下図の角θ)
            //
            //      :
            //      :      ◎魚
            //      :    ／
            //      :  ／
            //      :／
            //     分  θ   … 成す角expanse        →前方
            //      :＼
            //      :  ＼
            //      :    ＼
            //      :      ◎魚
            //      :
            //
            static const angle expanse_rz = (D180ANG - expanse)/2;

            angle ang_way = D0ANG;                        //放射状魚雷の一つ目の開始アングル 0=真下から,90=右から,180=上から
            angle ang_way_offset = D360ANG / firing_num_; //放射状魚雷と魚雷の間のなすアングル
            D3DXMATRIX matRotZ; //現在のオプションの向きから90度下に向く回転行列
            UTIL::setWorldMatrix_RzRy(UTIL::simplifyAng(pOrg_->_rz - D90ANG), pOrg_->_ry,
                                      matRotZ);
            double vx, vy, vz;
            coord x1, y1, z1, x2, y2, z2;
            coord rz,ry;
            for (int i = 0; i < firing_num_; i++) {
                UTIL::convRzRyToVector(expanse_rz, ang_way, vx, vy, vz);
                x1 = vx * r;
                y1 = vy * r;
                z1 = vz * r;
                //(x1,y1,z1) はオプションの頭の上のメガホン上の座標、
                //これをRZを-90度回転させメガホンをオプションの前方に向ける→(x2,y2,z2)
                x2 = x1*matRotZ._11 + y1*matRotZ._21 + z1*matRotZ._31;
                y2 = x1*matRotZ._12 + y1*matRotZ._22 + z1*matRotZ._32;
                z2 = x1*matRotZ._13 + y1*matRotZ._23 + z1*matRotZ._33;
                papTorpedo_[i]->setPosition(pOrg_->_x + x2,
                                         pOrg_->_y + y2,
                                         pOrg_->_z + z2);
                if (target_num == 0) {
                    papTorpedo_[i]->pTarget_ = nullptr;
                } else {
                    papTorpedo_[i]->pTarget_ = pLockonCtrler_->listTarget_.getNext(i);
                }
                UTIL::convVectorToRzRy(x2, y2, z2, rz, ry);
                papTorpedo_[i]->getLocusVehicle()->setRzRyMvAng(rz, ry); //飛ぶ方向
                papTorpedo_[i]->activate();
                ang_way = UTIL::addAng(ang_way, ang_way_offset); //次の放射状の魚雷へ
            }
        }

        return true;
    } else {
        return false;
    }
}

MyTorpedoController::~MyTorpedoController() {
    GGAF_DELETEARR(papTorpedo_);
}
