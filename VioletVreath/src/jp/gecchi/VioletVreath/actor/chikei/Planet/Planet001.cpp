#include "Planet001.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "Planet001Atmosphere.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"



using namespace GgafLib;
using namespace VioletVreath;


Planet001::Planet001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001", nullptr) {
    _class_name = "Planet001";
    setHitAble(false);
    setZEnableDraw(true);        //Z�o�b�t�@�͍l��
    setZWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setSpecialRenderDepthIndex(RENDER_DEPTH_INDEX_HOSHIBOSHI-2);
    drawAnyFar(true);//�����Ă��\��
    //��C���G�t�F�N�g�X�v���C�g
    pAtmosphere_ = NEW Planet001Atmosphere("P001ATMOS");
    appendChild(pAtmosphere_);
}

void Planet001::onCreateModel() {
}

void Planet001::initialize() {
    setCullingDraw(false);
    Spacetime* pSpacetime = pGOD->getSpacetime();
    _x = pSpacetime->_x_bound_right*10;
    setScale(1000*1000);
    setRzFaceAng(D90ANG - D_ANG(30));
    setRyFaceAng(D45ANG);
    getKuroko()->setRollFaceAngVelo(500); //���]�̑���

    pAtmosphere_->setScale(_sx);
    pAtmosphere_->setPositionAt(this);
}
void Planet001::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();

//    //����I�u�W�F�N�g�ړ��e�X�g
//    if (GgafDx::Input::isPressedKey(DIK_I)) {
//        _x += PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_O)) {
//        _x += PX_C(1000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_U)) {
//        _x -= PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_Y)) {
//        _x -= PX_C(1000);
//    }
//
//    if (GgafDx::Input::isPressedKey(DIK_8)) {
//        _y += PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_J)) {
//        _y -= PX_C(100);
//    }
//
//    if (GgafDx::Input::isPressedKey(DIK_M)) {
//        _y -= PX_C(1000);
//    }
//
//
//    if (GgafDx::Input::isPressedKey(DIK_9)) {
//        _z += PX_C(100);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_K)) {
//        _z -= PX_C(100);
//    }
//
//    if (GgafDx::Input::isPressedKey(DIK_0)) {
//        addScale(10000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_L)) {
//        addScale(-10000);
//    }
//
//    if (GgafDx::Input::isPushedDownKey(DIK_O)) {
//        _TRACE_("Planet001  "<<_x<<","<<_y<<","<<_z<<" scale="<<_rx);
//    }
    //_x = _x - PX_C(1);
    pKuroko->behave();

    pAtmosphere_->setScale(_sx);
    pAtmosphere_->setPositionAt(this);
}

Planet001::~Planet001() {
}

