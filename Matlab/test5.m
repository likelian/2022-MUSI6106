
ir =zeros(44100,1);
ir(1)=1; % unit impulse signal of length 100

audiowrite('/Users/likelian/Desktop/Audio_software/Input/IR.wav',ir,44100);

path = "/Users/likelian/Desktop/Audio_software/Output/";
[x,Fs] = audioread(path + "output.wav");
figure (1)
h = figure(1);
set(gcf,'PaperPositionMode','auto')
plot(x);
saveas(gcf,path +'ir.png')