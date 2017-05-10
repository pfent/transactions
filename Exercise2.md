---
header-includes:
    - \usepackage{qtree}
    - \usepackage{tikz}
---
<!-- compile with: pandoc Exercise2.md -o Exercise2.pdf -->
# Exercises for *Transaction Systems*, Sheet No. 2
Philipp Fent

## Exercise 1
Given the schedule
$$
s = r_1(x)\ r_3(x)\ w_3(y)\ w_2(x)\ c_3\ r_4(y)\ w_4(x)\ c_2\ r_5(x)\ c_4\ w_5(z)\ w_1(z)\ c_1\ c_5
$$
And the facts:
$$
H(f_{3\chi}(\gamma)) = H(f_{0\gamma}()) = f_{0\gamma}() = \gamma
$$
$$
H(f_{4\chi}(\gamma)) = H(f_{0\gamma}()) = f_{0\gamma}() = \gamma
$$
for some $\chi, \gamma$

We calculate the Herbrand semantics for all tuples: $x, y, z$

$$
H[s](x) = H[s](f_{4x}(H[s](f_{0y}()))) \stackrel{\text{initial values}}{=} H[s](f_{4x}(y)) \stackrel{t_4 \text{is \emph{copier}}}{=} H[s](y) = y
$$
$$
H[s](y) = H[s](f_{3y}(H[s](f_{0x}()))) \stackrel{\text{initial values}}{=} H[s](f_{3y}(x)) \stackrel{t_3 \text{is \emph{copier}}}{=} H[s](x) = x
$$
$$
H[s](z) = H[s](f_{1z}(H[s](f_{0x}()))) \stackrel{\text{initial values}}{=} H[s](f_{1z}(x)) = f_{1z}(x)
$$

## Exercise 2
Starting with CSR, we can draw the serialization graph for all conflits:
<!-- generated with dot2tex from s2e2.dot -->
\begin{tikzpicture}[>=latex,line join=bevel,scale=0.50]
  \pgfsetlinewidth{1bp}
%%
\pgfsetcolor{black}
  % Edge: 4 -> 5
  \draw [->] (66.222bp,72.571bp) .. controls (63.013bp,64.319bp) and (59.106bp,54.274bp)  .. (51.813bp,35.518bp);
  % Edge: 3 -> 2
  \draw [->] (107.56bp,217.3bp) .. controls (102.08bp,208.52bp) and (95.231bp,197.57bp)  .. (83.693bp,179.11bp);
  % Edge: 1 -> 2
  \draw [->] (37.669bp,217.3bp) .. controls (43.359bp,208.4bp) and (50.478bp,197.25bp)  .. (62.389bp,178.61bp);
  % Edge: 2 -> 4
  \draw [->] (73.0bp,143.83bp) .. controls (73.0bp,136.13bp) and (73.0bp,126.97bp)  .. (73.0bp,108.41bp);
  % Edge: 3 -> 4
  \draw [->] (118.72bp,215.85bp) .. controls (118.88bp,197.26bp) and (117.52bp,167.8bp)  .. (109.0bp,144.0bp) .. controls (105.24bp,133.5bp) and (99.004bp,123.04bp)  .. (86.628bp,105.88bp);
  % Edge: 5 -> 1
  \draw [->] (41.948bp,35.951bp) .. controls (40.264bp,46.435bp) and (38.264bp,59.935bp)  .. (37.0bp,72.0bp) .. controls (32.095bp,118.83bp) and (29.332bp,173.55bp)  .. (27.609bp,215.98bp);
  % Node: 1
\begin{scope}
  \definecolor{strokecol}{rgb}{0.0,0.0,0.0};
  \pgfsetstrokecolor{strokecol}
  \draw (27.0bp,234.0bp) ellipse (27.0bp and 18.0bp);
  \draw (27.0bp,234.0bp) node {1};
\end{scope}
  % Node: 3
\begin{scope}
  \definecolor{strokecol}{rgb}{0.0,0.0,0.0};
  \pgfsetstrokecolor{strokecol}
  \draw (118.0bp,234.0bp) ellipse (27.0bp and 18.0bp);
  \draw (118.0bp,234.0bp) node {3};
\end{scope}
  % Node: 2
\begin{scope}
  \definecolor{strokecol}{rgb}{0.0,0.0,0.0};
  \pgfsetstrokecolor{strokecol}
  \draw (73.0bp,162.0bp) ellipse (27.0bp and 18.0bp);
  \draw (73.0bp,162.0bp) node {2};
\end{scope}
  % Node: 5
\begin{scope}
  \definecolor{strokecol}{rgb}{0.0,0.0,0.0};
  \pgfsetstrokecolor{strokecol}
  \draw (45.0bp,18.0bp) ellipse (27.0bp and 18.0bp);
  \draw (45.0bp,18.0bp) node {5};
\end{scope}
  % Node: 4
\begin{scope}
  \definecolor{strokecol}{rgb}{0.0,0.0,0.0};
  \pgfsetstrokecolor{strokecol}
  \draw (73.0bp,90.0bp) ellipse (27.0bp and 18.0bp);
  \draw (73.0bp,90.0bp) node {4};
\end{scope}
%
\end{tikzpicture}

Where we can easily spot a cycle: $1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 1$, thus the history is **not** in CSR.

For FSR, we can calculate $LRF(s)$:
$$
LRF(s) = \{ (t_0,x,t_1),(t_0,x,t_3),(t_3,y,t_4),(t_4,x,t_\infty),(t_3,y,t_\infty),(t_1,z,t_\infty) \}
$$

From the LRF, we can see, that transaction 2 and transaction 5 are completely *dead*, so for a FSR histroy we can ignore their *reads-from* tuples. Since $t_5$ only writes to $z$, we can break the link $4 \rightarrow 5$ in the CSR graph and from there construct a FSR equivalent histroy:

$$
t_5, t_1, t_3, t_2, t_4
$$

$$
s' = r_5(x)\ w_5(z)\ c_5\ r_1(x)\ w_1(z)\ c_1\ r_3(x)\ w_3(y)\ c_3\ w_2(x)\ c_2\ r_4(y)\ w_4(x)\ c_4
$$

with the same $LRF(s') = LFR(s)$
