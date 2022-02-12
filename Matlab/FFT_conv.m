fft_size = 16;
x_size = 8;
y_size = 256;
x = randn(1, x_size);
y = randn(1, y_size);

X = fft(x, fft_size);

conv_fft = zeros(1,x_size+y_size);
hop_size = fft_size - x_size;

for k = 0:y_size/hop_size - 1;
    start = k*hop_size+1
    ending = start+hop_size-1
    y_block = y(start:ending)
    xy_block = ifft(X.*fft(y_block,fft_size))
    new_xy_block = conv_fft(start:start+fft_size-1) + xy_block
    conv_fft(start:start+fft_size-1) = new_xy_block
end

conv_xy = conv(x, y)

MAE = mean(abs(conv_fft(1:end-1) - conv_xy))


