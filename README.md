# Assignment Of Processess To The Optimal Processor

In distributed computing, the problem of assigning a set of processes to a set of processors is complex. 

Consider we are running a program *P = {p1, ..., pn}* with *n* processes. We know the cost *Xi* of running each process *pi* on processor *X*, and the cost *Yi*, of running each process *pi* on processor *Yi*.

Consider, additionally, the communication cost *Cij* between processes *pi* e *pj* if *i* != *j*. There are no communication cost between two processes running on the same processor.

The given algorithm minimizes the total execution cost of program *P* by utilizing graphs and the Ford-Fulkerson algorithm.