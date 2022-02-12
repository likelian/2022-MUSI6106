


yzeros = zeros(1, 44100);

audiowrite('/Users/likelian/Desktop/Audio_software/Input/zeros.wav',yzeros,44100);

path = "/Users/likelian/Desktop/Audio_software/Output/";
[x,Fs] = audioread(path + "output.wav");
figure (1)
h = figure(1);
set(gcf,'PaperPositionMode','auto')
plot(x);
saveas(gcf,path +'zeros.png')