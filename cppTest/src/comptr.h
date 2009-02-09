// Com_ptr�N���X (2006. 8. 10)

// DirectX�̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^��R�s�[�Ȃǂ̖�����������B
// �f�o�b�O���ɂ̓C���^�[�t�F�C�X�̎g�p�󋵂�DEBUG.txt�Ƃ����t�@�C������
// �O���ɏo�͂��܂��B
// �f�o�b�O���ɂ��̋@�\��OFF�ɂ���ɂ͉���
// OUTPUT_INTERFACEUSAGE�萔���R�����g�A�E�g���Ă��������B

#pragma once 

#include <windows.h>


#define OUTPUT_INTERFACEUSAGE

#ifdef OUTPUT_INTERFACEUSAGE
   #if _DEBUG
   // �f�o�b�O���Ƀt�@�C���o��
   #include <fstream>
   using namespace std;
   #endif
#endif



namespace IKD{

template <class T>
class Com_ptr
{
private:
   T** m_ppInterface;   // �C���^�[�t�F�C�X�ւ̃_�u���|�C���^
   static T* m_NullPtr;	// NULL�|�C���^

protected:
   // �Q�ƃJ�E���^����
   void AddRef(T* pInterface){
		#if _DEBUG
			#ifdef OUTPUT_INTERFACEUSAGE
				// �f�o�b�O�łł͎Q�ƃJ�E���g���o�͂���
				ULONG c = pInterface->AddRef();
				ofstream ofs;
				ofs.open("DEBUG.txt", ios::app);
				ofs << pInterface << "\t[" << c << "]" << endl;
				ofs.close();
            #else
				pInterface->AddRef();
			#endif// OUTPUT_INTERFACEUSAGE
		#else
			// �����[�X���[�h
			pInterface->AddRef();
		#endif
   }

	// �Q�ƃJ�E���^����
	void Release(T* pInterface){
		ULONG c;
		c = pInterface->AddRef() - 1;   // ���݂̎Q�ƃJ�E���^�����擾
		pInterface->Release();
		if(c<=1)
			delete m_ppInterface;
		pInterface->Release();      // ����̌Ăяo���ɂ��Release�͂���
		#if _DEBUG
			#ifdef OUTPUT_INTERFACEUSAGE
				// ��x�Q�ƃJ�E���^���𑝉����Đ������J�E���^���𓾂�
				ofstream ofs;
				ofs.open("DEBUG.txt", ios::app);
				ofs << pInterface << "\t[" << c-1 << "]" << endl;
				ofs.close();
			#endif// OUTPUT_INTERFACEUSAGE
		#endif
	}

public:
   // �f�t�H���g�R���X�g���N�^
   // �R���X�g���N�^��explicit�錾���܂��B
   // �����func(Com_ptr<IHoge> v)�Ƃ����֐��ɑ΂��āA
   // func(pIHoge)�̂悤�ȈÖٌ^�ϊ�����͏o���܂���B
   // �ʏ�A�|�C���^�̈��n�����ɂ��łɎQ�ƃJ�E���^��
   // �C���N�������g����Ă���̂ŁAAddRef�͍s���܂���B
	explicit Com_ptr(T* pInterface = NULL, BOOL add=FALSE){
		#if _DEBUG
			#ifdef OUTPUT_INTERFACEUSAGE
				// �f�o�b�O�łł͎Q�ƃJ�E���g�̏����l���o�͂���
				ofstream ofs;
				ofs.open("DEBUG.txt", ios::app);
				ofs << pInterface << "\t[" << 1 << "]" << endl;
				ofs.close();
			#endif// OUTPUT_INTERFACEUSAGE
		#endif
		if(pInterface && add)
			pInterface->AddRef();
		m_ppInterface = new T*;	// �|�C���^�i�[�̈���m��
		if(pInterface)
			*m_ppInterface = pInterface;
		else
			*m_ppInterface = m_NullPtr;
	}

	// �Öٌ^�L���X�g�R�s�[�R���X�g���N�^
	template<class T2> Com_ptr( Com_ptr<T2>& src ){
		// �����ɂ���Ƃ������Ƃ́A����������Ă��Ȃ���Ԃł��邽�߁A
		// �ⓚ���p�ŃA�b�v�L���X�g���ď��L�����擾����
		if(src.GetPtr()!=NULL){
			m_ppInterface = (T**)src.GetPtrPtr();	// ���L
			*m_ppInterface = src.GetPtr();			// �^�`�F�b�N�p
			// �Q�ƃJ�E���^����
			AddRef( *m_ppInterface );
		}
		else
		{
			// ���肪NULL�Ȃ̂ŐV�K�쐬
			m_ppInterface = new T*;
			*m_ppInterface = m_NullPtr;
		}
	}


	// �R�s�[�R���X�g���N�^
	Com_ptr(const Com_ptr<T> &src)
	{
		if(*src.m_ppInterface)
		{
			// �R�s�[���Ƌ��L����̂ŎQ�ƃJ�E���^��1���₷
			(*src.m_ppInterface)->AddRef();
			m_ppInterface = src.m_ppInterface;
		}
		else
		{
			// NULL����Ȃ̂ŐV�K�쐬
			m_ppInterface = new T*;
			*m_ppInterface = m_NullPtr;
		}
	}

	// �R�s�[�R���X�g���N�^(NULL����p)
	Com_ptr(const int nullval)
	{
		m_ppInterface = new T*;	// �|�C���^�i�[�̈�����߂Ċm��
		*m_ppInterface = m_NullPtr;
	}


	// �f�X�g���N�^
	virtual ~Com_ptr()
	{
		if(*m_ppInterface)
		{
			Release(*m_ppInterface);
		}
		else
			delete m_ppInterface;
	}

	/////////////////////////////////////////////
	// ���Z�q
	/////////////////////
	// =������Z�q�i�����I�R�s�[�j
	Com_ptr<T>& operator =(const Com_ptr<T>& src){
		if(*m_ppInterface)
		{
			// ���O���[�v�̏ꍇ�͉������Ȃ�
			if( *m_ppInterface == *src.m_ppInterface )
				return *this;
			// �����̎���COM�I�u�W�F�N�g�̎Q�ƃJ�E���^��1���炷
			Release(*m_ppInterface);
		}
		else
		{
			// ����Ƌ��L���邩�V�K�쐬�ɂȂ邽�߂�������ێ����Ă���_�u���|�C���^������
			// NULL�|�C���^�̋��L�҂͂��Ȃ����߁A���̍�Ƃ͑��l�ɖ��f�������Ȃ�
			delete m_ppInterface;
		}

		// �R�s�[���̎Q�ƃJ�E���^��1���₷
		if(*src.m_ppInterface)
		{
			(*src.m_ppInterface)->AddRef();
			m_ppInterface  = src.m_ppInterface;		// ���L
		}
		else
		{
			// ���肪NULL�ł���
			m_ppInterface  = new T*;
			*m_ppInterface = m_NullPtr;
		}

		return *this;
	}

	// ->�A���[���Z�q
	T* operator ->(){ return *m_ppInterface; }

	// =������Z�q�i�V�K�C���^�[�t�F�C�X�o�^�j
	void operator =(T* pInterface){
		// �����̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
		if(*m_ppInterface){
			Release(*m_ppInterface);	// �����������Ō�̈�l�������炱���Ń����o�ϐ��̏���������
		}
		else
		{
			// �����������
			delete m_ppInterface;
		}
		// �����͐V�����l�ɂȂ�̂ŁA
		// �V�����_�u���|�C���^���쐬
			m_ppInterface = new T*;

		// �V�K���
		if(pInterface)
			*m_ppInterface = pInterface;
		else
			*m_ppInterface = m_NullPtr;
	}

	// !=��r���Z�q
	bool operator !=(T* ptr){
		if(ptr != *m_ppInterface)
			return true;
		return false;
	}

	// !=��r���Z�q
	bool operator !=(Com_ptr<T> &src){
		if(*m_ppInterface != *src.m_ppInterface)
			return true;
		return false;
	}

	// ==��r���Z�q
	bool operator ==(T* ptr){
		if(ptr == *m_ppInterface)
			return true;
		return false;
	}

	// ==��r���Z�q
	bool operator ==(Com_ptr<T> &src){
		if(*m_ppInterface == *src.m_ppInterface)
			return true;
		return false;
	}

	// !�P�����Z�q
	bool operator !(){
		if( *m_ppInterface == NULL )
			return true;
		return false;
	}

// �����o�֐�
	// �Q�ƃJ�E���^�����擾
	ULONG GetRefCnt()
	{
		if(*m_ppInterface){
			ULONG c = (*m_ppInterface)->AddRef()-1;
			(*m_ppInterface)->Release();
			return c;
		}
		return 0;
	}

	// �A�b�v�L���X�g�R�s�[
	template<class T1> void UpcastCopy(Com_ptr<T1> & src ){
		// �����̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
		if(*m_ppInterface)
			Release(*m_ppInterface);

		// �R�s�[���̎Q�ƃJ�E���^��1���₷
		if(src.GetPtr())
		{
			src.GetPtr()->AddRef();
			m_ppInterface = src.GetPtrPtr();	// ���L
			*m_ppInterface = src.GetPtr();		// �`�F�b�N�p���
		}
		else
		{
			// NULL�R�s�[�Ȃ̂ŐV�K�쐬
			m_ppInterface = new T*;
			*m_ppInterface = m_NullPtr;
		}
	}

	// �|�C���^�擾
	T* GetPtr(){return *m_ppInterface;}

	// �_�u���|�C���^���擾
	T** GetPtrPtr(){return m_ppInterface;}

	// �C���^�[�t�F�C�X�����֐��֓n����p�֐�
	T** ToCreator(){
		if(*m_ppInterface)
		{
			Release(*m_ppInterface);
			m_ppInterface = new T*;
		}
		return m_ppInterface;
	}

	// COM�X���b�v
	bool Swap( Com_ptr<T> &src )
	{
		// ������COM�I�u�W�F�N�g�Ǝ��g�Ƃ����ւ���
		// �������o�����L����COM�I�u�W�F�N�g�������Ă��鎞�Ɍ���

		// �I�u�W�F�N�g�`�F�b�N
		if( *m_ppInterface == NULL || src.GetPtr()==NULL)
			return false;

		// �Q�ƃJ�E���^���̃`�F�b�N
		ULONG SrcRef = src->AddRef()-1;
		src->Release();

		ULONG MeRef = (*m_ppInterface)->AddRef()-1;
		(*m_ppInterface)->Release();

		// ������COM�I�u�W�F�N�g���擾
		T *pReleaseObj, *pAddObj;
		if(MeRef<=SrcRef){
			pReleaseObj = src.GetPtr();
			pAddObj = *m_ppInterface;
		}
		else
		{
			pReleaseObj = *m_ppInterface;
			pAddObj = src.GetPtr();
		}

		// �݂��̎Q�ƃJ�E���g��������
		ULONG i;
		ULONG Cnt = ((int)(SrcRef-MeRef))>0?(SrcRef-MeRef):MeRef-SrcRef;
		for(i=0; i<Cnt; i++){
			pReleaseObj->Release();
			pAddObj->AddRef();
		}

		// COM�|�C���^���̃|�C���^����
		T* pTmp = *src.m_ppInterface;
		*src.m_ppInterface = *m_ppInterface;
		*m_ppInterface = pTmp;

		return true;
	}
};


template <class T>
T* Com_ptr<T>::m_NullPtr = NULL;

}