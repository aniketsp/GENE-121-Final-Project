
const float rx = 2.70;
const float ry = 1.25
const int motorspeed = 30;
const float maxX = 0;
const float maxY = 0;

bool receive_Size(string paper, int & x, int & y)
{
	bool result = false;
	if (paper=="A4")
	{
		x = 297;
		y = 210;
		result = true;
	}
	return result;
}

int toEncoderX(float distance)
{
	return distance/(2*PI*rX) * 360;
}

int toEncoderY(float distance)
{
	return distance/(2*PI*rY) * 360;
}

void setxmotor(void) //sets x motor to 0 position
{
	while (SensorValue[S1] != 1)
	{
		motor[motorD] = 30;
	}
	motor[motorD] = 0;
	int width = nMotorEncoder[motorD];

	while (nMotorEncoder[motorD] > 0)
	{
		motor[motorD] = -30;
	}
	motor[motorD] = 0;
}
//y motor will be set using color sensor...some way mount color sensor near pencil
//all coordinates are relative to the top-right corner of page because of motor orientation

void moveX(float distance, int speed, int width)
{
	if ((nMotorEncoder[motorD] + distance)>0 && (nMotorEncoder[motorD]+distance)< width)
	{
		int originalEncoder = nMotorEncoder[motorD];
		int encoder = toEncoderX(distance);
		while (nMotorEncoder[motorD] != originalEncoder + encoder)
		{
			if (distance>=0)
			motor[motorD] = speed;
			else
			motor[motorD] = -speed;
		}
		motor[motorD] = 0;
	}
}

void moveY(float distance, int speed)
{
	if ((nMotorEncoder[motorB]+distance)>0 && (nMotorEncoder[motorB]+distance)<665)
	{
		int originalEncoder = nMotorEncoder[motorB];
		int encoder = toEncoderY(distance);
		int currentY = 0;
		while (nMotorEncoder[motorB] != originalEncoder + encoder)
		{
			if (distance>=0)
			motor[motorB] = speed;
			else
			motor[motorB] = -speed;
		}
		motor[motorB] = 0;
		currentY += distance;
	}
}

float toCoordinateY(int encoder)
{
	return (encoder/360)*2*PI*rY;


float toCoordinateX(int encoder)
{
	return (encoder/360)*2*PI*rX;
}

void moveTo(float startx, float starty, float finalx, float finaly)
{
	float xdiff = finalx - startx;
	float ydiff = finaly - starty;

	if (abs(xdiff) >= abs(ydiff))
	{
		float yTime = xdiff/motorspeed;
		int ySpeed = ydiff/yTime;

		moveX(xdiff, motorspeed);
		moveY(ydiff, ySpeed);
	}
	else
	{
		float xTime = ydiff/motorspeed;
		float xSpeed = xdiff/xTime;

		moveY(ydiff, motorspeed);
		moveX(xdiff, xSpeed);
	}
}

void penDown(void)
{
		nmotorEncoder[motorC] = 0;
		while (nMotorEncoder[motorC] < 50)

		{
			motor[motorC] = 10;
		}
		motor[motorC] = 0;
}

void penUp(void)
{
	nMotorEncoder[motorC] = 0;
	while (nMotorEncoder[motorC] > -50)
	{
		motor[motorC] = -10;
	}
	motor[motorC] = 0;
}

void drawline(int currentX, int currentY, int startX, int startY, int finalX, int finalY)
{
	moveTo(currentX, currentY, startX, startY);
	wait1Msec(100);
	penDown();
	wait1Msec(100);
	moveTo(startX, startY, finalX, finalY);
	wait1Msec(100);
	penUp();
}

bool canvas_Present(int sensor)
{
	if (sensorValue[sensor]!=6 && sensorValue[sensor]!=1)
		return false;
	else
		return true;
}

void end_program(int sensor)
{
	if (canvas_Present(sensor)==false)
	{
		motor[motorA] = 0;
		motor[motorB] = 0;
		motor[motorC] = 0;
		motor[motorD] = 0;
	}
}

void originSet(int & x, int & y)
{
	penUp();
	wait1Msec(1000);
	setxmotor();
	wait1Msec(1000);
	nMotorEncoder[motorB] = 0;
	while (nMotorEncoder[motorB] < 240
		)
	{
		motor[motorB] = 30;
	}
	motor[motorB] = 0;
	nMotorEncoder[motorB] = 0;
	wait1Msec(1000);
	penDown();


}

int runtime()
{
	return time1[T1]/10;
}


