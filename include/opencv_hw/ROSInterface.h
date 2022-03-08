//
// Created by abhinavchadaga on 3/7/22.
//

#ifndef OPENCV_HW_ROSINTERFACE_H
#define OPENCV_HW_ROSINTERFACE_H


#include <ros/node_handle.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "ColorFilter.h"

class ROSInterface {
protected:
    ros::NodeHandle _nh;
    image_transport::ImageTransport _it;
    image_transport::Publisher _b_pub;
    image_transport::Publisher _g_pub;
    image_transport::Publisher _r_pub;
    image_transport::Publisher _bgr_pub;
    image_transport::Subscriber _sub;
    ColorFilter _cf;
public:
    explicit ROSInterface(ColorFilter &cf);

    void imageCb(const sensor_msgs::ImageConstPtr &msg);
};


#endif //OPENCV_HW_ROSINTERFACE_H
