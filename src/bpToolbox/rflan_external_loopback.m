%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Externally connect transmit and receiver ports together using a coaxial
% cable.  The maximum input power at the receive port should not exceed 
% -20dBm.  If using the HDK SMA ports don't exceed -40dBm at the input of
% HDK SMA port.  This can be done using a combination of attenuators or
% by increasing the transmitter attenuation.  
%
% This script will load the transmiter DMA stream buffer and begin
% transmitting. This is followed by a receiver DMA stream enable and 
% several receiver DMA buffer reads.  Each produces a spectral plot of the 
% received buffer.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all; close all; clc;

h = rflan();
h.Open('COM16');

TxPort = h.Tx2;
RxPort = h.Rx2;
RxBufLength = 4096;

% Set Tx Output Power
h.SetTxAttn(TxPort, 20);
h.SetTxBoost(TxPort, 0);

% Load Transmit buffer with IQ data from file on SD card
h.RflanStreamBufLoad(TxPort,'CFR_sample_rate_61p44M_bw_20M.csv');
%h.RflanStreamBufLoad(TxPort,'sample_rate_24K_Tone_3K.csv');

% Enable continuous transmit stream
h.RflanStreamStart(TxPort, 1, RxBufLength);

% Read Carrier Frequency
fc = h.GetCarrierFrequency(RxPort);
fs = h.GetSampleRate(RxPort);

figure();
for i = 1:20    
    
% Start DMA Burst
h.RflanStreamStart(RxPort, 0, RxBufLength);

% Read DMA Buffer
iq = h.RflanStreamBufGet(RxPort,0,RxBufLength);

bins = length(iq)/2; 
h2 = spectrum.welch('Hamming',bins);
spec = msspectrum(h2,iq,...
        'Fs',fs,...
        'SpectrumType','twosided',...
        'CenterDC',true);    
    
f = spec.Frequencies/1e6 + fc/1e6;
a = 10*log10(spec.Data);    

plot(f,a);
title([RxPort ' Spectrum ']);
xlabel('Frequency(MHz)');
ylabel('Power (dBm)');

end

h.RflanStreamStop(RxPort);
h.RflanStreamStop(TxPort);

