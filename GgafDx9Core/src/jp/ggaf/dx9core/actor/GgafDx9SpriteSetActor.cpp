#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteSetActor::GgafDx9SpriteSetActor(const char* prm_name,
                                       const char* prm_model,
                                       const char* prm_effect,
                                       const char* prm_technique,
                                       GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                             prm_model,
                                                                             prm_effect,
                                                                             prm_technique,
                                                                             prm_pChecker) {
    _class_name = "GgafDx9SpriteSetActor";

    //���f���擾
    _pSpriteSetModel = (GgafDx9SpriteSetModel*)_pGgafDx9Model;
    _pSpriteSetEffect = (GgafDx9SpriteSetEffect*)_pGgafDx9Effect;

    //���f���̃}�e���A�����R�s�[���ĕێ�
//    _paD3DMaterial9 = NEW D3DMATERIAL9[1];
//    _paD3DMaterial9[0] = *(_pSpriteSetModel->_pD3DMaterial9_default);
    //�G�t�F�N�g�擾

    _pattno_ani_top = 0;
    _pattno_ani_bottom = _pSpriteSetModel->_pattno_ani_Max;
    _pattno_ani_now = 0;
    _frame_ani_interval = 0;
    _animation_method = ORDER_LOOP;
    _aniframe_counter = 0;
    _is_reverse_order_in_oscillate_animation_flg = false;
    _isBillboardingFlg = false;
}

void GgafDx9SpriteSetActor::processDrawMain() {
    int cnt = 1; //����`��[�x�ɁAGgafDx9SpriteSetActor�̓������f�����A�����Ă���J�E���g��
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            GgafDx9Model* pGgafDx9Model = _pNextDrawActor->_pGgafDx9Model;
            _TRACE_("cnt="<<cnt<<" pGgafDx9Model = "<<pGgafDx9Model->getName() << " =?= _pSpriteSetModel="<<_pSpriteSetModel->getName());

            if (pGgafDx9Model == _pSpriteSetModel && _pNextDrawActor->isActive()) {
                cnt++;
                if (cnt > 8) {
                    break;
                }
                _pNextDrawActor= _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    _draw_set_index = 0;
    _draw_object_num = 1;
_TRACE_("_pSpriteSetModel->_setnum = "<<_pSpriteSetModel->_setnum);
    //index   0 1 2 3 4
    //object  1 2 4 8 16
    if (cnt >= 8 && _pSpriteSetModel->_setnum >= 4) {
        _draw_set_index = 3;
        _draw_object_num = 8;
    } else if (4 <= cnt && _pSpriteSetModel->_setnum >= 3) {
        _draw_set_index = 2;
        _draw_object_num = 4;
    } else if (2 <= cnt && _pSpriteSetModel->_setnum >= 2) {
        _draw_set_index = 1;
        _draw_object_num = 2;
    } else {
        _draw_set_index = 0;
        _draw_object_num = 1;
    }


    _TRACE_("GgafDx9SpriteSetActor::processDrawMain() _draw_set_index="<<_draw_set_index<<"/_draw_object_num="<<_draw_object_num);

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_hMatView, &GgafDx9Universe::_pCamera->_vMatrixView );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) �Ɏ��s���܂����B");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    for (int i = 0; i < _draw_object_num; i++) {
        if (_isBillboardingFlg) {
            GgafDx9GeometricActor::getWorldMatrix_BillBoardXYZ_ScMv(pDrawActor, pDrawActor->_matWorld);
        } else {
            GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(pDrawActor, pDrawActor->_matWorld);
        }
        hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld) );
        mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::processDrawMain SetMatrix(_hMatWorld) �Ɏ��s���܂����B");

        //����`���UV
        static GgafDx9RectUV* pRectUV_Active;
        pRectUV_Active = _pSpriteSetModel->_paRectUV + (((GgafDx9SpriteSetActor*)(pDrawActor))->_pattno_ani_now);

        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
        mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::processDrawMain() SetFloat(_hOffsetU) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
        mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::processDrawMain() SetFloat(_hOffsetV) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahAlpha[i], pDrawActor->_fAlpha);
        mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetActor::processDrawMain SetFloat(_fAlpha) �Ɏ��s���܂����B");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //�A�N�e�B�u��i�߂�
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pSpriteSetModel->draw(this);
}

void GgafDx9SpriteSetActor::setActivAnimationPattern(int prm_pattno_ani) {
    if (0 > prm_pattno_ani || prm_pattno_ani > (_pSpriteSetModel->_pattno_ani_Max)) {
        throwGgafCriticalException("GgafDx9SpriteSetActor::setActivAnimationPattern �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����="<<prm_pattno_ani);
    } else {
        _pattno_ani_now = prm_pattno_ani;
    }
}

void GgafDx9SpriteSetActor::resetActivAnimationPattern() {
    _pattno_ani_now = _pattno_ani_top;
}

void GgafDx9SpriteSetActor::setAnimationPatternRenge(int prm_top, int prm_bottom = 1) {
    if (prm_top < 0 || prm_bottom > (_pSpriteSetModel->_pattno_ani_Max)) {
        throwGgafCriticalException("GgafDx9SpriteSetActor::setAnimationPatternRenge �A�j���[�V�����p�^�[���ԍ����͈͊O�ł��B����("<<prm_top<<","<<prm_bottom<<")");
    } else {
        _pattno_ani_top = prm_top;
        _pattno_ani_bottom = prm_bottom;
    }
}

void GgafDx9SpriteSetActor::setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_interval) {
    _animation_method = prm_method;
    _frame_ani_interval = prm_interval;
}

void GgafDx9SpriteSetActor::addNextAnimationFrame() {
//    _TRACE_(getName()<<":_pattno_ani_now="<<_pattno_ani_now<<"/_pattno_ani_bottom="<<_pattno_ani_bottom<<"/_pattno_ani_top="<<_pattno_ani_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");

    _aniframe_counter++;
    if (_frame_ani_interval < _aniframe_counter) {
        if (_animation_method == ORDER_LOOP) { //��F0,1,2,3,4,5,0,1,2,3,4,5,...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == REVERSE_LOOP) { //��F0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == ORDER_NOLOOP) { //��F0,1,2,3,4,5,5,5,5,5,5,5...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == REVERSE_NOLOOP) { //��F5,4,3,2,1,0,0,0,0,0,0...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == OSCILLATE_LOOP) { //��F0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
            if (_is_reverse_order_in_oscillate_animation_flg) { //�t������
                if (_pattno_ani_top < _pattno_ani_now) {
                    _pattno_ani_now--;
                } else {
                    _pattno_ani_now++;
                    _is_reverse_order_in_oscillate_animation_flg = false;
                }
            } else {                                            //��������
                if (_pattno_ani_bottom > _pattno_ani_now) {
                    _pattno_ani_now++;
                } else {
                    _pattno_ani_now--;
                    _is_reverse_order_in_oscillate_animation_flg = true;
                }

            }
        } else if (_animation_method == NOT_ANIMATED) {
            //�������Ȃ�
        }
        _aniframe_counter = 0;
    }

}

void GgafDx9SpriteSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //���ݒ�A���݃}�e���A����Diffuse�ȊO�֌W�Ȃ�
    _paD3DMaterial9[0].Ambient.a = _fAlpha;
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteSetActor::~GgafDx9SpriteSetActor() {
}
