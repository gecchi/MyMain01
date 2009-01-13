// DixSmartPtr.h

// �X�}�[�g�|�C���^�e���v���[�g  v2.11
//  Created by IKD (2008. 6. 30)
//   http://marupeke296.com

// 2007. 3. 6
// vector�ɑ���ł��Ȃ��o�O���C���i�R�s�[�R���X�g���N�^�̃~�X���C���j

// 2007. 3. 1
// ���`�R�s�[�ŃR�s�[�R���X�g���N�^���Ă΂�Ȃ��s����C��
// �����I�A�b�v�L���X�g�y�шÖٓI�A�b�v�L���X�g�Ń_�u���|�C���^���������Ȃ��s����C��

// 2007. 2. 11
// �X���b�v�ɑΉ�

// 2008. 5. 8
// �z��T�|�[�g

// 2008. 6. 30
// �^�L���X�g����̍ۂɕی상���o�ł���m_isAry�ɃA�N�Z�X�ł��Ȃ��R���p�C���G���[���C��


// �E �o�^���ꂽ�I�u�W�F�N�g�|�C���^�̎g�p�҂����Ȃ��Ȃ����玩���I��delete
// �E �ʏ�̃|�C���^���쉉�Z�q�u*�v�u->�v�u[ ]�v���g����B
// �E �قȂ�I�u�W�F�N�g�|�C���^���o�^���ꂽ��ԂŃA�b�v�L���X�g���ł���
// �E DownCast���\�b�h�ɂ����S�ȃ_�E���L���X�g�T�|�[�g
// �E SwapPtr���\�b�h�ɂ��|�C���^����ւ��̃T�|�[�g

#ifndef IKD_DIXSMARTPTR_H
#define IKD_DIXSMARTPTR_H

namespace Dix {
	template <class T>
	class sp
	{
	private:
	   unsigned int *m_pRefCnt;   // �Q�ƃJ�E���^�ւ̃|�C���^
	   T** m_ppPtr;             // T�^�̃I�u�W�F�N�g�̃_�u���|�C���^
	   static T* m_NullPtr;		// NULL�|�C���^�l
	   bool m_isAry;			// �z�񂩁H

	private:
	   /////////////////
	   // �Q�ƃJ�E���^����
	   /////
		  void AddRef(){(*m_pRefCnt)++;}

	   /////////////////
	   // �Q�ƃJ�E���^����
	   /////
		  void Release()
		  {
			 if(--(*m_pRefCnt) == 0){
				 if ( m_isAry )
					 delete[] *m_ppPtr;	// �z�񃁃����폜
				 else
					 delete *m_ppPtr;	// �P�ʃ������폜
				 delete m_ppPtr;
				 delete m_pRefCnt;
			 }
		  }

	public:
       ///////////////////////
	   // �f�t�H���g�R���X�g���N�^
	   /////
		  explicit sp(T* src=0, int add=0)
		  {
			 m_pRefCnt = new unsigned int;
			 *m_pRefCnt = add;
			 m_ppPtr = new T*;
			 m_NullPtr = 0;
			 if(src)
				 *m_ppPtr = src;
			 else
				 *m_ppPtr = m_NullPtr;   // NULL�|�C���^�����Ă���
			 AddRef();       // �Q�ƃJ�E���^����
			 m_isAry = false;
		  }

       //////////////////////////////////////////////
	   // �z��t���O�t���f�t�H���g�R���X�g���N�^
	   /////
		  sp(T* src, bool isAry, int add=0)
		  {
			 m_pRefCnt = new unsigned int;
			 *m_pRefCnt = add;
			 m_ppPtr = new T*;
			 m_NullPtr = 0;
			 if(src)
				 *m_ppPtr = src;
			 else
				 *m_ppPtr = m_NullPtr;   // NULL�|�C���^�����Ă���
			 AddRef();       // �Q�ƃJ�E���^����
			 m_isAry = isAry;
		  }

	   //////////////////////////////////////
	   // �R�s�[�R���X�g���N�^�i���^�R�s�[�j
	   /////
		  sp(const sp<T> &src)
		  {
			 // ����̃|�C���^�����ׂăR�s�[
			 m_pRefCnt = src.m_pRefCnt;   // �Q�ƃJ�E���^�|�C���^
			 m_ppPtr = src.m_ppPtr;       // T�^�_�u���|�C���^
			 m_isAry = src.m_isAry;

			 // �������g�̎Q�ƃJ�E���^�𑝉�
			 AddRef();
		  }

	  //////////////////////////////////////
	   // �R�s�[�R���X�g���N�^�i�ÖٓI�A�b�v�L���X�g�j
	   /////
		  template<class T2> sp(sp<T2> &src)
		  {
			 // ����̃_�u���|�C���^���R�s�[
			 m_pRefCnt = src.GetRefPtr();
			 m_ppPtr = (T**)src.GetPtrPtr();

			 // �^�`�F�b�N�R�s�[
			 *m_ppPtr = src.GetPtr();

			 m_isAry = src.isAry();m_isAry;

			 // �������g�̎Q�ƃJ�E���^�𑝉�
			 AddRef();
		  }


	   //////////////////////////////////////
	   // �R�s�[�R���X�g���N�^�iNULL�����p�j
	   /////
		  sp(const int nullval)
		  {
			 m_pRefCnt = new unsigned int;
			 *m_pRefCnt = 0;
			 m_ppPtr = new T*;
			 *m_ppPtr = m_NullPtr;
			 AddRef();       // �Q�ƃJ�E���^����
			 m_isAry = false;
		  }


	   ///////////////
	   // �f�X�g���N�^
	   /////
		 virtual ~sp()
		  {
			 Release();
		  }


	//���������Z�q�̃I�[�o�[���[�h����������������������


	   /////////////////////////////////
	   // =������Z�q�i�����I�R�s�[�j
	   /////
		  sp<T>& operator =(const sp<T> &src)
		  {
			 // �������g�ւ̑���͕s���ňӖ��������̂�
			 // �s��Ȃ��B
			 if(*src.m_ppPtr == *m_ppPtr)
				return (*this);

			  // �����͑��l�ɂȂ��Ă��܂��̂�
			 // �Q�ƃJ�E���^��1����
			 Release();

			 // ����̃|�C���^���R�s�[
			 m_pRefCnt = src.m_pRefCnt;
			 m_ppPtr = src.m_ppPtr;

			 m_isAry = src.m_isAry;

			 // �V�����������g�̎Q�ƃJ�E���^�𑝉�
			 AddRef();

			 return (*this);
		  }


	   /////////////////////////////////
	   // =������Z�q�i�����I�A�b�v�L���X�g�j
	   /////
		  template<class T2> sp<T>& operator =(sp<T2> &src)
		  {
			 // �������g�ւ̑���͕s���ňӖ��������̂�
			 // �s��Ȃ��B
			 if(src.GetPtr() == *m_ppPtr)
				return (*this);

			  // �����͑��l�ɂȂ��Ă��܂��̂�
			 // �Q�ƃJ�E���^��1����
			 Release();

			 // ����̃|�C���^���R�s�[
			 m_pRefCnt = src.GetRefPtr();
			 m_ppPtr = (T**)src.GetPtrPtr();

			 // �^�`�F�b�N�R�s�[
			 *m_ppPtr = src.GetPtr();

 			 m_isAry = src.m_isAry;

			 // �V�����������g�̎Q�ƃJ�E���^�𑝉�
			 AddRef();

			 return (*this);
		  }


	   /////////////////////////////////
	   // =������Z�q(NULL����ɂ�郊�Z�b�g�j
	   /////
		  sp<T>& operator =(const int nullval)
		  {
			  // �����͋�Ȑl�ɂȂ��Ă��܂��̂�
			  // �Q�ƃJ�E���^��1����
			  Release();

			  // �V�K�Ɏ������g�����
			  m_pRefCnt = new unsigned int(1);
			  m_ppPtr = new T*;
			  *m_ppPtr = m_NullPtr;
			  m_isAry = false;

			 return (*this);
		  }


	   ///////////////
	   // *�Ԑډ��Z�q
	   /////
		  T& operator *(){ return **m_ppPtr;}

	   //////////////////////
	   // ->�����o�I�����Z�q
	   /////
		  T* operator ->(){ return *m_ppPtr;}

	   /////////////////
	   // ==��r���Z�q
	   /////
	/*      bool operator ==(int val){
			 if((int)m_pPtr == val)
				return TRUE;
			 return FALSE;
		  }
	*/
		  bool operator ==(T *val){
			 if(*m_ppPtr == val)
				return true;
			 return false;
		  }

	   /////////////////
	   // !=��r���Z�q
	   /////
	/*      bool operator !=(int val){
			 if((int)m_pPtr != val)
				return TRUE;
			 return FALSE;
		  }
	*/
		  bool operator !=(T *val){
			 if(*m_ppPtr != val)
				return true;
			 return false;
		  }

	  ///////////////////
	  // �z��Q�Ɖ��Z�q
	  /////
		  T& operator[]( int elem ) {
			 return (*m_ppPtr)[ elem ];
		  }

	  ///////////////////
	  // �|�C���^���Z�q
	  /////
		  T* operator+( int add ) {
			 return (*m_ppPtr + add);
		  }


	//������ �����o�֐� ����������������������

	public:
	   //////////////////////////
	   // �|�C���^�̖����I�ȓo�^
	   /////
		  void SetPtr(T* src = ((void *)0), int add=0)
		  {
			 // �Q�ƃJ�E���^�����炵����ɍď�����
				Release();
				m_pRefCnt = new unsigned int;
				*m_pRefCnt = add;
				m_ppPtr = new T*;
				if(src)
					*m_ppPtr = src;
				else
					*m_ppPtr = m_NullPtr;
				AddRef();
		  }

	   ////////////////////////////////////////////
	   // �|�C���^�̖����I�ȓo�^�i�z��t���O�t���j
	   /////
		  void SetPtr(T* src, bool isAry, int add=0)
		  {
			 // �Q�ƃJ�E���^�����炵����ɍď�����
				Release();
				m_pRefCnt = new unsigned int;
				*m_pRefCnt = add;
				m_ppPtr = new T*;
				if(src) {
					*m_ppPtr = src;
					m_isAry = isAry;
				}
				else {
					*m_ppPtr = m_NullPtr;
					m_isAry = false;
				}
				AddRef();
		  }

	   /////////////////////
	   // �|�C���^�݂̑��o��
	   /////
		  T* GetPtr(){return *m_ppPtr;}
		  T** GetPtrPtr(){ return m_ppPtr;}

	   /////////////////////
	   // �l�擾
	   /////
		  T& At( int elem = 0 ) {
			  return (*m_ppPtr)[ elem ];
		  }

	   ///////////////////////////////
	   // �Q�ƃJ�E���^�ւ̃|�C���^���擾
	   /////
		  unsigned int* GetRefPtr(){return m_pRefCnt;}

	   //////////////////////////
	   // �_�E���L���X�g�R�s�[
	   /////
		template <class T2> bool DownCast(sp<T2> &src)
		{
			// �����̃X�}�[�g�|�C���^�̎��|�C���^���A
			// �����̓o�^���Ă���|�C���^��
			// �_�E���L���X�g�\�ȏꍇ�̓_�E���L���X�g�R�s�[�����s
			T* castPtr = dynamic_cast<T*>(src.GetPtr());
			if(castPtr){
				// �_�E���L���X�g����
				// �����͈Ⴄ�l�ɂȂ�̂�
				// �����̎Q�ƃJ�E���^��1����
				Release();
				// �V�����|�C���^�ƎQ�ƃJ�E���^�����L
				m_ppPtr = (T**)src.GetPtrPtr();
				*m_ppPtr = castPtr;
				m_pRefCnt = src.GetRefPtr();

				m_isAry = src.m_isAry;

				// �Q�ƃJ�E���^����
				AddRef();
				return true;
			}

			return false;
		}

		///////////////////////
		// �|�C���^�X���b�v�i�����j
		///////
		void SwapPtr( sp<T> &src )
		{
			// �|�C���^�̌���
			T* pTmp = src.GetPtr();
			*src.m_ppPtr = *m_ppPtr;
			*m_ppPtr = pTmp;

			// �z��t���O�̌���
			bool tmp = src.m_isAry;
			src.m_isAry = m_isAry;
			m_isAry = tmp;
		}

		///////////////////////
		// �z��H
		///////
		bool isAry() {
			return m_isAry;
		}
	};

	template <class T>
	T* sp<T>::m_NullPtr = 0;

} // end namespace Dix


#endif // !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
