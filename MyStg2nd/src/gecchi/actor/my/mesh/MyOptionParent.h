#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

class MyOptionParent : public GgafDx9LibStg::DefaultMeshActor {

public:

	/** �ΏۃA�N�^�[ */

	MyOptionParent(const char* prm_name, const char* prm_model);

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	void processJudgement();

	/**
	 * ��OverRide �ł���
	 */
 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


 	virtual ~MyOptionParent();
};


}
#endif /*MYOPTIONPARENT_H_*/

