#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

#define returnWhenFailed(HR, OKVAL, X) { \
    if (HR != OKVAL) { \
        std::stringstream ss; \
        ss << X; \
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND); \
        return E_FAIL; \
    } \
}

//TODO:�R�����g�Ƃ���������B��������B



HWND GgafDxGod::_pHWndPrimary = NULL;
HWND GgafDxGod::_pHWndSecondary = NULL;

IDirect3D9* GgafDxGod::_pID3D9 = NULL;
IDirect3DDevice9* GgafDxGod::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDxGod::_d3dlight9_default;
DWORD GgafDxGod::_dwAmbientBrightness_default = 0xff404040;


D3DFILLMODE GgafDxGod::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDxModelManager* GgafDxGod::_pModelManager = NULL;
GgafDxEffectManager* GgafDxGod::_pEffectManager = NULL;
GgafDxTextureManager* GgafDxGod::_pCubeMapTextureManager = NULL;
GgafDxTextureManager* GgafDxGod::_pBumpMapTextureManager = NULL;
bool GgafDxGod::_is_device_lost_flg = false;
bool GgafDxGod::_adjustGameScreen = false;
HWND GgafDxGod::_pHWnd_adjustScreen = NULL;


UINT32 GgafDxGod::_vs_v = 0;
UINT32 GgafDxGod::_ps_v = 0;


GgafDxGod::GgafDxGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) :
    GgafGod(prm_hInstance) {
    TRACE("GgafDxGod::GgafDxGod() ");

    GgafDxGod::_pHWndPrimary = prm_pHWndPrimary;
    GgafDxGod::_pHWndSecondary = prm_pHWndSecondary;
    _is_device_lost_flg = false;
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
    GgafRgb rgb_border = GgafRgb(GGAF_PROPERTY(BORDER_COLOR));
    _color_border = D3DCOLOR_RGBA(rgb_border._R, rgb_border._G, rgb_border._B, 0);
    GgafRgb rgb_bg = GgafRgb(GGAF_PROPERTY(BG_COLOR));
    _color_clear = D3DCOLOR_RGBA(rgb_bg._R, rgb_bg._G, rgb_bg._B, 0);
    _pRenderTexture = NULL;
    _pRenderTextureSurface = NULL;
    _pRenderTextureZ = NULL;
    _num_adapter = 1;
    _apSwapChain[0] = NULL;
    _apBackBuffer[0] = NULL;
    _apSwapChain[1] = NULL;
    _apBackBuffer[1] = NULL;

    _secondary_screen_x = 0;
    _secondary_screen_y = 0;

    //[�����FRECT�\����]
    //�����Ɏg�p����RECT�\���̂̃����o right, bottom �́u�E�����W�v�ƂȂ��Ă��邪�\�������m�ł͂Ȃ��B
    //���ۂ̒�`��
    //rect.right = rect.left + ��`��;
    //rect.bottom = rect.top + ��`����;
    //�܂� (10,10)-(17,17) �̈�́ARECT(10,10,18,18) �Ǝw�肷��̂��Ӑ}�����g�p���@�炵���B
    //��₱�����A�������A�ӂ̒��������߂�ꍇ�͕֗��ł���B
    //�i���{���̉E�����W�́Aright, bottom �� -1 �̒l�ɂȂ�j
    _rectGameBuffer.left   = 0;
    _rectGameBuffer.top    = 0;
    _rectGameBuffer.right  = _rectGameBuffer.left + GGAF_PROPERTY(GAME_BUFFER_WIDTH);
    _rectGameBuffer.bottom = _rectGameBuffer.top  + GGAF_PROPERTY(GAME_BUFFER_HEIGHT);

    _rectRenderTargetBuffer.left   = 0;
    _rectRenderTargetBuffer.top    = 0;
    _rectRenderTargetBuffer.right  = _rectRenderTargetBuffer.left + GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
    _rectRenderTargetBuffer.bottom = _rectRenderTargetBuffer.top  + GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    if (GGAF_PROPERTY(SWAP_GAME_VIEW)) {
        _primary = 1;
        _secondary = 0;
    } else {
        _primary = 0;
        _secondary = 1;
    }
    _aRect_HarfGameBuffer[_primary].left   = 0;
    _aRect_HarfGameBuffer[_primary].top    = 0;
    _aRect_HarfGameBuffer[_primary].right  = _aRect_HarfGameBuffer[_primary].left  + GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_primary].bottom = _aRect_HarfGameBuffer[_primary].top + GGAF_PROPERTY(GAME_BUFFER_HEIGHT);

    _aRect_HarfGameBuffer[_secondary].left   = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].top    = 0;
    _aRect_HarfGameBuffer[_secondary].right  = _aRect_HarfGameBuffer[_secondary].left + GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].bottom = _aRect_HarfGameBuffer[_secondary].top  + GGAF_PROPERTY(GAME_BUFFER_HEIGHT);

    _aRect_HarfRenderTargetBuffer[_primary].left   = 0;
    _aRect_HarfRenderTargetBuffer[_primary].top    = 0;
    _aRect_HarfRenderTargetBuffer[_primary].right  = _aRect_HarfRenderTargetBuffer[_primary].left  + GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_primary].bottom = _aRect_HarfRenderTargetBuffer[_primary].top + GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    _aRect_HarfRenderTargetBuffer[_secondary].left   = GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_secondary].top    = 0;
    _aRect_HarfRenderTargetBuffer[_secondary].right  = _aRect_HarfRenderTargetBuffer[_secondary].left + GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_secondary].bottom = _aRect_HarfRenderTargetBuffer[_secondary].top  + GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    //�\���̈�ݒ�
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        //�t���X�N���[�����[�h
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            _aRect_ViewScreen[0].top    = 0;
            _aRect_ViewScreen[0].left   = 0;
            _aRect_ViewScreen[0].right  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
            _aRect_ViewScreen[0].bottom = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
            _aRect_ViewScreen[1].top    = 0;
            _aRect_ViewScreen[1].left   = 0;
            _aRect_ViewScreen[1].right  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
            _aRect_ViewScreen[1].bottom = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);

            //�t���X�N���[�����[�h�E�Q��ʎg�p
            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����FIX�v�̂P��ʖڃt�����g�o�b�t�@�`��̈�
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����FIX�v�̂Q��ʖڃt�����g�o�b�t�@�`��̈�
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[1].left   = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION1), _aRect_Present[0],
                                    GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT));
            } else {
                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����X�g���b�`�v�̂P��ʖڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����X�g���b�`�v�̂Q��ʖڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
            }
        } else {
            //�t���X�N���[�����[�h�E�P��ʎg�p
            _aRect_ViewScreen[0].top    = 0;
            _aRect_ViewScreen[0].left   = 0;
            _aRect_ViewScreen[0].right  = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
            _aRect_ViewScreen[0].bottom = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            _aRect_ViewScreen[1] = _aRect_ViewScreen[0];

            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�t���X�N���[�����[�h�E�P��ʎg�p�E�c����FIX�v�̃t�����g�o�b�t�@�`��̈�
                if (1.0f * GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(GGAF_PROPERTY(SINGLE_VIEW_DRAW_POSITION), _aRect_Present[0],
                                    GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
            } else {
                //�u�t���X�N���[�����[�h�E�P��ʎg�p�E�c����X�g���b�`�v�̃t�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    } else {
        //�E�B���h�E���[�h
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            //�E�B���h�E���[�h�E�Q���g�p
            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����FIX�v�̂P���ڃt�����g�o�b�t�@�`��̈�
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����FIX�v�̂Q���ڃt�����g�o�b�t�@�`��̈�
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[1].left   = (GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }

                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION1), _aRect_Present[0],
                                    GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
            } else {
                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����X�g���b�`�v�̂P���ڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT);
                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����X�g���b�`�v�̂Q���ڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT);
            }
        } else {
            //�E�B���h�E���[�h�E�P���g�p
            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�E�B���h�E���[�h�E�P���g�p�E�c����FIX�v�̃t�����g�o�b�t�@�`��̈�
                if (1.0f * GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(GGAF_PROPERTY(SINGLE_VIEW_DRAW_POSITION), _aRect_Present[0],
                                    GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
            } else {
                //�u�E�B���h�E���[�h�E�P���g�p�E�c����X�g���b�`�v�̃t�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    }
    _TRACE_(" _aRect_Present[0].left   = "<<_aRect_Present[0].left  );
    _TRACE_(" _aRect_Present[0].top    = "<<_aRect_Present[0].top   );
    _TRACE_(" _aRect_Present[0].right  = "<<_aRect_Present[0].right );
    _TRACE_(" _aRect_Present[0].bottom = "<<_aRect_Present[0].bottom);
    _TRACE_(" _aRect_Present[1].left   = "<<_aRect_Present[1].left  );
    _TRACE_(" _aRect_Present[1].top    = "<<_aRect_Present[1].top   );
    _TRACE_(" _aRect_Present[1].right  = "<<_aRect_Present[1].right );
    _TRACE_(" _aRect_Present[1].bottom = "<<_aRect_Present[1].bottom);
}

HRESULT GgafDxGod::init() {
    //2011/09/18 WDDM ���g�p�ł���Ȃ�g�p����悤�ɕύX�B
    // �}���`���j�^�t���X�N���[�����̃f�o�C�X���X�g���̕������A
    // XP�ł͂��܂������̂�Vista�ł͂��܂������Ȃ��������邱�Ƃ����o�B
    // IDirect3D9Ex �̑��݂��C�ɂȂ�A�������Ɏ������B
    // WDDM�܂� IDirect3D9Ex or IDirect3D9 �̑I�����s���B
    // IDirect3D9Ex ���擾���� Direct3DCreate9Ex() ���g�p���A
    // �߂�l�̌��ʂŔ��肷��Ηǂ��ƈ��Ղɍl���Ă������A
    // IDirect3D9Ex �̎��Ԃ��AVista �ȍ~ �� d3d9.dll �ɂ̂ݑ��݂���炵���A
    // Direct3DCreate9Ex() �֐��̃R�[�h�����������_�ŁAXP�̏ꍇ d3d9.dll ���[�h����
    // �u�G���g���|�C���g������܂���v�Ƃ������G���[�ɂȂ��Ă��܂����s����ł��Ȃ��B
    // �R�[�h�𗼑Ή�������ɂ́ADirect3DCreate9Ex() �͎g���Ȃ��Ǝv���B
    // �����ňȉ��̂悤�� d3d9.dll ����ADirect3DCreate9Ex �𒼐ڒT���āA�|�C���^��
    // �擾������@��MSDN�ɂ������̂ŁA�Q�l�ɂ��Ď����B
    // __uuid ���Z�q�� GCC �ɂ͖����̂ŁAIDD_IDirect3D9 �ɕύX�B
    // TODO::����Ő����Ȃ̂��낤���c�B

    HRESULT hr;
    typedef HRESULT (WINAPI *DIRECT3DCREATE9EXFUNCTION)(UINT SDKVersion, IDirect3D9Ex**);
    IDirect3D9* pID3D9 = NULL;
    IDirect3D9Ex* pID3D9Ex = NULL;
    HMODULE hD3D = LoadLibrary(TEXT("d3d9.dll"));

    DIRECT3DCREATE9EXFUNCTION pFunc_Direct3DCreate9Ex = (DIRECT3DCREATE9EXFUNCTION)GetProcAddress(hD3D, "Direct3DCreate9Ex");
    if (pFunc_Direct3DCreate9Ex) {
        //d3d9.dll �� Direct3DCreate9Ex �͑��݂���B
        hr = ((*pFunc_Direct3DCreate9Ex)(D3D_SDK_VERSION, &pID3D9Ex)); //Direct3DCreate9Ex ���s
        if (FAILED(hr)) {
            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("IDirect3D9Ex �R���|�[�l���g�擾�Ɏ��s���܂����B(1)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            FreeLibrary(hD3D);
            return E_FAIL; //���s
        }
//        hr = pID3D9Ex->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&pID3D9)); //COM�Ƃ��Ďg�p
//        if (FAILED(hr)) {
//            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("IDirect3D9Ex �R���|�[�l���g�擾�Ɏ��s���܂����B(2)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
//            FreeLibrary(hD3D);
//            return E_FAIL; //���s
//        }
        GgafDxGod::_pID3D9 = (IDirect3D9*)pID3D9Ex;
        _can_wddm = true;
    } else {
        //d3d9.dll �� Direct3DCreate9Ex �͑��݂��Ȃ��B
        pID3D9 = Direct3DCreate9(D3D_SDK_VERSION);
        if (!pID3D9) {
            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("IDirect3D9 �R���|�[�l���g�擾�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            FreeLibrary(hD3D);
            return E_FAIL; //���s
        }
        GgafDxGod::_pID3D9 = pID3D9;
        _can_wddm = false;
    }
    FreeLibrary(hD3D);

    //�f�o�C�X�p�����[�^�쐬
    D3DCAPS9 caps;
    GgafDxGod::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] �f�B�X�v���C �A�_�v�^�����������B
                                       D3DDEVTYPE_HAL,     // [in] �f�o�C�X�̎�ށB D3DDEVTYPE�񋓌^�̃����o
                                       &caps);             // [out] �f�o�C�X�̔\�͂��i�[�����

    _num_adapter = caps.NumberOfAdaptersInGroup;   //�g����A�_�v�^�̐��擾
    _paPresetPrm = NEW D3DPRESENT_PARAMETERS[_num_adapter > 2 ? _num_adapter : 2];
    ZeroMemory(&_paPresetPrm[0], sizeof(D3DPRESENT_PARAMETERS));

    //�E�B���h�E���E�t���X�N���[��������
    _paPresetPrm[0].BackBufferCount        = 1;            //�o�b�N�o�b�t�@�̐�
    _paPresetPrm[0].EnableAutoDepthStencil = TRUE;         //�o�b�N�o�b�t�@�� Z�o�b�t�@�̎����쐬
    _paPresetPrm[0].AutoDepthStencilFormat = D3DFMT_D24S8; //�[�x�X�e���V���o�b�t�@ //D3DFMT_D16;
    _paPresetPrm[0].Flags                  = 0;            //0�ɂ��Ă���

    if (GGAF_PROPERTY(FULL_SCREEN)) {

        //�t���X�N���[����
        _paPresetPrm[0].BackBufferFormat           = D3DFMT_X8R8G8B8; //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
        _paPresetPrm[0].Windowed                   = false; //�t���X�N���[�����[�h��
        _paPresetPrm[0].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //���t���b�V�����[�g
        _paPresetPrm[0].PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT; //�X���b�v�̃^�C�~���O
        _paPresetPrm[0].SwapEffect                 = D3DSWAPEFFECT_DISCARD;

        if(GGAF_PROPERTY(DUAL_VIEW)) {
            _paPresetPrm[1] = _paPresetPrm[0]; //�R�R�܂ł𕡐�

            _paPresetPrm[0].EnableAutoDepthStencil = FALSE;   //Z�o�b�t�@�̎����쐬����
            _paPresetPrm[1].EnableAutoDepthStencil = FALSE;
            //�y�����z
            //EnableAutoDepthStencil = FALSE;
            //�Ƃ���ƁA�����_�����O�X�e�[�g�� D3DRS_ZENABLE �� FALSE �ɂȂ邾���̂悤�Ɍ�����B
            //�]���āu�����v�ɂ��������ł���A�u�g�p�s�v�ł͂Ȃ��̂��낤�E�E�E�B
        } else {
            _paPresetPrm[0].EnableAutoDepthStencil = FALSE; //Z �o�b�t�@�̎����쐬�L��
        }
    } else {
        //�E�B���h�E��
        _paPresetPrm[0].BackBufferFormat           = D3DFMT_UNKNOWN; //���݂̕\�����[�h�t�H�[�}�b�g
        _paPresetPrm[0].Windowed                   = true; //�E�B���h�E���[�h��
        _paPresetPrm[0].FullScreen_RefreshRateInHz = 0; //���t���b�V�����[�g
        _paPresetPrm[0].PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE; //����
        _paPresetPrm[0].SwapEffect                 = D3DSWAPEFFECT_COPY; //TODO:Window���[�h�͂������Ȃ̂��H�AD3DPRESENT_INTERVAL_ONE �Ƃ����߂��H

        if(GGAF_PROPERTY(DUAL_VIEW)) {
            _paPresetPrm[1] = _paPresetPrm[0]; //�R�R�܂ł𕡐�
            _paPresetPrm[0].EnableAutoDepthStencil = TRUE; //Z �o�b�t�@�̎����쐬
            _paPresetPrm[1].EnableAutoDepthStencil = TRUE;
        } else {

            _paPresetPrm[0].EnableAutoDepthStencil = TRUE; //Z �o�b�t�@�̎����쐬
        }


//        //�f�X�v���C���[�h�̎擾
//        D3DDISPLAYMODE structD3DDisplayMode0; //���ʂ��i�[�����\����
//        hr = GgafDxGod::_pID3D9->GetAdapterDisplayMode(0, &structD3DDisplayMode0);
//        returnWhenFailed(hr, D3D_OK, "GetAdapterDisplayMode �Ɏ��s���܂����B");
//        if(GGAF_PROPERTY(DUAL_VIEW)) {
//            D3DDISPLAYMODE structD3DDisplayMode1;
//            hr = GgafDxGod::_pID3D9->GetAdapterDisplayMode(1, &structD3DDisplayMode1);
//            returnWhenFailed(hr, D3D_OK, "2��ʖ� GetAdapterDisplayMode �Ɏ��s���܂���");
//            _paPresetPrm[0].BackBufferFormat = structD3DDisplayMode0.Format; //���݂̉�ʃ��[�h�𗘗p
//            _paPresetPrm[1].BackBufferFormat = structD3DDisplayMode1.Format; //���݂̉�ʃ��[�h�𗘗p
//        } else {
//            _paPresetPrm[0].BackBufferFormat = structD3DDisplayMode0.Format; //���݂̉�ʃ��[�h�𗘗p
//            _paPresetPrm[1].BackBufferFormat = D3DFMT_UNKNOWN; //���݂̉�ʃ��[�h�𗘗p
//        }
    }

    //�A���`�A�C���A�X�ɂł��邩�`�F�b�N
    DWORD qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;
//    if( SUCCEEDED(GgafDxGod::_pID3D9->CheckDeviceMultiSampleType(
//        D3DADAPTER_DEFAULT,
//        D3DDEVTYPE_HAL,
//        _paPresetPrm[0].BackBufferFormat,  //TODO:�E�B���h�E���[�h����
//        GGAF_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
//        D3DMULTISAMPLE_2_SAMPLES,
//        &qualityLevels) ) )
//    {
//        if( SUCCEEDED(GgafDxGod::_pID3D9->CheckDeviceMultiSampleType(
//            D3DADAPTER_DEFAULT,
//            D3DDEVTYPE_HAL,
//            _paPresetPrm[0].AutoDepthStencilFormat,
//            GGAF_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
//            D3DMULTISAMPLE_2_SAMPLES,
//            NULL) ) )
//        {
//            multiSampleType = D3DMULTISAMPLE_2_SAMPLES;
//            _TRACE_("�n�[�h�E�F�A MultiSampleType = D3DMULTISAMPLE_2_SAMPLES �L���I�I");
//        } else {
//            multiSampleType = D3DMULTISAMPLE_NONE;
//            qualityLevels = D3DMULTISAMPLE_NONE;
//        }
//    } else {
//        multiSampleType = D3DMULTISAMPLE_NONE;
//        qualityLevels = D3DMULTISAMPLE_NONE;
//    }

    if(GGAF_PROPERTY(DUAL_VIEW)) {
        //�}���`�T���v���̐�
        _paPresetPrm[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE; D3DMULTISAMPLE_2_SAMPLES
        //�}���`�T���v���̕i�����x��
        _paPresetPrm[0].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
        //�}���`�T���v���̐�
        _paPresetPrm[1].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
        //�}���`�T���v���̕i�����x��
        _paPresetPrm[1].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
    } else {
        //�}���`�T���v���̐�
        _paPresetPrm[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
        //�}���`�T���v���̕i�����x��
        _paPresetPrm[0].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
    }

//    //�}���`�T���v���̐�
//    _paPresetPrm[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
//    //�}���`�T���v���̕i�����x��
//    _paPresetPrm[0].MultiSampleQuality = 0;//qualityLevels - (qualityLevels > 0 ? 1 : 0);





    //Window�n���h�����ʎw��
    _paPresetPrm[0].hDeviceWindow = _pHWndPrimary;
    _paPresetPrm[1].hDeviceWindow = _pHWndSecondary;
    //�o�b�N�o�b�t�@�T�C�Y
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        if(GGAF_PROPERTY(DUAL_VIEW)) {
            //�t���X�N���[�����[�h�E�Q��ʎg�p
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
            _paPresetPrm[1].BackBufferHeight = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
        } else {
            //�t���X�N���[�����[�h�E�P��ʎg�p
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = 0;
            _paPresetPrm[1].BackBufferHeight = 0;
        }
    } else {
        if(GGAF_PROPERTY(DUAL_VIEW)) {
            //�E�B���h�E���[�h�E�Q��ʎg�p
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = 0;
            _paPresetPrm[1].BackBufferHeight = 0;
        } else {
            //�E�B���h�E���[�h�E�P��ʎg�p
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = 0;
            _paPresetPrm[1].BackBufferHeight = 0;
        }
    }

    _paDisplayMode = NEW D3DDISPLAYMODEEX[_num_adapter > 2 ? _num_adapter : 2];
    _paDisplayMode[0].Size = sizeof(_paDisplayMode[0]);
    _paDisplayMode[0].Width = _paPresetPrm[0].BackBufferWidth;
    _paDisplayMode[0].Height = _paPresetPrm[0].BackBufferHeight;
    _paDisplayMode[0].Format = _paPresetPrm[0].BackBufferFormat;
    _paDisplayMode[0].RefreshRate = _paPresetPrm[0].FullScreen_RefreshRateInHz;
    _paDisplayMode[0].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    _paDisplayMode[1].Size = sizeof(_paDisplayMode[1]);
    _paDisplayMode[1].Width = _paPresetPrm[1].BackBufferWidth;
    _paDisplayMode[1].Height = _paPresetPrm[1].BackBufferHeight;
    _paDisplayMode[1].Format = _paPresetPrm[1].BackBufferFormat;
    _paDisplayMode[1].RefreshRate = _paPresetPrm[1].FullScreen_RefreshRateInHz;
    _paDisplayMode[1].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    //�R��ʖڈȍ~�̃p�����[�^���R�s�[�ō쐬
    for (int i = 2; i < _num_adapter; i++) {
        _paPresetPrm[i] = _paPresetPrm[1];
        _paDisplayMode[i] = _paDisplayMode[1];
    }

    //�t���X�N���[���ɏo���邩���ׂ�
    _TRACE_("_num_adapter = "<< _num_adapter);
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        for (int disp_no = 0; disp_no <= (GGAF_PROPERTY(DUAL_VIEW) ? (_num_adapter-1) : 0); disp_no++) {
            int mode_num = GgafDxGod::_pID3D9->GetAdapterModeCount(disp_no,
                                                                    _paPresetPrm[0].BackBufferFormat);
            if (mode_num) {
                D3DDISPLAYMODE adp;
                for (int i = mode_num-1; i >= 0; i--) {
                    GgafDxGod::_pID3D9->EnumAdapterModes(disp_no,
                                                          _paPresetPrm[0].BackBufferFormat, i, &adp);
                    _TRACE_("disp_no["<<disp_no<<"].mode["<<i<<"]:"<<adp.Width<<"x"<<adp.Height);
                    if (disp_no > 1) {
                        //�R��ʖڈȍ~�P��ʖځE�Q��ʖڂ̉𑜓x�ȊO�̖���ȉ𑜓x��T���Ă���ɐݒ�B
                        if (adp.Format == _paPresetPrm[disp_no].BackBufferFormat) {
                            if ((adp.Width  == _paPresetPrm[0].BackBufferWidth && adp.Height == _paPresetPrm[0].BackBufferHeight) ||
                                (adp.Width  == _paPresetPrm[1].BackBufferWidth && adp.Height == _paPresetPrm[1].BackBufferHeight)
                            ) {
                                //�_��
                            } else {
                                _TRACE_("...USE!");
                                _paPresetPrm[disp_no].BackBufferWidth  = adp.Width;
                                _paPresetPrm[disp_no].BackBufferHeight = adp.Height;
                                _paDisplayMode[disp_no].Width  = _paPresetPrm[disp_no].BackBufferWidth;
                                _paDisplayMode[disp_no].Height = _paPresetPrm[disp_no].BackBufferHeight;
                                break;
                            }
                        }
                    } else {
                        //�P��ʖځE�Q��ʖڂ́A�v���p�e�B�v���̉𑜓x��T��
                        if (adp.Format == _paPresetPrm[disp_no].BackBufferFormat &&
                            adp.Width  == _paPresetPrm[disp_no].BackBufferWidth  &&
                            adp.Height == _paPresetPrm[disp_no].BackBufferHeight ) {
                            //OK
                            _TRACE_("...BINGO!");
                            break;
                        }
                    }
                    if (i == 0) {
                        //�v�������g����𑜓x��������Ȃ�
                        std::stringstream ss;
                        if (GGAF_PROPERTY(DUAL_VIEW)) {
                            ss << _paPresetPrm[disp_no].BackBufferWidth<<"x"<<_paPresetPrm[disp_no].BackBufferHeight<<" �t���X�N���[�����[�h�ɂ��鎖���ł��܂���B\n"<<
                                   (disp_no+1)<<"��ʖڂ̉𑜓x�̐ݒ���m�F���Ă��������B";
                        } else {
                            ss << _paPresetPrm[disp_no].BackBufferWidth<<"x"<<_paPresetPrm[disp_no].BackBufferHeight<<" �t���X�N���[�����[�h�ɂ��鎖���ł��܂���B\n"<<
                                    "�𑜓x�̐ݒ���m�F���Ă��������B";
                        }
                        MessageBox(GgafDxGod::_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                        return E_FAIL;
                    }
                }
            } else {
                MessageBox(GgafDxGod::_pHWndPrimary, TEXT("�t���X�N���[�����[�h�\�ȉ𑜓x��񂪎擾�ł��܂���ł����B\n���g�p�̃r�f�I�J�[�h�ł̓v���O���������s�ł��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                return E_FAIL;
            }
        }
    }

    //�s�N�Z���V�F�[�_�[�A���_�V�F�[�_�[�o�[�W�����`�F�b�N
    _vs_v = caps.VertexShaderVersion;
    _ps_v = caps.PixelShaderVersion;
    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(_vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(_vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(_ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(_ps_v));
    if (_vs_v < D3DVS_VERSION(2, 0) || _ps_v < D3DPS_VERSION(2, 0)) {
        _TRACE_("�r�f�I�J�[�h�n�[�h�̒��_�V�F�[�_�[�ƃs���N�Z���V�F�[�_�[�́A���Ƀo�[�W���� 2_0 �ȏオ�����ł��B");
        _TRACE_("���g�p�̃r�f�I�J�[�h�ł́A���������삵�Ȃ����ꂪ����܂��B");
    }

//    //default
//    UINT AdapterToUse = D3DADAPTER_DEFAULT;
//    D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
//    // NVIDIA PerfHUD �p begin --------------------------------------------->

//#ifdef MY_DEBUG
//
//#if SHIPPING_VERSION
//    // When building a shipping version, disable PerfHUD (opt-out)
//#else
//    _TRACE_("Look for 'NVIDIA PerfHUD' adapter...");
//    // If it is present, override default settings
//    for (UINT Adapter = 0; Adapter < GgafDxGod::_pID3D9->GetAdapterCount(); Adapter++) {
//        D3DADAPTER_IDENTIFIER9 Identifier;
//        HRESULT Res;
//        Res = GgafDxGod::_pID3D9->GetAdapterIdentifier(Adapter, 0, &Identifier);
//        if (strstr(Identifier.Description, "PerfHUD") != 0) {
//            _TRACE_("found NVIDIA PerfHUD!");
//            AdapterToUse = Adapter;
//            DeviceType = D3DDEVTYPE_REF;
//            break;
//        }
//    }
//#endif
//
//#endif
    // <------------------------------------------------ NVIDIA PerfHUD �p end


    if (GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(DUAL_VIEW)) {
        //���t���X�N���[�� ���� �f���A���r���[ �̏ꍇ��
        //�f�o�C�X�쐬������ GgafDxGod::_pID3DDevice9 �֐ݒ肷��B
        //�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
        hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                             D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                             _paPresetPrm, _paDisplayMode);
        if (hr != D3D_OK) {
            _TRACE_("�}���`�w�b�hD3DCREATE_HARDWARE_VERTEXPROCESSING : "<<GgafDxCriticalException::getHresultMsg(hr));

            //�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                 _paPresetPrm, _paDisplayMode);
            if (hr != D3D_OK) {
                _TRACE_("�}���`�w�b�hD3DCREATE_HARDWARE_VERTEXPROCESSING : "<<GgafDxCriticalException::getHresultMsg(hr));

                //�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDxGod::_pHWndPrimary,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                     _paPresetPrm, _paDisplayMode);
                if (hr != D3D_OK) {
                    _TRACE_("�}���`�w�b�hD3DCREATE_SOFTWARE_VERTEXPROCESSING : "<<GgafDxCriticalException::getHresultMsg(hr));

                    //�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
                    MessageBox(GgafDxGod::_pHWndPrimary, TEXT("DirectX�̏������Ɏ��s���܂����B\n�}���`�w�b�h�f�B�X�v���C�������݂��Ă��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDxGod::init �f�o�C�X�� MULTI FULLSCRREEN REF �ŏ������ł��܂����B");
                }

            } else {
                _TRACE_("GgafDxGod::init �f�o�C�X�� MULTI FULLSCRREEN HAL(soft vp) �ŏ������ł��܂����B");
            }

        } else {
            _TRACE_("GgafDxGod::init �f�o�C�X�� MULTI FULLSCRREEN HAL(pure vp) �ŏ������ł��܂����B");
        }

    } else {
        //��(�t���X�N���[�� ���� �f���A���r���[) �ȊO�̏ꍇ��
        //�f�o�C�X�쐬������ GgafDxGod::_pID3DDevice9 �֐ݒ肷��B
        //�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
        hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                             D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                             &_paPresetPrm[0], &_paDisplayMode[0]);
//                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
//                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        if (hr != D3D_OK) {
            //�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                 &_paPresetPrm[0], &_paDisplayMode[0]);
            if (hr != D3D_OK) {
                //�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDxGod::_pHWndPrimary,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                     &_paPresetPrm[0], &_paDisplayMode[0]);
                if (hr != D3D_OK) {
                    //�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
                    MessageBox(GgafDxGod::_pHWndPrimary, TEXT("DirectX�̏������Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDxGod::init �f�o�C�X�� REF �ŏ������ł��܂����B");
                }

            } else {
                _TRACE_("GgafDxGod::init �f�o�C�X�� HAL(soft vp) �ŏ������ł��܂����B");
            }

        } else {
            _TRACE_("GgafDxGod::init �f�o�C�X�� HAL(pure vp) �ŏ������ł��܂����B");
        }
    }

    //���̑��K�v�ȏ�����
    _pCubeMapTextureManager = NEW GgafDxTextureManager("CubeMapTexManager");
    _pBumpMapTextureManager = NEW GgafDxTextureManager("BumpMapTexManager");
    _pModelManager = NEW GgafDxModelManager("ModelManager");
    _pEffectManager = NEW GgafDxEffectManager("EffectManager");
    GgafDxUtil::init();  //���[�e�B���e�B����
    GgafDxInput::init(); //DirectInput����
    GgafDxSound::init(); //DirectSound����

    //�f�o�C�X������
    hr = initDx9Device();
    if (hr == E_FAIL) {
        return E_FAIL;
    }
    Sleep(1000);
    //�t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���[�쐬
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        hr = restoreFullScreenRenderTarget();
        if (hr == E_FAIL) {
            return E_FAIL;
        }
    }

    //2011/09/28
    //TODO:VISTA�łQ��ʃt���X�N���[�����A�N���b�N�Ńt���X�N���[���������̑΍�
    //WDDM�Ńf�o�C�X�쐬���A�Q��ʃt���X�N���[�����ŋN��������A�Q��ʖڂ̗̈�̂����A
    //���Ƃ��Ƃ̂P��ʖڂ������̈�(�𑜓x�ύX�ɂ��Q��ʖڂւ͂ݏo���o�������j���N���b�N����ƁA
    //�t���X�N���[������������Ă��܂����Ƃ��C�ɂȂ����B���Ȃ�̎��Ԃ��₵�����A�������@�͌�����Ȃ������B
    //�������A�����ŃE�B���h�E���č\�z���邱�ƂŁA�Ȃ������͉���ł����B
    //���Ԃ�A���K�̕��@����Ȃ��B����̍�E�E�E�B
    if (_can_wddm && GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(DUAL_VIEW)) {
        hr = releaseFullScreenRenderTarget();
        hr = restoreFullScreenRenderTarget();
    }
    return D3D_OK;
}


//�Q��ʖڂ̍�����W�𒲂ׂ�
BOOL CALLBACK GgafDxGod::getSecondaryMoniterPixcoordCallback(HMONITOR hMonitor,
                                                             HDC hdcMonitor,
                                                             LPRECT lprcMonitor,
                                                             LPARAM dwData) {
    //�R��ʖڈȍ~�̉𑜓x�́A�P��ʖځE�Q��ʖڂ̉𑜓x�ȊO�̖���ȉ𑜓x�ɐݒ肳��Ă��邱�Ƃ��O��
    GgafDxGod* pGod = (GgafDxGod*)dwData;
    MONITORINFOEX moniter_info;
    moniter_info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &moniter_info);
    if (moniter_info.dwFlags != MONITORINFOF_PRIMARY) {
        //�v���C�}�����j�^�ł͖���
        if (moniter_info.rcMonitor.right - moniter_info.rcMonitor.left == GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) &&
           moniter_info.rcMonitor.bottom - moniter_info.rcMonitor.top == GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT)
        ) {
            //�v���C�}�����j�^�ł͖����A���Q��ʖڂ̉𑜓x�Ɉ�v�B
            //����ĂQ��ʖڂƌ��Ȃ�(���U�@�łȂ��Ȃ��E�E�E)

            //�Q��ʖڂ̍�����W���㏑���ۑ�
            pGod->_secondary_screen_x = moniter_info.rcMonitor.left;
            pGod->_secondary_screen_y = moniter_info.rcMonitor.top;
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

HRESULT GgafDxGod::createDx9Device(UINT Adapter,
                                   D3DDEVTYPE DeviceType,
                                   HWND hFocusWindow,
                                   DWORD BehaviorFlags,
                                   D3DPRESENT_PARAMETERS* pPresentationParameters,
                                   D3DDISPLAYMODEEX* pFullscreenDisplayMode
                                  ) {
    HRESULT hr;
    if (_can_wddm) {
        if (!GGAF_PROPERTY(FULL_SCREEN)) {
            pFullscreenDisplayMode = NULL;
        }
        IDirect3D9Ex* pID3D9Ex = (IDirect3D9Ex*)GgafDxGod::_pID3D9;
        IDirect3DDevice9Ex* pID3DDevice9Ex;
        hr = pID3D9Ex->CreateDeviceEx(Adapter,
                                      DeviceType,
                                      hFocusWindow,
                                      BehaviorFlags,
                                      pPresentationParameters,
                                      pFullscreenDisplayMode,
                                      &pID3DDevice9Ex
                                      );
        GgafDxGod::_pID3DDevice9 = (IDirect3DDevice9Ex*)pID3DDevice9Ex;
    } else {
        hr = GgafDxGod::_pID3D9->CreateDevice(Adapter,
                                              DeviceType,
                                              hFocusWindow,
                                              BehaviorFlags,
                                              pPresentationParameters,
                                              &GgafDxGod::_pID3DDevice9
                                              );
    }
    return hr;
 }

HRESULT GgafDxGod::initDx9Device() {
    //���C�g�\���̂́A�V�F�[�_�[�̃p�����[�^�ɂȂ鎞�����邽�ߕK�v�B
    D3DXVECTOR3 vecDirection(-1.0f, -1.0f, 1.0f);
    D3DXVec3Normalize(&vecDirection, &vecDirection); //���K��
    ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9));
    GgafDxGod::_d3dlight9_default.Direction = vecDirection;
    GgafDxGod::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL;
    GgafDxGod::_d3dlight9_default.Diffuse.a = 1.0f;
    GgafDxGod::_d3dlight9_default.Diffuse.r = 1.0f;
    GgafDxGod::_d3dlight9_default.Diffuse.g = 1.0f;
    GgafDxGod::_d3dlight9_default.Diffuse.b = 1.0f;

    GgafDxGod::_d3dlight9_default.Ambient.a = 1.0f;
    GgafDxGod::_d3dlight9_default.Ambient.r = 0.3f; //�A���r�G���g���C�g��SetRenderState(D3DRS_AMBIENT, 0x00303030)�Őݒ�
    GgafDxGod::_d3dlight9_default.Ambient.g = 0.3f;
    GgafDxGod::_d3dlight9_default.Ambient.b = 0.3f;

    //GgafDxGod::_d3dlight9_default.Range = 1000.0f;


    //���C�g���Z�b�g
    //    GgafDxGod::_pID3DDevice9->SetLight(0, &GgafDxGod::_d3dlight9_default);
    //���C�g�X�C�b�`ON
    //    GgafDxGod::_pID3DDevice9->LightEnable(0, TRUE);
    //GgafDxGod::_pID3DDevice9->LightEnable(0, FALSE);
    //�����_���Ƀ��C�g�̉e���i�A�e�j��L��
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
    //�����_���Ƀ��C�g�̉e���i�A�e�j�𖳌� (�s�N�Z���V�F�[�_�[�ōs�Ȃ����߁j
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
    //�����_���A���E�ɋ��ʂ̃A���r�G���g���C�g��L���ɂ����悤�ɕ`��
    //   GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _dwAmbientBrightness_default);

    // Z�o�b�t�@��L����
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�𖳌���
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    //Z�o�b�t�@�������݉�
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //Z�o�b�t�@�������ݕs��
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    //D3DRENDERSTATE_ZFUNC

    //�X�e���V���e�X�g�̕��@
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //��Ƀe�X�g���p�X
    //��Ɏ��s�������ɃX�e���V���̒l���ǂ��ω������邩
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //�ω��Ȃ�
    //Z�e�X�g�Ŏ��s�����ꍇ�̃X�e���V���l�̕ω�
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //�ω��Ȃ�


    //���i�����v���j���ɃJ�����O �捶����W�n
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //�J�����O���Ȃ�
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // �f�B�U�����O
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
    // �}���`�T���v�����O�A���`�G�C���A�X(�Ƃ����Ă��t���X�N���[�������H)��TODO:�܂���
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

    //�s�N�Z���P�ʂ̃A���t�@�e�X�g��L��
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //���ݒ�̓V�F�[�_�[�ɏ������ɂ����̂ŃR�����g
    // �A���t�@�u�����h�n�m
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //2�i�K�ځA�������e�N�X�`����\��t�����|���S���ƃo�b�N�o�b�t�@�i�����_�[�^�[�Q�b�g�j�Ƃ̍���
    //�F�̎Z�o���@�̐ݒ�
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); //D3DBLENDOP_ADD=�]�����ɓ]���悪���Z
    //�����W��
    //    //��ɏ����摜�̍����@(�V�F�[�_�[�ɉe��)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=���ʂɕ`���B�|���S���̃A���t�@�l�̔Z���ŕ`���B�A���t�@�l�̒l��������΍����قǁA�Z���`���B
    //    //���n�̉摜�̍����@(�V�F�[�_�[�ɉe��)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=��ɕ`���|���S���̃A���t�@�l�̔Z���ɂ���āA���n�̕`��𔖂�����B



    //���_�J���[�𖳌��ɂ���
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, FALSE );
    // GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, TRUE );
    //    //�ʂ̃A���r�G���g���˂́A�}�e���A�����Q�Ƃ���悤�ɐݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃f�t���[�Y���˂́A�}�e���A�����Q�Ƃ���悤�ɐݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃G�~�b�V�u���˂́A�}�e���A�����Q�Ƃ���ݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃X�y�L�������˂́A�}�e���A�����Q�Ƃ���ݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    //���_�����g�p����Ƃ�
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);

    //
    //
    // �A���`�G�C���A�X�̎w��
    //GgafDxGod::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //GgafDxGod::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    //  Type��D3DSAMP_MINFILTER/D3DSAMP_MAGFILTER�i�g��/�k�����j ??D3DTSS_MAGFILTER
    //  Value��D3DTEXTUREFILTERTYPE�񋓌^���w�肷��
    //  D3DTEXF_POINT�@�@�@�@�F�t�B���^�������Ȃ��B�����`��ł���
    //  D3DTEXF_LINEAR�@�@�@�F���j�A�t�B���^�i���`�⊮�j
    //  D3DTEXF_ANISOTROPIC�@�F�ٕ����t�B���^�B�n�\�ʂȂǂ́A�g��k��������O�Ɖ��ňقȂ�ꍇ�Ɏg��
    //  D3DTEXF_PYRAMIDALQUAD�F�e���g�t�B���^�B���j�A�t�B���^�Ƃ��܂�ς��Ȃ��炵��
    //  D3DTEXF_GAUSSIANQUAD �F�K�E�V�A���t�B���^�B�܂��̖����ڂ����t�B���^
    //  ���w�肷��B

    //2009/3/4 SetSamplerState�̈Ӗ��������뗝������B
    //SetSamplerState�̓e�N�X�`������ǂ��T���v�����O�i�ǂݎ�邩�j���邩�̐ݒ�B
    //������A���`�G�C���A�X���Ă����Ă��A�e�N�X�`�������A���`�G�C���A�X��������܂���B
    //����s�N�Z���V�F�[�_�[�őS�������̂ŁA���̂�����̐ݒ�́A�S������Ȃ��Ȃ�͂����B


    //�A���`�G�C���A�X�ɂ�����郌���_�����O�X�e�[�g
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);

    //�F�������S�ăV�F�[�_�[�ŏ����ɂȂ����̂ŃR�����g
    //SetTextureStageState�͔p�~�H
    //  1�i�K�ڃ|���S���ƃe�N�X�`���̍������@�ݒ�
    //    //�e�N�X�`���[�̐F�ƁA���_�J���[��DIFFUSE�F����Z����悤�ɐݒ�
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    //    //�e�N�X�`���[�̃��ƁA���_�J���[�̃�����Z����悤�ɐݒ�
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


    //GgafDxCamera�ֈړ�����
    // VIEW�ϊ��i�J�����ʒu�j�ݒ�
    //D3DXMATRIX _matView; // �r���[�ϊ��s��
    //    DELETE_POSSIBLE_NULL(_pVecCamFromPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamLookatPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamUp);

    //GgafDxCamera�ֈړ�����
    // �ˉe�ϊ��i�R�c�����ʁj
    //D3DXMATRIX _matProj; // �ˉe�ϊ��s��
    //GgafDxGod::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_matProj);
    HRESULT hr;
    //�o�b�N�o�b�t�@���E�B���h�EBG�F�ŃN���A
    //�����ł�RenderTarget�͂܂��A�ʏ�̃o�b�N�o�b�t�@�ł���
    hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK, "�w�i�F(_color_border)�̓h��Ԃ����A��ʃN���A�Ɏ��s���܂����B");
    return D3D_OK;
}


HRESULT GgafDxGod::restoreFullScreenRenderTarget() {
    if (!GGAF_PROPERTY(FULL_SCREEN)) {
        _TRACE_("GgafDxGod::restoreFullScreenRenderTarget() ���x�����t���X�N���[�����ӊO�A�Ăяo���s�v�ł��B");
        return D3D_OK;
    }
    HRESULT hr;
    //�`���ƂȂ�e�N�X�`����ʓr�쐬�i�o�b�N�o�b�t�@�I�Ȏg�p���s���j
    hr = GgafDxGod::_pID3DDevice9->CreateTexture(
                                        GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH),
                                        GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT),
                                        1, //MipLevel Mip����
                                        D3DUSAGE_RENDERTARGET,
                                        _paPresetPrm[0].BackBufferFormat,
                                        D3DPOOL_DEFAULT,
                                        &_pRenderTexture,
                                        NULL);

//    LPDIRECT3DTEXTURE9 pIDirect3DTexture9;
//    HRESULT hr = D3DXCreateTextureFromFileEx(
//                     GgafDxGod::_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice,
//                     texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
//                     D3DX_DEFAULT,              // [in] UINT Widths,
//                     D3DX_DEFAULT,              // [in] UINT Height,
//                     D3DX_DEFAULT,              // [in] UINT MipLevels,  //D3DX_DEFAULT,
//                     0,                         // [in] DWORD Usage,
//                     D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
//                     D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
//                     D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINT�Ń{���P�i�C. D3DX_FILTER_LINEAR
//                     D3DX_DEFAULT,              // [in] DWORD MipFilter,
//                     0,                         // [in] D3DCOLOR ColorKey,
//                     _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
//                     NULL,                      // [in] PALETTEENTRY *pPalette,
//                     &pIDirect3DTexture9        // [out] LPDIRECT3DTEXTURE9* ppTexture
//                );

    //TODO:�A���`�G�C���A�X�̎����̂���
    //     �e�N�X�`���[�̑���ɃT�[�t�F�C�X���������B
    //    HRESULT CreateRenderTarget(
    //        UINT Width,
    //        UINT Height,
    //        D3DFORMAT Format,
    //        D3DMULTISAMPLE_TYPE MultiSample,
    //        DWORD MultisampleQuality,
    //        BOOL Lockable,
    //        IDirect3DSurface9** ppSurface,
    //        HANDLE* pHandle
    //    );


    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`��("<<GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)<<"x"<<GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT)<<")�̍쐬�Ɏ��s�B\n�T�C�Y���m�F���ĉ������B");
    //RenderTarget(�`���)���e�N�X�`���֐؂�ւ�
    hr = _pRenderTexture->GetSurfaceLevel(0, &_pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`���̃T�[�t�F�C�X�擾�Ɏ��s���܂����B");
    hr = GgafDxGod::_pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`���� SetRenderTarget �o���܂���ł����B");


    //�e�N�X�`���ɕ`�悷��ۂ̐[�x�o�b�t�@�p�T�[�t�F�C�X��ʓr�쐬
    hr = GgafDxGod::_pID3DDevice9->CreateDepthStencilSurface(
            GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH),
            GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT),
            _paPresetPrm[0].AutoDepthStencilFormat, //D3DFORMAT           Format,
            _paPresetPrm[0].MultiSampleType,        //D3DMULTISAMPLE_TYPE MultiSample,
            _paPresetPrm[0].MultiSampleQuality,     //DWORD               MultisampleQuality,
            TRUE,                                   //BOOL                Discard, SetDepthStencileSurface�֐��Ő[�x�o�b�t�@��ύX�������Ƀo�b�t�@��j�����邩�ǂ���
            &_pRenderTextureZ,                      //IDirect3DSurface9** ppSurface,
            NULL                                    //HANDLE*             pHandle ���ݖ��g�p
    );
    //�[�x�o�b�t�@�쐬���������́A�[�x�o�b�t�@�p�T�[�t�F�C�X����L�ɕύX
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`����Z�o�b�t�@�쐬�Ɏ��s���܂����B");
    hr =  GgafDxGod::_pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`���� SetDepthStencilSurface �o���܂���ł����B");
    //�w�i�F�ŃN���A
    hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
    hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK,  "�N���A�F(_color_border)�̓h��Ԃ����A��ʃN���A�Ɏ��s���܂����B");

    //�A�_�v�^�Ɋ֘A�t����ꂽ�X���b�v�`�F�[�����擾���ăo�b�N�o�b�t�@�擾
    hr = GgafDxGod::_pID3DDevice9->GetSwapChain( 0, &_apSwapChain[0] );
    returnWhenFailed(hr, D3D_OK, "�X���b�v�`�F�C���擾�Ɏ��s���܂����B");
    hr = _apSwapChain[0]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_apBackBuffer[0] );
    returnWhenFailed(hr, D3D_OK, "�X���b�v�`�F�C������A�^�[�Q�b�g�̃o�b�N�o�b�t�@�擾�Ɏ��s���܂����B");
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        hr = GgafDxGod::_pID3DDevice9->GetSwapChain( 1, &_apSwapChain[1] );
        returnWhenFailed(hr, D3D_OK, "�Q��ʖڂ̃X���b�v�`�F�C���擾�Ɏ��s���܂����B\n�}���`�f�B�X�v���C���ɖ�蔭�����܂����B");
        hr = _apSwapChain[1]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_apBackBuffer[1] );
        returnWhenFailed(hr, D3D_OK, "�Q��ʖڂ̃X���b�v�`�F�C������A�^�[�Q�b�g�̃o�b�N�o�b�t�@�擾�Ɏ��s���܂����B");
    }

    //�t���X�N���[�����A�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@��w�i�F�œh��
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1��ʖځA�w�i�F�h�Ɏ��s���܂����B(1)\n"<<
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);

        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                _apBackBuffer[1]      , &_aRect_ViewScreen[1],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2��ʖځA�w�i�F�h�Ɏ��s���܂����B(1)\n"<<
                                      "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);
    } else {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN �w�i�F�h�Ɏ��s���܂����B(1)");
    }

    hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
    returnWhenFailed(hr, D3D_OK, "Present(NULL, NULL, NULL, NULL)�Ɏ��s���܂����B");
    //�t���b�v���Ă�����x�w�i�F�œh��
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1��ʖځA�w�i�F�h�Ɏ��s���܂����B(2)\n"<<
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);

        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                _apBackBuffer[1]      , &_aRect_ViewScreen[1],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2��ʖځA�w�i�F�h�Ɏ��s���܂����B(2)\n"<<
                                      "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);
    } else {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE
                );
        checkDxException(hr, D3D_OK, "FULL_SCREEN �w�i�F�h�Ɏ��s���܂����B(2)");
    }
    //�����ʂȊ��������AVISTA��XP�̂Q��ʖڃt���X�N���[�����[�h��
    //  ���Ή�������̂͂��̂悤�ȃR�[�h�����Ȃ��Ƃ������_�B


    if (GGAF_PROPERTY(DUAL_VIEW)) {
        //�Q��ʖڂ̃E�B���h�E�ʒu��␳
        EnumDisplayMonitors(NULL, NULL, GgafDxGod::getSecondaryMoniterPixcoordCallback, (LPARAM)this);
        _TRACE_("�Q��ʖڂ̍��W("<<_secondary_screen_x<<","<<_secondary_screen_y<<")");
        ShowWindow(_pHWndSecondary, SW_SHOWNORMAL);
        UpdateWindow(_pHWndSecondary);
        SetWindowPos(_pHWndSecondary,
                     HWND_TOPMOST,
                     _secondary_screen_x, _secondary_screen_y, 0, 0,
                     SWP_SHOWWINDOW | SWP_NOSIZE );
        //��������s�Ȃ��Ă����Ȃ��ƁA����N�����A�Q��ʖڂ̗̈���N���b�N�����ہA
        //�Ăуt���X�N���[������������Ă��܂��B
        //�P��ʖڂ̓t���X�N���[���ɂȂ��Ă��AWindow�̍��オ(0,0)�̂��߃Y���Ȃ��̂ŁA
        //SetWindowPos�͂��Ԃ�s�v�B�������O�̂��߂ɓ��l�̏������s���B
        ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
        UpdateWindow(_pHWndPrimary);
        SetWindowPos(_pHWndPrimary,
                     HWND_TOPMOST,
                     0, 0, 0, 0,
                     SWP_SHOWWINDOW | SWP_NOSIZE);
    } else {
        ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
        UpdateWindow(_pHWndPrimary);
        SetWindowPos(_pHWndPrimary,
                     HWND_TOPMOST,
                     0, 0, 0, 0,
                     SWP_SHOWWINDOW | SWP_NOSIZE);
    }

    return D3D_OK;
}



HRESULT GgafDxGod::releaseFullScreenRenderTarget() {
    RELEASE_SAFETY(_pRenderTextureSurface);
    RELEASE_SAFETY(_pRenderTexture);
    RELEASE_SAFETY(_pRenderTextureZ);
    RELEASE_SAFETY(_apBackBuffer[0]);
    RELEASE_SAFETY(_apSwapChain[0]);
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        RELEASE_SAFETY(_apBackBuffer[1]);
        RELEASE_SAFETY(_apSwapChain[1]);
    }
    return D3D_OK;
}

void GgafDxGod::presentUniversalMoment() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::presentUniversalMoment();
    }
}

void GgafDxGod::executeUniversalJudge() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::executeUniversalJudge();
    }
}
void GgafDxGod::makeUniversalMaterialize() {
    if (_is_device_lost_flg) {
        return;
    }
    TRACE("GgafDxGod::materialize() start");
    HRESULT hr;
        //�ʏ펞����

    //�o�b�t�@�N���A
    hr = GgafDxGod::_pID3DDevice9->Clear(0, // �N���A�����`�̈�̐�
                                         NULL, // ��`�̈�
                                         D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                         _color_clear, //�N���A�F�inot �w�i�F�j
                                         1.0f,         // Z�o�b�t�@�̃N���A�l
                                         0             // �X�e���V���o�b�t�@�̃N���A�l
                                        );
    checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->Clear() �Ɏ��s���܂����B");

    //�`�掖�O����
    hr = GgafDxGod::_pID3DDevice9->BeginScene();
    checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->BeginScene() �Ɏ��s���܂����B");
    //�S�ċ���I�i�`��j
#ifdef MY_DEBUG
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
#endif
    GgafGod::makeUniversalMaterialize(); //�X�[�p�[��materialize���s
    //�`�掖�㏈��
    hr = GgafDxGod::_pID3DDevice9->EndScene();
    checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->EndScene() �Ɏ��s���܂����B");

    TRACE("GgafDxGod::makeUniversalMaterialize() end");
}

void GgafDxGod::presentUniversalVisualize() {
    //�����A������
    //if (GgafDxGod::_pID3DDevice9->Present(NULL,&_aRect_Present[0],NULL,NULL) == D3DERR_DEVICELOST) {
    //        static D3DRASTER_STATUS rs;
    //        while (SUCCEEDED(GgafDxGod::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
    //            if(rs.InVBlank) {
    //                break; //�����A�����Ԃł͂Ȃ�
    //            } else {
    //                Sleep(1);
    //            }
    //        }
    HRESULT hr;
    if (_is_device_lost_flg != true) {
        if (_adjustGameScreen && _pHWnd_adjustScreen) {
            adjustGameScreen(_pHWndPrimary);
            adjustGameScreen(_pHWndSecondary);
        }

        //Present
        if (GGAF_PROPERTY(FULL_SCREEN)) {
            if (GGAF_PROPERTY(DUAL_VIEW)) {
                //�Q��ʎg�p�E�t���X�N���[��
                //��ʂO�o�b�N�o�b�t�@����ʂP�o�b�N�o�b�t�@�փR�s�[����
                hr = GgafDxGod::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                        _apBackBuffer[0]      , &_aRect_Present[0],
                        D3DTEXF_LINEAR); //TODO:D3DTEXF_LINEAR���I�v�V�����w��ɂ��邩�H
                checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1��ʖ� StretchRect() �Ɏ��s���܂����B\n_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);

                hr = GgafDxGod::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                        _apBackBuffer[1]      , &_aRect_Present[1],
                        D3DTEXF_LINEAR);
                checkDxException(hr, D3D_OK, "StretchRect() �Ɏ��s���܂����B");

                hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
            } else {
                //�P��ʎg�p�E�t���X�N���[��
                hr = GgafDxGod::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,
                        &_rectRenderTargetBuffer,
                        _apBackBuffer[0],
                        &_aRect_Present[0],
                        D3DTEXF_LINEAR);
                checkDxException(hr, D3D_OK, "FULL 1gamen StretchRect() �Ɏ��s���܂����B");

                hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
            }
        } else {
            if (GGAF_PROPERTY(DUAL_VIEW)) {
                //�Q��ʎg�p�E�E�B���h�E���[�h
                if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //�c����Œ胂�[�h
                    hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[0], &_aRect_Present[0], NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[1], &_aRect_Present[1], _pHWndSecondary, NULL);
                    }
                } else {
                    //�c���X�g���b�`���[�h
                    hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[0], NULL, NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[1], NULL, _pHWndSecondary, NULL);
                    }
                }
            } else {
                //�P��ʎg�p�E�E�B���h�E���[�h
                if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //�c����Œ胂�[�h
                    hr = GgafDxGod::_pID3DDevice9->Present(NULL, &_aRect_Present[0], NULL, NULL);
                } else {
                    //�c���X�g���b�`���[�h
                    hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
                }
            }
        }

        if (hr != D3D_OK) { //hr �� Present �̖߂�l
             //�o�n�ّf�I���l�H
//            _TRACE_("���x�����f�o�C�X�ُ픭��!!" <<DXGetErrorString(hr) << " "<< DXGetErrorDescription(hr));
            _TRACE_("���x�����f�o�C�X�ُ픭��!! HRESULT="<<hr);
            if (hr == D3DERR_DEVICELOST) {
                _TRACE_("�ʏ�̐���f�o�C�X���X�g�I");
            }

            Sleep(100); // 1�b�҂�
            _TRACE_("�y�f�o�C�X���X�g�����zBEGIN ------>");

            //�H��x�~
            _TRACE_("�y�f�o�C�X���X�g�����z�H���~ BEGIN ------>");
            int cnt = 0;
            GgafFactory::beginRest();
         ___EndSynchronized1; // <----- �r���I��
            for (int i = 0; GgafFactory::isResting() == false; i++) {
                Sleep(10); //�H�ꂪ���������܂ő҂�
                if (i > 10*60*100) {
                    _TRACE_("�y�f�o�C�X���X�g����/�H���~�z 10���ҋ@���܂������A�H�ꂩ�甽��������܂���B����break���܂��B�v����");
                    break;
                }
            }
         ___BeginSynchronized1; // ----->�r���J�n
            _TRACE_("�y�f�o�C�X���X�g�����z�H���~ <-------- END");

            _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X��� BEGIN ------>");

            //�����_�����O�^�[�Q�b�g�A�f�o�C�X���X�g����
            if (GGAF_PROPERTY(FULL_SCREEN)) {
                releaseFullScreenRenderTarget();
            }
            //���}�b�v�e�N�X�`���A�f�o�C�X���X�g����
            GgafDxGod::_pCubeMapTextureManager->releaseAll();
            GgafDxGod::_pBumpMapTextureManager->releaseAll();
            //�G�t�F�N�g�A�f�o�C�X���X�g����
            GgafDxGod::_pEffectManager->onDeviceLostAll();
            //���f�����
            GgafDxGod::_pModelManager->onDeviceLostAll();
            //�S�m�[�h�ɉ�����Ȃ����C�x���g����
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_ON_DEVICE_LOST, this);
            _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X��� <-------- END");
            _is_device_lost_flg = true;
        }
    }

    if (_is_device_lost_flg) {
        _TRACE_("�y�f�o�C�X���X�g����/���\�[�X����z���������x���`�F�b�N BEGIN ------>");
        //for(int i = 0; i < 300; i++) {
        while(true) {
            if (_can_wddm) {
                hr = ((IDirect3DDevice9Ex*)GgafDxGod::_pID3DDevice9)->CheckDeviceState(_pHWndPrimary);
                if (hr == D3DERR_DEVICELOST || hr == S_PRESENT_OCCLUDED) {
                    return;
                } else {
                    break;
                }
            } else {
                hr = GgafDxGod::_pID3DDevice9->TestCooperativeLevel();
                if (hr == D3DERR_DEVICELOST) {
                    return;
                } else {
                    break;
                }
            }
        }
        _TRACE_("�y�f�o�C�X���X�g����/���\�[�X����z���������x���`�F�b�N <-------- END");

        //�f�o�C�X���Z�b�g�����݂�
        _TRACE_("�y�f�o�C�X���X�g�����z�f�o�C�X���Z�b�g BEGIN ------>");
        for(int i = 0; i < 100*60*10; i++) {
            if (GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(DUAL_VIEW)) {
                hr = GgafDxGod::_pID3DDevice9->Reset(_paPresetPrm);
            } else {
                hr = GgafDxGod::_pID3DDevice9->Reset(&(_paPresetPrm[0]));
            }
            if (hr != D3D_OK) {
                if (hr == D3DERR_DRIVERINTERNALERROR) {
                    Sleep(10);
                    return;
                } else if (hr == D3DERR_DRIVERINTERNALERROR) {
                    throwGgafDxCriticalException(hr, "�y�f�o�C�X���X�g����/�f�o�C�X���Z�b�g�zD3DERR_DRIVERINTERNALERROR�B�����I�����܂��B");
                } else if (hr == D3DERR_OUTOFVIDEOMEMORY) {
                    throwGgafDxCriticalException(hr, "�y�f�o�C�X���X�g����/�f�o�C�X���Z�b�g�zD3DERR_OUTOFVIDEOMEMORY�B������������܂���B�����I�����܂��B");
                } else {
                    Sleep(10);
                    return;
                }
            } else {
                break;
            }
        }
        _TRACE_("�y�f�o�C�X���X�g�����z�f�o�C�X���Z�b�g <-------- END");


        //�f�o�C�X�Đݒ�
        _TRACE_("�y�f�o�C�X���X�g�����z�f�o�C�X�č\�z BEGIN ------>");
        initDx9Device();
        _TRACE_("�y�f�o�C�X���X�g�����z�f�o�C�X�č\�z <-------- END");

        if (GGAF_PROPERTY(FULL_SCREEN)) {
            _TRACE_("�y�f�o�C�X���X�g�����z�t���X�N���[���������_�����O�^�[�Q�b�g�e�N�X�`���č\�z BEGIN ------>");
            restoreFullScreenRenderTarget();
            _TRACE_("�y�f�o�C�X���X�g�����z�t���X�N���[���������_�����O�^�[�Q�b�g�e�N�X�`���č\�z <-------- END");
        }

        //���\�[�X�č\�z
        _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X�č\�z BEGIN ------>");
        //���}�b�v�e�N�X�`���A���A����
        GgafDxGod::_pCubeMapTextureManager->restoreAll();
        GgafDxGod::_pBumpMapTextureManager->restoreAll();
        //�G�t�F�N�g���Z�b�g
        GgafDxGod::_pEffectManager->restoreAll();
        //���f���Đݒ�
        GgafDxGod::_pModelManager->restoreAll();
        //�S�m�[�h�ɍĐݒ肵�Ȃ����C�x���g����
        getUniverse()->throwEventToLowerTree(GGAF_EVENT_DEVICE_LOST_REDEPOSITORY, this);
        //�O��`�惂�f�����𖳌��ɂ���
        GgafDxModelManager::_pModelLastDraw = NULL;
        _is_device_lost_flg = false;
        _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X�č\�z <-------- END");

        //�H��ĊJ
        _TRACE_("�y�f�o�C�X���X�g�����z�H��ċN�� BEGIN ------>");
        GgafFactory::finishRest();
        _TRACE_("�y�f�o�C�X���X�g�����z�H��ċN�� <-------- END");

        _TRACE_("�y�f�o�C�X���X�g�����z<-------- END");

        Sleep(500);
        hr = GgafDxGod::_pID3DDevice9->Clear(0,    // �N���A�����`�̈�̐�
                                             NULL, // ��`�̈�
                                             D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                             _color_border, //�w�i�F      //D3DCOLOR_XRGB( 0, 0, 0 )
                                             1.0f, // Z�o�b�t�@�̃N���A�l
                                             0     // �X�e���V���o�b�t�@�̃N���A�l
                                            );
    }
}

void GgafDxGod::finalizeUniversal() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::finalizeUniversal();
    }
}

void GgafDxGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("GgafDxGod::clean() begin");
        for(int i = 0; i < 8; ++i) { GgafDxGod::_pID3DDevice9->SetTexture( i, NULL ); }
        for(int i = 0; i < 8; ++i) { GgafDxGod::_pID3DDevice9->SetStreamSource( i, NULL, 0, 0 ); }
        GgafDxGod::_pID3DDevice9->SetIndices( NULL );
        GgafDxGod::_pID3DDevice9->SetPixelShader( NULL );
        GgafDxGod::_pID3DDevice9->SetVertexShader( NULL );
        GgafDxGod::_pID3DDevice9->SetVertexDeclaration( NULL );

        GgafGod::clean();

        CmRandomNumberGenerator::getInstance()->release();
        //�ێ����f�����
        DELETE_IMPOSSIBLE_NULL(_pCubeMapTextureManager);
        DELETE_IMPOSSIBLE_NULL(_pBumpMapTextureManager);
        DELETE_IMPOSSIBLE_NULL(_pModelManager);
        DELETE_IMPOSSIBLE_NULL(_pEffectManager);
        _TRACE_("GgafDxGod::clean() end");
    }
}

void GgafDxGod::adjustGameScreen(HWND prm_pHWnd) {
    RECT rect;
    if (prm_pHWnd && !GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
        HRESULT hr;
        hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
        hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, _pHWndSecondary, NULL);
        }
        if (::GetClientRect(prm_pHWnd, &rect)) {
            LONG width = rect.right;
            LONG height = rect.bottom;
            LONG fix_width, fix_height;
            int pos1, pos2;
            if (GGAF_PROPERTY(DUAL_VIEW)) {
                fix_width  = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
                fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                pos1 = GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION1);
                pos2 = GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2);
            } else {
                fix_width  = GGAF_PROPERTY(GAME_BUFFER_WIDTH);
                fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                pos1 = GGAF_PROPERTY(SINGLE_VIEW_DRAW_POSITION);
                pos2 = GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2); //�Ƃ肠����
            }

            if (1.0f * width / height > 1.0f * fix_width / fix_height) {
                //��艡���ɂȂ��Ă��܂��Ă���
                double rate = 1.0 * height / fix_height; //�k����=�c���̔䗦
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left   = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(pos1, _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left   = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(pos2, _aRect_Present[1], width, height);
                }

            } else {
                //���c���ɂȂ��Ă��܂��Ă���
                double rate = 1.0 * width / fix_width; //�k����=�����̔䗦
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(pos1, _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(pos2, _aRect_Present[1], width, height);
                }
            }
        }
    } else {
        if (::GetClientRect(prm_pHWnd, &rect)) {
            if (prm_pHWnd == _pHWndPrimary) {
                _aRect_Present[0] = rect;
            } else {
                _aRect_Present[1] = rect;
            }

        }
    }
    GgafDxGod::_pID3DDevice9->GetViewport(&(P_CAM->_viewport));
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
}

void GgafDxGod::positionPresentRect(int prm_pos, RECT& out_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height) {
    // �V�@�W�@�X
    // �@�_�b�^
    // �S�\�T�\�U
    // �@�^�b�_
    // �P�@�Q�@�R
    //1:�����A2:���A3:�E���A4:���A5:�^�񒆁A6:�E�A7:����A8:��A9:�E��
    if (prm_pos == 5) {
        return;
    }
    if (prm_pos == 7 || prm_pos == 8 || prm_pos == 9) {
        out_rectPresent.bottom = out_rectPresent.bottom - out_rectPresent.top;
        out_rectPresent.top = 0;
    } else if (prm_pos == 1 || prm_pos == 2 || prm_pos == 3) {
        out_rectPresent.top = prm_screen_height - (out_rectPresent.bottom - out_rectPresent.top);
        out_rectPresent.bottom = prm_screen_height;
    }

    if (prm_pos == 7 || prm_pos == 4 || prm_pos == 1) {
        out_rectPresent.right = out_rectPresent.right - out_rectPresent.left;
        out_rectPresent.left = 0;
    } else if (prm_pos == 9 || prm_pos == 6 || prm_pos == 3) {
        out_rectPresent.left = prm_screen_width - (out_rectPresent.right - out_rectPresent.left);
        out_rectPresent.right = prm_screen_width;
    }
}

GgafDxGod::~GgafDxGod() {

    clean();
    _was_cleaned = true;
    //DirectSound���
    GgafDxSound::release();
    //DirectInput���
    GgafDxInput::release();

    if(GGAF_PROPERTY(FULL_SCREEN)) {
        releaseFullScreenRenderTarget();
    }

    _TRACE_("_pID3DDevice9 ��������[");
    Sleep(60);
    DELETEARR_IMPOSSIBLE_NULL(_paPresetPrm);
    DELETEARR_IMPOSSIBLE_NULL(_paDisplayMode);
    RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9);
    RELEASE_IMPOSSIBLE_NULL(_pID3D9);

}




//���� 2011/07/26
//
//�y�P��ʃE�B���h�E���[�h�z
//                                 �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                               �^                                        �^
//    �t�����g�o�b�t�@         �^                                        �^
//    (�E�C���h�E)           �^                                        �^
//                           �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P
//                           SINGLE_VIEW_WINDOW_WIDTH x SINGLE_VIEW_WINDOW_HEIGHT
//
//                                               ��
//                                               �b Present
//                                               �b(D3DSWAPEFFECT_COPY)
//                                               �b
//                                  �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �o�b�N�o�b�t�@              �^                                        �^
//                              �^                                        �^ Draw   �Q�Q�Q
//                            �^                                        �^    ��  �^    �^�Q�[���o�b�t�@
//                            �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P          �P�P�P
//                       RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT
//
//
//---------------------------------------------------------------------------------------------
//
//
//�y�Q��ʃE�B���h�E���[�h�z
//                            �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q             �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                          �^                    �^           �^                    �^
//    �t�����g�o�b�t�@    �^                    �^           �^                    �^
//    (�E�C���h�E)      �^                    �^           �^                    �^
//                      �P�P�P�P�P�P�P�P�P�P�P             �P�P�P�P�P�P�P�P�P�P�P
//                     DUAL_VIEW_WINDOW1_WIDTH x            DUAL_VIEW_WINDOW2_WIDTH x
//                       DUAL_VIEW_WINDOW1_HEIGHT             DUAL_VIEW_WINDOW2_HEIGHT
//
//                                 ��                               ��
//                                 �b Present                       �b Present
//                                 �b(D3DSWAPEFFECT_COPY)           �b (D3DSWAPEFFECT_COPY)
//
//                                  �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �o�b�N�o�b�t�@              �^                                        �^
//                              �^                                        �^ Draw   �Q�Q�Q
//                            �^                                        �^    ��  �^    �^�Q�[���o�b�t�@
//                            �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P          �P�P�P
//                    RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT
//
//
//---------------------------------------------------------------------------------------------
//
//
//�y�P��ʃt���X�N���[�����[�h�z
//                                         �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                                       �^                              �^
//                                     �^                              �^
//    �t�����g�o�b�t�@               �^                              �^
//    (�f�B�X�v���C)               �^                              �^
//                               �^                              �^
//                               �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P
//                                SINGLE_VIEW_FULL_SCREEN_WIDTH x
//                                  SINGLE_VIEW_FULL_SCREEN_HEIGHT
//
//                                                 ��
//                                                 �b Present
//                                                 �b(D3DSWAPEFFECT_DISCARD)
//                                        �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                                      �^                              �^
//                                    �^                              �^
//    �o�b�N�o�b�t�@                �^      _apBackBuffer[0]        �^
//                                �^                              �^
//                              �^                              �^
//                              �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P
//                               SINGLE_VIEW_FULL_SCREEN_WIDTH x
//                                 SINGLE_VIEW_FULL_SCREEN_HEIGHT
//
//                                                 ��
//                                                 �b StretchRect
//                                                 �b
//                                 �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �����_�[�^�[�Q�b�g         �^                                        �^
//    �e�N�X�`���[             �^       _pRenderTextureSurface           �^ Draw   �Q�Q�Q
//                           �^                                        �^    ��  �^    �^�Q�[���o�b�t�@
//                           �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P          �P�P�P
//                     RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT
//
//
//---------------------------------------------------------------------------------------------
//
//
//�y�Q��ʃt���X�N���[�����[�h�z
//                            �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q     |        �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                          �^                    �^     |      �^                    �^
//    �t�����g�o�b�t�@    �^                    �^       |    �^                    �^
//    (�f�B�X�v���C)    �^                    �^         |  �^                    �^
//                      �P�P�P�P�P�P�P�P�P�P�P           |  �P�P�P�P�P�P�P�P�P�P�P
//                     DUAL_VIEW_FULL_SCREEN1_WIDTH x    |   DUAL_VIEW_FULL_SCREEN2_WIDTH x
//                       DUAL_VIEW_FULL_SCREEN1_HEIGHT   |     DUAL_VIEW_FULL_SCREEN2_HEIGHT
//
//                               ��                                 ��
//                               �b Present                         �b Present
//                               �b(D3DSWAPEFFECT_DISCARD)          �b (D3DSWAPEFFECT_DISCARD)
//
//                            �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q             �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                          �^                    �^           �^                    �^
//    �o�b�N�o�b�t�@      �^  _apBackBuffer[0]  �^           �^  _apBackBuffer[1]  �^
//                      �^                    �^           �^                    �^
//                      �P�P�P�P�P�P�P�P�P�P�P             �P�P�P�P�P�P�P�P�P�P�P
//                     DUAL_VIEW_FULL_SCREEN1_WIDTH x        DUAL_VIEW_FULL_SCREEN2_WIDTH x
//                       DUAL_VIEW_FULL_SCREEN1_HEIGHT         DUAL_VIEW_FULL_SCREEN2_HEIGHT
//
//                                    ��                            ��
//                                    �b StretchRect                �b StretchRect
//                                    �b                            �b
//                                  �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �����_�[�^�[�Q�b�g          �^                                        �^
//    �e�N�X�`���[              �^       _pRenderTextureSurface           �^ Draw   �Q�Q�Q
//                            �^                                        �^    ��  �^    �^�Q�[���o�b�t�@
//                            �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P          �P�P�P
//                       RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT




//�ĂP
//                 <-------------------------------------------- 2048 --------------------------------------------->
//                 <--------- 512 --------->
//                 <------------------------- 1600 ------------------------------------------><------ 448 --------->
//
//         ^       +-----------------------+-----------------------+-----------------------+-+---------------------+
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//        512      |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         v       +-----------------------+-----------------------+-----------------------+-+---------------------+
//                                                                                         >-<-- 64


//�ĂQ
//                 <-------------------------------------------- 2048 --------------------------------------------->
//                 <--------- 512 --------->
//                 <------------------------- 1280 ----------------------------><-------------- 768 --------------->
//
//         ^   ^   +-----------------------+-----------------------+-----------+-----------+-----------------------+
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//        512 480  |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   v   +-----------------------+-----------------------+-----------+           |                       |
//         v  32   +-----------------------+-----------------------+-----------------------+-----------------------+
//
//                                                                 <----256----><---256---->


