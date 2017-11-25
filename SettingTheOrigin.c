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

void penDown(void)
{
		nmotorEncoder[motorC] = 0;
		while (nMotorEncoder[motorC] < 55)

		{
			motor[motorC] = 10;
		}
		motor[motorC] = 0;
}

void penUp(void)
{
	nMotorEncoder[motorC] = 0;
	while (nMotorEncoder[motorC] > -55)
	{
		motor[motorC] = -10;
	}
	motor[motorC] = 0;
}

task main()
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
