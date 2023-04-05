#ifndef GGAF_DX_CARETAKER_H_
#define GGAF_DX_CARETAKER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


/**
 * �Ǘ��҂��ێ����� CurveManufactureManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X�F�Ȑ��ړ��̏�񎯕ʕ�����B�v���p�e�B DIR_CURVE �z���́uX + ".ldr"�v�Ƃ����t�@�C�������g�p����
 * "FormationOebius002,1" �̈Ӗ��B�ǂݍ��ރt�@�C��=FormationOebius002.ldr
 * 1 �͍̗p����X�v���C���̃C���f�b�N�X(0�`)������킷�B
 * CURVE=mobius1.spl,mobius3.spl,mobius5.spl
 * ��`����Ă����ꍇ 1=mobius3.spl �̃f�[�^���̗p
 */
#define connectToCurveManufactureManager(X) ((GgafDx::CurveManufactureConnection*)((pCARETAKER)->_pCurveManufManager->connect((X), this)))

/**
 * �Ǘ��҂��ێ����� CurveSourceManager �ɐڑ����A�R�l�N�V�������擾�B
 * X�F���ʕ�����iCurveSourceManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) �� prm_idstr �ɓn��)
 */
#define connectToCurveSourceManager(X)   ((GgafDx::CurveSourceConnection*)((pCARETAKER)->_pCurveSrcManager->connect((X), this)))

#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1

#undef pCARETAKER
#define pCARETAKER ((GgafDx::Caretaker*)GgafCore::Caretaker::ask())

namespace GgafDx {

/**
 * DirectX�Ǘ��� .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class Caretaker : public GgafCore::Caretaker {

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
    /** �t���X�N���[�����A�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[���A�Y���̓f�B�X�v���C�A�_�v�^�ԍ� */
    IDirect3DSwapChain9** _papSwapChain;
    /** �t���X�N���[�����ADirectX�̃o�b�N�o�b�t�@�A�Y���̓f�B�X�v���C�A�_�v�^�ԍ�  */
    IDirect3DSurface9** _papBackBuffer;

    /** �f�o�C�X�쐬���p�����[�^�[�z��A�Y���̓f�B�X�v���C�A�_�u�^�ԍ� */
    D3DPRESENT_PARAMETERS* _paPresetPrm;
    /** ����̗p����Ă���f�o�C�X�z��A�Y���̓f�B�X�v���C�A�_�u�^�ԍ��iWDDM�g�p���̂ݕK�v�j */
    D3DDISPLAYMODEEX* _paDisplayMode;


private:
    /**
     * WDDM���ǂ������肵�A�f�o�C�X���쐬 .
     * ���ʂ� Caretaker::_pID3D9 �� pCARETAKER->_pID3DDevice9�ɕێ������B
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


    void setFullScreenWindowPos();

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
            GGAF_DELETEARR_NULLABLE(paModes);
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
            if (paRezoInfo) {
                GGAF_DELETEARR_NULLABLE(paRezoInfo);
            }
            paRezoInfo = NEW RezoInfo[rezo_num];
        }
        ~AdapterRezos() {
            GGAF_DELETEARR_NULLABLE(paRezoInfo);
        }
    };
    /** �g�p�\�ȃf�o�C�X�̃A�_�v�^�̉𑜓x���Z�b�g */
    AdapterRezos* _paAdapterRezos;
    ////////////////////////////////////////////////////////////

    /** ���f��(Model)�����Ǘ��� */
    ModelManager* _pModelManager;
    /** �G�t�F�N�g(Effect)�����Ǘ��� */
    EffectManager* _pEffectManager;
    /** ���}�b�v�p�e�N�X�`���[(Texture)�����Ǘ��ҁB�i���ʏ�̃e�N�X�`����Model�̓����Ǘ��j */
    TextureManager* _pCubeMapTextureManager;
    /** �o���v�}�b�v�p�e�N�X�`���[(Texture)�����Ǘ��ҁB�i���ʏ�̃e�N�X�`����Model�̓����Ǘ��j */
    TextureManager* _pBumpMapTextureManager;
    /** [r] 1��ʖڂ̃E�B���h�E�n���h��  */
    HWND _pHWndPrimary;
    /** [r] 2��ʖڂ̃E�B���h�E�n���h��  */
    HWND _pHWndSecondary;
    /** [r] �E�B���h�E�n���h��  */
    HWND* _paHWnd;
    /** [r] �{�A�v���P�[�V�����̃C���X�^���X�n���h�� */
    HINSTANCE _hInstance;
    /** [r] �f�o�b�O���[�h���A���C���[�t���[���\�� */
    D3DFILLMODE _d3dfillmode;
    /** [r] DirectX9�̃I�u�W�F�N�g */
    IDirect3D9* _pID3D9;
    /** [r] �f�o�C�X */
    IDirect3DDevice9* _pID3DDevice9;
    /** [r] �f�t�H���g�̃��C�g */
    D3DLIGHT9 _d3dlight9_default;
    /** [r] �f�o�C�X���X�g�t���O (true=���X�g��) */
    bool _is_device_lost_flg;
    /** [r] ��ʃA�X�y�N�g�䒲���t���O (true=�E�B���h�E�����T�C�Y����A�\���̈���Čv�Z) */
    bool _adjustGameWindow;
//    /** [r] �\���̈���Čv�Z���K�v�ȃE�B���h�E(�̃n���h��) */
//    HWND _pHWnd_adjustScreen;

    /** [r] ���_�V�F�[�_�[�̃o�[�W����(D3DVS_VERSION(_Major,_Minor)) */
    uint32_t _vs_v;
    /** [r] �s�N�Z���V�F�[�_�[�̃o�[�W����(D3DPS_VERSION(_Major,_Minor)) */
    uint32_t _ps_v;

    /** [r] �Q�[���o�b�t�@�̈�(�s�N�Z���I�Ȍn) */
    RECT _rectGameBuffer;
    /** [r] �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`������̃R�s�[���̈�(�s�N�Z��) */
    RECT _rectRenderBufferSource;
    /** [r] �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`������̃R�s�[���̈�́A[0]:�������̈�A[1]:�E�����̈� (�s�N�Z��) */
    RECT _aRect_HarfRenderBufferSource[2];
    /** [r] �ŏI�\���t�����g�o�b�t�@�t���[���̗̈�A[0]:�P��ʖځA[1]:�Q��ʖ� (�s�N�Z��) */
    RECT _aRect_FullScreen[2];
    /** [r] Present�̈�(�t���X�N���[�����A�܂��̓E�B���h�E���A�X�y�N�gFIX�̏ꍇ)�A[0]:�P��ʖځA[1]:�Q��ʖ� (�s�N�Z��) */
    RECT _aRect_Present[2];
    /** [r] �P��ʖڃA�_�v�^�ԍ��A _aRect_HarfRenderBufferSource[] �̏��� 0 �` */
    int _primary_game_view_display_no;
    /** [r] �Q��ʖڃA�_�v�^�ԍ��A _aRect_HarfRenderBufferSource[] �̏��� 0 �` */
    int _secondary_game_view_display_no;

public:
    CurveSourceManager* _pCurveSrcManager;
    CurveManufactureManager* _pCurveManufManager;

public:
    /**
     * �R���X�g���N�^<BR>
     */
    Caretaker();

    void setDisplaySizeInfo();

    /**
     * �K�؂ȉ𑜓x�ݒ���s�� .
     * @param allow_chang_rezo true:�𑜓x�ύX��������^false:�𑜓x�ύX�͂��Ȃ�
     */
    void setAppropriateDisplaySize(bool allow_chang_rezo = true);


    /**
     * �t���X�N���[�����A�ł��Ó��ȉ𑜓x��T���B
     * @param prm_paRezos �𑜓x���z��
     * @param prm_rezo_num �𑜓x�z��̗v�f��
     * @param prm_width ���]�̉𑜓x�̕�
     * @param prm_height ���]�̉𑜓x�̍���
     * @return �ł��Ó��ȗv�f�C���f�b�N�X
     */
    int checkAppropriateDisplaySize(Caretaker::RezoInfo* prm_paRezos, int prm_rezo_num,
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
     * @param out_hWnd1 �i�߂�l�j�P��ʖڂ̃E�B���h�E�n���h��
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title1,
                      HWND& out_hWnd1);

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
    void resetInitWindowsize();
    void resetDotByDotWindowsize(int d);
    void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height);

    void chengeViewPos1(int pos);
    void chengeViewPos2(int pos);
    void chengeViewPos(HWND prm_pHWnd, int pos);
    void chengeViewAspect(bool prm_b);

    /**
     * �E�B���h�E���������̍ő剻�ɂ���i�{�[�_�[���X�E�t���X�N���[���E�E�B���h�E�j .
     * @param prm_pHWnd �Ώۂ̃E�B���h�E�n���h��
     */
    void chengeToBorderlessFullWindow(HWND prm_pHWnd);

    /**
     * �{�[�_�[���X�E�t���X�N���[���E�E�B���h�E�����ɖ߂� .
     * @param prm_pHWnd �Ώۂ̃E�B���h�E�n���h��
     */
    void backToNomalWindow(HWND prm_pHWnd);

    /**
     * DirectX�̃f�o�C�X�̏����ݒ���s���B
     * @return E_FAIL:���s�^D3D_OK:����
     */
    virtual HRESULT initDevice();
    virtual void presentMoment() override;
    virtual void presentBehave() override;
    virtual void presentJudge() override;
    virtual void presentMaterialize() override;
    virtual void presentVisualize() override;
    virtual void presentClosing() override;


    /**
     * ���̐����擾 .
     * ���ʂŃI�[�o�[���C�h�\�B<BR>
     * @return ���̐�
     */
    virtual Spacetime* getSpacetime() override {  //���ς̖߂�l
        return (Spacetime*)_pSpacetime;
    }

    virtual ModelManager* getModelManager() {
        return _pModelManager;
    }
    virtual EffectManager* getEffectManager() {
        return _pEffectManager;
    }

    virtual ModelManager* createModelManager();
    virtual EffectManager* createEffectManager();

    virtual CurveSourceManager* createCurveSourceManager();
    virtual CurveManufactureManager* createCurveManufactureManager();

    /**
     * ���C�g�̐F�i�f�t�H���g�F1.0, 1.0, 1.0�j��ݒ� .
     * �y���ӁzEffect�I�u�W�F�N�g���쐬�����O�ɐݒ肵�Ȃ��Ɣ��f������Ȃ��B
     * @param r
     * @param g
     * @param b
     */
    void setLightDiffuseColor(float r, float g, float b);

    /**
     * �����̐F��ݒ�i�f�t�H���g�F0.2, 0.2, 0.2�j .
     * �y���ӁzEffect�I�u�W�F�N�g���쐬�����O�ɐݒ肵�Ȃ��Ɣ��f������Ȃ��B
     * @param r
     * @param g
     * @param b
     */
    void setLightAmbientColor(float r, float g, float b);

    virtual void clean() override;

    virtual ~Caretaker();
};

}
#endif /*GGAF_DX_CARETAKER_H_*/
