#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

//TODO:�R�����g�Ƃ���������B��������B

HWND GgafDx9God::_hWnd = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9_default;
D3DLIGHT9 GgafDx9God::_d3dlight9_temp;
DWORD GgafDx9God::_dwAmbientBrightness_default = 0xff404040;

RECT GgafDx9God::_rectPresentDest;

//double GgafDx9God::_cameraZ = 0;
//double GgafDx9God::_cameraZ_org = 0;
//double GgafDx9God::_tan_half_fovY = 0;
//double GgafDx9God::_dCamHarfXfovTan = 0;
//double GgafDx9God::_screen_aspect = 0;


D3DFILLMODE GgafDx9God::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDx9ModelManager* GgafDx9God::_pModelManager = NULL;
GgafDx9EffectManager* GgafDx9God::_pEffectManager = NULL;
//int const GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)  = 1024;
//int const GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT) = 600;
D3DPRESENT_PARAMETERS GgafDx9God::_structD3dPresent_Parameters;
bool GgafDx9God::_is_device_lost_flg = false;
bool GgafDx9God::_FULLSCRREEN = false;

GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND _hWnd) :
    GgafGod() {
    TRACE("GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND prmGgafDx9God::_hWnd) ");
    GgafDx9God::_hWnd = _hWnd;
    GgafDx9God::_hInstance = prm_hInstance;
    _is_device_lost_flg = false;
    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
}

HRESULT GgafDx9God::init() {
    _FULLSCRREEN = GGAFDX9_PROPERTY(FULL_SCREEN);
    _rectPresentDest.left = 0;
    _rectPresentDest.top = 0;
    _rectPresentDest.right = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH);
    _rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT);

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

    //�f�o�C�X�쐬
    ZeroMemory(&_structD3dPresent_Parameters, sizeof(D3DPRESENT_PARAMETERS));
    //�o�b�N�o�b�t�@�̏c�T�C�Y
    //_structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT);
    _structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT);
    //�o�b�N�o�b�t�@�̉��T�C�Y
    //_structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(GAME_SPACE_WIDTH);
    _structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH);
    //�o�b�N�o�b�t�@�̃t�H�[�}�b�g
    if (_FULLSCRREEN) {
        _structD3dPresent_Parameters.BackBufferFormat = D3DFMT_X8R8G8B8;//D3DFMT_A8R8G8B8;//D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;	//�t���X�N���[����
    } else {
        _structD3dPresent_Parameters.BackBufferFormat = structD3DDisplayMode.Format; //�E�B���h�E��
    }
    //_structD3dPresent_Parameters.BackBufferFormat = D3DFMT_UNKNOWN;	//���݂̉�ʃ��[�h�𗘗p
    //�o�b�N�o�b�t�@�̐�
    _structD3dPresent_Parameters.BackBufferCount = 1;

    //�X���b�v���ʂ��w�肷��
    _structD3dPresent_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    //�E�B���h�E�n���h��
    _structD3dPresent_Parameters.hDeviceWindow = NULL;
    //�E�B���h�E���[�h
    if (_FULLSCRREEN) {
        _structD3dPresent_Parameters.Windowed = false; //�t���X�N���[����
    } else {
        _structD3dPresent_Parameters.Windowed = true; //�E�B���h�E��
    }
    //�[�x�X�e���V���o�b�t�@
    //_structD3dPresent_Parameters.EnableAutoDepthStencil = FALSE;
    //_structD3dPresent_Parameters.AutoDepthStencilFormat = 0;
    _structD3dPresent_Parameters.EnableAutoDepthStencil = 1; //Z �o�b�t�@�̎����쐬
    _structD3dPresent_Parameters.AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;
    //0�ɂ��Ă���
    _structD3dPresent_Parameters.Flags = 0;
    //�t���X�N���[���ł̃��t���b�V�����[�g(�E�B���h�E���[�h�Ȃ�0���w��)
    if (_FULLSCRREEN) {
        _structD3dPresent_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //�t���X�N���[����
    } else {
        _structD3dPresent_Parameters.FullScreen_RefreshRateInHz = 0; //�E�B���h�E��
    }
    //�X���b�v�̃^�C�~���O
    if (_FULLSCRREEN) {
        _structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    } else {
        _structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //����
        //TODO:Window���[�h�͂������Ȃ̂��H�AD3DPRESENT_INTERVAL_ONE �Ƃ����߂��H
    }

    //�A���`�A�C���A�X�ɂł��邩�`�F�b�N
    UINT32 qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;

    //	if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //		D3DADAPTER_DEFAULT,
    //		D3DDEVTYPE_HAL,
    //		D3DFMT_A8R8G8B8,
    //		_FULLSCRREEN ? FALSE : TRUE,
    //		D3DMULTISAMPLE_2_SAMPLES,
    //		&qualityLevels) ) )
    //	{
    //		if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //			D3DADAPTER_DEFAULT,
    //			D3DDEVTYPE_HAL,
    //			D3DFMT_D24S8,
    //			_FULLSCRREEN ? FALSE : TRUE,
    //			D3DMULTISAMPLE_2_SAMPLES,
    //			NULL) ) )
    //		{
    //			multiSampleType = D3DMULTISAMPLE_2_SAMPLES;
    //			_TRACE_("MultiSampleType = D3DMULTISAMPLE_2_SAMPLES");
    //		}
    //	}
    //�}���`�T���v���̐�
    _structD3dPresent_Parameters.MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
    //�}���`�T���v���̕i�����x��
    _structD3dPresent_Parameters.MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);

    //�t���X�N���[���ɏo���邩���ׂ�
    if (_FULLSCRREEN) {
        int cc = GgafDx9God::_pID3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT,
                                                          _structD3dPresent_Parameters.BackBufferFormat);
        if (cc) {
            D3DDISPLAYMODE adp;
            for (int i = 0; i < cc; i++) {
                GgafDx9God::_pID3D9->EnumAdapterModes(D3DADAPTER_DEFAULT,
                                                      _structD3dPresent_Parameters.BackBufferFormat, i, &adp);
                if (adp.Format == _structD3dPresent_Parameters.BackBufferFormat && adp.Width
                        == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) && adp.Height
                        == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT)) {
                    //OK
                    break;
                }
                if (cc == i) {
                    //�v�������g����𑜓x��������Ȃ�
                    throwGgafCriticalException(GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) <<"x"<<GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) << "�̃t���X�N���[�����[�h�ɂ��鎖���ł��܂���B");
                    return E_FAIL;
                }
            }
        } else {
            throwGgafCriticalException("GetAdapterModeCount �Ɏ��s���܂���");
            return E_FAIL;
        }
    }

    // NVIDIA PerfHUD �p begin --------------------------------------------->

    //default
    UINT AdapterToUse = D3DADAPTER_DEFAULT;
    D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
#ifdef MY_DEBUG

#if SHIPPING_VERSION
    // When building a shipping version, disable PerfHUD (opt-out)
#else
    _TRACE_("Look for 'NVIDIA PerfHUD' adapter...");
    // If it is present, override default settings
    for (UINT Adapter = 0; Adapter < GgafDx9God::_pID3D9->GetAdapterCount(); Adapter++) {
        D3DADAPTER_IDENTIFIER9 Identifier;
        HRESULT Res;
        Res = GgafDx9God::_pID3D9->GetAdapterIdentifier(Adapter, 0, &Identifier);
        if (strstr(Identifier.Description, "PerfHUD") != 0) {
            _TRACE_("found NVIDIA PerfHUD!");
            AdapterToUse = Adapter;
            DeviceType = D3DDEVTYPE_REF;
            break;
        }
    }
#endif

#endif
    // <------------------------------------------------ NVIDIA PerfHUD �p end


    //�f�o�C�X�쐬������ GgafDx9God::_pID3DDevice9 �֐ݒ肷��B
    //�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
    hr = GgafDx9God::_pID3D9->CreateDevice(AdapterToUse, DeviceType, GgafDx9God::_hWnd,
                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                           &_structD3dPresent_Parameters, &GgafDx9God::_pID3DDevice9);

    if (hr != D3D_OK) {
        //�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
        hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_hWnd,
                                               D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                               &_structD3dPresent_Parameters, &GgafDx9God::_pID3DDevice9);
        if (hr != D3D_OK) {
            //�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_hWnd,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                   &_structD3dPresent_Parameters, &GgafDx9God::_pID3DDevice9);
            if (hr != D3D_OK) {
                //�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
                MessageBox(GgafDx9God::_hWnd, TEXT("Direct3D�̏������Ɏ��s"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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
    //    //�Q�ƃJ�E���^��]�����₷�B���R�̓f�X�g���N�^�̃f�o�C�X��������Q�ƁB
    //    GgafDx9God::_pID3DDevice9->AddRef();
    //    GgafDx9God::_pID3DDevice9->AddRef();

    //�s�N�Z���V�F�[�_�[�A���_�V�F�[�_�[�o�[�W�����`�F�b�N
    D3DCAPS9 caps;
    GgafDx9God::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] �f�B�X�v���C �A�_�v�^�����������B
                                       //      D3DADAPTER_DEFAULT �͏��
                                       //      �v���C�}�� �f�B�X�v���C �A�_�v�^
                                       D3DDEVTYPE_HAL, // [in] �f�o�C�X�̎�ށB D3DDEVTYPE�񋓌^�̃����o
                                       &caps); // [out] �f�o�C�X�̔\�͂��i�[�����

    UINT32 vs_v = caps.VertexShaderVersion;
    UINT32 ps_v = caps.PixelShaderVersion;
    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(ps_v));
    if (vs_v < D3DVS_VERSION(2, 0) || ps_v < D3DPS_VERSION(2, 0)) {
        _TRACE_("�r�f�I�J�[�h�n�[�h�̒��_�V�F�[�_�[�ƃs���N�Z���V�F�[�_�[�́A���Ƀo�[�W���� 2_0 �ȏ�łȂ���΂����܂���B");
        _TRACE_("���g�p�̃r�f�I�J�[�h�ł́A���������삵�Ȃ����ꂪ����܂��B");
    }

    //���̑��K�v�ȏ�����
    _pModelManager = NEW GgafDx9ModelManager("ModelManager");
    _pEffectManager = NEW GgafDx9EffectManager("EffectManager");
    GgafDx9Util::init(); //���[�e�B���e�B����
    GgafDx9Input::init(); //DirectInput����
    GgafDx9Sound::init(); //DirectSound����
    RELEASE_IMPOSSIBLE_NULL(_pID3D9);
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
     //GgafDx9God::_d3dlight9_default.Position = D3DXVECTOR3(-1*GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)/2, -1*GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)/2, -1*GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)/2);
     //GgafDx9God::_d3dlight9_default.Range = 1000;
     */

    //���C�g�\���̂́A�V�F�[�_�[�̃p�����[�^�ɂȂ鎞�����邽�ߕK�v�B
    D3DXVECTOR3 vecDirection(1.0f, -1.0f, 1.0f);
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
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

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


    // VIEW�ϊ��i�J�����ʒu�j�ݒ�
    //D3DXMATRIX _vMatrixView; // �r���[�ϊ��s��

    //    DELETE_POSSIBLE_NULL(_pVecCamFromPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamLookatPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamUp);


    // �ˉe�ϊ��i�R�c�����ʁj
    //D3DXMATRIX _vMatrixProj; // �ˉe�ϊ��s��


    //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_vMatrixProj);


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
                if (i > 2000) {
                    _TRACE_("GgafDx9God::makeUniversalMaterialize() �Q���ҋ@���܂������A�H�ꂩ�甽��������܂���Bbreak���܂��B�v����");
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
            getUniverse()->throwDownEvent(GGAF_EVENT_ON_DEVICE_LOST);

            //�f�o�C�X���Z�b�g�����݂�
            hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_structD3dPresent_Parameters));
            checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() �f�o�C�X���X�g��̃��Z�b�g�łɎ��s���܂����B");

            //�f�o�C�X�Đݒ�
            GgafDx9God::initDx9Device();
            //�G�t�F�N�g���Z�b�g
            GgafDx9God::_pEffectManager->restoreAll();
            //���f���Đݒ�
            GgafDx9God::_pModelManager->restoreAll();
            //�S�m�[�h�ɍĐݒ肵�Ȃ����C�x���g����
            getUniverse()->throwDownEvent(GGAF_EVENT_DEVICE_LOST_RESTORE);
            //�O��`�惂�f�����𖳌��ɂ���
            GgafDx9God::_pModelManager->_pModelLastDraw = NULL;
            _is_device_lost_flg = false;

            //�H��ĊJ
            GgafFactory::finishRest();
            _TRACE_("����f�o�C�X���X�g�����BEnd");
        }
    }

    if (_is_device_lost_flg != true) {
        //�o�b�t�@�N���A
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // �N���A�����`�̈�̐�
                                              NULL, // ��`�̈�
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
                                              D3DCOLOR_RGBA(0, 0, 0, 0), //�w�i���ɃN���A //D3DCOLOR_XRGB( 0, 0, 0 ), //�w�i���ɃN���A
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
        //if (GgafDx9God::_pID3DDevice9->Present(NULL,&_rectPresentDest,NULL,NULL) == D3DERR_DEVICELOST) {
        //        static D3DRASTER_STATUS rs;
        //        while (SUCCEEDED(GgafDx9God::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
        //            if(rs.InVBlank) {
        //                break; //�����A�����Ԃł͂Ȃ�
        //            } else {
        //                Sleep(1);
        //            }
        //        }
        HRESULT hr;
        if (_FULLSCRREEN) {
            hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
        } else {
            hr = GgafDx9God::_pID3DDevice9->Present(NULL, &_rectPresentDest, NULL, NULL);
        }
        if (hr == D3DERR_DEVICELOST) {
            //�o�n�ّ��I�|�l�I
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
            getUniverse()->throwDownEvent(GGAF_EVENT_ON_DEVICE_LOST);
            //�f�o�C�X���Z�b�g�����݂�
            hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_structD3dPresent_Parameters));
            checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() D3DERR_DRIVERINTERNALERROR �̂��� Reset() �������܂����A�ʖڂł����B");
            //�f�o�C�X�Đݒ�
            GgafDx9God::initDx9Device();
            //�G�t�F�N�g���Z�b�g
            GgafDx9God::_pEffectManager->restoreAll();
            //���f���Đݒ�
            GgafDx9God::_pModelManager->restoreAll();
            //�S�m�[�h�ɍĐݒ肵�Ȃ����C�x���g����
            getUniverse()->throwDownEvent(GGAF_EVENT_DEVICE_LOST_RESTORE);
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
        GgafGod::clean();

        CmRandomNumberGenerator::getInstance()->release();
        //�ێ����f�����
        DELETE_IMPOSSIBLE_NULL(_pModelManager);
        DELETE_IMPOSSIBLE_NULL(_pEffectManager);


        _TRACE_("GgafDx9God::clean() end");
    }
}

GgafDx9God::~GgafDx9God() {
    clean();
    _was_cleaned = true;
    Sleep(10);
    //DirectSound���
    GgafDx9Sound::release();
    //DirectInput���
    GgafDx9Input::release();
    _TRACE_("����_pID3DDevice9����I");
    Sleep(10);
    RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9);
}
