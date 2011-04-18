#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
//���ݖ��g�p
DefaultPointSpriteEffectActor::DefaultPointSpriteEffectActor(const char* prm_name) :
DefaultPointSpriteActor(prm_name, "hoshitest") {
    _class_name = "DefaultPointSpriteEffectActor";
    changeEffectTechnique("DestBlendOne"); //���Z����
    setHitAble(false);
    _CAM_ZF = abs(P_CAM->_zf * PX_UNIT * LEN_UNIT);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-1);
    _TRACE_("DefaultPointSpriteEffectActor::DefaultPointSpriteEffectActor _CAM_ZF="<<_CAM_ZF);
}

int DefaultPointSpriteEffectActor::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool DefaultPointSpriteEffectActor::isOutOfUniverse() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}
void DefaultPointSpriteEffectActor::initialize() {

}

void DefaultPointSpriteEffectActor::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void DefaultPointSpriteEffectActor::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void DefaultPointSpriteEffectActor::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDx9GeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
}

void DefaultPointSpriteEffectActor::processJudgement() {
}

//void DefaultPointSpriteEffectActor::processPreDraw() {
//    //��ʊO���薳���ɔ��Ȃ������ȗ���
//    //GgafDx9DrawableActor::processPreDraw() �Ɠ�������鎖�I
//    GgafDx9Universe::setDrawDepthLevel(MAX_DRAW_DEPTH_LEVEL-1,this); //�Ő[��-1�A�Ő[����WorldBound
//
////    //�ꎞ�e�N�j�b�N���ԃ`�F�b�N
////    if (_is_temp_technique) {
////        if (_frame_temp_technique <= _frame_of_behaving) {
////            //�ꎞ�e�N�j�b�N���Ԗ����B���ɖ߂�
////            _hash_technique = _hash_technique_temp;
////            strcpy(_technique, _technique_temp);
////            _is_temp_technique = false;
////            //����̓_���B�z��̈悪�ǂ����ɂ������߁B_technique_temp = "";
////            _hash_technique_temp = 0;
////        }
////    }
//}


DefaultPointSpriteEffectActor::~DefaultPointSpriteEffectActor() {
}