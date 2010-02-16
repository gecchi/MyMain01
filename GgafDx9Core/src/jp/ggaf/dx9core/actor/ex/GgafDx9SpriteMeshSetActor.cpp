#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshSetActor::GgafDx9SpriteMeshSetActor(const char* prm_name,
                                       const char* prm_model,
                                       GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshSetActor(prm_name,
                                                           prm_model,
                                                           "SpriteMeshSetEffect",
                                                           "SpriteMeshSetTechnique",
                                                           prm_pChecker) {

    _class_name = "GgafDx9SpriteMeshSetActor";
    _pUvFliper = NEW GgafDx9UvFliper(this);
    _pUvFliper->forceUvFlipPtnRange(0, 1);
    _pUvFliper->setUvFlipPtnNo(0);
    _pUvFliper->setUvFlipMethod(NOT_ANIMATED, 1);
//    _pattno_uvflip_top = 0;
//    _pattno_uvflip_bottom = 0;
//    _pattno_uvflip_now = 0;
//    _frame_uvflip_interval = 1;
//    _uvflip_method = FLIP_ORDER_LOOP;
//    _frame_counter_uvflip = 0;
//    _is_reverse_order_in_oscillate_animation_flg = false;

    //_tex_width = 1.0f;
    //_tex_height = 1.0f;
    //_tex_col_num = 1;
//    _h_offset_u = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_offset_u" );
//    _h_offset_v = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_offset_v" );

}


void GgafDx9SpriteMeshSetActor::processDraw() {

    _draw_set_num = 1; //GgafDx9MeshSetActor�̓������f�����A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > _pMeshSetModel->_set_num) {
                    _draw_set_num = _pMeshSetModel->_set_num;
                    break;
                }
                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW�ϊ��s��
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_hMatView) �Ɏ��s���܂����B");
    //��{���f�����_��
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_nVertexs) �Ɏ��s���܂����B2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    GgafDx9SpriteMeshSetActor* pA;
    float u = 0;
    float v = 0;
    for (int i = 0; i < _draw_set_num; i++) {
        (*_pFunc_calcWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ahMaterialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_MaterialDiffuse) �Ɏ��s���܂����B");

        pA = (GgafDx9SpriteMeshSetActor*)pDrawActor; //���̃L���X�g�͊댯�ł���B
        //[MEMO]
        //GgafDx9SpriteMeshSetActor �́AGgafDx9MeshSetActor ����h�����Ă���A���f���N���X�͓����ł���B
        //GgafDx9SpriteMeshSetActor���g�p���郂�f����("x/10/Flora"��)�ƁAGgafDx9MeshSetActor���g�p���郂�f������
        //�������̂����݂���ꍇ�ApDrawActor �́AGgafDx9MeshSetActor �̉\��������B
        //����́A_draw_set_num �����߂郍�W�b�N�͓���[�x�ŘA���̓���(�A�h���X)���f���ł���B�Ƃ������肵���s���Ă��Ȃ����߁B
        //���������āA�{���� GgafDx9SpriteMeshSetActor �� GgafDx9MeshSetActor �œ��ꃂ�f�������g�p���邱�Ƃ͋֎~�ɂ������B
        //���������ǂ��A���������N���鎖�ł������̂ŁA�Ƃ肠�������ӂ��ďd�������Ȃ��悤�Ɉӎ����邱�Ƃɂ���B
        //TODO:�d�����Ȃ��悤�ɂ���d�g�݂�g�ݍ���

        //UV�I�t�Z�b�g�ݒ�
        pA->_pUvFliper->getUV(u, v);
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetU[i], u);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetV[i], v);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) �Ɏ��s���܂����B");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);



}

//void GgafDx9SpriteMeshSetActor::setTextureUvRotation(int prm_tex_col_num, float prm_tex_width, float prm_tex_height)  {
//    if (prm_tex_col_num < 0) {
//        throwGgafCriticalException("GgafDx9SpriteMeshSetActor::setTextureUvRotation prm_tex_col_num��0�ȏ�̐����Őݒ肵�ĉ������B");
//    }
//    _tex_width = prm_tex_width;
//    _tex_height = prm_tex_height;
//    _tex_col_num = prm_tex_col_num;
//}
//
//void GgafDx9SpriteMeshSetActor::setUvFlipPtnNo(int prm_pattno_uvflip) {
//    _pattno_uvflip_now = prm_pattno_uvflip;
//}
//
//void GgafDx9SpriteMeshSetActor::resetUvFlipPtnNo() {
//    _pattno_uvflip_now = _pattno_uvflip_top;
//}
//
//void GgafDx9SpriteMeshSetActor::forceUvFlipPtnRange(int prm_top, int prm_bottom = 1) {
//    _pattno_uvflip_top = prm_top;
//    _pattno_uvflip_bottom = prm_bottom;
//}
//
//void GgafDx9SpriteMeshSetActor::setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval) {
//    _uvflip_method = prm_method;
//    _frame_uvflip_interval = prm_interval;
//}
//
//void GgafDx9SpriteMeshSetActor::behaveUvFlip() {
////    _TRACE_(getName()<<":_pattno_uvflip_now="<<_pattno_uvflip_now<<"/_pattno_uvflip_bottom="<<_pattno_uvflip_bottom<<"/_pattno_uvflip_top="<<_pattno_uvflip_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");
//
//    _frame_counter_uvflip++;
//    if (_frame_uvflip_interval < _frame_counter_uvflip) {
//        if (_uvflip_method == FLIP_ORDER_LOOP) { //��F0,1,2,3,4,5,0,1,2,3,4,5,...
//            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                _pattno_uvflip_now++;
//            } else {
//                _pattno_uvflip_now = _pattno_uvflip_top;
//            }
//        } else if (_uvflip_method == FLIP_REVERSE_LOOP) { //��F0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
//            if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                _pattno_uvflip_now--;
//            } else {
//                _pattno_uvflip_now = _pattno_uvflip_bottom;
//            }
//        } else if (_uvflip_method == FLIP_ORDER_NOLOOP) { //��F0,1,2,3,4,5,5,5,5,5,5,5...
//            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                _pattno_uvflip_now++;
//            } else {
//                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
//                _pattno_uvflip_now = _pattno_uvflip_bottom;
//            }
//        } else if (_uvflip_method == FLIP_REVERSE_NOLOOP) { //��F5,4,3,2,1,0,0,0,0,0,0...
//            if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                _pattno_uvflip_now--;
//            } else {
//                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
//                _pattno_uvflip_now = _pattno_uvflip_top;
//            }
//        } else if (_uvflip_method == FLIP_OSCILLATE_LOOP) { //��F0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
//            if (_is_reverse_order_in_oscillate_animation_flg) { //�t������
//                if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                    _pattno_uvflip_now--;
//                } else {
//                    _pattno_uvflip_now++;
//                    _is_reverse_order_in_oscillate_animation_flg = false;
//                }
//            } else {                                            //��������
//                if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                    _pattno_uvflip_now++;
//                } else {
//                    _pattno_uvflip_now--;
//                    _is_reverse_order_in_oscillate_animation_flg = true;
//                }
//
//            }
//        } else if (_uvflip_method == NOT_ANIMATED) {
//            //�������Ȃ�
//        }
//        _frame_counter_uvflip = 0;
//    }
//
//}

GgafDx9SpriteMeshSetActor::~GgafDx9SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFliper);
}
