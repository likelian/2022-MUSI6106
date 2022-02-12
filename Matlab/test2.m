
%generated sine at 
f=100;
Amp=1.;
ts=1/44100;
T=1;
t=0:ts:T;
y=Amp*sin(2*pi*f*t);
%plot(t,y)


audiowrite('/Users/likelian/Desktop/Audio_software/Input/sine.wav',y,44100);

path = "/Users/likelian/Desktop/Audio_software/Output/";
[x,Fs] = audioread(path + "output.wav");
figure (1)
h = figure(1);
set(gcf,'PaperPositionMode','auto')
plot(x);
saveas(gcf,path +'sine_iircomb.png')
