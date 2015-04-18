library(MASS)
library(ISLR)
attach(Smarket)

training = (Year < 2005)
testing = !training
training_data = Smarket[training,]
testing_data = Smarket[testing,]
Direction_testing=Direction[testing]

lr_model=glm(Direction ~ Lag1+Lag2+Lag3+Lag4+Lag5+Volume, data=training_data, family=binomial)
summary(lr_model)
lr_pred_probs = predict(lr_model, testing_data, type="response")
lr_pred_Direction=rep("Down",252)
lr_pred_Direction[lr_pred_probs>0.5]="Up"
table(lr_pred_Direction,Direction_testing)
cat("Misclassifications\n")
lr_mis=mean(lr_pred_Direction!=Direction_testing)
cat("LR : ",lr_mis,"\n")

lda_model=lda(Direction~Lag1+Lag2+Lag3+Lag4+Lag5+Volume,data=training_data)
lda_pred=predict(lda_model,testing_data)
lda_pred_Direction=lda_pred$class
table(lda_pred_Direction,Direction_testing)
lda_mis=mean(lda_pred_Direction!=Direction_testing)
cat("LDA : ",lda_mis,"\n")

qda_model=qda(Direction~Lag1+Lag2+Lag3+Lag4+Lag5+Volume,data=training_data)
qda_pred=predict(qda_model,testing_data)
qda_pred_Direction=qda_pred$class
table(qda_pred_Direction,Direction_testing)
qda_mis=mean(qda_pred_Direction!=Direction_testing)
cat("QDA : ",qda_mis,"\n")

library(class)
std_data=scale(Smarket[,c(2,3,4,5,6,7)])
training_data=std_data[training,]
testing_data=std_data[testing,]
training_Direction=Direction[training]
knn_pred_Direction=knn(training_data,testing_data,training_Direction,3)
table(knn_pred_Direction,Direction_testing)
knn_mis=mean(knn_pred_Direction!=Direction_testing)
cat("KNN : ",knn_mis)