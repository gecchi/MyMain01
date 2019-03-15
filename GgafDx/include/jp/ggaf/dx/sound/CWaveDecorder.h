
/****************************************************************
 *			wave�f�R�[�_����N���X
 *	@author		Ander/Echigo-ya koubou
 ****************************************************************/

#ifndef	_INCLUDE_WAVEDECORDER_HPP
#define	_INCLUDE_WAVEDECORDER_HPP
#include "GgafDxCommonHeader.h"
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {
/**
 @brief		Wave�t�@�C���f�R�[�_
 */

/**
 * wave�f�R�[�_����N���X .
 * �{�v���O�����́A<BR>
 *�u�z�㉮Cyber�v http://www.e-cyber.org/ <BR>
 * �̃����o�[�̃A���_�[���̃T���v���v���O�������x�[�X�ɂȂ��Ă���܂��B<BR>
 * ���Ȃ݂ɁA�N���X�������O�̑匳�́A���炭�}�C�N���\�t�g�� "wave.c" �Ǝv���܂��B<BR>
 * ���肪�������p�����Ă��������܂��B<BR>
 * �ΏہF CWaveDecorder �N���X<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author      Ander/Echigo-ya koubou
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
