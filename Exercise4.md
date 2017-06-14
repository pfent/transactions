---
header-includes:
    - \usepackage{tikz}
---
<!-- compile with: pandoc Exercise4.md -o Exercise4.pdf -->
# Exercises for *Transaction Systems*, Sheet No. 4
Philipp Fent  
MatrNr: 03647020

## Exercise 1

Draw the serialization graph for:
$$
 s = w_1(x)\ r_1(y)\ r_2(z)\ w_2(y)\ w_1(z)
$$

To draw the relative serialization graph, we need to draw 4 different edges:

1. I-edges
2. D-edges
3. F-edges
4. B-edges

**I-edges** are the simplest type, just connecting consecutive operations of the same transaction:
\begin{align*}
w_1(x) &\to_I r_1(y)\\
r_1(y) &\to_I w_1(z)\\
r_2(z) &\to_I w_2(y)\\
\end{align*}

**D-edges** are a bit more involved. To check the conditions for those, we first need to calculate $p \sim> q$ (if $p <_s q$ either $p_i <_t q_i$ or $p$ and $q$ are in conflict):
\begin{align*}
w_1(x) &\sim> r_1(y)\\
r_1(y) &\sim> w_2(y)\\
r_1(y) &\sim> w_1(z)\\
r_2(z) &\sim> w_2(y)\\
r_2(z) &\sim> w_1(z)\\
\end{align*}

Then we can build the transitive hull, *adding* some more depends on relations:
\begin{align*}
w_1(x) &\sim>^* w_2(y)\\
w_1(x) &\sim>^* w_1(z)\\
\end{align*}

Now, we draw D-edges from $p_i \sim>^* q_j, \iff i \neq j$, i.e.
\begin{align*}
r_1(y) &\to_D w_2(y)\\
w_1(x) &\to_D w_2(y)\\
r_2(z) &\to_D w_1(z)\\
\end{align*}

**F-edges** are calculated using the D-edges, i.e. $p_i \to_D q_j \Rightarrow F(p, t_j) \to_F q$

\begin{align*}
&r_1(y) \to_D w_2(y) &&\Rightarrow &&F(r_1(y), t_2) \to_F w_2(y) &&\Rightarrow &&r_1(y) \to_F w_2(y)\\
&w_1(x) \to_D w_2(y) &&\Rightarrow &&F(w_1(x), t_2) \to_F w_2(y) &&\Rightarrow &&r_1(y) \to_F w_2(y)\\
&r_2(z) \to_D w_1(z) &&\Rightarrow &&F(r_2(z), t_1) \to_F w_1(z) &&\Rightarrow &&w_2(y) \to_F w_1(z)\\
\end{align*}

**B-edges** are calculated using the D-edges, i.e. $p_i \to_D q_j \Rightarrow p \to_B B(q, t_i)$

\begin{align*}
&r_1(y) \to_D w_2(y) &&\Rightarrow &&r_1(y) \to_B B(w_2(y), t_1) &&\Rightarrow &&r_1(y) \to_F r_2(z)\\
&w_1(x) \to_D w_2(y) &&\Rightarrow &&w_1(x) \to_B B(w_2(y), t_1) &&\Rightarrow &&w_1(x) \to_F r_2(z)\\
&r_2(z) \to_D w_1(z) &&\Rightarrow &&r_2(z) \to_B B(w_1(z), T_2) &&\Rightarrow &&r_2(z) \to_F w_1(z)\\
\end{align*}

Now, we can plug everything into a nice DOT graph, to see if the RSG(s) is acyclic:

\begin{tikzpicture}[anchor=mid,>=latex,line join=bevel,]
  \pgfsetlinewidth{1bp}
\pgfsetcolor{black}
  % Edge: w1(x) -> w2(y)
  \draw [->] (89.694bp,347.77bp) .. controls (67.664bp,325.49bp) and (32.89bp,285.51bp)  .. (19.0bp,243.0bp) .. controls (7.0967bp,206.57bp) and (13.535bp,161.93bp)  .. (22.542bp,123.4bp);
  \definecolor{strokecol}{rgb}{0.0,0.0,0.0};
  \pgfsetstrokecolor{strokecol}
  \draw (29.5bp,235.5bp) node { D};
  % Edge: w2(y) -> w1(z)
  \draw [->] (39.71bp,86.619bp) .. controls (46.243bp,76.715bp) and (54.713bp,64.423bp)  .. (63.0bp,54.0bp) .. controls (65.671bp,50.64bp) and (68.576bp,47.201bp)  .. (78.358bp,36.246bp);
  \draw (72.5bp,61.5bp) node { F};
  % Edge: r2(z) -> w1(z)
  \draw [->] (107.63bp,173.71bp) .. controls (105.36bp,143.34bp) and (100.81bp,82.323bp)  .. (97.348bp,36.047bp);
  \draw (123.0bp,105.0bp) node { D, B};
  % Edge: w1(x) -> r2(z)
  \draw [->] (121.69bp,347.98bp) .. controls (130.25bp,334.61bp) and (140.74bp,315.57bp)  .. (145.0bp,297.0bp) .. controls (151.97bp,266.66bp) and (147.05bp,255.77bp)  .. (133.0bp,228.0bp) .. controls (131.43bp,224.89bp) and (129.63bp,221.72bp)  .. (122.34bp,210.17bp);
  \draw (158.0bp,279.0bp) node { B};
  % Edge: r1(y) -> w1(z)
  \draw [->] (122.34bp,260.83bp) .. controls (126.08bp,255.27bp) and (129.95bp,249.03bp)  .. (133.0bp,243.0bp) .. controls (164.43bp,180.89bp) and (168.78bp,153.12bp)  .. (147.0bp,87.0bp) .. controls (141.77bp,71.136bp) and (131.34bp,55.932bp)  .. (114.42bp,36.021bp);
  \draw (168.0bp,148.5bp) node { I};
  % Edge: w1(x) -> r1(y)
  \draw [->] (109.0bp,347.97bp) .. controls (109.0bp,336.19bp) and (109.0bp,320.56bp)  .. (109.0bp,297.0bp);
  \draw (117.0bp,322.5bp) node { I};
  % Edge: r1(y) -> w2(y)
  \draw [->] (81.751bp,262.45bp) .. controls (64.446bp,250.29bp) and (43.413bp,232.08bp)  .. (33.0bp,210.0bp) .. controls (21.629bp,185.88bp) and (21.608bp,155.1bp)  .. (24.834bp,123.09bp);
  \draw (53.0bp,192.0bp) node { D, F};
  % Edge: r2(z) -> w2(y)
  \draw [->] (85.352bp,173.88bp) .. controls (78.804bp,168.43bp) and (71.884bp,162.23bp)  .. (66.0bp,156.0bp) .. controls (58.908bp,148.49bp) and (51.927bp,139.67bp)  .. (40.053bp,123.27bp);
  \draw (74.0bp,148.5bp) node { I};
  % Edge: r1(y) -> r2(z)
  \draw [->] (109.0bp,260.97bp) .. controls (109.0bp,249.19bp) and (109.0bp,233.56bp)  .. (109.0bp,210.0bp);
  \draw (119.0bp,235.5bp) node { B};
  % Node: w1(x)
\begin{scope}
  \tikzset{text=red}
  \draw (109.0bp,366.0bp) node {w1(x)};
\end{scope}
  % Node: w1(z)
\begin{scope}
  \tikzset{text=red}
  \draw (96.0bp,18.0bp) node {w1(z)};
\end{scope}
  % Node: w2(y)
\begin{scope}
  \tikzset{text=blue}
  \draw (28.0bp,105.0bp) node {w2(y)};
\end{scope}
  % Node: r2(z)
\begin{scope}
  \tikzset{text=blue}
  \draw (109.0bp,192.0bp) node {r2(z)};
\end{scope}
  % Node: r1(y)
\begin{scope}
  \tikzset{text=red}
  \draw (109.0bp,279.0bp) node {r1(y)};
\end{scope}
\end{tikzpicture}


