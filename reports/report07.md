## Progress Report 7

Class | Week
----- | ----
CPE 495 | 16 Nov. 2015 -- 20 Nov. 2015

### Adaptive H.I.D.

<!--- This is a comment
Make sure to use *asterisks* to create italics on the member of whoever created the report
-->

* *Christopher Bero*
* Bryant Johnson
* John Gould
* Michael Baldwin

### Project Status
<!---
Project Status is a review of what was accomplished last week and a description of where we stand going into this sprint. A comparison between goals and actual accomplishments is a good idea.
-->

We've completed another hardware purchase order for prototyping materials (PCB and breadboard) and 3.5mm mono audio equipment to match the standards discussed with our customer. 

We have an initial MSP-USB firmware demo and are working on the SPI tools to upload it to our experimenter board. 

We are still looking for project maintainers to contact for our software research.

### Difficulties Encountered

<!---
Difficulties Encountered is required. Other teams report losing points if this is missing.
Put here any trouble we had while accomplishing work during the previous sprint/week.
-->

The MSP430F5529 Experimenter Board has an on-PCB MSP430F2258 that's used for SPI and real time debugging. This chip is also the only way to flash new firmware to the F5529, making the upload process more complicated when using raw firmware rather than Energia sketches. We're pursuing a fix by flashing firmware with a modified version of avrdude.

### Next Sprint

<!---
Next Sprint should be a list of tasks that each member is going to work towards for the upcomming week.
Make sure to email members on Thursday or Friday so that they can respond with their most recent progress.
-->

* Christopher Bero:
    * Flash USB firmware demo to MSP430F5529.
    * Create 12-switch prototype circuit.
* Michael Baldwin:
    * Continuation of sprint 7.
* John Gould: Task
* Bryant Johnson: Task



