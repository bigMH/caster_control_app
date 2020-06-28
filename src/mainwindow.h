#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ros/ros.h>
#include <QMainWindow>
// #include <ros/duration.h>
// #include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <pan_tilt_msg/PanTiltCmd.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib/client/simple_action_client.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ros::NodeHandle& nh_, QWidget *parent = nullptr);
    ~MainWindow();
    int getCasterGoal();
 
private:
    Ui::MainWindow *ui;
    double stents_data_;
    ros::Publisher stents_;
    ros::Publisher pan_tilt_;
    pan_tilt_msg::PanTiltCmd pan_cmd_;
    move_base_msgs::MoveBaseGoal goal_;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> caster_client_;

private slots:
    void on_pushButtonSendGoal_clicked(bool check);
    void on_pushButtonConnect_clicked(bool check);
    void on_pushButtonCancel_clicked(bool check);
};

#endif // MAINWINDOW_H
