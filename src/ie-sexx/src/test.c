#include "SExxx.h"

SCAN_DATA stScanData[1081]; //270-0.25-1081;

int main()
{
    int err=0;
    uint32_t ulWindNum=0;
    char *hostPC="192.168.1.100";      
    int   portPC=5500;
    SCAN_DATA stScanData[1081];

    if( 0x00==run_node(hostPC,portPC) )
    {
        StartMeasureTransmission();

        while(1)
        {
            err = GetLidarMeasDataDistance(stScanData);
            if(0==err)
            {
                printf("Receiving the measured data winding number:%d\r\n",ulWindNum++);
                for(int i=0;i<1081;i++)
                {
                    //printf("scan_msg.ranges[%d]=%f\t,scan_msg.intensities[%d]=%f\t\r\n",i,scan_msg.ranges[i],i,scan_msg.intensities[i]);
                    printf("stScanData[%d].fAngle=%f\t,scan_msg.intensities[%d]=%f\t\r\n",i,stScanData[i].fAngle,i,stScanData[i].fDistance);
                }
                //sleep(2);
            }else
            {
                printf("Laser timed out on delivering scan, attempting to reinitialize.\r\n");
            } 
        }
    }
}