# Introduction
<b>--- 27-07-2026 20:32 MONDAY ---</b>
<br/><br/>
1. One Pole LPF from scratch. No AI.
1. 20.33 -> Try to go into absolute depth and take a week to solve it. Next Monday review. Before Leh.
1. 20.41 -> So, the electrons that start out in full energy and then slowly dissipiate.. the one who decays more is filtered out. The one who couldn't bear the resistor. 
    1. Which is why a low pass filter always needs some sort of a resistance first.
    1. But for the high pass, it's the opposite. You're only allowed to pass if your source... what does a capacitor do to electrons?
        1. OKay so it just stops the electrons and traps it by pulling it away from the source.
    1. So, for a high pass, the electron which has the .. can an electron with high energy cross a capacitor?
        1. No, it can't.
    1. <b>TODO: Revisit this</b> ![](./01.png)
1. 20.42 ->
    1. what does a capacitor do to electrons?
    1. [1](https://ocw.mit.edu/courses/res-6-008-digital-signal-processing-spring-2011/video_galleries/video-lectures/)
    1. [2](https://phys.libretexts.org/Special:Search?qid=&fpid=230&fpth=&query=one+pole+low+pass&type=wiki)
    1. [3](https://www.dspguide.com/ch19/2.htm)
    1. [4](https://dsp.stackexchange.com/questions/54086/single-pole-iir-low-pass-filter-which-is-the-correct-formula-for-the-decay-coe)
    1. [5](https://www.youtube.com/watch?v=ftk9C45F_bo)
    1. [6](https://www.reddit.com/r/synthesizers/comments/ba75tl/what_are_poles_in_filters/)
    1. [7](https://www.youtube.com/watch?v=Sq0mQFwYTIk&t=49s)
    1. [9](https://www.youtube.com/watch?v=oHKwwvcn77Y)
    1. does reistance cause higfh energy electrons to stop
    1. [10](https://www.youtube.com/watch?v=oztGhZF11uo)
    1. [11](https://www.youtube.com/watch?v=I8_E1ppC3-Q&t=35s)
    1. is one pole low pass filter an IIR
    1. how is one pole low pass filter and iir
    1. what is an iir filter
        1. [12](https://in.mathworks.com/help/signal/ug/iir-filter-design.html)
    1. how does a one pole low pass filter work
        1. [13](https://www.embeddedrelated.com/showarticle/779.php)
1. 20.59 -> Filter Low Pass, only pass low frequncies, how do i get frequency from the buffer? 
    1. works with individual oscillators but what about noise or just being passed a buffer?
    1. Should explore this when done with theory.
    1. 21.02 -> No, this.
1. 21.09 -> Goal is: Filter low frequency ![](02.jpg)
    1. need to have cutoff frequency
1. 21.23 -> Need to find relationship between amplitude and frequency.
    1. More amplitude may imply a higher energy sample.. so it can kind of relate to my freuqncy. Higher frequency sounds louder?
        1. But is loudness dependent on frequency?
            1. Google says yes. 21.30 -> Let's assume this first and go with it. Later come back to this.
            1. 21.31 -> Fletcher-Munson curve
        1. So let's assume that loudness is equal to frequency in a way.. then I need to:
            1. Figure out the mathematical relationship between frequency and amplitude
                1. 21.26 -> Figure out the mathematical relationship between frequency and amplitude
                    1. 21.28 -> The only thing I will have is a buffer and the sample rate. Figure out according to that.
                            1. ![](03.jpg)
                        1. 21.36 -> what is x?
                            1. 21.42 -> TOMORROW
                            1. 21.43 -> Till 10PM.
                            1. 21.46 -> ``` SR = F * buffer.size() ``` !!! ![](04.jpg)
                    1. 21.48 -> So, id SR = F * buffer.size()
                        1. 21.50 -> but i can have a wave of 10000s and the buffer size would be quite high despite SR being 44100 and F being 441
                            1. So, the equation is wrong
                                1. PROJECT_IDEA: Git repo inside another git repo
                        1. 21.57 -> But duration can also be included here in the equation!
                            1. 22.03 -> TOMORROW ![](05.jpg)
            1. Figure out how to actually filter once the relationship is derived
<br/><br/>            
<b>--- 28-07-2026 11:23 TUESDAY ---</b>
<br/><br/>
1. First of all ```buffer.size()``` is simply ```SR * DURATION```.. the approach itself was wrong.
1. Keep it simple. Create a naive filter.
    1. Imagine a filter knob that can be used. Knob goes from 0 to 1.
    1. ```Filtered value = (1 - KNOB_VALUE) * sample[i] ``` That's it!
    1. Then figure out how to make it low pass or high pass. Right now it just cuts things off.
    1. 11.32 -> Should filter give only the value that should be subtracted or should it filter and give it?
        1. Let it give the filtered value
1. 11.55 -> The thing to realize is that I have actually created a gain control.
1. 12.16 -> If frequency is a rate, a single sample cannot give me the information for a filter.
    1. I need to take multiple samples into consideration.
    1. The variables I have:
        1. cutoff_frequency -> of the filter
        1. buffer samples -> double values holding amplitude
        1. sample_rate -> of the recording/audio buffer
    1. if cutoff_frequency is a knob and i have multiple samples, what can i do to manipulate output?
        1. and what about sample rate?
1. 13.06 -> 
    1. I know that sample_rate/Fc will give me the number of samples in a cycle
    1. That number is how many samples from the buffer i should take into consideration
    1. but then what do i do with these samples?
        1. if averages can be taken into consideration then how is an average doing the work of the filter?
    1. also, calculating average everytime is costly.. 
        1. so to make it efficient, i can just store the previous output and then take the current sampple in and come up with a formula.
    1. the main question is: how is averaging something filtering stuff out? and how is it a low pass and not a high pass? and after all this, what exactly is a one pole low pass filter? I understand filters.. but what about this?
1. 15.47 -> Summing rewards agreement between samples and punishes disagreement — slow signals agree, fast signals cancel.
1. 20.47 -> 
    1. filter needs to filter out frequencies
    1. this means filter can only work on relationship between two samples
    1. with the summing principle (mentioned at 15.47), i need to add the last output to the current input
    1. agreement is what slow samples have - which means that a low pass filter allows low frequencies to pass through.. and low freq means low rate of change
    1. i need to blend the current input with the past
    1. the factor with which blending is done is the knob
    1. knob is in Hz.. blending is a unitless process
        1. i need to find cycles per sample.... that gives me an idea of "freq"
        1. so Fc/SR is the ratio
    1. 21.01 -> Think again
        1. if agreement is what slow samples have..
            1. that means i need to find a relationship between the last sample and this sample
            1. which means that i am BLENDING the last sample and this sample
            1. which is why it is a low pass filter because i am summing things up and trying to maintain the "stickiness" in samples
            1. if it was a high pass filter, i would do the opposite.. try to remove the "stickiness".. which means subtraction
            1. anyways..
        1. so, the idea of a low pass filter is locked in.. make samples agree and blend them
        1. so what is the blending mechanism?
            1. i know that i have a sample rate and a cutoff frequency
            1. cutoff frequency - how many cycles go through in one second, sample rate - how many samples are in one second
            1. why am i taking these 2 into consideration?
                1. i need to take a fraction of the input sample so that it comes UNDER the cutoff frequency
                    1. so, that becomes ```some_fraction * x[i]```
                    1. so, my output right now is ``` y[i] = some_fraction * x[i]  => y[i] = (1 - K) * x[i]```
                1. now, what is this K? and the cutoff freq + sample rate relation with this K?
        1. 21.13 -> blending means 2 components
            1. but why 2? and if 2 - then what to take into consideration?
                1. let's start with what to take into consideration?
                    1. either last sample or something else altogether?
                        1. LAST SAMPLE:
                            1. PROS: 
                                1. i have some sort of an idea of what was there previously
                            1. CONS:
                                1. are 2 samples enough to verify a change? maybe the no. of samples in a cycle (```SR/Fc```) ACTUALLY help in understanding the freq content?
                    1. this means that the "something else altogether" is a history of the cycle?
                        1. if so, then maybe an average makes sense? what else?
                            1. let's say i take the average
                                1. then that means that i need to store each and every sample
                                1. then take the average
                                1. then add it to my input
                                1. then equation becomes: ```y[i] = (((x[i-1] + x[i-2]...) / SR) * FC)*(1 - K) + K * x[i]```
                                1. but when i go to the next sample, i discard the LAST sample from the average calculation for the previous input.. which means i have shifted by 1
                                1. but do i really care about the shift? why not just hold the last output?
                                    1. what is the last output made of? y[i-1] = ??
                                        1. it's equal to ????
1. 21.35 -> okay, used some AI here
    1. recalculating average of samples every time is:
        1. costly
        1. harsher cutoff
    1. if i just store the previous output and bring that into the mix for the next input
        1. less costly
        1. smoother cutoff
    1. now, how do we relate to the constants that we have - SR, Fc and then what exactly is K? 
        1. this is the only thing left; then my equation is simply: ```y[i] = (1 - K) * y[i-1] + K * x[i]```
<b>--- 29-07-2026 15:57 WEDNESDAY ---</b>
<br/><br/>        
1. should one pole lpf class store the sample rate?
    1. i could just store the constant only and accept the sample rate and cutoff frequency in the constructor
    1. thinking of the filter as a knob.... knob controls cutoff frequency.. sample rate is a fixed decision to be taken by the developer
1. 16.22 -> Testing with alpha = 0
    1. No change
    1. With alpha = 0.5, I can hear the harshness reduce.. so the filter is working
1. 16.30 -> Now, to find out the actual value of alpha and how it relates with the sample rate and cutoff frequency
## C++ Findings