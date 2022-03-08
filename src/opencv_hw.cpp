#include <ros/init.h>
#include "opencv_hw/ColorFilter.h"
#include "opencv_hw/ROSInterface.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_out");
    ColorFilter cf;
    ROSInterface ros_interface(cf);
    ros::spin();
    return 0;
}