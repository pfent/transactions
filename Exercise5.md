---
output: 
  md_document:
    variant: markdown+pipe_tables
---
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
Wait-die invariant: $t_i \to t_j \Rightarrow i < j$
Wound-wait invariant: $t_i \to t_j \Rightarrow j < i$

Step: $|WFG| = n + 1$  
The means, we have a subgraph $|WFG'| = n$, which is acyclic by the hypothesis and an additional edge $e$ on this graph.

Case **wait-die**: The hypothesis holds: $t_i \to t_j \Rightarrow i < j$. And we can differenciate on the direction of $e = t_k \to t_l$, i.e. $t_k$ was just blocked by $t_l$:  
If $t_k$ was started before $t_l$ ($k < l$). Which means the invariant still holds and the "waits for" relation is a partial order, thus cycle-free.  
If $t_l$ was started before $t_k$, the deadlock prevention strategy aborts $t_l$. This causes the edge to never be inserted and in the even smaller graph $WFG''$, the hypothesis still holds.

Case **wound-wait**: The hypothesis holds: $t_i \to t_j \Rightarrow j < i$. Again, we differenciate on the direction of $e = t_k \to t_l$:  
If $t_k$ was started before $t_l$, then the deadlock prevention algorithm aborts $t_l$ and in the resulting smaller waits for graph all invariants still hold.  
If $t_l$ was started before $t_k$, we can also partially order all transactions by the starting time, which means the graph is circle free and the invariant holds.


## Exercise 3 - O2PL schedules

$$
s_1\ =\ w_1(x)\ r_2(x)\ c_2\ r_3(y)\ c_3\ w_1(y)\ c_1
$$

| Step | $T_1$                      | $T_2$                       | $T_3$                      |
|-----:|:---------------------------|:----------------------------|:---------------------------|
| 1    | request $wl_1(x)$          |                             |                            |
| 2    | grant $wl_1(x)$            |                             |                            |
| 3    | $w_1(x)$                   |                             |                            |
| 4    |                            | request $r_2(x)$            |                            |
| 5    |                            | grant $r_2(x)$              |                            |
| 6    |                            | $r_2(x)$                    |                            |
| 7    |                            | attempt unlock $r_2(x)$     |                            |
| 8    |                            | *blocked*                   | request $r_3(y)$           |
| 9    |                            |                             | grant $r_3(y)$             |
| 10   |                            |                             | $r3(y)$                    |
| 11   |                            |                             | attempt unlock $r_3(y)$    |
| 12   |                            |                             | unlock $r_3(y)$            |
| 13   |                            |                             | $c_3$                      |
| 14   | request $wl_1(y)$          |                             |                            |
| 15   | grant $wl_1(y)$            |                             |                            |
| 16   | $w1(y)$                    |                             |                            |
| 17   | attempt unlock $wl_1(y)$   |                             |                            |
| 18   | unlock $wl_1(y)$           |                             |                            |
| 19   |                            | unlock $r_2(x)$             |                            |
| 20   |                            | $c_2$                       |                            |
| 21   | $c_1$                      |                             |                            |

$$
s_2\ =\ w_1(x)\ r_2(x)\ r_3(y)\ c_3\ r_2(z)\ c_2\ w_1(y)\ c_1
$$

| Step | $T_1$                      | $T_2$                       | $T_3$                      |
|-----:|:---------------------------|:----------------------------|:---------------------------|
| 1    | request $wl_1(x)$          |                             |                            |
| 2    | grant $wl_1(x)$            |                             |                            |
| 3    | $w1(x)$                    |                             |                            |
| 4    |                            | request $rl_2(x)$           |                            |
| 5    |                            | grant $rl_2(x)$             |                            |
| 6    |                            | $r_2(x)$                    |                            |
| 7    |                            |                             | request $rl_3(y)$          |
| 8    |                            |                             | grant $rl_3(y)$            |
| 9    |                            |                             | $r_3(y)$                   |
| 10   |                            |                             | attempt unlock $rl_3(y)$   |
| 11   |                            |                             | unlock $r_3(y)$            |
| 12   |                            |                             | $c_3$                      |
| 13   |                            | request $rl_2(z)$           |                            |
| 14   |                            | grant $rl_2(z)$             |                            |
| 15   |                            | $r_2(z)$                    |                            |
| 16   |                            | attempt unlock $rl_2(z)$    |                            |
| 17   |                            | attempt unlock $rl_2(x)$    |                            |
| 18   | request $wl_1(y)$          | *blocked*                   |                            |
| 19   | grant $wl_1(y)$            |                             |                            |
| 20   | $w_1(y)$                   |                             |                            |
| 21   | attempt unlock $wl_1(y)$   |                             |                            |
| 22   | unlock $wl_1(y)$           |                             |                            |
| 23   | attempt unlock $wl_1(x)$   |                             |                            |
| 24   | unlock $wl_1(x)$           |                             |                            |
| 25   |                            | unlock $rl_2(x)$            |                            |
| 26   |                            | unlock $rl_2(z)$            |                            |
| 27   |                            | $c_2$                       |                            |
| 28   | $c_1$                      |                             |                            |

## Exercise 4 - Example for a deadlock in O2PL

| Step | $T_1$                      | $T_2$                       |
|-----:|:---------------------------|:----------------------------|
| 1    | request $rl_1(x)$          |                             |
| 2    | grant $rl_1(x)$            |                             |
| 3    | $r_1(x)$                   |                             |
| 4    |                            | request $wl_2(x)$           |
| 5    |                            | grant $wl_2(x)$             |
| 6    |                            | $w_2(x)$                    |
| 7    |                            | request $wl_2(y)$           |
| 8    |                            | grant $wl_2(y)$             |
| 9    |                            | $w_2(y)$                    |
| 10   |                            | attempt unlock $wl_2(x)$    |
| 11   |                            | *blocked*                   |
| 12   | request $wl_1(y)$          |                             |
| 13   | *blocked*                  |                             |

The construction here is, that $T_2$ is order dependent on $T_1$, thus can not release any locks and is blocked. $T_1$ then requests an incompatible lock and is also blocked.
