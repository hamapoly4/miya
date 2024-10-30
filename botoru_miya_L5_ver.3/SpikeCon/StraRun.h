#ifndef ___CLASS_STRARUN
#define ___CLASS_STRARUN	// インクルードカード

#include "abstract_run.h"
#include "PDcon.h"

class StraRun : public Run {
private:
	static const unsigned char mSTRAIGHT = 0;
	unsigned char Mode;
	PDcon *mPDcon;
	int mturn;
public:
	StraRun(int pwm = 70,char mode = 0);
	~StraRun();
	void run();
};

#endif // ___CLASS_STRARUN
