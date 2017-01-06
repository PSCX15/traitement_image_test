#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;



int main( int argc, char** argv )
{
	ros::init(argc, argv, "image_publisher");
	if(argc < 3){
		cout << "Not enough parameters" << endl;
	}

	Mat I, J;
	if( argc == 4 && !strcmp(argv[3], "G"))
		I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	else
		I = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!I.data)
	{
		cout << "The image" << argv[1] << "could not be loaded." << endl;
		return -1;
	}

	int divideWith;
	stringstream s;
	s << argv[2];
	s >> divideWith;
	if (!s)
	{
		cout << "Invalid number entered for dividing." << endl;
		return -1;
	}

	uchar table[256];
	for (int i = 0; i < 256; ++i){
		table[i] = divideWith * (i/divideWith);
	}

	J = ScanImageAndReduceIterator(I,table);

	ros::init(argc, argv, "image_publisher");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Publisher pub = it.advertise("camera/image", 1);
  cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  cv::waitKey(30);
  sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

  ros::Rate loop_rate(5);
  while (nh.ok()) {
  pub.publish(msg);
  ros::spinOnce();
  loop_rate.sleep();
  }

