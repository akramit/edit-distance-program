# Edit Distance or Levenshtein distance

## Description
We write the program to print the entire Dynamic Programming Table for edit distance problem along with the alignment of the characters.
The table contains the following information.
* Given a string X and a string Y, ED(i,j) in the grid denotes the minimum edit distance between the strings X[1,..,i] and Y[1,..,j].  
* The value of the cell ED(i,j) is of the format "{L,B,D}+val" (e.g. L25, D14 etc.) where L represents when min ED(i,j) was obtained from left, and bottom, diagonal for B and D respectively. The 'val' is the min edit distance at cell (i,j).

Note: ED[0][0] is lower left cell and ED[m][n] is upper right cell.

## Installation
None required. Just compile CPP program and execute the output. 

## Example of an execution
```
String X: 
brambara
String Y: 
barbara
B7   L6   L5   L4   L4   D4   L4   L3   D2   
B6   L5   L4   L3   D3   B4   L3   D2   B3   
B5   L4   L3   D2   B3   L3   D2   B3   B4   
B4   L3   L2   D2   B3   D2   B3   B4   B5   
B3   L2   D1   B2   D2   B3   B4   D4   B5   
B2   L1   D1   D1   B2   B3   B4   B5   B6   
B1   D0   B1   B2   B3   B4   B5   B6   B7   
L0   L1   L2   L3   L4   L5   L6   L7   L8  
```
