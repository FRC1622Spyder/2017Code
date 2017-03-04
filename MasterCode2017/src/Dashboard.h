#ifndef SRC_DASHBOARD_H_
#define SRC_DASHBOARD_H_
#include <SmartDashboard/SmartDashboard.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <CameraServer.h>
#include <DriverStation.h>

class Dashboard {
private:
	cs::UsbCamera cam;

public:
	void DashboardInit();
	int AutoSelect();
};

#endif /* SRC_DASHBOARD_H_ */
