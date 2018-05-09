#ifndef GGAFDXCORE_GGAFDXGOD_H_
#define GGAFDXCORE_GGAFDXGOD_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"


#undef pGOD
#define pGOD ((GgafDxCore::GgafDxGod*)GgafCore::GgafGod::ask())

namespace GgafDxCore {

/**
 * DirectX�_ .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class GgafDxGod : public GgafCore::GgafGod {

private:
    /** Windows Display Driver Model�iWDDM�j���g�p�\���ۂ� */
    bool _can_wddm;
    /** �Q�[���\���̈�ȊO�̃N���b�v�̈�w�i�F */
    D3DCOLOR _color_border;
    /** �Q�[���\���̈�̕\���N���A���̔w�i�F */
    D3DCOLOR _color_clear;

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

    /** �f�o�C�X�쐬���p�����[�^�[ */
    D3DPRESENT_PARAMETERS* _paPresetPrm;
    /** ����̗p����Ă���f�o�C�X�iWDDM�g�p���̂ݕK�v�j */
    D3DDISPLAYMODEEX* _paDisplayMode;

    HWND* _paHWnd;

private:
    /**
     * WDDM���ǂ������肵�A�f�o�C�X���쐬 .
     * ���ʂ� GgafDxGod::_pID3D9 �� GgafDxGod::_pID3DDevice9�ɕێ������B
     * @param adapter
     * @param deviceType
     * @param hFocusWindow
     * @param behavior_flags
     * @param pPresentationParameters
     * @param pFullscreenDisplayMode
     * @return
     */
    HRESULT createDx9Device(UINT adapter,
                            D3DDEVTYPE device_type,
                            HWND hFocusWindow,
                            DWORD behavior_flags,
                            D3DPRESENT_PARAMETERS* pPresentationParameters,
                            D3DDISPLAYMODEEX* pFullscreenDisplayMode
                          );
    HRESULT initDx9Device();

    HRESULT restoreFullScreenRenderTarget();

    HRESULT releaseFullScreenRenderTarget();

    /**
     * �E�B���h�E���[�h���A�E�B���h�E�T�C�Y�ɉ������`��͈͂��Đݒ肷��B
     * @param prm_pHWnd
     */
    void adjustGameWindow(HWND prm_pHWnd);

    /**
     * �\���ʒu�ԍ��ɑΉ������`���W�͈�(�s�N�Z��)���擾����B
     * @param prm_pos �\���ʒu�ԍ�
     * @param inout_rectPresent [in]����(pos=5)��̗̈��`�A[out]�\���ʒu�ɑΉ������`���W�͈�
     * @param prm_screen_width ��ʕ�(�s�N�Z��)
     * @param prm_screen_height ��ʍ���(�s�N�Z��)
     */
    void setPositionPresentRect(int prm_pos, RECT& inout_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height);

    /**
     * �}���`�f�B�X�v���C�t���X�N���[�����[�h���A���j�^���W�����擾���� .
     * ���ʂ� _paAvailableAdapter[] �����o�[�Ɋi�[�����B
     * EnumDisplayMonitors�ɂ��R�[���o�b�N�֐��B
     */
    static BOOL CALLBACK updateMoniterPixcoordCallback(HMONITOR hMonitor,
                                                       HDC      hdcMonitor,
                                                       LPRECT   lprcMonitor,
                                                       LPARAM   dwData    );
public:

    ///////////////////////////////////////////////////////////
    class Adapter {
    public:
        int mode_num;
        HMONITOR hMonitor;
        RECT rcMonitor;
        D3DDISPLAYMODE* paModes;
        Adapter() {
            mode_num = 0;
            hMonitor = nullptr;
            paModes = nullptr;
        }
        void setModeNum(int prm_mode_num) {
            mode_num = prm_mode_num;
            paModes = NEW D3DDISPLAYMODE[mode_num];
        }
        ~Adapter() {
            GGAF_DELETEARR_NULLABLE(paModes);
        }
    };

    /** �g�p�\�ȃf�o�C�X�̃A�_�v�^�� */
    int _num_adapter;
    /** �g�p�\�ȃf�o�C�X�̃A�_�v�^�̏��Z�b�g */
    Adapter* _paAvailableAdapter;
    ///////////////////////////////////////////////////////////
    struct RezoInfo {
        UINT width;
        UINT height;
        std::string item_str;
    };
    class AdapterRezos {
    public:
        int rezo_num;
        RezoInfo* paRezoInfo;
        AdapterRezos() {
            rezo_num = 0;
            paRezoInfo = nullptr;
        }
        void init(int prm_rezo_num) {
            rezo_num = prm_rezo_num;
            paRezoInfo = NEW RezoInfo[rezo_num];
        }
        ~AdapterRezos() {
            GGAF_DELETEARR_NULLABLE(paRezoInfo);
        }
    };
    /** �g�p�\�ȃf�o�C�X�̃A�_�v�^�̉𑜓x���Z�b�g */
    AdapterRezos* _paAdapterRezos;
    ////////////////////////////////////////////////////////////

    /** ���f��(GgafDxModel)�����Ǘ��� */
    GgafDxModelManager* _pModelManager;
    /** �G�t�F�N�g(GgafDxEffect)�����Ǘ��� */
    GgafDxEffectManager* _pEffectManager;
    /** ���}�b�v�p�e�N�X�`���[(GgafDxTexture)�����Ǘ��ҁB�i���ʏ�̃e�N�X�`����GgafDxModel�̓����Ǘ��j */
    GgafDxTextureManager* _pCubeMapTextureManager;
    /** �o���v�}�b�v�p�e�N�X�`���[(GgafDxTexture)�����Ǘ��ҁB�i���ʏ�̃e�N�X�`����GgafDxModel�̓����Ǘ��j */
    GgafDxTextureManager* _pBumpMapTextureManager;
    /** [r] 1��ʖڂ̃E�B���h�E�n���h��  */
    static HWND _pHWndPrimary;
    /** [r] 2��ʖڂ̃E�B���h�E�n���h��  */
    static HWND _pHWndSecondary;
    /** [r] �{�A�v���P�[�V�����̃C���X�^���X�n���h�� */
    static HINSTANCE _hInstance;
    /** [r] �f�o�b�O���[�h���A���C���[�t���[���\�� */
    static D3DFILLMODE _d3dfillmode;
    /** [r] DirectX9�̃I�u�W�F�N�g */
    static IDirect3D9* _pID3D9;
    /** [r] �f�o�C�X */
    static IDirect3DDevice9* _pID3DDevice9;
    /** [r] �f�t�H���g�̃��C�g */
    static D3DLIGHT9 _d3dlight9_default;
    /** [r] �A���r�G���g���C�g�̃f�t�H���g�̖��邳 */
    static DWORD _ambient_brightness_default;
    /** [r] �f�o�C�X���X�g�t���O (true=���X�g��) */
    static bool _is_device_lost_flg;
    /** [r] ��ʃA�X�y�N�g�䒲���t���O (true=�E�B���h�E�����T�C�Y����A�\���̈���Čv�Z) */
    static bool _adjustGameWindow;
    /** [r] �\���̈���Čv�Z���K�v�ȃE�B���h�E(�̃n���h��) */
    static HWND _pHWnd_adjustScreen;


    /** [r] ���_�V�F�[�_�[�̃o�[�W����(D3DVS_VERSION(_Major,_Minor)) */
    static uint32_t _vs_v;
    /** [r] �s�N�Z���V�F�[�_�[�̃o�[�W����(D3DPS_VERSION(_Major,_Minor)) */
    static uint32_t _ps_v;

    /** [r] �Q�[���o�b�t�@�̈�(�s�N�Z���I�Ȍn) */
    RECT _rectGameBuffer;
    /** [r] �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���̗̈�(�s�N�Z��) */
    RECT _rectRenderTargetBuffer;
    /** [r] �Q�[���o�b�t�@�̈�́A[0]:�������̈�A[1]:�E�����̈� (�s�N�Z��) */
    RECT _aRect_HarfGameBuffer[2];
    /** [r] �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���̈�́A[0]:�������̈�A[1]:�E�����̈� (�s�N�Z��) */
    RECT _aRect_HarfRenderTargetBuffer[2];
    /** [r] �ŏI�\���t�����g�o�b�t�@�t���[���̗̈�A[0]:�P��ʖځA[1]:�Q��ʖ� (�s�N�Z��) */
    RECT _aRect_ViewScreen[2];
    /** [r] Present�̈�A[0]:�P��ʖځA[1]:�Q��ʖ� (�s�N�Z��) */
    RECT _aRect_Present[2];
    /** [r] �P��ʖڃA�_�v�^�ԍ��A _aRect_HarfRenderTargetBuffer[] �̏��� 0 �` */
    int _primary_adapter_no;
    /** [r] �Q��ʖڃA�_�v�^�ԍ��A _aRect_HarfRenderTargetBuffer[] �̏��� 0 �` */
    int _secondary_adapter_no;

public:
    /**
     * �R���X�g���N�^<BR>
     */
    GgafDxGod();

    /**
     * �t���X�N���[�����A�ł��Ó��ȉ𑜓x��T���B
     * @param prm_paRezos �𑜓x���z��
     * @param prm_rezo_num �𑜓x�z��̗v�f��
     * @param prm_width ���]�̉𑜓x�̕�
     * @param prm_height ���]�̉𑜓x�̍���
     * @return �ł��Ó��ȗv�f�C���f�b�N�X
     */
    static int checkAppropriateDisplaySize(GgafDxGod::RezoInfo* prm_paRezos, int prm_rezo_num,
                                           UINT prm_width, UINT prm_height);
    /**
     * �E�B���h�E�������� .
     * @param prm_wndclass1 �P��ʖڂ�WNDCLASSEX�p�����[�^
     * @param prm_wndclass2 �Q��ʖڂ�WNDCLASSEX�p�����[�^
     * @param prm_title1 �P��ʖڂ̃^�C�g��
     * @param prm_title2 �Q��ʖڂ̃^�C�g��
     * @param prm_dwStyle1 �E�B���h�E���[�h���̃E�C���h�E1�̃X�^�C���萔(WS_OVERLAPPEDWINDOW ��)
     * @param prm_dwStyle2 �E�B���h�E���[�h���̃E�C���h�E2�̃X�^�C���萔(WS_OVERLAPPEDWINDOW ��)
     * @param out_hWnd1 �i�߂�l�j�P��ʖڂ̃E�B���h�E�n���h��
     * @param out_hWnd2 �i�߂�l�j�Q��ʖڂ̃E�B���h�E�n���h��
     */
    void createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                      const char* prm_title1   , const char* prm_title2,
                      DWORD       prm_dwStyle1 , DWORD       prm_dwStyle2,
                      HWND&       out_hWnd1    , HWND&       out_hWnd2);

    /**
     * �E�B���h�E�������� .
     * @param prm_wndclass1 WNDCLASSEX�p�����[�^
     * @param prm_title1    �^�C�g��
     * @param prm_dwStyle1  �E�B���h�E���[�h���̃E�C���h�E1�̃X�^�C���萔
     * @param out_hWnd1     �i�߂�l�j�P��ʖڂ̃E�B���h�E�n���h��
     */
    void createWindow(WNDCLASSEX& prm_wndclass1,
                      const char* prm_title1   ,
                      DWORD       prm_dwStyle1 ,
                      HWND&       out_hWnd1     );

    /**
     * �E�B���h�E�������� .
     * �W���I�ȃE�B���h�E���쐬���܂��B
     * @param prm_WndProc �E�B���h�E�v���V�[�W���֐�
     * @param prm_title1 �P��ʖڂ̃^�C�g��
     * @param prm_title2 �Q��ʖڂ̃^�C�g��
     * @param out_hWnd1 �i�߂�l�j�P��ʖڂ̃E�B���h�E�n���h��
     * @param out_hWnd2 �i�߂�l�j�Q��ʖڂ̃E�B���h�E�n���h��
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title1, const char* prm_title2,
                      HWND&       out_hWnd1 , HWND&       out_hWnd2  );

    /**
     * �E�B���h�E�������� .
     * �W���I�ȃE�B���h�E���쐬���܂��B
     * @param prm_WndProc �E�B���h�E�v���V�[�W���֐�
     * @param prm_title1 �P��ʖڂ̃^�C�g��
     * @param prm_title2 �Q��ʖڂ̃^�C�g��
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title1, const char* prm_title2 = "window02");

    /**
     * �E�B���h�E�������� .
     * �E�B���h�E���[�h���̃E�C���h�E�X�^�C���萔�� WS_OVERLAPPEDWINDOW ���ݒ肳��܂��B
     * @param prm_wndclass1 �P��ʖڂ�WNDCLASSEX�p�����[�^
     * @param prm_wndclass2 �Q��ʖڂ�WNDCLASSEX�p�����[�^
     * @param prm_title1 �P��ʖڂ̃^�C�g��
     * @param prm_title2 �Q��ʖڂ̃^�C�g��
     * @param out_hWnd1 �i�߂�l�j�P��ʖڂ̃E�B���h�E�n���h��
     * @param out_hWnd2 �i�߂�l�j�Q��ʖڂ̃E�B���h�E�n���h��
     */
    void createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                      const char* prm_title1   , const char* prm_title2,
                      HWND&       out_hWnd1    , HWND&       out_hWnd2);

    /**
     * �E�B���h�E�������� .
     * �E�B���h�E���[�h���̃E�C���h�E�X�^�C���萔�� WS_OVERLAPPEDWINDOW ���ݒ肳��܂��B
     * @param prm_wndclass1 �P��ʖڂ�WNDCLASSEX�p�����[�^
     * @param prm_title1 �P��ʖڂ̃^�C�g��
     * @param out_hWnd1 �i�߂�l�j�P��ʖڂ̃E�B���h�E�n���h��
     */
    void createWindow(WNDCLASSEX& prm_wndclass1,
                      const char* prm_title1   ,
                      HWND&       out_hWnd1     );

    /**
     * �E�B���h�E�̃T�C�Y���Đݒ� .
     * @param hWnd �Đݒ肷��E�B���h�E��HWND
     * @param client_width �N���C�A���g�̈扡���i�s�N�Z���j
     * @param client_height �N���C�A���g�̈�c���i�s�N�Z���j
     */
    static void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height);

    static void chengeViewPos1(int pos);
    static void chengeViewPos2(int pos);
    static void chengeViewPos(HWND prm_pHWnd, int pos);
    static void chengeViewAspect(bool prm_b);

    /**
     * �E�B���h�E���������̍ő剻�ɂ���i�{�[�_�[���X�E�t���X�N���[���E�E�B���h�E�j .
     * @param prm_pHWnd �Ώۂ̃E�B���h�E�n���h��
     */
    static void chengeToBorderlessFullWindow(HWND prm_pHWnd);

    /**
     * �{�[�_�[���X�E�t���X�N���[���E�E�B���h�E�����ɖ߂� .
     * @param prm_pHWnd �Ώۂ̃E�B���h�E�n���h��
     */
    static void backToNomalWindow(HWND prm_pHWnd);

    /**
     * DirectX�̃f�o�C�X�̏����ݒ���s���B
     * @return E_FAIL:���s�^D3D_OK:����
     */
    virtual HRESULT initDevice();
    virtual void presentSpacetimeMoment() override;
    virtual void executeSpacetimeJudge() override;
    virtual void makeSpacetimeMaterialize() override;
    virtual void presentSpacetimeVisualize() override;
    virtual void finalizeSpacetime() override;


    /**
     * ���̐����擾 .
     * ���ʂŃI�[�o�[���C�h�\�B<BR>
     * @return ���̐�
     */
    virtual GgafDxSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (GgafDxSpacetime*)_pSpacetime;
    }


    virtual GgafDxModelManager* getModelManager() {
        return _pModelManager;
    }
    virtual GgafDxEffectManager* getEffectManager() {
        return _pEffectManager;
    }

    virtual GgafDxModelManager* createModelManager();
    virtual GgafDxEffectManager* createEffectManager();


    virtual void clean() override;

    virtual ~GgafDxGod();
};

}
#endif /*GGAFDXCORE_GGAFDXGOD_H_*/
