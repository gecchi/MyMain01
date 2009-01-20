#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_
namespace GgafDx9Core {


// �{�v���O�����́A<BR>
// �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
// �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
// �̃T���v���v���O�����𗬗p�i�ꕔ�ύX�j�����Ă��������āA�������Ă��܂��B<BR>
// �����IKD���̐ɂ��݂Ȃ��Z�p���L�̐S�ɁA���Ӑ\���グ�܂��B<BR>
//
//                                            2009/01/13 Masatoshi Tsuge<BR>

/**
 * Ogg �X�g���[���Đ��N���X .
 */
class GgafDx9Bgm : public GgafCore::GgafObject {
public:
	std::string _ogg_name;
	GgafDx9Core::GgafDx9Bgm* _pBgm_Next;
	Dix::PCMPlayer* pPcmPlayer;
	Dix::sp< Dix::OggVorbisFile > spOggResource;
	Dix::sp< Dix::OggDecoder > spOggDecoder;

	GgafDx9Bgm(std::string prm_wave_name);

	//TODO:
	//virtual void behave();�Ńt�F�[�h�C���t�F�[�h�A�E�g���������邼�I

	//! �Đ�
	void play( bool isLoop );

	//! �ꎞ��~
	void pause();

	//! ��~
	void stop();

	//! ���ʂ�ς���
	void setVolume( int volume );

	//! �p���̈ʒu��ς���
	void setPan( int pan );
	//! ��~
	void clear();

	bool isPlaying();

	virtual ~GgafDx9Bgm();
};


}
#endif /*GGAFDX9BGM_H_*/
