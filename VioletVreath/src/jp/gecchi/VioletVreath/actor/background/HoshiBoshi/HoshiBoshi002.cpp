#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;
//���ݖ��g�p
HoshiBoshi002::HoshiBoshi002(const char* prm_name) :
        DefaultPointSpriteActor(prm_name, "hoshitest", NULL) {
    _class_name = "HoshiBoshi002";
    changeEffectTechnique("DestBlendOne"); //���Z����
    setHitAble(false);
    CAM_ZF_ = GgafUtil::abs(DX_C(P_CAM->_zf));
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_HOSHIBOSHI);
    _TRACE_("HoshiBoshi002::HoshiBoshi002 CAM_ZF_="<<CAM_ZF_);
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
    if (_X < -CAM_ZF_) {
        _X += (CAM_ZF_*2);
    } else {
        _X -= 10000;
    }

    _pUvFlipper->behave();
}

void HoshiBoshi002::processSettlementBehavior() {
    //��ʊO���薳���ɔ��Ȃ������ȗ���
    //GgafDxGeometricActor::processSettlementBehavior() �Ɠ�������鎖�I
    _fX = C_DX(_X);
    _fY = C_DX(_Y);
    _fZ = C_DX(_Z);
}

void HoshiBoshi002::processJudgement() {
}

//void HoshiBoshi002::processPreDraw() {
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


HoshiBoshi002::~HoshiBoshi002() {
}
