//
// Created by abhinavchadaga on 3/7/22.
//

#include "opencv_hw/ROSInterface.h"
#include "opencv_hw/ColorFilter.h"
#include <cv_bridge/cv_bridge.h>

ROSInterface::ROSInterface(ColorFilter &cf) : _it(_nh), _cf(cf) {
    _sub = _it.subscribe("/kinect2/hd/image_color", 1, &ROSInterface::imageCb, this);
    _b_pub = _it.advertise("blue", 1);
    _g_pub = _it.advertise("green", 1);
    _r_pub = _it.advertise("red", 1);
    _bgr_pub = _it.advertise("bgr", 1);
}

void ROSInterface::imageCb(const sensor_msgs::ImageConstPtr &msg) {
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    _cf.processImage(cv_ptr->image);

    _b_pub.publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getBlueImage()).toImageMsg());
    _g_pub.publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getGreenImage()).toImageMsg());
    _r_pub.publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getRedImage()).toImageMsg());
    _bgr_pub.publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getBGRImage()).toImageMsg());
}