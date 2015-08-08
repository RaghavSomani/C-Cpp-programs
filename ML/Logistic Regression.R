library(ISLR)
library(MASS)
names(Smarket)
summary(Smarket)
pairs(Smarket,col = Smarket$Direction)
glm.fit = glm(Direction ~ Lag1+Lag2+Lag3+Lag4+Lag5+Volume,data=Smarket,family = binomial)
glm.fit
summary(glm.fit)
glm.probs = predict(glm.fit,type="response")
glm.probs[1:5]
glm.pred = ifelse(glm.probs>0.5,"Up","Down")
attach(Smarket)
table(glm.pred,Direction)
mean(glm.pred==Direction)
train=Year<2005
glm.fit = glm(Direction~Lag1+Lag2+Lag3+Lag4+Lag5+Volume,data=Smarket,subset=train,family = binomial)
glm.probs = predict(glm.fit,newdata=Smarket[!train,],type = "response")
glm.pred = ifelse(glm.probs>0.5,"Up","Down")
Direction.2005 = Smarket$Direction[!train]
table(Direction.2005,glm.pred)
mean(Direction.2005==glm.pred)
glm.fit = glm(Direction~Lag1+Lag2,data=Smarket,subset=train,family = binomial)
glm.probs = predict(glm.fit,newdata=Smarket[!train,],type = "response")
glm.pred = ifelse(glm.probs>0.5,"Up","Down")
Direction.2005 = Smarket$Direction[!train]
table(Direction.2005,glm.pred)
mean(Direction.2005==glm.pred)
summary(glm.fit)
