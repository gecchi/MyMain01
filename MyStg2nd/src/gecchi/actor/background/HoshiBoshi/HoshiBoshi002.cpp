#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;
//���ݖ��g�p
HoshiBoshi002::HoshiBoshi002(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "hoshitest", NULL) {
    _class_name = "HoshiBoshi002";
    changeEffectTechnique("DestBlendOne"); //���Z����
    setHitAble(false);
    _CAM_ZF = abs(DX2CO(P_CAM->_zf));
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-1);
    _TRACE_("HoshiBoshi002::HoshiBoshi002 _CAM_ZF="<<_CAM_ZF);
}

int HoshiBoshi002::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool HoshiBoshi002::isOutOfUniverse() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}
void HoshiBoshi002::initialize() {

}

void HoshiBoshi002::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 1);
}

void HoshiBoshi002::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void HoshiBoshi002::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDxGeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = CO2DX(_X);
    _fY = CO2DX(_Y);
    _fZ = CO2DX(_Z);
}

void HoshiBoshi002::processJudgement() {
}

//void HoshiBoshi002::processPreDraw() {
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


HoshiBoshi002::~HoshiBoshi002() {
}
