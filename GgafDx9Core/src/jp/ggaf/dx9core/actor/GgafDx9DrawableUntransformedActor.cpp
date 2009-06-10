#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DrawableUntransformedActor::GgafDx9DrawableUntransformedActor(const char* prm_name, GgafDx9Checker* prm_pChecker) :
    GgafDx9UntransformedActor(prm_name, prm_pChecker) {
    _class_name = "GgafDx9DrawableUntransformedActor";
    _fAlpha = 1.0f;
}


void GgafDx9DrawableUntransformedActor::processDrawPrior() {
    //TODO:�v����
    if (_is_active_flg && _can_live_flg) {
        if (getAlpha() < 1.0) {
            //��������
            //�����̏ꍇ�́AZ���l�ŉ�������`�悷��悤�ɐݒ�B
            //_Z �� �J�����ʒu �` �J���� + 1000*MAX_DRAW_DEPTH_LEVEL �̊Ԃł���� MAX_DRAW_DEPTH_LEVEL��
            //�i�K�����_�����O�����邱�ƂƂ���B
            //�e���� 1000�B�����͈̔͂�Z�͓���[�x�ƂȂ�B
            //TODO: �J����������Z���W�Ő[�x�����܂�Ȃ��ꍇ�g�󂷂�B�������̓J�������W����̋����Ń\�[�g���ׂ��B�E�E�E���̓���낤�B
            GgafDx9Universe::setDrawDepthLevel(
              (_Z-(GgafDx9Universe::_pCamera->_pVecCamFromPoint->z*LEN_UNIT*PX_UNIT)) / 1000,
              this
            );
        } else {
            //�s�����̏ꍇ�͏��߂ɕ`�悷��悤�ɐݒ�B
            //�����_�����O���ŉ�����`�悷��̂ŁA�[�x���x����MAX
            GgafDx9Universe::setDrawDepthMaxLevel(this);
        }
    }
}




GgafDx9DrawableUntransformedActor::~GgafDx9DrawableUntransformedActor() {
}
