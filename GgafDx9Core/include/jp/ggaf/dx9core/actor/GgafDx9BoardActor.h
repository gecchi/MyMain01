#ifndef GGAFDX9BOARDACTORD_H_
#define GGAFDX9BOARDACTORD_H_
namespace GgafDx9Core {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[.
 * GgafDx9TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�B<BR>
 * �P���\���i��]�g�喳���j�̂��ߍ����B�X�R�A�\����A�w�i���Ɏg�p���悤�B<BR>
 * �Q�c�Q�[�������Ȃ�A�I�u�W�F�N�g�͂��̃N���X��{�ł�����B<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardActor : public GgafDx9DrawableActor {
private:

//    struct VERTEX {
//        float x, y, z; // ���_���W
//        float tu, tv; // �e�N�X�`�����W
//    };

    /** �����A�j���p�^�[���p�J�E���^�[ */
    int _pattno_counter;
    /** �����A�j���t���[���p�J�E���^ */
    int _aniframe_counter;

public:
    /** ���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDx9BoardModel* _pBoardModel;
    /** �G�t�F�N�g */
    GgafDx9BoardEffect* _pBoardEffect;

//    /** ��`�̒��_��� */
//    VERTEX* _paVertex;
//    /** ��`�̒��_���v�̃T�C�Y */
//    UINT _size_vertices;
//    /** 1���_�̃T�C�Y */
//    UINT _size_vertex_unit;

    /** �p�^�[���ԍ��̏�� */
    int _pattno_top;
    /** �p�^�[���ԍ��̉��� */
    int _pattno_bottom;
    /** ���ݕ\�����̃A�j���p�^�[���ԍ� */
    int _patteno_now;

    GgafDx9BoardActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique );

    /**
     * ��OverRide �ł���<BR>
     */
    virtual void processDraw();

    virtual void setPatternNo(int prm_patteno);

//    void setAlpha(float prm_fAlpha) {
//        _fAlpha = prm_fAlpha;
//    }
//
//    float getAlpha() {
//        return _fAlpha;
//    }

    virtual ~GgafDx9BoardActor(); //�f�X�g���N�^

    //virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
