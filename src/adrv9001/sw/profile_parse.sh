#!/bin/bash

inDir=$1
outDir=$2

echo "Input Directory: $1"
echo "output Directory: $2"

cp -r $inDir/initialize*.c $outDir
cp -r $inDir/initialize*.h $outDir
cp -r $inDir/calibrate*.c $outDir
cp -r $inDir/calibrate*.h $outDir
cp -r $inDir/configure*.c $outDir
cp -r $inDir/configure*.h $outDir
cp -r $inDir/prime*.c $outDir
cp -r $inDir/prime*.h $outDir

sed -i '/printf/d' $outDir/*.c
sed -i '/getchar/d' $outDir/*.c  
sed -i 's/int initialize(adi_adrv9001_Device_t * adrv9001Device_0.*/int initialize(adi_adrv9001_Device_t * adrv9001Device_0)/g' $outDir/*  
sed -i '/#include "adi_fpga9001/d' $outDir/* 
sed -i '/error_code = adi_fpga9001/d' $outDir/*   
sed -i '/linux_uio_init/d' $outDir/*   
sed -i 's/adi_adrv9001_Init_t initialize_init_7/adrv9001_params_t Adrv9001Params/g' $outDir/*  
#sed -i 's/initialize_init_7/Adrv9001Params/g' $outDir/*
sed -i '1i #include "adrv9001.h"' $outDir/initialize*
sed -i '1i #include "adrv9001.h"' $outDir/configure*
sed -i 's/, adi_fpga9001_Device_t \* fpga9001Device_0//g' $outDir/*    
sed -i 's/\}\;/,/g' $outDir/initializeinit7.c  
echo '  .Lo1Carrier = {' >> $outDir/initializeinit7.c  
grep -m 1 'adi_adrv9001_Carrier_t' $outDir/initialize.c -A 4 | tail -n4 >> $outDir/initializeinit7.c  
echo '  .Lo2Carrier = {' >> $outDir/initializeinit7.c  
grep -m 2 'adi_adrv9001_Carrier_t' $outDir/initialize.c -A 4 | tail -n4 >> $outDir/initializeinit7.c   
echo '  .Tx1Attn = 10000,' >> $outDir/initializeinit7.c  
echo '  .Tx2Attn = 10000,' >> $outDir/initializeinit7.c  
echo '  .Tx1Boost = 0,' >> $outDir/initializeinit7.c  
echo '  .Tx2Boost = 0,' >> $outDir/initializeinit7.c  
echo '  .Tx1TestModeData = 0xA234ABC1,' >> $outDir/initializeinit7.c
echo '  .Tx2TestModeData = 0xA234ABC1,' >> $outDir/initializeinit7.c
echo '  .Rx1TestModeData = 0xA234ABC1,' >> $outDir/initializeinit7.c
echo '  .Rx2TestModeData = 0xA234ABC1,' >> $outDir/initializeinit7.c
echo '  .Tx1SsiEnableDly = 500,' >> $outDir/initializeinit7.c
echo '  .Tx2SsiEnableDly = 500,' >> $outDir/initializeinit7.c
echo '  .Rx1SsiEnableDly = 500,' >> $outDir/initializeinit7.c
echo '  .Rx2SsiEnableDly = 500,' >> $outDir/initializeinit7.c
echo '  .Tx1DisableDly = 200,' >> $outDir/initializeinit7.c
echo '  .Tx2DisableDly = 200,' >> $outDir/initializeinit7.c  
echo '  .Rx1SsiDisableDly = 200,' >> $outDir/initializeinit7.c
echo '  .Rx2SsiDisableDly = 200,' >> $outDir/initializeinit7.c
echo '  .Tx1EnableMode = 1,' >> $outDir/initializeinit7.c
echo '  .Tx2EnableMode = 1,' >> $outDir/initializeinit7.c
echo '  .Rx1EnableMode = 1,' >> $outDir/initializeinit7.c
echo '  .Rx2EnableMode = 1,' >> $outDir/initializeinit7.c

rm -rf tmp.txt
grep 'adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_1,' $outDir/initialize.c >> tmp.txt || true
sed -i 's/error_code = adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_1,/.Tx1ExternalPathDelay = /g' tmp.txt || true
sed -i 's/)\;/,/g' tmp.txt || true
grep '.Tx1ExternalPathDelay' tmp.txt >> $outDir/initializeinit7.c || true

rm -rf tmp.txt
grep 'adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_2,' $outDir/initialize.c >> tmp.txt || true
sed -i 's/error_code = adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_2,/.Tx2ExternalPathDelay = /g' tmp.txt || true 
sed -i 's/)\;/,/g' tmp.txt || true    
grep '.Tx2ExternalPathDelay' tmp.txt >> $outDir/initializeinit7.c || true     

rm -rf tmp.txt     
echo '.Rx1Agc = {' >> tmp.txt
grep -m 1 'adi_adrv9001_GainControlCfg_t' $outDir/configureagcCfg* -A 66 | tail -n66 >> tmp.txt || true
sed -i 's/}\;/ /g' tmp.txt
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c 
 
rm -rf tmp.txt    
echo '.Rx2Agc = {' >> tmp.txt
grep -m 2 'adi_adrv9001_GainControlCfg_t' $outDir/configureagcCfg* -A 66 | tail -n66 >> tmp.txt || true
sed -i 's/}\;/ /g' tmp.txt   
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c    

rm -rf tmp.txt
echo '  .Tx1DpdInitCfg = {' >> tmp.txt 
grep -m 1 'adi_adrv9001_DpdInitCfg_t' $outDir/initialize.c -A 8 | tail -n8 >> tmp.txt 
sed -i 's/}\;/ /g' tmp.txt     
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c  

rm -rf tmp.txt
echo '  .Tx2DpdInitCfg = {' >> tmp.txt   
grep -m 2 'adi_adrv9001_DpdInitCfg_t' $outDir/initialize.c -A 8 | tail -n8 >> tmp.txt   
sed -i 's/}\;/ /g' tmp.txt    
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c  

rm -rf tmp.txt  
echo '  .Tx1DpdCfg = {' >> tmp.txt
grep -m 1 'adi_adrv9001_DpdCfg_t' $outDir/configure.c -A 19 | tail -n19 >> tmp.txt   
sed -i 's/}\;/ /g' tmp.txt    
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c  

rm -rf tmp.txt  
echo '  .Tx2DpdCfg = {' >> tmp.txt 
grep -m 2 'adi_adrv9001_DpdCfg_t' $outDir/configure.c -A 19 | tail -n19 >> tmp.txt  
sed -i 's/}\;/ /g' tmp.txt   
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c   
 
rm -rf tmp.txt  
echo '  .Rx1InterfaceGain = {' >> tmp.txt  
grep -m 1 'adi_adrv9001_RxInterfaceGainCtrl_t' $outDir/configure.c -A 8 | tail -n8 >> tmp.txt  
sed -i 's/}\;/ /g' tmp.txt    
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c    

rm -rf tmp.txt  
echo '  .Rx2InterfaceGain = {' >> tmp.txt 
grep -m 2 'adi_adrv9001_RxInterfaceGainCtrl_t' $outDir/configure.c -A 8 | tail -n8 >> tmp.txt  
sed -i 's/}\;/ /g' tmp.txt    
echo '},' >> tmp.txt  
cat tmp.txt >> $outDir/initializeinit7.c    

sed -i 's/\;/,/g' $outDir/initializeinit7.c
echo '};' >> $outDir/initializeinit7.c    

sed -i -e '/adi_fpga9001_SsiCalibrationCfg_t/,+8d' $outDir/initialize.c      
sed -i -e '/adi_fpga9001_ClockStatus_t/,+5d' $outDir/initialize.c        
sed -i -e '/adi_fpga9001_Version_t/,+3d' $outDir/initialize.c  
sed -i -e '/adi_adrv9001_Carrier_t/,+4d' $outDir/initialize.c
sed -i -e '/adi_adrv9001_DpdInitCfg_t/,+8d' $outDir/initialize.c  
sed -i 's/\&initialize_init_7/(adi_adrv9001_Init_t*)\&Adrv9001Params/g' $outDir/initialize.c    
sed -i 's/adi_adrv9001_Tx_OutputPowerBoost_Set(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_Tx_OutputPowerBoost_Set(adrv9001Device_0, ADI_CHANNEL_1, Adrv9001Params.Tx1Boost);/g' $outDir/initialize.c  
sed -i 's/adi_adrv9001_Tx_OutputPowerBoost_Set(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_Tx_OutputPowerBoost_Set(adrv9001Device_0, ADI_CHANNEL_2, Adrv9001Params.Tx2Boost);/g' $outDir/initialize.c  
sed -i 's/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_1, \&Adrv9001Params.Tx1Attn);/g' $outDir/initialize.c 
sed -i 's/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_2, \&Adrv9001Params.Tx2Attn);/g' $outDir/initialize.c       
sed -i 's/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_1, .*/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_1, \&Adrv9001Params.Lo1Carrier);/g' $outDir/initialize.c  
sed -i 's/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_2, .*/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_TX, ADI_CHANNEL_2, \&Adrv9001Params.Lo2Carrier);/g' $outDir/initialize.c 
sed -i 's/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_1, .*/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_1, \&Adrv9001Params.Lo1Carrier);/g' $outDir/initialize.c 
sed -i 's/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_2, .*/adi_adrv9001_Radio_Carrier_Configure(adrv9001Device_0, ADI_RX, ADI_CHANNEL_2, \&Adrv9001Params.Lo2Carrier);/g' $outDir/initialize.c 
sed -i 's/adi_adrv9001_dpd_Initial_Configure(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_dpd_Initial_Configure(adrv9001Device_0, ADI_CHANNEL_1, \&Adrv9001Params.Tx1DpdInitCfg);/g' $outDir/initialize.c 
sed -i 's/adi_adrv9001_dpd_Initial_Configure(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_dpd_Initial_Configure(adrv9001Device_0, ADI_CHANNEL_2, \&Adrv9001Params.Tx2DpdInitCfg);/g' $outDir/initialize.c 	  
sed -i 's/adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_1, \Adrv9001Params.Tx1ExternalPathDelay);/g' $outDir/initialize.c      
sed -i 's/adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_cals_ExternalPathDelay_Set(adrv9001Device_0, ADI_CHANNEL_2, \Adrv9001Params.Tx2ExternalPathDelay);/g' $outDir/initialize.c
rm -rf $outDir/configureagcCfg* || true	

sed -i -e '/adi_adrv9001_DpdCfg_t/,+19d' $outDir/configure.c  
sed -i -e '/adi_adrv9001_RxInterfaceGainCtrl_t/,+8d' $outDir/configure.c    
sed -i 's/adi_adrv9001_Rx_GainControl_Configure(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_Rx_GainControl_Configure(adrv9001Device_0, ADI_CHANNEL_1, \&Adrv9001Params.Rx1Agc);/g' $outDir/configure.c 
sed -i 's/adi_adrv9001_Rx_GainControl_Configure(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_Rx_GainControl_Configure(adrv9001Device_0, ADI_CHANNEL_2, \&Adrv9001Params.Rx2Agc);/g' $outDir/configure.c 
sed -i 's/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_1, Adrv9001Params.Tx1Attn);/g' $outDir/configure.c 
sed -i 's/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_Tx_Attenuation_Set(adrv9001Device_0, ADI_CHANNEL_2, Adrv9001Params.Tx2Attn);/g' $outDir/configure.c    
sed -i 's/adi_adrv9001_dpd_Configure(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_dpd_Configure(adrv9001Device_0, ADI_CHANNEL_1, \&Adrv9001Params.Tx1DpdCfg);/g' $outDir/configure.c 
sed -i 's/adi_adrv9001_dpd_Configure(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_dpd_Configure(adrv9001Device_0, ADI_CHANNEL_2, \&Adrv9001Params.Tx2DpdCfg);/g' $outDir/configure.c      
sed -i 's/adi_adrv9001_Rx_InterfaceGain_Configure(adrv9001Device_0, ADI_CHANNEL_1, .*/adi_adrv9001_Rx_InterfaceGain_Configure(adrv9001Device_0, ADI_CHANNEL_1, \&Adrv9001Params.Rx1InterfaceGain);/g' $outDir/configure.c 
sed -i 's/adi_adrv9001_Rx_InterfaceGain_Configure(adrv9001Device_0, ADI_CHANNEL_2, .*/adi_adrv9001_Rx_InterfaceGain_Configure(adrv9001Device_0, ADI_CHANNEL_2, \&Adrv9001Params.Rx2InterfaceGain);/g' $outDir/configure.c      
       