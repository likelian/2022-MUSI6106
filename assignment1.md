

I use XCode argument inputs, not exactly command line. It should be the same. I will do testing differently next time. What is the best practice for testing that's easy to review?

Matlab's input and output paths have to be changed. Sorry.

I have plots from my own testing in assignment1_test.md. I thought that's the only requirement for the assignment.


For Real-World Example:

run fircomb_test.m

/Users/likelian/Desktop/Audio_software/Input/freesound.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

/Users/likelian/Desktop/Audio_software/Input/sweep.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run fircomb_test.m


run iircomb_test.m

/Users/likelian/Desktop/Audio_software/Input/freesound.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

/Users/likelian/Desktop/Audio_software/Input/sweep.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run iircomb_test.m



test1: FIR: Output is zero if input freq matches feedforward

fircomb_test

#run matlab test1.m (change audiowrite to freesoud.wav)

/Users/likelian/Desktop/Audio_software/Input/sine.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test1

#run matlab test1 (change audiowrite to sweep.wav)

/Users/likelian/Desktop/Audio_software/Input/sine.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test1


test2: IIR: amount of magnitude increase/decrease if input freq matches feedback


#run matlab test2 (change audiowrite to freesoud.wav)

/Users/likelian/Desktop/Audio_software/Input/sine.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter IIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test2


#run matlab test2 (change audiowrite to sweep.wav)

/Users/likelian/Desktop/Audio_software/Input/sine.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 512 Filter IIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test2


test3: FIR/IIR: correct result for VARYING input block size

/Users/likelian/Desktop/Audio_software/Input/sine.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 1024 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test1

/Users/likelian/Desktop/Audio_software/Input/sine.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 2048 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test1

....


test4: FIR/IIR: correct processing for zero input signal

run matlab test4

/Users/likelian/Desktop/Audio_software/Input/zeros.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 2048 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test4


/Users/likelian/Desktop/Audio_software/Input/zeros.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 2048 Filter IIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test4


test5: IR, One more additional MEANINGFUL test

run matlab test5

/Users/likelian/Desktop/Audio_software/Input/IR.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 2048 Filter FIR Gain 0.5 Delay 0.005 Max_delay 1

run matlab test5

/Users/likelian/Desktop/Audio_software/Input/IR.wav /Users/likelian/Desktop/Audio_software/Output output.wav  BlockSize 2048 Filter IIR Gain 0.5 Delay 0.005 Max_delay 1






![iircomb_left_compare_swwep](/Output/sweep/iir_left.png)
iircomb_left_compare_swwep

![iircomb_right_compare_swwep](/Output/sweep/iir_right.png)
iircomb_right_compare_swwep

![fircomb_left_compare_swwep](/Output/sweep/fir_left.png)
fircomb_left_compare_swwep

![fircomb_right_compare_swwep](/Output/sweep/fir_right.png)
fircomb_right_compare_swwep



![iircomb_left_compare_freesound](/Output/freesound/iir_left.png)
iircomb_left_compare_freesound

![iircomb_right_compare_freesound](/Output/freesound/iir_right.png)
iircomb_right_compare_freesound

![fircomb_left_compare_freesound](/Output/freesound/fir_left.png)
fircomb_left_compare_freesound

![fircomb_right_compare_freesound](/Output/freesound/fir_right.png)
fircomb_right_compare_freesound
