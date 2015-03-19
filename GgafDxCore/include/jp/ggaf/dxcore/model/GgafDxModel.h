#ifndef GGAFDXCORE_GGAFDXMODEL_H_
#define GGAFDXCORE_GGAFDXMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <d3d9.h>
#include <d3dx9.h>

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
    /** [r]���f���C���X�^���X��� */
    uint32_t _obj_model;
    /** [r]�}�e���A���z�� */
    D3DMATERIAL9* _paMaterial_default;
    /** [r]�}�e���A���� */
    DWORD _num_materials;

    /** [rw]���f���̋��E�����a�B��ʊO����ɗ��p����� */
    FLOAT _bounding_sphere_radius;
    /** [r]�_�ŋ��x (0.0 <= _power_blink <= 1.0)�BGgafDxTextureBlinker�ɂ�葀�삷�邱�� */
    FLOAT _power_blink;
    /** [r]�_�őΏ�RGB�l(0.0 <= tex2D()��rgb�̉��ꂩ <= 1.0)�BGgafDxTextureBlinker�ɂ�葀�삷�邱�� */
    FLOAT _blink_threshold;
    //_blink_threshold = 1.0 �Ǝw�肵���ꍇ�APS��tex2D()�̃T���v�����O�J���[��
    //r,g,b ���ꂩ >= 1.0 �� �̏ꍇ�A_power_blink�{���̐F(rgb)�����Z
    //�[�r�E�X�̃L�����̐Ԃ��_�ł̂悤�Ȃ��Ƃ��������������ߍ쐬�B

    /** [r]�e�N�X�`�������R�l�N�V�����z�� */
    GgafDxTextureConnection** _papTextureConnection;
    /** [r]�_�ő���x���I�u�W�F�N�g */
    GgafDxTextureBlinker* const _pTexBlinker;
    /** [r]GgafDxTextureBlinker��p�J�E���^�[ */
    frame _blinker_frames;

    /** [r/w]���f���̃X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
    float _specular;
    /** [r/w]���f���̃X�y�L�����[�̋��x�i�S�̂̔{���A0.0�ȊO��ݒ肷��ƃX�y�L�������L���ɂȂ�j */
    float _specular_power;

    /** [r]���f���P�ʂ̏������������s�ς݂��ǂ���(draw���`�F�b�N���ύX) */
    bool _is_init_model;

    UINT _num_pass;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    explicit GgafDxModel(const char* prm_model_name);

    char* getName(){
        return _model_name;
    }

    /**
     * �F���x�ƁA�ΏېF�������l��ݒ� .
     * �ΏېF�������l�Ƃ́A�F���x���e����^����Ώۂ̃e�N�X�`���̐F�̋�����ł��B<BR>
     * �s�N�Z���V�F�[�_�[�ɂ����āA<BR>
     * �E�����܂ł̌v�Z�����F�i�e�N�X�`���⃉�C�g�l���ς݁j�E�E�E colOut.rgba<BR>
     * �E�e�N�X�`���̐F �E�E�E colTex.rgba<BR>
     * �E�ΏېF�������l �E�E�E g_tex_blink_threshold<BR>
     * �E���݂̐F���x�l �E�E�E g_tex_blink_power<BR>
     * �Ƃ����ꍇ�A�ȉ��̗l�ȏ������s�Ȃ��Ă��܂��B<BR>
     * <code><pre>
     * <BR>
     * if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
     *     colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
     * }
     * </pre></code>
     * �[�r�E�X�̒n�㕨�̐Ԃ��_�ł̂悤�ȃG�t�F�N�g���ȒP�Ɏ������邽�߂Ɏ����E�E(��ɺ����
     * @param prm_power_blink �F���x�l1 (���̐� �` 0:�� �` 1.0:���{���x �` )
     * @param prm_blink_threshold �F���x�l���e������ΏېF�������l (0.0 �` 1.0)
     */
    void setBlinkPower(float prm_power_blink, float prm_blink_threshold) {
        _power_blink = prm_power_blink;
        _blink_threshold = prm_blink_threshold;
    }

    /**
     * �F���x�l�݂̂�ݒ� .
     * @param prm_power_blink �F���x�l1 (���̐� �` 0:�� �` 1.0:���{���x �` )
     */
    void setBlinkPower(float prm_power_blink) {
        _power_blink = prm_power_blink;
    }
    /**
     * �F���x���f�Ώۂ̐F�������l��ݒ� .
     * @param prm_blink_threshold �F���x�l���e������ΏېF�������l (0.0 �` 1.0)
     */
    void setBlinkThreshold(float prm_blink_threshold) {
        _blink_threshold = prm_blink_threshold;
    }
    /**
     * �F���x�l���擾 .
     * @return �F���x�l
     */
    float getBlinkPower() {
        return _power_blink;
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


    inline GgafDxTextureBlinker* getTexBlinker() {
        return _pTexBlinker;
    }

    /**
     * ���f����`�� .
     * ���ʃN���X�Ń��f���`�惍�W�b�N���������ĉ������B
     * @param prm_pActor_target �`�悷�郂�f���̃A�N�^�[
     * @param prm_draw_set_num �`�悷�郂�f���̃Z�b�g��
     * @return
     */
    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) = 0;

    /**
     * �}�e���A���̃e�N�X�`�������ւ��Đ؂�ւ���B .
     * �\�߃��f���ɕ����̃e�N�X�`��(�}�e���A��)��o�^���Ēu���K�v������B<BR>
     * ��̓I�ɂ� X �t�@�C���ŗ\�ߕ����}�e���A���G���g���i�e�N�X�`���j�������Ă����B<BR>
     * @param prm_texture0 �\�߃��f���ɕ����̃e�N�X�`���̐؂�ւ����̃e�N�X�`��ID
     *                    �i��GgafDxTextureManager �ɃG���g������Ă��鎯�ʕ�����j
     */
    virtual void swapTopTextureOrder(const char* prm_texture0);

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
#endif /*GGAFDXCORE_GGAFDXMODEL_H_*/
