# Salp

Salp, an easy to learn/use linear algebra library for Javascript.

It supports NodeJS as well as browser builds and has no third-party dependencies.

If you have a question, problem or feature request, feel free to contact me anytime. The best way (for me) is to use the [Github issue tracker](https://github.com/SebastianNiemann/Mantella/issues).

## Roadmap

- Support of basic matrix manipulations
- Support of matrix layout manipulations
- Support of common mathematical & trigonometric functions
- Support of common statistical functions
- Support of common set operations
- Support of common decompositions, factorizations, inversions and equation solvers
- Support of complex numbers
- Acceleration of BLAS/LAPACK-like operations with WebAssembly

## API

### Fields

- `.nElems`

  The number of elements.
  
  Same as `mat.nRows * mat.nCols`.

- `.nRows`

  The number of rows.

- `.nCols`

  The number of columns.

- `._raw`
- `._rng`

### Creation

- `new Mat()`
- `empty(nRows, nCols)`

    Shorthand for: `new Mat(nRows, nCols)`

- `zeros(nRows, nCols)`

    Shorthand for: `new Mat(nRows, nCols, () => 0)`

- `ones(nRows, nCols)`

    Shorthand for: `new Mat(nRows, nCols, () => 1)`

- `identity(nRows, nCols)`

    Shorthand for: `zeros(nRows, nCols).diag(() => 0)`

- `normal(nRows, nCols)`
- `uniform(nRows, nCols)`
- `gamma(nRows, nCols)`
- `arange()`
- `linspace()`
- `logspace()`
- `geomspace()`
- `meshGrid()`
- `repeat()`
- `sample()`

### Inplace-Manipulation and Access

- `.elem()`
- `.elemDiag()`
- `.col()`
- `.row()`
- `.rotate()`
- `.rotateCol()`
- `.rotateRow()`
- `.fill()`
- `.replace()`
- `.shuffle(mat)`
- `.clamp(mat, lowerBounds, upperBounds)`

### Layout

- `.resize(nRows, nCols)`
- `.flat()`
- `.appendCol()`
- `.appendRow()`
- `.prependCol()`
- `.prependRow()`
- `.insertCol()`
- `.insertRow()`
- `.removeCol()`
- `.removeRow()`
- `.lowerTriangular()`
- `.upperTriangular()`

### Functional

- `.map(callback)`
- `.mapCol(callback)`
- `.mapRow(callback)`
- `.reduce(callback, initialValue)`
- `.reduceCol(callback, initialValue)`
- `.reduceRow(callback, initialValue)`
- `.filter(callback)`
- `.filterCol()`
- `.filterRow()`
- `.some()`
- `.someCol()`
- `.someRow()`
- `.every()`
- `.everyCol()`
- `.everyRow()`
- `.none()`
- `.noneCol()`
- `.noneRow()`
- `.reverse()`
- `.reverseCol()`
- `.reverseRow()`
- `.sort()`
- `.sortCol()`
- `.sortRow()`
- `.count()`
- `.countCol()`
- `.countRow()`
- `swapElems()`
- `swapCols()`
- `swapRows()`

### Output

- `.toString(precision=5)`

### Logical

- `isApprox()`
- `isGreater()`
- `isGreaterOrEqual()`
- `isLess()`
- `isLessOrEqual()`
- `isEqual()`
- `isBetween()`
- `isEmpty()`
- `isVector()`
- `isCol()`
- `isRow()`
- `isSquare()`
- `isSymmetric()`
- `isPositiveDefinite()`
- `isFinite()`
- `hasInf()`
- `hasNaN()`
- `hasNull()`
- `find()`

### Statistic

- `min(mat)`
- `max(mat)`
- `range(mat)`
- `mode(mat)`
- `quantile(mat, q, k)`
- `median(mat)`

    Shorthand for: `quantile(mat, 2, 1)`

- `quartile(mat, k)`

    Shorthand for: `quantile(mat, 4, k)`

- `decile(mat, k)`

    Shorthand for: `quantile(mat, 10, k)`

- `percentile(mat, k)`

    Shorthand for: `quantile(mat, 100, k)`

- `interquartileRange(mat)`
- `mean(mat)`
- `centralMoment(mat, k)`
- `variance(mat)`
- `standardDeviation(mat)`
- `standardizedCentralMoment(mat, k)`
- `skewness(mat)`
- `kurtosis(mat)`
- `histogram()`
- `minIndex()`
- `maxIndex()`
- `covariance()`
- `correlation()`
- `comulative(mat, callback)`
- `diff(mat, callback)`

### Trigonometric

- `.acos()`

    Shorthand for: `mat.map(Math.acos)`

- `.acosh()`

    Shorthand for: `mat.map(Math.acosh)`

- `.acot()`

    Shorthand for: `mat.map(salp._scalarAcot)`

- `.acoth()`

    Shorthand for: `mat.map(salp._scalarAcoth)`

- `.acsc()`

    Shorthand for: `mat.map(salp._scalarAcsc)`

- `.acsch()`

    Shorthand for: `mat.map(salp._scalarAcsch)`

- `.asec()`

    Shorthand for: `mat.map(salp._scalarAsec)`

- `.asech()`

    Shorthand for: `mat.map(salp._scalarAsech)`
  
- `.asin()`

    Shorthand for: `mat.map(Math.asin)`

- `.asinh()`

    Shorthand for: `mat.map(Math.asinh)`

- `.atan()`

    Shorthand for: `mat.map(Math.atan)`

- `.atanh()`

    Shorthand for: `mat.map(Math.atanh)`

- `.cos()`

    Shorthand for: `mat.map(Math.cos)`

- `.cosh()`

    Shorthand for: `mat.map(Math.cosh)`

- `.cot()`

    Shorthand for: `mat.map(salp._scalarCot)`

- `.coth()`

    Shorthand for: `mat.map(salp._scalarCoth)`

- `.csc()`

    Shorthand for: `mat.map(salp._scalarCsc)`

- `.csch()`

    Shorthand for: `mat.map(salp._scalarCsch)`

- `.sec()`

    Shorthand for: `mat.map(salp._scalarSec)`

- `.sech()`

    Shorthand for: `mat.map(salp._scalarSech)`

- `.sin()`

    Shorthand for: `mat.map(Math.sin)`

- `.sinc(flavor='normalised')`

    If `flavor` is set to `'normalised'`:

    Shorthand for: `mat.map(x => salp._scalarSinc(Math.PI * x))`

    If `flavor` is set to `'unnormalised'`:

    Shorthand for: `mat.map(salp._scalarSinc)`

- `.sinh()`

    Shorthand for: `mat.map(Math.sinh)`

- `.sinhc()`

    Shorthand for: `mat.map(salp._scalarSinhc)`

- `.tan()`

    Shorthand for: `mat.map(Math.tan)`

- `.tanc()`

    Shorthand for: `mat.map(salp._scalarTanc)`

- `.tanh()`

    Shorthand for: `mat.map(Math.tanh)`

- `.tanhc()`

    Shorthand for: `mat.map(salp._scalarTanhc)`

- `atan2(matA, matB)`
- `hypot(matA, matB)`

### Sets

- `setIntersect(matA, matB)`
- `setDifference(matA, matB)`
- `setSymmetricDifference(matA, matB)`
- `setUnion(matA, matB)`
- `unique(mat)`

### Mathematical functions

- `.erf()`
- `.gamma()`
- `.negate()`

    Shorthand for: `mat.map(x => -x)`

- `.reciprocal()`

    Shorthand for: `mat.map(x => 1 / x)`

- `.mod()`
- `.remainder()`
- `.abs()`

    Shorthand for: `mat.map(Math.abs)`

- `.ceil()`

    Shorthand for: `mat.map(Math.ceil)`

- `.floor()`

    Shorthand for: `mat.map(Math.floor)`

- `.round()`

    Shorthand for: `mat.map(Math.round)`

- `.log()`

    Shorthand for: `mat.map(Math.log)`.

- `.logK(k)`

    Shorthand for:
    
    ```js
    const log2k = Math.log2(k);
    mat.map(x => Math.log2(x) / log2k);
    ```

- `.log2()`

    Shorthand for: `mat.map(Math.log2)`

- `.log10()`

    Shorthand for: `mat.map(Math.log10)`

- `.pow(exponent)`

    Shorthand for: `mat.map(x => Math.pow(x, exponent))`

- `.root(k)`

    Shorthand for: `mat.pow(1 / k)`

- `.sqrt()`

    Shorthand for: `mat.map(Math.sqrt)`

- `.clz32()`

    Shorthand for: `mat.map(Math.clz32)`

- `.expm1()`

    Shorthand for: `mat.map(Math.expm1)`

- `.fround()`

    Shorthand for: `mat.map(Math.fround)`

- `.log1p()`

    Shorthand for: `mat.map(Math.log1p)`

- `.square()`

    Shorthand for: `mat.pow(2)`

- `.cube()`

    Shorthand for: `mat.pow(3)`

- `.cbrt()`

    Shorthand for: `mat.map(Math.cbrt)`

- `.sign()`

    Shorthand for: `mat.map(Math.sign)`

- `.exp()`

    Shorthand for: `mat.map(Math.exp)`

- `.expK(k)`

    Shorthand for: `mat.map(x => Math.pow(k, x))`

- `.exp2()`

    Shorthand for: `mat.expK(2)`

- `.exp10()`

    Shorthand for: `mat.expK(10)`

- `.deg2Rad()`
- `.rad2Deg()`

- `.trunc()`

    Shorthand for: `mat.map(Math.trunc)`

### Linear algebra

- `cond()`
- `cross()`
- `dot()`
- `det()`
- `transpose()`
- `kron()`
- `norm()`
- `rank()`
- `add()`
- `multiply()`
- `subtract()`
- `divide()`
- `trace()`

---

Distributed under [MIT license](http://opensource.org/licenses/MIT).
