#ifndef GGAFDXMODEL_H_
#define GGAFDXMODEL_H_
namespace GgafDxCore {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2008/02/21
 * @author Masatoshi Tsuge
 */
class GgafDxModel : public GgafCore::GgafObject {
    friend class GgafDxModelManager;

protected:
public:
    class VERTEX_3D_BASE {
    public:
        float x, y, z;    // ���_���W
        float nx, ny, nz; // �@��
    };


    /** [r]ID */
    int _id;
    /** [r]�ő�\�����`��Z�b�g���i�L�����N�^���j*/
    int _set_num;
    /** [r]���f����`�̎��ʖ��B(50�����܂�) */
    char* _model_name;

    /** [r]�}�e���A���z�� */
    D3DMATERIAL9* _paMaterial_default;
    /** [r]�}�e���A���� */
    DWORD _num_materials;

    /** [rw]���f���̋��E�����a�B��ʊO����ɗ��p����� */
    FLOAT _bounding_sphere_radius;
    /** [r]�_�ŋ��x (0.0 <= _fblink <= 1.0)�BGgafDxTextureBlinker�ɂ�葀�삷�邱�� */
    FLOAT _power_blink;
    /** [r]�_�őΏ�RGB�l(0.0 <= tex2D()��rgb�̉��ꂩ <= 1.0)�BGgafDxTextureBlinker�ɂ�葀�삷�邱�� */
    FLOAT _blink_threshold;
    //_blink_threshold = 1.0 �Ǝw�肵���ꍇ�APS��tex2D()�̃T���v�����O�J���[��
    //r,g,b ���ꂩ >= 1.0 �� �̏ꍇ�A_power_blink�{���̐F(rgb)�����Z
    //�[�r�E�X�̃L�����̐Ԃ��_�ł̂悤�Ȃ��Ƃ��������������ߍ쐬�B

    /** [r]�e�N�X�`�������R�l�N�V�����z�� */
    GgafDxTextureConnection** _papTextureCon;
    /** [r]�_�ő���x���I�u�W�F�N�g */
    GgafDxTextureBlinker* _pTextureBlinker;
    /** [r]GgafDxTextureBlinker��p�J�E���^�[ */
    frame _blinker_frames;

    /** [r/w]���f���̃X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
    float _specular;
    /** [r/w]���f���̃X�y�L�����[�̋��x�i�S�̂̔{���A0.0�ȊO��ݒ肷��ƃX�y�L�������L���ɂȂ�j */
    float _specular_power;

    /** [r]���f���P�ʂ̏������������s�ς݂��ǂ���(draw���`�F�b�N���ύX) */
    bool _is_init_model;

    UINT _numPass;
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxModel(char* prm_model_name);

    char* getName(){
        return _model_name;
    }

    /**
     * ���f���̃X�y�L�����[���x��ݒ� .
     * �����̈����� 0 �ȊO�̐��l��ݒ肷��ƁA�X�y�L�����[���L���ɂȂ�܂��B
     * ���̂悤�ɐݒ肷��ƃX�y�L�����[�𖳌��ɏo���܂��B�i�f�t�H���g�̓X�y�L�����[�𖳌��j
     * setSpecular(0, 0)
     * @param prm_specular ���f���̃X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j
     * @param prm_specular_power ���f���̃X�y�L�����[�̋��x�i�S�̂̔{���A0.0�ȊO��ݒ肷��ƃX�y�L�������L���ɂȂ�j
     */
    virtual void setSpecular(float prm_specular, float prm_specular_power) {
        _specular = prm_specular;
        _specular_power = prm_specular_power;
    }

    /**
     * ���f����`�� .
     * ���ʃN���X�Ń��f���`�惍�W�b�N���������ĉ������B
     * @param prm_pActor_Target �`�悷�郂�f���̃A�N�^�[
     * @param prm_draw_set_num �`�悷�郂�f���̃Z�b�g��
     * @return
     */
    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) = 0;

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
     * delete����̂�GgafDxModelManager�ł���<BR>
     */
    virtual ~GgafDxModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXMODEL_H_*/
