

path = "/Users/likelian/Desktop/Audio_software/Output/";
%subpath = "sweep/";
subpath = "freesound/";
c_fir_filename = "fircomb_output.wav";
mat_fir_filename = "Mat_fircomb_output.wav";

c_iir_filename = "iircomb_output.wav";
mat_iir_filename = "Mat_iircomb_output.wav";

%test = "/Users/likelian/Desktop/Audio_software/Output/"+"sweep/";

[c_fir,Fs_c_fir] = audioread(path+subpath+c_fir_filename);
[mat_fir,Fs_mat_fir] = audioread(path+subpath+mat_fir_filename);

fir_compare = c_fir - mat_fir;


figure (1)
h = figure(1);
set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
plot(fir_compare(1));
saveas(gcf,path +'fir_left.png')

figure (2)
h = figure(2);
set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
plot(fir_compare(2));
saveas(gcf,path +'fir_right.png')


[c_iir,Fs_c_iir] = audioread(path+subpath+c_iir_filename);
[mat_iir,Fs_mat_iir] = audioread(path+subpath+mat_iir_filename);

iir_compare = c_iir - mat_iir;


figure (3)
h = figure(3);
set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
plot(iir_compare(1));
saveas(gcf,path +'iir_left.png')

figure (4)
h = figure(4);
set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
plot(iir_compare(2));
saveas(gcf,path +'iir_right.png')

