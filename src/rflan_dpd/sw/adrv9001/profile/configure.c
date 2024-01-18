#include "adrv9001.h"
/* This file contains code automatically generated by a machine. */
/* It has not been independently verified by any human. */
/* The generation process is deterministic and tested (not generative AI), */
/* but not every scenario or risk has been captured in unit tests. */
/* All code is provided as-is for example purposes only. */
/* The customer assumes all risks related to the use of this code. */


/* */
/* Silicon Revision: Presumed C0*/
/* */
/* Tx / Rx optimal carrier frequencies: 30 MHz to 6 GHz*/
/* External LO optimal frequencies: 60 MHz to 12 GHz*/
/* */
/* FPGA: v0.0.0*/
/* Device Driver API: v0.0.0*/
/* Device Driver Client: v68.10.1*/
/* Firmware: v0.22.27*/
/* Profile Generator: v0.53.2.0*/
/* Stream Generator Assembly: v0.7.10.0*/
/* Transceiver Evaluation Software: v0.25.0*/
/* ADRV9001 Plugin: v0.25.0*/

#include "configure.h"

int configure(adi_adrv9001_Device_t * adrv9001Device_0)
{
	int32_t error_code = 0;


	uint32_t gpIntMask_1 = 0;
	error_code = adi_adrv9001_gpio_GpIntMask_Get(adrv9001Device_0, &gpIntMask_1);


	error_code = adi_adrv9001_gpio_GpIntMask_Set(adrv9001Device_0, 16);

	error_code = adi_adrv9001_Tx_AttenuationMode_Set(adrv9001Device_0, ADI_CHANNEL_2, ADI_ADRV9001_TX_ATTENUATION_CONTROL_MODE_SPI);

	error_code = adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_2, 10000);

	adi_adrv9001_PowerSavingAndMonitorMode_ChannelPowerSavingCfg_t powerSavingCfg_5 = { 
		.channelDisabledPowerDownMode = ADI_ADRV9001_POWERSAVINGANDMONITORMODE_CHANNEL_MODE_DISABLED, 
		.gpioPinPowerDownMode = ADI_ADRV9001_POWERSAVINGANDMONITORMODE_CHANNEL_MODE_DISABLED };
	error_code = adi_adrv9001_powerSavingAndMonitorMode_ChannelPowerSaving_Configure(adrv9001Device_0, ADI_CHANNEL_2, &powerSavingCfg_5);

	adi_adrv9001_ChannelEnablementDelays_t delays_6 = { 
		.riseToOnDelay = 1475, 
		.riseToAnalogOnDelay = 0, 
		.fallToOffDelay = 418, 
		.guardDelay = 0, 
		.holdDelay = 0 };
	error_code = adi_adrv9001_Radio_ChannelEnablementDelays_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_2, &delays_6);

	error_code = adi_adrv9010_bbdc_LoopGain_Set(adrv9001Device_0, ADI_CHANNEL_2, 65536);

	adi_adrv9001_TrackingCals_t trackingCals_8 = { 
		.chanTrackingCalMask = { (adi_adrv9001_TrackingCalibrations_e) 0, ADI_ADRV9001_TRACKING_CAL_TX_QEC | ADI_ADRV9001_TRACKING_CAL_TX_LO_LEAKAGE | ADI_ADRV9001_TRACKING_CAL_TX_DPD_CLGC | ADI_ADRV9001_TRACKING_CAL_RX_BBDC | ADI_ADRV9001_TRACKING_CAL_RX_RFDC | ADI_ADRV9001_TRACKING_CAL_RX_QEC_FIC  } };
	error_code = adi_adrv9001_cals_Tracking_Set(adrv9001Device_0, &trackingCals_8);

	adi_adrv9001_DpdCfg_t dpdConfig_9 = { 
		.numberOfSamples = 4096, 
		.additionalPowerScale = 4, 
		.rxTxNormalizationLowerThreshold = 33954698, 
		.rxTxNormalizationUpperThreshold = 269711752, 
		.detectionPowerThreshold = 53942350, 
		.detectionPeakThreshold = 214748365, 
		.countsLessThanPowerThreshold = 4096, 
		.countsGreaterThanPeakThreshold = 0, 
		.immediateLutSwitching = true, 
		.useSpecialFrame = false, 
		.resetLuts = false, 
		.timeFilterCoefficient = 0, 
		.dpdSamplingRate_Hz = 0, 
		.clgcLoopOpen = 0, 
		.clgcGainTarget_HundredthdB = 0, 
		.clgcFilterAlpha = 1610612736, 
		.clgcLastGain_HundredthdB = 0, 
		.clgcFilteredGain_HundredthdB = 0, 
		.captureDelay_us = 0, 
		.enableRepeatedEstimationInTDD = false };
	error_code = adi_adrv9001_dpd_Configure(adrv9001Device_0, ADI_CHANNEL_2, &dpdConfig_9);


	return error_code;
}
