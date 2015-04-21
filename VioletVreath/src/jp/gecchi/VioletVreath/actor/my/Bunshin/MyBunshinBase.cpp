#include "MyBunshinBase.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int MyBunshinBase::max_bunshin_num_ = 9;
frame MyBunshinBase::bunshin_d_ = 15;

//MyBunshinBase::MyBunshinBase(const char* prm_name, int prm_no) :
//  GgafDxGeometricActor(prm_name, nullptr, nullptr) {

MyBunshinBase::MyBunshinBase(const char* prm_name, int prm_no) :
        DefaultMeshActor(prm_name, "myvic") {

    trace_offset_.set(0,0,0);
    no_ = prm_no;

    std::string bunshin_name = "Bunshin" + XTOS(no_);
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this);
    this->addSubGroupAsFk(pBunshin_,
                          0, PX_C(80), 0,
                          D0ANG, D0ANG, D0ANG);
}

void MyBunshinBase::config(
        coord prm_radius_position,
        angle prm_ang_position,
        angle prm_expanse,
        angvelo prm_angvelo_mv)
{
    bunshin_radius_position_ = prm_radius_position;
    bunshin_ang_position_  = prm_ang_position;
    bunshin_expanse_ = prm_expanse;
    bunshin_angvelo_mv_ = prm_angvelo_mv;
}

void MyBunshinBase::initialize() {
    setScaleR(2.0);
    setAlpha(0.7);
}

void MyBunshinBase::onReset() {
    pBunshin_->changeGeoLocal();
    pBunshin_->_y = bunshin_radius_position_;
    pBunshin_->changeGeoFinal();

    setRollFaceAng(bunshin_ang_position_);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(bunshin_angvelo_mv_);

    pBunshin_->setRzFaceAng(bunshin_expanse_);

}

void MyBunshinBase::onActive() {
}

void MyBunshinBase::processBehavior() {
    const MyShip* const pMyShip = P_MYSHIP;
    const VirtualButton* const pVbPlay = VB_PLAY;
    GgafDxKuroko* const pKuroko = getKuroko();


    const GgafDxGeoElem* pGeoMyShipTrace =
            pMyShip->pRing_GeoHistory4Bunshin_->getPrev(MyBunshinBase::bunshin_d_*(no_));
    _x = pGeoMyShipTrace->x;
    _y = pGeoMyShipTrace->y;
    _z = pGeoMyShipTrace->z;




    if (pVbPlay->isBeingPressed(VB_OPTION) && !pVbPlay->isBeingPressed(VB_TURBO)) {
            //ƒIƒvƒVƒ‡ƒ“Œü‚«‘€ì
            static const angvelo angvelo_turn = PX_C(3);
            if (pVbPlay->isBeingPressed(VB_UP)) {
                addRzFaceAng(angvelo_turn);
            }
            if (pVbPlay->isBeingPressed(VB_DOWN)) {
                addRzFaceAng(-angvelo_turn);
            }
            if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                addRyFaceAng(angvelo_turn);
            }
            if (pVbPlay->isBeingPressed(VB_LEFT)) {
                addRyFaceAng(-angvelo_turn);
            }
        }

    pKuroko->behave();
}

MyBunshinBase::~MyBunshinBase() {
}

