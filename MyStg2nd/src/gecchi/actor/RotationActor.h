#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ���[�e�[�V�����A�N�^�[�N���X .
 * ���@�̃V���b�g�ȂǁA��ʏ�ɃL�����N�^��MAX�����t�ŕ\���������ꍇ���ɗL���B
 */
class RotationActor : public GgafDummyActor {

public:
	RotationActor(string prm_name);

	/**
	 * �q�A�N�^�[�̂�擪���猟�����A�ŏ��ɏo����� play �\�ȃA�N�^�[���擾.
	 * �擾�ł����ꍇ�A���̃A�N�^�[��Ԃ��Ɠ����� �A�����X�g�̍Ō�Ɉړ������B<BR>
	 * �󂫂������ꍇ NULL ��Ԃ��B<BR>
	 * @return play �\�� Actor
	 */
	GgafActor* get();

	virtual ~RotationActor();
};


#endif /*ROTATIONACTOR_H_*/
