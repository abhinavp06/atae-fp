<b>--- 01-08-2026 09:07 SUNDAY ---</b>
<br/><br/>
1. Basic ADSR envelope.
1. I already know the concept.
    1. Start -> Go up on a ramp -> Go down after peak -> hold for a while -> fade out
1. Why is the ramp linear?
    1. TODO: Deep dive into this.
    1. For now, move on with a linear ADSR.
1.09.28 -> 
    1. Lifecycle ->
        1. User presses a note -> noteOn() triggered
        2. Ramps up to 1.0 then decays and sustains
        3. User then stops pressing the key -> noteOff() triggered
        4. noteOff() is the actual release trigger.. if not called sustain indefinitely?
    1. Experiment with this and try to find out bugs
<br/><br/>
<b>--- 13-08-2026 06:43 THURSDAY ---</b>
<br/><br/>
1. Decay must have a factor of sustain as well.. it has to reach the sustain level which means it needs to decrement the difference in a set amount of samples