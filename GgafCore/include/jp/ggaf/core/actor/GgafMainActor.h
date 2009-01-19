#ifndef GGAFMAINACTOR_H_
#define GGAFMAINACTOR_H_
namespace GgafCore {


/**
 * ���ʃA�N�^�[�N���X�ւ̃C���^�[�t�F�C�X .
 * GgafCore���C�u�����̗��p�҂́A�V���ɃA�N�^�[�N���X�����ꍇ�{�N���X���p�����ăA�N�^�[�N���X����邱�Ƃɂ���B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafMainActor : public GgafActor {

protected:
	/** �Ǘ��� */
    GgafLordActor* _pLordActor;
	/** ��ʁi�O���[�v�j���i��w�b�h�A�N�^�[ */
	GgafHeadActor* _pHeadActor;

public:

	GgafMainActor(string prm_name);

	/**
	 * ���̃m�[�h�擾����B .
	 * ��OverRide �ł���
	 * @return	���m�[�h
	 */
	virtual GgafMainActor* getNext() {
		return (GgafMainActor*)GgafActor::getNext();
	};

	/**
	 * �O�̃m�[�h�擾����B .
	 * ��OverRide �ł���
	 * @return	�O�m�[�h
	 */
	virtual GgafMainActor* getPrev() {
		return (GgafMainActor*)GgafActor::getPrev();
	}

	/**
	 * �q�m�[�h�̃O���[�v�̐擪�m�[�h���擾���� .
	 * �q�m�[�h�����݂��Ȃ��ꍇ�̓G���[�B
	 * ��OverRide �ł���
	 * @return	�q�m�[�h�̐擪�m�[�h
	 */
	virtual GgafMainActor* getSubFirst(){
		return (GgafMainActor*)GgafActor::getSubFirst();
	}

	/**
	 * ���c���[�m�[�h��A�����X�g����؂藣���A�Ɨ�����B .
	 * �؂藣���ꌊ���J���������́A����̃m�[�h�����𖄂߂܂��i�ĘA�����܂��j<BR>
	 * ���m�[�h�Ɏq���Ԃ牺�����Ă����ꍇ�A�������؂藣���ꂽ���ƂɂȂ�܂��B<BR>
	 * ��OverRide �ł���
	 * @return	���m�[�h�̃|�C���^
	 */
	virtual GgafMainActor* tear() {
		return (GgafMainActor*)GgafActor::tear();
	};

	/**
	 * �Ǘ��҂�ݒ肷��B .
	 */
	virtual void setLordActor(GgafLordActor* prm_pLordActor);


	/**
	 * �����w�b�h�A�N�^�[��ݒ肷��B<BR>
	 */
	virtual void setHeadActor(GgafHeadActor* prm_pHeadActor);

	/**
	 * �Ǘ��A�N�^�[�擾�B .
	 * @return �Ǘ��A�N�^�[
	 */
	virtual GgafLordActor* getLordActor();

	/**
	 * �����w�b�h�A�N�^�[���擾����B .
	 * @return �����w�b�h�A�N�^�[
	 */
	virtual GgafHeadActor* getHeadActor();

    /**
	 * �_�l�ɐڌ� .
	 * @return	�Ă΂�ďo�Ă����_�l
	 */
	virtual GgafGod* askGod();


	virtual ~GgafMainActor();
};


}
#endif /*GGAFMAINACTOR_H_*/
