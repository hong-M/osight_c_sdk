/*
 * SExxx_node.cpp
 *
 *  Created on: 05-09-2017
 *  Author: Zihong MA
 ***************************************************************************
 *  OSIGHT *
 * www.osighttech.com  *
 ***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <../include/SExxx.h>

#define DEG2RAD M_PI/180.0

LASER_SCAN                         scan_msg;
USER_PARA_SYNC_RSP_T               g_stRealUserPara;
MEAS_DATA_RSP_T                    g_stMeasDataRsp;
BITS32                             g_ulWindNum;

extern int server_socket_fd;

int run_node(char *vphostPC, int vlPortPC)
{
  INT32   err;
  char *hostPC=vphostPC;
  //char *hostPC="192.168.1.100";
  char *frame_id="laser";
  int portPC=vlPortPC;
  //int portPC=5500;

  while (1)
  {
    printf("Upper IP: %s\t,Port:%d\r\n",hostPC,portPC);
    
    if(0x01==se_connect(hostPC, portPC))
    {
      close(server_socket_fd);
      printf("se_connect--error\r\n");
      continue;
    }

    if (!isConnected())
    {
      //ROS_WARN("Unable to connect, retrying.");
      printf("Unable to connect, retrying.\r\n");
      continue;
    }

    do
    {
        ////ROS_INFO_STREAM("Parameters of the synchronous message.");
	      err=UserParaSync();
    } while( 0 !=err );

    printf("scan_msg  head\r\n");
    printf("CurrentSpeed:%f\r\n",g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*1.0);
    printf("AngularResolution:%f\r\n",g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/10000000.0);
    printf("StartAngle:%f\r\n",g_stRealUserPara.stDeviceAngleInfo.lStartAngle/1000.0);
    printf("PointNum:%ld\r\n",g_stRealUserPara.ulPointNum);

    scan_msg.header.frame_id = frame_id;
    scan_msg.range_min = 0.01;
    scan_msg.range_max = g_stRealUserPara.ulMaxDistance;
    scan_msg.scan_time   =   100.0 / (g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*100);  
    scan_msg.angle_increment = (double)(g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/1000.0)/10000.0*DEG2RAD;
    scan_msg.angle_min =  (double)(g_stRealUserPara.stDeviceAngleInfo.lStartAngle*10)/ 10000.0 * DEG2RAD - M_PI / 2;
    scan_msg.angle_max = (double)(g_stRealUserPara.stDeviceAngleInfo.lStartAngle*10+(g_stRealUserPara.stDeviceParaInfo.ulAngularResolution*g_stRealUserPara.ulPointNum/1000.0)) / 10000.0 * DEG2RAD - M_PI / 2;
    printf("Device resolution is %f degrees\r\n",(double)(g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/1000)/ 10000.0 );
    printf("Device frequency is %f HZ\r\n",(double) (g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*100)/ 100.0 );

    scan_msg.ranges      = (float *)malloc(sizeof(BITS32)*g_stRealUserPara.ulPointNum);
    scan_msg.intensities = (float *)malloc(sizeof(BITS16)*g_stRealUserPara.ulPointNum);
    printf("malloc-size-%ld\r\n",sizeof(BITS32)*g_stRealUserPara.ulPointNum);

    scan_msg.time_increment = ((g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/1000.0)/10000.0)/360.0/((g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*100)/100.0);
 

    //printf("hong-close(server_socket_fd)");
    //close(server_socket_fd);
    //free(scan_msg.ranges);
    //free(scan_msg.intensities);
     return 0;  
  }
  return 0;
}

#if 0
int main(int argc, char **argv)
{
  INT32   err;

  // parameters
  //std::string hostPC;
  //string hostPC;
  char *hostPC="192.168.1.100";

  //std::string frame_id;
  char *frame_id="laser";
  //string frame_id;
  int portPC=5500;

  //ros::init(argc, argv, "sexxx");
  //ros::NodeHandle nh;
  //ros::NodeHandle n("~");
  //ros::Publisher scan_pub = nh.advertise<sensor_msgs::LaserScan>("scan", 1);

  //n.param<std::string>("hostPC", hostPC, "192.168.1.100");
  //n.param<std::string>("frame_id", frame_id, "laser");
  //n.param<int>("portPC", portPC, 5500);


  while (1)
  {
    ////ROS_INFO_STREAM("Connecting to laser at " << hostPC<<"  "<<portPC );
    ////ROS_INFO_STREAM("Upper IP: "<< hostPC << "Port: " <<  portPC <<"Connecting to laser " );
    printf("Upper IP: %s\t,Port:%d\r\n",hostPC,portPC);
    
    if(0x01==se_connect(hostPC, portPC))
    {
      close(server_socket_fd);
    }


    if (!isConnected())
    {
      //ROS_WARN("Unable to connect, retrying.");
      printf("Unable to connect, retrying.\r\n");
      continue;
    }

    do
    {
        ////ROS_INFO_STREAM("Parameters of the synchronous message.");
	      err=UserParaSync();
    } while( 0 !=err );

    ////ROS_INFO_STREAM("scan_msg  head");
    printf("scan_msg  head");

    ////ROS_INFO_STREAM("CurrentSpeed:"<<g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*1.0);
    ////ROS_INFO_STREAM("AngularResolution:"<<g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/10000000.0);
    ////ROS_INFO_STREAM("StartAngle:"<<g_stRealUserPara.stDeviceAngleInfo.lStartAngle/1000.0);
    ////ROS_INFO_STREAM("PointNum:"<<g_stRealUserPara.ulPointNum);
    printf("CurrentSpeed:%f\r\n",g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*1.0);
    printf("AngularResolution:%f\r\n",g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/10000000.0);
    printf("StartAngle:%f\r\n",g_stRealUserPara.stDeviceAngleInfo.lStartAngle/1000.0);
    printf("PointNum:%ld\r\n",g_stRealUserPara.ulPointNum);


    scan_msg.header.frame_id = frame_id;
    scan_msg.range_min = 0.01;
    //scan_msg.range_max = 500.0;   //500 meter
    scan_msg.range_max = g_stRealUserPara.ulMaxDistance;

    //scan_msg.scan_time = 100.0 / 2500;  //25HZ
    scan_msg.scan_time   =   100.0 / (g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*100);  

    //scan_msg.angle_increment = (double)2500/ 10000.0 * DEG2RAD;  //0.25 degree
    scan_msg.angle_increment = (double)(g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/1000.0)/10000.0*DEG2RAD;

    //scan_msg.angle_min = (double)0xFFF92230 / 10000.0 * DEG2RAD - M_PI / 2;   //-450000
    scan_msg.angle_min =  (double)(g_stRealUserPara.stDeviceAngleInfo.lStartAngle*10)/ 10000.0 * DEG2RAD - M_PI / 2;
   
    //scan_msg.angle_max = (double)0x225510 / 10000.0 * DEG2RAD - M_PI / 2;    //2250000
    scan_msg.angle_max = (double)(g_stRealUserPara.stDeviceAngleInfo.lStartAngle*10+(g_stRealUserPara.stDeviceParaInfo.ulAngularResolution*g_stRealUserPara.ulPointNum/1000.0)) / 10000.0 * DEG2RAD - M_PI / 2;


    ////ROS_DEBUG_STREAM("Device resolution is " << (double)2500 / 10000.0 << " degrees.");  //0.25 degree
    ////ROS_INFO_STREAM("Device resolution is " << (double)(g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/1000)/ 10000.0 << " degrees.");
    printf("Device resolution is %f degrees\r\n",(double)(g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/1000)/ 10000.0 );


    ////ROS_DEBUG_STREAM("Device frequency is " <<(double) 2500 / 100.0 << " Hz");   //25HZ
    ////ROS_INFO_STREAM("Device frequency is " <<(double) (g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*100)/ 100.0 << " Hz");
    printf("Device frequency is %f HZ\r\n",(double) (g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*100)/ 100.0 );



    //scan_msg.ranges.resize(g_stRealUserPara.ulPointNum);
    //scan_msg.intensities.resize(g_stRealUserPara.ulPointNum);
    //malloc
    scan_msg.ranges      = (float *)malloc(sizeof(BITS32)*g_stRealUserPara.ulPointNum);
    scan_msg.intensities = (float *)malloc(sizeof(BITS16)*g_stRealUserPara.ulPointNum);
    printf("malloc-size-%ld\r\n",sizeof(BITS32)*g_stRealUserPara.ulPointNum);


    //scan_msg.time_increment =(2500 / 10000.0) / 360.0  / (2500/ 100.0);   //  0.25 degree ,  25HZ
    scan_msg.time_increment = ((g_stRealUserPara.stDeviceParaInfo.ulAngularResolution/1000.0)/10000.0)/360.0/((g_stRealUserPara.stDeviceParaInfo.ucCurrentSpeed*100)/100.0);

    ////ROS_DEBUG_STREAM("Time increment is " << static_cast<int>(scan_msg.time_increment * 1000000) << " microseconds");
    //printf("Time increment is %d microseconds\r\n" ,scan_msg.time_increment * 1000000 );

    ////ROS_DEBUG("Starting measurements.");
    printf("Starting measurements.\r\n");
    
    StartMeasureTransmission();

    while (1)
    {
      //ros::Time start = ros::Time::now();

      //scan_msg.header.stamp = start;
      //++scan_msg.header.seq;

      err = GetLidarMeasData();
      if(0==err)
      {
        err=-1;
        printf("Receiving the measured data winding number:%d\r\n",g_ulWindNum++);
        ////ROS_DEBUG("Publishing scan data.");
        //scan_pub.publish(scan_msg);
        //printf("scan_msg.ranges[%d]=%f\t,scan_msg.intensities[%d]=%f\t\r\n",0,scan_msg.ranges[0],0,scan_msg.intensities[0]);
        //printf("scan_msg.ranges[%d]=%f\t,scan_msg.intensities[%d]=%f\t\r\n",1,scan_msg.ranges[1],1,scan_msg.intensities[1]);
        //printf("scan_msg.ranges[%d]=%f\t,scan_msg.intensities[%d]=%f\t\r\n",2,scan_msg.ranges[2],2,scan_msg.intensities[2]);
        //printf("scan_msg.ranges[%d]=%f\t,scan_msg.intensities[%d]=%f\t\r\n",3,scan_msg.ranges[3],3,scan_msg.intensities[3]);
        //printf("scan_msg.ranges[%d]=%f\t,scan_msg.intensities[%d]=%f\t\r\n",4,scan_msg.ranges[4],4,scan_msg.intensities[4]);
        /*
        for(int i=0;i<g_stRealUserPara.ulPointNum;i++)
        {
            printf("scan_msg.ranges[%d]=%f\t,scan_msg.intensities[%d]=%f\t\r\n",i,scan_msg.ranges[i],i,scan_msg.intensities[i]);
        }
        */
        sleep(2);

	    }else
      {
        ////ROS_DEBUG("Laser timed out on delivering scan, attempting to reinitialize.");
        printf("Laser timed out on delivering scan, attempting to reinitialize.\r\n");
        //break;
      }
      //ros::spinOnce();
    }

     ////ROS_INFO_STREAM("hong-close(server_socket_fd)");
     printf("hong-close(server_socket_fd)");
     close(server_socket_fd);
     free(scan_msg.ranges);
     free(scan_msg.intensities);
  }

  return 0;
}
#endif
