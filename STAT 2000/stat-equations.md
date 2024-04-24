# Statistics Equations


## Linear Regression Model
### Calculating The Estimated Slope
$$b_1 = \frac{\sum{(x_i - \bar{x})}(y_i - \bar{y})}{\sum{(x_i - \bar{x})^2}}$$

### Calculating The Estimated Intercept
$$b_0 = \bar{y} - b_1\bar{x}$$

## ANOVA Table
|  |**df**|**Sum of Squares**|**Mean Square**|**F**|
|-------|----|----------------|-------------|---|
| **Regression** | $1$ | $\sum{(\hat{y} - \bar{y})^2}$ | $SSR/1$ | $MSR/MSE$ |
| **Error** | $n - 2$ | $\sum{(y_i - \bar{y})^2}$ | $SSE/(n-2)$ | 
| **Total** | $n - 1$ | $\sum{(y_i - y)^2}$ | 

## Confidence Intervals
### For Mean Y
$\hat{y} \pm t^*SE_{\hat{\mu}}$

### For Slope
$b_1 \pm t^*SE_{b_1}$

## Grand Mean
$$\bar{\bar{x}} = \frac{\sum_{i=1}^I{(n_i\bar{x_i})}}{N}$$
