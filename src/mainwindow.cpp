#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(ros::NodeHandle& nh_, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  caster_client_(nh_, "move_base", true) {

    ui->setupUi(this);
    if(!caster_client_.isServerConnected()) {
      ui->textEdit->setText("Server doesn't connect.");
    }
    stents_ = nh_.advertise<std_msgs::Float64>("/caster/body_controller/command", 1);
    pan_tilt_ = nh_.advertise<pan_tilt_msg::PanTiltCmd>("/pan_tilt_driver_node/pan_tilt_cmd", 1);

    stents_data_.data = 0.0;

    pan_cmd_.speed = 0;
    pan_cmd_.yaw   = 0.0;
    pan_cmd_.pitch = 0.0;

    goal_.target_pose.pose.position.z = 0;
    goal_.target_pose.pose.orientation.x = 0;
    goal_.target_pose.pose.orientation.y = 0;
    goal_.target_pose.header.frame_id = "map";
     
  }

 MainWindow::~MainWindow() {

     delete ui;
 }

int MainWindow::getCasterGoal() {
  ui->textEdit->setText("Server has connected.");
  goal_.target_pose.pose.position.x = ui->XlineEdit->text().toDouble();
  goal_.target_pose.pose.position.y = ui->YlineEdit->text().toDouble();
  goal_.target_pose.pose.orientation.z = ui->ZlineEdit->text().toDouble();
  goal_.target_pose.pose.orientation.w = ui->WlineEdit->text().toDouble();

  caster_client_.sendGoal(goal_);
  return 0;
}

int MainWindow::getPanTiltCmd() {
  pan_cmd_.yaw   = ui->lineEditYaw->text().toDouble();
  pan_cmd_.pitch = ui->lineEditPitch->text().toDouble();
  pan_cmd_.speed = ui->lineEditSpeed->text().toDouble();
  return 0;
}

void MainWindow::on_pushButtonSendGoal_clicked(bool check) {
  getCasterGoal();
  
}

void MainWindow::on_pushButtonCancel_clicked(bool check) {
  caster_client_.cancelGoal();
  ui->textEdit->setText("Caster goal had canceled.");

}

void MainWindow::on_pushButtonSendPanCmd_clicked(bool check) {
  getPanTiltCmd();
  pan_tilt_.publish(pan_cmd_);
}

void MainWindow::on_pushButtonSendHight_clicked(bool check) {
  stents_data_.data = ui->lineEditHight->text().toDouble();
  stents_.publish(stents_data_);
}

void MainWindow::on_pushButtonConnect_clicked(bool check) {
  ui->textEdit->setText("Waiting for server...");
  caster_client_.waitForServer();
  ui->textEdit->setText("Server has connected.");
}

void MainWindow::on_pushButtonExit_clicked(bool check) {
  QApplication::exit();
}
