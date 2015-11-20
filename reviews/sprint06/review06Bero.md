## Sprint 6 Hours - Christopher Bero

Class | Week
----- | ----
CPE 495 | 9 Nov. 2015 -- 13 Nov. 2015

### Sprint Stories

* Get set up with microcontroller hardware and begin circuit designs for sliding keyboard.

### Task Notes

The MSP430F5529 Experimenter Board comes with a pretty capable demo where the device presents itself as mass storage, and then reads the files you copy to it. I can't seem to find the source to this firmware on Ti's website..

There are a few ways to do the switch wiring. I'm currently in favor of the standard "charlieplexing" row scanning approach. With switches wired into a grid, we should be able to receive input from them with only 8 data lines (4 outputs, 4 inputs).

<br><br><br><br><br><br>
<br><br><br><br><br><br>

---

Signed: 
