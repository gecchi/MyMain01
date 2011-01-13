#ifndef GGAFDX9MODEL_H_
#define GGAFDX9MODEL_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2008/02/21
 * @author Masatoshi Tsuge
 */
class GgafDx9Model : public GgafCore::GgafObject {
    friend class GgafDx9ModelManager;

protected:
public:
    /** [r]ID */
    int _id;
    /** [r]�ő�\�����`��Z�b�g���i�L�����N�^���j*/
    int _set_num;
    /** [r]���f����`�̎��ʖ��B(50�����܂�) */
    char* _model_name;

    /** [r]�}�e���A���z�� */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** [r]�}�e���A���� */
    DWORD _dwNumMaterials;

    /** [rw]���f���̋��E�����a�B��ʊO����ɗ��p����� */
    FLOAT _fBoundingSphereRadius;
    /** [r]�_�ŋ��x (0.0 <= _fblink <= 1.0)�BGgafDx9TextureBlinker�ɂ�葀�삷�邱�� */
    FLOAT _fPowerBlink;
    /** [r]�_�őΏ�RGB�l(0.0 <= tex2D()��rgb�̉��ꂩ <= 1.0)�BGgafDx9TextureBlinker�ɂ�葀�삷�邱�� */
    FLOAT _fBlinkThreshold;
    //_fBlinkThreshold = 1.0 �Ǝw�肵���ꍇ�APS��tex2D()�̃T���v�����O�J���[��
    //r,g,b ���ꂩ >= 1.0 �� �̏ꍇ�A_fPowerBlink�{���̐F(rgb)�����Z
    //�[�r�E�X�̒n�㕨�j���̐Ԃ��_�ł̂悤�Ȃ��Ƃ������������B

    /** [r]�e�N�X�`�������R�l�N�V�����z�� */
    GgafDx9TextureConnection** _papTextureCon;
    /** [r]�_�ő���x���I�u�W�F�N�g */
    GgafDx9TextureBlinker* _pTextureBlinker;
    frame _frame_blinker;
    /** [r]���f���P�ʂ̏������������s�ς݂��ǂ���(draw���`�F�b�N���ύX) */
    bool _is_init_model;
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9Model(char* prm_model_name);

    char* getName(){
        return _model_name;
    }


    /**
     * ���f����`�悵�܂�.
     * @param prm_pActor_Target �`�悷�郂�f���̃A�N�^�[
     * @return HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) = 0;

    /**
     * ���f�����č\�z���܂�.
     */
    virtual void restore() = 0;

    /**
     * ���f����������܂�.
     */
    virtual void release() = 0;

    /**
     * �f�o�C�X���X�g���R�[���o�b�N
     */
    virtual void onDeviceLost() = 0;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9ModelManager�ł���<BR>
     */
    virtual ~GgafDx9Model(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MODEL_H_*/
