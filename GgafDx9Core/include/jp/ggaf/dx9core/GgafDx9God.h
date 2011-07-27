#ifndef GGAFDX9GOD_H_
#define GGAFDX9GOD_H_
namespace GgafDx9Core {
/**
 * DirectX�_ .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class GgafDx9God : public GgafCore::GgafGod {

public:
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
    /** �ꎞ�I�ȃ��C�g�i���ݖ��g�p�j */
    static D3DLIGHT9 _d3dlight9_temp;
    /** �A���r�G���g���C�g�̃f�t�H���g�̖��邳 */
    static DWORD _dwAmbientBrightness_default;
    /** �f�o�C�X���X�g�t���O (true=���X�g��) */
    static bool _is_device_lost_flg;

    static bool _adjustGameScreen;
    static HWND _pHWnd_adjustScreen;
    static GgafDx9ModelManager* _pModelManager;
    static GgafDx9EffectManager* _pEffectManager;
    static GgafDx9TextureManager* _pCubeMapTextureManager;
    static int _iNumAdapter;
    /** Present�̈� */

    RECT _aRect_Present[2];
    int _primary, _secondary;
    /* �X�N���[�������i�s�N�Z���j */
    //static int const GAME_BUFFER_HEIGHT;

    static D3DPRESENT_PARAMETERS* _d3dparam;
//    static LPDIRECT3DSWAPCHAIN9 _paSwapChain;
//    static LPDIRECT3DSWAPCHAIN9 _paBackBuffer;



    RECT _rectGameBuffer;
    RECT _rectRenderTargetBuffer;
    RECT _aRect_HarfGameBuffer[2];
    RECT _aRect_HarfRenderTargetBuffer[2];
    RECT _aRect_ViewScreen[2];
//    static RECT*  _pRectViewScreen;
    IDirect3DTexture9*  _pRenderTexture;   //�e�N�X�`��
//    static IDirect3DSurface9*  _pBackBuffer;      //�o�b�N�o�b�t�@
    IDirect3DSurface9*  _pRenderTextureSurface;     //�T�[�t�F�C�X
    IDirect3DSurface9*  _pRenderTextureZ;   //�e�N�X�`��

    LPDIRECT3DSWAPCHAIN9 _pSwapChain00;//�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[��
    LPDIRECT3DSURFACE9 _pBackBuffer00;//�o�b�N�o�b�t�@1��ʕ�
    LPDIRECT3DSWAPCHAIN9 _pSwapChain01;//�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[��
    LPDIRECT3DSURFACE9 _pBackBuffer01;//�o�b�N�o�b�t�@�P��ʕ�


    static UINT32 _vs_v;
    static UINT32 _ps_v;

    static D3DXMACRO _aD3DXMacro_Defines[3];

    D3DCOLOR _color_background;
    D3DCOLOR _color_clear;
    /**
     * �R���X�g���N�^<BR>
     */
    GgafDx9God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * ������<BR>
     */
    HRESULT init();
    HRESULT initDx9Device();

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void makeUniversalMaterialize();

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void presentUniversalVisualize();

    void adjustGameScreen(HWND prm_pHWnd);

    void positionPresentRect(int prm_pos, RECT& prm_rectPresent, int prm_screen_width, int prm_screen_height);

    D3DXMATRIX getInvRotateMat();
    //    /**
    //     * World�V�[�����쐬�B
    //	 * ��OverRide �ł���<BR>
    //	 */
    //	virtual GgafUniverse* createUniverse() {
    //		return (GgafUniverse*)createDx9World();
    //	};
    //
    //
    //    /**
    //     * World�V�[�����쐬�B
    //	 * ��OverRide �ł���<BR>
    //	 */
    //	virtual GgafDx9Universe* createDx9World() = 0;

    virtual void clean() override;
    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9God();
};

}
#endif /*GGAFDX9GOD_H_*/
