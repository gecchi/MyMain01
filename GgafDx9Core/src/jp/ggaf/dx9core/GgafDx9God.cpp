#include "stdafx.h"


HWND GgafDx9God::_hWnd = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9;
RECT GgafDx9God::_rectPresentDest;


//int const GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)  = 1024;
//int const GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) = 600;
D3DPRESENT_PARAMETERS GgafDx9God::_structD3dPresent_Parameters;
bool GgafDx9God::_deviceLostFlg = false;

GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND _hWnd) : GgafGod() {
	TRACE("GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND prmGgafDx9God::_hWnd) ");
	GgafDx9God::_hWnd = _hWnd;
	GgafDx9God::_hInstance = prm_hInstance;
	_deviceLostFlg = false;
	CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 �� Seed

}

HRESULT GgafDx9God::init() {
	bool FULLSCRREEN = GGAFDX9_PROPERTY(FULL_SCREEN);
	_rectPresentDest.left = 0;
	_rectPresentDest.top = 0;
	_rectPresentDest.right = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH);
	_rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT);

	HRESULT hr;

	//IDirect3D9�R���|�[�l���g�̎擾
	if (!(GgafDx9God::_pID3D9 = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		throw_GgafCriticalException("Direct3DCreate9 �Ɏ��s���܂���");
		return E_FAIL;  //���s
	}



	//�f�X�v���C���[�h�̎擾
	D3DDISPLAYMODE structD3DDisplayMode;  //���ʂ��i�[�����\����
	hr = GgafDx9God::_pID3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&structD3DDisplayMode);
	if (FAILED(hr))	{
		throw_GgafCriticalException("GetAdapterDisplayMode �Ɏ��s���܂���");
		return E_FAIL;
	}

	//�f�o�C�X�쐬
	ZeroMemory(&_structD3dPresent_Parameters,sizeof(D3DPRESENT_PARAMETERS));
	//�o�b�N�o�b�t�@�̏c�T�C�Y
	//_structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT);
	_structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT);
	//�o�b�N�o�b�t�@�̉��T�C�Y
	//_structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH);
	_structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH);
	//�o�b�N�o�b�t�@�̃t�H�[�}�b�g
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.BackBufferFormat = D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;	//�t���X�N���[����
	} else {
		_structD3dPresent_Parameters.BackBufferFormat = structD3DDisplayMode.Format; //�E�B���h�E��
	}
	//_structD3dPresent_Parameters.BackBufferFormat = D3DFMT_UNKNOWN;	//���݂̉�ʃ��[�h�𗘗p
	//�o�b�N�o�b�t�@�̐�
	_structD3dPresent_Parameters.BackBufferCount = 1;
	//�}���`�T���v���̐�
	_structD3dPresent_Parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	//�}���`�T���v���̕i�����x��
	_structD3dPresent_Parameters.MultiSampleQuality = 0;
	//�X���b�v���ʂ��w�肷��
	_structD3dPresent_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//�E�B���h�E�n���h��
	_structD3dPresent_Parameters.hDeviceWindow = NULL;
	//�E�B���h�E���[�h
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.Windowed = false;  //�t���X�N���[����
	} else {
		_structD3dPresent_Parameters.Windowed = true;     //�E�B���h�E��
	}
	//�[�x�X�e���V���o�b�t�@
	//_structD3dPresent_Parameters.EnableAutoDepthStencil = FALSE;
	//_structD3dPresent_Parameters.AutoDepthStencilFormat = 0;
	_structD3dPresent_Parameters.EnableAutoDepthStencil = 1;   //Z �o�b�t�@�̎����쐬
	_structD3dPresent_Parameters.AutoDepthStencilFormat = D3DFMT_D16;
	//0�ɂ��Ă���
	_structD3dPresent_Parameters.Flags = 0;
	//�t���X�N���[���ł̃��t���b�V�����[�g(�E�B���h�E���[�h�Ȃ�0���w��)
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;    //�t���X�N���[����
	} else {
		_structD3dPresent_Parameters.FullScreen_RefreshRateInHz = 0;                          //�E�B���h�E��
	}
	//�X���b�v�̃^�C�~���O
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	} else {
		_structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //����(Window���[�h�͂����炪�ǂ��炵���j
	}

	//�t���X�N���[���ɏo���邩���ׂ�
	if (FULLSCRREEN) {
		int cc = GgafDx9God::_pID3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT, _structD3dPresent_Parameters.BackBufferFormat);
	    if(cc){
	        D3DDISPLAYMODE adp;
	        for(int i = 0; i < cc; i++){
	        	GgafDx9God::_pID3D9->EnumAdapterModes(D3DADAPTER_DEFAULT, _structD3dPresent_Parameters.BackBufferFormat, i, &adp);
	            if (adp.Format == _structD3dPresent_Parameters.BackBufferFormat &&
	                adp.Width  == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH)     &&
	                adp.Height == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) )
	            {
	            	//OK
	            	break;
	            }
	            if (cc == i) {
	            	//�v�������g����𑜓x��������Ȃ�
	            	throw_GgafCriticalException(GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) <<"x"<<GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) << "�̃t���X�N���[�����[�h�ɂ��鎖���ł��܂���B");
	            	return E_FAIL;
	            }
	        }
	    } else {
			throw_GgafCriticalException("GetAdapterModeCount �Ɏ��s���܂���");
			return E_FAIL;
		}
	}

	//�f�o�C�X�쐬������ GgafDx9God::_pID3DDevice9 �֐ݒ肷��B
	//�n�[�h�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(pure vp)
	hr = GgafDx9God::_pID3D9->CreateDevice(
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								GgafDx9God::_hWnd,
								D3DCREATE_HARDWARE_VERTEXPROCESSING,
								&_structD3dPresent_Parameters,
								&GgafDx9God::_pID3DDevice9);
	if (FAILED(hr)) {
		//�\�t�g�E�F�A�ɂ�钸�_�����A�n�[�h�E�F�A�ɂ�郉�X�^���C�Y���s���f�o�C�X�쐬�����݂�BHAL(soft vp)
		hr = GgafDx9God::_pID3D9->CreateDevice(
									D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									GgafDx9God::_hWnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&_structD3dPresent_Parameters,
									&GgafDx9God::_pID3DDevice9);
		if (FAILED(hr)) {
			//�\�t�g�E�F�A�ɂ�钸�_�����A���X�^���C�Y���s���f�o�C�X�쐬�����݂�BREF
			hr = GgafDx9God::_pID3D9->CreateDevice(
										D3DADAPTER_DEFAULT,
										D3DDEVTYPE_REF,
										GgafDx9God::_hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&_structD3dPresent_Parameters,
										&GgafDx9God::_pID3DDevice9);
			if (FAILED(hr)) {
				//�ǂ̃f�o�C�X�̍쐬�����s�����ꍇ
				MessageBox(GgafDx9God::_hWnd,TEXT("Direct3D�̏������Ɏ��s"),TEXT("ERROR"),MB_OK | MB_ICONSTOP);
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
	return initDx9Device();

}





HRESULT GgafDx9God::initDx9Device() {
	 // �f�t�H���g�̃��C�g
/*
	ZeroMemory(&_d3dlight9, sizeof(D3DLIGHT9) );
	GgafDx9God::_d3dlight9.Type = D3DLIGHT_DIRECTIONAL; //���s���A�F�ƕ��������ł悢
	GgafDx9God::_d3dlight9.Direction = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	GgafDx9God::_d3dlight9.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	GgafDx9God::_d3dlight9.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	//���͕��s���ł͊֌W�Ȃ�
	//GgafDx9God::_d3dlight9.Position = D3DXVECTOR3(-1*GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)/2, -1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/2, -1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/2);
	//GgafDx9God::_d3dlight9.Range = 1000;
*/
	ZeroMemory(&_d3dlight9, sizeof(D3DLIGHT9) );
	GgafDx9God::_d3dlight9.Direction = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	GgafDx9God::_d3dlight9.Type = D3DLIGHT_DIRECTIONAL;
	GgafDx9God::_d3dlight9.Diffuse.r = 1.0f;
	GgafDx9God::_d3dlight9.Diffuse.g = 1.0f;
	GgafDx9God::_d3dlight9.Diffuse.b = 1.0f;
	GgafDx9God::_d3dlight9.Ambient.r = 0.0f; //�A���r�G���g���C�g��SetRenderState(D3DRS_AMBIENT, 0x00303030)�Őݒ�
	GgafDx9God::_d3dlight9.Ambient.g = 0.0f;
	GgafDx9God::_d3dlight9.Ambient.b = 0.0f;
	//GgafDx9God::_d3dlight9.Range = 1000.0f;



	//���C�g���Z�b�g
	GgafDx9God::_pID3DDevice9->SetLight( 0, &GgafDx9God::_d3dlight9 );
	//���C�g�X�C�b�`ON
	GgafDx9God::_pID3DDevice9->LightEnable( 0, TRUE );
	//�����_���Ƀ��C�g�̉e���i�A�e�j��L��
	GgafDx9God::_pID3DDevice9->SetRenderState( D3DRS_LIGHTING, TRUE);
	//���E�ɋ��ʂ̃A���r�G���g���C�g
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, 0x00303030);

	// Z�o�b�t�@��L����
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// Z�o�b�t�@�𖳌���
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//Z�o�b�t�@�������݉�
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE );
	//Z�o�b�t�@�������ݕs��
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
	//���i�����v���j���ɃJ�����O �捶����W�n
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//�J�����O���Ȃ�
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �A���t�@�u�����h�n�m
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// �F�̎Z�o���@�̐ݒ�
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �f�B�U�����OOFF
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
	// �}���`�T���v�����O�A���`�G�C���A�XOFF
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);


	// �e�N�X�`���������@�̐ݒ�
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	// �e�N�X�`���ƒ��_�F����Z����悤�ɐݒ�
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);




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

	//�A���`�G�C���A�X�ɂ�����郌���_�����O�X�e�[�g
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);


	// �r���[�ϊ��i�J�����ʒu�j�ݒ�
	double dCam = -1.0*(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/PX_UNIT/2)/tan(PI/9);
	_TRACE_("�J�����̈ʒu(0,0,"<<dCam<<")");
	D3DXMATRIX matrixView;   // �r���[�ϊ��s��
	D3DXVECTOR3 vFromPt   = D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)dCam); //�ʒu
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //�����������
	D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //�����
	D3DXMatrixLookAtLH(
				&matrixView,
				&vFromPt,
				&vLookatPt,
				&vUpVec
	);
	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_VIEW, &matrixView);


	// �ˉe�ϊ��i�R�c�����ʁj
	D3DXMATRIX matrixProjrction;   // �ˉe�ϊ��s��
	D3DXMatrixPerspectiveFovLH(
		&matrixProjrction,
		2.0*(PI/9),     //y��������p���f�B�A��(0�`��)
		(FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)), //�A�X�y�N�g��  640�~480 �̏ꍇ  640/480
		1.0,            //zn:�J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0
		2000.0          //zf:�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn
		//(FLOAT)(-1.0*dCam*4)
		//(-1.0*fCam)-30,
		//(-1.0*fCam)+30
	);
/*
	//������W�n���ˉe
	D3DXMatrixOrthoLH(
		&matrixProjrction,
		GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH),
		GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT),
		1.0f,
		GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)
	);
*/
	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &matrixProjrction);

	//���̑��K�v�ȏ�����
	GgafDx9Util::init(); //���[�e�B���e�B����
	GgafDx9Input::init(); //DirectInput����
	GgafDx9Sound::init(); //DirectSound����
	return S_OK;
}


void GgafDx9God::makeWorldMaterialize() {
	TRACE("GgafDx9God::materialize() start");


	if (_deviceLostFlg) {
		//�f�o�C�X���X�ƕ��A�����݂�
		if (GgafDx9God::_pID3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			//���A
			_TRACE_("�f�o�C�X���X�g���畜�A�����I");
			//���f���J��
			GgafDx9ModelManager::onDeviceLostAll();
			HRESULT hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_structD3dPresent_Parameters));
			if ( hr != D3D_OK ) {
				throw_GgafCriticalException("GgafDx9God::visualize() �f�o�C�X���X�g��̃��Z�b�g�Ń_���ł����B");
			}
			//�f�o�C�X�Đݒ�
			initDx9Device();
			//���f���Đݒ�
			GgafDx9ModelManager::restoreAll();
			//�O��`�惂�f�����𖳌��ɂ���
			GgafDx9Model::_s_modelname_lastdraw = "";
			_deviceLostFlg = false;
		}
	}

	if (_deviceLostFlg != true) {
		//�o�b�t�@�N���A
		GgafDx9God::_pID3DDevice9 -> Clear(
										 0, // �N���A�����`�̈�̐�
										 NULL, // ��`�̈�
										 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
										 //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���N���A
										 D3DCOLOR_XRGB( 0, 0, 0 ), //�w�i���ɃN���A
										 1.0f, // Z�o�b�t�@�̃N���A�l
										 0 // �X�e���V���o�b�t�@�̃N���A�l
									 );

		//�`�掖�O����
		GgafDx9God::_pID3DDevice9->BeginScene();
		//�S�ċ���I�i�`��j
		GgafGod::makeWorldMaterialize(); //�X�[�p�[��materialize���s
		//�`�掖�㏈��
		GgafDx9God::_pID3DDevice9->EndScene();
	}
	TRACE("GgafDx9God::makeWorldMaterialize() end");
}

void GgafDx9God::makeWorldVisualize() {
	if (_deviceLostFlg != true) {
		//�o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɓ]��
		//if (GgafDx9God::_pID3DDevice9 -> Present(NULL,&_rectPresentDest,NULL,NULL) == D3DERR_DEVICELOST) {
		if (GgafDx9God::_pID3DDevice9 -> Present(NULL,NULL,NULL,NULL) == D3DERR_DEVICELOST) {
			//�o�n�ّ��I�|�l�I
			_TRACE_("�f�o�C�X���X�g�I");
			_deviceLostFlg = true;
		}
	}
}

GgafDx9God::~GgafDx9God() {
	TRACE("GgafDx9God::~GgafDx9God() start -->");

	::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
	Sleep(20);
	//�H��|��
	GgafFactory::_isWorking = false;
	GgafFactory::clean();
	::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
	//�H�ꂪ���������܂ő҂�
	while (GgafFactory::_isFinish == false) {
		Sleep(10);
	}

	CmRandomNumberGenerator::getInstance()->release();
	//�ێ����f�����
	GgafDx9ModelManager::clear();
	//DirectInput���
	GgafDx9Input::release();
	//DirectSound���
	GgafDx9Sound::release();
	//�f�o�C�X���
	_pID3DDevice9->Release();
	_pID3D9->Release();
	TRACE("GgafDx9God::~GgafDx9God() end <--");
}
