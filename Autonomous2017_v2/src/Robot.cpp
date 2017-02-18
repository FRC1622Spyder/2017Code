#include <iostream>
#include <memory>
#include <string>
#include <math.h>

#include <IterativeRobot.h>
#include <CANTalon.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#define WHEEL_DIAM 6.0;
#define DRIVE_DIAM 28.75;
#define PULSE_PER_REV 860.0;
#define PI 3.141593;

class Robot: public frc::IterativeRobot {
public:

	CANTalon *rightFrontMotor = new CANTalon(2);
	CANTalon *rightBackMotor = new CANTalon(1);
	CANTalon *leftFrontMotor = new CANTalon(4);
	CANTalon *leftBackMotor = new CANTalon(8);

	const double wheelDiam = WHEEL_DIAM;
	const double driveDiam = DRIVE_DIAM;
	const double pulsePerRev = PULSE_PER_REV;
	const double pi = PI;

	const double pulse_per_inch  = (pulsePerRev) / (wheelDiam * pi);
	const double pulse_per_radian = (driveDiam / 2) * pulse_per_inch;

	int autonomousPhase = 0;
	int counter = 0;
	int autonomousChooser = 0;

	void DriveForward(double speed, double distance){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double encoderDistance = distance * pulse_per_inch;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
		}
		else {
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			leftFrontMotor->SetEncPosition(0);
			rightFrontMotor->SetEncPosition(0);
			counter = 0;
			autonomousPhase++;
		}
	}

	void DriveBackward(double speed, double distance){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double encoderDistance = distance * pulse_per_inch;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(-speed);
			leftBackMotor->Set(-speed);
			rightFrontMotor->Set(-speed);
			rightBackMotor->Set(-speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
			std::cout << counter << std::endl;
		}
		else {
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			leftFrontMotor->SetEncPosition(0);
			rightFrontMotor->SetEncPosition(0);
			counter = 0;
			autonomousPhase++;
		}
	}

	void RotateLeft(double speed, double angle){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double radianAngle = angle * (pi /180);
		double encoderDistance =  radianAngle * pulse_per_radian;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(-speed);
			leftBackMotor->Set(-speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
		}
		else {
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			leftFrontMotor->SetEncPosition(0);
			rightFrontMotor->SetEncPosition(0);
			counter = 0;
			autonomousPhase++;
		}
	}

	void RotateRight(double speed, double angle){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double radianAngle = angle * (pi /180);
		double encoderDistance =  radianAngle * pulse_per_radian;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(-speed);
			rightBackMotor->Set(-speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
		}
		else {
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			leftFrontMotor->SetEncPosition(0);
			rightFrontMotor->SetEncPosition(0);
			counter = 0;
			autonomousPhase++;
		}
	}

	void Wait(double time){
		double periods = time * 50;
		if(counter <= periods){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
		}
		else{
			counter = 0;
			autonomousPhase++;
		}
	}

	void RobotInit() {
		rightFrontMotor->SetInverted(true);
		rightBackMotor->SetInverted(true);
		leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
		rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
		leftFrontMotor->ConfigEncoderCodesPerRev(20);
		rightFrontMotor->ConfigEncoderCodesPerRev(20);
	}

	void AutonomousInit() {
		leftFrontMotor->SetEncPosition(0);
		rightFrontMotor->SetEncPosition(0);
		autonomousPhase = 0;
		counter = 0;
		autonomousChooser = 2;
	}

	void AutonomousPeriodic() {
		//red left
		if(autonomousChooser == 1){
				if(autonomousPhase == 0){
					DriveForward(0.7, 15);
				}
				else if (autonomousPhase == 1){
				RotateCounterClockwise(0.5, 45);
		        }
				else if (autonomousPhase == 2){
	              DriveForward(0.7,12)
				}
				else if (autonomousPhase == 3){
				wait(3.0);
		        }
				else if (autonomousPhase == 4){
				DriveBackward(0.7, 5);
		        }
				else if (autonomousPhase == 5){
				RotateClockwise(0.7, 45);
	         	}
				else if (autonomousPhase == 6){
				DriveForward(0.7, 15);
		        }
				else if (autonomousPhase == 7){
				Rotate(0.7, 45);
		        }
				else if (autonomousPhase == 8){
				DriveForward(0.7, 10);
		        }


		}
		//red center
		else if(autonomousChooser == 2){
					if(autonomousPhase == 0){
				DriveForward(0.7, 10);
					}
					else if (autonomousPhase == 1){
						RotateLeft(0.7, 45);
					}
					else if (autonomousPhase == 2){
					DriveForward(0.7, 10);
		            }
					else if (autonomousPhase == 3){
					RotateRight(0.7, 45);
		            }
					else if (autonomousPhase == 4){
					DriveForward(0.7, 15);
		            }
					else if (autonomousPhase == 5){
					RotateLeft(0.7, 45);
		            }
					else if (autonomousPhase == 6){
					DriveForward(0.7,10);
					}
					else if (autonomousPhase == 7){
					wait(3);
		            }
					else if (autonomousPhase == 8){
					DriveBackward(0.7,10);
		            }
					else if (autonomousPhase == 9){
					RotateRight(0.7, 45);
	             	}
					else if (autonomousPhase == 10){
					DriveForward(0.7, 15);
		            }
					else if (autonomousPhase == 11){
					RotateLeft(0.7, 45);
		            }
					else if (autonomousPhase == 12){
					DriveForward(0.7, 10);
	             	}

		 }

	//red left
		else if(autonomousChooser == 3){
			if(autonomousPhase == 1){
			 DriveForward(0.7,10);
			}
			else if (autonomousPhase == 1){
			RotateRight(0.7,5);
		    }
			else if (autonomousPhase == 2){
			DriveForward(0.7,5);
		    }
			else if (autonomousPhase == 3){
			DriveBackward(0.7,45);
	     	}
			else if (autonomousPhase == 4){
			RotateLeft(0.7,45);
		    }
			else if (autonomousPhase == 5){
			DriveForward(0.7,20);
		    }
			else if (autonomousPhase == 6){
			RotateLeft(0.7, 45);
		    }
			else if (autonomousPhase == 7){
			DriveForward(0.7,5);
		    }
			else if (autonomousPhase == 8){
			DriveBackward(0.7,45);
		    }
			else if (autonomousPhase == 9){
			RotateLeft(0.7,45);
		    }
			else if (autonomousPhase == 10){
			DriveForward(0.7,20);
		    }
			else if (autonomousPhase == 11){
			RotateRight(0.7,45);
		    }
			else if (autonomousPhase == 12){
			DriveForward(0.7,10);
		    }
	}
	//blue left
		else if(autonomousChooser == 4){
		    if(autonomousPhase == 0){
			DriveForward(0.7, 20);
		    }
			else if (autonomousPhase == 1){
				RotateLeft(0.7,10);
			}
			else if (autonomousPhase == 2){
	            DriveForward(0.6 10);
			}
			else if (autonomousPhase == 3){
                DriveBackward(0.7, 15);
			}
			else if (autonomousPhase == 4){
                 RotateRight(0.3, 45)
			}
			else if (autonomousPhase == 5){
                 DriveForward(0.7, 45);
			}
			else if (autonomousPhase == 6){
                 RotateLeft(0.7, 45);
			}
			else if (autonomousPhase == 7){
				DriveForward(0.7, 10);
			}
			else if (autonomousPhase == 8){
				DriveBackward(0.7,45);
			}
			else if (autonomousPhase == 9){
		        RotateClockwise(0.6, 45);
			}
			else if (autonomousPhase == 10){
		        DriveForward(0.7,10)
						}
	      //blue left
	    else if(autonomousChooser == 5){
	                   if(autonomousPhase == 4){


		//blue left
	               else if(autonomousChooser == 4){
			       if(autonomousPhase == 5)}
	               }
	void TeleopInit() {

	}

	void TeleopPeriodic() {

	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)
