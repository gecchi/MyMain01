
// �{�v���O�����́A<BR>
// �u�z�㉮Cyber�v http://www.e-cyber.org/ <BR>
// �̃����o�[�̃A���_�[���̃T���v���v���O�������I���W�i���ł��B<BR>
// �ꕔ�ύX���Ďg�p���Ă��܂��B<BR>
//
// �ΏہF CWaveDecorder �N���X
//                                            2009/01/13 Masatoshi Tsuge<BR>

/****************************************************************
 *			wave�f�R�[�_����N���X
 *	@author		Ander/Echigo-ya koubou
 ****************************************************************/

#ifndef	_INCLUDE_WAVEDECORDER_HPP
#define	_INCLUDE_WAVEDECORDER_HPP

#include <mmreg.h>
#include <mmsystem.h>
namespace GgafDxCore {
/**
 @brief		Wave�t�@�C���f�R�[�_
 */
class CWaveDecorder {
private:
    WAVEFORMATEX* m_pwfx; /// Wave�t�H�[�}�b�g
    HMMIO m_hmmioIn; /// MM I/O�n���h��
    MMCKINFO m_ckIn; /// Multimedia RIFF chunk
    MMCKINFO m_ckInRiff; /// Use in opening a WAVE file

    /**
     @brief		MM I/O�̓ǂݍ���
     */
    int readMMIO(void);

public:
    virtual ~CWaveDecorder(void);

    CWaveDecorder(void);

    /**
     @brief		Wave�t�@�C�����J��
     */
    int Open(LPSTR lpszFilename);
    /**
     @brief		Wave�t�@�C�������
     */
    void Close(void);

    /**
     @brief		�o�b�t�@�ǂݏo���ʒu���w��
     @param		lPosition		�o�b�t�@�ǂݏo���ʒu(offset�Ŏw��)
     */
    int SetPosition(long lPosition);

    /**
     @brief		Wave�f�[�^�̓]��
     @return		0�ȏ�F�]�����ꂽ�o�C�g���^�����FNG
     */
    long GetWave(LPBYTE lpDest, long lSize);
    /**
     @brief		Wave�f�[�^�̃T�C�Y���擾
     */
    DWORD GetWaveSize(void);

    /**
     @brief		WaveFormat�̎擾
     */
    WAVEFORMATEX* GetWaveFormat(void);

};

}
#endif	//	_INCLUDE_WAVEDECORDER_HPP
