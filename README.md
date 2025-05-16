# Greedy Algorithms Divide and Conquer Algorithms

## Project Overview
This project simulates a matching algorithm for a fictional dating service called Maximal Electronic Dating Services (MEDS). Each client completes two surveys, and their results are stored as two real-number scores. The main goal of the project is to find the two clients who are most similar—or “closest”—based on those scores, using either a greedy or divide-and-conquer approach depending on the case.

## How It Works
The program takes two command line arguments:
- The name of an input file containing client data (e.g., clients.data).
- A mode indicator:
  - "1" – Find the closest pair based on the first survey score.
  - "2" – Find the closest pair based on the second survey score.
  - "b" – Find the closest pair using both scores, using Euclidean distance.

Each line in the input file looks like this:
```bash
Name Score1 Score2
```
Example:
```bash
Emily 2.7183 3.1415927
Jones 1.2 3.4
Steve 0.11 42
```
## Program Behavior & Output
- For mode "1" or "2", the program sorts the clients by the selected score and uses a linear scan to find the closest pair in O(n log n) time.
- For mode "b", the program calculates the Euclidean distance between each pair using:
```bash
√((p1 - q1)² + (p2 - q2)²)
```
Example command:
```bash
./main test.data b
```
Expected output:
```bash
Emily Jones 1.54013
```

## Performance Note
- Modes "1" and "2" are implemented efficiently and run in better than O(n²) time.
- However, the "b" mode currently uses a brute-force approach and does not meet the required performance constraints yet.
- I am still working on optimizing the "b" part to run in O(n log n) time using a divide-and-conquer algorithm.
