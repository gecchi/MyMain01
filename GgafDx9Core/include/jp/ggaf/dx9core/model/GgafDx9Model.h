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
    /** ID */
    int _id;

    /** ���f����`�̎��ʖ��B(50�����܂�) */
    char* _model_name;
    /** ����GgafDx9Model�ւ̃|�C���^�B�I�[��NULL */
    //GgafDx9Model*	_pModel_Next;

    /** �}�e���A���z�� */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** �}�e���A���� */
    DWORD _dwNumMaterials;

    /** ���̃��f���̃��[�J�����W�̌��_����S���_�̋����ōő�̒��� */
    FLOAT _max_radius;
    /** �_�ŋ��x (0.0 <= _fblink <= 1.0)�AGgafDx9TextureBlinker�ɂ�葀��o���� */
    FLOAT _fPowerBlink;
    /** �_�őΏ�RGB�l(0.0 <= tex2D()��rgb�̉��ꂩ <= 1.0) */
    FLOAT _fBlinkThreshold;
    //_fBlinkThreshold = 1.0 �Ǝw�肵���ꍇ�APS��tex2D()�̃T���v�����O�J���[��
    //r,g,b ���ꂩ >= 1.0 �� �̏ꍇ�A_fPowerBlink�{���̐F(rgb)�����Z
    //�[�r�E�X�̒n�㕨�j���̐Ԃ��_�ł̂悤�Ȃ��Ƃ������������B

    /** �e�N�X�`�������R�l�N�V�����z�� */
    GgafDx9TextureConnection** _papTextureCon;
    /** �_�ő���x���I�u�W�F�N�g */
    GgafDx9TextureBlinker* _pTextureBlinker;
    DWORD _frame_blinker;
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
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target) = 0;

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
