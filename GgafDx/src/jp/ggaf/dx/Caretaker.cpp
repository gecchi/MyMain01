#include "jp/ggaf/dx/Caretaker.h"

#include <algorithm>
#include "jp/ggaf/dx/actor/camera/Camera.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/manager/CurveSourceManager.h"
#include "jp/ggaf/dx/manager/CurveManufactureManager.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/util/Input.h"

using namespace GgafDx;

#define returnWhenFailed(HR, OKVAL, X) { \
    if (HR != OKVAL) { \
        std::stringstream ss; \
        ss << X; \
        MessageBox(pCARETAKER->_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST); \
        return E_FAIL; \
    } \
}

//TODO:�R�����g�Ƃ���������B��������B

//�E�C���h�E��(NUMBER_OF_SCREENS_USED = 3)
//SCREEN01_DISPLAY_NO = 1   ����
//SCREEN02_DISPLAY_NO = 4 ����
//TERTIARY_SCREEN_DISPLAY_NO = 3  ����
// �L���ȃA�_�v�^�� = 5 (5��ʌq�����Ă�)
// HWND�z�� = 3
//                  ��  ��  ��
// HWND �Y��        0   1   2
// HWND             OK  OK  OK
// �A�_�v�^�ԍ��F0
// �A�_�v�^���v���C�}���ԍ��F0
//

//�t���X�N���[����(NUMBER_OF_SCREENS_USED = 1 )
//SCREEN01_DISPLAY_NO   = 1 �̗p
//SCREEN02_DISPLAY_NO = 4 ����
//TERTIARY_SCREEN_DISPLAY_NO  = 3 ����
//�L���ȃA�_�v�^�� = 5
//HWND�z�� = 5
//                        ������������������������������
//                        ��  ����������  ����  ����  ��
//                        ������������������������������
//HWND �Y��                  0    1      2     3     4
//HWND                     null   OK    null  null  null
//�A�_�v�^�ԍ�               0    1      2     3     4
//�A�_�v�^���v���C�}���ԍ�  -1    0     -1    -1    -1

//�t���X�N���[����(NUMBER_OF_SCREENS_USED = 3 )
//SCREEN01_DISPLAY_NO   = 1 �̗p
//SCREEN02_DISPLAY_NO = 4 �̗p
//TERTIARY_SCREEN_DISPLAY_NO  = 3 �̗p
//�L���ȃA�_�v�^�� = 5
//HWND�z�� = 5
//                       ������������������������������
//�����h��               ������������������������������
//                       ������������������������������
//HWND �Y��                 0     1     2     3     4
//HWND                     OK    OK    OK    OK    OK
//�A�_�v�^�ԍ�              0     1     2     3     4
//�A�_�v�^���v���C�}���ԍ� -1     0    -1     2     1

Caretaker::Caretaker() : GgafCore::Caretaker() {
    _pID3D9 = nullptr;
    _pID3DDevice9 = nullptr;
    _d3dfillmode = D3DFILL_SOLID;

    _is_device_lost_flg = false;
    _adjustGameWindow = false;

    _pHWndPrimary = nullptr;
    //�R�s�[
    for (int pry = 0; pry < MAX_SCREENS; pry++) {
        _screen_display_no[pry] = CONFIG::SCREEN_DISPLAY_NO[pry];
    }
    _primary_screen_adpter_no = 0;
    _hInstance = GetModuleHandle(0);
    _vs_v = 0;
    _ps_v = 0;
    GgafCore::CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
    GgafCore::Rgb rgb_border = GgafCore::Rgb(CONFIG::BORDER_COLOR);
    _color_border = D3DCOLOR_RGBA(rgb_border._red, rgb_border._green, rgb_border._blue, 0);
    GgafCore::Rgb rgb_bg = GgafCore::Rgb(CONFIG::BG_COLOR);
    _color_clear = D3DCOLOR_RGBA(rgb_bg._red, rgb_bg._green, rgb_bg._blue, 0);
    _pRenderTextureSurface = nullptr;
    _pRenderTextureZ = nullptr;
    _num_adapter = 1;
    _num_window = 1;
    _paAvailableAdapter = nullptr;
    _paAdapterRezos = nullptr;

    _can_wddm = true;//�Ƃ肠����
    _papSwapChain = nullptr;
    _papBackBuffer = nullptr;
    _paWindowNoToScreenPry = nullptr;
    _paPresetPrm = nullptr;
    _paDisplayMode = nullptr;
    _paHWnd = nullptr;

    _pTextureManager = nullptr;
    _pModelManager = nullptr;
    _pEffectManager = nullptr;

    //���C�g�\���̂́A�V�F�[�_�[�̃p�����[�^�ɂȂ鎞�����邽�ߕK�v�B
    D3DXVECTOR3 vecDirection(-1.0f, -1.0f, 1.0f);
    D3DXVec3Normalize(&vecDirection, &vecDirection); //���K��
    ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9));
    _d3dlight9_default.Direction = vecDirection;
    _d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL;
    _d3dlight9_default.Diffuse.a = 1.0f;
    _d3dlight9_default.Diffuse.r = 1.0f;
    _d3dlight9_default.Diffuse.g = 1.0f;
    _d3dlight9_default.Diffuse.b = 1.0f;
    _d3dlight9_default.Ambient.a = 1.0f;
    _d3dlight9_default.Ambient.r = 0.2f;
    _d3dlight9_default.Ambient.g = 0.2f;
    _d3dlight9_default.Ambient.b = 0.2f;

    //_d3dlight9_default.Range = 1000.0f

    _pCurveSrcManager = nullptr;
    _pCurveManufManager = nullptr;
}

void Caretaker::createWindow(WNDPROC prm_WndProc,
                             const char* prm_title) {
    //�E�B���h�E��`���쐬
    WNDCLASSEX wcex1;
    ZeroMemory(&wcex1, sizeof(WNDCLASSEX));
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex1.lpfnWndProc = (WNDPROC)prm_WndProc;
    wcex1.hInstance = _hInstance;
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.lpszClassName = "Gecchi Game App Framework";
    createWindow(wcex1, prm_title, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
}

void Caretaker::createWindow(WNDCLASSEX& prm_wndclass,
                             const char* prm_title   ,
                             DWORD       prm_dwStyle ) {
    //2011/09/18 WDDM ���g�p�ł���Ȃ�g�p����悤�ɕύX�B
    // �}���`���j�^�t���X�N���[�����̃f�o�C�X���X�g���̕������A
    // XP�ł͂��܂������̂�Vista�ł͂��܂������Ȃ��������邱�Ƃ����o�B
    // IDirect3D9Ex �̑��݂��C�ɂȂ�A�������Ɏ������B
    // WDDM�܂� IDirect3D9Ex or XPDM �܂� IDirect3D9 �̑I�����s���B
    // IDirect3D9Ex ���擾�� Direct3DCreate9Ex() ���g�p���A
    // �߂�l�̌��ʂŔ��肷��Ηǂ��ƈ��Ղɍl���Ă������A
    // IDirect3D9Ex �̎��Ԃ��AVista �ȍ~ �� d3d9.dll �ɂ̂ݑ��݂���炵���A
    // Direct3DCreate9Ex() �֐��̃R�[�h�����������_�ŁAXP�̏ꍇ d3d9.dll ���[�h����
    // �u�G���g���|�C���g������܂���v�Ƃ������G���[�ɂȂ��Ă��܂����s����ł��Ȃ��B
    // �����ňȉ��̂悤�� d3d9.dll ����ADirect3DCreate9Ex �𒼐ڒT���āA�|�C���^��
    // �擾������@��MSDN�ɂ������̂ŁA�Q�l�ɂ��Ď����B
    // __uuid ���Z�q�� GCC �ɂ͖����̂ŁAIDD_IDirect3D9 �ɕύX�B
    // TODO::����Ő����Ȃ̂��낤���c�B

    HRESULT hr;
    typedef HRESULT (WINAPI *DIRECT3DCREATE9EXFUNCTION)(UINT SDKVersion, IDirect3D9Ex**);
    IDirect3D9* pID3D9 = nullptr;
    IDirect3D9Ex* pID3D9Ex = nullptr;
    HMODULE hD3D = LoadLibrary(TEXT("d3d9.dll"));

    DIRECT3DCREATE9EXFUNCTION pFunc_Direct3DCreate9Ex = (DIRECT3DCREATE9EXFUNCTION)GetProcAddress(hD3D, "Direct3DCreate9Ex");
    if (pFunc_Direct3DCreate9Ex) {
        _TRACE_("d3d9.dll�ɁADirect3DCreate9Ex�͑��݂��܂����B");
        //d3d9.dll �� Direct3DCreate9Ex �͑��݂���B
        hr = ((*pFunc_Direct3DCreate9Ex)(D3D_SDK_VERSION, &pID3D9Ex)); //Direct3DCreate9Ex ���s
        if (FAILED(hr)) {
            FreeLibrary(hD3D);
            throwCriticalException("IDirect3D9Ex �R���|�[�l���g�擾�Ɏ��s���܂����B(1)"); //���s
        }
//        hr = pID3D9Ex->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&pID3D9)); //COM�Ƃ��Ďg�p
//        if (FAILED(hr)) {
//            MessageBox(_pHWndPrimary, TEXT("IDirect3D9Ex �R���|�[�l���g�擾�Ɏ��s���܂����B(2)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
//            FreeLibrary(hD3D);
//            return E_FAIL; //���s
//        }
        _pID3D9 = (IDirect3D9*)pID3D9Ex;
        _can_wddm = true;
        _TRACE_("WDDM ���[�h");
    } else {
        _TRACE_("d3d9.dll�ɁADirect3DCreate9Ex�͑��݂��܂���ł����B");
        //d3d9.dll �� Direct3DCreate9Ex �͑��݂��Ȃ��B
        pID3D9 = Direct3DCreate9(D3D_SDK_VERSION);
        if (!pID3D9) {
            FreeLibrary(hD3D);
            throwCriticalException("IDirect3D9 �R���|�[�l���g�擾�Ɏ��s���܂����B");
        }
        _pID3D9 = pID3D9;
        _can_wddm = false;
        _TRACE_("XPDM ���[�h");
    }
    FreeLibrary(hD3D);

    //�f�o�C�X�p�����[�^�쐬
    D3DCAPS9 caps;
    _pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] �f�B�X�v���C �A�_�v�^�����������B
                           D3DDEVTYPE_HAL,     // [in] �f�o�C�X�̎�ށB D3DDEVTYPE�񋓌^�̃����o
                           &caps);             // [out] �f�o�C�X�̔\�͂��i�[�����
    _num_adapter = caps.NumberOfAdaptersInGroup;   //�g����A�_�v�^�̐��擾
    _TRACE_("_num_adapter = "<< _num_adapter);
    //Config�`�F�b�N�ƁA_primary_screen_adpter_no�A_secondary_screen_adpter_no //TODO:NUMBER_OF_SCREENS_USED �R��ʈȏ�̂Ƃ������͏C��
    if (CONFIG::FULL_SCREEN) {
        if (_num_adapter < CONFIG::NUMBER_OF_SCREENS_USED) {
            throwCriticalException("�t���X�N���[���� NUMBER_OF_SCREENS_USED="<<(Config::NUMBER_OF_SCREENS_USED)<<"���͈͊O�ł��B"<<_num_adapter<<"��ʂ̃}���`���j�^�������o�ł��܂���B");
        }
        if (_num_adapter > MAX_SCREENS) {
            throwCriticalException("�{�A�v���́A�t���X�N���[������ MAX_SCREENS="<<MAX_SCREENS<<" �ȏ�̃}���`���j�^�̓T�|�[�g�o���܂���B"<<_num_adapter<<"��ʂ̃}���`���j�^�����o����܂����B");
        }

        for (int pry = 0; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) {
            if (_num_adapter-1 < _screen_display_no[pry]) {
                throwCriticalException("_screen_display_no["<<pry<<"]="<<_screen_display_no[pry]<<"�͔͈͊O�̃f�B�X�v���C�A�_�v�^�ԍ��ł��B"<<
                                       "�A�_�v�^�ԍ��� 0�`"<<_num_adapter-1<<" ���L���ł��B");
            }
            for (int pry2 = 0; pry2 < CONFIG::NUMBER_OF_SCREENS_USED; pry2++) {
                if (pry == pry2) {
                    continue;
                }
                if (_screen_display_no[pry] == _screen_display_no[pry2]) {
                    throwCriticalException("�����f�B�X�v���C�A�_�v�^�ԍ����w�肵�Ă��܂��B\n"
                                               "_screen_display_no["<<pry<<"]="<<_screen_display_no[pry]<<" �� "
                                               "_screen_display_no["<<pry2<<"]="<<_screen_display_no[pry2]<<" ���d�����Ă��܂����B");
                }
            }
        }
        //�t���X�N���[�����͎w�肳�ꂽ�A�_�v�^�ȊO���Ԃ�Ȃ��悤�ɂ��Ă���
        _TRACE_("�t���X�N���[�����͎w�肳�ꂽ�A�_�v�^�ȊO���Ԃ�Ȃ��悤�ɂ��Ă���");
        _TRACE_("�����O");
        for (int pry = 0; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) {
            _TRACE_("_screen_display_no["<<pry<<"]="<<_screen_display_no[pry]);
        }
        int wk_adp = CONFIG::NUMBER_OF_SCREENS_USED;
        for (int pry = CONFIG::NUMBER_OF_SCREENS_USED; pry < _num_adapter; pry++) {
            for (int pry2 = 0; pry2 < pry; pry2++) {
                if (_screen_display_no[pry] == _screen_display_no[pry2]) {
                    _screen_display_no[pry]=wk_adp;
                    wk_adp++;
                }
            }
        }
        _TRACE_("������");
        for (int pry = 0; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) {
            _TRACE_("_screen_display_no["<<pry<<"]="<<_screen_display_no[pry]);
        }
    } else {
        //�E�B���h�E��
        for (int pry = 0; pry < MAX_SCREENS; pry++) {
            _screen_display_no[pry]=pry;
        }
    }
    _primary_screen_adpter_no = _screen_display_no[SCREEN01];

    //_num_window ���m�肷��
    //�E�B���h�E��
    if (CONFIG::FULL_SCREEN) {
        //�t���X�N���[����
        //_num_window �̓A�_�v�^���Ɉ�v
        _num_window = _num_adapter;
    } else {
        //�E�B���h�E���[�h��
        //_num_window �̓E�B���h�E���Ɉ�v
        _num_window = Config::NUMBER_OF_SCREENS_USED;
    }
    //_paWindowNoToScreenPry �쐬
    _paWindowNoToScreenPry = NEW int[_num_window];
    if (CONFIG::FULL_SCREEN) {
        //�t���X�N���[����
        for (int wno = 0; wno < _num_window; wno++) {
            _paWindowNoToScreenPry[wno] = -1;
            for (int pry = 0; pry < CONFIG::NUMBER_OF_SCREENS_USED; pry++) { //pry=SCREEN01,SCREEN02
                int adp_no = _screen_display_no[pry];
                if (wno == adp_no) {
                    _paWindowNoToScreenPry[wno] = pry;
                    break;
                }
            }
        }
    } else {
        //�E�B���h�E���[�h��
        for (int wno = 0; wno < _num_window; wno++) {
            _paWindowNoToScreenPry[wno] = wno;
        }
    }

    //_paPresetPrm[] ��ݒ肵�Ă����܂��B
    _paPresetPrm = NEW D3DPRESENT_PARAMETERS[_num_window];

    for (int wno = 0; wno < _num_window; wno++) {
        ZeroMemory(&_paPresetPrm[wno], sizeof(D3DPRESENT_PARAMETERS));
    }
    for (int wno = 0; wno < _num_window; wno++) {
        //�E�B���h�E���E�t���X�N���[��������
        _paPresetPrm[wno].BackBufferCount        = 1;            //�o�b�N�o�b�t�@�̐�
        _paPresetPrm[wno].EnableAutoDepthStencil = TRUE;         //�o�b�N�o�b�t�@�� Z�o�b�t�@�̎����쐬
        _paPresetPrm[wno].AutoDepthStencilFormat = D3DFMT_D24S8; //�[�x�X�e���V���o�b�t�@ //D3DFMT_D16;
        _paPresetPrm[wno].Flags                  = 0;            //0�ɂ��Ă���
        if (CONFIG::FULL_SCREEN) {
            //�t���X�N���[�������ʁi�S��ʁj
            _paPresetPrm[wno].BackBufferFormat           = D3DFMT_X8R8G8B8; //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
            _paPresetPrm[wno].Windowed                   = false; //�t���X�N���[�����[�h��
            _paPresetPrm[wno].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //���t���b�V�����[�g
            _paPresetPrm[wno].PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT; //�X���b�v�̃^�C�~���O
            _paPresetPrm[wno].SwapEffect                 = D3DSWAPEFFECT_DISCARD;
            _paPresetPrm[wno].EnableAutoDepthStencil     = FALSE; //Z�o�b�t�@�̎����쐬����
            //�y�����z
            //EnableAutoDepthStencil = FALSE;
            //�Ƃ���ƁA�����_�����O�X�e�[�g�� D3DRS_ZENABLE �� FALSE �ɂȂ邾���̂悤�Ɍ�����B
            //�]���āu�����v�ɂ��������ł���A�u�g�p�s�v�ł͂Ȃ��̂��낤�E�E�E�B
        } else {
            //�E�B���h�E�����ʁi�S�E�B���h�E�j
            _paPresetPrm[wno].BackBufferFormat           = D3DFMT_UNKNOWN; //���݂̕\�����[�h�t�H�[�}�b�g
            _paPresetPrm[wno].Windowed                   = true; //�E�B���h�E���[�h��
            _paPresetPrm[wno].FullScreen_RefreshRateInHz = 0; //���t���b�V�����[�g
            _paPresetPrm[wno].PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE; //����
            _paPresetPrm[wno].SwapEffect                 = D3DSWAPEFFECT_COPY; //TODO:Window���[�h�͂������Ȃ̂��H�AD3DPRESENT_INTERVAL_ONE �Ƃ����߂��H
            _paPresetPrm[wno].EnableAutoDepthStencil = TRUE; //Z �o�b�t�@�̎����쐬
        }
    }

    //�A���`�A�C���A�X�ɂł��邩�`�F�b�N
    DWORD qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;
//    if( SUCCEEDED(_pID3D9->CheckDeviceMultiSampleType(
//        D3DADAPTER_DEFAULT,
//        D3DDEVTYPE_HAL,
//        _paPresetPrm[_primary_screen_adpter_no].BackBufferFormat,  //TODO:�E�B���h�E���[�h����
//        CONFIG::FULL_SCREEN ? FALSE : TRUE,
//        D3DMULTISAMPLE_2_SAMPLES,
//        &qualityLevels) ) )
//    {
//        if( SUCCEEDED(_pID3D9->CheckDeviceMultiSampleType(
//            D3DADAPTER_DEFAULT,
//            D3DDEVTYPE_HAL,
//            _paPresetPrm[_primary_screen_adpter_no].AutoDepthStencilFormat,
//            CONFIG::FULL_SCREEN ? FALSE : TRUE,
//            D3DMULTISAMPLE_2_SAMPLES,
//            nullptr) ) )
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

    //�}���`�T���v��
    for (int wno = 0; wno < _num_window; wno++) {
        int pry = _paWindowNoToScreenPry[wno];
        if (pry >= 0) {
            _paPresetPrm[wno].MultiSampleType = multiSampleType; //�}���`�T���v���̐�
            _paPresetPrm[wno].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0); //�}���`�T���v���̕i�����x��
        } else {
            _paPresetPrm[wno].MultiSampleType = D3DMULTISAMPLE_NONE;//D3DMULTISAMPLE_NONE;
            _paPresetPrm[wno].MultiSampleQuality = 0;
        }
    }

    //�o�b�N�o�b�t�@�T�C�Y
    for (int wno = 0; wno < _num_window; wno++) {
        int pry = _paWindowNoToScreenPry[wno];
        if (CONFIG::FULL_SCREEN) {
            //�t���X�N���[�����i�t���X�N���[���`�F�b�N�ŏ㏑������邩������Ȃ����ǃf�t�H���g�l��ݒ�)
            if (pry >= 0) {
                _paPresetPrm[wno].BackBufferWidth  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _paPresetPrm[wno].BackBufferHeight = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            } else {
                //���܂�̉��
                _paPresetPrm[wno].BackBufferWidth  = CONFIG::SCREEN_FULL_SCREEN[SCREEN01].WIDTH;
                _paPresetPrm[wno].BackBufferHeight = CONFIG::SCREEN_FULL_SCREEN[SCREEN01].HEIGHT;
            }
        } else {
            //�E�B���h�E�� �i���ۂɂ�_paPresetPrm[_primary_screen_adpter_no] �����g�p����Ȃ��j
            _paPresetPrm[wno].BackBufferWidth  = CONFIG::RENDER_TARGET_BUFFER_WIDTH;
            _paPresetPrm[wno].BackBufferHeight = CONFIG::RENDER_TARGET_BUFFER_HEIGHT;
        }
    }

    _paDisplayMode = NEW D3DDISPLAYMODEEX[_num_window];
    for (int wno = 0; wno < _num_window; wno++) {
        _paDisplayMode[wno].Size = sizeof(_paDisplayMode[wno]);
        _paDisplayMode[wno].Width = _paPresetPrm[wno].BackBufferWidth;
        _paDisplayMode[wno].Height = _paPresetPrm[wno].BackBufferHeight;
        _paDisplayMode[wno].Format = _paPresetPrm[wno].BackBufferFormat;
        _paDisplayMode[wno].RefreshRate = _paPresetPrm[wno].FullScreen_RefreshRateInHz;
        _paDisplayMode[wno].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
    }

    if (CONFIG::FULL_SCREEN) {
        _papSwapChain = NEW IDirect3DSwapChain9*[_num_adapter];
        _papBackBuffer = NEW IDirect3DSurface9*[_num_adapter];
        for (int adp = 0; adp < _num_adapter; adp++) {
            _papSwapChain[adp] = nullptr;
            _papBackBuffer[adp] = nullptr;
        }

    } else {
        _papSwapChain = nullptr;
        _papBackBuffer = nullptr;
        _paAdapterRezos = nullptr;
    }

    _paAvailableAdapter = NEW Adapter[_num_adapter];
    _paAdapterRezos = NEW AdapterRezos[_num_adapter];
    pCARETAKER->setDisplaySizeInfo();
    pCARETAKER->setAppropriateDisplaySize();

    // �E�C���h�E�̐���
    _paHWnd = NEW HWND[_num_window];
    for (int wno = 0; wno < _num_window; wno++) {
        _paHWnd[wno] = nullptr;
    }
    GgafCore::Rgb rgb = GgafCore::Rgb(CONFIG::BORDER_COLOR);
    prm_wndclass.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
//    prm_wndclass2.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
    if (CONFIG::FULL_SCREEN) {
        if (CONFIG::NUMBER_OF_SCREENS_USED == 1) {
            //�P��ʃt���X�N���[��
            int wno = _screen_display_no[SCREEN01];
            std::string title = std::string(prm_title);
            WNDCLASSEX wc = prm_wndclass;
            RegisterClassEx(&wc);
            _paHWnd[wno] =
                    CreateWindowEx(
                        WS_EX_APPWINDOW,
                        wc.lpszClassName,
                        title.c_str(),
                        WS_POPUP | WS_VISIBLE,  //WS_POPUP:�N���C�A���g�̈�̂�
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        _paPresetPrm[wno].BackBufferWidth,
                        _paPresetPrm[wno].BackBufferHeight,
                        HWND_DESKTOP,
                        nullptr,
                        wc.hInstance,
                        nullptr
                    );
        } else {
            //�Q��ʈȏ�̃t���X�N���[���́A�}���`�w�b�h�̂��߁A�S���̉�ʂɃE�B���h�E���쐬
            for (int wno = 0; wno < _num_window; wno++) {
                std::string title = wno == 0 ? std::string(prm_title) : std::string(prm_title) + "(" + XTOS(wno+1) + ")";
                WNDCLASSEX wc = prm_wndclass;
                RegisterClassEx(&wc);
                _paHWnd[wno] =
                        CreateWindowEx(
                            WS_EX_APPWINDOW,
                            wc.lpszClassName,
                            title.c_str(),
                            WS_POPUP | WS_VISIBLE,  //WS_POPUP:�N���C�A���g�̈�̂�
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            _paPresetPrm[wno].BackBufferWidth,
                            _paPresetPrm[wno].BackBufferHeight,
                            HWND_DESKTOP,
                            nullptr,
                            wc.hInstance,
                            nullptr
                        );
            }
        }
    } else {
        //�E�B���h�E���[�h��
        for (int wno = 0; wno < _num_window; wno++) {
            std::string title = wno == 0 ? std::string(prm_title) : std::string(prm_title) + "(" + XTOS(wno+1) + ")";
            WNDCLASSEX wc = prm_wndclass;
            RegisterClassEx(&wc);
            _paHWnd[wno] =
                    CreateWindow(
                        wc.lpszClassName,
                        title.c_str(),
                        prm_dwStyle,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CONFIG::SCREEN_WINDOW[wno].WIDTH,
                        CONFIG::SCREEN_WINDOW[wno].HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        wc.hInstance,
                        nullptr
                    );
        }
    }

    //Window�n���h�����ʎw��
    _mapHwndToPry[nullptr] = -1;
    _mapHwndToWindowNo[nullptr] = -1;
    for (int wno = 0; wno < _num_window; wno++) {
        _paPresetPrm[wno].hDeviceWindow = _paHWnd[wno]; //���ӁF�����v�f�ɂ� null �������Ă���
        if (_paHWnd[wno]) {
            _mapHwndToWindowNo[_paHWnd[wno]] = wno;
            _mapHwndToPry[_paHWnd[wno]] = _paWindowNoToScreenPry[wno];
        }
    }
    _pHWndPrimary  = _paHWnd[_primary_screen_adpter_no];
//    _pHWndSecondary = _paHWnd[_secondary_screen_adpter_no];

    //_pHWndPrimary �̗L����
    //�E�B���h�E�v���V�[�W���� WM_SETFOCUS ���̔r���ɂȂ��Ă���̂ŁA
    //�Q��ʖ� �� �P��ʖڂ̏��ő�����邱�ƁB
//    out_hWnd1 = _pHWndPrimary;
//    out_hWnd2 = _pHWndSecondary;

    if (!_pHWndPrimary) {
        throwCriticalException("�v���C�}���E�B���h�E���쐬�o���܂���ł����B");
    }
    if (CONFIG::FULL_SCREEN) {
        setFullScreenWindowPos();
    } else {
        //�E�B���h�E���[�h���A�N���C�A���g�̈�����]�̑傫���ɂ��邽�߁A
        //�^�C�g���o�[�A���T�C�Y�{�[�_�[�̌������l�����Đݒ�B
        //�E�B���h�E���[�h��
        for (int wno = 0; wno < _num_window; wno++) {
            if (_paHWnd[wno]) {
                int pry = _paWindowNoToScreenPry[wno];
                resetWindowsize(_paHWnd[wno], CONFIG::SCREEN_WINDOW[pry].WIDTH, CONFIG::SCREEN_WINDOW[pry].HEIGHT);
            }
        }
    }

    //�A�N�e�B�u��
    for (int wno = 0; wno < _num_window; wno++) {
        if (_paHWnd[wno]) {
            ShowWindow(_paHWnd[wno], SW_SHOWNORMAL);
            UpdateWindow(_paHWnd[wno]);
        }
    }
    _pCurveSrcManager = createCurveSourceManager();
    _pCurveManufManager = createCurveManufactureManager();

    //�f�o�C�X�쐬
    if (FAILED(initDevice())) {
        throwCriticalException("�������Ɏ��s���܂����B�A�v���P�[�V�������N���o���܂���B");
    }
}


HRESULT Caretaker::initDevice() {

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
//    for (UINT Adapter = 0; Adapter < _pID3D9->GetAdapterCount(); Adapter++) {
//        D3DADAPTER_IDENTIFIER9 Identifier;
//        HRESULT Res;
//        Res = _pID3D9->GetAdapterIdentifier(Adapter, 0, &Identifier);
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
//    _TRACE_("_primary_screen_adpter_no="<<_primary_screen_adpter_no);
//    _TRACE_("_secondary_screen_adpter_no="<<_secondary_screen_adpter_no);
    for (int n = 0; n < _num_window; n++) {
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferWidth            = "<<_paPresetPrm[n].BackBufferWidth            );
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferHeight           = "<<_paPresetPrm[n].BackBufferHeight           );
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferFormat           = "<<_paPresetPrm[n].BackBufferFormat           );
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferCount            = "<<_paPresetPrm[n].BackBufferCount            );
        _TRACE_("_paPresetPrm["<<n<<"].MultiSampleType            = "<<_paPresetPrm[n].MultiSampleType            );
        _TRACE_("_paPresetPrm["<<n<<"].MultiSampleQuality         = "<<_paPresetPrm[n].MultiSampleQuality         );
        _TRACE_("_paPresetPrm["<<n<<"].SwapEffect                 = "<<_paPresetPrm[n].SwapEffect                 );
        _TRACE_("_paPresetPrm["<<n<<"].hDeviceWindow              = "<<_paPresetPrm[n].hDeviceWindow              );
        _TRACE_("_paPresetPrm["<<n<<"].Windowed                   = "<<_paPresetPrm[n].Windowed                   );
        _TRACE_("_paPresetPrm["<<n<<"].EnableAutoDepthStencil     = "<<_paPresetPrm[n].EnableAutoDepthStencil     );
        _TRACE_("_paPresetPrm["<<n<<"].AutoDepthStencilFormat     = "<<_paPresetPrm[n].AutoDepthStencilFormat     );
        _TRACE_("_paPresetPrm["<<n<<"].Flags                      = "<<_paPresetPrm[n].Flags                      );
        _TRACE_("_paPresetPrm["<<n<<"].FullScreen_RefreshRateInHz = "<<_paPresetPrm[n].FullScreen_RefreshRateInHz );
        _TRACE_("_paPresetPrm["<<n<<"].PresentationInterval       = "<<_paPresetPrm[n].PresentationInterval       );

        _TRACE_("_paDisplayMode["<<n<<"].Size             = "<<_paDisplayMode[n].Size            );
        _TRACE_("_paDisplayMode["<<n<<"].Width            = "<<_paDisplayMode[n].Width           );
        _TRACE_("_paDisplayMode["<<n<<"].Height           = "<<_paDisplayMode[n].Height          );
        _TRACE_("_paDisplayMode["<<n<<"].RefreshRate      = "<<_paDisplayMode[n].RefreshRate     );
        _TRACE_("_paDisplayMode["<<n<<"].Format           = "<<_paDisplayMode[n].Format          );
        _TRACE_("_paDisplayMode["<<n<<"].ScanLineOrdering = "<<_paDisplayMode[n].ScanLineOrdering);
    }
    _TRACE_("_pHWndPrimary="<<_pHWndPrimary);
//    _TRACE_("_pHWndSecondary="<<_pHWndSecondary);

    HRESULT hr;
    //�s�N�Z���V�F�[�_�[�A���_�V�F�[�_�[�o�[�W�����`�F�b�N
    D3DCAPS9 caps;
    _pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] �f�B�X�v���C �A�_�v�^�����������B
                           D3DDEVTYPE_HAL,     // [in] �f�o�C�X�̎�ށB D3DDEVTYPE�񋓌^�̃����o
                           &caps);             // [out] �f�o�C�X�̔\�͂��i�[�����
    _vs_v = caps.VertexShaderVersion;
    _ps_v = caps.PixelShaderVersion;

    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(_vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(_vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(_ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(_ps_v));
    if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
        _TRACE_("�r�f�I�J�[�h�n�[�h�̒��_�V�F�[�_�[ 3_0 �A�s���N�Z���V�F�[�_�[ 3_0 �ȏオ�����ł��B");
        _TRACE_("���g�p�̃r�f�I�J�[�h�ł́A���������삵�Ȃ����ꂪ����܂��B");
    }

    if (CONFIG::FULL_SCREEN && Config::NUMBER_OF_SCREENS_USED > 1) {
        //���t���X�N���[�� ���� �f���A���r���[ �̏ꍇ��
        //�f�o�C�X�쐬������ _pID3DDevice9 �֐ݒ肷��B
        //�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
        if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
            hr = D3DERR_NOTAVAILABLE;
        } else {
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _paPresetPrm[0].hDeviceWindow,
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                 _paPresetPrm, _paDisplayMode);
        }
        if (hr != D3D_OK) {
            if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
                hr = D3DERR_NOTAVAILABLE;
            } else {
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _paPresetPrm[0].hDeviceWindow,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                     _paPresetPrm, _paDisplayMode);
            }
            if (hr != D3D_OK) {
                if (_ps_v < D3DPS_VERSION(3, 0)) {
                    hr = D3DERR_NOTAVAILABLE;
                } else {
                    //�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
                    hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _paPresetPrm[0].hDeviceWindow,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                         _paPresetPrm, _paDisplayMode);
                }
                if (hr != D3D_OK) {
                    //�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
                    hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _paPresetPrm[0].hDeviceWindow,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                         _paPresetPrm, _paDisplayMode);

                    if (hr != D3D_OK) {
                        //�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
                        _TRACE_(FUNC_NAME<<" DirectX�̏������Ɏ��s���܂����B�}���`�w�b�hD3DCREATE_SOFTWARE_VERTEXPROCESSING : "<<CriticalException::getHresultMsg(hr));
                        MessageBox(_pHWndPrimary, "DirectX�̏������Ɏ��s���܂����B\n�}���`�w�b�h�f�B�X�v���C�������݂��Ă��܂���B", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                        return E_FAIL;
                    } else {
                        _TRACE_(FUNC_NAME<<" �f�o�C�X�� MULTI FULLSCRREEN REF �ŏ������ł��܂����B");
                    }
                } else {
                    _TRACE_(FUNC_NAME<<" �f�o�C�X�� MULTI FULLSCRREEN HAL(soft vp) �ŏ������ł��܂����B");
                }
            } else {
                _TRACE_(FUNC_NAME<<" �f�o�C�X�� MULTI FULLSCRREEN HAL(hard vp) �ŏ������ł��܂����B");
            }
        } else {
            _TRACE_(FUNC_NAME<<" �f�o�C�X�� MULTI FULLSCRREEN HAL(pure vp) �ŏ������ł��܂����B");
        }

    } else {
        //��(�t���X�N���[�� ���� �f���A���r���[) �ȊO�̏ꍇ��

        D3DDISPLAYMODEEX* pDISPLAYMODE = nullptr;
        if (CONFIG::FULL_SCREEN) {
            pDISPLAYMODE = &_paDisplayMode[_primary_screen_adpter_no];
        }
        UINT adapter = _primary_screen_adpter_no; //�ǂ̃A�_�v�^�ɕ\�����邩
        //�f�o�C�X�쐬������ _pID3DDevice9 �֐ݒ肷��B
        //�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
        if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
            hr = D3DERR_NOTAVAILABLE;
        } else {
            hr = createDx9Device(adapter, D3DDEVTYPE_HAL, _pHWndPrimary,
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                 &_paPresetPrm[_primary_screen_adpter_no], pDISPLAYMODE);
    //                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        }
        if (hr != D3D_OK) {
            if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
                hr = D3DERR_NOTAVAILABLE;
            } else {
                hr = createDx9Device(adapter, D3DDEVTYPE_HAL, _pHWndPrimary,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                     &_paPresetPrm[_primary_screen_adpter_no], pDISPLAYMODE);
            }

            if (hr != D3D_OK) {
                if (_ps_v < D3DPS_VERSION(3, 0)) {
                    hr = D3DERR_NOTAVAILABLE;
                } else {
                    //�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
                    hr = createDx9Device(adapter, D3DDEVTYPE_HAL, _pHWndPrimary,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                         &_paPresetPrm[_primary_screen_adpter_no], pDISPLAYMODE);
                }
                if (hr != D3D_OK) {
                    //�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
                    hr = createDx9Device(adapter, D3DDEVTYPE_REF, _pHWndPrimary,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                         &_paPresetPrm[_primary_screen_adpter_no], pDISPLAYMODE);
                    if (hr != D3D_OK) {
                        //�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
                        _TRACE_(FUNC_NAME<<" DirectX�̏������Ɏ��s���܂����B "<<CriticalException::getHresultMsg(hr));
                        MessageBox(_pHWndPrimary, "DirectX�̏������Ɏ��s���܂����B", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                        return E_FAIL;
                    } else {
                        _TRACE_(FUNC_NAME<<" �f�o�C�X�� REF �ŏ������ł��܂����B");
                    }
                } else {
                    _TRACE_(FUNC_NAME<<" �f�o�C�X�� HAL(soft vp) �ŏ������ł��܂����B");
                }
            } else {
                _TRACE_(FUNC_NAME<<" �f�o�C�X�� HAL(hard vp) �ŏ������ł��܂����B");
            }
        } else {
            _TRACE_(FUNC_NAME<<" �f�o�C�X�� HAL(pure vp) �ŏ������ł��܂����B");
        }
    }

    //�e�X�g
    if (_can_wddm) {
        hr = ((IDirect3DDevice9Ex*)_pID3DDevice9)->SetMaximumFrameLatency(0);
        checkDxException(hr, D3D_OK, "SetMaximumFrameLatency(0) �Ɏ��s���܂����B");
    }
    _pTextureManager = createTextureManager();
    _pModelManager = createModelManager();
    _pEffectManager = createEffectManager();
    Util::init();  //���[�e�B���e�B����
    Input::init(); //DirectInput����
    Sound::init(); //DirectSound����
    //�f�o�C�X������
    hr = initDx9Device();
    if (hr == E_FAIL) {
        return E_FAIL;
    }
    Sleep(100);
    //�t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���[�쐬
    if (CONFIG::FULL_SCREEN) {
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
    //2015/09/02 �ǋL�E�v����
    //�����A�Ђ���Ƃ�����A���j�^���W��񂪁A�t���X�N���[���O�̕����擾���Ă邩�炾�낤���E�E�E
    if (_can_wddm && CONFIG::FULL_SCREEN && Config::NUMBER_OF_SCREENS_USED > 1) {
        hr = releaseFullScreenRenderTarget();
        hr = restoreFullScreenRenderTarget();
    }
    return D3D_OK;
}

BOOL CALLBACK Caretaker::updateMoniterPixcoordCallback(HMONITOR hMonitor,
                                                       HDC hdcMonitor,
                                                       LPRECT lprcMonitor,
                                                       LPARAM dwData) {
    Caretaker* pCaretaker = (Caretaker*)dwData;
    MONITORINFOEX moniter_info;
    moniter_info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &moniter_info);

    for (int adapter_no = 0; adapter_no < pCaretaker->_num_adapter; adapter_no++) {
        Adapter& adpt = pCaretaker->_paAvailableAdapter[adapter_no];
        if (adpt.hMonitor == hMonitor) {
            adpt.rcMonitor = moniter_info.rcMonitor;
        }
    }
    return TRUE; //�񋓂𑱍s
}

HRESULT Caretaker::createDx9Device(UINT adapter,
                                   D3DDEVTYPE device_type,
                                   HWND hFocusWindow,
                                   DWORD behavior_flags,
                                   D3DPRESENT_PARAMETERS* pPresentationParameters,
                                   D3DDISPLAYMODEEX* pFullscreenDisplayMode
                                  ) {
    HRESULT hr;
    if (_can_wddm) {
        if (!CONFIG::FULL_SCREEN) {
            pFullscreenDisplayMode = nullptr;
        }
        IDirect3D9Ex* pID3D9Ex = (IDirect3D9Ex*)_pID3D9;
        IDirect3DDevice9Ex* pID3DDevice9Ex;
        hr = pID3D9Ex->CreateDeviceEx(adapter,
                                      device_type,
                                      hFocusWindow,
                                      behavior_flags,
                                      pPresentationParameters,
                                      pFullscreenDisplayMode,
                                      &pID3DDevice9Ex
                                      );
        _pID3DDevice9 = (IDirect3DDevice9Ex*)pID3DDevice9Ex;
    } else {
        hr = _pID3D9->CreateDevice(adapter,
                                       device_type,
                                       hFocusWindow,
                                       behavior_flags,
                                       pPresentationParameters,
                                       &_pID3DDevice9
                                       );
    }
    return hr;
 }

HRESULT Caretaker::initDx9Device() {

    //�y���Ӂz�{�t���[�����[�N�̃f�t�H���g��RenderState��ݒ�B
    //�ύX���͈ȉ��ɉe�����Ȃ����m�F�B
    // void Spacetime::draw() �̕`�掞
    //FigureActor �R���X�g���N�^�̈ȉ��̃����o�̏����l
    // _zenable = true;
    // _zwriteenable = true;
    // _cull_enable = true;
    // _cull_mode_default = D3DCULL_CCW;
    // _cull_mode = _cull_mode_default

    //���C�g���Z�b�g
    //    _pID3DDevice9->SetLight(0, &Caretaker::_d3dlight9_default);
    //���C�g�X�C�b�`ON
    //    _pID3DDevice9->LightEnable(0, TRUE);
    //_pID3DDevice9->LightEnable(0, FALSE);
    //�����_���Ƀ��C�g�̉e���i�A�e�j��L��
    //    _pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
    //�����_���Ƀ��C�g�̉e���i�A�e�j�𖳌� (�s�N�Z���V�F�[�_�[�ōs�Ȃ����߁j
    _pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
    //�����_���A���E�ɋ��ʂ̃A���r�G���g���C�g��L���ɂ����悤�ɕ`��
    //   _pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _ambient_brightness_default);

    // Z�o�b�t�@��L����
    _pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�𖳌���
    //_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

    //Z�o�b�t�@�������݉�
    _pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //Z�o�b�t�@�������ݕs��
    //_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    //D3DRENDERSTATE_ZFUNC

    //�X�e���V���e�X�g�̕��@
    _pID3DDevice9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //��Ƀe�X�g���p�X
    //��Ɏ��s�������ɃX�e���V���̒l���ǂ��ω������邩
    _pID3DDevice9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //�ω��Ȃ�
    //Z�e�X�g�Ŏ��s�����ꍇ�̃X�e���V���l�̕ω�
    _pID3DDevice9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //�ω��Ȃ�


    //���i�����v���j���ɃJ�����O �捶����W�n
    _pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //�J�����O���Ȃ�
    //_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // �f�B�U�����O
    //_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
    // �}���`�T���v�����O�A���`�G�C���A�X(�Ƃ����Ă��t���X�N���[�������H)��TODO:�܂���
    _pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
//    _pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

    //�s�N�Z���P�ʂ̃A���t�@�e�X�g��L��
    _pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //���ݒ�̓V�F�[�_�[�ɏ������ɂ����̂ŃR�����g
    // �A���t�@�u�����h�n�m
    //    _pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //2�i�K�ځA�������e�N�X�`����\��t�����|���S���ƃo�b�N�o�b�t�@�i�����_�[�^�[�Q�b�g�j�Ƃ̍���
    //�F�̎Z�o���@�̐ݒ�
    //_pID3DDevice9->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); //D3DBLENDOP_ADD=�]�����ɓ]���悪���Z
    //�����W��
    //    //��ɏ����摜�̍����@(�V�F�[�_�[�ɉe��)
    //    _pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=���ʂɕ`���B�|���S���̃A���t�@�l�̔Z���ŕ`���B�A���t�@�l�̒l��������΍����قǁA�Z���`���B
    //    //���n�̉摜�̍����@(�V�F�[�_�[�ɉe��)
    //    _pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=��ɕ`���|���S���̃A���t�@�l�̔Z���ɂ���āA���n�̕`��𔖂�����B



    //���_�J���[�𖳌��ɂ���
    //_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, FALSE );
    // _pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, TRUE );
    //    //�ʂ̃A���r�G���g���˂́A�}�e���A�����Q�Ƃ���悤�ɐݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃f�t���[�Y���˂́A�}�e���A�����Q�Ƃ���悤�ɐݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃G�~�b�V�u���˂́A�}�e���A�����Q�Ƃ���ݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //�ʂ̃X�y�L�������˂́A�}�e���A�����Q�Ƃ���ݒ肷��B�i���_�J���[���Q�Ƃ���ꍇ�� D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    //���_�����g�p����Ƃ�
    //_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);

    //
    //
    // �A���`�G�C���A�X�̎w��
    //_pID3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //_pID3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
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
    //_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
    //_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);

    //�F�������S�ăV�F�[�_�[�ŏ����ɂȂ����̂ŃR�����g
    //SetTextureStageState�͔p�~�H
    //  1�i�K�ڃ|���S���ƃe�N�X�`���̍������@�ݒ�
    //    //�e�N�X�`���[�̐F�ƁA���_�J���[��DIFFUSE�F����Z����悤�ɐݒ�
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    //    //�e�N�X�`���[�̃��ƁA���_�J���[�̃�����Z����悤�ɐݒ�
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


    //Camera�ֈړ�����
    // VIEW�ϊ��i�J�����ʒu�j�ݒ�
    //D3DXMATRIX _matView; // �r���[�ϊ��s��
    //    GGAF_DELETE_NULLABLE(_pVecCamFromPoint);
    //    GGAF_DELETE_NULLABLE(_pVecCamLookatPoint);
    //    GGAF_DELETE_NULLABLE(_pVecCamUp);

    //Camera�ֈړ�����
    // �ˉe�ϊ��i�R�c�����ʁj
    //D3DXMATRIX _matProj; // �ˉe�ϊ��s��
    //_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_matProj);
    //HRESULT hr;
    //�o�b�N�o�b�t�@���E�B���h�EBG�F�ŃN���A
    //�����ł�RenderTarget�͂܂��A�ʏ�̃o�b�N�o�b�t�@�ł���
//    hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
//    returnWhenFailed(hr, D3D_OK, "�w�i�F(_color_border)�̓h��Ԃ����A��ʃN���A�Ɏ��s���܂����B");
    return D3D_OK;
}


HRESULT Caretaker::restoreFullScreenRenderTarget() {
_TRACE_("restoreFullScreenRenderTarget() 1");

    if (!CONFIG::FULL_SCREEN) {
        _TRACE_("�y�x���z�t���X�N���[�����ӊO�A�Ăяo���s�v�ł��B");
        return D3D_OK;
    }
    HRESULT hr;
    //�`���ƂȂ�T�[�t�F�C�X��ʓr�쐬�i�o�b�N�o�b�t�@�I�Ȏg�p���s���j
    hr = _pID3DDevice9->CreateRenderTarget(
        CONFIG::RENDER_TARGET_BUFFER_WIDTH,
        CONFIG::RENDER_TARGET_BUFFER_HEIGHT,
        _paPresetPrm[_primary_screen_adpter_no].BackBufferFormat,
        D3DMULTISAMPLE_NONE, //D3DMULTISAMPLE_TYPE MultiSample,
        0, //DWORD MultisampleQuality,
        true, //BOOL Lockable,
        &_pRenderTextureSurface,
        nullptr //HANDLE* pHandle
    );
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`���̃T�[�t�F�C�X�擾�Ɏ��s���܂����B");
    hr = _pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`���� SetRenderTarget �o���܂���ł����B");

    //�e�N�X�`���ɕ`�悷��ۂ̐[�x�o�b�t�@�p�T�[�t�F�C�X��ʓr�쐬
    hr = _pID3DDevice9->CreateDepthStencilSurface(
            CONFIG::RENDER_TARGET_BUFFER_WIDTH,
            CONFIG::RENDER_TARGET_BUFFER_HEIGHT,
            _paPresetPrm[_primary_screen_adpter_no].AutoDepthStencilFormat, //D3DFORMAT           Format,
            _paPresetPrm[_primary_screen_adpter_no].MultiSampleType,        //D3DMULTISAMPLE_TYPE MultiSample,
            _paPresetPrm[_primary_screen_adpter_no].MultiSampleQuality,     //DWORD               MultisampleQuality,
            TRUE,                                   //BOOL                Discard, SetDepthStencileSurface�֐��Ő[�x�o�b�t�@��ύX�������Ƀo�b�t�@��j�����邩�ǂ���
            &_pRenderTextureZ,                      //IDirect3DSurface9** ppSurface,
            nullptr                                 //HANDLE*             pHandle ���ݖ��g�p
    );
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`����Z�o�b�t�@�쐬�Ɏ��s���܂����B");
    //�[�x�o�b�t�@�쐬���������́A�[�x�o�b�t�@�p�T�[�t�F�C�X����L�ɕύX
    hr =  _pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
    returnWhenFailed(hr, D3D_OK, "�����_�����O�^�[�Q�b�g�e�N�X�`���� SetDepthStencilSurface �o���܂���ł����B");
    //�w�i�F�ŃN���A
    hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK,  "�N���A�F(_color_border)�̓h��Ԃ����A��ʃN���A�Ɏ��s���܂����B1");
    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK,  "�N���A�F(_color_border)�̓h��Ԃ����A��ʃN���A�Ɏ��s���܂����B2");
    hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK,  "�N���A�F(_color_border)�̓h��Ԃ����A��ʃN���A�Ɏ��s���܂����B3");
    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK,  "�N���A�F(_color_border)�̓h��Ԃ����A��ʃN���A�Ɏ��s���܂����B4");

    //�A�_�v�^�Ɋ֘A�t����ꂽ�X���b�v�`�F�[�����擾���ăo�b�N�o�b�t�@�擾
    //�����́A adapter 0, 1, 2, ����̏��� GetSwapChain() ���邱��
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        for (int adapter = 0; adapter < _num_adapter; adapter++) {
            hr = _pID3DDevice9->GetSwapChain( adapter, &_papSwapChain[adapter] );
            returnWhenFailed(hr, D3D_OK, "�X���b�v�`�F�C���擾�Ɏ��s���܂���(2)�Badapter="<<adapter);
            hr = _papSwapChain[adapter]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_papBackBuffer[adapter] );
            returnWhenFailed(hr, D3D_OK, "�X���b�v�`�F�C������A�^�[�Q�b�g�̃o�b�N�o�b�t�@�擾�Ɏ��s���܂���(2)�Badapter="<<adapter);
        }
    } else {
        hr = _pID3DDevice9->GetSwapChain( 0, &_papSwapChain[_primary_screen_adpter_no] );
        returnWhenFailed(hr, D3D_OK, "�X���b�v�`�F�C���擾�Ɏ��s���܂����B");
        hr = _papSwapChain[_primary_screen_adpter_no]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_papBackBuffer[_primary_screen_adpter_no] );
        returnWhenFailed(hr, D3D_OK, "�X���b�v�`�F�C������A�^�[�Q�b�g�̃o�b�N�o�b�t�@�擾�Ɏ��s���܂����B(3)");
    }

    //�t���X�N���[�����A�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@��w�i�F�œh��
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        for (int wno = 0; wno < _num_window; wno++) {
            int pry = _paWindowNoToScreenPry[wno];
            if (pry >= 0) {
                hr = _pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRectRenderBufferSource[pry],
                        _papBackBuffer[wno], &_aRect_FullScreen[pry],
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "FULL_SCREEN "<<wno<<"��ʖځA�w�i�F�h�Ɏ��s���܂����B(1)\n"
                                             "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_papBackBuffer[adapter]="<<_papBackBuffer[wno]);
            }
        }
    } else {
        hr = _pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRectRenderBufferSource[SCREEN01],
                _papBackBuffer[_primary_screen_adpter_no], &_aRect_FullScreen[SCREEN01],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN �w�i�F�h�Ɏ��s���܂����B(1)");
    }

    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK, "Present(nullptr, nullptr, nullptr, nullptr)�Ɏ��s���܂����B");
    //�t���b�v���Ă�����x�w�i�F�œh��
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        for (int wno = 0; wno < _num_window; wno++) {
            int pry = _paWindowNoToScreenPry[wno];
            if (pry >= 0) {
                hr = _pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRectRenderBufferSource[pry],
                        _papBackBuffer[wno], &_aRect_FullScreen[pry],
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "FULL_SCREEN "<<wno<<"��ʖځA�w�i�F�h�Ɏ��s���܂����B(2)\n"
                                             "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_papBackBuffer[adapter]="<<_papBackBuffer[wno]);
            }
        }
    } else {
        hr = _pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRectRenderBufferSource[SCREEN01],
                _papBackBuffer[_primary_screen_adpter_no], &_aRect_FullScreen[SCREEN01],
                D3DTEXF_NONE
                );
        checkDxException(hr, D3D_OK, "FULL_SCREEN �w�i�F�h�Ɏ��s���܂����B(2)");
    }
    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK, "Present(nullptr, nullptr, nullptr, nullptr)�Ɏ��s���܂����B(2)");
    //�����ʂȊ��������AVISTA��XP�̂Q��ʖڃt���X�N���[�����[�h��
    //  ���Ή�������̂͂��̂悤�ȃR�[�h�����Ȃ��Ƃ������_�B

    //�t���X�N���[���̃E�B���h�E�ʒu��␳
    setFullScreenWindowPos();
    return D3D_OK;
}
void Caretaker::setFullScreenWindowPos() {
    EnumDisplayMonitors(nullptr, nullptr, Caretaker::updateMoniterPixcoordCallback, (LPARAM)this);
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        for (int n = 0; n < _num_adapter; n++) {
            pixcoord full_screen_x = _paAvailableAdapter[n].rcMonitor.left;
            pixcoord full_screen_y = _paAvailableAdapter[n].rcMonitor.top;
            _TRACE_("��� adapter_no="<<n<<" �̍�����W("<<full_screen_x<<","<<full_screen_y<<")");
            ShowWindow(_paHWnd[n], SW_SHOWNORMAL);
            UpdateWindow(_paHWnd[n]);
            SetWindowPos(_paHWnd[n],
                         HWND_TOPMOST,
                         full_screen_x, full_screen_y, 0, 0,
                         SWP_NOSIZE);
            if (n == _primary_screen_adpter_no) {
                SetCursorPos(full_screen_x, full_screen_y);
            }
        }
    } else { //TODO:��ƗZ��������
        for (int n = 0; n < _num_adapter; n++) {
            if (n == _primary_screen_adpter_no) {
                pixcoord full_screen_x = _paAvailableAdapter[n].rcMonitor.left;
                pixcoord full_screen_y = _paAvailableAdapter[n].rcMonitor.top;
                _TRACE_("��� adapter_no="<<n<<" �̍�����W("<<full_screen_x<<","<<full_screen_y<<")");
                ShowWindow(_paHWnd[n], SW_SHOWNORMAL);
                UpdateWindow(_paHWnd[n]);
                SetWindowPos(_paHWnd[n],
                             HWND_TOPMOST,
                             full_screen_x, full_screen_y, 0, 0,
                             SWP_NOSIZE);
                SetCursorPos(full_screen_x, full_screen_y);
                break;
            }
        }
    }
}
void Caretaker::resetDotByDotWindowsize(int d) {
    if (!CONFIG::FULL_SCREEN) {
        for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            int wno = _screen_display_no[pry];
            resetWindowsize(_paHWnd[wno], CONFIG::RENDER_TARGET_BUFFER_WIDTH/CONFIG::NUMBER_OF_SCREENS_USED*d, CONFIG::RENDER_TARGET_BUFFER_HEIGHT*d);
        }
    }
}
void Caretaker::resetInitWindowsize() {
    //�����E�B���h�E�T�C�Y�Ƀ��Z�b�g
    if (!CONFIG::FULL_SCREEN) {
        for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            int wno = _screen_display_no[pry];
            resetWindowsize(_paHWnd[wno],
                            CONFIG::SCREEN_WINDOW[pry].WIDTH, CONFIG::SCREEN_WINDOW[pry].HEIGHT);
        }
    }
}
void Caretaker::resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height) {
    RECT wRect1, cRect1; // �E�B���h�E�S�̂̋�`�A�N���C�A���g�̈�̋�`
    pixcoord ww1, wh1; // �E�B���h�E�S�̂̕��A����
    pixcoord cw1, ch1; // �N���C�A���g�̈�̕��A����
    pixcoord fw1, fh1; // �t���[���̕��A����
    // �E�B���h�E�S�̂̕��E�������v�Z
    GetWindowRect(hWnd, &wRect1);
    ww1 = wRect1.right - wRect1.left;
    wh1 = wRect1.bottom - wRect1.top;
    // �N���C�A���g�̈�̕��E�������v�Z
    GetClientRect(hWnd, &cRect1);
    cw1 = cRect1.right - cRect1.left;
    ch1 = cRect1.bottom - cRect1.top;
    // �N���C�A���g�̈�ȊO�ɕK�v�ȃT�C�Y���v�Z
    fw1 = ww1 - cw1;
    fh1 = wh1 - ch1;
    // �v�Z�������ƍ������E�B���h�E�ɐݒ�
    SetWindowPos(
            hWnd,
            HWND_TOP,
            0,
            0,
            client_width + fw1,
            client_height + fh1,
            SWP_NOMOVE
    );
}

void Caretaker::chengeScreenPresentPos(HWND prm_pHWnd, int pos) {
    if (!CONFIG::FULL_SCREEN) {
        int pry = _mapHwndToPry[prm_pHWnd];
        CONFIG::SCREEN_PRESENT_POSITION[pry] = pos;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengePrimaryScreenPresentPos(int pos) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::SCREEN_PRESENT_POSITION[SCREEN01] = pos;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengeSecondaryScreenPresentPos(int pos) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::SCREEN_PRESENT_POSITION[SCREEN02] = pos;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengeViewAspect(HWND prm_pHWnd, bool prm_b) {
    if (!CONFIG::FULL_SCREEN) {
        int pry = _mapHwndToPry[prm_pHWnd];
        CONFIG::SCREEN_ASPECT_RATIO_FIXED[pry] = prm_b;
        _adjustGameWindow = true;
    }
}

void Caretaker::chengeViewAspect1(bool prm_b) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN01] = prm_b;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengeViewAspect2(bool prm_b) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::SCREEN_ASPECT_RATIO_FIXED[SCREEN02] = prm_b;
        _adjustGameWindow = true;
    }
}

void Caretaker::setDisplaySizeInfo() {
    //�A�_�v�^���i�[
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        _paAvailableAdapter[adapter_no].hMonitor = _pID3D9->GetAdapterMonitor(adapter_no);
        int mode_num = _pID3D9->GetAdapterModeCount(adapter_no, D3DFMT_X8R8G8B8);
        _paAvailableAdapter[adapter_no].setModeNum(mode_num);
        D3DDISPLAYMODE* paMode = _paAvailableAdapter[adapter_no].paModes;
        for (int n = 0; n < mode_num; n++) {
            _pID3D9->EnumAdapterModes(adapter_no, D3DFMT_X8R8G8B8, n, &(paMode[n]));
        }
    }

    //�𑜓x���i�[
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        std::vector<UINT> vecWidth;
        std::vector<UINT> vecHeight;
        std::vector<std::string> vecRezo;
        int mode_num = _paAvailableAdapter[adapter_no].mode_num;
        D3DDISPLAYMODE* paMode = pCARETAKER->_paAvailableAdapter[adapter_no].paModes;
        _TRACE_("���["<<adapter_no<<"] mode_num="<<mode_num);
        for (int n = 0; n < mode_num; n++) {
            UINT width = paMode[n].Width;
            UINT height = paMode[n].Height;
            D3DFORMAT format = paMode[n].Format;
            std::ostringstream oss;
            oss << width << "X" << height;
            std::string rezo = oss.str();
            if (std::find(vecRezo.begin(), vecRezo.end(), rezo) == vecRezo.end()) {
                vecRezo.push_back(rezo);
                vecWidth.push_back(width);
                vecHeight.push_back(height);
            }
        }
        _paAdapterRezos[adapter_no].init(vecRezo.size());
        for (int n = 0; n < vecRezo.size(); n++) {
            //���݂��Ă��Ȃ�
            _paAdapterRezos[adapter_no].paRezoInfo[n].width = vecWidth[n];
            _paAdapterRezos[adapter_no].paRezoInfo[n].height = vecHeight[n];
            _paAdapterRezos[adapter_no].paRezoInfo[n].item_str = vecRezo[n];
        }
    }

    _TRACE_("���p�\��ʉ𑜓x�ꗗ");
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        for (int n = 0; n < _paAdapterRezos[adapter_no].rezo_num; n++) {
            RezoInfo* pMode = _paAdapterRezos[adapter_no].paRezoInfo;
            _TRACE_("["<<adapter_no<<"]["<<n<<"]="<<(pMode[n].width)<<","<<(pMode[n].height)<<" = "<<(pMode[n].item_str));
        }
    }
    _TRACE_("------------------------------------------------");
}
void Caretaker::setAppropriateDisplaySize(bool allow_chang_rezo) {
    //�t���X�N���[���v�����A�w��𑜓x�ɏo���邩���ׁA
    //�o���Ȃ��ꍇ�́A�߂��𑜓x��T���A
    //_paPresetPrm[] �ƁA_paDisplayMode[] ���㏑������B
    EnumDisplayMonitors(nullptr, nullptr, Caretaker::updateMoniterPixcoordCallback, (LPARAM)this);
    HRESULT hr;
    if (CONFIG::FULL_SCREEN) {
        for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
            _TRACE_("--- " << adapter_no+1 << "��ʖ� �̉𑜓x�ݒ� --->");
            int rezo_num = _paAdapterRezos[adapter_no].rezo_num;
            RezoInfo* paRezos = _paAdapterRezos[adapter_no].paRezoInfo;
            int pry = _paWindowNoToScreenPry[adapter_no];
            if (pry >= 0) {
                if (allow_chang_rezo && CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH > 0) {
                    //�𑜓x�ύX����
                    _TRACE_("�𑜓x�ύX���܂��B");
                    int n = checkAppropriateDisplaySize(
                                paRezos, rezo_num,
                                (UINT)CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH,
                                (UINT)CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT
                            );
                    CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH = (pixcoord)(paRezos[n].width);
                    CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT = (pixcoord)(paRezos[n].height);
                } else {
                    //�𑜓x�ύX����
                    //�iallow_chang_rezo == false �܂��́ASCREEN_FULL_SCREEN.WIDTH �� 0 �̏ꍇ�A���݂̃��j�^�𑜓x�ōs���j
                    _TRACE_("�𑜓x�ύX�����ݒ�ł��B");
                    D3DDISPLAYMODE structD3DDisplayMode0;
                    hr = _pID3D9->GetAdapterDisplayMode(adapter_no, &structD3DDisplayMode0);
                    checkDxException(hr, D3D_OK, "GetAdapterDisplayMode �Ɏ��s���܂����B5");
                    CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH  = (pixcoord)(structD3DDisplayMode0.Width);
                    CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT = (pixcoord)(structD3DDisplayMode0.Height);
                }
                _paPresetPrm[adapter_no].BackBufferWidth  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _paPresetPrm[adapter_no].BackBufferHeight = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            } else {
                //�f��Ȃ��_�~�[���
                //�����F�Q�[����ʂR��ʖڈȍ~�P��ʖځE�Q��ʖڂ̉𑜓x�́A����̉𑜓x�����̂܂ܐݒ�B
                D3DDISPLAYMODE structD3DDisplayMode;
                hr = _pID3D9->GetAdapterDisplayMode(adapter_no, &structD3DDisplayMode);
                _paPresetPrm[adapter_no].BackBufferWidth  = (pixcoord)(structD3DDisplayMode.Width);
                _paPresetPrm[adapter_no].BackBufferHeight = (pixcoord)(structD3DDisplayMode.Height);
                checkDxException(hr, D3D_OK, "GetAdapterDisplayMode �Ɏ��s���܂����B4");
                _TRACE_("�f��Ȃ��_�~�[��ʂ́A����� "<<
                        _paPresetPrm[adapter_no].BackBufferWidth<<"x"<<_paPresetPrm[adapter_no].BackBufferHeight<<" �ɐݒ�");
            }
            //D3DDISPLAYMODEEX�㏑���X�V
            _paDisplayMode[adapter_no].Width  = _paPresetPrm[adapter_no].BackBufferWidth;
            _paDisplayMode[adapter_no].Height = _paPresetPrm[adapter_no].BackBufferHeight;
            _TRACE_("<---" << adapter_no+1 << "��ʖڂ̉𑜓x�́A"<<_paDisplayMode[adapter_no].Width<<"x"<<_paDisplayMode[adapter_no].Height<<"�Ɋm�肵�܂����B");
        }
    }

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
    _rectGameBuffer.right  = _rectGameBuffer.left + CONFIG::GAME_BUFFER_WIDTH;
    _rectGameBuffer.bottom = _rectGameBuffer.top  + CONFIG::GAME_BUFFER_HEIGHT;

    for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
        _aRectRenderBufferSource[pry].left   = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT;
        _aRectRenderBufferSource[pry].top    = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP;
        _aRectRenderBufferSource[pry].right  = _aRectRenderBufferSource[pry].left + CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH;
        _aRectRenderBufferSource[pry].bottom = _aRectRenderBufferSource[pry].top  + CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT;
    }

    //�\���̈�ݒ�
    if (CONFIG::FULL_SCREEN) {

        for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            //�t���X�N���[�����[�h�g�p
            _aRect_FullScreen[pry].top    = 0;
            _aRect_FullScreen[pry].left   = 0;
            _aRect_FullScreen[pry].right  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
            _aRect_FullScreen[pry].bottom = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;

            //�u�t���X�N���[�����[�h�g�p�ERENDER_TARGET_BUFFER�T�C�Y�����v
            if (CONFIG::SCREEN_ASPECT_RATIO_FIXED[pry]) {
                //�u�t���X�N���[�����[�h�g�p�E�c����FIX�v�̃t�����g�o�b�t�@�`��̈�
                LONG fix_width  = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  * CONFIG::SCREEN_RATIO[pry].WIDTH;
                LONG fix_height = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT * CONFIG::SCREEN_RATIO[pry].HEIGHT;
                if (1.0f * CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH / CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[pry].left   = (CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[pry].top    = 0;
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH / fix_width; //�k����=�����̔䗦
                    _aRect_Present[pry].left   = 0;
                    _aRect_Present[pry].top    = (CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                }
                setPositionPresentRect(CONFIG::SCREEN_PRESENT_POSITION[pry], _aRect_Present[pry],
                                       CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH, CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT);
            } else {
                //�u�t���X�N���[�����[�h�g�p�E�c����X�g���b�`�v�̃t�����g�o�b�t�@�`��̈�
                _aRect_Present[pry].left   = 0;
                _aRect_Present[pry].top    = 0;
                _aRect_Present[pry].right  = _aRect_Present[pry].left + CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _aRect_Present[pry].bottom = _aRect_Present[pry].top  + CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            }
        }

    } else {
        //�E�B���h�E���[�h
        for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            //�E�B���h�E���[�h�g�p
            if (CONFIG::SCREEN_ASPECT_RATIO_FIXED[pry]) {
                //�u�E�B���h�E���[�h�g�p�E�c����FIX�v�̃t�����g�o�b�t�@�`��̈�
                LONG fix_width  = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  * CONFIG::SCREEN_RATIO[pry].WIDTH;
                LONG fix_height = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT * CONFIG::SCREEN_RATIO[pry].HEIGHT;
                if (1.0f * CONFIG::SCREEN_WINDOW[pry].WIDTH / CONFIG::SCREEN_WINDOW[pry].HEIGHT > 1.0f * fix_width / fix_height) {
                    //��艡���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CONFIG::SCREEN_WINDOW[pry].HEIGHT / fix_height; //�k����=�c���̔䗦
                    _aRect_Present[pry].left   = (CONFIG::SCREEN_WINDOW[pry].WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[pry].top    = 0;
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                } else {
                    //���c���ɂȂ��Ă��܂��Ă���
                    double rate = 1.0 * CONFIG::SCREEN_WINDOW[pry].WIDTH / fix_width; //�k����=�����̔䗦
                    _aRect_Present[pry].left   = 0;
                    _aRect_Present[pry].top    = (CONFIG::SCREEN_WINDOW[pry].HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                }
                setPositionPresentRect(CONFIG::SCREEN_PRESENT_POSITION[pry], _aRect_Present[pry],
                                       CONFIG::SCREEN_WINDOW[pry].WIDTH, CONFIG::SCREEN_WINDOW[pry].HEIGHT);
            } else {
                //�u�E�B���h�E���[�h�g�p�E�c����X�g���b�`�v�̃t�����g�o�b�t�@�`��̈�
                _aRect_Present[pry].left   = 0;
                _aRect_Present[pry].top    = 0;
                _aRect_Present[pry].right  = _aRect_Present[pry].left + CONFIG::SCREEN_WINDOW[SCREEN01].WIDTH;
                _aRect_Present[pry].bottom = _aRect_Present[pry].top  + CONFIG::SCREEN_WINDOW[SCREEN01].HEIGHT;
            }
        }
    }

#ifdef MY_DEBUG
    _TRACE_("�����ݒ�");
    _TRACE_(" _primary_screen_adpter_no = "<<_primary_screen_adpter_no );
    for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
        _TRACE_(" _aRectRenderBufferSource["<<pry<<"].left   = "<<_aRectRenderBufferSource[pry].left  );
        _TRACE_(" _aRectRenderBufferSource["<<pry<<"].top    = "<<_aRectRenderBufferSource[pry].top   );
        _TRACE_(" _aRectRenderBufferSource["<<pry<<"].right  = "<<_aRectRenderBufferSource[pry].right );
        _TRACE_(" _aRectRenderBufferSource["<<pry<<"].bottom = "<<_aRectRenderBufferSource[pry].bottom);
        _TRACE_(" _aRect_Present["<<pry<<"].left   = "<<_aRect_Present[pry].left  );
        _TRACE_(" _aRect_Present["<<pry<<"].top    = "<<_aRect_Present[pry].top   );
        _TRACE_(" _aRect_Present["<<pry<<"].right  = "<<_aRect_Present[pry].right );
        _TRACE_(" _aRect_Present["<<pry<<"].bottom = "<<_aRect_Present[pry].bottom);
    }
#endif
}


int Caretaker::checkAppropriateDisplaySize(Caretaker::RezoInfo* prm_paRezos, int prm_rezo_num,
                                           UINT prm_width, UINT prm_height) {
    _TRACE_("checkAppropriateDisplaySize() ���]�𑜓x�A"<<prm_width<<"x"<<prm_height);

    for (int n = 0; n < prm_rezo_num; n++) {
        if (prm_width == prm_paRezos[n].width && prm_height == prm_paRezos[n].height) {
            _TRACE_("checkAppropriateDisplaySize() ["<<n<<"] ��BINGO!");
            return n; //�҂�����
        }
    }
    _TRACE_("BINGO�Ȃ��A�߂��𑜓x��T���܂��B");
    int cfg_width  = (int)(prm_width * 1.1);  //�𑜓x�̍����������I�����₷�����邽��
    int cfg_height = (int)(prm_height * 1.1); //10%������
    double cfg_aspect = 1.0 * cfg_width / cfg_height;

    int eval_top = INT_MAX; //�]��(�������قǗǂ�)
    int resut_index = 0;
    for (int n = 0; n < prm_rezo_num; n++) {
        int disp_width  = (int)(prm_paRezos[n].width);
        int disp_height = (int)(prm_paRezos[n].height);
        int eval_level = ABS(disp_width-cfg_width) + (int)(ABS(disp_height-cfg_height) * cfg_aspect * 1.5); //�A�X�y�N�g������d���̂���1.5�{
        _TRACE_("checkAppropriateDisplaySize() ["<<n<<"] "<<disp_width<<"x"<<disp_height<<" �E�E�E �]���F"<<eval_level);
        if (eval_level < eval_top) {
            eval_top = eval_level;
            resut_index = n;
        }
    }
    _TRACE_("checkAppropriateDisplaySize() ���_�A["<<resut_index<<"] �� "<<
            prm_paRezos[resut_index].width<<"x"<<prm_paRezos[resut_index].height<<" ���ǂ�������Ȃ�����I");
    return resut_index;
}


HRESULT Caretaker::releaseFullScreenRenderTarget() {
    GGAF_RELEASE_BY_FROCE(_pRenderTextureSurface);
    GGAF_RELEASE_BY_FROCE(_pRenderTextureZ);
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        IDirect3DSurface9* p1 = _papBackBuffer[adapter_no];
        GGAF_RELEASE_BY_FROCE(p1);
        IDirect3DSwapChain9* p2 = _papSwapChain[adapter_no];
        GGAF_RELEASE_BY_FROCE(p2);
    }
    return D3D_OK;
}

void Caretaker::chengeToBorderlessFullWindow(HWND prm_pHWnd) {
    LONG lStyle  = GetWindowLong( prm_pHWnd, GWL_STYLE );
    lStyle &= ~WS_OVERLAPPEDWINDOW;
    lStyle |= WS_POPUP;
    lStyle  = SetWindowLong( prm_pHWnd, GWL_STYLE, lStyle );
    SetWindowPos( prm_pHWnd, NULL, 0, 0, 0, 0, (SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED) );
    Sleep(1);
    ShowWindow(prm_pHWnd, SW_SHOWMAXIMIZED );
    UpdateWindow(prm_pHWnd);
    Sleep(1);
    ShowWindow(prm_pHWnd, SW_NORMAL );
    UpdateWindow(prm_pHWnd);
    Sleep(1);
    ShowWindow(prm_pHWnd, SW_SHOWMAXIMIZED );
    UpdateWindow(prm_pHWnd);
    _adjustGameWindow = true;
}

void Caretaker::backToNomalWindow(HWND prm_pHWnd) {

    LONG lStyle  = GetWindowLong( prm_pHWnd, GWL_STYLE );
    lStyle &= ~WS_POPUP;
    lStyle |= WS_OVERLAPPEDWINDOW;
    lStyle  = SetWindowLong( prm_pHWnd, GWL_STYLE, lStyle );
    SetWindowPos( prm_pHWnd, NULL, 0, 0, 0, 0, (SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED) );
    ShowWindow(prm_pHWnd, SW_NORMAL);
    UpdateWindow(prm_pHWnd);
    _adjustGameWindow = true;
}

void Caretaker::presentMoment() {
#ifdef MY_DEBUG
    if (GgafDx::Input::isPushedDownKey(DIK_T)) {
        _TRACE_("�c���[�\�� -->");
        _pSpacetime->dump();
        _TRACE_("<-- �c���[�\��");
    }

#endif

    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentMoment();
    }
}
void Caretaker::presentBehave() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentBehave();
    }
}
void Caretaker::presentJudge() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentJudge();
    }
}
void Caretaker::presentMaterialize() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    }
    IDirect3DDevice9* pDevice = _pID3DDevice9;
    HRESULT hr;
    //�ʏ펞����
    //�o�b�t�@�N���A
    hr = pDevice->Clear(0, // �N���A�����`�̈�̐�
                        nullptr, // ��`�̈�
                        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                        _color_clear, //�N���A�F�inot �w�i�F�j
                        1.0f,         // Z�o�b�t�@�̃N���A�l
                        0             // �X�e���V���o�b�t�@�̃N���A�l
                       );
    checkDxException(hr, D3D_OK, "pDevice->Clear() �Ɏ��s���܂����B");

    //�`�掖�O����
    hr = pDevice->BeginScene();
    checkDxException(hr, D3D_OK, "pDevice->BeginScene() �Ɏ��s���܂����B");
    //�S�ċ���I�i�`��j
#ifdef MY_DEBUG
    pDevice->SetRenderState(D3DRS_FILLMODE, pCARETAKER->_d3dfillmode);
#endif
    GgafCore::Caretaker::presentMaterialize(); //�X�[�p�[��materialize���s
    //�`�掖�㏈��
    hr = pDevice->EndScene();
    checkDxException(hr, D3D_OK, "pDevice->EndScene() �Ɏ��s���܂����B");

}

void Caretaker::presentVisualize() {
    IDirect3DDevice9* pDevice = _pID3DDevice9;
    //�����A������
    //if (_pID3DDevice9->Present(nullptr,&_aRect_Present[SCREEN01],nullptr,nullptr) == D3DERR_DEVICELOST) {
    //        static D3DRASTER_STATUS rs;
    //        while (SUCCEEDED(_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
    //            if(rs.InVBlank) {
    //                break; //�����A�����Ԃł͂Ȃ�
    //            } else {
    //                Sleep(1);
    //            }
    //        }
    HRESULT hr;
    if (pCARETAKER->_is_device_lost_flg == false) {
        if (_adjustGameWindow) {
            adjustGameWindow();
        }
        //Present
        if (CONFIG::FULL_SCREEN) {
            //�t���X�N���[��
            for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
                int wno = _screen_display_no[pry];
                hr = pDevice->StretchRect(
                        _pRenderTextureSurface, &_aRectRenderBufferSource[pry],
                        _papBackBuffer[wno], &_aRect_Present[pry],
                        D3DTEXF_LINEAR);
            }
            hr = pDevice->Present(nullptr, nullptr, nullptr, nullptr);
        } else {
            //�E�B���h�E���[�h
            for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
                int wno = _screen_display_no[pry];
                hr = pDevice->Present(&_aRectRenderBufferSource[pry], &_aRect_Present[pry], _paHWnd[wno], nullptr);
            }
        }
//        if (hr == S_PRESENT_OCCLUDED) {
//            _TRACE_("�y���zPresent �� HRESULT = S_PRESENT_OCCLUDED ");
//            Sleep(10);
//        }
        //S_PRESENT_OCCLUDED�͏��O
//        if (hr != S_PRESENT_OCCLUDED && hr != D3D_OK) { //hr �� Present �̖߂�l
        if (hr != D3D_OK) { //hr �� Present �̖߂�l
            pCARETAKER->syncTimeFrame();
//            _TRACE_("�y�x���z�f�o�C�X�ُ픭��!!" <<DXGetErrorString(hr) << " "<< DXGetErrorDescription(hr));
            _TRACE_("�y�x���z�f�o�C�X�ُ픭��!! HRESULT=0x"<<UTIL::dec2hex(hr,8)<<"("<<hr<<")");
            if (hr == D3DERR_DEVICELOST) {
                _TRACE_("�y���z�ʏ�̃f�o�C�X���X�g D3DERR_DEVICELOST");
            } else if (hr == S_PRESENT_OCCLUDED) {
                _TRACE_("�y���zPresent �̈悪����܂���BHRESULT = S_PRESENT_OCCLUDED ");
            } else {
                _TRACE_("�y���z�ʏ�̃f�o�C�X���X�g�ł͂Ȃ������H�I");
            }

            Sleep(10);
            _TRACE_("�y�f�o�C�X���X�g�����zBEGIN ------>");
            //�Ǘ��҂̈��A��~
            _TRACE_("�y�f�o�C�X���X�g�����z�Ǘ��҂̈��A��~ BEGIN ------>");
            GgafCore::Caretaker::beginRest();
            for (int i = 0; GgafCore::Caretaker::isResting() == false; i++) {
                Sleep(10); //�������������܂ő҂�
                if (i > 10*60*100) {
                    _TRACE_("�y�f�o�C�X���X�g����/����~�z 10���ҋ@���܂������A�����甽��������܂���B����break���܂��B�v����");
                    break;
                }
            }
            BEGIN_SYNCHRONIZED1; // ----->�r���J�n
            _TRACE_("�y�f�o�C�X���X�g�����z�Ǘ��҂̈��A��~ <-------- END");

            _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X��� BEGIN ------>");

            //�����_�����O�^�[�Q�b�g�A�f�o�C�X���X�g����
            if (CONFIG::FULL_SCREEN) {
                releaseFullScreenRenderTarget();
            }
            //�G�t�F�N�g�A�f�o�C�X���X�g����
            _TRACE_("�y�f�o�C�X���X�g�����z_pEffectManager->onDeviceLostAll() BEGIN ------>");
            _pEffectManager->onDeviceLostAll();
            _TRACE_("�y�f�o�C�X���X�g�����z_pEffectManager->onDeviceLostAll() <-------- END");
            //���f�����
            _TRACE_("�y�f�o�C�X���X�g�����z_pModelManager->onDeviceLostAll() BEGIN ------>");
            _pModelManager->onDeviceLostAll();
            _TRACE_("�y�f�o�C�X���X�g�����z_pModelManager->onDeviceLostAll() <-------- END");
            //�e�N�X�`���i���f�����琶������ĂȂ��e�N�X�`���j�A�f�o�C�X���X�g�����B����̓��f������ɊJ������K�v������B
            _TRACE_("�y�f�o�C�X���X�g�����z_pTextureManager->releaseAll() (���f�����琶������ĂȂ��e�N�X�`��) BEGIN ------>");
            _pTextureManager->releaseAll();
            _TRACE_("�y�f�o�C�X���X�g�����z_pTextureManager->releaseAll() (���f�����琶������ĂȂ��e�N�X�`��) <-------- END");
            //�S�m�[�h�ɉ�����Ȃ����C�x���g����
            _TRACE_("�y�f�o�C�X���X�g�����zgetSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST) BEGIN ------>");
            getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST);
            _TRACE_("�y�f�o�C�X���X�g�����zgetSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST) <-------- END");
            _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X��� <-------- END");
            pCARETAKER->_is_device_lost_flg = true;
            _sync_frame_time = true;
            END_SYNCHRONIZED1; // <----- �r���I��
        }
    }

    if (pCARETAKER->_is_device_lost_flg) {
        _TRACE_("�y�f�o�C�X���X�g����/���\�[�X����z���������x���`�F�b�N���E�E�E BEGIN ------>");
        _sync_frame_time = true;
        Sleep(10);
        //for (int i = 0; i < 300; i++) {
        while (true) {
            if (_can_wddm) {
                hr = ((IDirect3DDevice9Ex*)pDevice)->CheckDeviceState(_paPresetPrm[_primary_screen_adpter_no].hDeviceWindow);
                if (hr == D3DERR_DEVICELOST || hr == S_PRESENT_OCCLUDED) {
                    return; //D3DERR_DEVICELOST ����Ȃ��Ȃ�܂ő҂�
                } else {
                    break;
                }
            } else {
                hr = pDevice->TestCooperativeLevel();
                if (hr == D3DERR_DEVICELOST) {
                    return; //D3DERR_DEVICELOST ����Ȃ��Ȃ�܂ő҂�
                } else {
                    break;
                }
            }
        }
        _TRACE_("�y�f�o�C�X���X�g����/���\�[�X����z���������x���`�F�b�N <-------- END");

        BEGIN_SYNCHRONIZED1; // ----->�r���J�n
        //�𑜓x�ύX���l��
        if (CONFIG::FULL_SCREEN) {
            //��U�߂�
            for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
                CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH = CONFIG::SCREEN_FULL_SCREEN_BK[pry].WIDTH;
                CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT = CONFIG::SCREEN_FULL_SCREEN_BK[pry].HEIGHT;
            }
            pCARETAKER->setDisplaySizeInfo();
            pCARETAKER->setAppropriateDisplaySize(false);
            //checkAppropriateDisplaySize() �ɂ��𑜓x�ύX�͂��Ȃ�
            //���R�F��ʃ��[�e�[�g�ŉ𑜓x��ύX���ꂽ�ꍇ�A
            //���̉𑜓x���� CONFIG�̉𑜓x�ցA�X�ɉ𑜓x��ύX���悤�Ƃ����
            //�A�v���I�����ɕύX��̉𑜓x�̂܂܎c�邽�߁H

            //�o�b�N�o�b�t�@�T�C�Y
            for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
                int wno = _screen_display_no[pry];
                _paPresetPrm[wno].BackBufferWidth  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _paPresetPrm[wno].BackBufferHeight = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            }
            //����restoreFullScreenRenderTarget() �Ŏ����悤�Ȃ��Ƃ�����Ă�̂ł���񂩂�
            for (int pry = SCREEN01; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
                int wno = _screen_display_no[pry];
                if (_paHWnd[wno]) {
                    SetWindowPos(_paHWnd[wno], NULL, 0, 0,
                            _paPresetPrm[wno].BackBufferWidth,
                            _paPresetPrm[wno].BackBufferHeight,
                            SWP_NOMOVE | SWP_NOZORDER);
                }
            }
        }
        //�f�o�C�X���Z�b�g�����݂�
        _TRACE_("�y�f�o�C�X���X�g�����z�f�o�C�X���Z�b�g BEGIN ------>");
        for (int i = 0; i < 100*60*10; i++) {
            if (CONFIG::FULL_SCREEN && Config::NUMBER_OF_SCREENS_USED > 1) {
                hr = pDevice->Reset(_paPresetPrm);
            } else {
                hr = pDevice->Reset(&(_paPresetPrm[_primary_screen_adpter_no]));
            }
            if (hr != D3D_OK) {
                if (hr == D3DERR_DRIVERINTERNALERROR) {
                    Sleep(10);
                    return;
                } else if (hr == D3DERR_DRIVERINTERNALERROR) {
                    throwCriticalDxException(hr, "�y�f�o�C�X���X�g����/�f�o�C�X���Z�b�g�zD3DERR_DRIVERINTERNALERROR�B�����I�����܂��B");
                } else if (hr == D3DERR_OUTOFVIDEOMEMORY) {
                    throwCriticalDxException(hr, "�y�f�o�C�X���X�g����/�f�o�C�X���Z�b�g�zD3DERR_OUTOFVIDEOMEMORY�B������������܂���B�����I�����܂��B");
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

        if (CONFIG::FULL_SCREEN) {
            _TRACE_("�y�f�o�C�X���X�g�����z�t���X�N���[���������_�����O�^�[�Q�b�g�e�N�X�`���č\�z BEGIN ------>");
            restoreFullScreenRenderTarget();
            _TRACE_("�y�f�o�C�X���X�g�����z�t���X�N���[���������_�����O�^�[�Q�b�g�e�N�X�`���č\�z <-------- END");
        }

        //���\�[�X�č\�z
        _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X�č\�z BEGIN ------>");
        //�e�N�X�`���i���f������̃e�N�X�`���ȊO�j�Đݒ�i����̓��f�������restoreAll()����K�v������j
        _TRACE_("�y�f�o�C�X���X�g�����z_pTextureManager->restoreAll() (���f�����琶������ĂȂ��e�N�X�`��) BEGIN ------>");
        _pTextureManager->restoreAll();
        _TRACE_("�y�f�o�C�X���X�g�����z_pTextureManager->restoreAll() (���f�����琶������ĂȂ��e�N�X�`��) <-------- END");
        //�G�t�F�N�g���Z�b�g
        _TRACE_("�y�f�o�C�X���X�g�����z_pEffectManager->restoreAll() BEGIN ------>");
        _pEffectManager->restoreAll();
        _TRACE_("�y�f�o�C�X���X�g�����z_pEffectManager->restoreAll() <-------- END");
        //���f���Đݒ�
        _TRACE_("�y�f�o�C�X���X�g�����z_pModelManager->restoreAll() BEGIN ------>");
        _pModelManager->restoreAll();
        _TRACE_("�y�f�o�C�X���X�g�����z_pModelManager->restoreAll() <-------- END");

        //�S�m�[�h�ɍĐݒ肵�Ȃ����C�x���g����
        _TRACE_("�y�f�o�C�X���X�g�����zgetSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST_RESTORE) BEGIN ------>");
        getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST_RESTORE);
        _TRACE_("�y�f�o�C�X���X�g�����zgetSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST_RESTORE) <-------- END");
        //�O��`�惂�f�����𖳌��ɂ���
        ModelManager::_pModelLastDraw = nullptr;
        pCARETAKER->_is_device_lost_flg = false;
        _TRACE_("�y�f�o�C�X���X�g�����z���\�[�X�č\�z <-------- END");
        END_SYNCHRONIZED1; // <----- �r���I��
        //�Ǘ��҂̈��ĊJ
        _TRACE_("�y�f�o�C�X���X�g�����z�Ǘ��҂̈��A�ċN�� BEGIN ------>");
        GgafCore::Caretaker::finishRest();
        _TRACE_("�y�f�o�C�X���X�g�����z�Ǘ��҂̈��A�ċN�� <-------- END");

        _TRACE_("�y�f�o�C�X���X�g�����z<-------- END");

        Sleep(100);

        hr = pDevice->Clear(0,    // �N���A�����`�̈�̐�
                            nullptr, // ��`�̈�
                            D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                            _color_border, //�w�i�F      //D3DCOLOR_XRGB( 0, 0, 0 )
                            1.0f, // Z�o�b�t�@�̃N���A�l
                            0     // �X�e���V���o�b�t�@�̃N���A�l
                           );

    }
}

void Caretaker::presentClosing() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentClosing();
    }
}

void Caretaker::setLightDiffuseColor(float r, float g, float b) {
    _d3dlight9_default.Diffuse.r = r;
    _d3dlight9_default.Diffuse.g = g;
    _d3dlight9_default.Diffuse.b = b;
    //_d3dlight9_default.Range = 1000.0f;

}
void Caretaker::setLightAmbientColor(float r, float g, float b) {
    _d3dlight9_default.Ambient.r = r;
    _d3dlight9_default.Ambient.g = g;
    _d3dlight9_default.Ambient.b = b;
}

void Caretaker::clean() {
    _TRACE_(FUNC_NAME<<" begin");
    if (!_was_cleaned) {
        IDirect3DDevice9* pDevice = _pID3DDevice9;
        if (pDevice) {
            for (int i = 0; i < 8; ++i) { pDevice->SetTexture( i, nullptr ); }
            for (int i = 0; i < 8; ++i) { pDevice->SetStreamSource( i, nullptr, 0, 0 ); }
            pDevice->SetIndices( nullptr );
            pDevice->SetPixelShader( nullptr );
            pDevice->SetVertexShader( nullptr );
            pDevice->SetVertexDeclaration( nullptr );
        }
        _TRACE_(FUNC_NAME<<" GgafCore::Caretaker::clean() �J�n");
        GgafCore::Caretaker::clean();
        _TRACE_(FUNC_NAME<<" GgafCore::Caretaker::clean() �I��");
        GgafCore::CmRandomNumberGenerator::getInstance()->release();
        //�ێ����f�����

        _TRACE_(FUNC_NAME<<" _pModelManager �J���J�n");
        GGAF_DELETE(_pModelManager);
        _TRACE_(FUNC_NAME<<" _pModelManager �J���I��");

        _TRACE_(FUNC_NAME<<" _pTextureManager(���f�����琶������ĂȂ��e�N�X�`��) �J���J�n");
        GGAF_DELETE(_pTextureManager);
        _TRACE_(FUNC_NAME<<" _pTextureManager(���f�����琶������ĂȂ��e�N�X�`��) �J���I��");

        _TRACE_(FUNC_NAME<<" _pEffectManager �J���J�n");
        GGAF_DELETE(_pEffectManager);
        _TRACE_(FUNC_NAME<<" _pModelManager �J���I��");


        _TRACE_(FUNC_NAME<<" _pCurveSrcManager �J���J�n");
        GGAF_DELETE(_pCurveSrcManager);
        _TRACE_(FUNC_NAME<<" _pCurveSrcManager �J���I��");

        _TRACE_(FUNC_NAME<<" _pCurveManufManager �J���J�n");
        GGAF_DELETE(_pCurveManufManager);
        _TRACE_(FUNC_NAME<<" _pCurveManufManager �J���I��");
    }
    _TRACE_(FUNC_NAME<<" end");
}

//void Caretaker::adjustGameWindow(HWND prm_pHWnd) {
void Caretaker::adjustGameWindow() {
    if (!CONFIG::FULL_SCREEN ) {
        //�E�B���h�E���[�h��
        HRESULT hr;
        hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
        for (int wno = 0; wno < _num_window; wno++) {
            hr = _pID3DDevice9->Present(nullptr, nullptr, _paHWnd[wno], nullptr);
        }

        for (int wno = 0; wno < _num_window; wno++) {
            int pry = _paWindowNoToScreenPry[wno]; //�E�B���h�E���[�h���͕K�� pry >= 0
            RECT rect;
            if (::GetClientRect(_paHWnd[wno], &rect)) {
                LONG c_width= rect.right;
                LONG c_height = rect.bottom;
                LONG fix_width, fix_height;
                int pos = CONFIG::SCREEN_PRESENT_POSITION[pry];
//                if (_paHWnd[wno] == _pHWndPrimary) {
//                     pos = CONFIG::SCREEN01_PRESENT_POSITION;
//                } else if (_paHWnd[wno] == _pHWndSecondary) {
//                     pos = CONFIG::SCREEN02_PRESENT_POSITION;
//                }
                if (CONFIG::SCREEN_ASPECT_RATIO_FIXED[pry]) {
                    //�E�B���h�E���[�h���E�A�X�y�N�g��Œ�
                    fix_width  = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  * CONFIG::SCREEN_RATIO[pry].WIDTH;
                    fix_height = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT * CONFIG::SCREEN_RATIO[pry].HEIGHT;

                    if (1.0f * c_width / c_height > 1.0f * fix_width / fix_height) {
                        //��艡���ɂȂ��Ă��܂��Ă���
                        double rate = 1.0 * c_height / fix_height; //�k����=�c���̔䗦
                        _aRect_Present[pry].left   = (c_width / 2.0) - (fix_width * rate / 2.0);
                        _aRect_Present[pry].top    = 0;
                        _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                        _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                        setPositionPresentRect(pos, _aRect_Present[pry], c_width, c_height);
                    } else {
                        //���c���ɂȂ��Ă��܂��Ă���
                        double rate = 1.0 * c_width / fix_width; //�k����=�����̔䗦
                        _aRect_Present[pry].left   = 0;
                        _aRect_Present[pry].top    = (c_height / 2.0) - (fix_height * rate / 2.0);
                        _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                        _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                        setPositionPresentRect(pos, _aRect_Present[pry], c_width, c_height);
                    }
                } else {
                    //�E�B���h�E���[�h���E�c���X�g���b�`
                    if (::GetClientRect(_paHWnd[wno], &rect)) {
                        _aRect_Present[pry] = rect;
                    }
                }

            }
        }

#ifdef MY_DEBUG
        //_TRACE_("Caretaker::adjustGameWindow(" << (prm_pHWnd == _pHWndPrimary ? "Primary" : "Secondary") <<") �R�[��");
        if (Config::NUMBER_OF_SCREENS_USED > 1) {
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].left   = "<<_aRectRenderBufferSource[SCREEN01].left  );
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].top    = "<<_aRectRenderBufferSource[SCREEN01].top   );
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].right  = "<<_aRectRenderBufferSource[SCREEN01].right );
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].bottom = "<<_aRectRenderBufferSource[SCREEN01].bottom);
            _TRACE_(" _aRectRenderBufferSource[SCREEN02].left   = "<<_aRectRenderBufferSource[SCREEN02].left  );
            _TRACE_(" _aRectRenderBufferSource[SCREEN02].top    = "<<_aRectRenderBufferSource[SCREEN02].top   );
            _TRACE_(" _aRectRenderBufferSource[SCREEN02].right  = "<<_aRectRenderBufferSource[SCREEN02].right );
            _TRACE_(" _aRectRenderBufferSource[SCREEN02].bottom = "<<_aRectRenderBufferSource[SCREEN02].bottom);
            _TRACE_(" _aRect_Present[SCREEN01].left   = "<<_aRect_Present[SCREEN01].left  );
            _TRACE_(" _aRect_Present[SCREEN01].top    = "<<_aRect_Present[SCREEN01].top   );
            _TRACE_(" _aRect_Present[SCREEN01].right  = "<<_aRect_Present[SCREEN01].right );
            _TRACE_(" _aRect_Present[SCREEN01].bottom = "<<_aRect_Present[SCREEN01].bottom);
            _TRACE_(" _aRect_Present[SCREEN02].left   = "<<_aRect_Present[SCREEN02].left  );
            _TRACE_(" _aRect_Present[SCREEN02].top    = "<<_aRect_Present[SCREEN02].top   );
            _TRACE_(" _aRect_Present[SCREEN02].right  = "<<_aRect_Present[SCREEN02].right );
            _TRACE_(" _aRect_Present[SCREEN02].bottom = "<<_aRect_Present[SCREEN02].bottom);
        } else {
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].left   = "<<_aRectRenderBufferSource[SCREEN01].left  );
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].top    = "<<_aRectRenderBufferSource[SCREEN01].top   );
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].right  = "<<_aRectRenderBufferSource[SCREEN01].right );
            _TRACE_(" _aRectRenderBufferSource[SCREEN01].bottom = "<<_aRectRenderBufferSource[SCREEN01].bottom);
            _TRACE_(" _aRect_Present[SCREEN01].left   = "<<_aRect_Present[SCREEN01].left  );
            _TRACE_(" _aRect_Present[SCREEN01].top    = "<<_aRect_Present[SCREEN01].top   );
            _TRACE_(" _aRect_Present[SCREEN01].right  = "<<_aRect_Present[SCREEN01].right );
            _TRACE_(" _aRect_Present[SCREEN01].bottom = "<<_aRect_Present[SCREEN01].bottom);
        }
#endif
    } else {
        //�t���X�N���[����
    }
    Camera* pCam = getSpacetime()->getCamera();
    _pID3DDevice9->GetViewport(&(pCam->_viewport));
    _adjustGameWindow = false;
//    _pHWnd_adjustScreen = nullptr;
}

void Caretaker::setPositionPresentRect(int prm_pos, RECT& inout_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height) {
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
        inout_rectPresent.bottom = inout_rectPresent.bottom - inout_rectPresent.top;
        inout_rectPresent.top = 0;
    } else if (prm_pos == 1 || prm_pos == 2 || prm_pos == 3) {
        inout_rectPresent.top = prm_screen_height - (inout_rectPresent.bottom - inout_rectPresent.top);
        inout_rectPresent.bottom = prm_screen_height;
    }

    if (prm_pos == 7 || prm_pos == 4 || prm_pos == 1) {
        inout_rectPresent.right = inout_rectPresent.right - inout_rectPresent.left;
        inout_rectPresent.left = 0;
    } else if (prm_pos == 9 || prm_pos == 6 || prm_pos == 3) {
        inout_rectPresent.left = prm_screen_width - (inout_rectPresent.right - inout_rectPresent.left);
        inout_rectPresent.right = prm_screen_width;
    }
}

TextureManager* Caretaker::createTextureManager() {
    TextureManager* p =  NEW TextureManager("TextureManager");
    return p;
}

ModelManager* Caretaker::createModelManager() {
    ModelManager* p =  NEW ModelManager("ModelManager");
    return p;
}

EffectManager* Caretaker::createEffectManager() {
    EffectManager* p = NEW EffectManager("EffectManager");
    return p;
}

CurveSourceManager* Caretaker::createCurveSourceManager() {
    CurveSourceManager* p = NEW CurveSourceManager("CurveSourceManager");
    return p;
}

CurveManufactureManager* Caretaker::createCurveManufactureManager() {
    CurveManufactureManager* p = NEW CurveManufactureManager("CurveManufactureManager");
    return p;
}

Caretaker::~Caretaker() {
    _TRACE_(FUNC_NAME<<" ����J�n");
    calmDown();
    clean();
    _was_cleaned = true;
    //DirectSound���
    Sound::release();
    //DirectInput���
    Input::release();

    if(CONFIG::FULL_SCREEN) {
        releaseFullScreenRenderTarget();
    }

    _TRACE_("_pID3DDevice9 ���������");
    Sleep(60);
    if(CONFIG::FULL_SCREEN) {
        GGAF_DELETEARR(_papSwapChain);
        GGAF_DELETEARR(_papBackBuffer);
    }
    GGAF_DELETEARR(_paAvailableAdapter);
    GGAF_DELETEARR(_paAdapterRezos);
    GGAF_DELETEARR(_paPresetPrm);
    GGAF_DELETEARR(_paDisplayMode);
    GGAF_DELETEARR(_paHWnd);
    GGAF_DELETEARR(_paWindowNoToScreenPry);
    GGAF_RELEASE(_pID3DDevice9);
    GGAF_RELEASE(_pID3D9);
    _TRACE_(FUNC_NAME<<" ����I��");
}




//���� 2011/07/26
//
//�y�P��ʃE�B���h�E���[�h�z
//                                 �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                               �^                                        �^
//    �t�����g�o�b�t�@         �^                                        �^
//    (�E�C���h�E)           �^                                        �^
//                           �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P
//                           SCREEN01_WINDOW_WIDTH x SCREEN01_WINDOW_HEIGHT
//
//                                               ��
//                                               �b Present
//                                               �b(D3DSWAPEFFECT_COPY)
//                                               �b
//                                  �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �o�b�N�o�b�t�@              �^                                        �^
//                              �^ _paPresetPrm[0].BackBufferWidthxHeight �^ �S�ʂ�Draw   �Q�Q�Q
//                            �^                                        �^       ��     �^    �^�Q�[���o�b�t�@
//                            �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P                �P�P�PGAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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
//                     SCREEN01_WINDOW_WIDTH x            SCREEN02_WINDOW_WIDTH x
//                       SCREEN01_WINDOW_HEIGHT             SCREEN02_WINDOW_HEIGHT
//
//                                 ��                               ��
//                                 �b Present                       �b Present
//                                 �b(D3DSWAPEFFECT_COPY)           �b (D3DSWAPEFFECT_COPY)
//
//                                  �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �o�b�N�o�b�t�@              �^                                        �^
//                              �^ _paPresetPrm[0].BackBufferWidthxHeight �^ �S�ʂ�Draw   �Q�Q�Q
//                            �^                                        �^       ��     �^    �^�Q�[���o�b�t�@
//                            �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P                �P�P�PGAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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
//                                SCREEN01_FULL_SCREEN_WIDTH x
//                                  SCREEN01_FULL_SCREEN_HEIGHT
//
//                                                 ��
//                                                 �b Present (flip)
//                                                 �b(D3DSWAPEFFECT_DISCARD)
//                                                 ��
//                                        �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                                      �^                              �^
//                                    �^                              �^
//    �o�b�N�o�b�t�@                �^     _papBackBuffer[0]        �^
//                                �^                              �^
//                              �^                              �^
//                              �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P
//                               SCREEN01_FULL_SCREEN_WIDTH x
//                                 SCREEN01_FULL_SCREEN_HEIGHT
//
//                                                 ��
//                                                 �b StretchRect
//                                                 �b
//                                 �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �����_�[�^�[�Q�b�g         �^                                        �^
//    �e�N�X�`���[             �^       _pRenderTextureSurface           �^ �S�ʂ�Draw   �Q�Q�Q
//                           �^                                        �^       ��     �^    �^�Q�[���o�b�t�@
//                           �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P                �P�P�PGAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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
//                   SCREEN01_FULL_SCREEN_WIDTH x  |   SCREEN02_FULL_SCREEN_WIDTH x
//                     SCREEN01_FULL_SCREEN_HEIGHT |     SCREEN02_FULL_SCREEN_HEIGHT
//
//                               ��                                 ��
//                               �b Present (flip)                  �b Present (flip)
//                               �b(D3DSWAPEFFECT_DISCARD)          �b (D3DSWAPEFFECT_DISCARD)
//                               ��                                 ��
//                            �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q             �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//                          �^                    �^           �^                    �^
//    �o�b�N�o�b�t�@      �^  _papBackBuffer[0] �^           �^ _papBackBuffer[1]  �^
//                      �^                    �^           �^                    �^
//                      �P�P�P�P�P�P�P�P�P�P�P             �P�P�P�P�P�P�P�P�P�P�P
//                     SCREEN01_FULL_SCREEN_WIDTH x        SCREEN02_FULL_SCREEN_WIDTH x
//                       SCREEN01_FULL_SCREEN_HEIGHT         SCREEN02_FULL_SCREEN_HEIGHT
//
//                                    ��                            ��
//                                    �b StretchRect                �b StretchRect
//                                    �b                            �b
//                                  �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q
//    �����_�[�^�[�Q�b�g          �^                                        �^
//    �e�N�X�`���[              �^       _pRenderTextureSurface           �^ �S�ʂ�Draw   �Q�Q�Q
//                            �^                                        �^       ��     �^    �^�Q�[���o�b�t�@
//                            �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P                �P�P�P  GAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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


