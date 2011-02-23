#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_
namespace GgafDx9Core {

/**
 * �p�y�b�^�[(����l�`����) .
 * �p�y�b�g(GgafDx9D3DXAniMeshActor)�����ő���A���[�V���������������܂��B<BR>
 * �p�y�b�g�ɑ΂��ē�����2��ނ̃��[�V�����܂ł����o���܂���(���ő�g���b�N��2)<BR>
 * �l�`����������r�͂Q�{���������̂ŁA�����͂������Ȃ��ł��l�B<BR>
 * �������g���āA�p�y�b�g�����܂������Ă��������B<BR>
 * �܂�AID3DXAnimationController ���b�p�[�N���X�ł��B<BR>
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9Puppeteer : public GgafCore::GgafObject {
private:

public:
    /** ������� */
    GgafDx9D3DXAniMeshActor* _pPuppet;
    GgafDx9D3DXAniMeshModel* _pModel;
    ID3DXAnimationController* _pAc;

    LPD3DXANIMATIONSET* _papAnimationSet;
    double* _pa_as_anime_time;
    float* _pa_as_anime_speed;
    float* _pa_as_weight;

    UINT _num_animation_set;
    UINT _num_tracks;

    /** �A�N�e�B�u�Ȏ� 0:�E��^1:���� */
    UINT _hand;

    double _advance_time_per_draw;

    /**
     * �R���X�g���N�^ .
     * @param prm_pActor �������
     * @return
     */
    GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet);


    virtual ~GgafDx9Puppeteer();

    void play(UINT anim_set_id);
    void play();
    void stop();


    virtual void behave();
    virtual void work();


};

}
#endif /*GGAFDX9PUPPETEER_H_*/
