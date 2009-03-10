#ifndef GGAFDX9BOARDACTORD_H_
#define GGAFDX9BOARDACTORD_H_
namespace GgafDx9Core {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[.
 * GgafDx9TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł�<BR>
 */
class GgafDx9BoardActor : public GgafDx9TransformedActor {
private:

    struct VERTEX {
        float x, y, z; // ���_���W
        float tu, tv; // �e�N�X�`�����W
    };

    /** �����A�j���p�^�[���p�J�E���^�[ */
    int _pattno_counter;
    /** �����A�j���t���[���p�J�E���^ */
    int _aniframe_counter;

public:
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9BoardModel* _pBoardModel;
    /** �G�t�F�N�g */
    GgafDx9EffectConnection* _pEffectCon;
    GgafDx9BoardEffect* _pBoardEffect;

    /** �L�����S�̂̃� */
    float _fAlpha;

    /** ��`�̒��_��� */
    VERTEX* _paVertex;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertecs;
    /** 1���_�̃T�C�Y */
    UINT _size_vertec_unit;

    /** �A�j���p�^�[���ԍ��̏���ԍ� */
    int _pattno_top;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ� */
    int _pattno_bottom;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ� */
    int _patteno_now;

    GgafDx9BoardActor(const char* prm_name, const char* prm_spritemodel_name);

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDrawMain();

    virtual void setPatternNo(int prm_patteno);

    void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    float getAlpha() {
        return _fAlpha;
    }

    virtual ~GgafDx9BoardActor(); //�f�X�g���N�^

    //virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
