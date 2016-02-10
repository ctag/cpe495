## Progress Report 12

Class | Week
----- | ----
CPE 496 | 3 Feb. 2016 -- 9 Feb. 2016

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

We have finished development plans for our second keyboard prototype. It is currently being constructed.

Work on our desktop application is ongoing.

### Difficulties Encountered

<!---
Difficulties Encountered is required. Other teams report losing points if this is missing.
Put here any trouble we had while accomplishing work during the previous sprint/week.
-->

We upgraded from a 30W to 100W chemical laser bed and have had huge difficulties working with the control software. DXF if the preferred format for migrating an SVG model to the laser, but DXF files exported by Inkscape fail to be processed. We're working on an export format such as PLT or HPGL, but both crash a python script in Inkscape when invoked.

*Update Feb. 9*

We're closing in on a working method for designing and cutting files with the 100W laser bed. SVG files are exported as EPS, which is run through a script based on the `pstoedit` command line utility. This results in a useable DXF file which the laser computer recognizes. We're still investigating this approach, but it appears that color masks and layering works correctly.

### Next Sprint

<!---
Next Sprint should be a list of tasks that each member is going to work towards for the upcomming week.
Make sure to email members on Thursday or Friday so that they can respond with their most recent progress.
-->

* Christopher Bero:
    * Build braille keyboard.
* Michael Baldwin:
    * Continue work on predictive text application.
* John Gould:
    * Mediate testing and integration for hardware and software testing.
* Bryant Johnson:
    * Polyfill between hardware and software as support.



