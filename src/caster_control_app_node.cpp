#include <ros/ros.h>
#include <mainwindow.h>
#include <QApplication>

 int main(int argc, char** argv) {
  QApplication a (argc, argv);
  ros::init(argc, argv, "caster_controller");
  ros::NodeHandle node;
  MainWindow w(node);

  w.show();
  return a.exec();
}
