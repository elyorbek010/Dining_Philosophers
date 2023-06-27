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
But if each philosopher take first silverware, and at the same time
another philosopher takes second silverware, then both philosophers
can not consume their meal because they are waiting for each other's
shared silverware

## Solution:  
Philosophers at even location(starting from 0) should first take
silverware on their right, whereas philosophers at odd location 
should first take silverware on their left
In this case, at least each second philosopher can consume their meal

## RESULT:  
<pre>
Philosopher 0: ____RLEEEEEE_______RL_____R_________RLEEEE____RLEEEEEEEEE
Philosopher 1: _______L____LREEEEEEEEE_____L____L___LR___L_______LR_____L____LREEEEEEE_____LREEEEEEE
Philosopher 2: _____RLEEEEE________R______RLEEEEEEEE_____RL________RLEEEE
Philosopher 3: ________LR______LREEEEE________L________LREEEEE______LR______LREEEEE
Philosopher 4: ____RL______RLEEE____R___RLEEEEEEEE________R___RL_____RL________R_______RLEEEEEEEEE
</pre>
