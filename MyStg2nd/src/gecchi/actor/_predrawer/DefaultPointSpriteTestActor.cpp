#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;
DefaultPointSpriteTestActor::DefaultPointSpriteTestActor(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "_chk_DefaultPointSpriteTestModel", NULL) {
    _class_name = "DefaultPointSpriteTestActor";
    changeEffectTechnique("DestBlendOne"); //���Z����
    setHitAble(false);
    _CAM_ZF = abs(P_CAM->_zf * PX_UNIT * LEN_UNIT);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-1);
    _TRACE_("DefaultPointSpriteTestActor::DefaultPointSpriteTestActor _CAM_ZF="<<_CAM_ZF);
}

int DefaultPointSpriteTestActor::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool DefaultPointSpriteTestActor::isOutOfUniverse() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}
void DefaultPointSpriteTestActor::initialize() {

}

void DefaultPointSpriteTestActor::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void DefaultPointSpriteTestActor::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void DefaultPointSpriteTestActor::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDxGeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = Co2Dx(_X);
    _fY = Co2Dx(_Y);
    _fZ = Co2Dx(_Z);
}

void DefaultPointSpriteTestActor::processJudgement() {
}

//void DefaultPointSpriteTestActor::processPreDraw() {
//    //��ʊO���薳���ɔ��Ȃ������ȗ���
//    //GgafDxDrawableActor::processPreDraw() �Ɠ�������鎖�I
//    GgafDxUniverse::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1,this); //�Ő[��-1�A�Ő[����WorldBound
//
////    //�ꎞ�e�N�j�b�N���ԃ`�F�b�N
////    if (_is_temp_technique) {
////        if (_frame_of_behaving_temp_technique_end <= _frame_of_behaving) {
////            //�ꎞ�e�N�j�b�N���Ԗ����B���ɖ߂�
////            _hash_technique = _hash_temp_technique;
////            strcpy(_technique, _temp_technique);
////            _is_temp_technique = false;
////            //����̓_���B�z��̈悪�ǂ����ɂ������߁B_temp_technique = "";
////            _hash_temp_technique = 0;
////        }
////    }
//}


DefaultPointSpriteTestActor::~DefaultPointSpriteTestActor() {
}
