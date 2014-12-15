#include "Grid26Actor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include <dinput.h>
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

Grid26Actor::Grid26Actor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "jiki") { //Guruguru.x ���Q�Ƃ����B

}

void Grid26Actor::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, PX_C(40));
    setScaleR(3.0);
    setHitAble(true);
    //���߂ɃL������Z����]�̊p���x��ݒ�(���t���[��2�x)
}

void Grid26Actor::processBehavior() {

    int sx = 0;
    int sy = 0;
    int sz = 0;
    bool press1 = false;
    bool pressD = false;
    bool pressT = false;


    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_T)) {
        sy = 1; pressD = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_G)) {
        sy = 0; pressD = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_B)) {
        sy = -1;  pressD = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_Y)) {
        sy = 1; pressT = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_H)) {
        sy = 0; pressT = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_N)) {
        sy = -1;  pressT = true;
    }


    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD7)) {
        sx = -1;  sz = 1; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD8)) {
        sx = 0;  sz = 1; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD9)) {
        sx = 1;  sz = 1; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD4)) {
        sx = -1;  sz = 0; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD5)) {
        sx = 0;  sz = 0; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD6)) {
        sx = 1;  sz = 0; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD1)) {
        sx = -1;  sz = -1; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD2)) {
        sx = 0;  sz = -1; press1 = true;
    }
    if (GgafDxCore::GgafDxInput::isBeingPressedKey(DIK_NUMPAD3)) {
        sx = 1;  sz = -1; press1 = true;
    }

    int dx = PX_C(100)*sx;
    int dy = PX_C(100)*sy;
    int dz = PX_C(100)*sz;

    if (pressD && press1) {
        getKuroko()->asstB()->turnFaceAngByVdTwd(
                D_ANG(2),
                _x + dx, _y + dy, _z + dz, TURN_CLOSE_TO, true,
                0.3, 0.7, 0, true);
    }
    if (pressT && press1) {
        getKuroko()->asstB()->turnFaceAngByDtTwd(
                _x + dx, _y + dy, _z + dz, TURN_CLOSE_TO, true,
                60,
                0.3, 0.7, 0, true);
    }
    getKuroko()->behave(); //���߂�����������iZ����]����j
}

Grid26Actor::~Grid26Actor() {
}
