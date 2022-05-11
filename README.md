In this respostory, we give an example on how to do initilization step for MT-DPI on one word with s=2.

The initialization steps in MT-DPI contain two parts:
1. Triple generatioin between S and MB for all AND gates that will be evaluated.
2. Circuit evaluation for generating handles and certification.


In the first phase, the triple generation can be implmented using Ferrot-ROT. You can refer xxx and Appendix A of our paper for the implementation.

We mainly show how the second phase can work. The details are shown in the code.
