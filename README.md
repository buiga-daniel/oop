# FREQUENCY ANALYSIS

We can frequency analysis to break Caesar’s cipher. This is a brute force method that tests all the possible displacements and returns the most likely decryption of a text.
Frequency analysis relies on the fact that some letters (or combination of letters ) occur more in a language, regardless of the text size. For example, in English the letters E, A are the most frequent, while the Z and Q are the least frequent


## Requirement
Write a function that reads the distribution of the letters from a file (distribution.txt) and stores it into an array. Write a function that breaks the Caesar’s cipher using frequency analysis: iteratively shifts the encrypted code through all the possible permutations, computes the Chi-square distance between each permutation and the approximate distribution of letters in English, and returns the permutation with the least Chi squared distance as the solution.

The idea of this method is to compare the frequency of the letters with  the Chi-Squared distance:
X(C, E) = Σ (Ci - Ei )^2 / Ei (with i going from 'a' to 'z') 
, where Ci represents the occurrence of the ith character, and Ei is the expected count of the ith character of the alphabet. 

The formula seems complicated at a first glance, but it is really not that complicated. Basically, for each possible character (i goes from ‘a’ to ‘z’), we measure the discrepancy between how often it appeared in the encrypted text (Ci ) and how often it is expected to appear in English texts ( Ei ); the difference Ci - Ei is squared such that we remove negative signs. The division by Ei is simply a normalization factor.

The lower the Chi-square distance 2 (C, E), the more similar the histograms C and E are. 
As this algorithm is a brute force method to break the cipher, you should compute the histogram for all possible shifts, and compute the Chi Squared distance between these histograms and the average distribution of the characters in English. The shift with the lowest Chi Squared distance is the solution.

Bibliography and indications:
 
[Using Chi squared to crack codes](https://ibmathsresources.com/2014/06/15/using-chi-squared-to-crack-codes/)

[Crypto Analysis to Crack Vigenere Ciphers](https://ibmathsresources.com/tag/vigenere-cipher/)

-Frequency of letters in the English language (going from 0 to 1 => 1 meaning 100% frequency in all words, 0.1 meaning 10% frequency in all words, 0.01 meaning 1% frequency in all words ):

'a' = 0.082; 'n' = 0.067;

'b' = 0.015; 'o' = 0.075;

'c' = 0.028; 'p' = 0.019;

'd' = 0.043; 'q' = 0.001;

'e' = 0.127; 'r' = 0.060;

'f' = 0.022; 's' = 0.063;

'g' = 0.020; 't' = 0.091;

'h' = 0.061; 'u' = 0.028;

'i' = 0.070; 'v' = 0.010;

'j' = 0.002; 'w' = 0.024;

'k' = 0.008; 'x' = 0.002;

'l' = 0.040; 'y' = 0.020;

'm' = 0.024; 'z' = 0.001 ;
