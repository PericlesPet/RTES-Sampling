# RTES-Sampling
Given a time period t, sample every dt seconds and sleep in between.

## Running


### WITH TIMESTAMPS

from main directory

```shell
cd with\ Timestamps/
make
timestampsWith 7200 0.1 desired_filename
```


### WITHOUT TIMESTAMPS

from main directory

```
cd without\ Timestamps/
make
timestampsWithout 7200 0.1 desired_filename
```



## GETTING STATISTICS

from main directory

run timestampStats.m with **matlab** (octave doesn't work because tables have not yet been implemented in Octave)

the results are now in the *Results* directory


