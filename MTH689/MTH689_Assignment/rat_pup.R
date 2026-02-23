# Load the Rat Pup data
library(WWGbook)
data(ratpup)
View(ratpup)

# Encode the column sex of male as 0 and female as 1
ratpup$sex <- ifelse(ratpup$sex == "Male", 0, 1)

# box plot
boxplot(weight~treatment*sex, ratpup)
## Not suited to OLS fit because of imbalance

# Load the nlme library
library(nlme)

# Fit Model 3.1.
model3.1.fit <- lme(weight ~ treatment + sex + litsize +
                      treatment:sex, random = ~ 1 | litter,
                    data = ratpup, method = "REML")
plot(model3.1.fit)

# Summary of model fit, along with F-tests.
summary(model3.1.fit)
anova(model3.1.fit)

# Display the random effects (EBLUPs) from the model.
random.effects(model3.1.fit)

# Fit Model 3.1A.
model3.la.fit <- gls(weight ~ treatment + sex + litsize +
                       treatment:sex, data = ratpup)
plot(model3.1.fit)

anova(model3.1.fit, model3.la.fit) # Test Hypothesis 3.1.

# Fit Model 3.2A.
model3.2a.fit <- lme(weight ~ treatment + sex + litsize
                     + treatment:sex, random = ~1 | litter,data = ratpup, method = "REML",
                     weights  = varIdent(form = ~1 | treatment))
plot(model3.2a.fit)
summary(model3.2a.fit)

# Test Hypothesis 3.2.
anova(model3.1.fit, model3.2a.fit)

ratpup$trtgrp[treatment == "Control"] <- 1
ratpup$trtgrp[treatment == "Low" | treatment == "High"] <- 2

model3.2b.fit <- lme(weight ~ treatment + sex + litsize + treatment:sex,
                     random  = ~ 1 | litter,data = ratpup, method = "REML",
                     weights = varIdent(form = ~1 | trtgrp))
plot(model3.2b.fit)

# Test Hypothesis 3.3.
anova(model3.2a.fit, model3.2b.fit)

# Test Hypothesis 3.4.
anova(model3.1.fit, model3.2b.fit)

summary(model3.2b.fit)

# Test Hypothesis 3.5.
anova(model3.2b.fit)

model3.3.ml.fit <- lme(weight ~ treatment + sex + litsize,
                       random = ~1 | litter, data = ratpup, method = "ML",
                       weights = varIdent(form = ~1 | trtgrp))
plot(model3.3.ml.fit)

model3.3a.ml.fit <- lme(weight ~ sex + litsize,
                        random = ~1 | litter, data = ratpup, method = "ML",
                        weights = varIdent(form = ~1 | trtgrp))
plot(model3.3a.ml.fit)

# Test Hypothesis 3.6.
anova(model3.3.ml.fit, model3.3a.ml.fit)

# Model 3.3: Final Model.
model3.3.reml.fit <- lme(weight ~ sex + litsize + treatment,
                         random  = ~1 | litter, data = ratpup, method = "REML",
                         weights = varIdent(form = ~1 | trtgrp))
plot(model3.3.reml.fit)
summary(model3.3.reml.fit)
anova(model3.3.reml.fit)
