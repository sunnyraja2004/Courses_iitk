# --- Define helper functions ---

# Log posterior for beta_j
logf.b <- function(beta_j, beta, lambda, tau, x, y, j, t) {
  n <- nrow(x)
  p <- ncol(x)
  sum1 <- 0
  sum2 <- 0
  for (i in 1:n) {
    sum0 <- 0
    for (l in 1:p) {
      if (l != j) {
        sum0 <- sum0 + x[i, l] * beta[l, t]
      }
    }
    sum1 <- sum1 + y[i] * x[i, j] * beta_j
    sum2 <- sum2 + exp(x[i, j] * beta_j + sum0)
  }
  prior_term <- (beta_j^2) / (2 * tau^2 * lambda^2)
  ans <- sum1 - sum2 - prior_term
  return(ans)
}

# Independent MH for beta_j
IndMH.b <- function(curr, y, x_j, eta_minus_j, lambda, tau, mu, sigma) {
  prop <- rnorm(1, mu, sigma)
  ll_prop <- sum(y * x_j * prop) - sum(exp(x_j * prop + eta_minus_j))
  lp_prop <- - prop^2 / (2 * tau^2 * lambda^2)
  logp_prop <- ll_prop + lp_prop
  ll_curr <- sum(y * x_j * curr) - sum(exp(x_j * curr + eta_minus_j))
  lp_curr <- - curr^2 / (2 * tau^2 * lambda^2)
  logp_curr <- ll_curr + lp_curr
  if (log(runif(1)) < (logp_prop - logp_curr)) prop else curr
}

# Log posterior for lambda
logf.l <- function(lambda, beta_j, tau) {
  - (beta_j^2) / (2 * (tau * lambda)^2) - log(1 + lambda^2)
}

# Independent MH for lambda
IndMH.l <- function(curr, beta_j, tau, h = 1) {
  prop <- rexp(1)
  logf_prop <- logf.l(prop, beta_j, tau)
  logf_curr <- logf.l(curr,  beta_j, tau)
  logq_prop <- dexp(prop, log=TRUE)
  logq_curr <- dexp(curr, log=TRUE)
  log.ratio <- (logf_prop - logf_curr) + (logq_curr - logq_prop)
  if (log(runif(1)) < log.ratio) prop else curr
}

# Log posterior for tau
logf.t <- function(tau, c, p) {
  - c / (2 * tau^2) - p * log(tau) - log(1 + tau^2)
}

# Independent MH for tau
IndMH.t <- function(curr, c, p, s = 0.1) {
  lcurr <- log(curr)
  lprop <- rnorm(1, mean = lcurr, sd = s)
  prop  <- exp(lprop)
  logp_prop <- logf.t(prop, c, p)
  logp_curr <- logf.t(curr, c, p)
  jacobian <- lprop - lcurr
  log.ratio <- (logp_prop - logp_curr) + jacobian
  if (log(runif(1)) < log.ratio) prop else curr
}

# --- Main sampler function ---
poissonHorse <- function(y, X, n_iter, beta_start, lambda_start, tau_start) {
  n <- nrow(X)
  p <- ncol(X)
  
  # Initialize output storage
  beta   <- matrix(0, nrow = n_iter, ncol = p)
  lambda <- matrix(0, nrow = n_iter, ncol = p)
  tau    <- numeric(n_iter)
  
  # Set initial values
  beta[1, ]   <- beta_start
  lambda[1, ] <- lambda_start
  tau[1]      <- tau_start
  
  mu    <- 0
  sigma <- 1
  
  for (t in 2:n_iter) {
    # 1. Sample each β_j via component-wise MH
    eta_full <- drop(X %*% beta[t - 1, ])
    for (j in 1:p) {
      x_j <- X[, j]
      eta_minus_j <- eta_full - x_j * beta[t - 1, j]
      curr <- beta[t - 1, j]
      prop <- rnorm(1, mu, sigma)
      
      # Log-posterior values
      ll_prop <- sum(y * x_j * prop) - sum(exp(x_j * prop + eta_minus_j))
      lp_prop <- - prop^2 / (2 * tau[t - 1]^2 * lambda[t - 1, j]^2)
      logp_prop <- ll_prop + lp_prop
      
      ll_curr <- sum(y * x_j * curr) - sum(exp(x_j * curr + eta_minus_j))
      lp_curr <- - curr^2 / (2 * tau[t - 1]^2 * lambda[t - 1, j]^2)
      logp_curr <- ll_curr + lp_curr
      
      beta[t, j] <- if (log(runif(1)) < (logp_prop - logp_curr)) prop else curr
    }
    
    # 2. Sample λ via Half-Cauchy auxiliary trick
    for (j in 1:p) {
      eta_j <- 1 / (lambda[t - 1, j]^2)
      rate  <- (beta[t, j]^2) / (2 * tau[t - 1]^2)
      eta_j <- rgamma(1, shape = 1, rate = rate + 1)
      lambda[t, j] <- 1 / sqrt(eta_j)
    }
    
    # 3. Sample τ via Half-Cauchy auxiliary trick
    rate_tau <- sum((beta[t, ]^2) / (2 * lambda[t, ]^2))
    eta_tau  <- rgamma(1, shape = (p + 1) / 2, rate = rate_tau + 1)
    tau[t]   <- 1 / sqrt(eta_tau)
  }
  
  samples <- list(beta = beta, lambda = lambda, tau = tau)
  return(samples)
}

