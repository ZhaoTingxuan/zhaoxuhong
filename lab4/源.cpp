#include <iostream>
#include "test.h"
#include "OPT.h"
#include "FIFO.h"
#include "LRU.h"
#include "bclock.h"
#include "PBA.h"
int main()
{
	MemSchedule schedule = GeneVisitSeq(32);
	//    OPT(schedule);
	//    Fifo(schedule) ;
	//    LRU(schedule);
	//    bclock(schedule);
	PBA(schedule);
	return 0;

}