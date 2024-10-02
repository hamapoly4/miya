#ifndef ___CLASS_RUNDISTJUDGEMENT2
#define ___CLASS_RUNDISTJUDGEMENT2

#include "JudgeMent.h"
#include "RunDistDetect.h"

class RunDistJudgeMent2 : public JudgeMent {
private:
	RunDistDetect *mRunDistDetect1;
	RunDistDetect *mRunDistDetect2;

	enum eTire { RIGHT, LEFT,};

	float mtarget_dist1;
	float mtarget_dist2;
	float mcurrent_dist1;
	float mcurrent_dist2;
	unsigned char mtire;
	
public:
	RunDistJudgeMent2(unsigned char tire, float target_dist);
	~RunDistJudgeMent2();
	bool judge();
};

#endif // ___CLASS_RUNDISTJUDGEMENT
