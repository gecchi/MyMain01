//�ysal.h ���Ȃ�����ȂƂ���ɂ���̂ł����Y���^�����z
//
//�O��Ƃ��āA�{�v���O������GCC(MINGW����GCC4.X w32 & w64)�AVC++2005�AVC++2008�AVC++2010 �� x86 & x64 ��
//�R���p�C���y�ю��s�o����悤�ɖڎw���Ă���B
//VC++�ł͖��Ȃ����AMINGW-GCC�ŃR���p�C������ۂɁA�{�w�b�_�t�@�C���͕K�v�ƂȂ�B
//
//DirectX SDK August 2009 �ȍ~�ADirectX�̃w�b�_�[�R�[�h���ŁA����VC�p�w�b�_�t�@�C��("sal.h"��)��include���Ă���R�[�h�����ꂽ�I�B
//�w�b�_�[�p�X�̗D�揇�ʂ𒲐����Ă��A�ǂ��ɂ������ɂ�����ł����A���͂� DirectX SDK + MINGW �݂̂ŃR���p�C���o���Ȃ��Ȃ����i�Ǝv���j�B
//���������ׂĂ������ɁA
//�u�K�v��VC�̃w�b�_�� sal.h ������łȂ�Ƃ��Ȃ�񂶂�Ȃ����E�E�E�H�B�v
//�ƁA�^�S�ËS�ɂ�����Asal.h ���C���N���[�h�p�X�̒ʂ����ꏊ�ɃR�s�[���āA�Ȃ�Ƃ��R���p�C�����Ă����B���̂����A
//�usal.h �� #define ��`�́AGCC�ł͑S��������Ŗ�薳���񂶂�Ȃ��̂��H�v
//�Ƃ����g����ȋ^�S�ËS�ɂ܂����������Ă��܂����B
//�����ŁA�R���p�C�����ʂ�悤�ɁAsal.h �� define��`�����`�ɂ��܂������t�@�C���� MINGW�p�� sal.h�i�{�t�@�C���j�Ƃ��邱�Ƃɂ����B
//VC�ŃR���p�C������ꍇ�A�{�t�@�C�����Q�Ƃ���Ȃ��悤�ɃC���N���[�h�p�X�𒲐�����B
//MINGW-GCC�ŃR���p�C������ꍇ�A�{�t�@�C�����Q�Ƃ���悤�ɃC���N���[�h�p�X��ʂ��B
//
//��������Ȃ����Ǝv�������A�ʂ̖�肪�����B
//GCC �ł́A�ŋ� C++�R���p�C���̏ꍇ
//
//#define NULL __null
//
//�ƂȂ��Ă���B�ŁA __null �̒�`�͂ǂ��ɂ��Ȃ��B���낢������������ʁA__null �͖��ߍ��ݒ萔�̂悤�ł���B
//64bit���� sizeof �͎����I��8�o�C�g�ɂȂ�A__null �� GCC �Ɠ��̂��̂��ƍl���Ă���B
//�����������Asal.h �ɂȂ�� __null ���Ȃ񂩕ʂ̂��̂� #define ��`����Ă���ۂ��̂𔭌������B
//�����ĈĂ̒�ADirectX�w�b�_�� dsound.h ���ŁA__null �̋L�q������B(����)
//
//extern HRESULT WINAPI DirectSoundCreate(__in_opt LPCGUID pcGuidDevice, __deref_out LPDIRECTSOUND *ppDS, __null LPUNKNOWN pUnkOuter);
//
//�܂� __null �́AGCC �ł͖��ߍ��ݒ萔�BVC �ł̓}�N���Ƃ����ʂ̈����ɂȂ��Ă���̂��B���`���Ċ����BGCC�̎��ɃR���p�C���ł���B
//�ŁA���ׂĂ��������ɁAGCC�ŃR���p�C�����A dsound.h ���ł�
//�u__null  �� �����Ȃ��B�Ƃ�����`��Ԃł��Ԃ���Ȃ��v
//�Ǝv�����̂ŁAGCC�̏ꍇ�̂� #include <dsound.h> �̑O��Ƀv���v���Z�b�T��
//
//#ifdef __GNUG__
//    #define __null
//#endif
//#include <dsound.h>  //��sal.h �� include ����
//#ifdef __GNUG__
//    #undef __null
//    #undef __in
//    #undef __out
//#endif
//
//�Ƃ����Ώ����s�Ȃ��Ă���B
//GCC�ŃR���p�C����
//
//#define __null
//
//�Ƃ���� �u__null  �� �����Ȃ��v�Ƃ����󋵂ɂȂ�A���̏󋵉���
//
//#undef __null
//
//�ƋL�q������ƁA���� __null ��`�ɖ߂�BGCC�Ɍ����Ă� #undef �� __null ������`�ɂȂ��Ă��܂��킯�ł͂Ȃ��悤���B
//��������ȋC�������A���Ԃ� __null �͓��ʂȒ萔�ł����āA�}�N���ł͖������獡�͂����Ȃ�񂾂Ǝv����I
//__null ������g�p���Ă���DirectX�w�b�_�t�@�C����������΁A���̃w�b�_�̑O��ɏ�L�΍��t�^���Ȃ��Ă͂Ȃ�Ȃ��B���A
//�K���A���̉e���͈͂� dsound.h �݂̂ő��v�����������B
//#undef __in �� #undef __out �́AGCC �w�b�_�R�[�h�ŁA���[�J���ϐ����� __in , __out �Ƃ������O���g�p����Ă���ӏ���
//���邽�߂��B�����ɂ��Ă����Ȃ��Ɠ{����B
//
//�悵�E�E�E�A�R���p�C�����ʂ������ƁE�E�E�A�Ȃ�Ƃ��s�׍H�ł���B
//TODO:���΂炭����ł����̂���Ȃ����Ȃ��`�I�I �_(T_T)�^
//TODO:�ŋ� mingw-w64 �̃��C�u�����w�b�_�ɁA�Ǝ���"sal.h"����������E�E�E�B����������A�ǂ����悤���B

#ifndef MY_SAL_H_
#define MY_SAL_H_
//Mingw-GCC�p�ɃR���p�C�����ʂ�悤�ɋ��`
#define __ecount(size)
#define __bcount(size)
#define __in
#define __in_ecount(size)
#define __in_bcount(size)
#define __in_z
#define __in_ecount_z(size)
#define __in_bcount_z(size)
#define __in_nz
#define __in_ecount_nz(size)
#define __in_bcount_nz(size)
#define __out
#define __out_ecount(size)
#define __out_bcount(size)
#define __out_ecount_part(size,length)
#define __out_bcount_part(size,length)
#define __out_ecount_full(size)
#define __out_bcount_full(size)
#define __out_z
#define __out_z_opt
#define __out_ecount_z(size)
#define __out_bcount_z(size)
#define __out_ecount_part_z(size,length)
#define __out_bcount_part_z(size,length)
#define __out_ecount_full_z(size)
#define __out_bcount_full_z(size)
#define __out_nz
#define __out_nz_opt
#define __out_ecount_nz(size)
#define __out_bcount_nz(size)
#define __inout
#define __inout_ecount(size)
#define __inout_bcount(size)
#define __inout_ecount_part(size,length)
#define __inout_bcount_part(size,length)
#define __inout_ecount_full(size)
#define __inout_bcount_full(size)
#define __inout_z
#define __inout_ecount_z(size)
#define __inout_bcount_z(size)
#define __inout_nz
#define __inout_ecount_nz(size)
#define __inout_bcount_nz(size)
#define __ecount_opt(size)
#define __bcount_opt(size)
#define __in_opt
#define __in_ecount_opt(size)
#define __in_bcount_opt(size)
#define __in_z_opt
#define __in_ecount_z_opt(size)
#define __in_bcount_z_opt(size)
#define __in_nz_opt
#define __in_ecount_nz_opt(size)
#define __in_bcount_nz_opt(size)
#define __out_opt
#define __out_ecount_opt(size)
#define __out_bcount_opt(size)
#define __out_ecount_part_opt(size,length)
#define __out_bcount_part_opt(size,length)
#define __out_ecount_full_opt(size)
#define __out_bcount_full_opt(size)
#define __out_ecount_z_opt(size)
#define __out_bcount_z_opt(size)
#define __out_ecount_part_z_opt(size,length)
#define __out_bcount_part_z_opt(size,length)
#define __out_ecount_full_z_opt(size)
#define __out_bcount_full_z_opt(size)
#define __out_ecount_nz_opt(size)
#define __out_bcount_nz_opt(size)
#define __inout_opt
#define __inout_ecount_opt(size)
#define __inout_bcount_opt(size)
#define __inout_ecount_part_opt(size,length)
#define __inout_bcount_part_opt(size,length)
#define __inout_ecount_full_opt(size)
#define __inout_bcount_full_opt(size)
#define __inout_z_opt
#define __inout_ecount_z_opt(size)
#define __inout_ecount_z_opt(size)
#define __inout_bcount_z_opt(size)
#define __inout_nz_opt
#define __inout_ecount_nz_opt(size)
#define __inout_bcount_nz_opt(size)
#define __deref_ecount(size)
#define __deref_bcount(size)
#define __deref_out
#define __deref_out_ecount(size)
#define __deref_out_bcount(size)
#define __deref_out_ecount_part(size,length)
#define __deref_out_bcount_part(size,length)
#define __deref_out_ecount_full(size)
#define __deref_out_bcount_full(size)
#define __deref_out_z
#define __deref_out_ecount_z(size)
#define __deref_out_bcount_z(size)
#define __deref_out_nz
#define __deref_out_ecount_nz(size)
#define __deref_out_bcount_nz(size)
#define __deref_inout
#define __deref_inout_z
#define __deref_inout_ecount(size)
#define __deref_inout_bcount(size)
#define __deref_inout_ecount_part(size,length)
#define __deref_inout_bcount_part(size,length)
#define __deref_inout_ecount_full(size)
#define __deref_inout_bcount_full(size)
#define __deref_inout_z
#define __deref_inout_ecount_z(size)
#define __deref_inout_bcount_z(size)
#define __deref_inout_nz
#define __deref_inout_ecount_nz(size)
#define __deref_inout_bcount_nz(size)
#define __deref_ecount_opt(size)
#define __deref_bcount_opt(size)
#define __deref_out_opt
#define __deref_out_ecount_opt(size)
#define __deref_out_bcount_opt(size)
#define __deref_out_ecount_part_opt(size,length)
#define __deref_out_bcount_part_opt(size,length)
#define __deref_out_ecount_full_opt(size)
#define __deref_out_bcount_full_opt(size)
#define __deref_out_z_opt
#define __deref_out_ecount_z_opt(size)
#define __deref_out_bcount_z_opt(size)
#define __deref_out_nz_opt
#define __deref_out_ecount_nz_opt(size)
#define __deref_out_bcount_nz_opt(size)
#define __deref_inout_opt
#define __deref_inout_ecount_opt(size)
#define __deref_inout_bcount_opt(size)
#define __deref_inout_ecount_part_opt(size,length)
#define __deref_inout_bcount_part_opt(size,length)
#define __deref_inout_ecount_full_opt(size)
#define __deref_inout_bcount_full_opt(size)
#define __deref_inout_z_opt
#define __deref_inout_ecount_z_opt(size)
#define __deref_inout_bcount_z_opt(size)
#define __deref_inout_nz_opt
#define __deref_inout_ecount_nz_opt(size)
#define __deref_inout_bcount_nz_opt(size)
#define __deref_opt_ecount(size)
#define __deref_opt_bcount(size)
#define __deref_opt_out
#define __deref_opt_out_z
#define __deref_opt_out_ecount(size)
#define __deref_opt_out_bcount(size)
#define __deref_opt_out_ecount_part(size,length)
#define __deref_opt_out_bcount_part(size,length)
#define __deref_opt_out_ecount_full(size)
#define __deref_opt_out_bcount_full(size)
#define __deref_opt_inout
#define __deref_opt_inout_ecount(size)
#define __deref_opt_inout_bcount(size)
#define __deref_opt_inout_ecount_part(size,length)
#define __deref_opt_inout_bcount_part(size,length)
#define __deref_opt_inout_ecount_full(size)
#define __deref_opt_inout_bcount_full(size)
#define __deref_opt_inout_z
#define __deref_opt_inout_ecount_z(size)
#define __deref_opt_inout_bcount_z(size)
#define __deref_opt_inout_nz
#define __deref_opt_inout_ecount_nz(size)
#define __deref_opt_inout_bcount_nz(size)
#define __deref_opt_ecount_opt(size)
#define __deref_opt_bcount_opt(size)
#define __deref_opt_out_opt
#define __deref_opt_out_ecount_opt(size)
#define __deref_opt_out_bcount_opt(size)
#define __deref_opt_out_ecount_part_opt(size,length)
#define __deref_opt_out_bcount_part_opt(size,length)
#define __deref_opt_out_ecount_full_opt(size)
#define __deref_opt_out_bcount_full_opt(size)
#define __deref_opt_out_z_opt
#define __deref_opt_out_ecount_z_opt(size)
#define __deref_opt_out_bcount_z_opt(size)
#define __deref_opt_out_nz_opt
#define __deref_opt_out_ecount_nz_opt(size)
#define __deref_opt_out_bcount_nz_opt(size)
#define __deref_opt_inout_opt
#define __deref_opt_inout_ecount_opt(size)
#define __deref_opt_inout_bcount_opt(size)
#define __deref_opt_inout_ecount_part_opt(size,length)
#define __deref_opt_inout_bcount_part_opt(size,length)
#define __deref_opt_inout_ecount_full_opt(size)
#define __deref_opt_inout_bcount_full_opt(size)
#define __deref_opt_inout_z_opt
#define __deref_opt_inout_ecount_z_opt(size)
#define __deref_opt_inout_bcount_z_opt(size)
#define __deref_opt_inout_nz_opt
#define __deref_opt_inout_ecount_nz_opt(size)
#define __deref_opt_inout_bcount_nz_opt(size)

#endif /**MY_SAL_H_*/
