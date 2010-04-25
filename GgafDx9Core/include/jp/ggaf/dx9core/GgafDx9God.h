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
    static HWND _hWnd;
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

    /** Present�̈� */
    static RECT _rectPresentDest;
    /* �X�N���[�������i�s�N�Z���j */
    //static int const GAME_SCREEN_HEIGHT;

    static D3DPRESENT_PARAMETERS _structD3dPresent_Parameters;

    /** �f�o�C�X���X�g�t���O (true=���X�g��) */
    static bool _is_device_lost_flg;


//    /** �ˉe�ϊ�������� */
//    static D3DXMATRIX _vMatrixProj;
//    /** ���ˉe�ϊ�������� */
//    static D3DXMATRIX _vMatrixOrthoProj;
//

    static GgafDx9ModelManager* _pModelManager;
    static GgafDx9EffectManager* _pEffectManager;


    /**
     * �R���X�g���N�^<BR>
     */
    GgafDx9God(HINSTANCE prm_hInstance, HWND prm_hWnd);

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


    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9God();
};

}
#endif /*GGAFDX9GOD_H_*/
