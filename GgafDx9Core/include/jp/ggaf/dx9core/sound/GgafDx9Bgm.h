#ifndef GGAFDX9BGM_H_
#define GGAFDX9BGM_H_

class GgafDx9Bgm : public GgafObject {
public:
	//CC3DSoundBGM* _pSoundBgm;
	string _ogg_name;
	GgafDx9Bgm* _pBgm_Next;
	OggDecoder* _pOggDecoder;
	OggVorbisFile* _pOggResource;
	PCMPlayer* _pPcmPlayer;

	GgafDx9Bgm(string prm_wave_name);

	//virtual void behave();フェードインフェードアウトを実装するぞ！

	//! 再生
	void play( bool isLoop );

	//! 一時停止
	void pause();

	//! 停止
	void stop();

	//! 音量を変える
	void setVolume( int volume );

	//! パンの位置を変える
	void setPan( int pan );
	//! 停止
	void clear();


	virtual ~GgafDx9Bgm();
};

#endif /*GGAFDX9BGM_H_*/
