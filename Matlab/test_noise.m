


yNoise = Amp * rand(1, 44100);

audiowrite('/Users/likelian/Desktop/Audio_software/Input/noise.wav',yNoise,44100);

path = "/Users/likelian/Desktop/Audio_software/Output/";
[x,Fs] = audioread(path + "output.wav");

s = spectrogram(x);

spectrogram(x,'yaxis')

figure (1)
h = figure(1);
set(gcf,'PaperPositionMode','auto')
%plot(s);
saveas(gcf,path +'sine_iircomb.png')