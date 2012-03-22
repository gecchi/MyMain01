#ifndef GGAFDXEFFECT_H_
#define GGAFDXEFFECT_H_
namespace GgafDxCore {

/**
 * �G�t�F�N�g���N���X.
 * �L����(�A�N�^�[)�̃G�t�F�N�g��ێ�����N���X�ł��B<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffect : public GgafCore::GgafObject {
    friend class GgafDxEffectManager;

protected:
    static D3DXMACRO _aD3DXMacro_Defines[3];

public:
    D3DXHANDLE _h_alpha_master;
    /** [r]�G�t�F�N�g��`�̎��ʖ��B(50�����܂�) */
    char* _effect_name;
    /** [r]�G�t�F�N�g */
    ID3DXEffect* _pID3DXEffect;
#ifdef MY_DEBUG
    bool _begin;
#endif
    /**
     * �R���X�g���N�^<BR>
     * @param prm_effect_name �G�t�F�N�g��`�̎��ʖ��B".fx"��ǉ�����ƃG�t�F�N�g�t�@�C�����ɂȂ�B
     */
    GgafDxEffect(char* prm_effect_name);

    char* getName() {
        return _effect_name;
    }

    /**
     * 1�t���[����1����s���邾���ŗǂ��G�t�F�N�g�p�����[�^��
     * ���̃��\�b�h�ɋL�q����B
     */
    virtual void setParamPerFrame() = 0;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDxEffectManager�ł���<BR>
     */
    virtual ~GgafDxEffect();
};

}
#endif /*GGAFDXEFFECT_H_*/
