#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    pe,             sensorAnalog)
#pragma config(Sensor, dgtl1,  flyEnc,         sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  flyLed,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  intakeLed,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl5,  leftLim,        sensorTouch)
#pragma config(Sensor, dgtl6,  rightLim,       sensorTouch)
#pragma config(Sensor, dgtl7,  red,            sensorTouch)
#pragma config(Sensor, dgtl8,  back,           sensorTouch)
#pragma config(Sensor, dgtl10, redLed,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, yellowLed,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, greenLed,       sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  lDriveEnc,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rDriveEnc,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           lift,          tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           brWheel,       tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           mrWheel,       tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port4,           frWheel,       tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rFly,          tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           lFly,          tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           flWheel,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           mlWheel,       tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port9,           blWheel,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          intake,        tmotorVex393TurboSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define RKCOMP_LCD //Enable LCD stuff in rkCompetition
//#define RKCOMP_DEBUG //Comment to disable debug mode

#define MODE_COMPETITION "Competition" //Competition (default) mode
#define MODE_SKILLS_DRV "Driver Skills" //Driver skills mode
#define MODE_SKILLS_PGM "Prgm. Skills" //Programming skills mode

#define PGM_MODE MODE_COMPETITION
//#define PGM_MODE MODE_SKILLS_DRV
//#define PGM_MODE MODE_SKILLS_PGM

#define RKCOMP_DEBUG_MENU_COND vexRT[Btn8L]
/*
#define RKCOMP_DEBUG_DISABLE_COND vexRT[Btn8L]
#define RKCOMP_DEBUG_AUTON_COND vexRT[Btn8D]
#define RKCOMP_DEBUG_DRIVER_COND vexRT[Btn8R]
#define RKCOMP_DEBUG_RESTART_COND vexRT[Btn6U]
*/

#define SAVE_ENC_BTN vexRT[Btn8L]
#define SAVE_ENC_MAX 15

#define FLY_LR_BTN vexRT[Btn7U]
#define FLY_MR_BTN vexRT[Btn7L]
#define FLY_SR_BTN vexRT[Btn7D]
#define FLY_OFF_BTN vexRT[Btn7R]

#define FLY_LR_BTN_2 vexRT[Btn7UXmtr2]
#define FLY_MR_BTN_2 vexRT[Btn7LXmtr2]
#define FLY_SR_BTN_2 vexRT[Btn7DXmtr2]
#define FLY_OFF_BTN_2 vexRT[Btn7RXmtr2]

#define FLY_BTNS (FLY_LR_BTN || FLY_MR_BTN || FLY_SR_BTN || FLY_OFF_BTN || FLY_LR_BTN_2 || FLY_MR_BTN_2 || FLY_SR_BTN_2 || FLY_OFF_BTN_2)

#define PWR_BTN_DOWN ((nLCDButtons & kButtonLeft) || vexRT[Btn5D] || vexRT[Btn8DXmtr2])
#define PWR_BTN_UP ((nLCDButtons & kButtonRight) || vexRT[Btn5U] || vexRT[Btn8UXmtr2])

#define DRIVE_ROT joyAnalog(ChRX, 10)
#define DRIVE_FWD joyAnalog(ChLY, 10)
#define DRIVE_LEFT joyAnalog(ChLY, 10)
#define DRIVE_RIGHT joyAnalog(ChRY, 10)

#define DRIVE_TANK_BTN vexRT[Btn8L]
#define DRIVE_FLIP_BTN vexRT[Btn8R]

#define FEEDIN_BTN vexRT[Btn6U]
#define FEEDOUT_BTN vexRT[Btn6D]

#define INTAKE_FEEDIN_BTN (FEEDIN_BTN || vexRT[Btn5UXmtr2])
#define INTAKE_FEEDOUT_BTN (FEEDOUT_BTN || vexRT[Btn5DXmtr2])

#define LIFT_RAISE_BTN (FEEDIN_BTN || vexRT[Btn6UXmtr2])
#define LIFT_LOWER_BTN (FEEDOUT_BTN)

#define FIRE_BTN vexRT[Btn8U]

#define BATT_WARNING_DISMISS (nLCDButtons || vexRT[Btn8D] || (abs(vexRT[AccelY]) > 63)))

#include "rkUtil/lib.h"
#include "rkUtil/floatDlog.h"

#include "rkLogic/dlatch.h"

#include "rkLcd/lib.h"

#include "rkControl/base.h"
#include "rkControl/diff.h"
#include "rkControl/rollAvg.h"
#include "rkControl/tbh.h"
#include "rkControl/tbhController.h"
#include "rkControl/pid.h"

#include "rkCompetition/lib.h"

#define USE_PRELOAD_AUTON //Comment to start the intake immediately in auton

typedef struct {
	int encVals[SAVE_ENC_MAX],
		deltaEnc[SAVE_ENC_MAX];
} DriveEnc;

int flyDir,
	shotCount = 0;

float flyPwr[4] = { 0, 1920, 2435, 2875 };

const string flyPwrNames[4] = {
  "Off",
  "Short Power",
  "Mid Power",
  "Long Power",
};

const float velThresh = 20,
  accelThresh = 75,
  driveFacOffs = .25,
  driveFacRange = 1 - driveFacOffs,
  masterDriveFacOffs = .75,
  masterDriveFacRange = 1 - masterDriveFacOffs;

DLatch ballShot;

/*
#if PGM_MODE == MODE_SKILLS_PGM
const float autonFlyPwr = flyPwr[2];
#else
const float autonFlyPwr = flyPwr[3];
#endif
*/

const float autonFlyPwr[2] = { 2680, 2710 };

ADiff flyDiff, fly2Diff, lDriveDiff, rDriveDiff;
RAFlt flyDispFlt, flyDispErrFlt, fly2Flt;
Tbh flyTbh;
TbhController flyCtl;
DriveEnc lDrive, rDrive;
Pid lPid, rPid;

task lcd() {
  const float flyPwrIncrement = 5;
  const word battThresh = 7200;
  const long pwrBtnsDelayInterval = 250,
    pwrBtnsRepeatInterval = 100,
    dispPwrTimeout = 1000;

  bool battWarning = false,
    flash = false,
    flashLeds,
    forceBattWarning = true,
    pwrBtnsDown,
    pwrBtnsDelayed,
    pwrBtnsRepeating;

  float pwrBtns;
  long time = nSysTime, startTs = time, flashTs = time, dispPwrTs = time, pwrBtnTs = time;
  string str;

  DLatch dismissWarningLatch, pwrBtnLatch;

  while (true) {
    time = nSysTime;
    battWarning = nImmediateBatteryLevel < battThresh || BackupBatteryLevel < battThresh;

    if (flyTbh.doRun) {
      flashLeds = false;

      SensorValue[redLed] =
        SensorValue[yellowLed] =
        SensorValue[greenLed] = 0;

      if (fabs(flyDispErrFlt.out) <= velThresh) {
        if (fabs(fly2Flt.out) <= accelThresh) SensorValue[greenLed] = 1;
        else  SensorValue[yellowLed] = 1;
      }
      else SensorValue[redLed] = 1;
    }
    else if (battWarning) {
      if ((time - flashTs) >= 500) {
        flash = !flash;
        flashTs = time;
      }

      flashLeds = true;
    }
    else {
      SensorValue[redLed] =
        SensorValue[yellowLed] =
        SensorValue[greenLed] = 0;
    }

    clearLCD();

    if ((time - startTs) <= 3000) {
		  bLCDBacklight = true;

		  displayLCDCenteredString(0, "Program Mode:");
		  displayLCDCenteredString(1, PGM_MODE);
    }
    else if (nLCDButtons & kButtonCenter) {
      bLCDBacklight = true;

      displayLCDCenteredString(0, "Battery:");

      sprintBatt(str, in1);

      displayLCDString(1, 0, str);
    }
    else if (!flyTbh.doRun && battWarning && (rkBotDisabled || rkAutonMode || forceBattWarning)) {
      bLCDBacklight = flash;

      if (flash) displayLCDCenteredString(0, "BATTERY WARNING");

      sprintBatt(str);
      displayLCDString(1, 0, str);

      if (fallingEdge(&dismissWarningLatch, BATT_WARNING_DISMISS) forceBattWarning = false;
    }
    else if (rkBotDisabled) {
      bLCDBacklight = false;

      displayLCDCenteredString(0, "Moosebot Mk. IV");
      displayLCDCenteredString(1, "4800Buckets");
    }
    else if (rkAutonMode) {
      bLCDBacklight = true;

      displayLCDCenteredString(0, "BUCKETS MODE");
      displayLCDCenteredString(1, "ENGAGED");
    }
    else { //User op mode
      bLCDBacklight = true;

      pwrBtnsDown = PWR_BTN_DOWN ^ PWR_BTN_UP;
      risingEdge(&pwrBtnLatch, pwrBtnsDown);

      if ((pwrBtnsDown || FLY_BTNS) && flyDir) dispPwrTs = time;

      if (pwrBtnsDown) {
        dispPwrTs = time;

        if (pwrBtnLatch.out || (time - pwrBtnTs >= (pwrBtnsRepeating ? pwrBtnsRepeatInterval : pwrBtnsDelayInterval))) {
          pwrBtnTs = time;

          if (pwrBtnsDelayed) {
            if (!pwrBtnsRepeating) pwrBtnsRepeating = true;
          }
          else pwrBtnsDelayed = true;

          pwrBtns = twoWay(PWR_BTN_DOWN, -flyPwrIncrement, PWR_BTN_UP, flyPwrIncrement);

          if (flyDir) {
            flyPwr[flyDir] += pwrBtns;
            playImmediateTone(pwrBtns > 0 ? 2700 : 2000, 5);
          }
        }
      }
      else pwrBtnsDelayed = pwrBtnsRepeating = false;

      if (time - dispPwrTs <= dispPwrTimeout && flyDir) {
        displayLCDCenteredString(0, flyPwrNames[flyDir]);
        displayLCDNumber(1, 0, flyPwr[flyDir]);
      }
      else if (flyTbh.doRun) {
        sprintf(str, "% 07.1f  % 07.1f",
          fmaxf(-9999.9, fminf(9999.9, flyDispFlt.out)),
          fmaxf(-9999.9, fminf(9999.9, -flyDispErrFlt.out)));
        displayLCDString(0, 0, str);

        sprintf(str, "% 07.1f  % 07.1f",
          fmaxf(-9999.9, fminf(9999.9, flyTbh.deriv)),
          fmaxf(-9999.9, fminf(9999.9, flyTbh.out)));
        displayLCDString(1, 0, str);
      }
      else {
        sprintf(str, "%-8s%8s", "Speed", "Error");
        displayLCDString(0, 0, str);

        sprintf(str, "%-8s%8s", "Accel", "Out");
        displayLCDString(1, 0, str);
      }
    }

    if (flashLeds) {
      SensorValue[redLed] =
        SensorValue[yellowLed] =
        SensorValue[greenLed] = flash;
    }

    wait1Msec(20);
  }
}

void startFlyTbh(bool useCtl) {
  resetTbh(&flyTbh, 0);

  resetDiff(&flyDiff, 0);
  resetDiff(&fly2Diff, 0);

  resetRAFlt(&fly2Flt, 0);

  if (useCtl) updateTbhController(&flyCtl, 0);
  else setTbhDoRun(&flyTbh, true);

  SensorValue[flyEnc] = 0;
}

void stopCtls() {
  setTbhDoRun(&flyTbh, false);

  stopCtlLoop();
}

#define FLY_DISP_FLT_LEN 10
#define FLY_DISP_ERR_FLT_LEN 10
#define FLY2_FLT_LEN 5
float flyDispFltBuf[FLY_DISP_FLT_LEN],
  flyDispErrFltBuf[FLY_DISP_ERR_FLT_LEN],
  flyFltBuf[FLY2_FLT_LEN];

void init() {
  ctlLoopInterval = 50;

  initTbh(&flyTbh, 0, .09, .001, .0007, 127, true);  //Initialize TBH with coefficients								You will change these numbers to tune the loop

  initTbhController(&flyCtl, &flyTbh, false);

  initRAFlt(&flyDispFlt, flyDispFltBuf, FLY_DISP_FLT_LEN);
  initRAFlt(&flyDispErrFlt, flyDispErrFltBuf, FLY_DISP_ERR_FLT_LEN);
  initRAFlt(&fly2Flt, flyFltBuf, FLY2_FLT_LEN);

  initPid(&lPid, 10, 1, .001, .01, 127, false);
  initPid(&rPid, 10, 1, .001, .01, 127, false);
}

void updateCtl(float dt) {
  updateDiff(&flyDiff, SensorValue[flyEnc] / 2., dt);
  updateDiff(&fly2Diff, flyDiff.out, dt);
  updateDiff(&lDriveDiff, SensorValue[lDriveEnc], dt);
  updateDiff(&rDriveDiff, SensorValue[rDriveEnc], dt);

  updateRAFlt(&flyDispFlt, flyDiff.out);
  updateRAFlt(&fly2Flt, fly2Diff.out);

  if (flyTbh.doUpdate)
    motor[lFly] =
    motor[rFly] =
      updateTbh(&flyTbh, flyDiff.out, fly2Flt.out, dt);

  updatePid(&lPid, SensorValue[lDriveEnc], lDriveDiff.out, dt);
  updatePid(&rPid, SensorValue[rDriveEnc], rDriveDiff.out, dt);

  updateRAFlt(&flyDispErrFlt, flyTbh.err);

  if(motor[lift] >= 0 && fallingEdge(&ballShot, (SensorValue[leftLim] || SensorValue[rightLim])))
  	shotCount++;
}

task auton() {																																			//AUTONOMOUS
  playSoundFile("Start_converted.wav");

  const float recoilThresh = 40;

  startFlyTbh(false);
  startCtlLoop();

  setPidDoRun(&lPid, true);
  setPidDoRun(&rPid, true);

 	if(SensorValue[red]) {
 		if(SensorValue[back]) {

 			setTbh(&flyTbh, autonFlyPwr[0]);

 			setPid(&lPid, 915); //drive straight
  		setPid(&rPid, -890);

  		while(!lPid.isOnTgt && !rPid.isOnTgt)
  			wait1Msec(5);

			movePid(&lPid, 85); //turn
			movePid(&rPid, 154);

			while(!lPid.isOnTgt && !rPid.isOnTgt)
  			wait1Msec(5);

			movePid(&lPid, -338); //drive straight
			movePid(&rPid, 381);

			while(!lPid.isOnTgt && !rPid.isOnTgt) {
				motor[intake] =
  				127;
  			if(!SensorValue[leftLim] && !SensorValue[rightLim])
  				motor[lift] = 127;
  			else
  				motor[lift] = 0;
	  		wait1Msec(5);
	  	}

	  	motor[intake] =
	  		motor[lift] =
	  		0;

			movePid(&lPid, -102); // turn
			movePid(&rPid, -82);

			while(!lPid.isOnTgt && !rPid.isOnTgt)
	  		wait1Msec(5);

	  	while(shotCount < 4) { //shoot
	  		motor[intake] = 127;
	  		if(flyTbh.isOnTgt)
	  			motor[lift] = 127;
	  		wait1Msec(5);
	  	}

	  	setTbh(&flyTbh, autonFlyPwr[1]);

 			movePid(&lPid, 111); //turn
	  	movePid(&rPid, 77);

  		while(!lPid.isOnTgt && !rPid.isOnTgt)
  			wait1Msec(5);

  		movePid(&lPid, -386); //drive straight
  		movePid(&rPid, 365);

  		while(!lPid.isOnTgt && !rPid.isOnTgt) { //intake
  			motor[intake] =
  				127;
  			if(!SensorValue[leftLim] && !SensorValue[rightLim])
  				motor[lift] = 127;
  			else
  				motor[lift] = 0;
  			wait1Msec(5);
  		}

  		motor[intake] =
  			motor[lift] =
  			0;

  		movePid(&lPid, -145); //turn
  		movePid(&rPid, -51);

 			while(!lPid.isOnTgt && !rPid.isOnTgt)
 	 			wait1Msec(5);
 	 		while(shotCount < 8) { //shoot
 	 			motor[intake] =	127;
 	 			if(flyTbh.isOnTgt)
 	 				motor[lift] = 127;
 	 			else
 	 				motor[lift] = 0;
 	 		}
 		}

 		else {

 		}
 	}

 	else {
 		if(SensorValue[back]) {

 			setTbh(&flyTbh, autonFlyPwr[0]);

	  	setPid(&lPid, 915); //drive straight
  		setPid(&rPid, -890);

  		while(!lPid.isOnTgt && !rPid.isOnTgt)
  			wait1Msec(5);

			movePid(&lPid, -85); //turn
			movePid(&rPid, -154);

			while(!lPid.isOnTgt && !rPid.isOnTgt)
  			wait1Msec(5);

			movePid(&lPid, -338); //drive straight
			movePid(&rPid, 381);

			while(!lPid.isOnTgt && !rPid.isOnTgt) {
				motor[intake] =
  				127;
  			if(!SensorValue[leftLim] && !SensorValue[rightLim])
  				motor[lift] = 127;
  			else
  				motor[lift] = 0;
	  		wait1Msec(5);
	  	}

	  	motor[intake] =
	  		motor[lift] =
	  		0;

			movePid(&lPid, 102); // turn
			movePid(&rPid, 82);

			while(!lPid.isOnTgt && !rPid.isOnTgt)
	  		wait1Msec(5);

	  	while(shotCount < 4) { //shoot
	  		motor[intake] =
  				127;
  			if(flyTbh.isOnTgt)
  				motor[lift] = 127;
  			else
  				motor[lift] = 0;
	  		wait1Msec(5);
	  	}

	  	setTbh(&flyTbh, autonFlyPwr[1]);

 			movePid(&lPid, -111); //turn
	  	movePid(&rPid, -77);

  		while(!lPid.isOnTgt && !rPid.isOnTgt)
  			wait1Msec(5);

  		movePid(&lPid, -386); //drive straight
  		movePid(&rPid, 365);

  		while(!lPid.isOnTgt && !rPid.isOnTgt) { //intake
  			motor[intake] =
  				127;
  			if(!SensorValue[leftLim] && !SensorValue[rightLim])
  				motor[lift] = 127;
  			else
  				motor[lift] = 0;
  			wait1Msec(5);
  		}

  		motor[intake] =
  			motor[lift] =
  			0;

  		movePid(&lPid, 145); //turn
  		movePid(&rPid, 51);

 			while(!lPid.isOnTgt && !rPid.isOnTgt)
 	 			wait1Msec(5);
 	 		while(shotCount < 8) //shoot
 	 			motor[intake] =
 	 				motor[lift] =
 	 				127;
		}
		else {

		}
	}

  /*
  Speed for 2nd stack- 2710
  */

/*#ifdef USE_PRELOAD_AUTON
  block(!(isTbhInThresh(&flyTbh, velThresh) &&
    isTbhDerivInThresh(&flyTbh, accelThresh)));

  while (true) {
    motor[intake] = motor[lift] = 80;

    block(isTbhInThresh(&flyTbh, recoilThresh) &&
      isTbhDerivInThresh(&flyTbh, accelThresh));

    motor[intake] = motor[lift] = 0;

    block(!(isTbhInThresh(&flyTbh, velThresh) &&
      isTbhDerivInThresh(&flyTbh, accelThresh)));

    wait1Msec(20);
  }
#else
  motor[intake] = motor[lift] = 127;
#endif*/
}

void endAuton() {
  stopCtls();
}

task userOp() {
  startFlyTbh(true);
  startCtlLoop();

  DLatch cutLatch,
    flipLatch,
    flipDownLatch,
    tankLatch,
    flyLRLatch,
    flyMRLatch,
    flySRLatch,
    flyOffLatch,
    flyLRLatch2,
    flyMRLatch2,
    flySRLatch2,
    flyOffLatch2,
    saveEncsLatch;

  static int saveEncs = 0;

  resetDLatch(&cutLatch, 0);
  resetDLatch(&flipLatch, 0);
  resetDLatch(&tankLatch, 0);
  resetDLatch(&flyLRLatch, 0);
  resetDLatch(&flyMRLatch, 0);
  resetDLatch(&flySRLatch, 0);
  resetDLatch(&flyOffLatch, 0);
  resetDLatch(&flyLRLatch2, 0);
  resetDLatch(&flyMRLatch2, 0);
  resetDLatch(&flySRLatch2, 0);
  resetDLatch(&flyOffLatch2, 0);
  resetDLatch(&saveEncsLatch, 0);

  word mMid, mSide, sMid, sSide;
  float fMid, fSide, fMidFac, fSideFac, fMMid, fMSide, fSMid, fSSide;

  while (true) {
    risingBistable(&flipLatch, DRIVE_FLIP_BTN);

    if (risingBistable(&tankLatch, DRIVE_TANK_BTN)) {
      float left = DRIVE_LEFT,
        right = DRIVE_RIGHT;

      fMid = (left + right) / 2;
      fSide = (left - right) / 2;
    }
    else {
      fMid = DRIVE_FWD;
      fSide = DRIVE_ROT;
    }

    fMidFac = fabs(fMid) / 127;
    fSideFac = fabs(fSide) / 127;

    fSMid = fMid * (driveFacOffs + fMidFac * driveFacRange);
    fSSide = fSide * (driveFacOffs + fSideFac * driveFacRange);

    fMMid = fMid * (masterDriveFacOffs + fMidFac * masterDriveFacRange);
    fMSide = fSide * (masterDriveFacOffs + fSideFac * masterDriveFacRange);

	  sMid = (word)round(fSMid);
	  sSide = (word)round(fSSide);
	  mMid = (word)round(fMMid);
	  mSide = (word)round(fMSide);

    	motor[blWheel] =
	  	motor[flWheel] = arcadeLeft(sSide, sMid, flipLatch.out);
    motor[mlWheel] =
    	arcadeLeft(mSide, mMid, flipLatch.out);

    motor[brWheel] =
    	motor[frWheel] =
    	arcadeRight(sSide, sMid, flipLatch.out);
    motor[mrWheel] = arcadeRight(mSide, mMid, flipLatch.out);

    SensorValue[intakeLed] = flipLatch.out;
    SensorValue[flyLed] = !SensorValue[intakeLed];

    if (risingEdge(&flipDownLatch, DRIVE_FLIP_BTN)) {
      clearSounds();

      if (flipLatch.out) {
        playTone(3000, 10);
        playTone(2300, 10);
      }
      else {
        playTone(2300, 10);
        playTone(3000, 10);
      }
    }

    if (risingEdge(&flyLRLatch, FLY_LR_BTN) || risingEdge(&flyLRLatch2, FLY_LR_BTN_2))
      flyDir = 3;

    if (risingEdge(&flyMRLatch, FLY_MR_BTN) || risingEdge(&flyMRLatch2, FLY_MR_BTN_2))
      flyDir = 2;

    if (risingEdge(&flySRLatch, FLY_SR_BTN) || risingEdge(&flySRLatch2, FLY_SR_BTN_2))
      flyDir = 1;

    if (risingEdge(&flyOffLatch, FLY_OFF_BTN) || risingEdge(&flyOffLatch2, FLY_OFF_BTN_2))
      flyDir = 0;

    updateTbhController(&flyCtl, flyPwr[flyDir]);

    if (FIRE_BTN) motor[intake] = motor[lift] = 127;
    else {
   	  int feedInSpeed = (!flyTbh.isOnTgt && (SensorValue[leftLim] || SensorValue[rightLim])) ? 0 : 127;

      motor[intake] =
        twoWay(INTAKE_FEEDIN_BTN, 127, INTAKE_FEEDOUT_BTN, -127);
     	motor[lift] =
      	twoWay(LIFT_RAISE_BTN, feedInSpeed, LIFT_LOWER_BTN, -127);
   }

    if(risingEdge(&saveEncsLatch, SAVE_ENC_BTN) && saveEncs < SAVE_ENC_MAX) {
    	lDrive.encVals[saveEncs] = SensorValue[lDriveEnc];
    	rDrive.encVals[saveEncs] = SensorValue[rDriveEnc];
    	lDrive.deltaEnc[saveEncs] = (saveEncs > 0) ? (lDrive.encVals[saveEncs] - lDrive.encVals[saveEncs-1]) : 0;
    	rDrive.deltaEnc[saveEncs] = (saveEncs > 0) ? (rDrive.encVals[saveEncs] - rDrive.encVals[saveEncs-1]) : 0;
    	saveEncs++;
    }


    wait1Msec(25);
  }
}

void endUserOp() {
  stopCtls();
}
