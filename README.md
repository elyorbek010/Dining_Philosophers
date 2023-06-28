# Dining_Philosophers
Number of philosophers can be configured in philosophers.h
Number of meals philosophers should consumer before finishing can be configured in philosophers.h

<pre>
         philosopher 1       philosopher 2      philosopher 3 ...  
silverware 1       silverware 2        silverware 3              ...

</pre>

## Problem:  
There are N philosophers and N silverware
Each philosopher needs 2 silverware around him to consume meal  
But if a philosopher takes first silverware, and at the same time
another philosopher takes the second silverware,   
then both philosophers can not consume their meal because they are waiting for each other's
shared silverware

## Solution:  
Philosophers at even location(starting from 0) should first take
silverware on their right, whereas philosophers at odd location 
should first take silverware on their left  
In this case, at least each second philosopher can consume their meal

## RESULT:  
<pre>
Philosopher 0: _____RLEEEEE_____R_____RL_____RLEEEEE_____R_____RLEEEEE_____R_____RL_____RLEEEEE_____RL_____R_____RLEEEEE
Philosopher 1: _____LR_____L_____LREEEEE_____L_____LREEEEE_____LR_____L_____LREEEEE_____L_____LREEEEE_____L_____LR_____LREEEEE
Philosopher 2: _____R_____RLEEEEE_____R_____RLEEEEE_____R_____RL_____RLEEEEE_____R_____RLEEEEE_____R_____RLEEEEE
Philosopher 3: _____L_____L_____LREEEEE_____LR_____L_____LREEEEE_____L_____LREEEEE_____LREEEEE_____L_____LR_____LREEEEE
Philosopher 4: _____RL_____RLEEEEE_____R_____RL_____RLEEEEE_____R_____RLEEEEE_____R_____RL_____R_____RLEEEEE_____RL_____R_____RLEEEEE
</pre>
