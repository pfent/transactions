<!-- compile with: pandoc Exercise5.md -o Exercise5.pdf -->
# Exercises for *Transaction Systems*, Sheet No. 5
Philipp Fent  
MatrNr: 03647020

## Exercise 1 - 2PL starvation

The starvation problematic is very dependent on the deadlock resolution algorithm / strategy. 
In this example, we take a look at the "youngest" strategy, as defined in the lecture. I.e. abort the youngest transaction in the cycle.

\begin{align*}
t_1: wl(1), wl(2), wl(3), wl(4), wl(5), c\\
t_2: wl(5), wl(4), wl(3), wl(2), wl(1), c
\end{align*}

example schedule: 
\begin{align*}
s = &wl_1(1), wl_2(5), wl_2(4), wl_2(3), wl_2(2), wl_2(1), wl_1(2), a_2,\\
    &wl_2(5), wl_2(4), wl_2(3), wl_2(2), wl_1(3), a_2,\\
    &wl_2(5), wl_2(4), wl_2(3), wl_1(4), a_2,\\
    &wl_2(5), wl_2(4), wl_1(5), a_2\\
    &...
\end{align*}

The schedule can be extended for arbitrary length by using more locks, which create more aborts of $t_2$

How could we extend 2PL in order to avoid this starvation?  
We usually use a deadlock prevention mechanism, as discussed in the next exercises.  
One way to prevent this situation on the 2PL scheduler level, would be to sort the locks, only allowing the same locking order in each transaction.

## Exercise 2 - Deadlock Prevention Proof

Show that the wait-die and wound-wait approaches to deadlock prevention both guarantee an acyclic WFG at any point in time

From intuition: The wait-die and wound-wait approaches both impose a waiting order on the transactions, where either younger transactions wait for older ones or the other way round.

Proof by structural induction on the sedges of the waiting graph $WFG$, denoted as $|WFG|$:

Base Case: $|WFG| = 0$:  
Since we have no edges, the graph is trivially acyclic. And the wait-die / wound-wait invariants are satisfied.

Hypothesis: $|WFG| = n$ is acyclic. And:  
Case wait-die: $t_i \to t_j \Rightarrow i < j$
Case wound-wait: $t_i \to t_j \Rightarrow j < i$

Step: $|WFG| = n + 1$  
The means, we have a subgraph $|WFG'| = n$, which is acyclic by the assumption and an additional edge $e$ on this graph.  

