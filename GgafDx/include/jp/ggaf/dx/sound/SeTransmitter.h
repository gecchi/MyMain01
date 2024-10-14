#ifndef GGAF_DX_SEREFLECTOR_H_
#define GGAF_DX_SEREFLECTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <map>


typedef uint64_t t_se_id;

namespace GgafDx {

/**
 * �T�E���h�G�t�F�N�g�o�͎x���N���X .
 * ������ SeManager ���p���A�K�v�Œ����SE������
 * �Đ��`�����l���̋@�\�������B
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class SeTransmitter : public GgafCore::Object {

public:
    /** [r]����SE�̐� */
//    int _se_num;
    /** [r]SE�����ڑ��̔z�� */
    std::map<t_se_id, SeConnection*> _mapSeConnection;
    /** [r]����SE�̃{�����[���z�� */
    std::map<t_se_id, double> _map_volume;
    /** [r]����SE�̃p���l */
    std::map<t_se_id, float> _map_pan;

public:
    /**
     * �R���X�g���N�^ .
     */
    SeTransmitter();

    /**
     * SE�̐ݒ���s�� .
     * �����̃`�����l���ԍ����قȂ�΁A����SE��`����Wave�ł��A���������������ł���B
     * �����̃`�����l���ԍ��������ł���΁A��̔��������ł��Ȃ��B
     * �A���ASE�̍Đ����Ԃ� CONFIG::END_DELAY_FRAME+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �㏑���Đݒ�\�B
     * @param prm_se_id SE�o�^ID
     * @param prm_se_key SE��`��(�v���p�e�B�t�@�C����wave�t�@�C���w��̃L�[)
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    virtual void set(t_se_id prm_se_id, const char* prm_se_key, int prm_cannel);

    /**
     * �Đ� .
     * @param prm_se_id  SE�o�^ID
     * @param prm_can_looping  true:���[�v�Đ��^false:1��Đ�
     */
    virtual void play(t_se_id prm_se_id, bool prm_can_looping = false);


    /**
     * �{�����[���l��ݒ肷��B
     * SE�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_se_id SE�o�^ID(0 �` )
     * @param prm_volume �{�����[���l(0 �` 1000)
     */
    virtual void setVolume(t_se_id prm_se_id, double prm_volume);

    /**
     * �{�����[���l���擾���� .
     * SE�}�X�^�[�{�����[�����l������Ă��Ȃ�setVolume()�Őݒ肳�ꂽ���ʂ��擾�B
     * @param prm_se_id SE�o�^ID(0 �` )
     * @return �{�����[���l(0 �` 1000)
     */
    virtual int getVolume(t_se_id prm_se_id) {
        return _map_volume[prm_se_id];
    }

    /**
     * �{�����[���l�����Z���� .
     * SE�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_se_id SE�o�^ID(0 �` )
     * @param prm_volume ���Z�{�����[���l(0 �` 1000)
     * @return
     */
    virtual void addVolume(t_se_id prm_se_id, double prm_volume) {
        setVolume(prm_se_id, _map_volume[prm_se_id] + prm_volume);
    }

    /**
     * �p���l��ݒ� .
     * SE�}�X�^�[�p���͖��쐬�̂��߁A���̂܂ܔ��f
     * @param prm_pan �p���l(left:-1.0 �` center:0 �` right:1.0)
     */
    virtual void setPan(t_se_id prm_se_id, float prm_pan);

    /**
     * �p���l���擾���� .
     * @param prm_se_id
     * @return
     */
    virtual float getPan(t_se_id prm_se_id) {
        return _map_pan[prm_se_id];
    }


    /**
     * �Đ���~ .
     * @param prm_se_id  SE�o�^ID
     */
    virtual void stop(t_se_id prm_se_id);


    /**
     * Se ���擾�B
     * @param prm_se_id SE�o�^ID
     */
    virtual Se* getSe(t_se_id prm_se_id) ;

    /**
     * �f�X�g���N�^
     */
    virtual ~SeTransmitter();
};

}
#endif /*GGAF_DX_SEREFLECTOR_H_*/
