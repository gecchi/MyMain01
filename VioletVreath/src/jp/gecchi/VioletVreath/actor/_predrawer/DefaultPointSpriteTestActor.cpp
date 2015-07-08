#include "DefaultPointSpriteTestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultPointSpriteTestActor::DefaultPointSpriteTestActor(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "_chk_DefaultPointSpriteTestModel", nullptr) {
    _class_name = "DefaultPointSpriteTestActor";
    effectBlendOne(); //���Z����
    setHitAble(false);
    setSpecialDrawDepth(RENDER_DEPTH_LEVEL_BACK);
}

int DefaultPointSpriteTestActor::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool DefaultPointSpriteTestActor::isOutOfSpacetime() const {
    //�Q�[�����W�͈͊O���薳��
    return false;
}
void DefaultPointSpriteTestActor::initialize() {

}

void DefaultPointSpriteTestActor::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 1);
}

void DefaultPointSpriteTestActor::processBehavior() {
    getUvFlipper()->behave();
}

void DefaultPointSpriteTestActor::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDxGeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
}

void DefaultPointSpriteTestActor::processJudgement() {
}

DefaultPointSpriteTestActor::~DefaultPointSpriteTestActor() {
}
