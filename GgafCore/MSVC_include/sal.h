//�ysal.h ���Ȃ�����ȂƂ���ɂ���̂ł����Y���^�����z
//
//�O��Ƃ��āA�{�v���O������GCC(MINGW��GCC4.X)�AVC++2010�AVC++2008�AVC++2005 �ŃR���p�C���o����悤�ɖڎw���Ă���B
//VC++�ł͖��Ȃ����AGCC�ŃR���p�C������ۂɁA�{�w�b�_�t�@�C���͕K�v�ƂȂ�B
//
//DirectX SDK August 2009 �ȍ~�A�Ȃ��SDK�̃w�b�_�[�R�[�h���ŁA����VC�p�w�b�_�t�@�C��("sal.h"��)��include���Ă���R�[�h�����ꂽ�I�B
//�w�b�_�[�p�X�̗D�揇�ʂ𒲐����Ă��A�ǂ��ɂ������ɂ�����ł����A���͂� DirectX SDK + MINGW �݂̂ŃR���p�C���o���Ȃ��Ȃ����i�Ǝv���j�B
//���������ׂĂ������ɁA�u�K�v��VC�̃w�b�_�� sal.h ������łȂ�Ƃ��Ȃ�񂶂�Ȃ����E�E�E�H�B�v�ƁA
//�^�S�ËS�ɂ�����Asal.h �̃R�s�[���C���N���[�h�p�X�̉����ꏊ�ɒu���Ďg�p���Ă����B
//���̂����Asal.h �� define��`�́AGCC�ł͑S��������Ŗ��Ȃ�����Ȃ��̂��H�Ƃ����g����Ȍ��_�ɒB�����B
//�����ŁA�R���p�C�����ʂ�悤�ɁAsal.h �� define��`�����`�ɂ��܂������t�@�C���� MINGW�p�� sal.h�i�{�t�@�C���j�Ƃ��邱�Ƃɂ��܂��B
//VC�ŃR���p�C������ꍇ�A�{�t�@�C�����Q�Ƃ���Ȃ��悤�ɃC���N���[�h�p�X�𒲐�����B
//GCC�ŃR���p�C������ꍇ�A�{�t�@�C�����Q�Ƃ���悤�ɃC���N���[�h�p�X��ʂ��B

//�֘A����ʂ̖��B
//GCC �ł́AC++�̏ꍇ
//
//#define NULL __null
//
//�ƂȂ��Ă���A__null �͖��ߍ��ݒ萔�̂悤�ł���A���m�ɒ�`����Ă��Ȃ��B
//__null �� GCC �Ɠ��̃}�W�b�N�萔�H���Ǝv���Ă��̂��Asal.h �ɂȂ�� __null ��define��`����Ă���̂ł���I
//����ł����āAdsound.h ���ŁA__null ���g�p���Ă���̂ł���B����ɂ͍������B
//dsound.h ���ł�
//  __null  �� �����Ȃ�
//�Ƃ�����`��ԂłłȂ��Ƃ����Ȃ��̂ŁAdsound.h ��include�̑O���

//#ifdef __GNUG__
//    #define __null
//#endif
//#include <dsound.h>
//#ifdef __GNUG__
//    #undef __null
//#endif

//�Ƃ����Ώ����s�Ȃ��Ă���B
//GCC�� #undef __null �ƒ�`���������Ă� NULL ����ɂ͂Ȃ�Ȃ��B __null �͖��ߍ��ݒ萔�����炾�I
//__null ������g�p���Ă���w�b�_�t�@�C��������΁A���̃w�b�_�̑O��ɕt���Ȃ��Ă͂Ȃ�Ȃ����A
//�K���A���̉e���͈͂� dsound.h �݂̂������B

//�悵�A�R���p�C�����ʂ������ƁE�E�E
//TODO:����ł����̂���Ȃ����Ȃ��`�I�I �_(T_T)�^

#ifndef MY_SAL_H_
#define MY_SAL_H_
//GCC�p�ɃR���p�C�����ʂ�悤�ɋ��`
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
