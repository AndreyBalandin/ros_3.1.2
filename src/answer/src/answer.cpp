#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "visualization_msgs/Marker.h"

#define POINTS_LIMIT 5


class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    pub = n.advertise<visualization_msgs::Marker>("/output", 1);
    sub = n.subscribe("/input", 1, &SubscribeAndPublish::callback, this);
    points_counter = 0;
  }

  void callback(const geometry_msgs::Point::ConstPtr& point)
  {
    points[points_counter] = *point;
    points_counter += 1;

    if (points_counter == POINTS_LIMIT) {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "frame";
        marker.header.stamp = ros::Time::now();
        marker.ns = "points";
        marker.id = 0;
        marker.type = visualization_msgs::Marker::POINTS;
        marker.action = visualization_msgs::Marker::ADD;
        marker.scale.x = 0.1;
        marker.scale.y = 0.1;
        marker.color.a = 1.0;
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        for (int i=0; i<POINTS_LIMIT; ++i)
            marker.points.push_back(points[i]);
        pub.publish(marker);
        points_counter = 0;
    }
  }

private:
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::Subscriber sub;
  int points_counter;
  geometry_msgs::Point points[POINTS_LIMIT];

}; //End of class SubscribeAndPublish


int main(int argc, char **argv)
{
  ros::init(argc, argv, "answer");
  SubscribeAndPublish SAPObject;
  ros::spin();

  return 0;
}
