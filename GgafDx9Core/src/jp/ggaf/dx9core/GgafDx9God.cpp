#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


//TODO:�R�����g�Ƃ���������B��������B


HWND GgafDx9God::_pHWndPrimary = NULL;
HWND GgafDx9God::_pHWndSecondary = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9_default;
D3DLIGHT9 GgafDx9God::_d3dlight9_temp;
DWORD GgafDx9God::_dwAmbientBrightness_default = 0xff404040;


//RECT GgafDx9God::_rectDualDisplayWindow_Primary;
//RECT GgafDx9God::_rectDualDisplayWindow_Secondary;
//RECT GgafDx9God::_rectDualDisplayFullScreen_Primary;
//RECT GgafDx9God::_rectDualDisplayFullScreen_Secondary;





//RECT*  GgafDx9God::_pRectViewScreen = NULL;

//double GgafDx9God::_cameraZ = 0;
//double GgafDx9God::_cameraZ_org = 0;
//double GgafDx9God::_tan_half_fovY = 0;
//double GgafDx9God::_dCamHarfXfovTan = 0;
//double GgafDx9God::_screen_aspect = 0;


D3DFILLMODE GgafDx9God::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDx9ModelManager* GgafDx9God::_pModelManager = NULL;
GgafDx9EffectManager* GgafDx9God::_pEffectManager = NULL;
//int const CFG_PROPERTY(GAME_BUFFER_WIDTH)  = 1024;
//int const CFG_PROPERTY(GAME_BUFFER_HEIGHT) = 600;
D3DPRESENT_PARAMETERS* GgafDx9God::_d3dparam;

bool GgafDx9God::_is_device_lost_flg = false;
bool GgafDx9God::_adjustGameScreen = false;
HWND GgafDx9God::_pHWnd_adjustScreen = NULL;

int GgafDx9God::_iNumAdapter = 1;

UINT32 GgafDx9God::_vs_v = 0;
UINT32 GgafDx9God::_ps_v = 0;

D3DXMACRO GgafDx9God::_aD3DXMacro_Defines[3] =
{
    { "VS_VERSION", "vs_3_0" },
    { "PS_VERSION", "ps_3_0" },
    { NULL, NULL }
};


IDirect3DTexture9*  GgafDx9God::_pRenderTexture = NULL;   //�e�N�X�`��
//IDirect3DSurface9*  GgafDx9God::_pBackBuffer = NULL;      //�o�b�N�o�b�t�@
IDirect3DSurface9*  GgafDx9God::_pRenderTextureSurface = NULL;     //�T�[�t�F�C�X
IDirect3DSurface9* GgafDx9God::_pRenderTextureZ = NULL;


GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) :
    GgafGod() {
    TRACE("GgafDx9God::GgafDx9God() ");
    GgafDx9God::_pHWndPrimary = prm_pHWndPrimary;
    GgafDx9God::_pHWndSecondary = prm_pHWndSecondary;
    GgafDx9God::_hInstance = prm_hInstance;
    _is_device_lost_flg = false;
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
    GgafRgb rgb = GgafRgb(CFG_PROPERTY(BG_COLOR));
    _color_background = D3DCOLOR_RGBA(rgb._R, rgb._G, rgb._B, 0);
    _color_clear = D3DCOLOR_RGBA(0, 0, 0, 0);
    pSwapChain00 = NULL;//�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[��
    pBackBuffer00 = NULL;//�o�b�N�o�b�t�@1��ʕ�
    pSwapChain01 = NULL;//�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[��
    pBackBuffer01 = NULL;//�o�b�N�o�b�t�@�P��ʕ�


    //[����]
    //�����Ɏg�p����RECT�\���̂̃����o right, bottom �́u�E�����W�v�ƂȂ��Ă��邪�A����͐��m�ł͂Ȃ��B
    //���ۂ̒�`��
    //rect.right = rect.left + ��`��;
    //rect.bottom = rect.top + ��`����;
    //�炵���B
    //����āA�Ⴆ�� (10,10)-(17,17)�̈�́ARECT(10,10,18,18) �Ǝw�肵�Ȃ���΂����Ȃ��炵���B��₱�����B
    //�i���{���̉E�����W�́Aright, bottom �� -1 �̒l�ɂȂ�j

    _rectGameBuffer.left   = 0;
    _rectGameBuffer.top    = 0;
    _rectGameBuffer.right  = _rectGameBuffer.left + CFG_PROPERTY(GAME_BUFFER_WIDTH);
    _rectGameBuffer.bottom = _rectGameBuffer.top  + CFG_PROPERTY(GAME_BUFFER_HEIGHT);

    if (CFG_PROPERTY(SWAP_GAME_VIEW)) {
        _primary = 1;
        _secondary = 0;
    } else {
        _primary = 0;
        _secondary = 1;
    }
    _aRect_HarfGameBuffer[_primary].left   = 0;
    _aRect_HarfGameBuffer[_primary].top    = 0;
    _aRect_HarfGameBuffer[_primary].right  = _aRect_HarfGameBuffer[_primary].left  + CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_primary].bottom = _aRect_HarfGameBuffer[_primary].top + CFG_PROPERTY(GAME_BUFFER_HEIGHT);

    _aRect_HarfGameBuffer[_secondary].left   = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].top    = 0;
    _aRect_HarfGameBuffer[_secondary].right  = _aRect_HarfGameBuffer[_secondary].left + CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].bottom = _aRect_HarfGameBuffer[_secondary].top  + CFG_PROPERTY(GAME_BUFFER_HEIGHT);


    //�\���̈�ݒ�
    if (CFG_PROPERTY(FULL_SCREEN)) {
        //�t���X�N���[�����[�h
        if (CFG_PROPERTY(DUAL_VIEW)) {
            //�t���X�N���[�����[�h�E�Q��ʎg�p
            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����FIX�v�̂P��ʖڃt�����g�o�b�t�@�`��̈�
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����FIX�v�̂Q��ʖڃt�����g�o�b�t�@�`��̈�
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[1].left   = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }
                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH), CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH), CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT));
            } else {
                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����X�g���b�`�v�̂P��ʖڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
                //�u�t���X�N���[�����[�h�E�Q��ʎg�p�E�c����X�g���b�`�v�̂Q��ʖڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
            }
        } else {
            //�t���X�N���[�����[�h�E�P��ʎg�p
            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�t���X�N���[�����[�h�E�P��ʎg�p�E�c����FIX�v�̃t�����g�o�b�t�@�`��̈�
                if (1.0f * CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
            } else {
                //�u�t���X�N���[�����[�h�E�P��ʎg�p�E�c����X�g���b�`�v�̃t�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    } else {
        //�E�B���h�E���[�h
        if (CFG_PROPERTY(DUAL_VIEW)) {
            //�E�B���h�E���[�h�E�Q���g�p
            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����FIX�v�̂P���ڃt�����g�o�b�t�@�`��̈�
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����FIX�v�̂Q���ڃt�����g�o�b�t�@�`��̈�
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[1].left   = (CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }

                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
            } else {
                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����X�g���b�`�v�̂P���ڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT);
                //�u�E�B���h�E���[�h�E�Q���g�p�E�c����X�g���b�`�v�̂Q���ڃt�����g�o�b�t�@�`��̈�
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT);
            }
        } else {
            //�E�B���h�E���[�h�E�P���g�p
            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //�u�E�B���h�E���[�h�E�P���g�p�E�c����FIX�v�̃t�����g�o�b�t�@�`��̈�
                if (1.0f * CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[0].left   = (CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / fix_width; //�k����=�����̔䗦
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
            } else {
                //�u�E�B���h�E���[�h�E�P���g�p�E�c����X�g���b�`�v�̃t�����g�o�b�t�@�`��̈�
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    }
    _TRACE_(" _aRect_Present[0].left     = "<<_aRect_Present[0].left    );
    _TRACE_(" _aRect_Present[0].top      = "<<_aRect_Present[0].top     );
    _TRACE_(" _aRect_Present[0].right    = "<<_aRect_Present[0].right   );
    _TRACE_(" _aRect_Present[0].bottom   = "<<_aRect_Present[0].bottom  );
    _TRACE_(" _aRect_Present[1].left   = "<<_aRect_Present[1].left  );
    _TRACE_(" _aRect_Present[1].top    = "<<_aRect_Present[1].top   );
    _TRACE_(" _aRect_Present[1].right  = "<<_aRect_Present[1].right );
    _TRACE_(" _aRect_Present[1].bottom = "<<_aRect_Present[1].bottom);
}

HRESULT GgafDx9God::init() {
    HRESULT hr;

    //IDirect3D9�R���|�[�l���g�̎擾
    if (!(GgafDx9God::_pID3D9 = Direct3DCreate9(D3D_SDK_VERSION))) {
        throwGgafCriticalException("Direct3DCreate9 �Ɏ��s���܂���");
        return E_FAIL; //���s
    }
    //    //�Q�ƃJ�E���^��]�����₷�B���R�̓f�X�g���N�^�̃f�o�C�X��������Q�ƁB
    //    GgafDx9God::_pID3D9->AddRef();
    //    GgafDx9God::_pID3D9->AddRef();

    //�f�X�v���C���[�h�̎擾
    D3DDISPLAYMODE structD3DDisplayMode; //���ʂ��i�[�����\����
    hr = GgafDx9God::_pID3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &structD3DDisplayMode);
    checkDxException(hr, D3D_OK, "GetAdapterDisplayMode �Ɏ��s���܂���");

    D3DCAPS9 caps___;
    GgafDx9God::_pID3D9->GetDeviceCaps(0, D3DDEVTYPE_HAL, &caps___);
    _iNumAdapter = caps___.NumberOfAdaptersInGroup;   //�g����A�_�v�^�̐��擾
    _TRACE_("_iNumAdapter = "<< _iNumAdapter);

    //�f�o�C�X�p�����[�^�쐬
    _d3dparam = NEW D3DPRESENT_PARAMETERS[2];
    ZeroMemory(&_d3dparam[0], sizeof(D3DPRESENT_PARAMETERS));
    //�o�b�N�o�b�t�@�̐�
    _d3dparam[0].BackBufferCount = 1;
    //�[�x�X�e���V���o�b�t�@
    //_d3dparam[0].EnableAutoDepthStencil = FALSE;
    //_d3dparam[0].AutoDepthStencilFormat = 0;
    _d3dparam[0].EnableAutoDepthStencil = TRUE; //Z �o�b�t�@�̎����쐬
    _d3dparam[0].AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;
    //0�ɂ��Ă���
    _d3dparam[0].Flags = 0;

    if (CFG_PROPERTY(FULL_SCREEN)) {
        //�t���X�N���[����
        _d3dparam[0].BackBufferFormat = D3DFMT_X8R8G8B8;
                                        //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
        _d3dparam[0].Windowed = false; //�t���X�N���[�����[�h��
        _d3dparam[0].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //���t���b�V�����[�g
        _d3dparam[0].PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //�X���b�v�̃^�C�~���O
        if (CFG_PROPERTY(DUAL_VIEW)) {
            _d3dparam[0].SwapEffect = D3DSWAPEFFECT_COPY;
        } else {
            _d3dparam[0].SwapEffect = D3DSWAPEFFECT_DISCARD;
        }
    } else {
        //�E�B���h�E��
        _d3dparam[0].BackBufferFormat = structD3DDisplayMode.Format;
                                      // D3DFMT_UNKNOWN;   //���݂̉�ʃ��[�h�𗘗p
        _d3dparam[0].Windowed = true; //�E�B���h�E���[�h��
        _d3dparam[0].FullScreen_RefreshRateInHz = 0; //���t���b�V�����[�g
        _d3dparam[0].PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //����
        //TODO:Window���[�h�͂������Ȃ̂��H�AD3DPRESENT_INTERVAL_ONE �Ƃ����߂��H
        _d3dparam[0].SwapEffect = D3DSWAPEFFECT_COPY;
    }

    //�A���`�A�C���A�X�ɂł��邩�`�F�b�N
    UINT32 qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;

    //	if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //		D3DADAPTER_DEFAULT,
    //		D3DDEVTYPE_HAL,
    //		D3DFMT_A8R8G8B8,
    //		CFG_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
    //		D3DMULTISAMPLE_2_SAMPLES,
    //		&qualityLevels) ) )
    //	{
    //		if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //			D3DADAPTER_DEFAULT,
    //			D3DDEVTYPE_HAL,
    //			D3DFMT_D24S8,
    //			CFG_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
    //			D3DMULTISAMPLE_2_SAMPLES,
    //			NULL) ) )
    //		{
    //			multiSampleType = D3DMULTISAMPLE_2_SAMPLES;
    //			_TRACE_("MultiSampleType = D3DMULTISAMPLE_2_SAMPLES");
    //		}
    //	}
    //�}���`�T���v���̐�
    _d3dparam[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
    //�}���`�T���v���̕i�����x��
    _d3dparam[0].MultiSampleQuality = 0;//qualityLevels - (qualityLevels > 0 ? 1 : 0);

    //�Q��ʎg�p���̍����C��
    _d3dparam[1] = _d3dparam[0]; //���ʂ��������߃R�s�[
    //Window�n���h�����ʎw��
    _d3dparam[0].hDeviceWindow = _pHWndPrimary;
    _d3dparam[1].hDeviceWindow = _pHWndSecondary;
    //�o�b�N�o�b�t�@�T�C�Y
    if (CFG_PROPERTY(FULL_SCREEN)) {
        if(CFG_PROPERTY(DUAL_VIEW)) {
            //�t���X�N���[�����[�h�E�Q��ʎg�p
            _d3dparam[0].BackBufferWidth  = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
            _d3dparam[0].BackBufferHeight = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
            _d3dparam[1].BackBufferWidth  = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
            _d3dparam[1].BackBufferHeight = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
        } else {
            //�t���X�N���[�����[�h�E�P��ʎg�p
            _d3dparam[0].BackBufferWidth  = CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
            _d3dparam[0].BackBufferHeight = CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            _d3dparam[1].BackBufferWidth  = 0;
            _d3dparam[1].BackBufferHeight = 0;
        }
    } else {
        if(CFG_PROPERTY(DUAL_VIEW)) {
            //�E�B���h�E���[�h�E�Q��ʎg�p
            _d3dparam[0].BackBufferWidth  = CFG_PROPERTY(GAME_BUFFER_WIDTH);
            _d3dparam[0].BackBufferHeight = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
            _d3dparam[1].BackBufferWidth  = 0;
            _d3dparam[1].BackBufferHeight = 0;
        } else {
            //�E�B���h�E���[�h�E�P��ʎg�p
            _d3dparam[0].BackBufferWidth  = CFG_PROPERTY(GAME_BUFFER_WIDTH);
            _d3dparam[0].BackBufferHeight = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
            _d3dparam[1].BackBufferWidth  = 0;
            _d3dparam[1].BackBufferHeight = 0;
        }
    }



    //    //�t���X�N���[���ɏo���邩���ׂ�
    //    if (CFG_PROPERTY(FULL_SCREEN)) {
    //        int cc = GgafDx9God::_pID3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT,
    //                                                          _d3dparam[0].BackBufferFormat);
    //        if (cc) {
    //            D3DDISPLAYMODE adp;
    //            for (int i = 0; i < cc; i++) {
    //                GgafDx9God::_pID3D9->EnumAdapterModes(D3DADAPTER_DEFAULT,
    //                                                      _d3dparam[0].BackBufferFormat, i, &adp);
    //                if (adp.Format == _d3dparam[0].BackBufferFormat && adp.Width
    //                        == (UINT)CFG_PROPERTY(GAME_BUFFER_WIDTH) && adp.Height
    //                        == (UINT)CFG_PROPERTY(GAME_BUFFER_HEIGHT)) {
    //                    //OK
    //                    break;
    //                }
    //                if (cc == i) {
    //                    //�v�������g����𑜓x��������Ȃ�
    //                    throwGgafCriticalException(CFG_PROPERTY(GAME_BUFFER_WIDTH) <<"x"<<CFG_PROPERTY(GAME_BUFFER_HEIGHT) << "�̃t���X�N���[�����[�h�ɂ��鎖���ł��܂���B");
    //                    return E_FAIL;
    //                }
    //            }
    //        } else {
    //            throwGgafCriticalException("GetAdapterModeCount �Ɏ��s���܂���");
    //            return E_FAIL;
    //        }
    //    }


    //default
    UINT AdapterToUse = D3DADAPTER_DEFAULT;
    D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
    // NVIDIA PerfHUD �p begin --------------------------------------------->

//#ifdef MY_DEBUG
//
//#if SHIPPING_VERSION
//    // When building a shipping version, disable PerfHUD (opt-out)
//#else
//    _TRACE_("Look for 'NVIDIA PerfHUD' adapter...");
//    // If it is present, override default settings
//    for (UINT Adapter = 0; Adapter < GgafDx9God::_pID3D9->GetAdapterCount(); Adapter++) {
//        D3DADAPTER_IDENTIFIER9 Identifier;
//        HRESULT Res;
//        Res = GgafDx9God::_pID3D9->GetAdapterIdentifier(Adapter, 0, &Identifier);
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

    if (CFG_PROPERTY(FULL_SCREEN) && CFG_PROPERTY(DUAL_VIEW)) {

        //�f�o�C�X�쐬������ GgafDx9God::_pID3DDevice9 �֐ݒ肷��B
        //�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
        hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                               D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE  ,
                                               _d3dparam, &GgafDx9God::_pID3DDevice9);
        //checkDxException(hr, D3D_OK, "CreateDevice() �Ɏ��s���܂����B");
        if (hr != D3D_OK) {
            _TRACE_("D3DCREATE_PUREDEVICE: "<<GgafDx9CriticalException::getHresultMsg(hr));

            //�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE,
                                                   _d3dparam, &GgafDx9God::_pID3DDevice9);
            if (hr != D3D_OK) {
                _TRACE_("D3DCREATE_SOFTWARE_VERTEXPROCESSING: "<<GgafDx9CriticalException::getHresultMsg(hr));

                //�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
                hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_pHWndPrimary,
                                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE,
                                                       _d3dparam, &GgafDx9God::_pID3DDevice9);
                if (hr != D3D_OK) {
                    _TRACE_("D3DCREATE_SOFTWARE_VERTEXPROCESSING: "<<GgafDx9CriticalException::getHresultMsg(hr));

                    //�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
                    MessageBox(GgafDx9God::_pHWndPrimary, TEXT("MULTI FULLSCRREEN Direct3D�̏������Ɏ��s"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDx9God::init �f�o�C�X�� MULTI FULLSCRREEN REF �ŏ������ł��܂����B");
                }

            } else {
                _TRACE_("GgafDx9God::init �f�o�C�X�� MULTI FULLSCRREEN HAL(soft vp) �ŏ������ł��܂����B");
            }

        } else {
            _TRACE_("GgafDx9God::init �f�o�C�X�� MULTI FULLSCRREEN HAL(pure vp) �ŏ������ł��܂����B");
        }

    } else {
        //�f�o�C�X�쐬������ GgafDx9God::_pID3DDevice9 �֐ݒ肷��B
        //�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
        hr = GgafDx9God::_pID3D9->CreateDevice(AdapterToUse, DeviceType, GgafDx9God::_pHWndPrimary,
                                               D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                               &_d3dparam[0], &GgafDx9God::_pID3DDevice9);

        if (hr != D3D_OK) {
            //�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                   &_d3dparam[0], &GgafDx9God::_pID3DDevice9);
            if (hr != D3D_OK) {
                //�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
                hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_pHWndPrimary,
                                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                       &_d3dparam[0], &GgafDx9God::_pID3DDevice9);
                if (hr != D3D_OK) {
                    //�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
                    MessageBox(GgafDx9God::_pHWndPrimary, TEXT("Direct3D�̏������Ɏ��s"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDx9God::init �f�o�C�X�� REF �ŏ������ł��܂����B");
                }

            } else {
                _TRACE_("GgafDx9God::init �f�o�C�X�� HAL(soft vp) �ŏ������ł��܂����B");
            }

        } else {
            _TRACE_("GgafDx9God::init �f�o�C�X�� HAL(pure vp) �ŏ������ł��܂����B");
        }
    }

    //�s�N�Z���V�F�[�_�[�A���_�V�F�[�_�[�o�[�W�����`�F�b�N
    D3DCAPS9 caps;
    GgafDx9God::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] �f�B�X�v���C �A�_�v�^�����������B
                                       //      D3DADAPTER_DEFAULT �͏��
                                       //      �v���C�}�� �f�B�X�v���C �A�_�v�^
                                       D3DDEVTYPE_HAL, // [in] �f�o�C�X�̎�ށB D3DDEVTYPE�񋓌^�̃����o
                                       &caps); // [out] �f�o�C�X�̔\�͂��i�[�����

    _vs_v = caps.VertexShaderVersion;
    _ps_v = caps.PixelShaderVersion;
    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(_vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(_vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(_ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(_ps_v));
    if (_vs_v < D3DVS_VERSION(2, 0) || _ps_v < D3DPS_VERSION(2, 0)) {
        _TRACE_("�r�f�I�J�[�h�n�[�h�̒��_�V�F�[�_�[�ƃs���N�Z���V�F�[�_�[�́A���Ƀo�[�W���� 2_0 �ȏ�łȂ���΂����܂���B");
        _TRACE_("���g�p�̃r�f�I�J�[�h�ł́A���������삵�Ȃ����ꂪ����܂��B");
    }

    //���̑��K�v�ȏ�����
    _pModelManager = NEW GgafDx9ModelManager("ModelManager");
    _pEffectManager = NEW GgafDx9EffectManager("EffectManager");
    GgafDx9Util::init(); //���[�e�B���e�B����
    GgafDx9Input::init(); //DirectInput����
    GgafDx9Sound::init(); //DirectSound����

//�R�R�ŌĂԂƃ������ᔽ
//    adjustGameScreen(_pHWndPrimary);
//    if (_pHWndSecondary) {
//        adjustGameScreen(_pHWndSecondary);
//    }


//    _adjustGameScreen = true;
    return initDx9Device();

}

HRESULT GgafDx9God::initDx9Device() {
    // �f�t�H���g�̃��C�g
    /*
     ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9) );
     GgafDx9God::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL; //���s���A�F�ƕ��������ł悢
     GgafDx9God::_d3dlight9_default.Direction = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
     GgafDx9God::_d3dlight9_default.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
     GgafDx9God::_d3dlight9_default.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
     //���͕��s���ł͊֌W�Ȃ�
     //GgafDx9God::_d3dlight9_default.Position = D3DXVECTOR3(-1*CFG_PROPERTY(GAME_BUFFER_WIDTH)/2, -1*CFG_PROPERTY(GAME_BUFFER_HEIGHT)/2, -1*CFG_PROPERTY(GAME_BUFFER_HEIGHT)/2);
     //GgafDx9God::_d3dlight9_default.Range = 1000;
     */

    //���C�g�\���̂́A�V�F�[�_�[�̃p�����[�^�ɂȂ鎞�����邽�ߕK�v�B
    D3DXVECTOR3 vecDirection(-1.0f, -1.0f, 1.0f);
    D3DXVec3Normalize(&vecDirection, &vecDirection);
    ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9));
    GgafDx9God::_d3dlight9_default.Direction = vecDirection;
    GgafDx9God::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL;
    GgafDx9God::_d3dlight9_default.Diffuse.a = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.r = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.g = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.b = 1.0f;

    GgafDx9God::_d3dlight9_default.Ambient.a = 1.0f;
    GgafDx9God::_d3dlight9_default.Ambient.r = 0.3f; //�A���r�G���g���C�g��SetRenderState(D3DRS_AMBIENT, 0x00303030)�Őݒ�
    GgafDx9God::_d3dlight9_default.Ambient.g = 0.3f;
    GgafDx9God::_d3dlight9_default.Ambient.b = 0.3f;

    //GgafDx9God::_d3dlight9_default.Range = 1000.0f;


    //���C�g���Z�b�g
    //    GgafDx9God::_pID3DDevice9->SetLight(0, &GgafDx9God::_d3dlight9_default);
    //���C�g�X�C�b�`ON
    //    GgafDx9God::_pID3DDevice9->LightEnable(0, TRUE);
    //GgafDx9God::_pID3DDevice9->LightEnable(0, FALSE);
    //�����_���Ƀ��C�g�̉e���i�A�e�j��L��
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
    //�����_���Ƀ��C�g�̉e���i�A�e�j�𖳌� (�s�N�Z���V�F�[�_�[�ōs�Ȃ����߁j
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
    //�����_���A���E�ɋ��ʂ̃A���r�G���g���C�g��L���ɂ����悤�ɕ`��
    //   GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _dwAmbientBrightness_default);

    // Z�o�b�t�@��L����
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�𖳌���
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    //Z�o�b�t�@�������݉�
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //Z�o�b�t�@�������ݕs��
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    //D3DRENDERSTATE_ZFUNC

    //�X�e���V���e�X�g�̕��@
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //��Ƀe�X�g���p�X
    //��Ɏ��s�������ɃX�e���V���̒l���ǂ��ω������邩
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //�ω��Ȃ�
    //Z�e�X�g�Ŏ��s�����ꍇ�̃X�e���V���l�̕ω�
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //�ω��Ȃ�


    //���i�����v���j���ɃJ�����O �捶����W�n
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //�J�����O���Ȃ�
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // �f�B�U�����O
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
    // �}���`�T���v�����O�A���`�G�C���A�X(�Ƃ����Ă��t���X�N���[�������H)��TODO:�܂���
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

    //�s�N�Z���P�ʂ̃A���t�@�e�X�g��L��
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //���ݒ�̓V�F�[�_�[�ɏ������ɂ����̂ŃR�����g
    // �A���t�@�u�����h�n�m
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //2�i�K�ځA�������e�N�X�`����\��t�����|���S���ƃo�b�N�o�b�t�@�i�����_�[�^�[�Q�b�g�j�Ƃ̍���
    //�F�̎Z�o���@�̐ݒ�
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); //D3DBLENDOP_ADD=�]�����ɓ]���悪���Z
    //�����W��
    //    //��ɏ����摜�̍����@(�V�F�[�_�[�ɉe��)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=���ʂɕ`���B�|���S���̃A���t�@�l�̔Z���ŕ`���B�A���t�@�l�̒l��������΍����قǁA�Z���`���B
    //    //���n�̉摜�̍����@(�V�F�[�_�[�ɉe��)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=��ɕ`���|���S���̃A���t�@�l�̔Z���ɂ���āA���n�̕`��𔖂�����B


    //���_�J���[�𖳌��ɂ���
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, FALSE );
    // GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, TRUE );
    //    //�ʂ̃A���r�G���g���˂́A�}�e���A�����Q�Ƃ���悤�ɐݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃f�t���[�Y���˂́A�}�e���A�����Q�Ƃ���悤�ɐݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃G�~�b�V�u���˂́A�}�e���A�����Q�Ƃ���ݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃X�y�L�������˂́A�}�e���A�����Q�Ƃ���ݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    //���_�����g�p����Ƃ�
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);

    //
    //
    // �A���`�G�C���A�X�̎w��
    //GgafDx9God::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //GgafDx9God::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    //	Type��D3DSAMP_MINFILTER/D3DSAMP_MAGFILTER�i�g��/�k�����j ??D3DTSS_MAGFILTER
    //	Value��D3DTEXTUREFILTERTYPE�񋓌^���w�肷��
    //	D3DTEXF_POINT�@�@�@�@�F�t�B���^�������Ȃ��B�����`��ł���
    //	D3DTEXF_LINEAR�@�@�@�F���j�A�t�B���^�i���`�⊮�j
    //	D3DTEXF_ANISOTROPIC�@�F�ٕ����t�B���^�B�n�\�ʂȂǂ́A�g��k��������O�Ɖ��ňقȂ�ꍇ�Ɏg��
    //	D3DTEXF_PYRAMIDALQUAD�F�e���g�t�B���^�B���j�A�t�B���^�Ƃ��܂�ς��Ȃ��炵��
    //	D3DTEXF_GAUSSIANQUAD �F�K�E�V�A���t�B���^�B�܂��̖����ڂ����t�B���^
    //	���w�肷��B

    //2009/3/4 SetSamplerState�̈Ӗ��������뗝������B
    //SetSamplerState�̓e�N�X�`������ǂ��T���v�����O�i�ǂݎ�邩�j���邩�̐ݒ�B
    //������A���`�G�C���A�X���Ă����Ă��A�e�N�X�`�������A���`�G�C���A�X��������܂���B
    //����s�N�Z���V�F�[�_�[�őS�������̂ŁA���̂�����̐ݒ�́A�S������Ȃ��Ȃ�͂����B


    //�A���`�G�C���A�X�ɂ�����郌���_�����O�X�e�[�g
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);

    //�F�������S�ăV�F�[�_�[�ŏ����ɂȂ����̂ŃR�����g
    //SetTextureStageState�͔p�~�H
    //  1�i�K�ڃ|���S���ƃe�N�X�`���̍������@�ݒ�
    //    //�e�N�X�`���[�̐F�ƁA���_�J���[��DIFFUSE�F����Z����悤�ɐݒ�
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    //    //�e�N�X�`���[�̃��ƁA���_�J���[�̃�����Z����悤�ɐݒ�
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


    //GgafDx9Camera�ֈړ�����
    // VIEW�ϊ��i�J�����ʒu�j�ݒ�
    //D3DXMATRIX _matView; // �r���[�ϊ��s��
    //    DELETE_POSSIBLE_NULL(_pVecCamFromPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamLookatPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamUp);

    //GgafDx9Camera�ֈړ�����
    // �ˉe�ϊ��i�R�c�����ʁj
    //D3DXMATRIX _matProj; // �ˉe�ϊ��s��
    //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_matProj);
    HRESULT hr;
    //�o�b�N�o�b�t�@���E�B���h�EBG�F�ŃN���A
    //�����ł�RenderTarget�͂܂��A�ʏ�̃o�b�N�o�b�t�@�ł���
    hr = GgafDx9God::_pID3DDevice9->Clear(0, // �N���A�����`�̈�̐�
                                          NULL, // ��`�̈�
                                          D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                          //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                          _color_background, //�E�B���h�E�w�i�F�Ƃ��낦��
                                          1.0f, // Z�o�b�t�@�̃N���A�l
                                          0 // �X�e���V���o�b�t�@�̃N���A�l
            );
    checkDxException(hr, D3D_OK, "Clear���s");
    if (CFG_PROPERTY(FULL_SCREEN)) {


        //�`���ƂȂ�e�N�X�`����ʓr�쐬�i�o�b�N�o�b�t�@�I�Ȏg�p���s���j
        hr = GgafDx9God::_pID3DDevice9->CreateTexture(
                                                CFG_PROPERTY(GAME_BUFFER_WIDTH),
                                                CFG_PROPERTY(GAME_BUFFER_HEIGHT),
                                                 1, //MipLevel Mip����
                                                 D3DUSAGE_RENDERTARGET,
                                                 _d3dparam[0].BackBufferFormat,
                                                 D3DPOOL_DEFAULT,
                                                 &_pRenderTexture,
                                                 NULL);
        checkDxException(hr, D3D_OK, "�o�b�N�o�b�t�@�E�e�N�X�`���쐬���s");
        //RenderTarget(�`���)���e�N�X�`���֐؂�ւ�
        hr = _pRenderTexture->GetSurfaceLevel(0, &_pRenderTextureSurface);
        checkDxException(hr, D3D_OK, "�e�N�X�`���̃T�[�t�F�C�X�|�C���^�擾���s");
        hr = GgafDx9God::_pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
        checkDxException(hr, D3D_OK, "SetRenderTarget �e�N�X�`���̃T�[�t�F�C�X���s");
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // �N���A�����`�̈�̐�
                                              NULL, // ��`�̈�
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              _color_clear, //�w�i���ɃN���A
                                              1.0f, // Z�o�b�t�@�̃N���A�l
                                              0 // �X�e���V���o�b�t�@�̃N���A�l
                );
        checkDxException(hr, D3D_OK, "Clear���s");

        //�e�N�X�`���ɕ`�悷��ۂ̐[�x�o�b�t�@�p�T�[�t�F�C�X��ʓr�쐬
        hr = GgafDx9God::_pID3DDevice9->CreateDepthStencilSurface(
                CFG_PROPERTY(GAME_BUFFER_WIDTH),
                CFG_PROPERTY(GAME_BUFFER_HEIGHT),
                _d3dparam[0].AutoDepthStencilFormat,   //D3DFORMAT   Format,
                _d3dparam[0].MultiSampleType,          //D3DMULTISAMPLE_TYPE     MultiSample,
                _d3dparam[0].MultiSampleQuality,       //DWORD   MultisampleQuality,
                TRUE,                                  //BOOL    Discard, SetDepthStencileSurface�֐��Ő[�x�o�b�t�@��ύX�������Ƀo�b�t�@��j�����邩�ǂ���
                &_pRenderTextureZ,                     //IDirect3DSurface9**     ppSurface,
                NULL                                   //HANDLE*     pHandle ���ݖ��g�p
        );
        //�[�x�o�b�t�@�쐬���������́A�[�x�o�b�t�@�p�T�[�t�F�C�X����L�ɕύX
        checkDxException(hr, D3D_OK, "�o�b�N�o�b�t�@�E�e�N�X�`����Z�o�b�t�@�쐬���s");
        hr =  GgafDx9God::_pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
        checkDxException(hr, D3D_OK, "SetDepthStencilSurface�o�b�N�o�b�t�@�E�e�N�X�`����Z�o�b�t�@���s");
        //�N���A

        checkDxException(hr, D3D_OK, "CFG_PROPERTY(FULL_SCREEN)��������GgafDx9God::_pID3DDevice9->Clear() �Ɏ��s���܂����B");

//            //�A�_�v�^�Ɋ֘A�t����ꂽ�X���b�v�`�F�[�����擾���ăo�b�N�o�b�t�@���擾
        hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 0, &pSwapChain00 );
        checkDxException(hr, D3D_OK, "0GetSwapChain() �Ɏ��s���܂����B");
        hr = pSwapChain00->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer00 );
        checkDxException(hr, D3D_OK, "0GetBackBuffer() �Ɏ��s���܂����B");

        if (CFG_PROPERTY(DUAL_VIEW)) {


    //
            hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 1, &pSwapChain01 );
            checkDxException(hr, D3D_OK, "1GetSwapChain() �Ɏ��s���܂����B");
            hr = pSwapChain01->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer01 );
            checkDxException(hr, D3D_OK, "1GetBackBuffer() �Ɏ��s���܂����B");
        }
    }

    return S_OK;
}

// �J�����ƑΛ������]�s����擾
// �r���{�[�h��VIEW�ϊ��s����擾
D3DXMATRIX GgafDx9God::getInvRotateMat() {
    D3DXMATRIX Inv;
    //   D3DXMatrixIdentity(&Inv);
    //   D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
    //   D3DXMatrixInverse(&Inv, NULL, &Inv);

    return Inv;
}

void GgafDx9God::makeUniversalMaterialize() {
    TRACE("GgafDx9God::materialize() start");
    HRESULT hr;
    if (_is_device_lost_flg) {
        //����f�o�C�X���X�g�����B�f�o�C�X���\�[�X�̉�������A���������݂�B
        if (GgafDx9God::_pID3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            //�H��x�~
            GgafFactory::beginRest();
            ___EndSynchronized; // <----- �r���I��
            for (int i = 0; GgafFactory::isResting() == false; i++) {
                Sleep(60); //�H�ꂪ���������܂ő҂�
                if (i > 3000) {
                    _TRACE_("GgafDx9God::makeUniversalMaterialize() 3���ҋ@���܂������A�H�ꂩ�甽��������܂���B����break���܂��B�v����");
                    break;
                }
            }
            //            while (GgafFactory::isResting() == false) { //�H�ꂪ���������܂ő҂�
            //                Sleep(10);
            //            }
            ___BeginSynchronized; // ----->�r���J�n
            _TRACE_("����f�o�C�X���X�g�����BBegin");
            //�G�t�F�N�g�A�f�o�C�X���X�g����
            GgafDx9God::_pEffectManager->onDeviceLostAll();
            //���f�����
            GgafDx9God::_pModelManager->onDeviceLostAll();
            //�S�m�[�h�ɉ�����Ȃ����C�x���g����
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_ON_DEVICE_LOST, this);

            //�f�o�C�X���Z�b�g�����݂�
            hr = GgafDx9God::_pID3DDevice9->Reset(&(_d3dparam[0]));
            checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() �f�o�C�X���X�g��̃��Z�b�g[0]�Ɏ��s���܂����B");
            if (CFG_PROPERTY(DUAL_VIEW)) {
                for (int i = 1; i < _iNumAdapter; i++) {
                    hr = GgafDx9God::_pID3DDevice9->Reset(&(_d3dparam[i]));
                    checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() �f�o�C�X���X�g��̃��Z�b�g[1]�Ɏ��s���܂����B");
                }
            }

            //�f�o�C�X�Đݒ�
            GgafDx9God::initDx9Device();
            //�G�t�F�N�g���Z�b�g
            GgafDx9God::_pEffectManager->restoreAll();
            //���f���Đݒ�
            GgafDx9God::_pModelManager->restoreAll();
            //�S�m�[�h�ɍĐݒ肵�Ȃ����C�x���g����
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_DEVICE_LOST_RESTORE, this);
            //�O��`�惂�f�����𖳌��ɂ���
            GgafDx9God::_pModelManager->_pModelLastDraw = NULL;
            _is_device_lost_flg = false;

            //�H��ĊJ
            GgafFactory::finishRest();
            _TRACE_("����f�o�C�X���X�g�����BEnd");
        }
    } else {
        //�ʏ펞�i�f�o�C�X���X�g�ł͂Ȃ��j�̏���

        //�o�b�t�@�N���A
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // �N���A�����`�̈�̐�
                                              NULL, // ��`�̈�
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              _color_clear, //�w�i���ɃN���A //D3DCOLOR_XRGB( 0, 0, 0 ), //�w�i���ɃN���A
                                              1.0f, // Z�o�b�t�@�̃N���A�l
                                              0 // �X�e���V���o�b�t�@�̃N���A�l
                );
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() �Ɏ��s���܂����B");

        //�`�掖�O����
        hr = GgafDx9God::_pID3DDevice9->BeginScene();
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->BeginScene() �Ɏ��s���܂����B");
        //�S�ċ���I�i�`��j
#ifdef MY_DEBUG
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
#endif
        GgafGod::makeUniversalMaterialize(); //�X�[�p�[��materialize���s
        //�`�掖�㏈��
        hr = GgafDx9God::_pID3DDevice9->EndScene();
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->EndScene() �Ɏ��s���܂����B");

    }
    TRACE("GgafDx9God::makeUniversalMaterialize() end");
}

void GgafDx9God::presentUniversalVisualize() {
    if (_is_device_lost_flg != true) {
        //�o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɓ]��
        //if (GgafDx9God::_pID3DDevice9->Present(NULL,&_aRect_Present[0],NULL,NULL) == D3DERR_DEVICELOST) {
        //        static D3DRASTER_STATUS rs;
        //        while (SUCCEEDED(GgafDx9God::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
        //            if(rs.InVBlank) {
        //                break; //�����A�����Ԃł͂Ȃ�
        //            } else {
        //                Sleep(1);
        //            }
        //        }

        if (_adjustGameScreen && _pHWnd_adjustScreen) {
            adjustGameScreen(_pHWndPrimary);
            adjustGameScreen(_pHWndSecondary);
        }

        HRESULT hr;
//        hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
        if (CFG_PROPERTY(FULL_SCREEN)) {
            if (CFG_PROPERTY(DUAL_VIEW)) {
    //
                //��ʂO�o�b�N�o�b�t�@����ʂP�o�b�N�o�b�t�@�փR�s�[����
                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,  &_aRect_HarfGameBuffer[0],
                        pBackBuffer00,           &_aRect_Present[0],
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1��ʖ� StretchRect() �Ɏ��s���܂����B\n_pRenderTextureSurface="<<_pRenderTextureSurface<<"/pBackBuffer00="<<pBackBuffer00);

                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,  &_aRect_HarfGameBuffer[1],
                        pBackBuffer01,           &_aRect_Present[1],
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "StretchRect() �Ɏ��s���܂����B");

                hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);

    //            //�v���C�}���o�b�N�o�b�t�@�̉E�������Z�J���_���o�b�N�o�b�t�@�փR�s�[
                //hr = GgafDx9God::_pID3DDevice9->UpdateSurface( pBackBuffer00, &_aRect_HarfGameBuffer[1], pBackBuffer01, _pPoint);
                //checkDxException(hr, D3D_OK, "UpdateSurface() �Ɏ��s���܂����B");
    //            //�R�s�[�t���b�v
//                hr = pSwapChain00->Present(NULL, NULL, NULL, NULL,0);
//    //            hr = pSwapChain00->Present(&_aRect_HarfGameBuffer[0], NULL, NULL, NULL,0);
//                checkDxException(hr, D3D_OK, "0Present() �Ɏ��s���܂����B");
//                hr = pSwapChain01->Present(NULL, NULL, NULL, NULL,0);
//                checkDxException(hr, D3D_OK, "1Present() �Ɏ��s���܂����B");
    ////            //�o�b�N�o�b�t�@��Z�o�b�t�@���擾����
    ////            if(FAILED(m_pd3dDevice->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&m_pBackBuffer))){
    ////            }
    ////            if(FAILED(m_pd3dDevice->GetDepthStencilSurface(&m_pZBuffer))){
    ////            }

            } else {
                //�P��ʎg�p�E�t���X�N���[�����[�h
//                LPDIRECT3DSWAPCHAIN9 pSwapChain00 = NULL;//�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[��
//                LPDIRECT3DSURFACE9 pBackBuffer00 = NULL;//�o�b�N�o�b�t�@1��ʕ�
                //�t���X�N���[��
//                hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 0, &pSwapChain00 );
//                checkDxException(hr, D3D_OK, "0GetSwapChain() �Ɏ��s���܂����B");
//                hr = pSwapChain00->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer00 );
//                checkDxException(hr, D3D_OK, "FULL 1gamen GetBackBuffer() �Ɏ��s���܂����B");

                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,
                        &_rectGameBuffer,
                        pBackBuffer00,
                        &_aRect_Present[0],
                        D3DTEXF_NONE
                        );
                checkDxException(hr, D3D_OK, "FULL 1gamen StretchRect() �Ɏ��s���܂����B");

                hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);

//                //�R�s�[�t���b�v
//                hr = pSwapChain00->Present(NULL, NULL, NULL, NULL,0);
//                checkDxException(hr, D3D_OK, "FULL 1gamen Present() �Ɏ��s���܂����B");


//                RELEASE_SAFETY(pBackBuffer00);
//                RELEASE_SAFETY(pSwapChain00);

            }
        } else {
            if (CFG_PROPERTY(DUAL_VIEW)) {
                //�Q��ʎg�p�E�E�B���h�E���[�h
                if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //�c����Œ胂�[�h
                    hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfGameBuffer[0], &_aRect_Present[0], NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfGameBuffer[1], &_aRect_Present[1], _pHWndSecondary, NULL);
                    }
                } else {
                    //�c���X�g���b�`���[�h
                    hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfGameBuffer[0], NULL, NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfGameBuffer[1], NULL, _pHWndSecondary, NULL);
                    }
                }
            } else {
                //�P��ʎg�p�E�E�B���h�E���[�h
                if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //�c����Œ胂�[�h
                    hr = GgafDx9God::_pID3DDevice9->Present(NULL, &_aRect_Present[0], NULL, NULL);
                } else {
                    //�c���X�g���b�`���[�h
                    hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
                }
            }
        }
        if (hr == D3DERR_DEVICELOST) {
            //�o�n�ّf�I���l�I
            _TRACE_("�ʏ�f�o�C�X���X�g�IPresent()");
            _is_device_lost_flg = true;
        } else if (hr == D3DERR_DRIVERINTERNALERROR) {
            //Present�ُ펞�A���ʂ�������Ȃ����f�o�C�X���X�g�Ɠ������������݂�B
            _TRACE_("Present() == D3DERR_DRIVERINTERNALERROR!! Reset()�����݂܂��B�i�ʖڂ�������܂���j");
            //�H��x�~
            GgafFactory::beginRest();
            ___EndSynchronized; // <----- �r���I��
            for (int i = 0; GgafFactory::isResting() == false; i++) {
                Sleep(60); //�H�ꂪ���������܂ő҂�
                if (i > 1000) {
                    _TRACE_("GgafDx9God::presentUniversalVisualize() 1���ҋ@���܂������A�H�ꂩ�甽��������܂���Bbreak���܂��B�v����");
                }
            }
            ___BeginSynchronized; // ----->�r���J�n
            _TRACE_("D3DERR_DRIVERINTERNALERROR�I ����Begin");
            //�G�t�F�N�g�A�f�o�C�X���X�g����
            GgafDx9God::_pEffectManager->onDeviceLostAll();
            //���f�����
            GgafDx9God::_pModelManager->onDeviceLostAll();
            //�S�m�[�h�ɉ�����Ȃ����C�x���g����
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_ON_DEVICE_LOST, this);
            //�f�o�C�X���Z�b�g�����݂�
            hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_d3dparam[0]));
            checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() D3DERR_DRIVERINTERNALERROR �̂��� Reset([0]) �������܂����A�ʖڂł����B");
            if (CFG_PROPERTY(DUAL_VIEW)) {
                for (int i = 1; i < _iNumAdapter; i++) {
                    hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_d3dparam[i]));
                    checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() D3DERR_DRIVERINTERNALERROR �̂��� Reset([1]) �������܂����A�ʖڂł����B");
                }
            }
            //�f�o�C�X�Đݒ�
            GgafDx9God::initDx9Device();
            //�G�t�F�N�g���Z�b�g
            GgafDx9God::_pEffectManager->restoreAll();
            //���f���Đݒ�
            GgafDx9God::_pModelManager->restoreAll();
            //�S�m�[�h�ɍĐݒ肵�Ȃ����C�x���g����
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_DEVICE_LOST_RESTORE, this);
            //�O��`�惂�f�����𖳌��ɂ���
            GgafDx9God::_pModelManager->_pModelLastDraw = NULL;

            //�H��ĊJ
            GgafFactory::finishRest();
            _TRACE_("D3DERR_DRIVERINTERNALERROR�I ����End");
        }
    }
}

void GgafDx9God::clean() {
    if (!_was_cleaned) {
        _TRACE_("GgafDx9God::clean() begin");

        for( int i=0; i<8; ++i ) { GgafDx9God::_pID3DDevice9->SetTexture( i, NULL ); }
        for( int i=0; i<8; ++i ) { GgafDx9God::_pID3DDevice9->SetStreamSource( i, NULL, 0, 0 ); }
        GgafDx9God::_pID3DDevice9->SetIndices( NULL );
        GgafDx9God::_pID3DDevice9->SetPixelShader( NULL );
        GgafDx9God::_pID3DDevice9->SetVertexShader( NULL );
        GgafDx9God::_pID3DDevice9->SetVertexDeclaration( NULL );

        GgafGod::clean();

        CmRandomNumberGenerator::getInstance()->release();
        //�ێ����f�����
        DELETE_IMPOSSIBLE_NULL(_pModelManager);
        DELETE_IMPOSSIBLE_NULL(_pEffectManager);

        _TRACE_("GgafDx9God::clean() end");
    }
}

void GgafDx9God::adjustGameScreen(HWND prm_pHWnd) {
     RECT rect;
    if (prm_pHWnd && !CFG_PROPERTY(FULL_SCREEN) && CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
        HRESULT hr;
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // �N���A�����`�̈�̐�
                                              NULL, // ��`�̈�
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              _color_background, //�w�i���ɃN���A //D3DCOLOR_XRGB( 0, 0, 0 ), //�w�i���ɃN���A
                                              1.0f, // Z�o�b�t�@�̃N���A�l
                                              0 // �X�e���V���o�b�t�@�̃N���A�l
                );
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() �Ɏ��s���܂����B");
        if (::GetClientRect(prm_pHWnd, &rect)) {
            LONG width = rect.right;
            LONG height = rect.bottom;
            LONG fix_width, fix_height;
            if (CFG_PROPERTY(DUAL_VIEW)) {
                fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
                fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
            } else {
                fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH);
                fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
            }

            if (1.0f * width / height > 1.0f * fix_width / fix_height) {
                //��艡���ɂȂ��Ă��܂��Ă���
                double rate = 1.0 * height / fix_height; //�k����=�c���̔䗦
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1], width, height);
                }


            } else {
                //���c���ɂȂ��Ă��܂��Ă���
                double rate = 1.0 * width / fix_width; //�k����=�����̔䗦
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left = 0;
                    _aRect_Present[0].top = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left = 0;
                    _aRect_Present[1].top = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1], width, height);
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
    GgafDx9God::_pID3DDevice9->GetViewport(&(P_CAM->_viewport));
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
}

void GgafDx9God::positionPresentRect(int prm_pos, RECT& prm_rectPresent, int prm_screen_width, int prm_screen_height) {
//789
//456
//123
    if (prm_pos == 5) {
        return;
    }

    if (prm_pos == 7 || prm_pos == 8 || prm_pos == 9) {
        prm_rectPresent.bottom = prm_rectPresent.bottom - prm_rectPresent.top;
        prm_rectPresent.top = 0;
    } else if (prm_pos == 1 || prm_pos == 2 || prm_pos == 3) {
        prm_rectPresent.top = prm_screen_height - (prm_rectPresent.bottom - prm_rectPresent.top);
        prm_rectPresent.bottom = prm_screen_height;
    }

    if (prm_pos == 7 || prm_pos == 4 || prm_pos == 1) {
        prm_rectPresent.right = prm_rectPresent.right - prm_rectPresent.left;
        prm_rectPresent.left = 0;
    } else if (prm_pos == 9 || prm_pos == 6 || prm_pos == 3) {
        prm_rectPresent.left = prm_screen_width - (prm_rectPresent.right - prm_rectPresent.left);
        prm_rectPresent.right = prm_screen_width;
    }
}
//void GgafDx9God::adjustGameScreen() {
//     RECT rect;
//    if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
//
//        D3DVIEWPORT9 vClient;
//        vClient.MinZ = 0.0f;
//        vClient.MaxZ = 1.0f;
//        vClient.X = (DWORD)0;
//        vClient.Y = (DWORD)0;
//        vClient.Width = (DWORD)(CFG_PROPERTY(GAME_BUFFER_WIDTH));
//        vClient.Height = (DWORD)(CFG_PROPERTY(GAME_BUFFER_HEIGHT));
//        _pID3DDevice9->SetViewport(&vClient);
//        HRESULT hr;
//        hr = GgafDx9God::_pID3DDevice9->Clear(0, // �N���A�����`�̈�̐�
//                                              NULL, // ��`�̈�
//                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
//                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
//                                              _color_background, //�w�i���ɃN���A //D3DCOLOR_XRGB( 0, 0, 0 ), //�w�i���ɃN���A
//                                              1.0f, // Z�o�b�t�@�̃N���A�l
//                                              0 // �X�e���V���o�b�t�@�̃N���A�l
//                );
//        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() �Ɏ��s���܂����B");
//
//
//        if (::GetClientRect(_pHWndPrimary, &rect)) {
//            D3DVIEWPORT9 vp;    //�r���[�|�[�g
//            vp.MinZ = 0.0f;
//            vp.MaxZ = 1.0f;
//            double aspect_client = 1.0 * rect.right / rect.bottom;
//            double aspect_buffer = 1.0 * CFG_PROPERTY(GAME_BUFFER_WIDTH) / CFG_PROPERTY(GAME_BUFFER_HEIGHT);
////            _TRACE_("aspect_client = "<<aspect_client<<" aspect_buffer="<<aspect_buffer);
//            if (aspect_client > aspect_buffer) {
//                //��艡���ɂȂ��Ă��܂��Ă���
//                double rate = (1.0 * CFG_PROPERTY(GAME_BUFFER_WIDTH) / CFG_PROPERTY(GAME_BUFFER_HEIGHT) / (1.0 *rect.right / rect.bottom));
//                vp.X = (DWORD)((CFG_PROPERTY(GAME_BUFFER_WIDTH) / 2.0) - (CFG_PROPERTY(GAME_BUFFER_WIDTH) * rate / 2.0)) ;
//                vp.Y = (DWORD)0;
//                vp.Width = (DWORD)(CFG_PROPERTY(GAME_BUFFER_WIDTH) * rate);
//                vp.Height = (DWORD)(CFG_PROPERTY(GAME_BUFFER_HEIGHT));
//            } else {
//                //���c���ɂȂ��Ă��܂��Ă���
//                double rate = (1.0 * CFG_PROPERTY(GAME_BUFFER_HEIGHT) / CFG_PROPERTY(GAME_BUFFER_WIDTH) / (1.0 *rect.bottom / rect.right));
//                vp.X = (DWORD)0;
//                vp.Y = (DWORD)((CFG_PROPERTY(GAME_BUFFER_HEIGHT) / 2.0) - (CFG_PROPERTY(GAME_BUFFER_HEIGHT) * rate / 2.0)) ;;
//                vp.Width = (DWORD)(CFG_PROPERTY(GAME_BUFFER_WIDTH));
//                vp.Height = (DWORD)(CFG_PROPERTY(GAME_BUFFER_HEIGHT) * rate);
//
//            }
////            _TRACE_("new vp="<<vp.X<<","<<vp.Y<<","<<vp.Width<<","<<vp.Height);
//            _pID3DDevice9->SetViewport(&vp);
//            _adjustGameScreen = false;
//        }
//    } else {
//        if (::GetClientRect(_pHWndPrimary, &rect)) {
//            _aRect_Present[0].top = rect.top;
//            _aRect_Present[0].left = rect.left;
//            _aRect_Present[0].right = rect.right;
//            _aRect_Present[0].bottom = rect.bottom;
//            _adjustGameScreen = false;
//        }
//    }
//}

GgafDx9God::~GgafDx9God() {

    clean();
    _was_cleaned = true;

    //DirectSound���
    GgafDx9Sound::release();
    //DirectInput���
    GgafDx9Input::release();
    _TRACE_("_pID3DDevice9 ��������[");
    Sleep(60);
    RELEASE_SAFETY(pBackBuffer00);
    RELEASE_SAFETY(pBackBuffer01);
    RELEASE_SAFETY(pSwapChain00);
    RELEASE_SAFETY(pSwapChain01);
    DELETEARR_IMPOSSIBLE_NULL(_d3dparam);
    RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9); //�{���͂��ꂪ�K�v
    RELEASE_IMPOSSIBLE_NULL(_pID3D9);
//    D3DCREATE_HARDWARE_VERTEXPROCESSING �Ńt���X�N���[���ŏI�����A�܂�Ƀu���[�X�N���[���ɂȂ�B
//    �J���}�V���́AVISTA, GeForce go 7600 �iHP DV9200) �ŋN����B
//    �������A���̃}�V���ł͋N��Ȃ����͊m�F�o�����B
//    �r�f�I�J�[�h�h���C�o�̂����Ȃ̂��ADV9200�ŗL�̖��Ȃ̂��H�I
//    �Ƃ������Ƃɂ��Ă������B�u���[�X�N���[���ɂȂ������A��ϐ\����Ȃ��B
//    ���Ȃ�̎��Ԃ��g���Ē������������ǌ����s���B�E�E�������₾��߂ā`


}



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

