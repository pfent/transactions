---
output: 
  md_document:
    variant: markdown+pipe_tables
header-includes:
    - \usepackage{qtree}
    - \usepackage{tikz}
---
<!-- compile with: pandoc Exercise3.md -o Exercise3.pdf -->
# Exercises for *Transaction Systems*, Sheet No. 3
Philipp Fent
MatrNr: 03647020

## Exercise 1
To Prove:
$$
s \in CSR \iff (\forall T \subseteq trans(s)) \Pi_T(s) \in VSR
$$

* $(\Rightarrow)$: Prove that the membership in class CSR is monotone  
  In other words: If $h \not\in CSR$, then there is no suffix $i$ for $h$, such that the concatenation of both histories: $hi \in CSR$  
  From intuition: A history is not in CSR, if and only if the conflict graph has a circle. Since $h \subseteq hi$, the conflict graph of $h$ needs to be included in the conflict graph of $hi$, thus also $hi \not\in CSR$  
  Suppose $h \not\in CSR$, then we can find a circle in the corresponding conflict graph.  
  Assume, that we can find a suffix $i$, such that $hi \in CSR$.  
  Since $h$ is a prefix of $hi$, the conflicts $conf(h) \subseteq conf(hi)$.
  Since we can find a circle in the graph of $conf(h)$, and $conf(h) \subseteq conf(hi)$, we can also find a circle in the graph of $conf(hi)$. Thus $hi \not\in CSR$, so our assumption is wrong, which means CSR is monotone.
* Lemma: Let $s_1$ be a schedule with the set of transactions $T_1$.  
  And let $CG(s_1)$ have an edge $T_i \to T_j$ because of x,  
  and no other transaction writes $x$.  
  Then in any serial schedule that is view equivalent to $s_1$: $T_i < T_j$  
  Tho schedules $s$ and $s'$ are equivalent, iff $op(s) = op(s') \land RF(s) = RF(s')$  
  Prove by contradiction: Let the three statements from above and assume, there is a view equivalent serial schedule $s_2$ with $T_j < T_i$.  
  Since we have an edge in $CG(s_1)$, between $T_i \to T_j$ because of x, we can differenciate between the three possible conflicts:  
    1. $w_i(x) < r_j(x)$:  
    Then $(T_i, x, T_j) \in RF(s_1)$, "$T_j$ reads from $T_i".  
    This contradicts VSR equivalence, because $T_j < T_i \Rightarrow (T_i, x, T_j) \not\in RF(s_2)$, i.e. $RF(s_1) \neq RF(s_2)$
    2. $r_i(x) < w_j(x)$:  
    Then $(T_i, x, T_j) \not\in RF(s_1)$.  
    This contradicts VSR equivalence, because $op(s_1) = op(s_2)$ implies $(T_j, x, T_i) \in RF(s_2)$, i.e. $RF(s_1) \neq RF(s_2)$
    3. $w_i(x) < w_j(x)$:  
    Then $(T_j, x T_{\infty}) \in RF(s_1)$.  
    This contradicts VSR equivalence, because $op(s_1) = op(s_2)$ and no other transaction writes $x$, implies $(T_i, x, T_{\infty}) \in RF(s_2)$, i.e. $RF(s_1) \neq RF(s_2)$  
We exhausted all the cases, which prooves by contradiction: In any serial schedule that is view equivalent to $s_1$: $T_i < T_j$
* $(\Leftarrow)$: 


## Exercise 2
$$
s = w_1(x)\ r_2(y)\ r_1(x)\ c_1\ r_2(x)\ w_2(y)\ c_2
$$

Output for:

* 2PL  

| Step | $T_1$       | $T_2$       |
|-----:|:-----------:|:-----------:|
| 1    | $lockX(x)$  |             |
| 2    | $w_1(x)$    |             |
| 3    |             | $lockS(y)$  |
| 4    |             | $r_2(y)$    |
| 5    | $r_1(x)$    |             |
| 6    | $unlock(x)$ |             |
| 7    | $c_1$       |             |
| 8    |             | $lockS(x)$  |
| 9    |             | $r_2(x)$    |
| 10   |             | $lockX(y)$  |
| 11   |             | $unlock(x)$ |
| 12   |             | $w_2(y)$    |
| 13   |             | $unlock(y)$ |
| 14   |             | $c_2$       |

* S2PL (same as 2PL)

| Step | $T_1$       | $T_2$       |
|-----:|:-----------:|:-----------:|
| 1    | $lockX(x)$  |             |
| 2    | $w_1(x)$    |             |
| 3    |             | $lockS(y)$  |
| 4    |             | $r_2(y)$    |
| 5    | $r_1(x)$    |             |
| 6    | $unlock(x)$ |             |
| 7    | $c_1$       |             |
| 8    |             | $lockS(x)$  |
| 9    |             | $r_2(x)$    |
| 10   |             | $lockX(y)$  |
| 11   |             | $unlock(x)$ |
| 12   |             | $w_2(y)$    |
| 13   |             | $unlock(y)$ |
| 14   |             | $c_2$       |

* SS2PL (only step 12 and 13 changed)

| Step | $T_1$       | $T_2$       |
|-----:|:-----------:|:-----------:|
| 1    | $lockX(x)$  |             |
| 2    | $w_1(x)$    |             |
| 3    |             | $lockS(y)$  |
| 4    |             | $r_2(y)$    |
| 5    | $r_1(x)$    |             |
| 6    | $unlock(x)$ |             |
| 7    | $c_1$       |             |
| 8    |             | $lockS(x)$  |
| 9    |             | $r_2(x)$    |
| 10   |             | $lockX(y)$  |
| 11   |             | $w_2(y)$    |
| 12   |             | $unlock(x)$ |
| 13   |             | $unlock(y)$ |
| 14   |             | $c_2$       |
