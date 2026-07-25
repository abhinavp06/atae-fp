# Introduction
<b>--- 25-07-2026 10:59 SATURDAY ---</b>
<br/><br/>
Lately, while working on my "audio-tools-and-effects" library and learning about Audio DSP with Claude, I realised I was moving too fast. I have created this repository to slow down and relearn everything again. Use Google, documentations, etc.
<br/><br/>
I'll start with a basic oscillator and keep a Log file for each branch I create. It will help me document my true learnings which I can refer to later and maybe even help someone else.
<br/><br/>

# Ideas
## Idea 1 --- 25-07-2026 11:02 ---
Create a simple script which produces values which mimic a sine wave. The script should write values to a CSV file. 
<br/><br/>
<b>X -></b> time (assume 44100 values in 1 second)
<br/>
<b>Y -></b> amplitude (keeps shifting between -1 and +1)
### TODO
1. Create a function which generates a sine wave and the returns an array with values ranging from -1 to +1.
2. Create a function which accepts an array of double values and assigns it to the Y column. Generation of X values to happen in the function itself based on the sample count. This function also writes to a .csv file.