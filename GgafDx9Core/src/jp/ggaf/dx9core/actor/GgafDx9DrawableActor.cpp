#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
GgafDx9DrawableActor::GgafDx9DrawableActor(const char* prm_name,
                                                                     const char* prm_model,
                                                                     const char* prm_effect,
                                                                     const char* prm_technique,
                                                                     GgafDx9Checker* prm_pChecker) :
  GgafDx9GeometricActor(prm_name, prm_pChecker) {

TRACE4("GgafDx9DrawableActor::GgafDx9DrawableActor(");
TRACE4("    prm_name="<<prm_name);
TRACE4("    prm_model="<<prm_model);
TRACE4("    prm_effect="<<prm_effect);
TRACE4("    prm_technique="<<prm_technique);
TRACE4(")");

    _class_name = "GgafDx9DrawableActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    _pNext_TheSameDrawDepthLevel = NULL;
    //���f���擾
    _pGgafDx9ModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model);
    _pGgafDx9Model = (GgafDx9Model*)_pGgafDx9ModelCon->view();
    //�G�t�F�N�g�擾
    _pGgafDx9EffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pGgafDx9Effect = (GgafDx9Effect*)_pGgafDx9EffectCon->view();
    //�}�e���A�����R�s�[
    _paD3DMaterial9 = NEW D3DMATERIAL9[_pGgafDx9Model->_dwNumMaterials];
    for (DWORD i = 0; i < _pGgafDx9Model->_dwNumMaterials; i++){
        _paD3DMaterial9[i] = _pGgafDx9Model->_paD3DMaterial9_default[i];
    }
    _fAlpha = 1.0f;

}


void GgafDx9DrawableActor::processDrawPrior() {
    _pNext_TheSameDrawDepthLevel = NULL;
    //TODO:�v����
    if (_is_active_flg && _can_live_flg) {
        if (getAlpha() < 1.0) {
            if (_isTransformed) {
                GgafDx9Universe::setDrawDepthLevel(
                                    (int)(_z * MAX_DRAW_DEPTH_LEVEL),
                                    this
                                 );
            } else {
                //��������
                //�����̏ꍇ�́AZ���l�ŉ�������`�悷��悤�ɐݒ�B
                //_Z �� �J�����ʒu �` �J���� + 1000*MAX_DRAW_DEPTH_LEVEL �̊Ԃł���� MAX_DRAW_DEPTH_LEVEL��
                //�i�K�����_�����O�����邱�ƂƂ���B
                //�e���� 1000�B�����͈̔͂�Z�͓���[�x�ƂȂ�B
                //TODO: �J����������Z���W�Ő[�x�����܂�Ȃ��ꍇ�g�󂷂�B�������̓J�������W����̋����Ń\�[�g���ׂ��B�E�E�E���̓���낤�B
                GgafDx9Universe::setDrawDepthLevel(
                  (_Z-(GgafDx9Universe::_pCamera->_pVecCamFromPoint->z*LEN_UNIT*PX_UNIT)) / 10000,
                  this
                );
            }
        } else {
            //�s�����̏ꍇ�͏��߂ɕ`�悷��悤�ɐݒ�B
            //�����_�����O���ŉ�����`�悷��̂ŁA�[�x���x����MAX
            GgafDx9Universe::setDrawDepthMaxLevel(this);
        }
    }
}




GgafDx9DrawableActor::~GgafDx9DrawableActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pGgafDx9ModelCon->close();
    _pGgafDx9EffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
