path = "/Users/likelian/Desktop/Audio_software/Output/";
[x,Fs] = audioread(path + "output.wav");
figure (1)
h = figure(1);
set(gcf,'PaperPositionMode','auto')
plot(x);
%saveas(gcf,path +'512.png')
%saveas(gcf,path +'1024.png')
%saveas(gcf,path +'2048.png')
saveas(gcf,path +'4096.png')