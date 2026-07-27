# Introduction
<b>--- 27-07-2026 07:33 MONDAY ---</b>
<br/><br/>
1. A mixer will hold an array of buffers and each buffer will have their own gain parameter.
1. 07.41 -> Logic is pretty easy. Iterate through the inputs, add each input (after it's multiplied with their gains)
    1. TODO: Validation is important here
    1. TODO: There should be some way to clamp the output between -1,1. Not sure if I should add it as an option in the mixer or assume the user will handle it everytime.
## C++ Findings
1. Declaring ```mixed``` inside or outside the loop makes no difference performance wise for modern compilers
    1. Helps prevent bugs in case ```mixed = 0.0``` is not writtern after every iteration
1. Prefer using ```++i``` for iteration.
    1. ```++i``` increments and returns the updated value.
    1. ```i++``` returns the old value before incrementing, which may require an extra copy for iterators and user-defined types.