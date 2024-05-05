# l1 min

常见的 $\ell_1$ minimization 问题：
$$
\begin{aligned}
\min_x \quad& \mu \|x\|_1 \\
s.t. \quad & \frac{1}{2}\|Ax-b\|_{2} = 0 \quad(1)\\
\quad & x \in \mathbb{R^n},
\end{aligned}
$$


$$
\begin{aligned}
&\min_x \mu \|x\|_1+\frac{1}{2}\|Ax-b\|_{2}^2,& (2)\\
&\min_{x}\mu\|x\|_{1}+\|Ax-b\|_{2},&(3)\\
&\min_{x}\mu\|x\|_{1}+\|Ax-b\|_{1},&(4)\\
&\min_x \mu \|x\|_1+\frac{1}{2}\|Ax-b\|_{\infty},&(5)\\
&\min_{x}\mu\|x\|_{1/2}+\|Ax-b\|_{2},&(6)\\
\end{aligned}$$

