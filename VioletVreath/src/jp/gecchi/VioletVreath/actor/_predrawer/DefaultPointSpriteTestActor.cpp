#include "DefaultPointSpriteTestActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultPointSpriteTestActor::DefaultPointSpriteTestActor(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "_chk_DefaultPointSpriteTestModel", nullptr) {
    _class_name = "DefaultPointSpriteTestActor";
    effectBlendOne(); //���Z����
    setHitAble(false);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-1);
}

int DefaultPointSpriteTestActor::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool DefaultPointSpriteTestActor::isOutOfUniverse() const {
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

//void DefaultPointSpriteTestActor::processPreDraw() {
//    //��ʊO���薳���ɔ��Ȃ������ȗ���
//    //GgafDxDrawableActor::processPreDraw() �Ɠ�������鎖�I
//    GgafDxUniverse::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1,this); //�Ő[��-1�A�Ő[����WorldBound
//
////    //�ꎞ�e�N�j�b�N���ԃ`�F�b�N
////    if (is_temp_technique_) {
////        if (frame_of_behaving_temp_technique_end_ <= frame_of_behaving_) {
////            //�ꎞ�e�N�j�b�N���Ԗ����B���ɖ߂�
////            hash_technique_ = hash_temp_technique_;
////            strcpy(technique_, temp_technique_);
////            is_temp_technique_ = false;
////            //����̓_���B�z��̈悪�ǂ����ɂ������߁Btemp_technique_ = "";
////            hash_temp_technique_ = 0;
////        }
////    }
//}


DefaultPointSpriteTestActor::~DefaultPointSpriteTestActor() {
}
