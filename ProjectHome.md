## Version 1.5.5 Released! ##

<a href='http://www.youtube.com/watch?feature=player_embedded&v=Aoip3pK91Rw' target='_blank'><img src='http://img.youtube.com/vi/Aoip3pK91Rw/0.jpg' width='720' height=480 /></a>

~ Fixed [issue #2](https://code.google.com/p/paping/issues/detail?id=#2) - Missing DLL: MSVCP100D.dll

~ Fixed [issue #4](https://code.google.com/p/paping/issues/detail?id=#4) - Incorrectly Reported all ports on LocalHost as open

~ Fixed [issue #5](https://code.google.com/p/paping/issues/detail?id=#5) - Return codes not being set

## Can you help? ##

**UDP**
I realize that testing UDP ports is not reliable but it would be nice to add the feature - Know how?  Please help the project (papingproject@gmail.com).

**Translation**
Can you help translate the strings used, if so please check out the Wiki article 'Translation' for a list.

## Command line options ##
```
paping v1.5.1 - Copyright (c) 2010 Mike Lovell

Connecting to www.l.google.com [209.85.225.147] on TCP 80:

Connected to 209.85.225.147: time=24.00ms protocol=TCP port=80
Connected to 209.85.225.147: time=25.00ms protocol=TCP port=80
Connected to 209.85.225.147: time=24.00ms protocol=TCP port=80
Connected to 209.85.225.147: time=24.00ms protocol=TCP port=80

Connection statistics:
        Attempted = 4, Connected = 4, Failed = 0 (0.00%)
Approximate connection times:
        Minimum = 24.00ms, Maximum = 25.00ms, Average = 24.25ms
```

## Example usage ##

```
C:\> paping www.google.com -p 80 -c 4

paping v1.5.1 - Copyright (c) 2010 Mike Lovell

Connecting to www.l.google.com [209.85.225.147] on TCP 80:

Connected to 209.85.225.147: time=24.00ms protocol=TCP port=80
Connected to 209.85.225.147: time=25.00ms protocol=TCP port=80
Connected to 209.85.225.147: time=24.00ms protocol=TCP port=80
Connected to 209.85.225.147: time=24.00ms protocol=TCP port=80

Connection statistics:
        Attempted = 4, Connected = 4, Failed = 0 (0.00%)
Approximate connection times:
        Minimum = 24.00ms, Maximum = 25.00ms, Average = 24.25ms
```