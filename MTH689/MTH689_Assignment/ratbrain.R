# Load the Rat brain data
library(WWGbook)
data(rat.brain)
# Create a new factor REGION.F,which has VDB (REGION=3) as the lowest value (equal to zero).
rat.brain$region.f <- 0
rat.brain$region.f[rat.brain$region == 1] <- 1
rat.brain$region.f[rat.brain$region == 2] <- 2
rat.brain$region.f[rat.brain$region == 3] <- 0
rat.brain$region.f <- factor(region.f)
# Create TREAT, which is an indicator variable for the carbachol treatment 
# i.e (TREAT=1 for carbachol, TREAT=0 for basal)
rat.brain$treat <- ifelse(rat.brain$treatment == 1, 0, 1)

# Load the nlme library
library(nlme)
# Fit a model with a “loaded” mean structure (Model 5.1)
# Model 5.1.
model5.1.fit <- lme(activate ~ region.f*treat, 
                    random = ~1 | animal, method = "REML", data = rat.brain)
plot(model5.1.fit)
summary(model5.1.fit)

# Type I(sequential) F-tests for the fixed effects in this model
anova(model5.1.fit)

#  Select a structure for the random effects (Model 5.1 vs. Model 5.2)
# Model 5.2.

plot(model5.2.fit)
summary(model5.2.fit)
anova(model5.2.fit)

# Likelihood ratio test for Hypothesis 5.1.
anova(model5.1.fit,model5.2.fit)
# The test statistic is significant (p < .001), 
# so we decide to reject the null hypothesis and retain the random treatment effects in the model

# Select a covariance structure for the residuals (Model 5.2 vs. Model 5.3)
# Model 5.3.
model5.3.fit <- lme(activate ~ region.f*treat, 
                    random = ~treat | animal, 
                    weights = varIdent(form = ~1 | treat), 
                    data = rat.brain)
plot(model5.3.fit)
summary(model5.3.fit)
anova(model5.3.fit)
# Likelihood ratio test for Hypothesis 5.2.
anova(model5.2.fit, model5.3.fit)

