#include "canfestival.h"

unsigned int TimeCNT=0;//时间计数
unsigned int NextTime=0;//下一次触发时间计数
unsigned int TIMER_MAX_COUNT=70000;//最大时间计数
static TIMEVAL last_time_set = TIMEVAL_MAX;//上一次的时间计数setTimer和getElapsedTime函数实现如下：

//Set the next alarm //
void setTimer(TIMEVAL value)
{
	NextTime=(TimeCNT+value)%TIMER_MAX_COUNT;
}

// Get the elapsed time since the last occured alarm //
TIMEVAL getElapsedTime(void)
{
	int ret=0;
	ret = TimeCNT> last_time_set ? TimeCNT - last_time_set : TimeCNT + TIMER_MAX_COUNT - last_time_set;
	last_time_set = TimeCNT;
	return ret;
}


unsigned char canSend(CAN_PORT notused, Message *m)
{
/*	uint32_t i;
	CanTxMsg *ptx_msg=&TxMessage;
	ptx_msg->StdId = m->cob_id;
    if(m->rtr) {
        ptx_msg->RTR = CAN_RTR_REMOTE;
    }
    else {
        ptx_msg->RTR = CAN_RTR_DATA;
    }
    ptx_msg->IDE = CAN_ID_STD;
    ptx_msg->DLC = m->len;
    for(i = 0; i < m->len; i++) {
        ptx_msg->Data = m->data;
    }
    
    
    if( CAN_Transmit( CAN1, ptx_msg )==CAN_NO_MB) {
        return 0xff;
    }
    else {
        return 0x00;
    }*/
		return 0;
}

//要开一个1毫秒的定时器，每1毫秒调用一下下面这个函数。 
void timerForCan(void)
{
	TimeCNT++;
	if (TimeCNT>=TIMER_MAX_COUNT)
	{
		TimeCNT=0;
	}

	if (TimeCNT==NextTime)
  {
		TimeDispatch();
	}
}

/*
void CAN1_RX0_IRQHandler(void)
{
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
    //接收处理
    m.cob_id=RxMessage.StdId;
    
    if(RxMessage.RTR == CAN_RTR_REMOTE)
    m.rtr=1;
    else if(RxMessage.RTR == CAN_RTR_DATA)
    m.rtr=0;
    m.len=RxMessage.DLC;
    for(i = 0; i < RxMessage.DLC; i++)
    m.data=RxMessage.Data;
    
    canDispatch(&TestSlave_Data, &m);
}
*/

