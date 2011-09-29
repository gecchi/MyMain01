#ifndef GGAFDXGOD_H_
#define GGAFDXGOD_H_


namespace GgafDxCore {
/**
 * DirectX�_ .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class GgafDxGod : public GgafCore::GgafGod {

public:
    static GgafDxModelManager* _pModelManager;
    static GgafDxEffectManager* _pEffectManager;
    static GgafDxTextureManager* _pCubeMapTextureManager;

    static HWND _pHWndPrimary;
    static HWND _pHWndSecondary;
    static HINSTANCE _hInstance;

    static D3DFILLMODE _d3dfillmode;

    /** DirectX9�̃I�u�W�F�N�g */
    static IDirect3D9* _pID3D9;
    /** �f�o�C�X */
    static IDirect3DDevice9* _pID3DDevice9;
    /** �f�t�H���g�̃��C�g */
    static D3DLIGHT9 _d3dlight9_default;
    /** �A���r�G���g���C�g�̃f�t�H���g�̖��邳 */
    static DWORD _dwAmbientBrightness_default;
    /** �f�o�C�X���X�g�t���O (true=���X�g��) */
    static bool _is_device_lost_flg;


    static bool _adjustGameScreen;
    static HWND _pHWnd_adjustScreen;

    /** �g�p�\�ȃf�o�C�X�̃A�_�v�^�� */
    int _num_adapter;


    /** Windows Display Driver Model�iWDDM�j���g�p�\���ۂ� */
    bool _can_wddm;

    /** �f�o�C�X�쐬���p�����[�^�[ */
    D3DPRESENT_PARAMETERS* _paPresetParam;
    /** �f�o�C�X�쐬���p�����[�^�[�iWDDM�g�p���̂ݕK�v�j */
    D3DDISPLAYMODEEX* _paDisplayMode;

    /** �Q�[���o�b�t�@�̈� */
    RECT _rectGameBuffer;
    /** �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���̗̈� */
    RECT _rectRenderTargetBuffer;
    /** �Q�[���o�b�t�@�̈�́A[0]:�������̈�A[1]:�E�����̈� */
    RECT _aRect_HarfGameBuffer[2];
    /** �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���̈�́A[0]:�������̈�A[1]:�E�����̈� */
    RECT _aRect_HarfRenderTargetBuffer[2];
    /** �ŏI�\���t�����g�o�b�t�@�t���[���̗̈�A[0]:�P��ʖځA[1]:�Q��ʖ� */
    RECT _aRect_ViewScreen[2];
    /** Present�̈�A[0]:�P��ʖځA[1]:�Q��ʖ�  */
    RECT _aRect_Present[2];
    /** �P��ʖڂ� _aRect_HarfRenderTargetBuffer[] �̏��� */
    int _primary;
    /** �Q��ʖڂ� _aRect_HarfRenderTargetBuffer[] �̏��� */
    int _secondary;
    /** �t���X�N���[�����Q��ʖڂ̍���X���W */
    pixcoord _secondary_screen_x;
    /** �t���X�N���[�����Q��ʖڂ̍���Y���W */
    pixcoord _secondary_screen_y;

    /** �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`�� */
    IDirect3DTexture9*  _pRenderTexture;
    /** �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���̃T�[�t�F�C�X */
    IDirect3DSurface9*  _pRenderTextureSurface;
    /** �t���X�N���[�����A�����_�����O�^�[�Q�b�g��Z�o�b�t�@�̃T�[�t�F�C�X */
    IDirect3DSurface9*  _pRenderTextureZ;
    /** �t���X�N���[�����A�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[���A[0]:�P��ʖځA[1]:�Q��ʖ� */
    IDirect3DSwapChain9* _apSwapChain[2];
    /** �t���X�N���[�����ADirectX�̃o�b�N�o�b�t�@�A[0]:�P��ʖځA[1]:�Q��ʖ� */
    IDirect3DSurface9* _apBackBuffer[2];

    /** ���_�V�F�[�_�[�̃o�[�W����(D3DVS_VERSION(_Major,_Minor)) */
    static UINT32 _vs_v;
    /** �s�N�Z���V�F�[�_�[�̃o�[�W����(D3DPS_VERSION(_Major,_Minor)) */
    static UINT32 _ps_v;


    /** �Q�[���\���̈�ȊO�̃N���b�v�̈�w�i�F */
    D3DCOLOR _color_background;
    /** �Q�[���\���̈�̕\���N���A���̔w�i�F */
    D3DCOLOR _color_clear;
    /**
     * �R���X�g���N�^<BR>
     */
    GgafDxGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * ������<BR>
     */
    HRESULT init();
    HRESULT createDx9Device(UINT Adapter,
                            D3DDEVTYPE DeviceType,
                            HWND hFocusWindow,
                            DWORD BehaviorFlags,
                            D3DPRESENT_PARAMETERS* pPresentationParameters,
                            D3DDISPLAYMODEEX *pFullscreenDisplayMode
                          );
    HRESULT initDx9Device();
    HRESULT restoreFullScreenRenderTarget();
    HRESULT releaseFullScreenRenderTarget();

    virtual void presentUniversalMoment() override;
    virtual void executeUniversalJudge() override;
    virtual void makeUniversalMaterialize() override;
    virtual void presentUniversalVisualize() override;
    virtual void finalizeUniversal() override;

    void adjustGameScreen(HWND prm_pHWnd);

    void positionPresentRect(int prm_pos, RECT& prm_rectPresent, int prm_screen_width, int prm_screen_height);

    HRESULT restoreRenderSurface();

    virtual void clean() override;

    virtual ~GgafDxGod();
};

}
#endif /*GGAFDXGOD_H_*/
