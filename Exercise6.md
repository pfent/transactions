---
output: 
  md_document:
    variant: markdown+pipe_tables
header-includes:
    \usepackage{graphicx}
---
<!-- compile with: pandoc Exercise6.md -o Exercise6.pdf -->
# Exercises for *Transaction Systems*, Sheet No. 6
Philipp Fent  
MatrNr: 03647020

## Exercise 1 - Gen(BTO) vs. Gen(2PL)

BTO permits some schedules, which 2PL does not. For example:

\begin{align*}
s_1 = w_1(x), r_2(x), c_1, c_2\\
\text{with } &s_1 \in \text{Gen(BTO)},\\
\text{but }  &s_1 \not\in \text{Gen(2PL)}
\end{align*}

Some schedules are permitted by both, e.g. the empty schedule $s_2 = \emptyset$

2PL also permits some schedules, which BTO does not permit:

\begin{align*}
s_3 = r_1(x), r_2(x), c_2, w_2(x), c_2\\
\text{with } &s_3 \not\in \text{Gen(BTO)},\\
\text{but }  &s_3 \in \text{Gen(2PL)}
\end{align*}

The means, Gen(BTO) and Gen(2PL) intersect, but neither is a subset of one another.

## Exercise 2 - BOCC vs. FOCC

Hand-drawn solution in Figure \ref{e2Scan}.

\begin{figure}[ht]
    \centering
    \includegraphics[width=\columnwidth]{s6e2.pdf}
    \caption{Solution for Exercise 2}
    \label{e2Scan}
\end{figure}

## Exercise 3 - DIY Exam Question

I don't have enough time this week to be creative, sorry :)
