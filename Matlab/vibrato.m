
input_path = "../Input/";

file = "sweep";
%file = "freesound";
filename = file + ".wav";

[x,Fs] = audioread(input_path + filename);

Modfreq = 10.;
Width = 0.1;

output = vibrato_func(x,Fs,Modfreq,Width);
output_path = "../Output/Matlab/";
audiowrite(output_path+filename, output, Fs);


matlab_output_path = "../Output/Matlab/";
[mat_output,Fs] = audioread(matlab_output_path + filename);

c_output_path = "../Output/C++/";
[c_output,Fs] = audioread(c_output_path + filename);



compare = c_output - mat_output;

plot_path = "../Plots/";
figure (1)
h = figure(1);
set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
plot(compare(:,1));
saveas(gcf,plot_path + file + '_left.png')

figure (2)
h = figure(2);
set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
plot(compare(:,2));
saveas(gcf, plot_path + file +'_right.png')


downmix = sum(compare, 2);
figure (3)
h = figure(3);
set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
plot(downmix);
saveas(gcf, plot_path + file +'_downmix.png')


function y=vibrato_func(x,SAMPLERATE,Modfreq,Width)
% Author: S. Disch
%
%--------------------------------------------------------------------------
% This source code is provided without any warranties as published in 
% DAFX book 2nd edition, copyright Wiley & Sons 2011, available at 
% http://www.dafx.de. It may be used for educational purposes and not 
% for commercial applications without further permission.
%--------------------------------------------------------------------------

ya_alt=0;
Delay=Width; % basic delay of input sample in sec
DELAY=round(Delay*SAMPLERATE); % basic delay in # samples
WIDTH=round(Width*SAMPLERATE); % modulation width in # samples
if WIDTH>DELAY 
  error('delay greater than basic delay !!!');
  return;
end
MODFREQ=Modfreq/SAMPLERATE; % modulation frequency in # samples
LEN=length(x);        % # of samples in WAV-file
L=2+DELAY+WIDTH*2;    % length of the entire delay  
Delayline=zeros(L,1); % memory allocation for delay
y=zeros(size(x));     % memory allocation for output vector
for n=1:(LEN-1)
   M=MODFREQ;
   MOD=sin(M*2*pi*n);
   TAP=1+DELAY+WIDTH*MOD;
   i=floor(TAP);
   frac=TAP-i;
   Delayline=[x(n);Delayline(1:L-1)]; 
   %---Linear Interpolation-----------------------------
   y(n,1)=Delayline(i+1)*frac+Delayline(i)*(1-frac);
end
end