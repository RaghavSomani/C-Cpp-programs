library(ISLR)
library(MASS)
lda.fit = lda(Direction~Lag1+Lag2,data=Smarket,subset=Year<2005)
lda.fit
summary(lda.fit)
plot(lda.fit)
Smarket.2005 = subset(Smarket,Year==2005)
lda.pred = predict(lda.fit,Smarket.2005)
data.frame(lda.pred)[1:5,]
table(lda.pred$class,Smarket.2005$Direction)
mean(lda.pred$class==Smarket.2005$Direction)