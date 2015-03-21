$$\begin{align}
F(X) &:= \left\Vert \prod_{i = 1}^{N} \left| Z_i \right| S_i \right\Vert_{2}\\
Z &:= R \cdot \left( X - X^\text{opt} \right)\\
S &:= T_\text{scaled} \left( Z^{2} \right)
\end{align}$$

**DifferentPowersFunction( <small>unsigned int</small> N )**

- Creates an *N*-dimensional optimisation problem instance of this class.
- The problem must have at least 1 dimension.

---
**<small>void</small> .setXOpt( <small>arma::Col&lt;T&gt;</small> X )**

- Parameterises the transition by variable \\(X^\text{opt}\\).

---
**<small>void</small> .setR( <small>arma::Mat&lt;T&gt;</small> R )**

- Parameterises the rotation by variable \\(R\\).
- The rotation matrix must be orthonormal \\(\left( R^{t} = R^{-1} \right)\\) with determinant 1 or -1.

---
**<small>std::string</small> .toString()** {% include noexcept %}

- Returns a filesystem friendly name of the problem, i.e. *different-powers-function*.