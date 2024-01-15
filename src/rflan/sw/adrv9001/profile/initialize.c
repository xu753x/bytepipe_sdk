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

#include "initialize.h"

int initialize(adi_adrv9001_Device_t * adrv9001Device_0)
{
	int32_t error_code = 0;

	adi_common_ApiVersion_t apiVersion_0 = { 
		.major = 0, 
		.minor = 0, 
		.patch = 0 };
	error_code = adi_adrv9001_ApiVersion_Get(adrv9001Device_0, &apiVersion_0);






	error_code = adi_adrv9001_HwClose(adrv9001Device_0);

	adi_adrv9001_SpiSettings_t spiSettings_5 = { 
		.msbFirst = 1, 
		.enSpiStreaming = 0, 
		.autoIncAddrUp = 1, 
		.fourWireMode = 1, 
		.cmosPadDrvStrength = ADI_ADRV9001_CMOSPAD_DRV_STRONG };
	error_code = adi_adrv9001_HwOpen(adrv9001Device_0, &spiSettings_5);

	error_code = adi_adrv9001_HwReset(adrv9001Device_0);

	error_code = adi_adrv9001_InitAnalog(adrv9001Device_0, &initialize_init_7, ADI_ADRV9001_DEVICECLOCKDIVISOR_2);

	error_code = adi_adrv9001_arm_AhbSpiBridge_Enable(adrv9001Device_0);

	error_code = adi_adrv9001_Stream_Image_Write(adrv9001Device_0, 0, initialize_binary_9, 32768, ADI_ADRV9001_ARM_SINGLE_SPI_WRITE_MODE_STANDARD_BYTES_252);

	error_code = adi_adrv9001_arm_Image_Write(adrv9001Device_0, 0, initialize_binary_10, 310272, ADI_ADRV9001_ARM_SINGLE_SPI_WRITE_MODE_STANDARD_BYTES_252);

	error_code = adi_adrv9001_arm_Profile_Write(adrv9001Device_0, &initialize_init_7);

	error_code = adi_adrv9001_arm_PfirProfiles_Write(adrv9001Device_0, &initialize_init_7);

	adi_adrv9001_RxLnaConfig_t lnaConfig_13 = { 
		.externalLnaPresent = false, 
		.gpioSourceSel = ADI_ADRV9001_GPIO_ANALOG_PIN_NIBBLE_UNASSIGNED, 
		.externalLnaPinSel = ADI_ADRV9001_EXTERNAL_LNA_PIN_RX1_LOWER_RX2_UPPER, 
		.settlingDelay = 0, 
		.numberLnaGainSteps = 0, 
		.lnaGainSteps_mdB = { 0, 0, 0, 0  }, 
		.lnaDigitalGainDelay = 0, 
		.minGainIndex = 0, 
		.lnaType = ADI_ADRV9001_EXTERNAL_LNA_TYPE_SINGLE };
	error_code = adi_adrv9001_Rx_GainTable_Write(adrv9001Device_0, ADI_ORX, ADI_CHANNEL_1, 14, initialize_gainTableRows_13, 13, &lnaConfig_13, ADI_ADRV9001_RX_GAIN_CORRECTION_TABLE);

	error_code = adi_adrv9001_Rx_GainTable_Write(adrv9001Device_0, ADI_ORX, ADI_CHANNEL_2, 14, initialize_gainTableRows_14, 13, &lnaConfig_13, ADI_ADRV9001_RX_GAIN_CORRECTION_TABLE);

	error_code = adi_adrv9001_Rx_GainTable_Write(adrv9001Device_0, ADI_RX, ADI_CHANNEL_1, 255, initialize_gainTableRows_15, 69, &lnaConfig_13, ADI_ADRV9001_RX_GAIN_CORRECTION_TABLE);

	error_code = adi_adrv9001_Rx_GainTable_Write(adrv9001Device_0, ADI_RX, ADI_CHANNEL_2, 255, initialize_gainTableRows_16, 69, &lnaConfig_13, ADI_ADRV9001_RX_GAIN_CORRECTION_TABLE);

	error_code = adi_adrv9001_Tx_AttenuationTable_Write(adrv9001Device_0, 3, 0, initialize_attenTableRows_17, 960);

	adi_adrv9001_PowerManagementSettings_t powerManagementSettings_18 = { 
		.ldoPowerSavingModes = { ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1, ADI_ADRV9001_LDO_POWER_SAVING_MODE_1  } };
	error_code = adi_adrv9001_powermanagement_Configure(adrv9001Device_0, &powerManagementSettings_18);

	error_code = adi_adrv9001_arm_Start(adrv9001Device_0);

	error_code = adi_adrv9001_arm_StartStatus_Check(adrv9001Device_0, 5000000);


	error_code = adi_adrv9001_Tx_OutputPowerBoost_Set(adrv9001Device_0, ADI_CHANNEL_1, false);

	error_code = adi_adrv9001_Tx_OutputPowerBoost_Set(adrv9001Device_0, ADI_CHANNEL_2, false);

	adi_adrv9001_SsiCalibrationCfg_t ssiCalibration_24 = { 
		.rxClkDelay = { 0, 0  }, 
		.rxStrobeDelay = { 0, 0  }, 
		.rxIDataDelay = { 0, 0  }, 
		.rxQDataDelay = { 0, 0  }, 
		.txClkDelay = { 0, 0  }, 
		.txRefClkDelay = { 0, 0  }, 
		.txStrobeDelay = { 0, 0  }, 
		.txIDataDelay = { 0, 0  }, 
		.txQDataDelay = { 0, 0  } };
	error_code = adi_adrv9001_Ssi_Delay_Configure(adrv9001Device_0, ADI_ADRV9001_SSI_TYPE_LVDS, &ssiCalibration_24);

	error_code = adi_adrv9001_gpio_ControlInit_Configure(adrv9001Device_0, &initialize_gpioCtrlInitCfg_25);

	adi_adrv9001_PllLoopFilterCfg_t pllLoopFilterConfig_26 = { 
		.effectiveLoopBandwidth_kHz = 0, 
		.loopBandwidth_kHz = 300, 
		.phaseMargin_degrees = 60, 
		.powerScale = 5 };
	error_code = adi_adrv9001_Radio_PllLoopFilter_Set(adrv9001Device_0, ADI_ADRV9001_PLL_LO1, &pllLoopFilterConfig_26);

	error_code = adi_adrv9001_Radio_PllLoopFilter_Set(adrv9001Device_0, ADI_ADRV9001_PLL_LO2, &pllLoopFilterConfig_26);

	error_code = adi_adrv9001_Radio_PllLoopFilter_Set(adrv9001Device_0, ADI_ADRV9001_PLL_AUX, &pllLoopFilterConfig_26);

	adi_adrv9001_PowerSavingAndMonitorMode_MonitorModeRssiCfg_t monitorModeRssiCfg_29 = { 
		.numberOfMeasurementsToAverage = 4, 
		.measurementsStartPeriod_ms = 1, 
		.detectionThreshold_mdBFS = -80000, 
		.measurementDuration_samples = 10 };
	error_code = adi_adrv9001_powerSavingAndMonitorMode_MonitorMode_Rssi_Configure(adrv9001Device_0, &monitorModeRssiCfg_29);

	adi_adrv9001_PowerSavingAndMonitorMode_MonitorModeDmrSearchCfg_t dmrSearchCfg_30 = { 
		.pathDelay = 0, 
		.magcorrTh = 250, 
		.detCnt1 = 375, 
		.detCnt2 = 500, 
		.detTgtMin = 880000 };
	error_code = adi_adrv9001_powerSavingAndMonitorMode_MonitorMode_DmrSearch_Configure(adrv9001Device_0, &dmrSearchCfg_30);

	adi_adrv9001_RxPortSwitchCfg_t switchConfig_31 = { 
		.minFreqPortA_Hz = 890000000, 
		.maxFreqPortA_Hz = 910000000, 
		.minFreqPortB_Hz = 1890000000, 
		.maxFreqPortB_Hz = 1910000000, 
		.enable = false, 
		.manualRxPortSwitch = false };
	error_code = adi_adrv9001_Rx_PortSwitch_Configure(adrv9001Device_0, &switchConfig_31);

	adi_adrv9001_Carrier_t carrier_32 = { 
		.loGenOptimization = ADI_ADRV9001_LO_GEN_OPTIMIZATION_POWER_CONSUMPTION, 
		.carrierFrequency_Hz = 2400000000, 
		.intermediateFrequency_Hz = 0, 
		.manualRxport = ADI_ADRV9001_RX_A };
	error_code = adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_1, &carrier_32);

	adi_adrv9001_ChannelEnablementDelays_t delays_33 = { 
		.riseToOnDelay = 0, 
		.riseToAnalogOnDelay = 0, 
		.fallToOffDelay = 0, 
		.guardDelay = 0, 
		.holdDelay = 0 };
	error_code = adi_adrv9001_Radio_ChannelEnablementDelays_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_1, &delays_33);

	error_code = adi_adrv9001_Rx_AdcSwitchEnable_Set(adrv9001Device_0, ADI_CHANNEL_1, false);

	error_code = adi_adrv9001_Ssi_PowerDown_Set(adrv9001Device_0, ADI_RX, ADI_CHANNEL_1, ADI_ADRV9001_SSI_POWER_DOWN_DISABLED);

	adi_adrv9001_Carrier_t carrier_36 = { 
		.loGenOptimization = ADI_ADRV9001_LO_GEN_OPTIMIZATION_PHASE_NOISE, 
		.carrierFrequency_Hz = 900000000, 
		.intermediateFrequency_Hz = 0, 
		.manualRxport = ADI_ADRV9001_RX_A };
	error_code = adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_2, &carrier_36);

	error_code = adi_adrv9001_Radio_ChannelEnablementDelays_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_2, &delays_33);

	error_code = adi_adrv9001_Rx_AdcSwitchEnable_Set(adrv9001Device_0, ADI_CHANNEL_2, false);

	error_code = adi_adrv9001_Ssi_PowerDown_Set(adrv9001Device_0, ADI_RX, ADI_CHANNEL_2, ADI_ADRV9001_SSI_POWER_DOWN_DISABLED);

	error_code = adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_1, &carrier_32);

	error_code = adi_adrv9001_Radio_ChannelEnablementDelays_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_1, &delays_33);

	error_code = adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_1, 0);

	error_code = adi_adrv9001_Ssi_PowerDown_Set(adrv9001Device_0, ADI_TX, ADI_CHANNEL_1, ADI_ADRV9001_SSI_POWER_DOWN_DISABLED);

	adi_adrv9001_SlewRateLimiterCfg_t config_44 = { 
		.srlEnable = false, 
		.srlStatisticsEnable = false, 
		.srlTableSelect = ADI_ADRV9001_SRL_TABLE0, 
		.srlSlewOffset = 0, 
		.srlStatisticsMode = ADI_ADRV9001_SRL_STATISTICS_MIN_SLEW_FACTOR_OBSERVED };
	error_code = adi_adrv9001_Tx_SlewRateLimiter_Configure(adrv9001Device_0, ADI_CHANNEL_1, &config_44);

	error_code = adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_2, &carrier_36);

	error_code = adi_adrv9001_Radio_ChannelEnablementDelays_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_2, &delays_33);

	error_code = adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_2, 0);

	error_code = adi_adrv9001_Ssi_PowerDown_Set(adrv9001Device_0, ADI_TX, ADI_CHANNEL_2, ADI_ADRV9001_SSI_POWER_DOWN_DISABLED);

	error_code = adi_adrv9001_Tx_SlewRateLimiter_Configure(adrv9001Device_0, ADI_CHANNEL_2, &config_44);

	adi_adrv9001_PllConfig_t pllConfig_50 = { 
		.pllCalibration = ADI_ADRV9001_PLL_CALIBRATION_NORMAL, 
		.pllPower = ADI_ADRV9001_PLL_POWER_LOW };
	error_code = adi_adrv9001_Radio_Pll_Configure(adrv9001Device_0, ADI_ADRV9001_PLL_LO1, &pllConfig_50);

	error_code = adi_adrv9001_Radio_Pll_Configure(adrv9001Device_0, ADI_ADRV9001_PLL_LO2, &pllConfig_50);

	adi_adrv9001_McsDelay_t mcsDelay_52 = { 
		.readDelay = 1, 
		.sampleDelay = 0 };
	error_code = adi_adrv9001_Mcs_ChannelMcsDelay_Set(adrv9001Device_0, ADI_RX, ADI_CHANNEL_1, &mcsDelay_52);

	adi_adrv9001_McsDelay_t mcsDelay_53 = { 
		.readDelay = 5, 
		.sampleDelay = 0 };
	error_code = adi_adrv9001_Mcs_ChannelMcsDelay_Set(adrv9001Device_0, ADI_TX, ADI_CHANNEL_1, &mcsDelay_53);

	error_code = adi_adrv9001_Mcs_ChannelMcsDelay_Set(adrv9001Device_0, ADI_RX, ADI_CHANNEL_2, &mcsDelay_52);

	error_code = adi_adrv9001_Mcs_ChannelMcsDelay_Set(adrv9001Device_0, ADI_TX, ADI_CHANNEL_2, &mcsDelay_53);

	error_code = adi_adrv9001_arm_System_Program(adrv9001Device_0, 15);






	return error_code;
}
