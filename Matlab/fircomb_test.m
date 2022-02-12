% Authors: P. Dutilleux, U Zölzer
%
%--------------------------------------------------------------------------
% This source code is provided without any warranties as published in 
% DAFX book 2nd edition, copyright Wiley & Sons 2011, available at 
% http://www.dafx.de. It may be used for educational purposes and not 
% for commercial applications without further permission.
%--------------------------------------------------------------------------


[x,Fs] = audioread('/Users/likelian/Desktop/Audio_software/Input/freesound.wav');


%x=zeros(100,1);x(1)=1; % unit impulse signal of length 100
delayInSeconds = 0.01;
delayInSamples = 0.01*44100;
g=0.5;
Delayline=zeros(delayInSamples,2);% memory allocation for length 10
y=zeros(length(x),2);
for n=1:length(x);
	y(n,1)=x(n,1)+g*Delayline(delayInSamples,1);
    y(n,2)=x(n,2)+g*Delayline(delayInSamples,2);
	Delayline(:,1)=[x(n,1);Delayline(1:delayInSamples-1,1)];
    Delayline(:,2)=[x(n,2);Delayline(1:delayInSamples-1,2)];
end;

audiowrite('/Users/likelian/Desktop/Audio_software/Output/Mat_fircomb_output.wav',y,Fs)