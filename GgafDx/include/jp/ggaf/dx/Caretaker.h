#ifndef GGAF_DX_CARETAKER_H_
#define GGAF_DX_CARETAKER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include <map>


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

#define connectToTextureManager(X) ((GgafDx::TextureConnection*)(pCARETAKER)->_pTextureManager->connect((X), this))

#define connectToModelManager(X) ((GgafDx::ModelConnection*)(pCARETAKER)->_pModelManager->connect((X), this))

#define connectToEffectManager(X) ((GgafDx::EffectConnection*)(pCARETAKER)->_pEffectManager->connect((X), this))


#undef pCARETAKER
#define pCARETAKER ((GgafDx::Caretaker*)GgafCore::Caretaker::ask())

#define SCREEN01 0
#define SCREEN02 1
#define SCREEN03 2
#define SCREEN04 3
#define SCREEN05 4
#define SCREEN06 5
#define SCREEN07 6
#define SCREEN08 7
#define SCREEN09 8
#define SCREEN10 9
#define SCREEN11 10
#define SCREEN12 11
#define SCREEN13 12
#define SCREEN14 13
#define SCREEN15 14
#define SCREEN16 15

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
    /** �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`���̃T�[�t�F�C�X */
    IDirect3DSurface9*  _pRenderTextureSurface;
    /** �t���X�N���[�����A�����_�����O�^�[�Q�b�g��Z�o�b�t�@�̃T�[�t�F�C�X */
    IDirect3DSurface9*  _pRenderTextureZ;
    /** �t���X�N���[�����A�A�_�v�^�Ɋ֘A�t�����ꂽ�X���b�v�`�F�[���A�Y���̓f�B�X�v���C�A�_�v�^�ԍ� */
    IDirect3DSwapChain9** _papSwapChain;
    /** �t���X�N���[�����ADirectX�̃o�b�N�o�b�t�@�A�Y���̓f�B�X�v���C�A�_�v�^�ԍ�  */
    IDirect3DSurface9** _papBackBuffer;

    /** �f�o�C�X�쐬���p�����[�^�[�z��A�Y���̓f�B�X�v���C�A�_�u�^�ԍ�(�A���A�Œ� MAX_SCREENS ����) */
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
     */
    void adjustGameWindow();
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
    /** �g�p�\�ȃf�o�C�X�̃f�B�X�v���C�A�_�v�^�� */
    int _num_adapter;
    /** �g�p�\�ȃf�o�C�X�̃A�_�v�^�̏��Z�b�g�A�v�f���� _num_adapter  */
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
    /** �g�p�\�ȃf�o�C�X�̃A�_�v�^�̉𑜓x���Z�b�g�A�v�f���� _num_adapter */
    AdapterRezos* _paAdapterRezos;
    ////////////////////////////////////////////////////////////

    TextureManager* _pTextureManager;
    /** ���f��(Model)�����Ǘ��� */
    ModelManager* _pModelManager;
    /** �G�t�F�N�g(Effect)�����Ǘ��� */
    EffectManager* _pEffectManager;
    /** [r] 1��ʖڂ̃E�B���h�E�n���h��  */
    HWND _pHWndPrimary;
    /** [r] �E�B���h�E�n���h���̔z��A�v�f�̓Y���� D3DPRESENT_PARAMETERS�v�f�ԍ�(�A�_�v�^�ԍ��܂�) */
    HWND* _paHWnd;
    /** [r] window���B�E�C���h�E���[�h���� NUMBER_OF_SCREENS_USED�A�t���X�N���[�����̓A�_�v�^���B */
    int _num_window;

    int _screen_display_no[MAX_SCREENS];
    /** [r]window�C���f�b�N�X(=�t���X�N���[�����̓A�_�v�^�C���f�b�N�X) �� �X�N���[���v���C�I���e�B�B0:SCREEN01/1:SCREEN02/2:TERTIARY */
    int* _paWindowNoToScreenPry;

    /** [r] HWND => �X�N���[���v���C�I���e�B�B0:SCREEN01/1:SCREEN02/2:TERTIARY */
    std::map<HWND, int> _mapHwndToPry;
    /** [r] HWND => �A�_�v�^�ԍ� */
    std::map<HWND, int> _mapHwndToWindowNo;

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

    /** [r] ���_�V�F�[�_�[�̃o�[�W����(D3DVS_VERSION(_Major,_Minor)) */
    uint32_t _vs_v;
    /** [r] �s�N�Z���V�F�[�_�[�̃o�[�W����(D3DPS_VERSION(_Major,_Minor)) */
    uint32_t _ps_v;

    /** [r] �Q�[���o�b�t�@�̈�(�s�N�Z���I�Ȍn) */
    RECT _rectGameBuffer;
    /** [r] �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`������̃R�s�[���̈�(�s�N�Z��) */
//    RECT _aRectRenderBufferSource[SCREEN01];
    /** [r] �t���X�N���[�����A�����_�����O�^�[�Q�b�g�e�N�X�`������̃R�s�[���̈�́A[0]:�������̈�A[1]:�E�����̈� (�s�N�Z��) */
    RECT _aRectRenderBufferSource[MAX_SCREENS];
    /** [r] �ŏI�\���t�����g�o�b�t�@�t���[���̗̈�A[0]:�P��ʖځA[1]:�Q��ʖ� (�s�N�Z��) */
    RECT _aRect_FullScreen[MAX_SCREENS];
    /** [r] Present�̈�(�t���X�N���[�����A�܂��̓E�B���h�E���A�X�y�N�gFIX�̏ꍇ)�A[0]:�P��ʖځA[1]:�Q��ʖ� (�s�N�Z��) */
    RECT _aRect_Present[MAX_SCREENS];
    /** [r] �P��ʖڃA�_�v�^�ԍ��A _aRectRenderBufferSource[] �̏��� 0 �` */
    int _primary_screen_adpter_no;
    /** [r] �Q��ʖڃA�_�v�^�ԍ��A _aRectRenderBufferSource[] �̏��� 0 �` */
//    int _secondary_screen_adpter_no;

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
     * @param prm_WndProc �E�B���h�E�v���V�[�W��
     * @param prm_title �E�B���h�E�^�C�g���i�Q��ʖڈȍ~�A�^�C�g��������"(2)"�Ɖ�ʔԍ�������ɕt�^�j
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title);

    /**
     * �E�B���h�E�������� .
     * @param prm_wndclass �E�B���h�E��WNDCLASSEX�p�����[�^
     * @param prm_title �E�B���h�E�^�C�g���i�Q��ʖڈȍ~�A�^�C�g��������"(2)"�Ɖ�ʔԍ�������ɕt�^�j
     * @param prm_dwStyle �E�B���h�E���[�h���̃X�^�C���萔
     */
    void createWindow(WNDCLASSEX& prm_wndclass,
                      const char* prm_title   ,
                      DWORD       prm_dwStyle );

    int getNumWindow() {
        return _num_window;
    }
    HWND getHWND(int prm_pry) {
        return _paHWnd[prm_pry];
    }
    /**
     * �E�B���h�E�̃T�C�Y���Đݒ� .
     * @param hWnd �Đݒ肷��E�B���h�E��HWND
     * @param client_width �N���C�A���g�̈扡���i�s�N�Z���j
     * @param client_height �N���C�A���g�̈�c���i�s�N�Z���j
     */
    void resetInitWindowsize();
    void resetDotByDotWindowsize(int d);
    void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height);

    void chengePrimaryScreenPresentPos(int pos);
    void chengeSecondaryScreenPresentPos(int pos);
    void chengeScreenPresentPos(HWND prm_pHWnd, int pos);

    void chengeViewAspect1(bool prm_b);
    void chengeViewAspect2(bool prm_b);
    void chengeViewAspect(HWND prm_pHWnd, bool prm_b);

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

    virtual TextureManager* getTextureManager() {
        return _pTextureManager;
    }

    virtual ModelManager* getModelManager() {
        return _pModelManager;
    }

    virtual EffectManager* getEffectManager() {
        return _pEffectManager;
    }

    virtual TextureManager* createTextureManager();
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
