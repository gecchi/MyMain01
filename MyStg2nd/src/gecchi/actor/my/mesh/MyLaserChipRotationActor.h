#ifndef MYLASERCHIPROTATIONACTOR_H_
#define MYLASERCHIPROTATIONACTOR_H_
namespace MyStg2nd {

class MyLaserChipRotationActor : public GgafDx9LibStg::RotationActor {

public:
    int _iNumActiveChip;
    MyLaserChip2* _pHeadChip;
    int _mode;// = 0 OK /=1 ‹ó‚É‚È‚é‚Ü‚Å‘Ò‚Â
    GgafDx9Core::GgafDx9SeConnection* _pLaserConnection;


	MyLaserChipRotationActor(const char* prm_name);

	virtual void processBehavior();

	virtual GgafCore::GgafMainActor* obtain();

 	virtual ~MyLaserChipRotationActor();

};

}
#endif /*MYLASERCHIPROTATIONACTOR_H_*/
